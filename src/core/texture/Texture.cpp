#include "core/texture/Texture.h"

Texture::Texture(Material new_mat, 
				 std::vector <float> u,
				 std::vector <float> v,
				 Color* image,
				 int width,
				 int height) 
{
	this->mat = new_mat;
	for(uint32_t i = 0; i < u.size(); i++){
		this->u.push_back(u[i]);
		this->v.push_back(v[i]);
	}

	/*
	for(int i = 0; i < v.size(); i++) {
      std::cout << i << ") u: " << u[i] <<" v: " << v[i] << std::endl;
    }*/

    this->tex_img = image;
    this->img_width = width;
    this->img_height = height;

    std::cout << "Width: " << img_width << " Height: " << img_height << std::endl;
}

Texture::~Texture() {
	delete[] this->tex_img;
}

Material Texture::getTexturedMaterial(Face3f & face, uint32_t face_num, float u, float v) {
	uint32_t Va = face.vertices[0];
	uint32_t Vb = face.vertices[1];
	uint32_t Vc = face.vertices[2];

	float ua, ub, uc, va, vb, vc;

	ua = this->u[Va+face_num*3];
	va = this->v[Va+face_num*3];

	ub = this->u[Vb+face_num*3];
	vb = this->v[Vb+face_num*3];

	uc = this->u[Vc+face_num*3];
	vc = this->v[Vc+face_num*3];

	float u_img = ua + u*(ub-ua) + v*(uc-ua);
	float v_img = va + u*(vb-va) + v*(vc-va);

	u_img = u_img * img_width;
	v_img = v_img * img_width;

	int x_pix = int(u_img);
	int y_pix = int(v_img);

	Color pixel = this->tex_img[y_pix*this->img_height + x_pix];

	Material ret_mat = this->mat;
	Color* mat_dif = mat.getDif();

	float new_red = mat_dif->getRed() * pixel.getRed();
	float new_green = mat_dif->getGreen() * pixel.getGreen();
	float new_blue = mat_dif->getBlue() * pixel.getBlue();

	ret_mat.setDif(new_red, new_green, new_blue);

	return ret_mat;
}