#include "level1.h"
#include "GameObject.h"


GameLevel LEVEL1::createLevel(){
	GameLevel level;

	level.objects[0] = GameObject(0,200,100,40);
	level.objects[1] = GameObject(50,150,50,10);
	level.objCount = 2;

	level.player = Player(20,180, 20, 20);

	return level;
}