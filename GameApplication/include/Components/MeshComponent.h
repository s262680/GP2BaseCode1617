#ifndef MESH_COMPONENT_H
#define MESH_COMPONENT_H

#include "Component.h"
#include "Mesh.h"

class MeshComponent :public BaseComponet
{
public:
	MeshComponent(IMeshManager * meshManager);
	~MeshComponent();

	void onRender();
	void onInit();
	void setMeshID(const string& ID);
private:
	string m_MeshID;
	Mesh *m_Mesh;
	IMeshManager * m_MeshManager;

};


#endif
