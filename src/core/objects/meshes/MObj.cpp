#include "core/objects/meshes/MObj.h"
MObj::MObj() {
  this->vertices = NULL;
  this->faces = NULL;
  this->texture = NULL;
}

MObj::~MObj() {
  delete[] this->vertices;
  delete[] this->faces;
  delete[] this->texture;
}

void MObj::applyTransform(const TMatrix & param) {
	for(uint32_t i = 0; i < vertices_num; i++){
		vertices[i].applyTransform(param);
	}
}

float MObj::hitObject(Ray & ray) {
	float t =hitTriangles(ray, this, vertices, faces, faces_num);
	return t;
}

Material MObj::getMaterial(Ray &ray) {
  if(this->texture != NULL) {
    Material mat = texture->getTexturedMaterial(ray);
    return mat;
  }
  else {
    return this->material;
  }
}

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
  std::vector <float> out_u;
  std::vector <float> out_v;
  Material out_mat;
  Color* out_tex = NULL;

  std::cout << "Load file init!\n";
  bool load = loadOBJ(path, &out_vertices, &out_faces, &out_u, &out_v, out_mat, out_tex);
  std::cout << "Load file done!\n";

  if (load){
    if(this->vertices != NULL)
      delete[] this->vertices;
    if(this->faces != NULL)
      delete[] this->faces;
    if(this->texture != NULL) {
      delete[] this->texture;
    }
    this->texture = NULL;

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

    if(out_tex != NULL) { // Check if there is a texture loaded. v_out.size() could be used instead
      texture = new Texture(out_mat,
                            out_u,
                            out_v,
                            out_tex,
                            getImageWidth(),
                            getImageHeight());
    }

    std::cout << "Passed!\n";
  }

  return load;
}
