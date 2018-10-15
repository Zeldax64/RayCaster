#include "core/material/Material.h"

Material::Material() {
  this->setAmb(1.0, 1.0, 1.0);
  this->setDif(1.0, 1.0, 1.0);
  this->setSpe(1.0, 1.0, 1.0);
}

Material::Material(float ar, float ag, float ab,
                   float dr, float dg, float db,
                   float sr, float sg, float sb) {
  this->setAmb(ar, ag, ab);
  this->setDif(dr, dg, db);
  this->setSpe(sr, sg, sb);
}


Material::~Material() {}

void Material::setAmb(float r, float g, float b) {
  k_amb.setColor(r, g, b);
}

void Material::setDif(float r, float g, float b) {
  k_dif.setColor(r, g, b);
}

void Material::setSpe(float r, float g, float b) {
  k_spe.setColor(r, g, b);
}

Color* Material::getAmb() { return &k_amb; }
Color* Material::getDif() { return &k_dif; }
Color* Material::getSpe() { return &k_spe; }

void Material::operator = (Material &param) {
  //std::cout << "Operator = ";
  //param.print();
  Color* k = param.getAmb();
  this->setAmb(k->getRed(), k->getGreen(), k->getBlue());
  k = param.getDif();
  this->setDif(k->getRed(), k->getGreen(), k->getBlue());
  k = param.getSpe();
  this->setSpe(k->getRed(), k->getGreen(), k->getBlue());
}

void Material::print() {
  k_amb.print();
  k_dif.print();
  k_spe.print();
}
