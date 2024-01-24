#include "graphics.h"
#include "quad.h"

Quad::Quad() {
    fill = {1, 1, 0};
    center = {0, 0};
    width = 50;
    height = 50;
}

Quad::Quad(color fill, point center, unsigned int width, unsigned int height) {
    this->fill = fill;
    this->center = center;
    this->width = width;
    this->height = height;
}

int Quad::getCenterX() const {
    return center.x;
}

int Quad::getLeftX() const {
    return center.x - (width / 2);
}

int Quad::getRightX() const {
    return center.x + (width / 2);
}

int Quad::getCenterY() const {
    return center.y;
}

int Quad::getTopY() const {
    return center.y - (height / 2);
}

int Quad::getBottomY() const {
    return center.y + (height / 2);
}

point Quad::getCenter() const {
    return center;
}

double Quad::getRed() const {
    return fill.red;
}

double Quad::getGreen() const {
    return fill.green;
}

double Quad::getBlue() const {
    return fill.blue;
}

color Quad::getFill() const {
    return fill;
}

unsigned int Quad::getWidth() const {
    return width;
}

unsigned int Quad::getHeight() const {
    return height;
}

void Quad::setColor(double red, double green, double blue) {
    fill = {red, green, blue};
}

void Quad::setColor(color fill) {
    this->fill = fill;
}

void Quad::move(int deltaX, int deltaY) {
    center.x += deltaX;
    center.y += deltaY;
}

void Quad::resize(unsigned int width, unsigned int height) {
    this->width = width;
    this->height = height;
}

void Quad::draw() const {
    // set drawing color to fill color
    glColor3f(fill.red, fill.green, fill.blue);
    // draw rect as QUAD
    glBegin(GL_QUADS);
    // draw corners
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getRightX(), getTopY());
    glVertex2i(getRightX(), getBottomY());
    // end QUAD
    glEnd();
}
