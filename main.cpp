/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#include <iostream>
#include <getopt.h>
#include <GL/glut.h>
#include <irrKlang.h>
#include "conio.h"
#include "game.h"
#include "constants.h"
#include "png_texture.h"
using namespace irrklang;

void display();
void keyboard(unsigned char c, int x, int y);
void keyboardUp(unsigned char c, int x, int y);
void special(int key, int x, int y);
void specialUp(int key, int x, int y);
void idle();
void usage(char *);
void changeStrategyType(StrategyType * strategy, char * optarg);
void changeBackground(char * optarg);

const char * windowTitle = "Pang game - Merino";

Game game;
long last_t;

StrategyType Constants::strategyTypePlayer = HEURISTIC_AGENT;
StrategyType Constants::strategyTypeEnemy  = ALPHA_BETA_AGENT;
char * Constants::player1Name       = (char *) "Link";
char * Constants::player2Name       = (char *) "Mario";
char * Constants::background        = (char *) "images/mario_world.png";
Texture Constants::marioTextures[3] = { MARIO_STOP, MARIO_RIGHT, MARIO_LEFT };
Texture Constants::linkTextures[3] = { LINK_STOP, LINK_RIGHT, LINK_LEFT };
int main(int argc, char * argv[]){
    /* parse options */
    int option_index = 0, opt;
    static struct option loptions[] = {
        { "help",        no_argument,       0, 'h' },
        { "player",      required_argument, 0, 'P' },
        { "enemy",       required_argument, 0, 'E' },
        { "player_name", required_argument, 0, 'p' },
        { "enemy_name",  required_argument, 0, 'e' },
        { "background",  required_argument, 0, 'b' },
        { "music",       no_argument,       0, 'm' },
        { NULL,                          0, 0,   0 }
    };

    while (1) {
        opt = getopt_long(argc, argv, "hP:E:p:e:b:m",
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
            case 'b':
                changeBackground(optarg);
                break;
            case 'm':
                ISoundEngine * engine = createIrrKlangDevice();
                if (engine) {
                    engine->play2D("songs/song.ogg", true);
                    Constants::background = (char *) "images/miku.png";
                } else {
                    std::cout << "Could not startup engine" << '\n';
                }
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
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    TextureLoader().loadTextures();
    glutMainLoop();


    return 0;
} // main

void display(){
    glClearColor(Color::background.red, Color::background.green,
      Color::background.blue, Color::background.alpha);
    glClear(GL_COLOR_BUFFER_BIT);

    game.draw();
    game.printScores(1, Constants::DEFAULT_HEIGHT * 0.95, 0);
    game.printScores(1, Constants::DEFAULT_HEIGHT * 0.9, 1);

    glutSwapBuffers();
} // display

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
        case GLUT_KEY_F1:
            game.changePlayerAI(PLAYER_2, HUMAN_AGENT);
            break;
        case GLUT_KEY_F2:
            game.changePlayerAI(PLAYER_2, RANDOM_AGENT);
            break;
        case GLUT_KEY_F3:
            game.changePlayerAI(PLAYER_2, REFLEX_AGENT);
            break;
        case GLUT_KEY_F4:
            game.changePlayerAI(PLAYER_2, HEURISTIC_AGENT);
            break;
        case GLUT_KEY_F5:
            game.changePlayerAI(PLAYER_2, ALPHA_BETA_AGENT);
            break;
        case GLUT_KEY_F8:
            game.changePlayerAI(PLAYER_1, ALPHA_BETA_AGENT);
            break;
        case GLUT_KEY_F9:
            game.changePlayerAI(PLAYER_1, HEURISTIC_AGENT);
            break;
        case GLUT_KEY_F10:
            game.changePlayerAI(PLAYER_1, REFLEX_AGENT);
            break;
        case GLUT_KEY_F11:
            game.changePlayerAI(PLAYER_1, RANDOM_AGENT);
            break;
        case GLUT_KEY_F12:
            game.changePlayerAI(PLAYER_1, HUMAN_AGENT);
            break;
    }
    glutPostRedisplay();
} // special

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
         << "  -P  --player            Select player strategy (Default Heuristic)" << endl
         << "  -E  --enemy             Select enemy strategy  (Default AlphaBeta)" << endl
         << "  Options:" << endl
         << "    · human (F12 / F1)" << endl
         << "    · random (F11 / F2)" << endl
         << "    · reflex (F10 / F3)" << endl
         << "    · heuristic (F9 / F4)" << endl
         << "    · alphabeta (F8 / F5)" << endl
         << "You can change the strategy dynamically using the F# shortcuts (player / enemy)" << endl
         << "\nAgent name options:" << endl
         << "  -p  --player_name       Change player name (Default Link)" << endl
         << "  -e  --enemy_name        Change enemy name  (Default Mario)" << endl
         << "\nBackground options:" << endl
         << "  -b  --background        Change background image (Default mountain)" << endl
         << "  Options:" << endl
         << "    · mountain" << endl
         << "    · beach" << endl
         << "    · miku" << endl
         << "    · mario" << endl
         << "\nBackground options:" << endl
         << "  -m  --music             Activate music during the game" << endl
         << "" << endl
         << "Note: Order is not important." << endl
         << "Examples:" << endl
         << "  " << name << endl
         << "  " << name << " -P reflex -E human" << endl
         << "  " << name << " -e Merino" << endl
         << endl;
    exit(EXIT_SUCCESS);
} // usage

void changeStrategyType(StrategyType * strategy, char * optarg){
    if (strcmp("human", optarg) == 0) (*strategy) = HUMAN_AGENT;
    else if (strcmp("random", optarg) == 0) (*strategy) = RANDOM_AGENT;
    else if (strcmp("reflex", optarg) == 0) (*strategy) = REFLEX_AGENT;
    else if (strcmp("heuristic", optarg) == 0) (*strategy) = HEURISTIC_AGENT;
    else if (strcmp("alphabeta", optarg) == 0) (*strategy) = HEURISTIC_AGENT;
}

void changeBackground(char * optarg){
    if (strcmp("mountain", optarg) == 0) Constants::background = (char *) "images/mountain.png";
    else if (strcmp("beach", optarg) == 0) Constants::background = (char *) "images/beach.png";
    else if (strcmp("miku", optarg) == 0) Constants::background = (char *) "images/miku.png";
    else if (strcmp("mario", optarg) == 0) Constants::background = (char *) "images/mario_world.png";
}
