#ifndef _MESH_H
#define _MESH_H

#include "Common.h"
#include "Vertex.h"

struct Mesh
{
  float startVertexIndex;
  float numberOfVertices;

  vector<Vertex> Verts;
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

  shared_ptr<Mesh> createMesh(const string &name,Vertex *pVerts,int numberOfVertices);
  shared_ptr<Mesh> getMesh(const string &name);

  bool meshExists(const string &name);
private:
  bool copyVertexData(Vertex *pVertex,int numberOfVertices);
private:
  vector<shared_ptr<Mesh> > m_MeshList;
  map<string,shared_ptr<Mesh> > m_MeshTable;
  int m_CurrentBufferOffetBytes;
  int m_CurrentBufferIndex;
  int m_BufferSize;
  GLuint m_VBO;
  GLuint m_VAO;


};

#endif
