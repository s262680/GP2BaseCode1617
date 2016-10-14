#include "MyGame.h"



const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	Vertex verts[]={
		{vec3(-0.5f, -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,3.0f)},
		{vec3(0.5f, -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,3.0f)},
		{vec3(-0.5f,  0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,0.0f)},
		{vec3(0.5f, 0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,0.0f)},
	};

	int indices[] = {
		0,1,2,
		2,3,1
	};

	GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);

	GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);

	m_ShaderProgram = glCreateProgram();
	glAttachShader(m_ShaderProgram, vertexShaderProgram);
	glAttachShader(m_ShaderProgram, fragmentShaderProgram);
	glLinkProgram(m_ShaderProgram);
	checkForLinkErrors(m_ShaderProgram);

	//now we can delete the VS & FS Programs
	glDeleteShader(vertexShaderProgram);
	glDeleteShader(fragmentShaderProgram);

	logShaderInfo(m_ShaderProgram);

	//lets load texture
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	m_Texture = loadTextureFromFile(texturePath);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenSamplers(1,&m_ClampSampler);
	glSamplerParameteri(m_ClampSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(m_ClampSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(m_ClampSampler, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glSamplerParameteri(m_ClampSampler, GL_TEXTURE_WRAP_T, GL_CLAMP);

	m_CurrentMesh=m_StaticMeshManager->createMesh("Sprite1",verts,4,indices,6);
}

void MyGame::destroyScene()
{
	glDeleteSamplers(1,&m_ClampSampler);
	glDeleteTextures(1, &m_Texture);
	glDeleteProgram(m_ShaderProgram);
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_ModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -0.2f));
}

void MyGame::render()
{
	GameApplication::render();

	glUseProgram(m_ShaderProgram);
	m_StaticMeshManager->bind();

	//glBindVertexArray(m_VAO);

	GLint MVPLocation = glGetUniformLocation(m_ShaderProgram, "MVP");
	if (MVPLocation != -1)
	{
		mat4 MVP = m_ProjMatrix*m_ViewMatrix*m_ModelMatrix;
		glUniformMatrix4fv(MVPLocation, 1, GL_FALSE, glm::value_ptr(MVP));
	}
	glBindSampler(0, m_ClampSampler);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	GLint textureLocation = glGetUniformLocation(m_ShaderProgram, "diffuseSampler");
	if (textureLocation != -1)
	{
		glUniform1i(textureLocation, 0);
	}

	//glDrawArrays(GL_TRIANGLES, m_CurrentMesh->startVertexIndex, m_CurrentMesh->numberOfVertices);
	//glDrawRangeElements(GL_TRIANGLES, m_CurrentMesh->startIndex, m_CurrentMesh->numberOfIndices+1, m_CurrentMesh->numberOfIndices, GL_UNSIGNED_INT, 0);
	glDrawElements(GL_TRIANGLES, m_CurrentMesh->numberOfIndices, GL_UNSIGNED_INT, NULL);
}
