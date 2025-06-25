AFRAME.registerComponent('wall-collision', {
    schema: {
        enabled: { type: 'boolean', default: true },
        checkDistance: { type: 'number', default: 0.5 }
    },

    init() {
        this.character = this.el;
        this.raycasters = [];

        // Wait for scene to load before setting up raycasters
        this.el.sceneEl.addEventListener('loaded', () => {
            this.setupRaycasters();
        });
    },

    setupRaycasters() {
        // Only 4 cardinal directions - keep it simple
        const directions = [
            { name: 'forward', direction: new THREE.Vector3(0, 0, -1) },
            { name: 'backward', direction: new THREE.Vector3(0, 0, 1) },
            { name: 'left', direction: new THREE.Vector3(-1, 0, 0) },
            { name: 'right', direction: new THREE.Vector3(1, 0, 0) }
        ];

        directions.forEach(dir => {
            const raycaster = new THREE.Raycaster();
            raycaster.far = this.data.checkDistance;
            this.raycasters.push({
                name: dir.name,
                raycaster: raycaster,
                direction: dir.direction.clone()
            });
        });
    },

    tick() {
        if (!this.data.enabled || !this.raycasters.length) return;

        // Get current movement from character component
        const characterComponent = this.character.components.character;
        if (!characterComponent || !characterComponent.velocity) return;

        const currentVelocity = characterComponent.velocity;
        const currentPosition = this.character.object3D.position;

        // Only check if character is actually trying to move
        if (currentVelocity.length() > 0.001) {
            const blockedDirections = this.getBlockedDirections(currentPosition, currentVelocity);
            this.applyDirectionalBlocking(characterComponent, blockedDirections, currentVelocity);
        }
    },

    getBlockedDirections(position, velocity) {
        const blocked = {
            forward: false,
            backward: false,
            left: false,
            right: false
        };

        // Get collision mesh
        const collisionMesh = document.querySelector('[gltf-model="#navMesh"]');
        if (!collisionMesh || !collisionMesh.object3D) return blocked;

        const collisionObjects = [];
        collisionMesh.object3D.traverse((child) => {
            if (child.isMesh) {
                collisionObjects.push(child);
            }
        });

        if (collisionObjects.length === 0) return blocked;

        // Check each direction, but only if we're moving in that direction
        this.raycasters.forEach(rayData => {
            const { raycaster, direction, name } = rayData;

            // Calculate if we're moving towards this direction
            const movementTowardsWall = direction.dot(velocity);

            // Only check for walls if we're moving towards them
            if (movementTowardsWall > 0.1) {
                const rayOrigin = position.clone();
                rayOrigin.y += 0.5;

                raycaster.set(rayOrigin, direction);
                const intersections = raycaster.intersectObjects(collisionObjects, true);

                if (intersections.length > 0) {
                    const closestIntersection = intersections[0];
                    if (closestIntersection.distance < this.data.checkDistance) {
                        blocked[name] = true;
                        console.log(`${name} direction blocked - moving towards wall at distance:`, closestIntersection.distance);
                    }
                }
            }
        });

        return blocked;
    },

    applyDirectionalBlocking(characterComponent, blockedDirections, currentVelocity) {
        let newVelocity = currentVelocity.clone();

        // Only block movement in directions where walls are detected AND we're moving towards them
        if (blockedDirections.forward && currentVelocity.z < -0.01) {
            newVelocity.z = +1.5;
            console.log('Blocked forward movement');
        }
        if (blockedDirections.backward && currentVelocity.z > 0.01) {
            newVelocity.z = -1.5;
            console.log('Blocked backward movement');
        }
        if (blockedDirections.left && currentVelocity.x < -0.01) {
            newVelocity.x = +1.5;
            console.log('Blocked left movement');
        }
        if (blockedDirections.right && currentVelocity.x > 0.01) {
            newVelocity.x = -1.5;
            console.log('Blocked right movement');
        }

        characterComponent.velocity = newVelocity;
    }
});
