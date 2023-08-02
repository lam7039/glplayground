#version 450 core 
out vec4 FragColor;
// layout (location = 0) out vec4 o_Color;

in vec4 color;
in vec2 texCoord;

uniform sampler2D ourTexture;
// uniform sampler2D ourTexture;

void main() {
    // o_Color = texture(ourTextures[index], texCoord) * vec4(color, 1.0f);
    // o_Color = texture(ourTextures[index], texCoord);
    // FragColor = texture(ourTextures[index], texCoord) * vec4(color, 1.0f);
    FragColor = texture(ourTexture, texCoord);
    // FragColor = texture(ourTexture, texCoord) * vec4(color, 1.0f);
    // FragColor = texture(ourTexture, texCoord);
    // FragColor = vec4(color, 1.0f);
    // FragColor = vec4(textureId, textureId, textureId, 1.0f);
}
