#include "core/renderer/RayCasting.h"

RayCasting::RayCasting(uint32_t width, uint32_t height) {
  buff = new Color[width * height];
  this->width = width;
  this->height = height;
  this->H = 1.0;
  this->W = 1.0;
  this->dx = this->W / this->width;
  this->dy = this->H / this->height;
  this->d = 1.0;
  this->bg = false; // No background
}


RayCasting::~RayCasting() {
  delete[] buff;
  delete[] bg_buff;
}

void RayCasting::render() {
  scn->worldToCamTransform();

#pragma omp parallel for
  for(uint32_t l = 0; l < height; l++) {
    float y = (H/2) - dy/2 - l * dy;
    for(uint32_t c = 0; c < width; c++) {
      float x = -(W/2) + dx/2 + c * dx;
      Ray ray = Ray(x, y, -d);
      Vertex3f n;
      Material mat;
      float t;
      t = scn->hitRay(ray, mat, n);

      if(t >= 1.0 && t < FLT_MAX) {
        calcIllumination(&buff[l*width+c],
                         t,
                         mat,
                         ray,
                         n
                       );
      }
      else {
        if(this->bg == true) {
          buff[l*width+c].setColor(bg_buff[l*width+c].getRed(),
                                   bg_buff[l*width+c].getGreen(),
                                   bg_buff[l*width+c].getBlue());
        }
        else {
          buff[l*width+c].setColor(0.0,
                                   0.0,
                                   0.0);
        }
      }
    }
  }
}

void RayCasting::setScenery(Scenery * scn) {
  this->scn = scn;
}

void RayCasting::setCamera(Camera * cam) {
  this->cam = cam;
}

Scenery* RayCasting::getScenery() {
  return scn;
}

bool RayCasting::loadBG(const char* filename) {
  Color* temp_buff;
  if(loadImage(filename, temp_buff)) {
    this->bg = true;

    if(bg_buff == NULL) {
      delete[] bg_buff;
    }
    this->bg_buff = temp_buff;

    // resizing buffer
    this->width = getImageWidth();
    this->height = getImageHeight();
    delete [] this->buff;
    this->buff = new Color[width * height];
    this->dx = this->W / this->width;
    this->dy = this->H / this->height;
    return true;
  }
  else {
    return false;
  }

}

uint32_t RayCasting::getWidth() { return this->width; }
uint32_t RayCasting::getHeight() { return this->height; }
Camera* RayCasting::getCamera() { return cam; }
Color* RayCasting::getBuffer() { return buff; }


/*----- Private methods -----*/
void RayCasting::calcIllumination(Color * buffer, float t, Material & mat, Ray & ray, Vertex3f & n) {
  Color* col_amb = scn->getAmb();

  Color I_amb, I_dif, I_spe;

  // Ambient illumination
  Color* kamb = mat.getAmb();
  I_amb = (*col_amb) * (*kamb);

  std::list<Light*>* lights = scn->getLights();
  std::list<Light*>::iterator it_lights;
  for(it_lights = lights->begin(); it_lights != lights->end(); ++it_lights){
      Light* src = (*it_lights);
      Color* src_int = src->getSource();
      // Handling vectors
      Vertex3f ray_dir = ray.getDirection();
      Vertex3f hit_point = ray_dir * t;
      Vertex3f l = src->getPosition() - hit_point;
      l = l.unit();
      Vertex3f v = (-hit_point).unit();

      if(!calcShadow(src, hit_point)) {
        // Diffuse illumination
        float cos_theta = n.dotProduct(l);
        if(cos_theta >= 0.0) {
          Color* kdif = mat.getDif();
          Color contribution = (*src_int) * (*kdif) * cos_theta;
          I_dif =  I_dif + contribution;
        }

        // Specular illumination
        Color* k_spe = mat.getSpe();
        float spe_exp = mat.getSpeExp();
        Vertex3f r = n*2*(l.dotProduct(n))*n-l;
        cos_theta = r.dotProduct(v);
        if(cos_theta >= 0.0) {
          cos_theta = pow(cos_theta, spe_exp);
          Color contribution = (*src_int) * (*k_spe) * cos_theta;
          I_spe = I_spe + contribution;
        }

        *buffer = I_amb + I_dif + I_spe;
      }
      else {
        *buffer = I_amb;
      }
  }

}

bool RayCasting::calcShadow(Light* src, Vertex3f intersection) {
      Vertex3f dir = src->getPosition() - intersection;
      dir = dir.unit();
      Ray ray = Ray(intersection, dir);
      float t = scn->lookShadow(ray);

      if(t != FLT_MAX) {
        return true;
      }

  return false;
}
