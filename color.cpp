/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include "color.h"

Color::Color(){ }

Color::Color(const GLfloat red, const GLfloat green, const GLfloat blue, const GLfloat alpha)
    : red(RGBToGlut(red)), green(RGBToGlut(green)), blue(RGBToGlut(blue)), alpha(RGBToGlut(alpha)){ }

const Color Color::background = Color(0, 250, 0);
const Color Color::ball       = Color(180, 0, 0);

GLfloat Color::RGBToGlut(int num){
    return num / 255.0;
}
