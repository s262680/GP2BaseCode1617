#include "Components/MeshComponent.h"

MeshComponent::MeshComponent(IMeshManager * meshManager)
{
	m_MeshManager = meshManager;
}

MeshComponent::~MeshComponent()
{
}

void MeshComponent::onRender()
{
	glDrawElements(GL_TRIANGLES, m_Mesh->numberOfIndices, GL_UNSIGNED_INT, (void**)(m_Mesh->startIndex * sizeof(int)));
}

void MeshComponent::onInit()
{
	m_Mesh = m_MeshManager->getMesh(m_MeshID);
}

void MeshComponent::setMeshID(const string & ID)
{
	m_MeshID = ID;
}
