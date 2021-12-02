#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

class GameObject{
    public:
        GameObject(int x1, int y1, int w1, int h1){
            x = x1;
            y = y1;
            w = w1;
            h = h1;
        };
        void drawObject();
        //void collision(GameObject *obj);
        int x, y, w, h;
    private:
        
};

class Player: public GameObject{
    public:
        Player(int x1, int y1, int w1, int h1) : GameObject(x1, y1, w1, h1){};
        void drawPlayer();
        float xVelocity, yVelocity;
    private:
};

class GameLevel{
    public:
        GameLevel();
        void drawGameObjects();
        GameObject objects[20];
        int objCount = 0;
    private:
        
};

#endif

