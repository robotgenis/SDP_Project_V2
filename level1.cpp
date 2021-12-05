#include "level1.h"
#include "GameObject.h"
#include "FEHUtility.h"

// #define gravity 3

GameLevel LEVEL1::createLevel(){
	GameLevel level;

	
	level.objects[0] = GameObject(0,200,500,40, STYLE_GRASS);
	level.objects[1] = GameObject(150,150,10,50, STYLE_GRASS);
	level.objects[2] = GameObject(360,160,40,10, STYLE_GRASS);
	level.objects[3] = GameObject(300,120,40,10, STYLE_GRASS);
	level.objects[4] = GameObject(400,100,100,100, STYLE_GRASS);
	//Open floor
	level.objects[5] = GameObject(560,100,40,10, STYLE_GRASS);
	level.objects[6] = GameObject(660,100,40,10, STYLE_GRASS);
	level.objects[7] = GameObject(760,100,100,140, STYLE_GRASS);
	//Third part
	level.objects[8] = GameObject(890,-100,10,290, STYLE_GRASS);
	level.objects[9] = GameObject(860,210,90,30, STYLE_GRASS);
	level.objects[10] = GameObject(1000,160,50,10, STYLE_GRASS);
	level.objects[11] = GameObject(900,110,50,10, STYLE_GRASS);
	level.objects[12] = GameObject(1000,60,50,10, STYLE_GRASS);
	level.objects[13] = GameObject(900,10,50,10, STYLE_GRASS);
	level.objects[14] = GameObject(1000,-40,50,10, STYLE_GRASS);
	level.objects[15] = GameObject(1050,-100,10,340, STYLE_GRASS);
	level.objCount = 16;

	level.player = Player(20,180, 20, 20);

	level.player.xVelocity = 3;
	level.player.jumpVelocity = 8;
	level.player.yVelocity = 0;
	level.player.accel = 15;

	level.offsetX = 0;
	level.offsetY = 0;

	level.offsetXMin = 0;
	level.offsetXMax = 740;
	level.offsetYMin = -100;
	level.offsetYMax = 0;
	level.offsetRange = 100;
	
	return level;
}