#include "level1.h"
#include "GameObject.h"
#include "FEHUtility.h"

/*
*Function for LEVEL1 namespace
*void GameLevel LEVEL1::createLevel()
*   creates level and returns the level object
*Ex. 
*   Used in main.cpp to create level 1 when user selects level 1
*Authors: Brandon Y., Aadit S.
*/
GameLevel LEVEL1::createLevel(){
	GameLevel level;
	
	//first part of level objects
	level.objects[0] = GameObject(0,200,500,40, STYLE_GRASS);
	level.objects[1] = GameObject(150,150,20,50, STYLE_BOX);
	level.objects[2] = GameObject(360,160,40,10, STYLE_PLATFORM);
	level.objects[3] = GameObject(300,120,40,10, STYLE_PLATFORM);
	level.objects[4] = GameObject(400,100,100,100, STYLE_GRASS);
	//second part of level objects
	level.objects[5] = GameObject(560,100,40,10, STYLE_PLATFORM);
	level.objects[6] = GameObject(660,100,40,10, STYLE_PLATFORM);
	level.objects[7] = GameObject(760,100,100,140, STYLE_GRASS);
	//Third part of level objects
	level.objects[8] = GameObject(890,-100,10,290, STYLE_PLATFORM);
	level.objects[9] = GameObject(860,210,90,30, STYLE_GRASS);
	level.objects[10] = GameObject(1000,160,50,10, STYLE_PLATFORM);
	level.objects[11] = GameObject(900,110,50,10, STYLE_PLATFORM);
	level.objects[12] = GameObject(1000,60,50,10, STYLE_PLATFORM);
	level.objects[13] = GameObject(900,10,50,10, STYLE_PLATFORM);
	level.objects[14] = GameObject(1000,-40,50,10, STYLE_PLATFORM);
	level.objects[15] = GameObject(1050,-100,10,340, STYLE_PLATFORM);
	//Flag at end of level
	level.objects[16] = GameObject(1020,-70,20,30, STYLE_FLAG);

	//moving death objects
	level.objects[17] = GameObject(200,0,20, 100, STYLE_DEATH, 100, 0);
	level.objects[18] = GameObject(965,-100,20, 100, STYLE_DEATH, 240, 0);

	//tree decoration
	level.objects[19] = GameObject(28,170, 4, 30, STYLE_TREE_TRUNK);
	level.objects[20] = GameObject(23,165, 16, 16, STYLE_TREE_LEAVES);

	//object count for loops
	level.objCount = 21;

	//create player with starting position
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
	level.offsetXMax = 740;
	level.offsetYMin = -100;
	level.offsetYMax = 0;
	level.offsetRange = 100;

	//initilize time variable to track moving objects
	level.loopTime = 0;
	level.loopTimeTotal = 6;

	//initlize level timing variables
	level.levelTime = 45;
	level.playTime = 0;

	//set points for completing level
	level.levelPoints = 100;
	level.levelPointsTimeMulti = 10;
	
	//return created level
	return level;
}