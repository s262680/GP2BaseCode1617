#version 410

out vec4 FragColor;
in vec2 vertexTexCoordsOut;

uniform sampler2D diffuseSampler;

void main()
{
	FragColor = texture(diffuseSampler, vertexTexCoordsOut)*vec4(0.0f,1.0f,0.0f,1.0f);
	
	}
