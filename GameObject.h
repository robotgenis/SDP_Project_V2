#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#define COLLIDE_NONE 0
#define COLLIDE_RIGHT 1
#define COLLIDE_BOTTOM 2
#define COLLIDE_LEFT 3
#define COLLIDE_TOP 4

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define STYLE_GRASS 1
#define STYLE_PLAYER 2
#define STYLE_BOX 3
#define STYLE_PLATFORM 4
#define STYLE_FLAG 5

#define STATE_NONE 0
#define STATE_DEATH 1
#define STATE_COMPLETE 2

class GameObject{
    public:
        GameObject(int x1, int y1, int w1, int h1, int s){
            x = x1;
            y = y1;
            w = w1;
            h = h1;
            style = s;
        };
        GameObject(){
            x = 0;
            y = 0;
            w = 0;
            h = 0;
            style = STYLE_GRASS;
        };
        void drawObject(int offsetX, int offsetY);
        int right();
        int left();
        int top();
        int bottom();
        int x, y, w, h, style;
    private:
        
};

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

class GameLevel{
    public:
        void drawGameObjects();
        int update(int xMouse, int yMouse, bool clicked, float changeTime);
        GameObject objects[20];
        Player player;
        int objCount = 0;
        int offsetX, offsetY;
        int offsetXMin, offsetXMax, offsetYMin, offsetYMax, offsetRange;
    private:
        
};

#endif

