#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
uniform mat4 mvp;
out vec4 vColor;

void main()
{
        vec4 aux = vec4(position.x, position.y, position.z, 1.0f);
		gl_Position = aux * mvp;
        vColor = vec4(color, 1.0f);
}
