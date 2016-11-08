#include "MyGame.h"

const std::string ASSET_PATH = "assets";
const std::string SHADER_PATH = "/shaders";
const std::string TEXTURE_PATH = "/textures";
const std::string MODEL_PATH = "/models";

MyGame::MyGame()
{
	m_TestObject = nullptr;
	m_TestModelObject = nullptr;
}

MyGame::~MyGame()
{

}

void MyGame::initScene()
{
	m_CameraPos = vec3(0.0f, 0.0f, 100.0f);

	/*
	Vertex verts[] = {
		{vec3(-0.5f, -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,3.0f)},
		{vec3(0.5f, -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,3.0f)},
		{vec3(-0.5f,  0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,0.0f)},
		//{vec3(-0.5f, 0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(0.0f,0.0f)},
		{vec3(0.5f, 0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,0.0f)},
		//{vec3(0.5f,  -0.5f, 0.0f),vec4(1.0f,1.0f,1.0f,1.0f),vec2(3.0f,3.0f)}
	};
	*/
	
	
	int Indices[] = { 0,1,2,2,3,1 };

	m_TestObject = new GameObject();

	string vsPath = ASSET_PATH + SHADER_PATH + "/lightVS.glsl";
	string fsPath = ASSET_PATH + SHADER_PATH + "/lightFS.glsl";
	string simpleFSPath=ASSET_PATH + SHADER_PATH + "/simpleFS.glsl";

	m_TestObject->loadShaders(vsPath, fsPath);

	//lets load texture
	string texturePath = ASSET_PATH + TEXTURE_PATH + "/texture.png";
	m_TestObject->loadTexture(texturePath);

	//m_TestObject->copyVertexData(verts, 6);	
	//m_TestObject->copyVertexData(verts,4,Indices,6);


	string mdPath = ASSET_PATH + MODEL_PATH + "/utah-teapot.fbx";
	m_TestModelObject=loadModelFromFile(mdPath);
	m_TestModelObject->loadShaders(vsPath, fsPath);
}

void MyGame::destroyScene()
{
	if (m_TestModelObject)
	{
		m_TestModelObject->onDestroy();
		delete m_TestModelObject;
		m_TestModelObject = nullptr;
	}
	if (m_TestObject)
	{
		m_TestObject->onDestroy();
		delete m_TestObject;
		m_TestObject = nullptr;
	}
	
}

void MyGame::update()
{
	GameApplication::update();

	m_ProjMatrix = perspective(radians(45.0f), (float)m_WindowWidth / (float)m_WindowHeight, 0.1f, 100.0f);
	m_ViewMatrix = lookAt(m_CameraPos, vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	m_ModelMatrix = translate(mat4(1.0f), vec3(0.0f, 0.0f, -0.2f));

	m_TestObject->onUpdate();
	m_TestModelObject->onUpdate();

	m_TestModelObject->setCameraPosition(m_CameraPos);

	m_TestObject->setPositionNScale(vec3(-10.0f, 10.0f, 0.0f), vec3(10.0f, 10.0f, 10.0f));
	m_TestModelObject->setPositionNScale(vec3(0.0f, -5.0f, 0.0f),vec3(0.5f, 0.5f, 0.5f));
}

void MyGame::render()
{
	GameApplication::render();
	m_TestObject->onRender(m_ViewMatrix, m_ProjMatrix);
	m_TestModelObject->onRender(m_ViewMatrix, m_ProjMatrix);
}
