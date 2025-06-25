/*
 * mine.js
 *
 * This component now only handles mine-specific effects (e.g., explosion animation, sound) when triggered.
 * Health deduction and removal are handled by the obstacle component.
 */
AFRAME.registerComponent('mine', {
    init: function () {
        // Listen for the same event as obstacle
        this.el.addEventListener('collide-with-character', this.handleMineEffect.bind(this));
    },

    handleMineEffect: function (event) {
        // Play explosion animation or sound here
        // Example: add a class, trigger a particle system, etc.
        // This is a placeholder for your custom effect logic
        console.log('Mine triggered! Play explosion effect here.');
    },
});
