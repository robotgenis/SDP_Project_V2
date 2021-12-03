#include "FEHLCD.h"
#include "GameObject.h"
#include "FEHUtility.h"


void GameObject::drawObject(){
    LCD.SetFontColor(GREEN);
    LCD.FillRectangle(x, y, w, h);
}

int GameObject::right(){
    return x + w;
}

int GameObject::left(){
    return x;
}

int GameObject::top(){
    return y;
}

int GameObject::bottom(){
    return y + h;
}

void Player::updateCollision(GameObject *obj){
    int l = left() - obj->right();
    int r = obj->left() - right();
    int t = top() - obj->bottom();
    int b = obj->top() - bottom();

    if(l <= 0 && r <= 0 && t <= 0 && b <= 0){
        if(l >= r && l >= t && l >= b){
            //left collision
            x = obj->right();
        }else if(r >= b && r >= t){
            //right collision
            x = obj->left() - w;
        }else if(b >= t){
            // bottom collision
            y = obj->top() - h;
            if(yVelocity > 0){
                yVelocity = 0;
            }
        }else{
            //top collision
            y = obj->bottom();
            if(yVelocity < 0){
                yVelocity = 0;
            }
        }
    }
}

bool Player::onGround(GameObject *obj){
    int l = left() - obj->right();
    int r = obj->left() - right();
    int t = top() - obj->bottom();
    int b = obj->top() - bottom();

    if(l <= 0 && r <= 0 && t <= 0 && b <= 0){
        //If object is colliding on bottom
        if(b >= t)
            return true;
    }
     return false;   
}

void Player::drawPlayer(){
    LCD.SetFontColor(BLUE);
    LCD.FillRectangle(x, y, w, h);
}
void Player::updatePlayer(int xMouse, int yMouse, bool clicked, bool onGround, float changeTime){
    //If user clicked right of position
    if(clicked){
        if(xMouse>right()){
            if(xMouse>right()+xVelocity)
                x+=xVelocity;
            else 
                x = xMouse-w;
        }
        //If User clicked left of position
        else if(xMouse<x){
            if(xMouse<x-xVelocity)
                x-=xVelocity;
            else 
                x = xMouse;
        }
    
        if(yMouse<y - 40){
            if(onGround){
                yVelocity = -jumpVelocity;
            }
        }
    }

    y += yVelocity;
    yVelocity += accel * changeTime;
}

void GameLevel::drawGameObjects(){
    for(int i = 0; i< objCount; i++){
        objects[i].drawObject();
    }
    player.drawPlayer();
}

void GameLevel::update(int xMouse, int yMouse, bool clicked, float changeTime){
    
    bool onGround = false;
    for(int i = 0; i < objCount; i++){
        if(player.onGround(&objects[i])){
            onGround = true;
        }
    }

    // Update player
    player.updatePlayer(xMouse, yMouse, clicked, onGround, changeTime);

    //Collision loop
    for(int i = 0; i < objCount; i++){
        player.updateCollision(&objects[i]);
    }
}
