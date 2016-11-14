#ifndef _VARIABLEGAME_H_
#define _VARIABLEGAME_H_

#define FULL_SCREEN								0		// 0: Window, 1: Full Screen
#define SCREEN_WIDTH							800
#define SCREEN_HEIGHT							600
#define GAME_TITLE								"Castle Game"

#define PI_NUMBER								3.14f

#define FRAME_NUMBER							120		// ~ 0.008 s / frame
#define OBJECT_WIDTH							50
#define OBJECT_HEIGHT							50

#define VELOCITY_VERYSLOW						60		// ~1 pixel / frame
#define VELOCITY_SLOW							120		// ~2 pixel / frame
#define VELOCITY_NORMAL							20		// ~3 pixel / frame
#define VELOCITY_FAST							50		// ~5 pixel / frame
#define VELOCITY_VERYFAST						100		// ~8 pixel / frame

#define NORMAL_ANIMATION_RATE					150 // ms
#define RUN_ANIMATION_RATE						10 // ms

#define TIME_OF_MARIO_TYPE_CHANGING				150 // ms
#define MAX_TIME_OF_MARIO_TYPE_CHANGING			2000 // ms
#define MAX_TIME_OF_MARIO_IMMORTALITY			15000 // ms
#define MAX_TIME_OF_MARIO_THROW_BULLETS			100
#define TIME_OF_MARIO_DIE						2000
#define MAX_BULLETS								4
#define ANGLE_OF_BULLET							(PI_NUMBER / 6.0f)

#define MAX_HEIGHT_MOVE_UP_OF_BRICK				20
#define TIME_OF_LIVING_OF_COINS					5000
#define MAX_DISTANCE_OF_HORIZONTALMOVING_BAR	100
#define RADIUS_MOVING_OF_FLYING_TURTLE			50
#define MAX_DISTANCE_OF_FLYING_TURTLE			400
#define TIME_DELAY_OF_CARNIVOROUS_FLOWER		1500
#define TIME_DISAPPEAR_OF_ENEMY					1000
#define TIME_DELAY_OF_TURTLE					5000
#define RADIUS_MOVING_OF_BULLET					50
#define TIME_OF_SHOOTING_BULLET_OF_MACHINE		5000
#define TIME_OF_SPRING							200
#define TIME_DELAY_OF_BAR_FALLING				50
#define DISTANCE_MAX_OF_MACHINE_BULLET			4000

#define TIME_OF_CHANGING_WORLD					2000
#define TIME_OF_WAITING_WORLD					5000
#endif