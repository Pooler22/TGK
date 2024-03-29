#include "Model.h"

#include <GL/freeglut.h>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <string>


Model::Model(): Faces_Triangles(nullptr), Faces_Quads(nullptr), Vertex_Buffer(nullptr), Normals(nullptr), TotalConnectedTriangles(0), TotalConnectedQuads(0), TotalConnectedPoints(0), TotalFaces(0)
{
}

float* Model::calculateNormal(float* coord1, float* coord2, float* coord3) const
{
	float va[3], vb[3], vr[3], val;
	va[0] = coord1[0] - coord2[0];
	va[1] = coord1[1] - coord2[1];
	va[2] = coord1[2] - coord2[2];

	vb[0] = coord1[0] - coord3[0];
	vb[1] = coord1[1] - coord3[1];
	vb[2] = coord1[2] - coord3[2];

	vr[0] = va[1] * vb[2] - vb[1] * va[2];
	vr[1] = vb[0] * va[2] - va[0] * vb[2];
	vr[2] = va[0] * vb[1] - vb[0] * va[1];

	val = sqrt(vr[0] * vr[0] + vr[1] * vr[1] + vr[2] * vr[2]);

	float norm[3];
	norm[0] = vr[0] / val;
	norm[1] = vr[1] / val;
	norm[2] = vr[2] / val;

	return norm;
}


int Model::Load(char* filename)
{
	this->TotalConnectedTriangles = 0;
	this->TotalConnectedQuads = 0;
	this->TotalConnectedPoints = 0;

	auto pch = strstr(filename, ".ply");

	if (pch != nullptr)
	{
		FILE* file = nullptr;
		fopen_s(&file, filename, "r");

		fseek(file, 0, SEEK_END);
		auto fileSize = ftell(file);

		try
		{
			Vertex_Buffer = static_cast<float*>(malloc(ftell(file)));
		}
		catch (char*)
		{
			return -1;
		}
		if (Vertex_Buffer == nullptr) return -1;
		fseek(file, 0, SEEK_SET);

		Faces_Triangles = static_cast<float*>(malloc(fileSize * sizeof(float)));
		Normals = static_cast<float*>(malloc(fileSize * sizeof(float)));

		if (file)
		{
			int i;
			auto triangle_index = 0;
			auto normal_index = 0;
			char buffer[1000];

			fgets(buffer, 300, file); // ply

			while (strncmp("element vertex", buffer, strlen("element vertex")) != 0)
			{
				fgets(buffer, 300, file); // format
			}
			strcpy_s(buffer, buffer + strlen("element vertex"));
			sscanf_s(buffer, "%i", &this->TotalConnectedPoints);

			fseek(file, 0, SEEK_SET);
			while (strncmp("element face", buffer, strlen("element face")) != 0)
			{
				fgets(buffer, 300, file); // format
			}
			strcpy_s(buffer, buffer + strlen("element face"));
			sscanf_s(buffer, "%i", &this->TotalFaces);

			while (strncmp("end_header", buffer, strlen("end_header")) != 0)
			{
				fgets(buffer, 300, file); // format
			}

			i = 0;
			for (auto iterator = 0; iterator < this->TotalConnectedPoints; iterator++)
			{
				fgets(buffer, 300, file);

				sscanf_s(buffer, "%f %f %f", &Vertex_Buffer[i], &Vertex_Buffer[i + 1], &Vertex_Buffer[i + 2]);
				i += 3;
			}

			// read faces
			i = 0;
			for (auto iterator = 0; iterator < this->TotalFaces; iterator++)
			{
				fgets(buffer, 300, file);

				if (buffer[0] == '3')
				{
					auto vertex1 = 0, vertex2 = 0, vertex3 = 0;
					buffer[0] = ' ';
					sscanf_s(buffer, "%i%i%i", &vertex1, &vertex2, &vertex3);

					Faces_Triangles[triangle_index] = Vertex_Buffer[3 * vertex1];
					Faces_Triangles[triangle_index + 1] = Vertex_Buffer[3 * vertex1 + 1];
					Faces_Triangles[triangle_index + 2] = Vertex_Buffer[3 * vertex1 + 2];
					Faces_Triangles[triangle_index + 3] = Vertex_Buffer[3 * vertex2];
					Faces_Triangles[triangle_index + 4] = Vertex_Buffer[3 * vertex2 + 1];
					Faces_Triangles[triangle_index + 5] = Vertex_Buffer[3 * vertex2 + 2];
					Faces_Triangles[triangle_index + 6] = Vertex_Buffer[3 * vertex3];
					Faces_Triangles[triangle_index + 7] = Vertex_Buffer[3 * vertex3 + 1];
					Faces_Triangles[triangle_index + 8] = Vertex_Buffer[3 * vertex3 + 2];

					float coord1[3] = {Faces_Triangles[triangle_index], Faces_Triangles[triangle_index + 1],Faces_Triangles[triangle_index + 2]};
					float coord2[3] = {Faces_Triangles[triangle_index + 3],Faces_Triangles[triangle_index + 4],Faces_Triangles[triangle_index + 5]};
					float coord3[3] = {Faces_Triangles[triangle_index + 6],Faces_Triangles[triangle_index + 7],Faces_Triangles[triangle_index + 8]};
					float* norm = this->calculateNormal(coord1, coord2, coord3);

					Normals[normal_index] = norm[0];
					Normals[normal_index + 1] = norm[1];
					Normals[normal_index + 2] = norm[2];
					Normals[normal_index + 3] = norm[0];
					Normals[normal_index + 4] = norm[1];
					Normals[normal_index + 5] = norm[2];
					Normals[normal_index + 6] = norm[0];
					Normals[normal_index + 7] = norm[1];
					Normals[normal_index + 8] = norm[2];

					normal_index += 9;

					triangle_index += 9;
					TotalConnectedTriangles += 3;
				}
				i += 3;
			}
			fclose(file);
		}

		else { printf("File can't be opened\n"); }
	}
	else
	{
		printf("File does not have a .PLY extension. ");
	}
	return 0;
}

void Model::Draw() const
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	//glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POLYGON_SMOOTH);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, Faces_Triangles);
	glNormalPointer(GL_FLOAT, 0, Normals);
	glDrawArrays(GL_TRIANGLES, 0, TotalConnectedTriangles);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);

	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
}
