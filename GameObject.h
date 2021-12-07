#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

/*
*Define constant for screen size
*Authors: Brandon Y., Aadit S.
*/
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

/*
*Defined constants for style of objects in levels
*Authors: Brandon Y., Aadit S.
*/
#define STYLE_GRASS 1
#define STYLE_PLAYER 2
#define STYLE_BOX 3
#define STYLE_PLATFORM 4
#define STYLE_FLAG 5
#define STYLE_DEATH 6
#define STYLE_TREE_TRUNK 7
#define STYLE_TREE_LEAVES 8

/*
*Defined constants for returning status of level
*Authors: Brandon Y., Aadit S.
*/
#define STATE_NONE 0
#define STATE_DEATH 1
#define STATE_COMPLETE 2

/*
*GameObject object holds the position, size, style and movement variables for objects in the levels
*@param sx
    sx is the initial x position of the GameObject 
*@param sy 
    sx is the initial x position of the GameObject 
*@param x 
    x holds the x position of the GameObject
*@param y 
    y holds the y position of the GameObject
*@param w 
    w stores the width of the GameObject
*@param h 
    h stores the height of the GameObject
*@param style 
    style stores the type of item to draw and interact with 
*@param horizDelta 
    horizDelta stores the amount the object should move horizontally in one cycle 
*@param vertDelta 
    vertDelta stores the amount the object should move vertically in one cycle 
*Authors: Brandon Y., Aadit S.
*/
class GameObject{
    public:GameObject(int x1, int y1, int w1, int h1, int s, int vd, int hd){
            x = x1;
            y = y1;
            sx = x;
            sy = y;
            w = w1;
            h = h1;
            style = s;
            horizDelta = hd;
            vertDelta = vd;
        };
        GameObject(int x1, int y1, int w1, int h1, int s){
            x = x1;
            y = y1;
            sx = x;
            sy = y;
            w = w1;
            h = h1;
            style = s;
            horizDelta = 0;
            vertDelta = 0;
        };
        GameObject(){
            x = 0;
            y = 0;
            sx = x;
            sy = y;
            w = 0;
            h = 0;
            style = STYLE_GRASS;
            horizDelta = 0;
            vertDelta = 0;
        };
        void drawObject(int offsetX, int offsetY);
        int right();
        int left();
        int top();
        int bottom();
        void updateTimeDelta(float percentOfAnimation);
        int sx, sy, x, y, w, h, style, horizDelta, vertDelta;
};

/*
*Player object is extension of GameObject and holds more varaible with the movemnt of the character
*@param xVelocity
    xVelocity holds the max speed to move the player left and right
*@param yVelocity
    yVelocity holds the speed of the Player on the vertical axis
*@param jumpVelocity
    jumpvelocity holds the speed at which the player jumps off the ground
*@param accel 
    accel holds the amount to accelerate the object downward to apply gravity to the player
*Authors: Brandon Y., Aadit S.
*/
class Player: public GameObject{
    public:
        Player(int x1, int y1, int w1, int h1) : GameObject(x1, y1, w1, h1, STYLE_PLAYER){};
        Player():GameObject(){};
        
        int updateCollision(GameObject *obj);
        bool onGround(GameObject *obj);
        void updatePlayer(int xMouse, int yMouse, bool clicked, int offsetX, int offsetY, bool onGround, float changeTime);
        float xVelocity, yVelocity, jumpVelocity, accel;
    private:
};

/*
*GameLevel object holds all informaiton about level, each level is defined in it's own class
*@param objects[]
    objects array holds all game objects to interact with and to draw on screen
*@param player
    player holds the player object to be drawn and moved on screen
*@param objCount
    objCount holds a count of the number of objects in the objects array
*@param offsetX
    offsetX holds the offset value for the scene on the x axis
*@param offsetY
    offsetY holds the offset value for the scene on the y axis
*@param offsetXMin
    offsetXMin holds the mininum offset value for the x axis
*@param offsetXMax
    offsetXMax holds the maximum offset value for the x axis
*@param offsetYMin
    offsetYMin holds the mininum offset value for the y axis
*@param offsetYMax
    offsetYMax holds the maximum offset value for the y axis
*@param offsetRange
    offsetRange holds the range from the edge of the screen, used to move offset
*@param loopTime
    loopTime holds the current time in the animation cycle
*@param loopTimeTotal
    loopTimeTotal holds the length of time of one cycle of animation
*@param levelTime
    levelTime holds the countdown timer for time limit
*@param playTime
    playTime holds the count up timer for statistics
*@param levelPoints
    levelPoints holds the starting points value for winning a level
*@param levelPointsTimeMulti
    levelPointsTimeMulti holds the points mutiply for having time left when level complete 
*Authors: Brandon Y., Aadit S.
*/
class GameLevel{
    public:
        void drawGameObjects();
        int update(int xMouse, int yMouse, bool clicked, float changeTime);
        GameObject objects[30];
        Player player;
        int objCount = 0;
        int offsetX, offsetY;
        int offsetXMin, offsetXMax, offsetYMin, offsetYMax, offsetRange;
        float loopTime, loopTimeTotal, levelTime, playTime;
        int levelPoints, levelPointsTimeMulti;
    private:
        
};

#endif

