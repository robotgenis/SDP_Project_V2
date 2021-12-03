#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#define COLLIDE_NONE 0
#define COLLIDE_RIGHT 1
#define COLLIDE_BOTTOM 2
#define COLLIDE_LEFT 3
#define COLLIDE_TOP 4

class GameObject{
    public:
        GameObject(int x1, int y1, int w1, int h1){
            x = x1;
            y = y1;
            w = w1;
            h = h1;
        };
        GameObject(){
            x = 0;
            y = 0;
            w = 0;
            h = 0;
        };
        void drawObject();
        int right();
        int left();
        int top();
        int bottom();
        int x, y, w, h;
    private:
        
};

class Player: public GameObject{
    public:
        Player(int x1, int y1, int w1, int h1) : GameObject(x1, y1, w1, h1){};
        Player():GameObject(){};
        
        void updateCollision(GameObject *obj);
        bool onGround(GameObject *obj);
        void drawPlayer();
        void updatePlayer(int xMouse, int yMouse, bool clicked, bool onGround, float changeTime);
        float xVelocity, yVelocity, jumpVelocity, accel;
    private:
};

class GameLevel{
    public:
        void drawGameObjects();
        void update(int xMouse, int yMouse, bool clicked, float changeTime);
        GameObject objects[20];
        Player player;
        int objCount = 0;
    private:
        
};

#endif

