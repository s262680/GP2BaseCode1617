#version 410

out vec4 FragColor;

in vec4 vertexColoursOut;
in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;
in vec3 lightDirectionOut;


uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform vec4 diffuseMaterialColour=vec4(0.8f,0.0f,0.0f,1.0f);
uniform vec4 specularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);


uniform sampler2D diffuseSampler;
uniform sampler2D specularSampler;
uniform sampler2D normalSampler;



struct DirectionalLight
{
float specularPower;
vec3 direction;
vec4 ambientColour;
vec4 diffuseColour;
vec4 specularColour;
};

uniform DirectionalLight directionLight;



void main()
{
	vec3 bumpNormals = texture(normalSampler,vertexTextureCoordsOut).xyz;
	bumpNormals=normalize(bumpNormals*2.0f-1.0f);


	vec3 lightDir=normalize(-directionLight.direction);

	//float diffuseTerm = dot(vertexNormalOut, lightDir);
	float diffuseTerm = dot(bumpNormals, lightDir);

	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);

	//float specularTerm = pow(dot(vertexNormalOut, halfWayVec), directionLight.specularPower);
	float specularTerm = pow(dot(bumpNormals, halfWayVec), directionLight.specularPower);

	vec4 diffuseTextureColor = texture(diffuseSampler,vertexTextureCoordsOut);
	vec4 specularTextureColor = texture(specularSampler,vertexTextureCoordsOut);

	
	//FragColor=vec4(bumpNormals,1.0f);
	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColor*directionLight.diffuseColour*diffuseTerm) + (specularTextureColor*directionLight.specularColour*specularTerm);
	
	
}
