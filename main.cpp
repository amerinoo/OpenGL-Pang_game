/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <getopt.h>
#include <GL/glut.h>
#include "ball.h"
#include "gravityForceGenerator.h"
using namespace std;

#define WIDTH            6
#define HEIGHT           6
#define PIXELS_PER_METER 100

void display();
void keyboard(unsigned char c, int x, int y);
void idle();
void usage(char *);

const char * windowTitle = "Pang game - Merino";

Ball ball;
Vector3 initialPosition(3, 0);
Vector3 initialVelocity(0, 10);
long last_t;
bool gravity = true;

int main(int argc, char * argv[]){
    /* parse options */
    int option_index = 0, opt;
    static struct option loptions[] = {
        { "help", no_argument, 0, 'h' },
        { NULL,             0, 0,   0 }
    };

    while (1) {
        opt = getopt_long(argc, argv, "h",
          loptions, &option_index);
        if (opt == -1) break;
        switch (opt) {
            case '0': break;
            case 'h':
                usage(argv[0]);
                break;
        }
    }

    ball   = Ball(1, initialPosition, initialVelocity, 0.1, Color::ball);
    last_t = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(WIDTH * PIXELS_PER_METER, HEIGHT * PIXELS_PER_METER);
    glutCreateWindow(windowTitle);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WIDTH, 0, HEIGHT);

    glutMainLoop();


    return 0;
} // main

void display(){
    glClearColor(Color::background.red, Color::background.green,
      Color::background.blue, Color::background.alpha);
    glClear(GL_COLOR_BUFFER_BIT);

    ball.draw();

    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y){
    if (c == ' ') {
        ball.setPosition(initialPosition);
        ball.setVelocity(initialVelocity);
    } else if (c == 'g') {
        gravity = !gravity;
    }
}

void idle(){
    ball.clearForceAccumulator();
    GravityForceGenerator gfg;
    if (gravity) gfg.updateForce(&ball);
    long t;

    t = glutGet(GLUT_ELAPSED_TIME);

    if (last_t == 0) {
        last_t = t;
    } else {
        ball.integrate((t - last_t) / 1000.0);
        last_t = t;
    }


    glutPostRedisplay();
}

void usage(char * name){
    cout << "Usage: " << name << " [OPTIONS]" << endl
         << "\nHelp options:" << endl
         << "  -h, --help         Print this help message" << endl
         << "Note: Order is not important." << endl
         << "Examples:" << endl
         << "  " << name << endl
         << endl;
    exit(EXIT_SUCCESS);
}
