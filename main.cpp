#include "FEHLCD.h"
#include "FEHUtility.h"
#include <iostream>
#define GOLDEN_RATIO 1.618
#define X_BOUND 319
#define Y_BOUND 239
using namespace FEHIcon;
using namespace std;

//window x bounds : (0,319)
//window y bounds : (0, 239)

void drawStatisticsPage();
void drawMainMenu();
void drawInstructionsPage();
void drawCreditsPage();
void playGame();

void drawMainMenu(){
    LCD.Clear();
    int height = 40;
    int width = 150;
    int centerPosition = X_BOUND/2 - width/2;
    Icon playButton;
    Icon instructionsButton;
    Icon statButton;
    Icon creditsButton;
    Icon backButton;

    backButton.SetProperties("Quit", 20, 200, 50, 20, WHITE, SCARLET);
    playButton.SetProperties("Play", centerPosition, 10, width, height, WHITE, RED);
    instructionsButton.SetProperties("Instructions", centerPosition, 70, width, height, WHITE, BLUE);
    statButton.SetProperties("Statistics", centerPosition, 130, width, height, WHITE, GREEN);
    creditsButton.SetProperties("Credits", centerPosition, 190, width, height, WHITE, YELLOW);

    playButton.Draw();
    instructionsButton.Draw();
    statButton.Draw();
    creditsButton.Draw();
    backButton.Draw();

    bool inMenu = true;
    int x,y;

    while(inMenu){

        if(LCD.Touch(&x,&y)){

            if(playButton.Pressed(x,y,0)){
                playGame();
                LCD.Clear();
                playButton.Draw();
                instructionsButton.Draw();
                statButton.Draw();
                creditsButton.Draw();
                backButton.Draw();

            }
            if(instructionsButton.Pressed(x,y,0)){
                drawInstructionsPage();
                LCD.Clear();
                playButton.Draw();
                instructionsButton.Draw();
                statButton.Draw();
                creditsButton.Draw();
                backButton.Draw();

            }
            if(statButton.Pressed(x,y,0)){
                drawStatisticsPage();
                LCD.Clear();
                playButton.Draw();
                instructionsButton.Draw();
                statButton.Draw();
                creditsButton.Draw();
                backButton.Draw();

            }
            if(creditsButton.Pressed(x,y,0)){
                drawCreditsPage();
                LCD.Clear();
                playButton.Draw();
                instructionsButton.Draw();
                statButton.Draw();
                creditsButton.Draw();
                backButton.Draw();

            }
            if(backButton.Pressed(x,y,0)){
                inMenu = false;
            }

        }

    }
    
}

void drawStatisticsPage(){
    LCD.Clear();

    Icon title;
    title.SetProperties("Statistics", X_BOUND/2 - 150/2, 5, 150, 30, BLACK, GREEN);

    Icon backButton;
    backButton.SetProperties("Back", 20, 5, 50, 20, WHITE, SCARLET);

    backButton.Draw();
    title.Draw();

    int p1Wins = 0;
    int p2Wins = 0;
    int goldSpent = 0;
    int roundsPlayed = 0;

    LCD.SetFontColor(WHITE);
    LCD.WriteRC("Player1 wins - ", 2, 1);
    LCD.WriteRC(p1Wins, 2, 16);
    LCD.WriteRC("Player2 wins - ", 3, 1);
    LCD.WriteRC(p2Wins, 3, 16);
    LCD.WriteRC("Gold spent - ", 4, 1);
    LCD.WriteRC(goldSpent, 4, 14);
    LCD.WriteRC("Rounds played - ", 5, 1);
    LCD.WriteRC(roundsPlayed, 5, 17);

    bool inMenu = true;
    int x,y;

    while(inMenu){
        if(LCD.Touch(&x,&y)){

            if(backButton.Pressed(x,y,0)){
                inMenu = false;
            }

        }
    }

}

void drawInstructionsPage(){
    LCD.Clear();

    Icon title;
    title.SetProperties("Instructions", X_BOUND/2 - 150/2, 5, 150, 30, BLACK, BLUE);

    Icon backButton;
    backButton.SetProperties("Back", 20, 5, 50, 20, WHITE, SCARLET);

    backButton.Draw();
    title.Draw();
    LCD.SetFontColor(WHITE);
    LCD.WriteRC("This is a turn-based", 2, 1);
    LCD.WriteRC("strategy game. First the", 3, 1);
    LCD.WriteRC("players use their gold", 4, 1);
    LCD.WriteRC("to place troops,", 5, 1);
    LCD.WriteRC("and the troops will", 6, 1);
    LCD.WriteRC("automatically battle.", 7, 1);
    LCD.WriteRC("The first player to", 8, 1);
    LCD.WriteRC("win 3 battles wins", 9, 1);
    LCD.WriteRC("the game!", 10, 1);


    bool inMenu = true;
    int x,y;

    while(inMenu){
        if(LCD.Touch(&x,&y)){

            if(backButton.Pressed(x,y,0)){
                inMenu = false;
            }

        }
    }

}

void drawCreditsPage(){
    LCD.Clear();

    Icon title;
    title.SetProperties("Credits", X_BOUND/2 - 150/2, 5, 150, 30, BLACK, YELLOW);

    Icon backButton;
    backButton.SetProperties("Back", 20, 5, 50, 20, WHITE, SCARLET);

    backButton.Draw();
    title.Draw();

    LCD.SetFontColor(WHITE);
    LCD.WriteRC("Developers:", 5, 6);
    LCD.WriteRC("Alex Stuk", 7, 8);
    LCD.WriteRC("Nate Grandisher", 9, 8);

    bool inMenu = true;
    int x,y;

    while(inMenu){
        if(LCD.Touch(&x,&y)){

            if(backButton.Pressed(x,y,0)){
                inMenu = false;
            }

        }
    }

}

void playGame(){
    LCD.Clear();

    Icon backButton;
    backButton.SetProperties("Back", 20, 5, 50, 20, WHITE, SCARLET);

    backButton.Draw();

    LCD.WriteRC("Play game", 7, 8);

    bool inMenu = true;
    int x,y;

    while(inMenu){
        if(LCD.Touch(&x,&y)){

            if(backButton.Pressed(x,y,0)){
                inMenu = false;
            }

        }
    }
}


int main()
{
    drawMainMenu();
    return 0;
}