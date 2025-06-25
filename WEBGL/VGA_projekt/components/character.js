import { gameSettings } from '../config/gameSettings.js'

AFRAME.registerComponent('character', {
    schema: {
        health: {
            type: 'int',
            default: gameSettings.player.health
        }
    },

    init() {
        console.log('[ Character initialized ]');

        this.characterModel = this.el.children[0];
        this.walkSpeed = gameSettings.player.walkSpeed;
        this.runSpeed = gameSettings.player.runSpeed;
        this.jumpForce = gameSettings.player.jumpForce;

        this.pressedMovementKeys = {
            up: false,
            down: false,
            left: false,
            right: false
        };

        this.isDead = false;
        this.isRunning = false;
        this.isJumping = false;
        this.rotationY = null;
        this.velocity = null;

        this.secondsPlayed = 0;

        this.health = this.data.health;
        this.collisionBodies = [];

        this.passcodes = []; // int array of collected passcodes used to open doors

        // Initialize health display
        if (window.gameUI) {
            window.gameUI.updateHealth(this.health);
        }

        // Setup collision listener
        this.el.addEventListener('collide', event => this.processCollision(event))

        // Setup hit listener
        this.el.addEventListener('hit', event => {
            if (this.isDead) return;

            // Calculate new health and ensure it doesn't go below 0
            const newHealth = Math.max(0, this.health - event.detail.damage);
            this.health = newHealth;
            this.hits++;

            // Update UI
            if (window.gameUI) {
                window.gameUI.updateHealth(this.health);
                window.gameUI.incrementHits();
            }

            if (this.health <= 0 && !this.isDead) {
                this.die();
            }
        });

        // Notify UI about elapsed time
        this.timerInterval = setInterval(() => {
            if (this.isDead) {
                clearInterval(this.timerInterval);
                return;
            }
            this.secondsPlayed += 1;
            window.gameUI.updateSecondsPlayed(this.secondsPlayed);
        }, 1000);

        this.playWelcomeAnimation();
        this.setupMovementKeyListener();
        this.setupGroundCollisionListener();
    },

    setupGroundCollisionListener() {
        // Listen for ground collisions to detect landing
        this.el.addEventListener('collide', (e) => {
            if (e.detail.contact.ni.y > 0.5) {
                this.isJumping = false;
                this.updateMovement();
            }
        });
    },

    setupMovementKeyListener() {
        // Key press
        document.addEventListener('keydown', (event) => {
            const key = event.key.toLowerCase();

            if (key === 'shift' && !this.isJumping) {
                this.isRunning = true;
                this.updateMovement();
                return;
            }

            if (key === ' ' && !this.isJumping) {
                this.jump();
                return;
            }

            let inputsChanged = false;

            switch(key) {
                case 'w':
                case 'arrowup':
                    this.pressedMovementKeys.up = true;
                    inputsChanged = true;
                    break;
                case 's':
                case 'arrowdown':
                    this.pressedMovementKeys.down = true;
                    inputsChanged = true;
                    break;
                case 'a':
                case 'arrowleft':
                    this.pressedMovementKeys.left = true;
                    inputsChanged = true;
                    break;
                case 'd':
                case 'arrowright':
                    this.pressedMovementKeys.right = true;
                    inputsChanged = true;
                    break;
            }

            if (inputsChanged) {
                this.updateMovement();
            }
        });

        // Key release
        document.addEventListener('keyup', (event) => {
            const key = event.key.toLowerCase();

            if (key === 'shift') {
                this.isRunning = false;
                this.updateMovement();
                return;
            }

            let inputsChanged = false;

            switch(key) {
                case 'w':
                case 'arrowup':
                    this.pressedMovementKeys.up = false;
                    inputsChanged = true;
                    break;
                case 's':
                case 'arrowdown':
                    this.pressedMovementKeys.down = false;
                    inputsChanged = true;
                    break;
                case 'a':
                case 'arrowleft':
                    this.pressedMovementKeys.left = false;
                    inputsChanged = true;
                    break;
                case 'd':
                case 'arrowright':
                    this.pressedMovementKeys.right = false;
                    inputsChanged = true;
                    break;
            }

            if (inputsChanged) {
                this.updateMovement();
            }
        });
    },

    jump() {
        if (this.isDead) return;

        this.el.body.velocity.y = this.jumpForce;
        this.isJumping = true;

        // Slow down current animation
        this.characterModel.setAttribute('animation-mixer', {
            crossFadeDuration: 0.2,
            repetitions: 'Infinity',
            timeScale: this.isRunning? -0.5 : 0.5,
        });
    },

    tick() {
        if (this.isDead) return;

        if (this.velocity) {
            const currentVelocity = this.el.body.velocity;
            this.el.body.velocity.set(this.velocity.x, currentVelocity.y, this.velocity.z);
        }
    },

    updateMovement() {
        if (this.isDead) return;

        let dx = 0, dz = 0;
        if (this.pressedMovementKeys.up) dz -= 1;
        if (this.pressedMovementKeys.down) dz += 1;
        if (this.pressedMovementKeys.left) dx -= 1;
        if (this.pressedMovementKeys.right) dx += 1;

        if (dx === 0 && dz === 0) {
            this.stopMovement();
            return;
        }

        const movementSpeed = this.isRunning ? this.runSpeed : this.walkSpeed;

        if (dx !== 0 && dz !== 0) {
            const length = Math.sqrt(dx * dx + dz * dz);
            dx /= length;
            dz /= length;
        }

        dx *= movementSpeed;
        dz *= movementSpeed;
        this.velocity = new CANNON.Vec3(dx, 0, dz);

        this.updateRotation(dx, dz);

        // Do not play other animations while jumping
        if (this.isJumping) return;

        // Play run or walk animation
        this.characterModel.setAttribute('animation-mixer', {
            clip: this.isRunning ? '*Run_Back*' : '*Walk*',
            crossFadeDuration: 0.2,
            repetitions: 'Infinity',
            timeScale: this.isRunning ? -1 : 1.5,
        });
    },

    updateRotation(dx, dz) {
        let targetRotation;
        if (dx !== 0 && dz !== 0) {
            targetRotation = dx > 0 ? (dz > 0 ? 45 : 135) : (dz > 0 ? -45 : -135);
        } else {
            targetRotation = dx !== 0 ? (dx > 0 ? 90 : -90) : (dz > 0 ? 0 : 180);
        }

        let currentRotation = this.rotationY || 0;
        let rotationDiff = targetRotation - currentRotation;

        while (rotationDiff > 180) rotationDiff -= 360;
        while (rotationDiff < -180) rotationDiff += 360;

        this.rotationY = currentRotation + rotationDiff;

        // Animate rotation
        this.characterModel.setAttribute('animation', {
            property: 'rotation',
            to: { x: 0, y: this.rotationY, z: 0 },
            dur: 200,
            easing: 'easeOutQuad'
        });
    },

    stopMovement() {
        this.velocity = null;

        // Play idle animation
        this.characterModel.setAttribute('animation-mixer', {
            clip: '*Idle_Neutral*',
            crossFadeDuration: 0.2,
            repetitions: 'Infinity',
        });
    },

    playWelcomeAnimation() {
        this.characterModel.addEventListener('animation-finished', (e) => {
            // Play idle animation
            if (this.isDead) return;
            this.characterModel.setAttribute('animation-mixer', {
                clip: '*Idle_Neutral*',
                crossFadeDuration: 0.2,
                repetitions: 'Infinity',
                timeScale: 1
            });
        });

        setTimeout(() => {
            // Play wave animation
            this.characterModel.setAttribute('animation-mixer', {
                clip: '*Wave*',
                crossFadeDuration: 0.2,
                repetitions: 1,
                timeScale: 1
            });
        },  500);
    },

    die() {
        if (this.isDead) return;

        this.isDead = true;
        this.stopMovement();

        // Play death animation once
        this.characterModel.removeAttribute('animation-mixer');
        this.characterModel.setAttribute('animation-mixer', {
            clip: '*Death*',
            crossFadeDuration: 0.2,
            repetitions: 1,
            clampWhenFinished: true,
            timeScale: 1.3
        });

        setTimeout(() => {
            // Emit game over event
            this.el.emit('game-over');

            // Notify UI
            if (window.gameUI) {
                window.gameUI.gameOver();
            }
        }, 800);
    },

    processCollision(event) {
        if (this.isDead) return; // Don't process collisions if dead

        const otherEntity = event.detail.body;

        // consider only collisions with obstacles (entities having obstacle component)
        if (!otherEntity.el.hasAttribute('obstacle')) {
            return;
        }

        // do not collide repeatedly with the same entity
        if (this.collisionBodies.includes(otherEntity)) {
            return;
        }

        // add the entity, which we collided with, to the array, so we can avoid another collision with the same entity
        this.collisionBodies.push(otherEntity);

        // if there is a delay of at least 500ms between the collisions, enable collision with the same entity
        // in other words: remove the collided entity from the array after 500ms if no other collisions happen in the meantime
        clearTimeout(this.clearTimeout);
        this.clearTimeout = setTimeout(() =>
                this.collisionBodies.splice(this.collisionBodies.indexOf(otherEntity)),
            500
        );

        // Calculate new health and ensure it doesn't go below 0
        const damage = gameSettings.obstacles.defaultDamage;
        this.health = Math.max(0, this.health - damage);

        if (window.gameUI) {
            window.gameUI.updateHealth(this.health);
            window.gameUI.showHealthChange(-damage);
        }
        console.log('Health', this.health)

        // if there is no health remaining, trigger death
        if (this.health <= 0 && !this.isDead) {
            console.log('Health reached 0, triggering death');
            this.die();
        }

        // tell the other entity that the collision happened, so it can destroy itself
        otherEntity.el.emit('collide-with-character')
    },

    addPasscode(code) {
        if (!this.passcodes.includes(code)) {
            this.passcodes.push(code);
            console.log('Added passcode:', code);
        }
    },

    hasPasscode(code) {
        return this.passcodes.includes(code);
    }
});
