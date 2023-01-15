#version 450 core
layout (location=0) in vec3 inPosition;
layout (location=1) in vec3 inColor;
layout (location=2) in vec2 inTexCoord;
layout (location=3) in float inTextureId;

out vec3 color;
out vec2 texCoord;
out float textureId;

void main() {
    gl_Position = vec4(inPosition, 1.0);
    color = inColor;
    texCoord = inTexCoord;
    textureId = inTextureId;
}
