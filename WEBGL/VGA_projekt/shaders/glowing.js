AFRAME.registerShader('glowing', {
    schema: {
        time: {type: 'time', is: 'uniform'},
        color1: {type: 'color', is: 'uniform'},  // Base glow color
        color2: {type: 'color', is: 'uniform'},  // Secondary laser color
        uMap: {type: 'map', is: 'uniform'},      // Optional texture map
    },

    vertexShader: `
    precision highp float;

    varying vec2 vUv;
    varying vec3 vNormal;
    varying vec3 vWorldPosition;

    void main() {
      vUv = uv;
      vNormal = normalize(normalMatrix * normal);
      vec4 worldPosition = modelMatrix * vec4(position, 1.0);
      vWorldPosition = worldPosition.xyz;
      gl_Position = projectionMatrix * modelViewMatrix * vec4(position, 1.0);
    }
  `,

    fragmentShader: `
    precision highp float;

    uniform float time;
    uniform vec3 color1;
    uniform vec3 color2;
    uniform sampler2D uMap;

    varying vec2 vUv;
    varying vec3 vNormal;
    varying vec3 vWorldPosition;

    void main() {
      float pulse = 0.5 + 0.5 * sin(time * 0.005);
      
      // Moving scanlines
      float scan = sin((vUv.y + time * 0.002) * 100.0) * 0.1;

      // Fresnel effect based on view angle
      float fresnel = pow(1.0 - dot(vNormal, vec3(0.0, 0.0, 1.0)), 2.0);

      // Optional texture influence
      vec3 texColor = texture2D(uMap, vUv).rgb;

      // Combine color layers
      vec3 baseGlow = color1 * pulse;
      vec3 laserLines = color2 * scan;
      vec3 fresnelGlow = mix(baseGlow, color2, fresnel);

      vec3 finalColor = fresnelGlow + laserLines + texColor * 0.2;

      float alpha = 0.5 + 0.2 * fresnel + 0.1 * pulse;
      gl_FragColor = vec4(finalColor, alpha);
    }
  `
});
