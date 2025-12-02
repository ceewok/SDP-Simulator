#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
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

    int x,y;

    while(true){

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
                break;
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

    int x,y;

    while(true){
        if(LCD.Touch(&x,&y)){

            if(backButton.Pressed(x,y,0)){
                break;
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

    int x,y;

    while(true){
        if(LCD.Touch(&x,&y)){

            if(backButton.Pressed(x,y,0)){
                break;
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
    LCD.WriteRC("Nate Gradisher", 9, 8);

    int x,y;

    while(true){
        if(LCD.Touch(&x,&y)){

            if(backButton.Pressed(x,y,0)){
                break;
            }

        }
    }

}

void drawGrid(){
    LCD.SetFontColor(WHITE);

int topGridPosition = 0;
int bottomGridPosition = Y_BOUND - 53;
int rightGridPosition = X_BOUND - 69;
int leftGridPosition = 65;

//Border
LCD.DrawLine(leftGridPosition,topGridPosition,leftGridPosition,bottomGridPosition);
LCD.DrawLine(leftGridPosition,topGridPosition,rightGridPosition,topGridPosition);
LCD.DrawLine(leftGridPosition,bottomGridPosition,rightGridPosition,bottomGridPosition);
LCD.DrawLine(rightGridPosition,topGridPosition,rightGridPosition,bottomGridPosition);

//Vertical Lines
int numVertLines = 5;
int vertStepSize = 31;
for(int i = 1; i <= numVertLines; i++){
    LCD.DrawVerticalLine(vertStepSize * i + leftGridPosition, topGridPosition, bottomGridPosition);
}

//Horizontal Lines
int numHoriLines = 6;
int horiStepSize = 31;
for(int i = 1; i <= numHoriLines; i++){
    LCD.DrawHorizontalLine(horiStepSize * i, leftGridPosition, rightGridPosition);
}

}

void drawPlayer2Fog(){
    int bottomGridPosition = Y_BOUND - 53;
    int rightGridPosition = X_BOUND - 69;
    int leftGridPosition = 65;
    int halfwayGridPositionY = 3 * 31;
    float numLines = 50;
    float xStep = (rightGridPosition - leftGridPosition) / numLines;
    float yStep = (bottomGridPosition - halfwayGridPositionY) / numLines;
    for(int i = 1; i <= numLines; i++){

        int randomColor = Random.RandInt();
        if(randomColor < 10000){
            LCD.SetFontColor(LCD.ScaleColor(GRAY, 0.7f));
        }else if(randomColor < 20000){
            LCD.SetFontColor(LCD.ScaleColor(GRAY, 1.2f));
        }else{
            LCD.SetFontColor(GRAY);
        }

        //Left & top
        LCD.DrawLine(leftGridPosition, halfwayGridPositionY + (yStep * i), leftGridPosition + (xStep * i), halfwayGridPositionY);
        //Bottom & right
        LCD.DrawLine(leftGridPosition + (xStep * i), bottomGridPosition, rightGridPosition, halfwayGridPositionY + (yStep * i));

        //left & bottom
        LCD.DrawLine(leftGridPosition, bottomGridPosition - (yStep * i), leftGridPosition + (xStep * i), bottomGridPosition);
        //Right & top
        LCD.DrawLine(rightGridPosition - (xStep * i), halfwayGridPositionY, rightGridPosition, halfwayGridPositionY + (yStep * i));
    }

}

int xToCol(int x){
    int leftGridPosition = 65;
    return ((x - leftGridPosition) / 31) + 1;
}

int yToRow(int y){
    return (y / 31) + 1;
}

int rowToY(int row){
    return (row - 1) * 31;
}

int colToX(int col){
    int leftGridPosition = 65;
    return ((col - 1) * 31) + leftGridPosition;
}

class Soldier
{
private:
    int health = 3;
    int xPos;
    int yPos;
public:
    Soldier(int x, int y, int board[][6]);
    ~Soldier();
};

Soldier::Soldier(int x, int y, int board[][6]){

}


Soldier::~Soldier()
{
}


void playGame(){
    LCD.Clear();

    LCD.SetFontColor(SCARLET);
    LCD.WriteRC("PLAYER 1 TURN", 7, 8);
    Sleep(1.0);
    LCD.Clear();

    Icon backButton;
    backButton.SetProperties("X", 0, 0, 15, 20, WHITE, SCARLET);
    backButton.Draw();

    int topGridPosition = 0;
    int bottomGridPosition = Y_BOUND - 53;
    int rightGridPosition = X_BOUND - 69;
    int leftGridPosition = 65;

    drawGrid();
    drawPlayer2Fog();

    //Troop Buttons
    Icon soldierButton;
    soldierButton.SetProperties("", 20, 30, 32, 32, WHITE, WHITE);
    soldierButton.Draw();
    FEHImage soliderImage("sprites/soldier.png");
    soliderImage.Draw(20, 30);

    Icon archerButton;
    archerButton.SetProperties("", 20, 70, 32, 32, WHITE, WHITE);
    archerButton.Draw();
    FEHImage archerImage("sprites/archer.png");
    archerImage.Draw(20, 70);

    Icon mageButton;
    mageButton.SetProperties("", 20, 110, 32, 32, WHITE, WHITE);
    mageButton.Draw();
    FEHImage mageImage("sprites/mage.png");
    mageImage.Draw(20, 110);

    Icon knightButton;
    knightButton.SetProperties("", 20, 150, 32, 32, WHITE, WHITE);
    knightButton.Draw();
    FEHImage knightImage("sprites/knight.png");
    knightImage.Draw(20, 150);

    Icon hoverIcon;

    int x,y;
    bool troopSelected = false;

    int board[6][6] = {};

    while(true){

        if(LCD.Touch(&x,&y)){
            if(backButton.Pressed(x,y,0)){
                break;
            }
            if(!troopSelected){
                if(soldierButton.Pressed(x,y,0)){
                    troopSelected = true;
                }
            }else if((x >= leftGridPosition && x <= rightGridPosition) && (y >= topGridPosition && y <= bottomGridPosition)){
                int column = xToCol(x);
                int row = yToRow(y);
                Sleep(0.5);
            }
            

        }else if(!LCD.Touch(&x, &y) && (x >= 0 && x <= 65) && (y >= 0 && y <= Y_BOUND)){
            if(soldierButton.Pressed(x,y,1) || archerButton.Pressed(x,y,1)){
                hoverIcon.SetProperties("2 GOLD", X_BOUND/2 - 80/2, Y_BOUND - 32, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();
                hoverIcon.SetProperties("1 GOLD", X_BOUND/2 - 80/2, Y_BOUND - 32, 80, 30, WHITE, GOLDENROD);
                hoverIcon.Draw();
            }else if(mageButton.Pressed(x,y,1) || knightButton.Pressed(x,y,1)){
                hoverIcon.SetProperties("1 GOLD", X_BOUND/2 - 80/2, Y_BOUND - 32, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();
                hoverIcon.SetProperties("2 GOLD", X_BOUND/2 - 80/2, Y_BOUND - 32, 80, 30, WHITE, GOLDENROD);
                hoverIcon.Draw();
            }else{
                hoverIcon.SetProperties("1 GOLD", X_BOUND/2 - 80/2, Y_BOUND - 32, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();
                hoverIcon.SetProperties("2 GOLD", X_BOUND/2 - 80/2, Y_BOUND - 32, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();
            }
        }
    }
}


int main()
{
    drawMainMenu();
    return 0;
}