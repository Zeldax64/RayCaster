#include "core/renderer/RayCasting.h"

bool shadow_debug = false;
extern bool debug, mouse_debug;

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

int x_line;
int y_line;

void RayCasting::render() {
  std::cout << "RayCasting::render()->render start!\n";
  scn->worldToCamTransform();

#pragma omp parallel for
  for(uint32_t l = 0; l < height; l++) {
    float y = (H/2) - dy/2 - l * dy;
    for(uint32_t c = 0; c < width; c++) {
      //std::cout << "X: " << c << " Y:" << l << "\n";

      x_line = c;
      y_line = l;

      float x = -(W/2) + dx/2 + c * dx;
      Vertex3f vector = Vertex3f(x, y, -d);
      vector = vector.unit();
      Ray ray = Ray(vector);
      Vertex3f n;
      Material mat;
      float t;
      t = scn->hitRay(ray, mat, n);

      if(t >= 0.0 && t < FLT_MAX) {
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
  std::cout << "RayCasting::render()->render finishes!\n";

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


void RayCasting::calcIllumination(Color * buffer, float t, Material & mat, Ray & ray, Vertex3f & n) {
  //std::cout << "->calcIllumination()" << "\n";
  //std::cout << "X: " << x_line << " Y: " << y_line << "\n";
  Color* col_amb = scn->getAmb();

  Color I_amb, I_dif, I_spe;
  Color* kamb;
  Color* kdif;
  Color* kspe;
  // Ambient illumination
  kamb = mat.getAmb();
  I_amb = (*col_amb) * (*kamb);

  std::list<Light*>* lights = scn->getLights();
  std::list<Light*>::iterator it_lights;

  Vertex3f hit_point;
  bool shadow;
  for(it_lights = lights->begin(); it_lights != lights->end(); ++it_lights){
      Light* src = (*it_lights);
      Color* src_int = src->getSource();
      // Handling vectors
      Vertex3f ray_dir = ray.getDirection();
      Vertex3f ray_org = ray.getOrigin();
      hit_point = ray_dir * t + ray_org;
      Vertex3f l = src->getPosition() - hit_point;
      l = l.unit();
      //Vertex3f v = (-hit_point).unit(); // Flipped ray
      Vertex3f v = -ray_dir; // Flipped ray

      shadow = calcShadow(src, hit_point);

      if(!shadow) {
        // Diffuse illumination
        float cos_theta = l.dotProduct(n);
        if(cos_theta >= 0.0) {
          kdif = mat.getDif();
          Color contribution = (*src_int) * (*kdif) * cos_theta;
          I_dif =  I_dif + contribution;
        }
        if(mouse_debug) {
          std::cout << "Diffuse Contribution:\n";
          std::cout << "cos" << cos_theta << "\n";
          std::cout << "normal: "; n.print();
          std::cout << "l: "; l.print();
        }

        // Specular illumination
        kspe = mat.getSpe();
        float spe_exp = mat.getSpeExp();
        Vertex3f r = n*2*(l.dotProduct(n));
        r = r.unit();
        cos_theta = r.dotProduct(v);
        if(cos_theta >= 0.0) {
          cos_theta = pow(cos_theta, spe_exp);
          Color contribution = (*src_int) * (*kspe) * cos_theta;
          I_spe = I_spe + contribution;
        }

        if(mouse_debug) {
          std::cout << "Specular Contribution:\n";
          std::cout << "cos" << cos_theta << "\n";

        }

        //std::cout << "I_amb: "; I_amb.print();
        //std::cout << "I_dif: "; I_dif.print();
        //std::cout << "I_spe: "; I_spe.print();
        //std::cout << "kamb: "; kamb->print();
        //std::cout << "kdif: "; kdif->print();
        //std::cout << "kspe: "; kspe->print();
      }
    }

    *buffer = I_amb + I_dif + I_spe;
}

bool RayCasting::calcShadow(Light* src, Vertex3f intersection) {
      shadow_debug = true;
      Vertex3f dir = src->getPosition() - intersection;
      Vertex3f vector = dir.unit();
      intersection = intersection+vector*1e-5; // Trick to avoid self-intersection: Push ray origin a little in light's direction
      Ray ray = Ray(intersection, vector);
      float t = scn->lookShadow(ray);

      //if(t != FLT_MAX && (vector*t).length() < dir.length()) { // t > epsilon to avoid shadow acme
      if(t > 0.0 && t < dir.length()) { // t > epsilon to avoid shadow acme
        if(mouse_debug) {
          std::cout << "--- calcShadow() SHADOW --- \n";
          std::cout << "vector: "; vector.print();
          std::cout << "origin: "; intersection.print();
          std::cout << "hitpoint to light: "; (vector*t+intersection).print();
          std::cout << "T: " << t << "\n";
          std::cout << "Light pos: "; src->getPosition().print();
          std::cout << "Ray: "; ray.print();
        }
        shadow_debug = false;
        return true;
      }
      else{
        if(mouse_debug) {
          std::cout << "--- calcShadow() NO SHADOW--- \n";
          std::cout << "vector: "; vector.print();
          std::cout << "origin: "; intersection.print();
          std::cout << "hitpoint: "; (vector*t+intersection).print();
          std::cout << "T: " << t << "\n";
          std::cout << "Light pos: "; src->getPosition().print();
          std::cout << "Ray: "; ray.print();
          shadow_debug = false;
        }
        return false;
      }
}
