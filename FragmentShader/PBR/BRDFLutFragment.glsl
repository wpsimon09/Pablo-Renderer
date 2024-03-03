#version 330 core
out vec4 FragColor;

const float PI = 3.14159265359;

in vec2 TexCoords;

//generates the lowe descrepancy sequence
float radicalInverse_VdC(uint bits) {
	bits = (bits << 16u) | (bits >> 16u);
	bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
	bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
	bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
	bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
	
	return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

//returns the sample i from all of the samples;
vec2 Hammersley(uint i, uint N)
{
	return vec2(float(i)/float(N), radicalInverse_VdC(i));
}

// Importance sample the GGX distribution to generate a microfacet halfway (H) in tangent space,
// and transform it to world space to obtain the final sampled direction vector within the specular lobe.
vec3 importanceSampleGGX(vec2 Xi, vec3 N, float rougness)
{
	float a = rougness * rougness;
	float phi = 2.0 * PI * Xi.x;
	float cosTheta = sqrt((1.0 - Xi.y) / (1.0 + (a*a - 1.0) * Xi.y));
	float sinTheta = sqrt(1.0 - cosTheta*cosTheta);
	
	//from spherecal coordinates to cartasian
	vec3 H;
	H.x = cos(phi) * sinTheta;
	H.y = sin(phi) * sinTheta;
	H.z = cosTheta;

	// from tangent-space vector to world-space sample vector
	vec3 up = abs(N.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
	vec3 tangent = normalize(cross(up, N));
	vec3 bitangent = cross(N, tangent);

	//final sample vector that is withing the specular lobe 
	vec3 sampleVector = tangent * H.x + bitangent * H.y + N * H.z;
	return normalize(sampleVector);
}


//goemetry function for eaither view or light direction
float GeometrySchlickGGX(float NdotV, float roughness)
{
	float a = roughness;
	float k = (a * a) / 2.0;
	float nom = NdotV;
	float denom = NdotV * (1.0 - k) + k;
	return nom / denom;
}

//function combining GeoemtrySchlickGGX for view direction and light direction
float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
	float NdotV = max(dot(N, V), 0.0);
	float NdotL = max(dot(N, L), 0.0);

	//for view direction
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);

	//for light direction
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	return ggx1 * ggx2;
}

vec2 IntagrateBRDF(float NdotV, float roughness)
{
	vec3 V;
	V.x = sqrt(1.0 - NdotV * NdotV);
	V.y = 0.0;
	V.z = NdotV;

	float A = 0.0;
	float B = 0.0;

	vec3 N = vec3(0.0, 0.0, 1.0);

	const uint SAMPLE_COUNT = 1024u;

	for(uint i = 0u; i<SAMPLE_COUNT ; ++i)
	{
		//select sample semi-random sample
		vec2 Xi = Hammersley(i, SAMPLE_COUNT);

		//place it within the specular lobe
		vec3 H = importanceSampleGGX(Xi, N, roughness);

		//calculate the light direction
		vec3 L = normalize(2.0* dot(V, H) * H-V);

		float NdotL = max(L.z, 0.0);
		float NdotH = max(H.z, 0.0);
		float VdotH = max(dot(V,H), 0.0);

		if(NdotL > 0.0)
		{
			float G = GeometrySmith(N, V, L, roughness);
			float G_vis = (G* VdotH)/(NdotH * NdotV);
			float Fc = pow(1.0 - VdotH, 5.0);

			A += (1.0 - Fc) * G_vis;
			B += Fc * G_vis;
		}
	}
	A /= float(SAMPLE_COUNT);
	B /= float(SAMPLE_COUNT);

	return vec2(A,B);
}

void main()
{
	vec2 integratedBRDF = IntagrateBRDF(TexCoords.x, TexCoords.y);
	FragColor = vec4(integratedBRDF, 0.0, 1.0);
}