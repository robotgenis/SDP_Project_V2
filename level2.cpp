#include "level2.h"
#include "GameObject.h"
#include "FEHUtility.h"

/*
*Function for LEVEL2 namespace
*void GameLevel LEVEL2::createLevel()
*   creates level and returns the level object
*Ex. 
*   Used in main.cpp to create level 2 when user selects level 2
*Authors: Brandon Y., Aadit S.
*/
GameLevel LEVEL2::createLevel(){
	GameLevel level;
	
	//first part of level objects
	level.objects[0] = GameObject(0,200,100,40, STYLE_GRASS);
	level.objects[1] = GameObject(100,200,80,10, STYLE_PLATFORM, 0, 160);
	level.objects[2] = GameObject(500,200,80,10, STYLE_PLATFORM, 0, -160);
	//second part of level objects
	level.objects[3] = GameObject(580,200,250,40, STYLE_GRASS);
	level.objects[4] = GameObject(680,140,50,60, STYLE_BOX);
	level.objects[5] = GameObject(900,140,100,100, STYLE_BOX);
	level.objects[6] = GameObject(1080,200,80,10, STYLE_PLATFORM, -160, 0);
	//third part of level objects
	level.objects[7] = GameObject(1220,40,100,200, STYLE_BOX);
	level.objects[8] = GameObject(1360,40,80,10, STYLE_PLATFORM, 0, 160);
	level.objects[9] = GameObject(1460,20,20,20, STYLE_DEATH);
	level.objects[10] = GameObject(1680,40,80,10, STYLE_PLATFORM, 0, -160);
	level.objects[11] = GameObject(1620,20,20,20, STYLE_DEATH);
	level.objects[12] = GameObject(1760,40,80,200, STYLE_BOX);
	//end of level flag
	level.objects[13] = GameObject(1780,10,20,30, STYLE_FLAG);

	//set object count for loops
	level.objCount = 14;

	//initilize player and starting position
	level.player = Player(20,180, 20, 20);

	//set physics, jumping and moving parameteres
	level.player.xVelocity = 3;
	level.player.jumpVelocity = 8;
	level.player.yVelocity = 0;
	level.player.accel = 15;

	//set screen starting offset
	level.offsetX = 0;
	level.offsetY = 0;

	//set scene offset min max and edge range
	level.offsetXMin = 0;
	level.offsetXMax = 1500;
	level.offsetYMin = -100;
	level.offsetYMax = 0;
	level.offsetRange = 130;

	//initilize time variable to track moving objects
	level.loopTime = 0;
	level.loopTimeTotal = 6;

	//initlize level timing variables
	level.levelTime = 60;
	level.playTime = 0;
	
	//set points for completing level
	level.levelPoints = 200;
	level.levelPointsTimeMulti = 10;
	
	//return created level
	return level;
}