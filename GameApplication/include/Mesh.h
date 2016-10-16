#ifndef _MESH_H
#define _MESH_H

#include "Common.h"
#include "Vertex.h"

struct Mesh
{

	Mesh()
	{
		startVertexIndex=0;
		numberOfVertices=0;

		startIndex=0;
		numberOfIndices=0;
	};

	~Mesh()
	{
		Verts.clear();
		Indices.clear();
	};

  int startVertexIndex;
  int numberOfVertices;

  int startIndex;
  int numberOfIndices;

  vector<Vertex> Verts;
  vector<int> Indices;
};

class IMeshManager
{
public:
	virtual ~IMeshManager() {};
	virtual void bind() = 0;
	virtual bool create(int bufferSize)=0;
	virtual void destroy()=0;

	virtual Mesh* createMesh(const string &name, Vertex *pVerts, int numberOfVertices, int *pIndices, int numberOfIndices)=0;
	virtual Mesh* getMesh(const string &name)=0;

	virtual bool meshExists(const string &name)=0;
};

class MeshManager:public IMeshManager
{
public:
  MeshManager();
  ~MeshManager();

  void bind()
  {
    glBindVertexArray(m_VAO);
  };

  bool create(int bufferSize);
  void destroy();

  Mesh * createMesh(const string &name,Vertex *pVerts,int numberOfVertices,int *pIndices,int numberOfIndices);
  Mesh * getMesh(const string &name);

  bool meshExists(const string &name);
private:
  bool copyVertexData(Vertex *pVertex,int numberOfVertices,int *pIndices,int numberOfIndices);
private:
  vector<shared_ptr<Mesh> > m_MeshList;
  map<string,Mesh*> m_MeshTable;
  
  int m_CurrentVertexBufferOffetBytes;
  int m_CurrentVertexBufferIndex;
  int m_VertexBufferSize;

  int m_CurrentElementBufferOffetBytes;
  int m_CurrentElementBufferIndex;
  int m_ElementBufferSize;

  GLuint m_VBO;
  GLuint m_EBO;
  GLuint m_VAO;
};

#endif
