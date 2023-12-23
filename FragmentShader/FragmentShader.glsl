#version 330


//specifies the color of each ambient, diffuses, specular to simulat different materials
//shinines is for how big is the radius of specular hightlights
//-----------
struct Material {
	sampler2D texture_diffuse0;
	sampler2D texture_specular0;
	sampler2D texture_emmision0;
	float shininess;
};


//stores values needed for the directional light calcualtions
struct DirLight {
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

//stores values needed for the point light caclucation
struct PointLight {
	float constant;
	float linear;
	float quadratic;
	
	vec3 position;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	float cutOff;
	float outerCutOff;
	
	float constant;
	float linear;
	float quadratic;

	bool isOn;	
	
	vec3 position;
	vec3 direciton;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


//number of pointlight we want to have in the scene
#define NR_POINT_LIGHTS 1

//INPUT VARIABLES
//--------------
in vec3 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 fragmentColor;

//UNIFORMS
//--------------
uniform vec3 viewPos;

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights;
uniform SpotLight spotLight;

//FUNCTIONS
//---------------
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos,vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPostition, vec3 viewDir);

void main() {
	
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	//Directional lighting
	vec3 result = CalcPointLight(pointLights, norm, FragPos, viewDir);
	result += CalcDirLight(dirLight, norm , viewDir);
	fragmentColor = vec4(result, 1.0f);
}

//calculating direction light
//------------
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),material.shininess);
	
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0,TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0,TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0,TexCoord));
	vec3 emision = vec3(texture(material.texture_emmision0, TexCoord));
	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos,vec3 viewDir)
{
	// here we are calclating light direction vector to do it we have
	//to subtract light position from framgnet position
	//currently it is pointing from the fragment to the light possition
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading

	float diff = max(dot(normal, lightDir), 0.0);
	
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0),
	material.shininess);
	
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	// combine results
	vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0,TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0,TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(material.texture_specular0,TexCoord));
	
	diffuse *= attenuation;
	specular *= attenuation;
	vec3 emision = vec3(texture(material.texture_emmision0, TexCoord));
	return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPostition, vec3 viewDir) {
	
	vec3 lightDir = normalize(light.position - FragPos);

	//theta value is outer coune of the flashlight
	float theta = dot(lightDir, normalize(-light.direciton));

	//inner cone of the flashlight
	float epsilon = light.cutOff - light.outerCutOff;
	
	//calculating intesity of each fragment 
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	if(light.isOn){		
		//ambient
		//------------
		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0, TexCoord));

		//diffuse
		//calculating diffuse strength on each fragment
		//------------
		float diff = max(dot(normal, lightDir), 0);

		//calculating diffuse strength for each fragment
		vec3 diffuse = light.diffuse * diff * vec3(texture(material.texture_diffuse0, TexCoord));

		//specular
		//----------
		float specularStrength = 0.5f;
	
		//calculating reflect direciton whiwch is reflectec light direciton vector around normal vector
		vec3 reflctDir = reflect(-lightDir, normal);

		//calculating specular strengt
		float spec = pow(max(dot(viewDir, reflctDir), 0.0f), material.shininess);
	
		//calculating color of specular lighting (map)
		vec3 specular = light.specular * spec * vec3((texture(material.texture_specular0, TexCoord)));

		float distance = length(light.position - FragPos);
		float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

		//ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		diffuse *= intensity;
		specular *= intensity;
		//resoult
		//------------
		vec3 emision = vec3(texture(material.texture_emmision0, TexCoord));
		return (ambient + diffuse + specular + emision);
	}

	else {
		vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse0,TexCoord));
		return ambient;
	}
}


