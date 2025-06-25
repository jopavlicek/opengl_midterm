AFRAME.registerComponent('drone', {
    schema: {},

    init() {
        console.log('Hello, you DRONE!');

        this.velocityX = 0;

        this.setupKeyListeners();
    },

    setupKeyListeners() {
        // Key press
        document.addEventListener('keydown', event => {
            const key = event.key.toLowerCase();
            if (key === "r") {
                this.velocityX = -5;
            } else if (key === "t") {
                this.velocityX = 5;
            }
        });

        // Key depress
        document.addEventListener('keyup', event => {
            const key = event.key.toLowerCase();
            if (key === "r") {
                this.velocityX = 0;
            } else if (key === "t") {
                this.velocityX = 0;
            }
        });
    },

    tick() {
        if (!this.el.body) return;
        this.el.body.velocity.set(this.velocityX, 0.1, -2);
    }
})
