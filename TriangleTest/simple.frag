#version 330

in highp vec3 vNormal;
in highp vec4 vColor;
out highp vec4 fColor;

vec3 diffuse = vec3(0.8f, 0.8f, 0.8f);
vec3 ambient = vec3(0.2f, 0.2f, 0.2f);
vec3 specular = vec3(1.0f, 0.5f, 0.3f);
float shininess = 2;

vec3 lightDir = normalize(vec3(-1.0f, 2.0f, 1.0f));
vec3 camPos = vec3(0.0f, 0.0f, 1.0f);

void main()
{
	vec3 n = normalize(vNormal);
	vec3 e = normalize(camPos);
	float intensity = max(dot(n, lightDir), 0.0f);
	vec3 h = normalize(lightDir + e);
	float spec = max(dot(h, n), 0.0);
	specular = specular * pow(spec, shininess);
    fColor = vColor * vec4(max(intensity * diffuse + spec, ambient), 1.0f);
}
