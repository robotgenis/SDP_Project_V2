#include "level1.h"
#include "GameObject.h"
#include "FEHUtility.h"

// #define gravity 3

GameLevel LEVEL1::createLevel(){
	GameLevel level;

	level.objects[0] = GameObject(0,200,100,40);
	level.objects[1] = GameObject(50,150,50,10);
	level.objects[2] = GameObject(0,150,10,50);
	level.objects[3] = GameObject(200,150,10,50);
	level.objCount = 4;

	level.player = Player(20,180, 20, 20);

	
	level.player.xVelocity = 2;
	level.player.jumpVelocity = 5;
	level.player.yVelocity = 0;
	level.player.accel = 5;
	
	return level;
}