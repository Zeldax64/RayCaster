#include "core/objects/meshes/MObj.h"
MObj::MObj() {
}

MObj::~MObj() {
  delete[] this->vertices;
  delete[] this->faces;
}

void MObj::applyTransform(const TMatrix & param) {
	for(uint32_t i = 0; i < vertices_num; i++){
		vertices[i].applyTransform(param);
	}
}

float MObj::hitObject(Ray & ray, Vertex3f & ret_n, Material * & ret_mat) {
	float t =hitTriangles(ray, this, vertices, faces, faces_num, ret_n, ret_mat);
	return t;
}

Material* MObj::getMaterial() { return &this->material; }

void MObj::print(){
  	for(uint32_t i = 0; i < vertices_num; i++){
  		vertices[i].print();
  	}

    for(uint32_t i = 0; i < faces_num; i++){
      faces[i].print();
    }

}

bool MObj::loadObj(const char * path) {
  std::vector <Vertex3f> out_vertices;
  std::vector <Face3f> out_faces;
  std::cout << "Load file init!\n";
  bool load = loadOBJ(path, &out_vertices, &out_faces);

  if(this->vertices != NULL)
  std::cout << "Load file done!\n";
    delete[] this->vertices;
  if(this->faces != NULL)
    delete[] this->faces;

  if (load){

    this->vertices = new Vertex3f[out_vertices.size()];
    this->faces = new Face3f[out_faces.size()];
    for(uint32_t i = 0; i < out_vertices.size(); i++){
      vertices[i] = out_vertices[i];
    }
    std::cout << "Load vertices done!\n";

    vertices_num = out_vertices.size();
    for(uint32_t i = 0; i < out_faces.size(); i++){
      faces[i] = out_faces[i];
    }
    std::cout << "Load faces done!\n";
    faces_num = out_faces.size();

    std::cout << "Passed!\n";
    return load;
  }

  return load;
}
