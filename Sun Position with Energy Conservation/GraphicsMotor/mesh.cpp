#include "mesh.h"
#include "loaderOBJ.hpp"
#include <iostream>
#include <fstream>


Mesh::Mesh(){

	vertexList=new std::vector<vertex_t>();
	faceList=new std::vector<int>();
//añadir vértices

	vertex_t v1,v2,v3;
	
	v1.posicion=glm::vec4(-0.5f,-0.5,0.0f,1.0f);
	v2.posicion=glm::vec4( 0.0f, 0.5,0.0f,1.0f);
	v3.posicion=glm::vec4( 0.5f,-0.5,0.0f,1.0f);
	
	vertexList->push_back(v1);
	vertexList->push_back(v2);
	vertexList->push_back(v3);
	
	faceList->push_back(0);
	faceList->push_back(1);
	faceList->push_back(2);
}


Mesh::Mesh(std::string fileName, std::string textureFileName){

	vertexList=new std::vector<vertex_t>();
	faceList=new std::vector<int>();
//añadir vértices
	loadFromFile(fileName, textureFileName);
}




void Mesh::setColor(int idxVertex, glm::vec4 color){
	(*vertexList)[idxVertex].color=color;
}

void Mesh::loadFromFile(std::string fileName, std::string textureFileName) {
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	loadOBJ(fileName.c_str(), temp_vertices, temp_uvs, temp_normals);
	for (int i = 0; i < temp_vertices.size(); i++) {
		vertex_t v1;
		v1.posicion.x = temp_vertices[i].x;
		v1.posicion.y = temp_vertices[i].y;
		v1.posicion.z = temp_vertices[i].z;
		v1.posicion.w = 1;
		v1.color.r = 1;
		v1.color.g = 1;
		v1.color.b = 1;
		v1.color.a = 1;
		v1.normal.x = temp_normals[i].x;
		v1.normal.y = temp_normals[i].y;
		v1.normal.z = temp_normals[i].z;
		v1.normal.w = 0;
		v1.texCoord.x = temp_normals[i].x;
		v1.texCoord.y = temp_normals[i].y;
		vertexList->push_back(v1);
		int b1;
		b1 = i;
		faceList->push_back(b1);

	}
	printf("%f", vertexList->at(0).posicion.x);
	std::string vshader = "GraphicsMotor/vshader.txt";
	std::string fshader = "GraphicsMotor/fshader.txt";
	std::string textureFile = textureFileName;

	shader = new GLShader(vshader, fshader);
	tex = new Texture(textureFile);
	printf("Completado!");

}



Mesh::~Mesh(){
	
	delete vertexList;
	delete faceList;
}
