#include "core/material/Material.h"

Material::Material() {
    col.setColor(1.0, 1.0, 1.0);
}

Material::~Material() {}

void Material::setColor(float r, float g, float b) {
  col.setColor(r, g, b);
}

void Material::setRed(float r) {
  col.setRed(r);
}

void Material::setGreen(float g) {
  col.setGreen(g);
}

void Material::setBlue(float b) {
  col.setBlue(b);
}

Color* Material::getColor() { return &col; }
float Material::getRed() { return col.getRed(); }
float Material::getGreen() { return col.getGreen(); }
float Material::getBlue() {return col.getBlue(); }

void Material::print() {
  col.print();
}
