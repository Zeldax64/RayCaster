#include "app/objects/Pot.h"
#define imax 11

Pot::Pot() {
	int angulo = 45;
	float seno, cosseno;
	int j,k,a,b,c,d;
    	int kmax = 360/angulo;

	verticessize = imax*kmax;
	facessize = (imax-1)*kmax*2;

	vertices = new Vertex3f[verticessize];
	faces = new Face3f[facessize]; 
	float pote[imax][2] = {
			{0.0,0.0},
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
	j=0;
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
}

Material* Pot::getMaterial() { return &this->material; }

Material Pot::getTexturedMaterial(uint32_t face, float u, float v) {
    return *(this->getMaterial());
}


void Pot::print(){

	for(uint8_t i = 0; i < verticessize; i++){
		vertices[i].print();
	}
}
