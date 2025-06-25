AFRAME.registerComponent('doors', {
    schema: {
        passcode: {
            type: 'int',
            default: null
        }
    },
    init() {
        console.log('force-field initialized.');

        this.hasBeenOpened = false;

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
        if (event.key.toLowerCase() === 'e' && this.isIntersected) {
            this.enterPasscode();
        }
    },

    enterPasscode() {
        const playerEl = document.querySelector('[character]');
        const playerComp = playerEl.components.character;

        const doorCode = this.data.passcode;

        if (playerComp.hasPasscode(doorCode)) {
            console.log('✅ Access granted!', doorCode);
            this.openDoor();
        } else {
            console.log('❌ Access denied. Missing passcode:', doorCode);
        }
    },

    openDoor() {
        if (this.hasBeenOpened) return;
        this.hasBeenOpened = true;

        const currentPosition = this.el.object3D.position.clone(); // clone to avoid mutation
        const targetY = currentPosition.y - 5;

        // Animate down from current position and fade out
        this.el.setAttribute('animation__slide', {
            property: 'position',
            to: `${currentPosition.x} ${targetY} ${currentPosition.z}`,
            dur: 1200,
            easing: 'easeInOutQuad'
        });
        this.el.setAttribute('animation__fade', {
            property: 'material.opacity',
            to: 0,
            dur: 1200,
            easing: 'easeInOutQuad'
        });

        // Remove the door after animation completes
        setTimeout(() => {
            if (this.el.parentNode) {
                this.el.parentNode.removeChild(this.el);
            }
            console.log('🚪 Door opened and removed!');
        }, 850);
    }
})
