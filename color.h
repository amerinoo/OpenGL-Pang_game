/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef color_h
#define color_h
#include <GL/glut.h>

class Color {
public:
    static const Color background;
    static const Color ball;
    static const Color player1;
    static const Color player2;
    GLfloat red;
    GLfloat green;
    GLfloat blue;
    GLfloat alpha;

    Color();
    Color(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha = 1);

    GLfloat RGBToGlut(int);
};
#endif // ifndef color_h
