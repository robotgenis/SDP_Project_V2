#include "FEHLCD.h"
#include "GameObject.h"


void GameObject::drawObject(){
    LCD.SetFontColor(GREEN);
    LCD.FillRectangle(x, y, w, h);
}

void Player::drawPlayer(){
    LCD.SetFontColor(BLUE);
    LCD.FillRectangle(x, y, w, h);
}

void GameLevel::drawGameObjects(){
    for(int i = 0; i< objCount; i++){
        objects[i].drawObject()
    }
}