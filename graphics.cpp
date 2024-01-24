#include "graphics.h"
#include "quad.h"
#include "button.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

#ifdef _WIN32
const string python = "py";
#else
const string python3 = "python3";
#endif

double textPosX, textPosY;
GLdouble width, height;
int wd;
//ASCII keyboard for type, had to remove ' because it was causing issues
vector<int> keyboard = {8, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43,
                        44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58,
                        59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73,
                        74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88,
                        89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102,
                        103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113,
                        114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124,
                        125, 126, 127};
vector<char> typedStatement;
vector<char> translatedStatement;
Quad topBox({1, 1, 1}, {200, 125}, 300, 150);
Quad resultBox({1, 1, 1}, {200, 325}, 300, 150);
Button goBox({1, 1, 1}, {400, 225}, 50, 50, "Go");
int typeCount = 0;
string language;
int wordCount;
int currentx = 60, currenty = 75;
const int STARTX = 60, STARTY = 75;
const int STARTX2 = 60, STARTY2 = 275;
const int MAXTYPE = 223;

void init() {
    width = 500;
    height = 500;
}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque

}

void typeFunction(int keypress) {
    //8 for Windows & 127 for Mac
    if (keypress == 8 || keypress == 127) {
        typeCount--;
        typedStatement.pop_back();
        currentx -= 10;
    }
    else if (typeCount > MAXTYPE) {
        //If you've reached the limit, stop functioning until you backspace...
    }
    else {
        typeCount++;
        typedStatement.push_back(keypress);
    }
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // Tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height); // DO NOT CHANGE THIS LINE (unless you're on a Mac running Catalina)

    // Do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION); // DO NOT CHANGE THIS LINE
    glLoadIdentity(); // DO NOT CHANGE THIS LINE
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f); // DO NOT CHANGE THIS LINE

    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT); // DO NOT CHANGE THIS LINE

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // DO NOT CHANGE THIS LINE

    /*
     * Draw here
     */

    //Type box
    topBox.draw();

    //Result box
    resultBox.draw();

    //Reverse box
    goBox.draw();

    //For loop for drawing vector chars:
    for (int i = 0; i < typedStatement.size(); i++) {
        glColor3f(0, 0, 0);
        glRasterPos2d(STARTX + (i % 28 * 10), STARTY + (i / 28 * 15));
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, typedStatement[i]);
    }

    //For loop for drawing translation chars or whatever I end up doing:
    for (int i = 0; i < translatedStatement.size(); i++) {
        glColor3f(0, 0, 0);
        glRasterPos2d(STARTX2 + (i % 28 * 10), STARTY2 + (i / 28 * 15));
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, translatedStatement[i]);
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y)
{
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }

    for (int i = 0; i < keyboard.size(); i++) {
        if (key == keyboard[i]) {
            typeFunction(keyboard[i]);
        }
    }

    glutPostRedisplay();
}

void cursor(int x, int y) {
    if (goBox.isOverlapping(x, y)) {
        goBox.hover();
    }
    else {
        goBox.release();
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    if (goBox.isOverlapping(x, y) && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        goBox.pressDown();

        //Convert the typed statement into string and send it to python for translation
        string command;

        //https://www.geeksforgeeks.org/convert-vector-of-chars-to-string-in-cpp/
        string translate(typedStatement.begin(), typedStatement.end());
        command = python3 + " ../translate.py " + translate + " " + language;

        //Send to Python
        system(command.c_str());

        //Get the result from translation.txt
        char letter;
        ifstream inputFile;
        inputFile.open("../translation.txt");
        while (inputFile) {
            inputFile.get(letter);
            translatedStatement.push_back(letter);
        }
        translatedStatement.pop_back();

        inputFile.close();
    }

    glutPostRedisplay();
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    string line;
    ifstream inputFile;
    inputFile.open("../validlanguages.txt");
    bool good = false;
    cout << "Disclaimer: If you're translating into a non-UTF8 language (ie. Chinese, Russian etc.) they are incompatible with GLUT and will only appear in \'translation.txt\'" << endl;
    cout << "Please enter a valid language option: " << endl;
    getline(cin, language);
    while (inputFile) {
        getline(inputFile, line);
        if (language == line) {
            good = true;
            inputFile.close();
        }
    }
    inputFile.close();
    while (good == false) {
        inputFile.open("../validlanguages.txt");
        cout << "Invalid manipulation method, please enter a valid language option: " << endl;
        getline(cin, language);
        while (inputFile) {
            getline(inputFile, line);
            if (language == line) {
                good = true;
                inputFile.close();
            }
        }
    }

    init();

    glutInit(&argc, argv);          // Initialize GLUT

    glutInitDisplayMode(GLUT_RGBA);

    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Translator" /* title */ );

    // Register callback handler for window re-paint event
    glutDisplayFunc(display);

    // Our own OpenGL initialization
    initGL();

    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);

    // handles mouse movement
    glutPassiveMotionFunc(cursor);

    // handles mouse click
    glutMouseFunc(mouse);

    // Enter the event-processing loop
    glutMainLoop();

    return 0;
}
