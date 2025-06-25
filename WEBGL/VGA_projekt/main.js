import './style.css'
import 'aframe'
import 'aframe-extras'
import 'aframe-physics-system'
import { createApp } from 'vue'
import GameUI from './components/GameUI.vue'
import './components/character'
import './components/obstacle'
import './components/collider-check'
import './components/wall-collision'
import './components/health-pickup'
import './components/mine'
import './components/doors'
import './components/door-key'
import './shaders/glowing'

// Create Vue app
const app = createApp(GameUI)
const vm = app.mount('#app')

// Create A-Frame scene
const scene = document.createElement('a-scene')
scene.innerHTML = `
    <!-- External files -->
    <a-assets>
    
        <img src="/models/concrete.jpeg" id="concrete">
        <img src="/models/tiles.jpg" id="tiles">
        <img src="/models/panels.jpg" id="panels">
        
        
        <a-asset-item id="lvl1-visual" src="/models/L1-visual-v1.glb"></a-asset-item>
        <a-asset-item id="lvl1-collision" src="/models/L1-collision-v1.glb"></a-asset-item>
        <a-asset-item id="navMesh" src="/models/L1-collision-v0.glb"></a-asset-item>
        <a-asset-item id="Health" src="/models/Pickup-Health.glb"></a-asset-item>
        <a-asset-item id="HealthRed" src="/models/Red-heal.glb"></a-asset-item>
        <a-asset-item id="HealthRed" src="/models/Red-heal.glb"></a-asset-item>
        <a-asset-item id="landmine" src="/models/Landmine.glb"></a-asset-item>
        <a-asset-item id="container-small" src="/models/Container-Small.glb"></a-asset-item>
        <a-asset-item id="container-big" src="/models/Container-Red.glb"></a-asset-item>
        <a-asset-item id="Terminal" src="/models/Computer-terminal-futuristic.glb"></a-asset-item>

        
        
        <a-asset-item id="hoodie" src="/models/Hoodie-Character.glb"></a-asset-item>
        <a-asset-item id="business" src="/models/Business-Man.glb"></a-asset-item>
        <a-asset-item id="SWAT" src="/models/SWAT.glb"></a-asset-item>
        <a-asset-item id="drone" src="/models/Robot-Enemy-Flying.glb"></a-asset-item>
        
        
    </a-assets>

    <!-- Environment -->

    <!--ground--> 

         <!-- visual map --> <a-entity
         gltf-model="#lvl1-visual"
         position="0 0.2 0"
         scale="0.7 0.7 0.7"
         ></a-entity>

    <!-- collision/navMesh --> <a-entity
    gltf-model="#navMesh"
    static-body="shape: mesh; mass: 1; restitution: 0.0; friction: 1.0; sphereRadius: 0.1;"
    position="0 0.0 0"
    scale="0.7 0.7 0.7"
    visible="false"
    ></a-entity>
    
    <!-- lights -->
    
    <a-light type="ambient" color="#FFF" intensity="0.3"></a-light>
    
    <!--    <a-light type="directional" color="#FFF" intensity="0.6" position="-1 2 1"></a-light>-->
    <a-light type="point" color="#FFF" intensity="1" distance="2" position="1 2 0"></a-light>

    <a-box 
     static-body="friction: 0;" 
     position="0 0 -4" 
     width="70"
     height="0.2"
     depth="70"
     material="src: #panels; repeat: 15 30;"
     ></a-box>

    <!--  sky    --> <a-sky color="#eeeeee"></a-sky>
    <!-- TODO -->

    <!-- Obstacles -->
    <a-sphere obstacle="strength: 9999" dynamic-body="mass: 1;" position="2 1 -3" radius="0.5" color="orange"></a-sphere>
    <a-sphere obstacle="strength: 999" dynamic-body="mass: 1;" position="2 1 -2" radius="0.5" color="red"></a-sphere>
    <a-sphere obstacle="strength: 999" dynamic-body="mass: 1;" position="2 1 -1" radius="0.5" color="purple"></a-sphere>
    <a-sphere obstacle="strength: 999" dynamic-body="mass: 1;" position="-2 1 -5" radius="0.5" color="blue"></a-sphere>

    <!-- Pickups -->
    
    <!--    Heal 50-->
    <a-entity position="0 0.5 0" scale="1 1 1" health-pickup="healAmount: 50">
      <a-entity gltf-model="#HealthRed"></a-entity>
      <a-light type="point" color="#ff0000" intensity="1" distance="2" position="0 0.5 0"> </a-light>
    </a-entity>
    
    <!--    Heal 25-->
    <a-entity position="-5 0.5 5" scale="1 1 1" health-pickup="healAmount: 25">
      <a-entity gltf-model="#Health"></a-entity>
      <a-light type="point" color="#00ff00" intensity="1" distance="2" position="0 0.5 0"> </a-light>
    </a-entity>
    
    <a-entity position="13.4 0.5 14.0" scale="1 1 1" health-pickup="healAmount: 25">
      <a-entity gltf-model="#Health"></a-entity>
      <a-light type="point" color="#00ff00" intensity="1" distance="2" position="0 0.5 0"> </a-light>
    </a-entity>
    

    <!-- Objects -->
    
    <!--    landmine-->
    <a-entity 
      obstacle="strength: 1; damage: 100"
      mine
      gltf-model="#landmine"
      static-body="shape: box; mass: 0"
      position="5 0 -2"
      scale="1 1 1">
      <a-light type="point" color="#ff0000" intensity="1" distance="1" position="0 0.4 0"></a-light>
    </a-entity>
    
<!--    container-small-->
    <a-entity 
      gltf-model="#container-small"
      position="-5 0 -2"
      scale="1 1 1"
      dynamic-body="shape: box; mass: 1.0; restitution: 0.0; friction: 1.0">
    </a-entity>

    
<!--    enemies-->
    <a-entity 
      obstacle="damage: 40; strength: 2"
      gltf-model="#drone"
      static-body="shape: box; mass: 1"
      drone-path="from: 0 1 0; to: 10 1 0; speed: 2"
      >
      <a-light type="point" color="#ff0000" intensity="20" distance="1" position="0 0 0.1"> </a-light>
    </a-entity>

     <a-entity 
      obstacle="damage: 40; strength: 2"
      gltf-model="#drone"
      dynamic-body="shape: box; halfExtents: 0.2 0.2 0.2; gravity: 0 0 0"
      position="3 1 -2"
      follow-character="speed: 1.5"
      >
      <a-light type="point" color="#ff0000" intensity="20" distance="1" position="0 0 0.1"> </a-light>
    </a-entity>

    <!-- Doors & Keys -->
    <!-- doors 1 -->
    <a-entity
        doors="passcode: 1111;"
        static-body
        geometry="primitive: box; height: 2; width: 3"
        material="shader: glowing; color1: #fcac2a; color2: #fc0505; src: #lasers; transparent: true; blending: additive;"
        position="2.890 1.06 10.767"
        scale="0.6 1.066 0.2"
        >
          <a-light type="point" color="#fc0505" intensity="1" distance="3" position="0 0 0.1"> </a-light>
    </a-entity>
    <a-box
        door-key="passcode: 1111;"
        gltf-model="#Terminal"
        position="4 0 6"
        transparency="0"
    >
        <a-light
          type="point"
          color="#00ffff"
          intensity="2"
          distance="2"
          position="0 1.5 0.2"
          animation="property: intensity; from: 2; to: 1; dur: 100; dir: alternate; loop: true"
      ></a-light>
    </a-box>
    
    <!-- doors 2 -->
    <a-entity
        doors="passcode: 2222;"
        static-body
        geometry="primitive: box; height: 2; width: 3"
        material="shader: glowing; color1: #fcac2a; color2: #fc0505; src: #lasers; transparent: true; blending: additive;"
        position="-14.212 1.06 -5.793"
        scale="0.6 1.2 0.2"
        >
          <a-light type="point" color="#fc0505" intensity="1" distance="3" position="0 0 0.1"> </a-light>
    </a-entity>
    <a-box
        door-key="passcode: 2222;"
        gltf-model="#Terminal"
        position="-14.212 0 -2.793"
        transparency="0"
    >
        <a-light
          type="point"
          color="#00ffff"
          intensity="2"
          distance="2"
          position="0 1.5 0.2"
          animation="property: intensity; from: 2; to: 0; dur: 100; dir: alternate; loop: true"
      ></a-light>
    </a-box>
    
    <!-- doors 3 -->
    <a-entity
        doors="passcode: 3333;"
        static-body
        geometry="primitive: box; height: 2; width: 3"
        material="shader: glowing; color1: #fcac2a; color2: #fc0505; src: #lasers; transparent: true; blending: additive;"
        position="8.113 1.06 -33.65"
        scale="0.6 1.2 0.3"
        >
          <a-light type="point" color="#fc0505" intensity="1" distance="3" position="0 0 0.1"> </a-light>
    </a-entity>
    <a-box
        door-key="passcode: 3333;"
        gltf-model="#Terminal"
        position="8.113 0 -28.65"
        transparency="0"
    >
        <a-light
          type="point"
          color="#00ffff"
          intensity="2"
          distance="2"
          position="0 1.5 0.2"
          animation="property: intensity; from: 2; to: 0; dur: 100; dir: alternate; loop: true"
      ></a-light>
    </a-box>
    
    
    <!--    Cameras-->


    <!-- Character -->
    <a-entity character wall-collision dynamic-body="mass: 1; angularDamping: 1; linearDamping: 0.95; shape: box;" position="-2 0.4 -3">
        <a-entity 
        gltf-model="#business" 
        animation-mixer="clip: *Idle_Neutral*;" 
        position="0 0 0"
        rotation="0 0 0"
        scale="1 1 1"
        ></a-entity>

        <!-- Right raycaster -->
        <a-entity raycaster="direction: 1 0 0; far: 1.5;"
        position="0 0.5 0" collider-check></a-entity>
        <!-- Forward raycaster -->
        <a-entity raycaster="direction: 0 0 1; far: 1.5;"
        position="0 0.5 0" collider-check></a-entity>
        <!-- Left raycaster -->
        <a-entity raycaster="direction: -1 0 0; far: 1.5;"
        position="0 0.5 0" collider-check></a-entity>
        <!-- Backward raycaster -->
        <a-entity raycaster="direction: 0 0 -1; far: 1.5;"
        position="0 0.5 0" collider-check></a-entity>

        <!-- Camera -->
        <a-entity camera position="0 6 4" rotation="-60 0 0"></a-entity>
    </a-entity>
`

// Add scene to the document
document.body.appendChild(scene)

// Make Vue instance available globally for A-Frame components
window.gameUI = vm

AFRAME.registerComponent('drone-path', {
  schema: {
    from: { type: 'vec3', default: {x: 0, y: 2, z: 0} },
    to: { type: 'vec3', default: {x: 10, y: 2, z: 0} },
    speed: { type: 'number', default: 2 }
  },
  init: function () {
    this.direction = 1;
    this.progress = 0;
  },
  tick: function (time, deltaTime) {
    const t = (this.progress += this.direction * this.data.speed * deltaTime / 1000 / 10);
    if (t > 1) {
      this.progress = 1;
      this.direction = -1;
    } else if (t < 0) {
      this.progress = 0;
      this.direction = 1;
    }
    // Linear interpolation between from and to
    const pos = {
      x: this.data.from.x + (this.data.to.x - this.data.from.x) * this.progress,
      y: this.data.from.y + (this.data.to.y - this.data.from.y) * this.progress,
      z: this.data.from.z + (this.data.to.z - this.data.from.z) * this.progress
    };
    this.el.setAttribute('position', pos);
  }
});

AFRAME.registerComponent('follow-character', {
  schema: {
    speed: { type: 'number', default: 1.0 }
  },
  tick: function () {
    // Find the character entity
    const character = document.querySelector('[character]');
    if (!character) return;

    // Get positions
    const dronePos = this.el.object3D.position;
    const charPos = character.object3D.position;

    // Calculate direction vector
    const direction = new THREE.Vector3(
      charPos.x - dronePos.x,
      0, // Keep drone at same height (optional, or use charPos.y - dronePos.y for 3D)
      charPos.z - dronePos.z
    );
    const distance = direction.length();

    if (distance > 0.1) { // Don't jitter when very close
      direction.normalize();
      // Move drone toward character
      dronePos.x += direction.x * this.data.speed * 0.016; // 0.016 ≈ 60fps
      dronePos.z += direction.z * this.data.speed * 0.016;
      this.el.setAttribute('position', {x: dronePos.x, y: dronePos.y, z: dronePos.z});
    }
  }
});
