#version 410

out vec4 FragColor;
out vec4 TextureReturn;

in vec3 vertexNormalOut;
in vec3 cameraDirectionOut;
in vec2 vertexTextureCoordsOut;

uniform vec3 lightDirection=vec3(0.0f,0.0f,1.0f);

uniform vec4 ambientMaterialColour=vec4(0.5f,0.0f,0.0f,1.0f);
uniform vec4 diffuseMaterialColour=vec4(0.8f,0.0f,0.0f,1.0f);
uniform vec4 specularMaterialColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform float specularPower=25.0f;

uniform vec4 ambientLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform vec4 diffuseLightColour=vec4(1.0f,1.0f,1.0f,1.0f);
uniform vec4 specularLightColour=vec4(1.0f,1.0f,1.0f,1.0f);

uniform sampler2D diffuseSampler;

void main()
{
	vec3 lightDir=normalize(-lightDirection);
	float diffuseTerm = dot(vertexNormalOut, lightDir);
	vec3 halfWayVec = normalize(cameraDirectionOut + lightDir);
	float specularTerm = pow(dot(vertexNormalOut, halfWayVec), specularPower);

	TextureReturn = texture(diffuseSampler,vertexTextureCoordsOut);
	FragColor = (ambientMaterialColour*ambientLightColour) + (TextureReturn*diffuseLightColour*diffuseTerm) + (specularMaterialColour*specularLightColour*specularTerm);
	

}
