/*
 * Project name: Pang Game
 * Version 1
 * Student : Albert Eduard Merino Pulido
 */
#ifndef enums_h
#define enums_h

class Constants {
public:
    static const int DEFAULT_WIDTH    = 16;  // meters
    static const int DEFAULT_HEIGHT   = 8;   // meters
    static const int PIXELS_PER_METER = 100; // pixels

    static const int DEFAULT_LIVES   = 3;
    static const int TIME_IMMORTAL   = 1; // seconds
    static const int CHARACTER_SPEED = 4;

    static const int BIG_BALL_POINTS    = 100;
    static const int MEDIUM_BALL_POINTS = 50;
    static const int SMALL_BALL_POINTS  = 25;
    static const int LAST_BALL_POINTS   = 100;
    static const int HIT_PUNISHMENT     = 20;

    static const double SMALL_BALL_SIZE  = 0.2; // meters
    static const double MEDIUM_BALL_SIZE = 0.4; // meters
    static const double BIG_BALL_SIZE    = 0.8; // meters

    static const double EPSILON         = 0.2; // meters
    static const double SAFETY_DISTANCE = 2.5; // meters
    static const double CONE_WIDTH      = 0.5;
    Constants(){ }
};

enum PlayerID {
    PLAYER_1 = 0,
    PLAYER_2 = 1
};

enum StrategyType {
    HUMAN_AGENT
};

enum Action {
    STOP  = 0,
    RIGHT = 1,
    LEFT  = 2
};

#endif // ifndef enums_h
