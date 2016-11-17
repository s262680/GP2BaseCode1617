#version 410

out vec4 FragColor;


in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;

//uniform vec3 lightDirection=vec3(0.0f,0.0f,1.0f);

uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform vec4 diffuseMaterialColour=vec4(0.8f,0.0f,0.0f,1.0f);
uniform vec4 specularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);
//uniform float specularPower=25.0f;

//uniform vec4 ambientLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
//uniform vec4 diffuseLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
//uniform vec4 specularLightColour=vec4(1.0f,1.0f,1.0f,1.0f);

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


//directionLight.specularPower=25.0f;
//directionLight.direction=vec3(0.0f,0.0f,1.0f);
//directionLight.ambientColour=vec4(1.0f,1.0f,1.0f,1.0f);
//directionLight.diffuseColour=vec4(1.0f,1.0f,1.0f,1.0f);
//directionLight.specularColour=vec4(1.0f,1.0f,1.0f,1.0f);


void main()
{
	vec3 lightDir=normalize(-directionLight.direction);
	float diffuseTerm = dot(vertexNormalOut, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(vertexNormalOut, halfWayVec), directionLight.specularPower);

	vec4 diffuseTextureColor = texture(diffuseSampler,vertexTextureCoordsOut);
	vec4 specularTextureColor = texture(specularSampler,vertexTextureCoordsOut);

	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColor*directionLight.diffuseColour*diffuseTerm) + (specularTextureColor*directionLight.specularColour*specularTerm);
	

}
