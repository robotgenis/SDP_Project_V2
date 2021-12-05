#include "FEHLCD.h"
#include "GameObject.h"
#include "FEHUtility.h"


void GameObject::drawObject(int offsetX, int offsetY){

    
    int xTemp = x - offsetX;
    int yTemp = y - offsetY;

    if(xTemp + w < 0) return;
    if(xTemp > SCREEN_WIDTH) return;

    if(yTemp+h < 0) return;
    if(yTemp > SCREEN_HEIGHT) return;

    //Start position
    int x1 = (xTemp < 0) ? 0 : xTemp;
    int y1 = (yTemp < 0) ? 0 : yTemp;

    //End position
    int x2 = (xTemp + w > SCREEN_WIDTH) ? SCREEN_WIDTH : xTemp + w;
    int y2 = (yTemp + h > SCREEN_HEIGHT) ? SCREEN_HEIGHT : yTemp + h;

    //With and height
    int w1 = x2 - x1;
    int h1 = y2 - y1;

    switch(style){
        case STYLE_GRASS:
            LCD.SetFontColor(GREEN);
            LCD.FillRectangle(x1, y1, w1, h1);
            break;
        case STYLE_PLAYER:
            LCD.SetFontColor(RED);
            LCD.FillRectangle(x1, y1, w1, h1);
            break;
        case STYLE_BOX:
            LCD.SetFontColor(LIGHTGRAY);
            LCD.FillRectangle(x1, y1, w1, h1);
            LCD.SetFontColor(DARKGRAY);
            LCD.DrawLine(x1, y1, x2, y1);
            LCD.DrawLine(x2, y1, x2, y2);
            LCD.DrawLine(x2, y2, x1, y2);
            LCD.DrawLine(x1, y2, x2, y1);
    }

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
        if(b >= t && b >= l && b >= r)
            return true;
    }
     return false;   
}

void Player::updatePlayer(int xMouse, int yMouse, bool clicked, int offsetX, int offsetY, bool onGround, float changeTime){
    //If user clicked right of position

    int xCenter = x + w/2 - offsetX;
    int yCenter = y + h/2 - offsetY;

    if(clicked){
        if(xMouse>xCenter){
            if(xMouse>xCenter+xVelocity)
                x+=xVelocity;
            else 
                x = xMouse-w/2+offsetX;
        }
        //If User clicked left of position
        else if(xMouse<xCenter){
            if(xMouse<xCenter-xVelocity)
                x-=xVelocity;
            else 
                x = xMouse-w/2+offsetX;
        }
    
        if(yMouse<yCenter - 30){
            if(onGround){
                yVelocity = -jumpVelocity;
            }
        }
    }


    yVelocity += accel * changeTime;
    y += yVelocity;
}

void GameLevel::drawGameObjects(){
    for(int i = 0; i< objCount; i++){
        objects[i].drawObject(offsetX, offsetY);
    }
    player.drawObject(offsetX, offsetY);
}

void GameLevel::update(int xMouse, int yMouse, bool clicked, float changeTime){
    //Check for player on ground with each object
    bool onGround = false;
    for(int i = 0; i < objCount; i++){
        if(player.onGround(&objects[i])){
            onGround = true;
        }
    }
    if(player.yVelocity != 0){
        onGround = false;
    }

    // Update player movement
    player.updatePlayer(xMouse, yMouse, clicked, offsetX, offsetY, onGround, changeTime);

    //Collision loop between player and any object
    for(int i = 0; i < objCount; i++){
        player.updateCollision(&objects[i]);
    }

    //update offset of window
    int right = SCREEN_WIDTH + offsetX - player.right();
    if(right < offsetRange){
        offsetX += offsetRange - right;
        if(offsetX > offsetXMax) offsetX = offsetXMax;
    }
    int left = player.left() - offsetX;
    if(left < offsetRange){
        offsetX -= offsetRange - left;
        if(offsetX < offsetXMin) offsetX = offsetXMin;
    }

    int bottom = SCREEN_HEIGHT + offsetY - player.bottom();
    if(bottom < offsetRange){
        offsetY += offsetRange - bottom;
        if(offsetY > offsetYMax) offsetY = offsetYMax;
    }
    int top = player.top() - offsetY;
    if(top < offsetRange){
        offsetY -= offsetRange - top;
        if(offsetY < offsetYMin) offsetY = offsetYMin;
    }
}
