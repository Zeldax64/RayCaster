#include "app/objects/Pot.h"

Pot::Pot() {
	int angulo = 90;
	float seno, cosseno;
	float pote[imax][2] = {
                        {0.85,0.0},
                        {0.85,0.1},
                        {0.80,0.2},
                        {0.80,0.3},
                        {0.75,0.4},
                        {0.60,0.5},
                        {0.40,0.6},
                        {0.20,0.7},
                        {0.30,0.8},
                        {0.40,0.9}};

    int j=0;
    for(int ang=0;ang<360;ang=ang+angulo)
    {
        cosseno = cos(ang*PI/180);
        seno = sin(ang*PI/180);

        for(int i=0;i<imax;i++)
        {
						vertices[j].moveTo(pote[i][0]*cosseno+0, pote[i][1], -pote[i][0]*seno+0);
            j++;
        }
    }
    int k,a,b,c,d;
    int kmax = 360/angulo;
    j=0;

    for(int kaux=0;kaux<kmax;kaux++)
    {
        for(int i=0;i<imax-1;i++)
        {
            k =  kaux;
            a =  k*imax+i;
            c =  k*imax+i+1;

            if((k+1)>=kmax) b=i;
            else b = (k+1)*imax +i;
            if((k+1)>=kmax) d=i+1;
            else d = (k+1)*imax +i+1;

						faces[j].setFace(a, b, c);
            j++;
						faces[j].setFace(b, d, c);
            j++;
        }
    }

	this->material.setAmb(0.8, 0.8, 0.8);
  this->material.setDif(0.5, 0.5, 0.5);
  this->material.setSpe(0.0, 0.0, 0.0, 0.0);
}

Pot::~Pot() {

}

void Pot::applyTransform(const TMatrix & param) {
	for(uint8_t i = 0; i < verticessize; i++){
		vertices[i].applyTransform(param);
	}
}

float Pot::hitObject(Ray & ray, Vertex3f & ret_n, Material * & ret_mat) {
	float t = hitTriangles(ray, this, vertices, faces, facessize, ret_n, ret_mat);
	return t;
/*
	float best_t = FLT_MAX;
	for (int i = 0; i < facessize; i++) {
		Face3f face = faces[i];
		Vertex3f v0 = vertices[face.vertices[0]];
		Vertex3f v1 = vertices[face.vertices[1]];
		Vertex3f v2 = vertices[face.vertices[2]];

		Vertex3f n;

		float tint = hitTriangle(ray, v0, v1, v2, n);

		if (tint >= 1.0 && tint < best_t) {
			best_t = tint;
			ret_mat = &this->material;
			ret_n = n;
		}
	}
	return best_t;
*/
}

Material* Pot::getMaterial() { return &this->material; }

void Pot::print(){

	for(uint8_t i = 0; i < verticessize; i++){
		vertices[i].print();
	}
}
