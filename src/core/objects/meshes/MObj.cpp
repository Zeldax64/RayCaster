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
  Material out_mat;
  Color* out_tex;

  std::cout << "Load file init!\n";
  bool load = loadOBJ(path, &out_vertices, &out_faces, out_mat, out_tex);
  std::cout << "Load file done!\n";

  if (load){
    if(this->vertices != NULL)
      delete[] this->vertices;
    if(this->faces != NULL)
      delete[] this->faces;
    if(this->texture != NULL)
      delete[] this->texture;

    this->vertices = new Vertex3f[out_vertices.size()];
    this->faces = new Face3f[out_faces.size()];
    for(uint32_t i = 0; i < out_vertices.size(); i++){
      vertices[i] = out_vertices[i];
    }

    vertices_num = out_vertices.size();
    for(uint32_t i = 0; i < out_faces.size(); i++){
      faces[i] = out_faces[i];
    }
    faces_num = out_faces.size();

    this->material = out_mat;
    this->texture = out_tex;

    std::cout << "Passed!\n";
  }

  return load;
}
