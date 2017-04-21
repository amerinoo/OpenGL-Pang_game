/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include <iostream>
#include <getopt.h>
#include <GL/glut.h>
#include "game.h"
#include "constants.h"
using namespace std;

void display();
void keyboard(unsigned char c, int x, int y);
void keyboardUp(unsigned char c, int x, int y);
void special(int key, int x, int y);
void specialUp(int key, int x, int y);
void idle();
void usage(char *);
void changeStrategyType(StrategyType * strategy, char * optarg);

const char * windowTitle = "Pang game - Merino";

Game game;
long last_t;

StrategyType Constants::strategyTypePlayer = HUMAN_AGENT;
StrategyType Constants::strategyTypeEnemy  = REFLEX_AGENT;
char * Constants::player1Name = (char *) "Player 1";
char * Constants::player2Name = (char *) "Player 2";
int main(int argc, char * argv[]){
    /* parse options */
    int option_index = 0, opt;
    static struct option loptions[] = {
        { "help",        no_argument,       0, 'h' },
        { "player",      required_argument, 0, 'P' },
        { "enemy",       required_argument, 0, 'E' },
        { "player_name", required_argument, 0, 'p' },
        { "enemy_name",  required_argument, 0, 'e' },
        { NULL,                          0, 0,   0 }
    };

    while (1) {
        opt = getopt_long(argc, argv, "hP:E:p:e:",
          loptions, &option_index);
        if (opt == -1) break;
        switch (opt) {
            case '0': break;
            case 'h':
                usage(argv[0]);
                break;
            case 'P':
                changeStrategyType(&Constants::strategyTypePlayer, optarg);
                break;
            case 'E':
                changeStrategyType(&Constants::strategyTypeEnemy, optarg);
                break;
            case 'p':
                Constants::player1Name = optarg;
                break;
            case 'e':
                Constants::player2Name = optarg;
                break;
        }
    }
    srand(time(NULL));
    Plane leftPlane   = Plane(Vector3(1, 0), Vector3(0, 0));
    Plane rightPlane  = Plane(Vector3(-1, 0), Vector3(Constants::DEFAULT_WIDTH, 0));
    Plane bottomPlane = Plane(Vector3(0, 1), Vector3(0, 0));
    game = Game(new PangScenario(leftPlane, rightPlane, bottomPlane,
          Constants::DEFAULT_WIDTH, Constants::DEFAULT_HEIGHT));
    game.startGame();
    last_t = 0;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(Constants::DEFAULT_WIDTH * Constants::PIXELS_PER_METER,
      Constants::DEFAULT_HEIGHT * Constants::PIXELS_PER_METER);
    glutCreateWindow(windowTitle);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
    glutSpecialFunc(special);
    glutSpecialUpFunc(specialUp);
    glutIdleFunc(idle);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, Constants::DEFAULT_WIDTH, 0, Constants::DEFAULT_HEIGHT);
    glutMainLoop();


    return 0;
} // main

void display(){
    glClearColor(Color::background.red, Color::background.green,
      Color::background.blue, Color::background.alpha);
    glClear(GL_COLOR_BUFFER_BIT);

    game.getPangScenario()->draw();
    game.printScores(1, Constants::DEFAULT_HEIGHT * 0.95, 0);
    game.printScores(1, Constants::DEFAULT_HEIGHT * 0.9, 1);

    glutSwapBuffers();
}

void keyboard(unsigned char c, int x, int y){
    c = tolower(c); // Prevent upper case

    if (c == '-') game.getPangScenario()->shoot(PLAYER_1);
    else if (c == ' ') game.getPangScenario()->shoot(PLAYER_2);
    else if (c == 'r') game.getPangScenario()->reset();
    else if (c == 'p') game.pause();
    else if (c == 'a') game.getPangScenario()->move(PLAYER_2, LEFT);
    else if (c == 'd') game.getPangScenario()->move(PLAYER_2, RIGHT);
}

void keyboardUp(unsigned char c, int x, int y){
    c = tolower(c); // Prevent upper case

    if (c == 'a' || c == 'd') game.getPangScenario()->move(PLAYER_2, STOP);
}

void special(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
            game.getPangScenario()->move(PLAYER_1, LEFT);
            break;
        case GLUT_KEY_RIGHT:
            game.getPangScenario()->move(PLAYER_1, RIGHT);
            break;
    }
    glutPostRedisplay();
}

void specialUp(int key, int x, int y){
    switch (key) {
        case GLUT_KEY_UP:
            break;
        case GLUT_KEY_DOWN:
            break;
        case GLUT_KEY_LEFT:
        case GLUT_KEY_RIGHT:
            game.getPangScenario()->move(PLAYER_1, STOP);
            break;
    }
    glutPostRedisplay();
}

void idle(){
    long t;

    t = glutGet(GLUT_ELAPSED_TIME);

    if (last_t == 0) {
        last_t = t;
    } else {
        game.integrate((t - last_t) / 1000.0);
        last_t = t;
    }


    glutPostRedisplay();
}

void usage(char * name){
    cout << "Usage: " << name << " [OPTIONS]" << endl
         << "\nHelp options:" << endl
         << "  -h, --help              Print this help message" << endl
         << "\nAgent options:" << endl
         << "  -P  --player            Select player strategy (Default Human)" << endl
         << "  -E  --enemy             Select enemy strategy  (Default Reflex)" << endl
         << "  Options:" << endl
         << "    · human" << endl
         << "    · random" << endl
         << "    · reflex" << endl
         << "\nAgent name options:" << endl
         << "  -p  --player_name       Change player name (Default Player 1)" << endl
         << "  -e  --enemy_name        Change enemy name  (Default Player 2)" << endl
         << "" << endl
         << "Note: Order is not important." << endl
         << "Examples:" << endl
         << "  " << name << endl
         << "  " << name << " -P reflex -E human" << endl
         << "  " << name << " -e Merino" << endl
         << endl;
    exit(EXIT_SUCCESS);
}

void changeStrategyType(StrategyType * strategy, char * optarg){
    if (strcmp("human", optarg) == 0) (*strategy) = HUMAN_AGENT;
    else if (strcmp("random", optarg) == 0) (*strategy) = RANDOM_AGENT;
    else if (strcmp("reflex", optarg) == 0) (*strategy) = REFLEX_AGENT;
}
