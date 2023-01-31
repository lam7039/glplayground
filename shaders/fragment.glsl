#version 450 core 
out vec4 FragColor;
// layout (location = 0) out vec4 o_Color;

in vec4 color;
in vec2 texCoord;
in float textureId;

uniform sampler2D ourTextures[2];
// uniform sampler2D ourTexture;

void main() {
    int index = int(textureId);
    // o_Color = texture(ourTextures[index], texCoord) * vec4(color, 1.0f);
    // o_Color = texture(ourTextures[index], texCoord);
    // FragColor = texture(ourTextures[index], texCoord) * vec4(color, 1.0f);
    FragColor = texture(ourTextures[index], texCoord);
    // FragColor = texture(ourTexture, texCoord) * vec4(color, 1.0f);
    // FragColor = texture(ourTexture, texCoord);
    // FragColor = vec4(color, 1.0f);
    // FragColor = vec4(textureId, textureId, textureId, 1.0f);
}
