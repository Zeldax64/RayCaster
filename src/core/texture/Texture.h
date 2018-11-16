/*
	Texture Class - This class is will work correctly for triangle meshes ONLY
*/

#pragma once

#include <vector>

#include <stdint.h>

#include "core/math/Vertex3f.h"
#include "core/math/Face3f.h"
#include "core/color/Color.h"
#include "core/material/Material.h"
#include "core/math/Ray.h"

class Texture
{
	Material mat;
	std::vector <float> u;
	std::vector <float> v;
	Color* tex_img;
	int img_width, img_height;

public:
	Texture(Material new_mat, 
			std::vector <float> u, 
			std::vector <float> v, 
			Color* image, 
			int width, 
			int height);

	~Texture();

	Material getTexturedMaterial(Face3f & face, uint32_t face_num, float u, float v);
};	