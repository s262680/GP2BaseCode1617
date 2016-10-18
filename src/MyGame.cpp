#include "MyGame.h"

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{

}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	/*
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


	m_TestGO = unique_ptr<GameObject>(new GameObject());

	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	m_TestGO->loadTextureFromFile(texturePath);

	string vsFilename = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	string fsFilename = ASSET_PATH + SHADER_PATH + "/textureFS.glsl";
	m_TestGO->loadShadersFromFile(vsFilename, fsFilename);

	m_TestGO->copyVertexData(verts, 4, indices, 6);*/

	string modelPath = ASSET_PATH + MODEL_PATH + "/utah-teapot.fbx";
	m_TestGO=loadModelFromFile(modelPath);
	string vsFilename = ASSET_PATH + SHADER_PATH + "/simpleVS.glsl";
	string fsFilename = ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";
	m_TestGO->loadShadersFromFile(vsFilename, fsFilename);
	m_TestGO->setScale(vec3(0.5f, 0.5f, 0.5f));
}

void MyGame::onKeyDown(SDL_Keycode keyCode)
{
	if (keyCode == SDLK_a)
	{
		m_TestGO->rotate(vec3(0.0f, -0.5f, 0.0f));
	}else if (keyCode == SDLK_d)
	{
		m_TestGO->rotate(vec3(0.0f, 0.5f, 0.0f));
	}
}

void MyGame::destroyScene()
{
	m_TestGO->onDestroy();
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 1000.0f);
	m_ViewMatrix = lookAt(vec3(0.0f, 0.0f, 100.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_TestGO->onUpdate();
}

void MyGame::render()
{
	GameApplication::render();
	m_TestGO->onRender(m_ViewMatrix, m_ProjMatrix);
}
