#version 460 core 
out vec4 FragColor;

in vec3 outColor;
in vec2 outTexCoord;

uniform sampler2D ourTexture;

void main() {
    FragColor = texture(ourTexture, outTexCoord);
    // FragColor = vec4(outColor, 1.0f);
}
