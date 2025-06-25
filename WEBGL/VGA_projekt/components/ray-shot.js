AFRAME.registerComponent('ray-shot', {
    init() {
        this.collisionCount = 0;
        this.uniqueHits = new Set();

        this.el.addEventListener('raycaster-intersection1', event => {
            event.detail.els.forEach(hitEl => {
                const id = hitEl.id || hitEl; // fallback pokud element nemá id
                if (!this.uniqueHits.has(id)) {
                    this.uniqueHits.add(id);
                    this.collisionCount++;
                    console.log(`Ray hit #${this.collisionCount}:`, id);
                }
            });
        });
    }
});