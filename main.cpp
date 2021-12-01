#include "FEHLCD.h"


#define LEVEL_MAIN_MENU 1
#define LEVEL_LEVEL_SELECT 2
#define LEVEL_1 3
#define LEVEL_2 4


class Levels{
    public:
        void draw();
        void update(int x, int y, bool clicked);
        void setLevel(int l);
        bool running = true;
    private:
        int level;
};

/*
 * Entry point to the application
 */
int main() {
    //Initilize variables
    int x, y;
    bool clicked;

    //define menu object
    Levels levels;

    levels.setLevel(LEVEL_MAIN_MENU);
    levels.draw();

    while(levels.running) {
        clicked = LCD.Touch(&x, &y);
        
        levels.update(x, y, clicked);
        
        LCD.Update();

        if(clicked){
            while(LCD.Touch(&x, &y)){};
        }
    }

    return 0;
}

//Funciton for Menu class
void Levels::draw(){
    switch(level){
        case LEVEL_MAIN_MENU: 
            LCD.SetBackgroundColor(BLACK);
            LCD.DrawRectangle(80, 60, 160, 50);
            LCD.WriteAt("Game Start", 100, 80);
            LCD.DrawRectangle(80, 120, 160, 50);
            LCD.WriteAt("Exit", 110, 140);
            break;
        case LEVEL_LEVEL_SELECT: 
            LCD.SetBackgroundColor(BLACK);
            LCD.DrawRectangle(80, 60, 160, 50);
            LCD.WriteAt("Level 1", 100, 800);
            LCD.DrawRectangle(80, 120, 160, 50);
            LCD.WriteAt("Level 2", 100, 140);
            break;
        case LEVEL_1: 
            LCD.SetBackgroundColor(BLACK);
            LCD.WriteAt("Welcome to Level 1", 80, 60);
            break;
        case LEVEL_2: 
            LCD.SetBackgroundColor(BLACK);
            LCD.WriteAt("Welcome to Level 2", 80, 60);
            break;
    }
    
}


void Levels::update(int x, int y, bool clicked){
    switch(level){
        case LEVEL_MAIN_MENU:
            if(clicked){
                //If user clicks button at x:(100,200) and y:(100,200) game start
                if(x>80 && x<240 && y>60 && y<110){
                    setLevel(LEVEL_LEVEL_SELECT);
                }
                if(x>80 && x<240 && y>120 && y<170){
                    running = false;
                }
            }
            break;
        case LEVEL_LEVEL_SELECT:
            if(clicked){
                if(x>80 && x<240 && y>60 && y<110){
                    setLevel(LEVEL_1);
                }
                else if(x>80 && x<240 && y>120 && y<170){
                    setLevel(LEVEL_2);
                }
            }
            break;
    }
    
}



void Levels::setLevel(int l){
    level = l;

    LCD.Clear();
    draw();
}

