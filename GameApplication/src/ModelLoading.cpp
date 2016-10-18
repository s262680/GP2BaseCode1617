#include "ModelLoading.h"

//http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
shared_ptr<GameObject> loadModelFromFile(const string & filename)
{
	shared_ptr<GameObject> gameObject = nullptr;
	const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);

	const aiScene* scene = aiImportFile(filename.c_str(), aiProcessPreset_TargetRealtime_MaxQuality);

	if (scene)
	{
		const aiMesh * mesh=scene->mMeshes[0];

		vector<int> indices;
		vector<Vertex> verts;

		for (int f = 0; f < mesh->mNumFaces; f++)
		{
			const aiFace * face = &mesh->mFaces[f];
			for (int i = 0; i < face->mNumIndices; i++)
			{
				int index = face->mIndices[i];
				indices.push_back(index);
			}
		}

		for (int v = 0; v < mesh->mNumVertices; v++)
		{
			aiVector3D position = mesh->mVertices[v];
			aiVector3D normal = mesh->mNormals[v];
			//aiVector3D texCoords = mesh->mTextureCoords[v];
			Vertex ourV;
			ourV.position = vec3(position.x, position.y, position.z);
			ourV.normal = vec3(normal.x, normal.y, normal.z);
			verts.push_back(ourV);
		}

		gameObject = shared_ptr<GameObject>(new GameObject());
		gameObject->copyVertexData(&verts[0], verts.size(), &indices[0], indices.size());
	}

	aiReleaseImport(scene);


	return gameObject;
}
