#include "Mesh.h"

MeshManager::MeshManager()
{
	m_VBO = 0;
	m_VAO = 0;
	m_CurrentVertexBufferOffetBytes = 0;
	m_VertexBufferSize = 0;
	m_CurrentVertexBufferIndex = 0;
	m_CurrentElementBufferOffetBytes = 0;
	m_CurrentElementBufferIndex = 0;
	m_ElementBufferSize = 0;
}

MeshManager::~MeshManager()
{

}

bool MeshManager::meshExists(const string &name)
{
	if (m_MeshTable.count(name) > 0)
	{
		return true;
	}

	return false;
}

bool MeshManager::copyVertexData(Vertex *pVertex, int numberOfVertices, int *pIndices, int numberOfIndices)
{
	int sizeInBytesVBO = numberOfVertices * sizeof(Vertex);
	int sizeInBytesEBO = numberOfIndices * sizeof(int);

	if (((sizeInBytesVBO + m_CurrentVertexBufferOffetBytes) > m_VertexBufferSize) || ((sizeInBytesVBO + m_CurrentElementBufferOffetBytes) > m_ElementBufferSize))
	{
		LOG(WARNING, "%s", "Buffer is full, consider increasing size");
		return false;
	}

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferSubData(GL_ARRAY_BUFFER, m_CurrentVertexBufferOffetBytes, sizeInBytesVBO, pVertex);
	m_CurrentVertexBufferOffetBytes += sizeInBytesVBO;
	m_CurrentVertexBufferIndex += numberOfVertices;

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, m_CurrentElementBufferOffetBytes, sizeInBytesEBO, pIndices);
	m_CurrentElementBufferOffetBytes += sizeInBytesEBO;
	m_CurrentElementBufferIndex += numberOfIndices;


	return true;
}

Mesh * MeshManager::createMesh(const string &name, Vertex *pVerts, int numberOfVertices, int *pIndices, int numberOfIndices)
{
	shared_ptr<Mesh> mesh = nullptr;
	//find Mesh
	if (meshExists(name))
	{
		return m_MeshTable[name];
	}
	mesh = shared_ptr<Mesh>(new Mesh());
	mesh->startVertexIndex = m_CurrentVertexBufferIndex;
	mesh->numberOfVertices = numberOfVertices;
	mesh->startIndex = m_CurrentElementBufferIndex;
	mesh->numberOfIndices = numberOfIndices;

	mesh->Verts.insert(mesh->Verts.end(), &pVerts[0], &pVerts[numberOfVertices]);
	mesh->Indices.insert(mesh->Indices.end(), &pIndices[0], &pIndices[numberOfIndices]);

	if (copyVertexData(pVerts, numberOfVertices, pIndices, numberOfIndices))
	{
		m_MeshList.push_back(mesh);
		m_MeshTable[name] = mesh.get();
		return mesh.get();
	}

	return nullptr;
}

Mesh * MeshManager::getMesh(const string &name)
{
	return m_MeshTable[name];
}

bool MeshManager::create(int bufferSize)
{
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, bufferSize * sizeof(Vertex), NULL, GL_STATIC_DRAW);

	glGenBuffers(1, &m_EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * bufferSize * sizeof(int), NULL, GL_STATIC_DRAW);

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		NULL);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, colours)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
		(void**)(offsetof(Vertex, TexCoords0)));

	m_VertexBufferSize = bufferSize * sizeof(Vertex);
	m_ElementBufferSize = 3 * bufferSize * sizeof(int);
	return true;
}

void MeshManager::destroy()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(1, &m_EBO);
	glDeleteBuffers(1, &m_VBO);

	m_MeshTable.clear();
	m_MeshList.clear();
}
