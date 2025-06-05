#version 450 core
layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec2 inTexCoords;

out vec4 vColor;
out vec2 vTexCoords;

// uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * vec4(inPosition, 1.0);
    vColor = inColor;
    vTexCoords = inTexCoords;
}
