AFRAME.registerComponent('health-pickup', {
    schema: {
        healAmount: {
            type: 'int',
            default: 50
        },
        rotationSpeed: {
            type: 'number',
            default: 0.5
        }
    },
    init() {
        console.log('Health pickup initialized!');

        this.hasBeenCollected = false;

        // Add floating animation
        this.yOffset = 0;
        this.floatSpeed = 0.5;
        this.initialY = this.el.object3D.position.y;

        // Handle pickup with E key via raycaster collision
        this.el.addEventListener('raycaster-intersected', () => {
            this.isIntersected = true;
        });

        this.el.addEventListener('raycaster-intersected-cleared', () => {
            this.isIntersected = false;
        });

        document.addEventListener('keydown', this.onKeyDown.bind(this));
    },

    onKeyDown(event) {
        if (event.key.toLowerCase() === 'e' && this.isIntersected && !this.hasBeenCollected) {
            this.collectHealthPickup();
        }
    },

    collectHealthPickup() {
        if (this.hasBeenCollected) return;

        this.hasBeenCollected = true;

        // Update health in game UI
        if (window.gameUI) {
            const currentHealth = window.gameUI.health;
            const maxHealth = window.gameUI.maxHealth;
            const newHealth = Math.min(currentHealth + this.data.healAmount, maxHealth);

            window.gameUI.updateHealth(newHealth);
            window.gameUI.showHealthChange(this.data.healAmount);
            console.log(`Health pickup collected! Added ${this.data.healAmount} health.`);
        }

        // Remove the entity
        setTimeout(() => this.el.remove(), 0);
    },

    tick(time, deltaTime) {
        if (this.hasBeenCollected) return;

        // Rotate the health pickup
        this.el.object3D.rotation.y += this.data.rotationSpeed * (deltaTime / 1000);

        // Float up and down
        this.yOffset += this.floatSpeed * (deltaTime / 1000);
        const newY = this.initialY + Math.sin(this.yOffset) * 0.1;
        this.el.object3D.position.y = newY;
    }
});
