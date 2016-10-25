#include "MyGame.h"

/*
struct Vertex {
	vec3 position;
	vec4 colour;
	vec2 texCoord;
};
*/


const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";

MyGame::MyGame()
{
	m_testObject = nullptr;
}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{

	Vertex verts[] = {
	{vec3(-0.5f, -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,3.0f)},
	{vec3(0.5f, -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,3.0f)},
	{vec3(-0.5f,  0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,0.0f)},
	{ vec3(-0.5f, 0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,0.0f)},
	{vec3(0.5f, 0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,0.0f)},
	{vec3(0.5f,  -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,3.0f)}
	};
	

	m_testObject = new GameObject();



	//GLuint vertexShaderProgram = 0;
	string vsPath = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	//vertexShaderProgram = loadShaderFromFile(vsPath, VERTEX_SHADER);

	//GLuint fragmentShaderProgram = 0;
	string fsPath = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	//fragmentShaderProgram = loadShaderFromFile(fsPath, FRAGMENT_SHADER);

	m_testObject->loadShaders(vsPath, fsPath);




	//lets load texture
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";

	m_testObject->loadTexture(texturePath);

	m_testObject->copyVertexData(verts, 6);
	/*
	m_Texture = loadTextureFromFile(texturePath);
	glBindTexture(GL_TEXTURE_2D, m_Texture);
	glGenerateMipmap(GL_TEXTURE_2D);

	glGenSamplers(1,&m_ClampSampler);
	glSamplerParameteri(m_ClampSampler, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(m_ClampSampler, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glSamplerParameteri(m_ClampSampler, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glSamplerParameteri(m_ClampSampler, GL_TEXTURE_WRAP_T, GL_CLAMP);
	*/
}

void MyGame::destroyScene()
{
	if (m_testObject)
	{
		m_testObject->onDestroy();
		delete m_testObject;
		m_testObject = nullptr;
	}
	/*
	glDeleteSamplers(1,&m_ClampSampler);
	glDeleteTextures(1, &m_Texture);
	glDeleteProgram(m_ShaderProgram);
	glDeleteBuffers(1, &m_VBO);
	glDeleteVertexArrays(1, &m_VAO);
	*/
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(vec3(0.0f, 0.0f, 10.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_ModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -0.2f));

	m_testObject->onUpdate();
}

void MyGame::render()
{
	GameApplication::render();
	m_testObject-> onRender(m_ViewMatrix, m_ProjMatrix);
    /*
	glUseProgram(m_ShaderProgram);
	glBindVertexArray(m_VAO);

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

	glDrawArrays(GL_TRIANGLES, 0, 6);
	*/
}
