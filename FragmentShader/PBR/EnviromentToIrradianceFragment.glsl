#version 330 core

out vec4 FragColor;

uniform samplerCube enviromentMap;
in vec3 localPos;

const float PI = 3.14159265359;

void main()
{
	vec3 normal = normalize(localPos);

	vec3 irradiance = vec3(0.0);

	//calculations for tangent space	
	vec3 up = vec3(0.0, 1.0, 0.0);
	vec3 right = cross(up,normal);
	up = cross(normal, right);

	//hemisphere specs
	float sampleDelta = 0.011;
	float nrSamples = 0;

	for(float phi = 0.0; phi< 2* PI; phi += sampleDelta)
	{
		for(float theta = 0.0; theta< 0.5 * PI; theta += sampleDelta)
		{
			vec3 tangentSample = vec3(sin(theta) * cos(phi), sin(theta) * sin(phi), cos(theta));

			vec3 sampleVec = tangentSample.x * right + tangentSample.y * up + tangentSample.z * normal;

			irradiance += texture(enviromentMap, sampleVec).rgb * cos(theta) * sin(theta);

			nrSamples ++;
		}
	}

	irradiance = PI * irradiance * (1.0/float(nrSamples));
	FragColor = vec4(irradiance, 1.0);
}