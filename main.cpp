#include "FEHLCD.h"
#include "level1.h"
#include "GameObject.h"
#include "level1.h"
#include "level2.h"
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
#define LEVEL_COMPLETE 10
#define LEVEL_DEATH_2 11

class Levels{
    public:
        void draw();
        void update(int x, int y, bool clicked);
        void setLevel(int l);
        GameLevel currentLevel;
        int level;
        float prevTime;
        int points, deaths;
        float totalPlayTime;
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
            LCD.WriteAt("Credits", 35, 90);
            //Directions Button
            LCD.SetFontColor(WHITE);
            LCD.DrawRectangle(175, 70, 140, 50);
            LCD.WriteAt("Directions", 185, 90);
            
            break;
        case LEVEL_LEVEL_SELECT: 
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.WriteAt("Level Select", 5, 5);
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
            LCD.WriteAt("Points:", 50, 50);
            LCD.WriteAt(points, 150, 50);
            LCD.WriteAt("Deaths:", 50, 65);
            LCD.WriteAt(deaths, 150, 65);
            LCD.WriteAt("Time Played:", 50, 80);
            LCD.WriteAt(totalPlayTime, 200, 80);
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 130, 160, 50);
            LCD.WriteAt("Main Menu", 120, 130);
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
            LCD.WriteAt("Main Menu", 130, 200);
            break;
        case LEVEL_1: 
            LCD.SetBackgroundColor(LIGHTBLUE);
            LCD.Clear();
            LCD.WriteAt("Welcome to Level 1", 40, 60);
            Sleep(0.5);
            currentLevel = LEVEL1::createLevel();
            prevTime = TimeNow();

            break;
        case LEVEL_2: 
            LCD.SetBackgroundColor(LIGHTGRAY);
            LCD.Clear();
            LCD.WriteAt("Welcome to Level 2", 40, 60);
            Sleep(0.5);
            currentLevel = LEVEL2::createLevel();
            prevTime = TimeNow();
            break;

        case LEVEL_DEATH_1: 
            deaths += 1;
            totalPlayTime += currentLevel.playTime;
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();

            LCD.SetFontColor(RED);
            LCD.WriteAt("YOU DIED", 120, 10);
            LCD.WriteAt("Deaths: ", 100, 30);
            LCD.WriteAt(deaths, 200, 30);
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 100, 160, 50);
            LCD.WriteAt("Main Menu", 120, 120);
             LCD.DrawRectangle(100, 160, 160, 50);
            LCD.WriteAt("Respawn", 120, 180);
            while(LCD.Touch(&x, &y)){};
            break;
        case LEVEL_COMPLETE:
            points += (int)(currentLevel.levelPoints + currentLevel.levelPointsTimeMulti * currentLevel.levelTime);
            totalPlayTime = currentLevel.playTime;

            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 160, 160, 50);
            LCD.WriteAt("Main Menu", 120, 180);
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("Points Earned:", 60, 50);
            LCD.WriteAt((int)(currentLevel.levelPoints + currentLevel.levelPointsTimeMulti * currentLevel.levelTime), 250, 50);
            break;
        case LEVEL_DEATH_2:
            deaths += 1;
            totalPlayTime += currentLevel.playTime;
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();

            LCD.SetFontColor(RED);
            LCD.WriteAt("YOU DIED", 120, 10);
            LCD.WriteAt("Deaths: ", 100, 30);
            LCD.WriteAt(deaths, 200, 30);
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 100, 160, 50);
            LCD.WriteAt("Main Menu", 120, 120);
            LCD.DrawRectangle(100, 160, 160, 50);
            LCD.WriteAt("Respawn", 120, 180);
            while(LCD.Touch(&x, &y)){};
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
            state = currentLevel.update(x, y, clicked, t - prevTime);
            if(state == STATE_DEATH){
                setLevel(LEVEL_DEATH_1);
            }else if(state == STATE_COMPLETE){
                setLevel(LEVEL_COMPLETE);
            }else{
                currentLevel.drawGameObjects();
            }
            if(clicked){
                if(x>305 && x<320 && y>0 && y<15){
                    totalPlayTime += currentLevel.playTime;
                    setLevel(LEVEL_MAIN_MENU);
                }
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
        case LEVEL_DEATH_2:
            if(clicked){
                if(x>100 && x<260 && y>100 && y<150){
                    setLevel(LEVEL_MAIN_MENU);
                }
                else if(x>100 && x<260 && y>160 && y<210){
                    setLevel(LEVEL_2);
                }
            }
            break;  
        case LEVEL_COMPLETE:
            if(clicked){
                if(x>100 && x<260 && y>160 && y<210){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;  
        case LEVEL_2:
            t = TimeNow();
            LCD.Clear();
            state = currentLevel.update(x, y, clicked, t - prevTime);
            if(state == STATE_DEATH){
                setLevel(LEVEL_DEATH_2);
            }else if(state == STATE_COMPLETE){
                setLevel(LEVEL_COMPLETE);
            }else{
                currentLevel.drawGameObjects();
            }
            if(clicked){
                if(x>305 && x<320 && y>0 && y<15){
                    totalPlayTime += currentLevel.playTime;
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            prevTime = t;
            break;
    }
}

void Levels::setLevel(int l){
    level = l;
    draw();
}
