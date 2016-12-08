#ifndef Model_h
#define Model_h

class Model
{
public:
	int Model::Load(char* filename);
	void Model::Draw() const;
	float* Model::calculateNormal(float* coord1, float* coord2, float* coord3) const;
	Model();

	float* Faces_Triangles;
	float* Faces_Quads;
	float* Vertex_Buffer;
	float* Normals;

	int TotalConnectedTriangles;
	int TotalConnectedQuads;
	int TotalConnectedPoints;
	int TotalFaces;
};

#endif
