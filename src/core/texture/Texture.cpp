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
	std::cout << "Printing vt: "<< std::endl;
	for(int i = 0; i < v.size(); i++) {
		std::cout << i << ") u: " << u[i] <<" v: " << v[i] << std::endl;
  }
*/
    this->tex_img = image;
    this->img_width = width;
    this->img_height = height;

//    std::cout << "Width: " << img_width << " Height: " << img_height << std::endl;
}

Texture::~Texture() {
	delete[] this->tex_img;
}

Material Texture::getTexturedMaterial(Face3f & face, uint32_t face_num, float u, float v) {
	float ua, ub, uc, va, vb, vc;

	ua = this->u[face_num*3+0];
	va = this->v[face_num*3+0];

	ub = this->u[face_num*3+1];
	vb = this->v[face_num*3+1];

	uc = this->u[face_num*3+2];
	vc = this->v[face_num*3+2];


	float u_img = ua + u*(ub-ua) + v*(uc-ua);
	float v_img = va + u*(vb-va) + v*(vc-va);


	if(u_img > 1.0) {
		u_img = 1.0;
	}
	if(u_img < 0.0) {
		u_img = 0.0;
	}
	if(v_img > 1.0) {
		v_img = 1.0;
	}
	if( v_img < 0.0) {
		v_img = 0.0;
	}

	//u_img = 1.0 - u_img;
	//v_img = 1.0 - v_img;
	u_img = u_img * img_width;
	v_img = v_img * img_width;

	int x_pix = int(u_img);
	int y_pix = int(v_img);

	Color pixel = this->tex_img[y_pix*this->img_width + x_pix];

	Material ret_mat = this->mat;
	Color* mat_dif = mat.getDif();

	float new_red = mat_dif->getRed() * pixel.getRed();
	float new_green = mat_dif->getGreen() * pixel.getGreen();
	float new_blue = mat_dif->getBlue() * pixel.getBlue();

	ret_mat.setDif(new_red, new_green, new_blue);

	return ret_mat;
}
