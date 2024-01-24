#include "Button.h"
#include "graphics.h"
using namespace std;

Button::Button(color fill, point center, unsigned int width, unsigned int height, std::string label) : Quad(fill, center, width, height) {
    this->label = label;
    originalFill = fill;
    hoverFill = {fill.red - 0.5, fill.green - 0.5, fill.blue - 0.5};
    pressFill = {fill.red - 0.5, fill.green - 0.5, fill.blue - 0.5};
}

Button::Button(point center, unsigned int width, unsigned int height, bool status) : Quad({1, 1, 1}, center, width, height) {
    this->status = status;
    switch (status) {
        case (true):
            fill = {1, 1, 0};
            break;

        case (false):
            fill = {0.5, 0.5, 0.5};
            break;
    }
    hoverFill = {fill.red + 0.5, fill.green + 0.5, fill.blue + 0.5};
    pressFill = {fill.red - 0.5, fill.green - 0.5, fill.blue - 0.5};
}

void Button::draw() const {
    Quad::draw();
    glColor3f(0, 0, 0);
    glRasterPos2i(center.x - (4 * label.length()), center.y + 7);
    for (const char &letter : label) {
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, letter);
    }
}

void Button::hoverDraw() const {
    glColor3f(fill.red, fill.green, fill.blue);
    glBegin(GL_LINE_LOOP);
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getRightX(), getTopY());
    glVertex2i(getRightX(), getBottomY());
    glEnd();
}

/* Returns true if the coordinate is inside the box */
bool Button::isOverlapping(int x, int y) const {
    if((getCenterX() - width/2 < x and getCenterX() + width/2 > x) and (getCenterY() - width/2 < y and getCenterY() + width/2 > y)) {
        return true;
    }
    return false; // Placeholder for compilation
}


/* Change color of the box when the user is hovering over it */
void Button::hover() {
    setColor(hoverFill);
}

/* Draws outline around game squares when the user is hovering */
void Button::gameSquareHover() {
    /*glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(getLeftX(), getBottomY());
    glVertex2i(getLeftX(), getTopY());
    glVertex2i(getRightX(), getTopY());
    glVertex2i(getRightX(), getBottomY());
    glEnd();*/
    fill = {1,0,0};
}

/* Change color of the box when the user is clicking on it */
void Button::pressDown() {
    setColor(pressFill);
}

/* Change the color back when the user is not clicking/hovering */
void Button::release() {
    setColor(originalFill);
}

/* Removes outline from game squares back when user isn't hovering */
void Button::gameSquareRelease() {
    if(status == true) {
        setColor(1, 1, 0);
    }
    else {
        setColor(.25, .25, .25);
    }
}

/* Changes state of game square from what it currently is */
void Button::changeStatus() {
    if(status == true) {
        status = false;
        setColor(.5, .5, .5);
    }
    else {
        status = true;
        setColor(1, 1, 0);
    }
}

/* returns status of game square */
bool Button::getStatus() {
    return status;
}
