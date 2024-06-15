#version 330 core

out vec4 FragColor;

in vec3 localPos;

uniform samplerCube envMap;
uniform float roughness;

const float PI = 3.14159265359;

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a = roughness*roughness;
    float a2 = a*a;
    float NdotH = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;

    float nom   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;

    return nom / denom;
}

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

void main()
{
	const uint SAMPLE_COUNT = 1096u;
	//get normal, reflection and view direction vectors
	vec3 N = normalize(localPos); //w_o output direction
	vec3 R = N;
	vec3 V = R;

	float totalWeight = 0.0;
	vec3 prefilterColor = vec3(0.0);
	for(uint i = 0u; i < SAMPLE_COUNT; ++i)
	{
		//retrieve the random direction vector from low-discreapncy sequence
		vec2 Xi = Hammersley(i, SAMPLE_COUNT);
		
		//retrive the sample vector within the specular lobe
		vec3 H = importanceSampleGGX(Xi, N, roughness);

		//get the reflected vector of the light 
		vec3 L = normalize(2.0 * dot(V,H) * H - V);

		//calculate the impact of the light 
		float NdotL = max(dot(N,L), 0.0);
	
		if(NdotL>0.0)
		{
			float D = DistributionGGX(N, H, roughness);
			float NdotH = max(dot(N,H),0.0);
			float HdotV = max(dot(H,V), 0.0);
			float pdf = D * NdotH/ (4.0 * HdotV) + 0.0001;

			float resolution = 512.0;
			float saTexel  = 4.0 * PI / (6.0 * resolution * resolution);
			float saSample = 1.0/(float(SAMPLE_COUNT) * pdf + 0.0001);

			float mipLevel = roughness == 0.0 ? 0.0 : 0.5 * log2(saSample/saTexel);

			//weight the color based on how strong the light is 
			prefilterColor += textureLod(envMap, L, mipLevel).rgb * NdotL;
			
			//less impact = less weight
			totalWeight += NdotL;
		}
	}
	prefilterColor = prefilterColor / totalWeight;

	FragColor = vec4(prefilterColor, 1.0);
}