#include "core/color/Color.h"

Color::Color() { setColor(0.0, 0.0, 0.0); }

Color::Color(float r, float g, float b) { setColor(r, g, b); }

Color::~Color() {}

void Color::setColor(float r, float g, float b) {
  colors[0] = r;
  colors[1] = g;
  colors[2] = b;
}

void Color::setRed(float r) {
  colors[0] = r;
}

void Color::setGreen(float g) {
  colors[1] = g;
}

void Color::setBlue(float b) {
  colors[2] = b;
}

float Color::getRed() { return colors[0]; }
float Color::getGreen() { return colors[1]; }
float Color::getBlue() { return colors[2]; }

Color Color::operator + (Color & param) {
  Color temp;
  temp.setColor(this->getRed() + param.getRed(),
                this->getGreen() + param.getGreen(),
                this->getBlue() + param.getBlue()
              );
  return temp;
}

Color Color::operator * (const Color & param) {
  Color temp;
  temp.setRed(colors[0] * param.colors[0]);
  temp.setGreen(colors[1] * param.colors[1]);
  temp.setBlue(colors[2] * param.colors[2]);
  return temp;
}

Color Color::operator * (const float val) {
  Color temp;
  temp.setColor(colors[0] * val,
                colors[1] * val,
                colors[2] * val);
  return temp;
}

void Color::print() {
  std::cout << "Red: "  << colors[0] <<
              " Green:" << colors[1] <<
              " Blue: " << colors[2] <<
              "\n";
}
