#ifndef _MESH_H
#define _MESH_H

#include "Common.h"
#include "Vertex.h"

struct Mesh
{
  int startVertexIndex;
  int numberOfVertices;

  int startIndex;
  int numberOfIndices;

  vector<Vertex> Verts;
  vector<int> Indices;
};


class MeshManager
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

  shared_ptr<Mesh> createMesh(const string &name,Vertex *pVerts,int numberOfVertices,int *pIndices,int numberOfIndices);
  shared_ptr<Mesh> getMesh(const string &name);

  bool meshExists(const string &name);
private:
  bool copyVertexData(Vertex *pVertex,int numberOfVertices,int *pIndices,int numberOfIndices);
private:
  vector<shared_ptr<Mesh> > m_MeshList;
  map<string,shared_ptr<Mesh> > m_MeshTable;
  
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
