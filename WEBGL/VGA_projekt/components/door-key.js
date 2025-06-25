AFRAME.registerComponent('door-key', {
    schema: {
        passcode: { type: 'int' }
    },

    init() {
        this.isIntersected = false;
        this.hasBeenRead = false;

        this.el.addEventListener('raycaster-intersected', () => {
            this.isIntersected = true;
        });

        this.el.addEventListener('raycaster-intersected-cleared', () => {
            this.isIntersected = false;
        });

        document.addEventListener('keydown', this.onKeyDown.bind(this));
    },

    onKeyDown(event) {
        if (this.hasBeenRead) return;

        if (event.key.toLowerCase() === 'e' && this.isIntersected) {
            this.pickUp();
        }
    },

    pickUp() {
        const playerEl = document.querySelector('[character]');
        const player = playerEl.components.character;

        const code = this.data.passcode;

        if (!player.passcodes.includes(code)) {
            player.passcodes.push(code);
            console.log(`🔑 Passcode ${code} acquired!`);
        }

        // Remove child light, if any
        const light = this.el.querySelector('[light]');
        if (light) {
            light.parentNode.removeChild(light);
            console.log('💡 Key has been read');
        }

        this.hasBeenRead = true;
    }
});
