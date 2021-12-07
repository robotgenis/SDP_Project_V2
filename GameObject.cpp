#include "FEHLCD.h"
#include "GameObject.h"
#include "FEHUtility.h"

/*
*Function for GameObject
*void GameObject::drawObject(int offsetX, int offsetY)
*   Draws GameObject with offset from @param
*@param offsetX
*   The horizontal offset of the view
*@param offsetY
*   The vertical offset of the view
*Ex. 
*   drawObject(0,0); Draws a game object at (0, 0) if GameObject position is (0,0) 
*Authors: Brandon Y., Aadit S.
*/
void GameObject::drawObject(int offsetX, int offsetY){

    //apply offset values of view
    int xTemp = x - offsetX;
    int yTemp = y - offsetY;

    //ignore if off the screen on x axis
    if(xTemp + w < 0) return;
    if(xTemp > SCREEN_WIDTH) return;

    //ignore if off the screen on the y axis
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

    //extra variable for ceratin styles
    int x3, y3, x4, y4;
    int i;

    //draw depending on style
    switch(style){
        case STYLE_GRASS:
            //Green grass style
            LCD.SetFontColor(GREEN);
            LCD.FillRectangle(x1, y1, w1, h1);
            break;
        case STYLE_PLAYER:
            //Player style for player object
            LCD.SetFontColor(RED);
            LCD.FillRectangle(x1, y1, w1, h1);
            break;
        case STYLE_BOX:
            //Draw box style brown
            LCD.SetFontColor(0xc49845);
            LCD.FillRectangle(x1, y1, w1, h1);
            LCD.SetFontColor(0x8a692c);
            LCD.DrawLine(x1, y1, x2 - 1, y1);
            LCD.DrawLine(x2 - 1, y1, x2 - 1, y2 - 1);
            LCD.DrawLine(x2 - 1, y2 - 1, x1, y2 - 1);
            LCD.DrawLine(x1, y2 - 1, x1, y1);
            break;
        case STYLE_PLATFORM:
            //Draw gray platform style
            LCD.SetFontColor(0x8c8272);
            LCD.FillRectangle(x1, y1, w1, h1);
            LCD.SetFontColor(0xc2b5a1);
            LCD.DrawLine(x1, y1, x2-1, y1);
            LCD.DrawLine(x1, y1+1, x2-1, y1+1);
            break;
        case STYLE_FLAG:
            //draw flag style
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
            //draw death object ('spikes')
            //set four points position for the inner and outer rectangles
            x1 = xTemp;
            y1 = yTemp;
            x2 = xTemp + 3;
            y2 = yTemp + 3;
            x3 = xTemp + w - 3;
            y3 = yTemp + h - 3;
            x4 = xTemp + w - 1;
            y4 = yTemp + h - 1;
            
            //check make sure the first point is on the screen
            x1 = (x1 < 0) ? 0 : x1;
            y1 = (y1 < 0) ? 0 : y1;
            x1 = (x1 > SCREEN_WIDTH) ? SCREEN_WIDTH : x1;
            y1 = (y1 > SCREEN_HEIGHT) ? SCREEN_HEIGHT : y1;
            
            //check second point on the screen
            x2 = (x2 < 0) ? 0 : x2;
            y2 = (y2 < 0) ? 0 : y2;
            x2 = (x2 > SCREEN_WIDTH) ? SCREEN_WIDTH : x2;
            y2 = (y2 > SCREEN_HEIGHT) ? SCREEN_HEIGHT : y2;
            
            //check third point on the screen
            x3 = (x3 < 0) ? 0 : x3;
            y3 = (y3 < 0) ? 0 : y3;
            x3 = (x3 > SCREEN_WIDTH) ? SCREEN_WIDTH : x3;
            y3 = (y3 > SCREEN_HEIGHT) ? SCREEN_HEIGHT : y3;
            
            //check fourth point on the screen
            x4 = (x4 < 0) ? 0 : x4;
            y4 = (y4 < 0) ? 0 : y4;
            x4 = (x4 > SCREEN_WIDTH) ? SCREEN_WIDTH : x4;
            y4 = (y4 > SCREEN_HEIGHT) ? SCREEN_HEIGHT : y4;

            //set color to purple
            LCD.SetFontColor(0x7e00e6);
            
            //draw left spikes
            for(i = y2; i < y3; i += 3){
                LCD.DrawLine(x1, i, x2, i);
            }

            //draw right spikes
            for(i = y2; i < y3; i += 3){
                LCD.DrawLine(x3, i, x4, i);
            }

            //draw top spiks
            for(i = x2; i < x3; i += 3){
                LCD.DrawLine(i, y1, i, y2);
            }

            //draw bottom spikes
            for(i = x2; i < x3; i += 3){
                LCD.DrawLine(i, y3, i, y4);
            }

            //draw inner rectangle
            LCD.FillRectangle(x2, y2, x3 - x2, y3 - y2);
            break;
        case STYLE_TREE_LEAVES:
            //draw leaves with green faded color
            LCD.SetFontColor(0xc9e89e);
            LCD.FillRectangle(x1,y1,w1, h1);
            break;
        case STYLE_TREE_TRUNK:
            //draw tree trunk with faded brown color
            LCD.SetFontColor(0x9e8e52);
            LCD.FillRectangle(x1,y1,w1, h1);
            break;
    }
}

/*
*Function for GameObject
*int GameObject::right()
*   returns x position of right side of object
*Ex. 
*   if x value is 5 and w value is 10 then returns 15
*Authors: Brandon Y., Aadit S.
*/
int GameObject::right(){
    return x + w;
}

/*
*Function for GameObject
*int GameObject::left()
*   returns x position of left side of object
*Ex. 
*   if x value is 5 then returns 5
*Authors: Brandon Y., Aadit S.
*/
int GameObject::left(){
    return x;
}

/*
*Function for GameObject
*int GameObject::top()
*   returns y position of top side of object
*Ex. 
*   if y value is 5 then returns 5
*Authors: Brandon Y., Aadit S.
*/
int GameObject::top(){
    return y;
}

/*
*Function for GameObject
*int GameObject::bottom()
*   returns y position of bottom side of object
*Ex. 
*   if y value is 5 and h value is 10 then returns 15
*Authors: Brandon Y., Aadit S.
*/
int GameObject::bottom(){
    return y + h;
}

/*
*Function for GameObject
*void GameObject::updateTimeDelta(float percentOfAnimation)
*   moves object passed on percent of animation (0-2) (0-1 is moving towards end position, 1-2 is moving back to orginal position)
*@param percentOfAnimation
*   percent value of animation completion
*Ex. 
*   if percentOfAnimation is 1 the object will move to the end of animation position
*Authors: Brandon Y., Aadit S.
*/
void GameObject::updateTimeDelta(float percentOfAnimation){
    //adjust animation percent to 0 - 1
    if(percentOfAnimation > 1) percentOfAnimation = 2 - percentOfAnimation;

    //find offset from orginal position
    int xTimeDelta = percentOfAnimation * horizDelta;
    int yTimeDelta = percentOfAnimation * vertDelta;

    //set current position
    x = sx + xTimeDelta;
    y = sy + yTimeDelta;
}

/*
*Function for Player
*int Player::updateCollision(GameObject *obj)
*   check for collision and prevents overlapping
*@param obj
*   obj is another GameObject to check collision with
*Ex. 
*   if GameObject collides with floor the Player will stop and stay ontop
*Authors: Brandon Y., Aadit S.
*/
int Player::updateCollision(GameObject *obj){
    //calculate overlap values
    int l = left() - obj->right();
    int r = obj->left() - right();
    int t = top() - obj->bottom();
    int b = obj->top() - bottom();
    
    //check for level complete style
    if(obj->style == STYLE_FLAG){
        if(l <= 0 && r <= 0 && t <= 0 && b <= 0){
            //Level Complete
            return STATE_COMPLETE;
        }
    }
    //check for death style
    else if(obj->style == STYLE_DEATH){
        if(l <= 0 && r <= 0 && t <= 0 && b <= 0){
            //death of player
            return STATE_DEATH;
        }
    }else{
        //check for collision
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
                //force player donw into floor for moving platforms
                if(yVelocity >= 2){
                    yVelocity = 2;
                }
            }else{
                //top collision
                y = obj->bottom();
                if(yVelocity < 0){
                    //stop player vertical motion
                    yVelocity = 0;
                }
            }
        }
    }
    return STATE_NONE;
}

/*
*Function for Player
*bool Player::onGround(GameObject *obj)
*   check for collision on the bottom of the player
*@param obj
*   obj is another GameObject to check collision with
*Ex. 
*   if GameObject collides with floor return true
*Authors: Brandon Y., Aadit S.
*/
bool Player::onGround(GameObject *obj){
    //calculate overlap values
    int l = left() - obj->right();
    int r = obj->left() - right();
    int t = top() - obj->bottom();
    int b = obj->top() - bottom();

    //check for collision
    if(l <= 0 && r <= 0 && t <= 0 && b <= 0){
        //If object is colliding on bottom
        if(b >= t && b >= l && b >= r)
            return true;
    }
    return false;   
}

/*
*Function for Player
*void Player::updatePlayer(int xMouse, int yMouse, bool clicked, int offsetX, int offsetY, bool onGround, float changeTime)
*   update player motion from mouse input and time informaiton
*@param xMouse
*   xMouse is x position of the mouse
*@param yMouse
*   yMouse is the y position of the mouse
*@param clicked
*   clicked is wether the mouse has been clicked
*@param offsetX
*   offsetX holds the horizontal offset of the view
*@param offsetY
*   offsetY holds the vertical offset of the view
*@param onGround
*   onGround holds wether the player is on ground and can jump
*@param changeTime
*   changeTime holds the amount of time that has gone by in seconds
*Ex. 
*   if mouse is clicked above the player, the player jumps
*Authors: Brandon Y., Aadit S.
*/
void Player::updatePlayer(int xMouse, int yMouse, bool clicked, int offsetX, int offsetY, bool onGround, float changeTime){
    //find center of player
    int xCenter = x + w/2 - offsetX;
    int yCenter = y + h/2 - offsetY;

    //check for mouse being clicked
    if(clicked){
        //move in the positive x
        if(xMouse>xCenter){
            //check if exceding max speed
            if(xMouse>xCenter+xVelocity)
                x+=xVelocity;
            else 
                x = xMouse-w/2+offsetX;
        }
        //move in the negative x
        else if(xMouse<xCenter){
            //check if exceding max speed
            if(xMouse<xCenter-xVelocity)
                x-=xVelocity;
            else 
                x = xMouse-w/2+offsetX;
        }
        //check for jump
        if(yMouse<yCenter - 30){
            //make sure player is on ground
            if(onGround){
                //apply jump
                yVelocity = -jumpVelocity;
            }
        }
    }

    //update gravity physics
    yVelocity += accel * changeTime;
    y += yVelocity;
}

/*
*Function for Player
*void GameLevel::drawGameObjects()
*   draws all game objects and visual elements of the level
*Ex. 
*   draws player and objects
*Authors: Brandon Y., Aadit S.
*/
void GameLevel::drawGameObjects(){
    //draw all objects in the level
    for(int i = 0; i< objCount; i++){
        objects[i].drawObject(offsetX, offsetY);
    }
    //draw player ontop of all objects
    player.drawObject(offsetX, offsetY);

    //draw timer for level
    LCD.SetFontColor(GRAY);
    LCD.FillRectangle(0, 0, 30, 20);
    LCD.SetFontColor(YELLOW);
    int t = levelTime;
    LCD.WriteAt(t, 2, 2);

    //draw pause button
    LCD.SetFontColor(GRAY);
    LCD.DrawRectangle(305, 0, 15, 15);
    LCD.FillRectangle(305,0,15,15);
    LCD.SetFontColor(DARKGRAY);
    LCD.DrawHorizontalLine(6, 307, 314);
    LCD.DrawHorizontalLine(7, 307, 314);
    LCD.DrawLine(310, 3, 315, 6);
    LCD.DrawLine(315, 8, 310, 11);
}

/*
*Function for Player
*int GameLevel::update(int xMouse, int yMouse, bool clicked, float changeTime)
*   updates entire level collision, physics and controls
*@param xMouse
*   xMouse is x position of the mouse
*@param yMouse
*   yMouse is the y position of the mouse
*@param clicked
*   clicked is wether the mouse has been clicked
*@param changeTime
*   changeTime holds the amount of time that has gone by in seconds
*Ex. 
*   checks if player is onground and jumps if mouse is clicke above player
*Authors: Brandon Y., Aadit S.
*/
int GameLevel::update(int xMouse, int yMouse, bool clicked, float changeTime){
    //update timers
    loopTime += changeTime;
    levelTime -= changeTime;
    playTime += changeTime;

    //check if out of time
    if(levelTime <= 0){
        return STATE_DEATH;
    }

    //prevent overflow on time loop
    if(loopTime >= loopTimeTotal){
        loopTime = 0;
    }

    //calculate animation percetage
    float percentOfAnimation = loopTime / loopTimeTotal * 2.0;

    //Check for player on ground with each object
    bool onGround = false;
    for(int i = 0; i < objCount; i++){
        if(player.onGround(&objects[i])){
            onGround = true;
        }
    }

    //move objects that can move
    for(int i = 0; i < objCount; i++){
       objects[i].updateTimeDelta(percentOfAnimation);   
    }

    //make sure player is not moving up while onground
    if(player.yVelocity < 1){
        onGround = false;
    }

    // Update player movement
    player.updatePlayer(xMouse, yMouse, clicked, offsetX, offsetY, onGround, changeTime);

    //Collision loop between player and any object
    for(int i = 0; i < objCount; i++){
        //check for collision
        int s = player.updateCollision(&objects[i]);

        //level competetion and death check
        if(s == STATE_COMPLETE){
            return STATE_COMPLETE;
        }else if(s == STATE_DEATH){
            return STATE_DEATH;
        }
    }

    //update offset of window right side
    int right = SCREEN_WIDTH + offsetX - player.right();
    if(right < offsetRange){
        offsetX += offsetRange - right;
        if(offsetX > offsetXMax) offsetX = offsetXMax;
    }
    
    //update offset of window left side
    int left = player.left() - offsetX;
    if(left < offsetRange){
        offsetX -= offsetRange - left;
        if(offsetX < offsetXMin) offsetX = offsetXMin;
    }

    //update offset of window bottom side
    int bottom = SCREEN_HEIGHT + offsetY - player.bottom();
    if(bottom < offsetRange){
        offsetY += offsetRange - bottom;
        if(offsetY > offsetYMax) offsetY = offsetYMax;
    }

    //update offset of window top side
    int top = player.top() - offsetY;
    if(top < offsetRange){
        offsetY -= offsetRange - top;
        if(offsetY < offsetYMin) offsetY = offsetYMin;
    }

    //Check for death on bottom of world
    if(player.y > offsetYMax + SCREEN_HEIGHT){
        return STATE_DEATH;
    }

    //return default state
    return STATE_NONE;
}
