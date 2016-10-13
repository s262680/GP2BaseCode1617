#include "Mesh.h"

MeshManager::MeshManager()
{
  m_VBO=0;
  m_VAO=0;
  m_CurrentBufferOffetBytes=0;
  m_BufferSize=0;
  m_CurrentBufferIndex=0;
}

MeshManager::~MeshManager()
{

}

bool MeshManager::meshExists(const string &name)
{
  if (m_MeshTable.count(name)>0)
  {
    return true;
  }

  return false;
}

bool MeshManager::copyVertexData(Vertex *pVertex,int numberOfVertices)
{
  int sizeInBytes=numberOfVertices*sizeof(Vertex);
  if ((sizeInBytes+m_CurrentBufferOffetBytes)>m_BufferSize)
  {
    LOG(WARNING,"%s","Buffer is full, consider increasing size");
    return false;
  }

  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferSubData(GL_ARRAY_BUFFER,m_CurrentBufferOffetBytes,sizeInBytes,pVertex);
  m_CurrentBufferOffetBytes+=sizeInBytes;
  m_CurrentBufferIndex+=numberOfVertices;
  return true;
}

shared_ptr<Mesh> MeshManager::createMesh(const string &name,Vertex *pVerts,int numberOfVertices)
{
  shared_ptr<Mesh> mesh=nullptr;
  //find Mesh
  if (meshExists(name))
  {
    return m_MeshTable[name];
  }
  mesh=shared_ptr<Mesh>(new Mesh());
  mesh->startVertexIndex=m_CurrentBufferIndex;
  mesh->numberOfVertices=numberOfVertices;
  mesh->Verts.insert(mesh->Verts.end(), &pVerts[0], &pVerts[numberOfVertices]);

  if (copyVertexData(pVerts,numberOfVertices))
  {
    return mesh;
  }

  return nullptr;
}

shared_ptr<Mesh> MeshManager::getMesh(const string &name)
{
  return m_MeshTable[name];
}

bool MeshManager::create(int bufferSize)
{
  glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(Vertex), NULL, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex,colours)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex,TexCoords0)));

  m_BufferSize=bufferSize * sizeof(Vertex);
  return true;
}

void MeshManager::destroy()
{
  glDeleteBuffers(1, &m_VBO);
  glDeleteVertexArrays(1, &m_VAO);
  m_MeshTable.clear();
  m_MeshList.clear();
}
