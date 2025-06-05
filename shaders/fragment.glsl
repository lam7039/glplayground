#version 450 core 
out vec4 FragColor;
// layout (location = 0) out vec4 outColor;

in vec4 vColor;
in vec2 vTexCoords;

uniform sampler2D uTexture;

void main() {
    // outColor = texture(uTexture[index], vTexCoord) * vec4(vColor, 1.0f);
    // outColor = texture(uTexture[index], vTexCoord);
    // FragColor = texture(uTexture[index], vTexCoord) * vec4(vColor, 1.0f);
    // FragColor = vColor;
    FragColor = texture(uTexture, vTexCoords);
    // FragColor = vec4(vTexCoords, 0.0, 1.0);  // Shows UVs directly
    // FragColor = texture(uTexture, vTexCoord) * vec4(vColor, 1.0f);
    // FragColor = texture(uTexture, vTexCoord);
    // FragColor = vec4(vColor, 1.0f);
    // FragColor = vec4(textureId, textureId, textureId, 1.0f);
}
