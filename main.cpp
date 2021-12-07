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

/*
*Levels object holds the current menu scene, statistics about the player on *all levels, and methods to update current level menu scene
*@param 
    currentLevel holds the current game level user has selected
*@param level 
    holds the current menu scene
*@param prevTime 
    stores the time of the previous frame
*@param points 
    stores number of points player has
*@param deaths 
    stores number of deaths player has
*@param totalPlayTime 
    stores total time player has played the game for
*@param hoverLeave 
    stores true if user has hovered over area and then clicked
*       over area
*Authors: Brandon Y., Aadit S.
*/
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
        bool hoverLeave;
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
    levels.points = 0;
    levels.deaths = 0;
    levels.totalPlayTime = 0;
    levels.hoverLeave = false;

    levels.prevTime = TimeNow();

    //Create and display Main Menu
    levels.setLevel(LEVEL_MAIN_MENU);
    levels.draw();
    
    //While user doesn't exit run program
    while(levels.level != LEVEL_EXIT) {
        //Update scene depending on where user clicked
        Sleep(0.01);
        clicked = LCD.Touch(&x, &y);
        levels.update(x, y, clicked);
        
        //Wait for release on certain pages
        if(clicked){
            if(levels.level == LEVEL_MAIN_MENU ||
                levels.level == LEVEL_MAIN_MENU ||
                levels.level == LEVEL_LEVEL_SELECT ||
                levels.level == LEVEL_DISPLAY_STATS ||
                levels.level == LEVEL_DIRECTIONS ||
                levels.level == LEVEL_CREDITS ||
                levels.level == LEVEL_COMPLETE ||
                levels.level == LEVEL_DEATH_1 ||
                levels.level == LEVEL_DEATH_2
            )
                while(LCD.Touch(&x, &y)){};
        }
    }


    return 0;
}


/*
*Function for Menu class
*void Levels::draw() 
*   Function draws the menu state depending on what @param level is set to
*Ex. 
*   If level is LEVEL_MAIN_MENU, function would draw the main menu
*Authors: Brandon Y., Aadit S.
*/
void Levels::draw(){
    //Declare variables for the position of where user touches screen 
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
            //Title
            LCD.WriteAt("Bloc-Jump", 100, 180);
            LCD.DrawHorizontalLine(198, 100, 220);
            
            break;
        case LEVEL_LEVEL_SELECT: 
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            LCD.WriteAt("Level Select", 5, 5);
            //Level 1 Button
            LCD.DrawRectangle(80, 60, 160, 50);
            LCD.WriteAt("Level 1", 100, 800);
            //Level 2 Button
            LCD.DrawRectangle(80, 120, 160, 50);
            LCD.WriteAt("Level 2", 100, 140);
            //Main Menu Button
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(80, 180, 160, 50);
            LCD.WriteAt("Main Menu", 100, 200);
            break;
        case LEVEL_DISPLAY_STATS:
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            //Points
            LCD.WriteAt("Points:", 50, 50);
            LCD.WriteAt(points, 150, 50);
            //Deaths
            LCD.WriteAt("Deaths:", 50, 65);
            LCD.WriteAt(deaths, 150, 65);
            //Time Played
            LCD.WriteAt("Time Played:", 50, 80);
            LCD.WriteAt(totalPlayTime, 200, 80);
            //Main Menu Button
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 130, 160, 50);
            LCD.WriteAt("Main Menu", 120, 150);
            break;
        case LEVEL_CREDITS:
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            //Credits
            LCD.WriteAt("Created By: ", 10, 180);
            LCD.WriteAt("AADIT S. & BRANDON Y.", 10, 200);
            //Main Menu Button
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 100, 160, 50);
            LCD.WriteAt("Main Menu", 120, 120);
            break;
        case LEVEL_DIRECTIONS:
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            //Instructions
            LCD.WriteAt("Directions", 0, 0);
            LCD.WriteAt("The Goal is to reach the", 0, 20);
            LCD.WriteAt("flag at the end of each", 0, 40);
            LCD.WriteAt("level.", 0, 60);
            LCD.WriteAt("To Move, touch where you", 0, 80);
            LCD.WriteAt("want the player to move. ", 0, 100);
            LCD.WriteAt("To Jump, touch above the", 0, 120);
            LCD.WriteAt("player. ", 0, 140);
            //Main Menu Button
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 180, 160, 50);
            LCD.WriteAt("Main Menu", 130, 200);
            break;
        case LEVEL_1: 
            LCD.SetBackgroundColor(LIGHTBLUE);
            LCD.Clear();
            //Welcome to Level 1 scene
            LCD.WriteAt("Welcome to Level 1", 40, 60);
            //Pauses and creates Level 1
            Sleep(0.5);
            currentLevel = LEVEL1::createLevel();
            prevTime = TimeNow();

            break;
        case LEVEL_2: 
            LCD.SetBackgroundColor(LIGHTGRAY);
            LCD.Clear();
            //Welcome to Level 2 scene
            LCD.WriteAt("Welcome to Level 2", 40, 60);
            Sleep(0.5);
            //Pauses and creates Level 2
            currentLevel = LEVEL2::createLevel();
            prevTime = TimeNow();
            break;

        case LEVEL_DEATH_1: 
            //Updates total deaths and play time 
            deaths += 1;
            totalPlayTime += currentLevel.playTime;
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            //Death screen
            LCD.SetFontColor(RED);
            LCD.WriteAt("YOU DIED", 120, 10);
            LCD.WriteAt("Deaths: ", 100, 30);
            LCD.WriteAt(deaths, 200, 30);
            //Main menu button
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 100, 160, 50);
            LCD.WriteAt("Main Menu", 120, 120);
            //Respwan Button
            LCD.DrawRectangle(100, 160, 160, 50);
            LCD.WriteAt("Respawn", 120, 180);
            while(LCD.Touch(&x, &y)){};
            break;
        case LEVEL_COMPLETE:
            //Update total points and total play time
            points += (int)(currentLevel.levelPoints + currentLevel.levelPointsTimeMulti * currentLevel.levelTime);
            totalPlayTime = currentLevel.playTime;

            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            //Main Menu Button
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 160, 160, 50);
            LCD.WriteAt("Main Menu", 120, 180);
            //Points earned
            LCD.SetFontColor(WHITE);
            LCD.WriteAt("Points Earned:", 60, 50);
            LCD.WriteAt((int)(currentLevel.levelPoints + currentLevel.levelPointsTimeMulti * currentLevel.levelTime), 250, 50);
            break;
        case LEVEL_DEATH_2:
            //Updates total deaths and play time 
            deaths += 1;
            totalPlayTime += currentLevel.playTime;
            LCD.SetBackgroundColor(BLACK);
            LCD.Clear();
            //Death Screen
            LCD.SetFontColor(RED);
            LCD.WriteAt("YOU DIED", 120, 10);
            LCD.WriteAt("Deaths: ", 100, 30);
            LCD.WriteAt(deaths, 200, 30);
            //Main Menu Button
            LCD.SetFontColor(GREEN);
            LCD.DrawRectangle(100, 100, 160, 50);
            LCD.WriteAt("Main Menu", 120, 120);
            //Respawn Button
            LCD.DrawRectangle(100, 160, 160, 50);
            LCD.WriteAt("Respawn", 120, 180);
            while(LCD.Touch(&x, &y)){};
            break;

    }
    
}

/*
*Function for Menu class
*void Levels::update(int x, int y, boolean clicked) 
*   Updates @param level depending on where user clicks
*@param x
*   The horizontal position of where user clicks
*@param y 
*   The vertical position of where user clicks
*@param clicked
*   If user has clicked the position or not
*Ex. 
*   If user clicks button in Main Menu at x:(5,145) and y:(5,55), set scene 
*   to Level Select
*Authors: Brandon Y., Aadit S.
*/
void Levels::update(int x, int y, bool clicked){
    float t = 0;
    int state = STATE_NONE;
    switch(level){
        //If in Main Menu
        case LEVEL_MAIN_MENU:
            if(clicked){
                //Level Select Scene
                if(x>5 && x<145 && y>5 && y<55){
                    setLevel(LEVEL_LEVEL_SELECT);
                }
                //Display Stats Scene
                if(x>175 && x<315 && y>5 && y<55){
                    setLevel(LEVEL_DISPLAY_STATS);
                }
                //Displays Credit Scene
                if(x>5 && x<145 && y>70 && y<120){
                    setLevel(LEVEL_CREDITS);
                }
                //Displays Directions 
                if(x>175 && x<315 && y>70 && y<120){
                    setLevel(LEVEL_DIRECTIONS);
                }
            }
            break;
        //If in Level Select     
        case LEVEL_LEVEL_SELECT:
            if(clicked){
                //Level 1
                if(x>80 && x<240 && y>60 && y<110){
                    setLevel(LEVEL_1);
                }
                //Level 2
                else if(x>80 && x<240 && y>120 && y<170){
                    setLevel(LEVEL_2);
                }
                //Main Menu
                else if(x>80 && x<240 && y>180 && y<230){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;
        case LEVEL_DISPLAY_STATS:
            if(clicked){
                //Main Menu
                if(x>100 && x<260 && y>130 && y<180){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;
        case LEVEL_CREDITS:
            if(clicked){
                //Main Menu
                if(x>100 && x<260 && y>100 && y<150){
                    setLevel(LEVEL_MAIN_MENU);
                }
            }
            break;
        case LEVEL_DIRECTIONS:
            if(clicked){
                //Main Menu
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
            if(x>305 && x<320 && y>0 && y<15){
                if(clicked && hoverLeave){
                     totalPlayTime += currentLevel.playTime;
                    setLevel(LEVEL_MAIN_MENU);
                }
                if(!clicked){
                    hoverLeave = true;
                }
               
            }else{
                hoverLeave = false;
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
            if(x>305 && x<320 && y>0 && y<15){
                if(clicked && hoverLeave){
                     totalPlayTime += currentLevel.playTime;
                    setLevel(LEVEL_MAIN_MENU);
                }
                if(!clicked){
                    hoverLeave = true;
                }
               
            }else{
                hoverLeave = false;
            }
            prevTime = t;
            break;
    }
}

void Levels::setLevel(int l){
    level = l;
    draw();
}
