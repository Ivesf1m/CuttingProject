#version 330

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec3 normal;
uniform mat4 mvp;
uniform vec3 translateFactor;
out vec4 vColor;
out vec3 vNormal;

void main()
{
        //vec4 aux = vec4(position.x - 0.5f, position.y - 0.5f, position.z, 1.0f);
		vec4 aux = vec4(position + translateFactor, 1.0f);
		gl_Position = aux * mvp;
        vColor = vec4(color, 1.0f);
		vNormal = normal;
}
