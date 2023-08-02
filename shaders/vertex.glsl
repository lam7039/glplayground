#version 450 core
layout (location=0) in vec3 inPosition;
layout (location=1) in vec4 inColor;
layout (location=2) in vec2 inTexCoord;

out vec4 color;
out vec2 texCoord;

uniform mat4 mvp_matrix;

void main() {
    // gl_Position = vec4(inPosition, 1.0);
    gl_Position = mvp_matrix * vec4(inPosition, 1.0);
    color = inColor;
    texCoord = inTexCoord;
}
