#version 320 es

precision mediump float;

in vec2 texCoord0;
out vec4 fragColor;

uniform vec3 ambientIntensity;
uniform sampler2D sampler;

void main() {
  fragColor = texture2D(sampler, texCoord0.xy) * vec4(ambientIntensity, 1);
}
