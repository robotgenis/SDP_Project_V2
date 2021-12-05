#include "FEHLCD.h"
#include "level1.h"
#include "GameObject.h"
#include "level1.h"
#include "FEHUtility.h"

#define LEVEL_MAIN_MENU 1
#define LEVEL_LEVEL_SELECT 2
#define LEVEL_DISPLAY_STATS 3
#define LEVEL_DIRECTIONS 4
#define LEVEL_CREDITS 5
#define LEVEL_1 6
#define LEVEL_2 7
#define LEVEL_EXIT 8
#define LEVEL_DEATH_1 9
#define LEVEL_COMPLETE_1 10
class Levels{
    public:
        void draw();
        void update(int x, int y, bool clicked);
        void setLevel(int l);
        GameLevel currentLevel;
        int level;
        float prevTime;
        int Level1_Deaths, Level1_Points;
        bool Level1_Completed = false;
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

    levels.prevTime = TimeNow();

    levels.setLevel(LEVEL_MAIN_MENU);
    levels.draw();
    
    while(levels.level != LEVEL_EXIT) {
        Sleep(0.01);

        clicked = LCD.Touch(&x, &y);
        
        levels.update(x, y, clicked);
        
        //LCD.Update();

        if(clicked){
            if(levels.level == LEVEL_MAIN_MENU ||
                levels.level == LEVEL_MAIN_MENU ||
                levels.level == LEVEL_LEVEL_SELECT ||
                levels.level == LEVEL_DISPLAY_STATS ||
                levels.level == LEVEL_DIRECTIONS ||
                levels.level == LEVEL_CREDITS
            )
                while(LCD.Touch(&x, &y)){};
        }
    }


    return 0;
}

//Funciton for Menu class
void Levels::draw(){
    int x,y;
    switch(level){
        case LEVEL_MAIN_MENU: 
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            //Start Button
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(5, 5, 140, 50);
            LCD.WriteAt("Game Start" , 10, 25);
            //Stats Button
            LCD.SetFontColor(YELLOW);
            LCD.DrawRectangle(175, 5, 140, 50);
            LCD.WriteAt("Display", 195, 10);
            LCD.WriteAt("Statistics", 180, 30);
            //Exit Button
            LCD.SetFontColor(RED);
            LCD.DrawRectangle(5, 70, 140, 50);
            LCD.WriteAt("Credits", 45, 90);
            //Directions Button
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(175, 70, 140, 50);
            LCD.WriteAt("Directions", 185, 90);
            
            break;
        case LEVEL_LEVEL_SELECT: 
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.WriteAt("Play Game here", 0, 0);
            LCD.DrawRectangle(80, 60, 160, 50);
            LCD.WriteAt("Level 1", 100, 800);
            LCD.DrawRectangle(80, 120, 160, 50);
            LCD.WriteAt("Level 2", 100, 140);
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(80, 180, 160, 50);
            LCD.WriteAt("Main Menu", 100, 200);
            break;
        case LEVEL_DISPLAY_STATS:
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.WriteAt("Wins: 0", 100, 50);
            LCD.WriteAt("Deaths: 0", 100, 100);
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 130, 160, 50);
            LCD.WriteAt("Main Menu", 120, 150);
            break;
        case LEVEL_CREDITS:
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.WriteAt("Created By: ", 10, 180);
            LCD.WriteAt("AADIT S. & BRANDON Y.", 10, 200);
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 100, 160, 50);
            LCD.WriteAt("Main Menu", 120, 120);
            break;
        case LEVEL_DIRECTIONS:
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.WriteAt("Directions", 0, 0);
            LCD.WriteAt("The Goal is to reach the", 0, 20);
            LCD.WriteAt("flag at the end of each", 0, 40);
            LCD.WriteAt("level.", 0, 60);
            LCD.WriteAt("To Move, touch where you", 0, 80);
            LCD.WriteAt("want the player to move. ", 0, 100);
            LCD.WriteAt("To Jump, touch above the", 0, 120);
            LCD.WriteAt("player. ", 0, 140);
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 180, 160, 50);
            LCD.WriteAt("Main Menu", 120, 210);
            break;
        case LEVEL_1: 
            LCD.SetBackgroundColor(LIGHTBLUE);
            LCD.Clear();
            LCD.WriteAt("Welcome to Level 1", 70, 60);
            Sleep(0.5);
            currentLevel = LEVEL1::createLevel();
            prevTime = TimeNow();

            break;
        case LEVEL_2: 
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.WriteAt("Welcome to Level 2", 80, 60);
            break;

        case LEVEL_DEATH_1: 
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();

            LCD.SetFontColor(RED);
            LCD.WriteAt("YOU DIED", 120, 10);
            Level1_Deaths++;
            LCD.WriteAt("Deaths: ", 130, 30);
            LCD.WriteAt(Level1_Deaths, 200, 30);
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 100, 160, 50);
            LCD.WriteAt("Main Menu", 120, 120);
             LCD.DrawRectangle(100, 160, 160, 50);
            LCD.WriteAt("Respawn", 120, 180);
            while(LCD.Touch(&x, &y)){};
            break;
        case LEVEL_COMPLETE_1:
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 160, 160, 50);
            LCD.WriteAt("Main Menu", 120, 180);
            if(!Level1_Completed){
                Level1_Completed = true;
                Level1_Points +=1000;
            }
            
            LCD.WriteAt("Points:", 120, 50);
            LCD.WriteAt(Level1_Points, 210, 50);


            break;
    }
    
}


void Levels::update(int x, int y, bool clicked){
    float t = 0;
    int state = STATE_NONE;
    switch(level){
        case LEVEL_MAIN_MENU:
            if(clicked){
                //If user clicks button at x:(100,200) and y:(100,200) game start
                if(x>5 && x<145 && y>5 && y<55){
                    setLevel(LEVEL_LEVEL_SELECT);
                }
                if(x>175 && x<315 && y>5 && y<55){
                    setLevel(LEVEL_DISPLAY_STATS);
                }
                if(x>5 && x<145 && y>70 && y<120){
                    setLevel(LEVEL_CREDITS);
                    
                }
                if(x>175 && x<315 && y>70 && y<120){
                    setLevel(LEVEL_DIRECTIONS);
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
                else if(x>80 && x<240 && y>180 && y<230){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;
        case LEVEL_DISPLAY_STATS:
            if(clicked){
                if(x>100 && x<260 && y>130 && y<180){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;
        case LEVEL_CREDITS:
            if(clicked){
                if(x>100 && x<260 && y>100 && y<150){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;
        case LEVEL_DIRECTIONS:
            if(clicked){
                if(x>100 && x<260 && y>180 && y<230){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;
        case LEVEL_1:
            t = TimeNow();
            LCD.Clear();
            // LCD.SetFontColor(0x9e8e52);
            // LCD.FillRectangle(28,170,4, 30);
            // LCD.SetFontColor(0xc9e89e);
            // LCD.FillCircle(30,170,5);
            
            // LCD.SetFontColor(0x9e8e52);
            // LCD.FillRectangle(43,170,4, 30);
            // LCD.SetFontColor(0xc9e89e);
            // LCD.FillCircle(45,170,5);
            state = currentLevel.update(x, y, clicked, t - prevTime);
            if(state == STATE_DEATH){
                setLevel(LEVEL_DEATH_1);
            }else if(state == STATE_COMPLETE){
                setLevel(LEVEL_COMPLETE_1);
            }else{
                currentLevel.drawGameObjects();
            }

            prevTime = t;
            break;
        case LEVEL_DEATH_1:
            if(clicked){
                if(x>100 && x<260 && y>100 && y<150){
                    setLevel(LEVEL_MAIN_MENU);
                }
                else if(x>100 && x<260 && y>160 && y<210){
                    setLevel(LEVEL_1);
                }
            }
            break;  
        case LEVEL_COMPLETE_1:
            if(clicked){
                if(x>100 && x<260 && y>160 && y<210){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;  
          
    }
}

void Levels::setLevel(int l){
    level = l;
    draw();
}
