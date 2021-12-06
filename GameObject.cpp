#include "FEHLCD.h"
#include "GameObject.h"
#include "FEHUtility.h"


void GameObject::drawObject(int offsetX, int offsetY){

    int xTemp = x - offsetX;
    int yTemp = y - offsetY;

    if(xTemp + w < 0) return;
    if(xTemp > SCREEN_WIDTH) return;

    if(yTemp + h < 0) return;
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

    int x3, y3, x4, y4;
    int i;

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
            LCD.SetFontColor(0xc49845);
            LCD.FillRectangle(x1, y1, w1, h1);
            LCD.SetFontColor(0x8a692c);
            LCD.DrawLine(x1, y1, x2 - 1, y1);
            LCD.DrawLine(x2 - 1, y1, x2 - 1, y2 - 1);
            LCD.DrawLine(x2 - 1, y2 - 1, x1, y2 - 1);
            LCD.DrawLine(x1, y2 - 1, x1, y1);
            
            // LCD.DrawLine(x1, y1, x2 - 1, y2 - 6);
            // LCD.DrawLine(x1, y2 - 1, x2 - 1, y1 + 4);
            break;
        case STYLE_PLATFORM:
            LCD.SetFontColor(0x8c8272);
            LCD.FillRectangle(x1, y1, w1, h1);
            LCD.SetFontColor(0xc2b5a1);
            LCD.DrawLine(x1, y1, x2-1, y1);
            LCD.DrawLine(x1, y1+1, x2-1, y1+1);
            break;
        case STYLE_FLAG:
            LCD.SetFontColor(BLACK);
            if(xTemp + w <= SCREEN_WIDTH){
                LCD.DrawLine(xTemp + w, y1, xTemp + w, y2);
            }

            y3 = yTemp + 15;
            if(y3 >= y1){
                LCD.FillRectangle(x1, y1, w1, y3 - y1);
            }
            break;
        case STYLE_DEATH:
            x1 = xTemp;
            y1 = yTemp;
            x2 = xTemp + 3;
            y2 = yTemp + 3;
            x3 = xTemp + w - 3;
            y3 = yTemp + h - 3;
            x4 = xTemp + w - 1;
            y4 = yTemp + h - 1;
            
            x1 = (x1 < 0) ? 0 : x1;
            y1 = (y1 < 0) ? 0 : y1;
            x1 = (x1 > SCREEN_WIDTH) ? SCREEN_WIDTH : x1;
            y1 = (y1 > SCREEN_HEIGHT) ? SCREEN_HEIGHT : y1;
            
            x2 = (x2 < 0) ? 0 : x2;
            y2 = (y2 < 0) ? 0 : y2;
            x2 = (x2 > SCREEN_WIDTH) ? SCREEN_WIDTH : x2;
            y2 = (y2 > SCREEN_HEIGHT) ? SCREEN_HEIGHT : y2;
            
            x3 = (x3 < 0) ? 0 : x3;
            y3 = (y3 < 0) ? 0 : y3;
            x3 = (x3 > SCREEN_WIDTH) ? SCREEN_WIDTH : x3;
            y3 = (y3 > SCREEN_HEIGHT) ? SCREEN_HEIGHT : y3;
            
            x4 = (x4 < 0) ? 0 : x4;
            y4 = (y4 < 0) ? 0 : y4;
            x4 = (x4 > SCREEN_WIDTH) ? SCREEN_WIDTH : x4;
            y4 = (y4 > SCREEN_HEIGHT) ? SCREEN_HEIGHT : y4;

            LCD.SetFontColor(0x7e00e6);
            
            for(i = y2; i < y3; i += 3){
                LCD.DrawLine(x1, i, x2, i);
            }

            for(i = y2; i < y3; i += 3){
                LCD.DrawLine(x3, i, x4, i);
            }

            for(i = x2; i < x3; i += 3){
                LCD.DrawLine(i, y1, i, y2);
            }

            for(i = x2; i < x3; i += 3){
                LCD.DrawLine(i, y3, i, y4);
            }

            LCD.FillRectangle(x2, y2, x3 - x2, y3 - y2);
            break;
        case STYLE_TREE_LEAVES:
            LCD.SetFontColor(0xc9e89e);
            LCD.FillRectangle(x1,y1,w1, h1);
            break;
        case STYLE_TREE_TRUNK:
            LCD.SetFontColor(0x9e8e52);
            LCD.FillRectangle(x1,y1,w1, h1);
            break;
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


void GameObject::updateTimeDelta(float percentOfAnimation){
    if(percentOfAnimation > 1) percentOfAnimation = 2 - percentOfAnimation;

    int xTimeDelta = percentOfAnimation * horizDelta;
    int yTimeDelta = percentOfAnimation * vertDelta;

    x = sx + xTimeDelta;
    y = sy + yTimeDelta;
}


int Player::updateCollision(GameObject *obj){
    int l = left() - obj->right();
    int r = obj->left() - right();
    int t = top() - obj->bottom();
    int b = obj->top() - bottom();
    
    if(obj->style == STYLE_FLAG){
        if(l <= 0 && r <= 0 && t <= 0 && b <= 0){
            //Level Complete
            return STATE_COMPLETE;
        }
    }
    else if(obj->style == STYLE_DEATH){
        if(l <= 0 && r <= 0 && t <= 0 && b <= 0){
            //Level Complete
            return STATE_DEATH;
        }
    }else{
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
                if(yVelocity >= 2){
                    yVelocity = 2;
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
    return STATE_NONE;
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

    LCD.SetFontColor(GRAY);
    LCD.FillRectangle(0, 0, 30, 20);
    LCD.SetFontColor(YELLOW);
    int t = levelTime;
    LCD.WriteAt(t, 2, 2);

    LCD.SetFontColor(GRAY);
    LCD.DrawRectangle(305, 0, 15, 15);
    LCD.FillRectangle(305,0,15,15);
    LCD.SetFontColor(DARKGRAY);
    LCD.DrawHorizontalLine(6, 307, 314);
    LCD.DrawHorizontalLine(7, 307, 314);
    LCD.DrawLine(310, 3, 315, 6);
    LCD.DrawLine(315, 8, 310, 11);
}

int GameLevel::update(int xMouse, int yMouse, bool clicked, float changeTime){
    //move moving targets
    loopTime += changeTime;
    levelTime -= changeTime;
    playTime += changeTime;

    if(levelTime <= 0){
        return STATE_DEATH;
    }

    if(loopTime >= loopTimeTotal){
        loopTime = 0;
    }

    float percentOfAnimation = loopTime / loopTimeTotal * 2.0;

    //Check for player on ground with each object
    bool onGround = false;
    for(int i = 0; i < objCount; i++){
        if(player.onGround(&objects[i])){
            onGround = true;
        }
    }

    for(int i = 0; i < objCount; i++){
       objects[i].updateTimeDelta(percentOfAnimation);   
    }

    if(player.yVelocity < 1){
        onGround = false;
    }

    // Update player movement
    player.updatePlayer(xMouse, yMouse, clicked, offsetX, offsetY, onGround, changeTime);

    //Collision loop between player and any object
    for(int i = 0; i < objCount; i++){
        int s = player.updateCollision(&objects[i]);

        if(s == STATE_COMPLETE){
            return STATE_COMPLETE;
        }else if(s == STATE_DEATH){
            return STATE_DEATH;
        }
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

    if(player.y > offsetYMax + SCREEN_HEIGHT){
        return STATE_DEATH;
    }
    return STATE_NONE;
}
