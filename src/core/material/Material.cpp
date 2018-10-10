#include "core/material/Material.h"

Material::Material() {
  this->setAmb(1.0, 1.0, 1.0);
  this->setDif(1.0, 1.0, 1.0);
  this->setEsp(1.0, 1.0, 1.0);
}

Material::~Material() {}

void Material::setAmb(float r, float g, float b) {
  k_amb.setColor(r, g, b);
}

void Material::setDif(float r, float g, float b) {
  k_dif.setColor(r, g, b);
}

void Material::setEsp(float r, float g, float b) {
  k_esp.setColor(r, g, b);
}

Color* Material::getAmb() { return &k_amb; }
Color* Material::getDif() { return &k_dif; }
Color* Material::getEsp() { return &k_esp; }

void Material::operator = (Material &param) {
  Color* k = param.getAmb();
  this->setAmb(k->getRed(), k->getGreen(), k->getBlue());
  k = param.getDif();
  this->setDif(k->getRed(), k->getGreen(), k->getBlue());
  k = param.getEsp();
  this->setDif(k->getRed(), k->getGreen(), k->getBlue());
}

void Material::print() {
  k_amb.print();
}
