#ifndef LEVEL1_H
#define LEVEL1_H

#include "GameObject.h"

namespace LEVEL1{
	GameLevel createLevel(){
		GameLevel test;

		test.objects[0] = GameObject(0,0,50,50);
		test.objCount = 1;

		return test;
	}
};

#endif
