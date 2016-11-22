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
uniform sampler2D heightMap;


uniform float bias=0.03f;
uniform float scale=0.015f;



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
	float height=texture(heightMap,vertexTextureCoordsOut).r;

	//vec2 correctedTexCoords= scale*vertexTextureCoordsOut.xy*height;
	//correctedTexCoords=correctedTexCoords-bias;

	vec2 correctedTexCoords= scale*vertexTextureCoordsOut.xy*height;
	correctedTexCoords=vertexTextureCoordsOut-correctedTexCoords-bias;
	


	vec3 bumpNormals = texture(normalSampler,correctedTexCoords).xyz;
	bumpNormals=normalize(bumpNormals*2.0f-1.0f);


	vec3 lightDir=normalize(-directionLight.direction);

	
	float diffuseTerm = dot(bumpNormals, lightDir);

	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);

	
	float specularTerm = pow(dot(bumpNormals, halfWayVec), directionLight.specularPower);

	vec4 diffuseTextureColor = texture(diffuseSampler,correctedTexCoords);
	vec4 specularTextureColor = texture(specularSampler,correctedTexCoords);

	
	//FragColor=vec4(bumpNormals,1.0f);
	FragColor = (ambientMaterialColour*directionLight.ambientColour) + (diffuseTextureColor*directionLight.diffuseColour*diffuseTerm) + (specularTextureColor*directionLight.specularColour*specularTerm);
	
	
}
