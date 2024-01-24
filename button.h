#ifndef GRAPHICS_STARTER_BUTTON_H
#define GRAPHICS_STARTER_BUTTON_H

#include "Quad.h"
#include <string>

class Button : public Quad {
private:
    std::string label;
    bool status;
    color originalFill, hoverFill, pressFill;
    // bool isHovering;

public:
    Button(color fill, point center, unsigned int width, unsigned int height, std::string label);
    Button(point center, unsigned int width, unsigned int height, bool status);
    /* Uses OpenGL to draw the box with the label on top */
    virtual void draw() const override;

    void hoverDraw() const;

    /* Returns true if the coordinate is inside the box */
    bool isOverlapping(int x, int y) const;

    /* Change color of the Button when the user is hovering over it */
    void hover();

    /* Draws outline around game squares when the user is hovering */
    void gameSquareHover();

    /* Change color of the Button when the user is clicking on it */
    void pressDown();

    /* Change the color back when the user is not clicking/hovering */
    void release();

    /* Removes outline from game squares back when user isn't hovering */
    void gameSquareRelease();

    /* Changes state of game square from what it currently is */
    void changeStatus();

    /* returns status of game square */
    bool getStatus();
};

#endif //GRAPHICS_STARTER_BUTTON_H
