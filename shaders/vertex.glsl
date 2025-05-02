#version 450 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoord;

out vec4 vColor;
out vec2 vTexCoord;

uniform mat4 uMvpMatrix;

void main() {
    // gl_Position = vec4(inPosition, 1.0);
    gl_Position = uMvpMatrix * vec4(inPosition, 1.0);
    vColor = inColor;
    vTexCoord = inTexCoord;
}
