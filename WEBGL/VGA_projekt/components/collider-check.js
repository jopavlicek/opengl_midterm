// Create a shared Set for all instances
const sharedUniqueHits = new Set();
let sharedCollisionCount = 0;

AFRAME.registerComponent('collider-check', {
    init() {
        // Use the shared Set and counter
        this.uniqueHits = sharedUniqueHits;
        this.collisionCount = sharedCollisionCount;

        // Add keydown listener for E key
        document.addEventListener('keydown', (event) => {
            if (event.key.toLowerCase() === 'e') {
                this.checkCollisions();
            }
        });
    },

    checkCollisions() {
        // Get all raycaster entities
        const character = this.el.closest('[character]');
        if (!character) return;

        const raycasterEntities = character.querySelectorAll('[raycaster]');
        
        raycasterEntities.forEach(raycaster => {
            // Check for intersections
            raycaster.components.raycaster.refreshObjects();
            const intersections = raycaster.components.raycaster.intersections;

            intersections.forEach(intersection => {
                const hitEl = intersection.object.el;
                const id = hitEl.id || hitEl;

                // Skip if it's the ground or character
                if ((hitEl.tagName.toLowerCase() === 'a-box' && hitEl.getAttribute('static-body')) || 
                    hitEl.hasAttribute('character') ||
                    hitEl.closest('[character]')) {
                    return;
                }

                if (!this.uniqueHits.has(id)) {
                    this.uniqueHits.add(id);
                    this.collisionCount++;
                    sharedCollisionCount = this.collisionCount;

                    // Update points in UI
                    if (window.gameUI) {
                        window.gameUI.incrementPoints();
                    }

                    console.log(`Hit #${this.collisionCount}:`, id);
                    console.log('Points:', this.collisionCount);

                    if (hitEl.hasAttribute('obstacle')) {
                        hitEl.parentNode.removeChild(hitEl);
                        console.log(`Removed obstacle: ${id}`);
                    }
                }
            });
        });
    }
});
