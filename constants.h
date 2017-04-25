/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef enums_h
#define enums_h

enum StrategyType {
    HUMAN_AGENT,
    RANDOM_AGENT,
    REFLEX_AGENT
};

enum Texture {
    BACKGROUND,
    MARIO_STOP,
    MARIO_RIGHT,
    MARIO_LEFT,
    LINK_STOP,
    LINK_RIGHT,
    LINK_LEFT
};

class Constants {
public:
    static const int DEFAULT_WIDTH      = 16;  // meters
    static const int DEFAULT_HEIGHT     = 8;   // meters
    static const int PIXELS_PER_METER   = 100; // pixels
    static const int VELOCITY_SEPARATOR = 2;

    static const int DEFAULT_LIVES           = 3;
    static const int TIME_IMMORTAL           = 1; // seconds
    static const int CHARACTER_SPEED         = 4;
    static const double CHARACTER_BASE_WIDTH = 0.5; // meters
    static const double CHARACTER_HEIGHT     = 1;   // meters

    static const int BIG_BALL_POINTS    = 100;
    static const int MEDIUM_BALL_POINTS = 50;
    static const int SMALL_BALL_POINTS  = 25;
    static const int LAST_BALL_POINTS   = 100;
    static const int HIT_PUNISHMENT     = 20;

    static const double SMALL_BALL_SIZE  = 0.2; // meters
    static const double MEDIUM_BALL_SIZE = 0.4; // meters
    static const double BIG_BALL_SIZE    = 0.8; // meters

    static const double EPSILON         = 0.25; // meters
    static const double SAFETY_DISTANCE = 2.5;  // meters
    static const double CONE_WIDTH      = 0.5;

    static char * player1Name;
    static char * player2Name;
    static char * background;
    static StrategyType strategyTypePlayer;
    static StrategyType strategyTypeEnemy;

    static Texture marioTextures[3];
    static Texture linkTextures[3];
};

enum PlayerID {
    PLAYER_1 = 0,
    PLAYER_2 = 1
};


enum Action {
    STOP  = 0,
    RIGHT = 1,
    LEFT  = 2
};

#endif // ifndef enums_h
