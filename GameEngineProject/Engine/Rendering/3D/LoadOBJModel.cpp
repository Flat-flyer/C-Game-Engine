#include "LoadOBJModel.h"

LoadOBJModel::LoadOBJModel()
{
	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	indices.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshvertices.reserve(200);
	subMeshes.reserve(10);
}

LoadOBJModel::~LoadOBJModel()
{
	vertices.clear();
	normals.clear();
	textureCoords.clear();
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshvertices.clear();
	subMeshes.clear();
}

void LoadOBJModel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJModel::GetSubMeshes()
{
	return subMeshes;
}

BoundingBox LoadOBJModel::GetBoundingBox() const
{
	return boundingBox;
}

void LoadOBJModel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshvertices.push_back(vert);
	}
	SubMesh mesh;
	mesh.vertexList = meshvertices;
	mesh.meshIndices = indices;
	mesh.material = currentMaterial;

	subMeshes.push_back(mesh);

	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshvertices.clear();

	currentMaterial = Material();
}

void LoadOBJModel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);
	if (!in) {
		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJModel.cpp", __LINE__);
		return;
	}

	std::string line;

	while (std::getline(in, line)) {
		//VERTEX DATA
		if (line.substr(0, 2) == "v ") {
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));
			if (boundingBox.maxVert.x < x) {
				boundingBox.maxVert.x = x;
			}
			if (boundingBox.maxVert.y < y) {
				boundingBox.maxVert.y = y;
			}
			if (boundingBox.maxVert.z < z) {
				boundingBox.maxVert.z = z;
			}
			if (boundingBox.minVert.x > x) {
				boundingBox.minVert.x = x;
			}
			if (boundingBox.minVert.y > y) {
				boundingBox.minVert.y = y;
			}
			if (boundingBox.minVert.z > z) {
				boundingBox.minVert.z = z;
			}
		}

		//NORMAL DATA
		if (line.substr(0, 3) == "vn ") {
			std::stringstream vn(line.substr(3));
			float x, y, z;
			vn >> x >> y >> z;
			normals.push_back(glm::vec3(x, y, z));
		}

		//TEXTURE DATA
		if (line.substr(0, 3) == "vt ") {
			std::stringstream vt(line.substr(3));
			float x, y;
			vt >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}

		//NEW MESH
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}

		//FACES
		if (line.substr(0, 2) == "f ") {
			std::stringstream f(line.substr(2));
			GLint temp_glint;
			int counter = 0;
			while (f >> temp_glint) {
				if (counter == 0)
				{
					indices.push_back(temp_glint - 1);
				}
				else if (counter == 1) {
					textureIndices.push_back(temp_glint -1);
				}
				else if (counter == 2) {
					normalIndices.push_back(temp_glint -1);
				}

				if (f.peek() == '/') {
					++counter;
					f.ignore(1, '/');
				}
				else if (f.peek() == ' ') {
					++counter;
					f.ignore(1, ' ');
				}

				if (counter > 2) {
					counter = 0;
				}
			}
			
			
		}
	}
	PostProcessing();
}

void LoadOBJModel::LoadMaterial(const std::string& matName_)
{
	currentMaterial = MaterialHandler::GetInstance()->GetMaterial(matName_);
}

void LoadOBJModel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	MaterialLoader::LoadMaterial(matFilePath_);
}
