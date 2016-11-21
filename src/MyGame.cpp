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
	GameApplication::initScene();

	string modelPath = ASSET_PATH + MODEL_PATH + "/Earth.fbx";

	string vsParallaxFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingVS.glsl";
	string fsParallaxFilename = ASSET_PATH + SHADER_PATH + "/parallaxMappingFS.glsl";
	string vsBumpFilename=ASSET_PATH+SHADER_PATH+"/normalMappingVS.glsl";
	string fsBumpFilename=ASSET_PATH+SHADER_PATH+"/normalMappingFS.glsl";
	string vsTextureFilename=ASSET_PATH+SHADER_PATH+"/lightTextureVS.glsl";
	string fsTextureFilename=ASSET_PATH+SHADER_PATH+"/lightTextureFS.glsl";

	string diffuseTexturePath = ASSET_PATH + TEXTURE_PATH + "/bricks_diff.jpg";
	string specularTexturePath = ASSET_PATH + TEXTURE_PATH + "/bricks_spec.png";
	string normalTexturePath = ASSET_PATH + TEXTURE_PATH + "/bricks_norm.png";
	string heightTexturePath=ASSET_PATH+TEXTURE_PATH+"/bricks_height.png";

	shared_ptr<GameObject> testGO=shared_ptr<GameObject>(loadModelFromFile(modelPath));
	testGO->loadShaders(vsParallaxFilename, fsParallaxFilename);
	testGO->loadDiffuseTexture(diffuseTexturePath);
	testGO->loadSpecularTexture(specularTexturePath);
	testGO->loadNormalTexture(normalTexturePath);
	testGO->loadHeightTexture(heightTexturePath);
	testGO->setPosition(vec3(6.0f,0.0f,0.0f));
	addGameObject(testGO);
	addKeyboardListner(shared_ptr<IKeyboardListener>(new DemoKeyListener(testGO.get())));

	testGO=shared_ptr<GameObject>(loadModelFromFile(modelPath));
	testGO->loadShaders(vsBumpFilename, fsBumpFilename);
	testGO->loadDiffuseTexture(diffuseTexturePath);
	testGO->loadSpecularTexture(specularTexturePath);
	testGO->loadNormalTexture(normalTexturePath);
	testGO->setPosition(vec3(0.0f,0.0f,0.0f));
	addGameObject(testGO);
	addKeyboardListner(shared_ptr<IKeyboardListener>(new DemoKeyListener(testGO.get())));

	testGO=shared_ptr<GameObject>(loadModelFromFile(modelPath));
	testGO->loadShaders(vsTextureFilename, fsTextureFilename);
	testGO->loadDiffuseTexture(diffuseTexturePath);
	testGO->loadSpecularTexture(specularTexturePath);
	testGO->setPosition(vec3(-6.0f,0.0f,0.0f));
	addGameObject(testGO);
	addKeyboardListner(shared_ptr<IKeyboardListener>(new DemoKeyListener(testGO.get())));
}
