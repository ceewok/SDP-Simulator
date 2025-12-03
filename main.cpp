#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include <iostream>
#include <map>
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

void drawPlayer1Fog(){
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
        LCD.DrawLine(leftGridPosition, (yStep * i), leftGridPosition + (xStep * i), 0);
        //Bottom & right
        LCD.DrawLine(leftGridPosition + (xStep * i), halfwayGridPositionY, rightGridPosition, (yStep * i));

        //left & bottom
        LCD.DrawLine(leftGridPosition, halfwayGridPositionY - (yStep * i), leftGridPosition + (xStep * i), halfwayGridPositionY);
        //Right & top
        LCD.DrawLine(rightGridPosition - (xStep * i), 0, rightGridPosition, (yStep * i));
    }

}

int xToCol(int x){
    int leftGridPosition = 65;
    return (x - leftGridPosition) / 31;
}

int yToRow(int y){
    return y / 31;
}

int rowToY(int row){
    return row * 31;
}

int colToX(int col){
    int leftGridPosition = 65;
    return (col * 31) + leftGridPosition;
}

void clearSpace(int col, int row){
    LCD.SetFontColor(BLACK);
    LCD.FillRectangle(colToX(col) + 1, rowToY(row) + 1, 29, 30);
}

class Troop
{
private:
    int health;
    std::string troopType;
    FEHImage image;
    int player;
    int col;
    int row;
public:
    Troop(std::string troopType, int plr, int c, int r);
    Troop();
    ~Troop();

    void drawTroop();
    int getCol();
    int getRow();
    void move(int c, int r);
    std::string type();
    int damage(int dam);
};

Troop::Troop(std::string type, int plr, int c, int r){
    troopType = type;
    player = plr;
    col = c;
    row = r;

    if(type.compare("SOLDIER") == 0){
        health = 3;
        image.Open("sprites/soldier.png");
    }

}

Troop::Troop(){
    troopType = "NAN";
}

Troop::~Troop()
{
}

void Troop::drawTroop(){
    image.Draw(colToX(col), rowToY(row));
}

int Troop::getCol(){
    return col;
}

int Troop::getRow(){
    return row;
}

std::string Troop::type(){
    return troopType;
}

void Troop::move(int c, int r){
    clearSpace(col, row);
    col = c;
    row = r;
    drawTroop();
}

int Troop::damage(int dam){
    health -= dam;
    return health;
}


void playGame(){
    LCD.Clear();

    LCD.SetFontColor(SCARLET);
    LCD.WriteRC("PLAYER 1 TURN", 6, 6);
    Sleep(1.0);
    LCD.Clear();

    Icon backButton;
    backButton.SetProperties("X", 0, 0, 15, 20, WHITE, SCARLET);

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
    int board[6][6] = {};
    std::map<std::pair<int, int>, Troop> troops;

    std::vector<Troop> p1Troops;
    std::vector<Troop> p2Troops;

    std::string selectedTroop;
    bool troopSelected = false;

    int playerMove = 1;
    bool battleStarted = false;

    int p1Gold = 3;
    int p2Gold = 3;
    Icon goldIcon;
    char buffer[20];
    sprintf(buffer, "%d GOLD", p1Gold);
    goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
    goldIcon.Draw();

    while(true){

        if(p1Gold <= 0){
            p1Gold = 6;
            playerMove = 2;


            LCD.Clear();
            LCD.SetFontColor(SCARLET);
            LCD.WriteRC("PLAYER 2 TURN", 6, 7);
            Sleep(1.0);
            LCD.Clear();

            soldierButton.Draw();
            soliderImage.Draw(20, 30);
            archerButton.Draw();
            archerImage.Draw(20, 70);
            mageButton.Draw();
            mageImage.Draw(20, 110);
            knightButton.Draw();
            knightImage.Draw(20, 150);
            drawGrid();
            drawPlayer1Fog();

            sprintf(buffer, "%d GOLD", p2Gold);
            goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
            goldIcon.Draw();

        }else if(p2Gold <= 0){
            p2Gold = 6;
            LCD.Clear();
            LCD.SetFontColor(SCARLET);
            LCD.WriteRC("WHO GOES FIRST?", 2, 5);
            Icon p1Button;
            p1Button.SetProperties("P1", X_BOUND/2 - 65, 60, 60, 30, WHITE, SCARLET);
            p1Button.Draw();
            Icon p2Button;
            p2Button.SetProperties("P2", X_BOUND/2 + 5, 60, 60, 30, WHITE, SCARLET);
            p2Button.Draw();
            while(true){
                if(LCD.Touch(&x, &y)){
                    if(p1Button.Pressed(x,y,1)){
                        playerMove = 1;
                        break;
                    }
                    if(p2Button.Pressed(x,y,1)){
                        playerMove = 2;
                        break;
                    }
                }
            }
            LCD.Clear();
            drawGrid();
            for(int col = 0; col < 6; col++){

                for(int row = 0; row < 6; row++){
                    
                    if(board[col][row] != 0){
                        troops.at({col, row}).drawTroop();
                    }

                }

            }
            battleStarted = true;
        }

        while(battleStarted){

            Sleep(1.0);

            if(playerMove == 1){

                for(Troop &troop : p1Troops){

                    int closestEnemy = 100;
                    Troop target;
                    int troopCol = troop.getCol();
                    int troopRow = troop.getRow();
                    for(int col = 0; col < 6; col++){

                        for(int row = 0; row < 6; row++){

                            if(board[col][row] == 2){

                                if((abs(col - troopCol) + abs(row - troopRow)) < closestEnemy){
                                    target = troops.at({col, row});
                                }

                            }

                        }

                    }
                    int targetCol = target.getCol();
                    int targetRow = target.getRow();

                    if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){

                        board[troopCol][troopRow] = 0;
                        troops.erase({troopCol, troopRow});

                        board[troopCol][troopRow + 1] = playerMove;
                        troops.insert({{troopCol, troopRow + 1}, troop});

                        troop.move(troopCol, troopRow + 1);
                    }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){

                        board[troopCol][troopRow] = 0;
                        troops.erase({troopCol, troopRow});

                        board[troopCol][troopRow - 1] = playerMove;
                        troops.insert({{troopCol, troopRow - 1}, troop});

                        troop.move(troopCol, troopRow - 1);
                    }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                        board[troopCol][troopRow] = 0;
                        troops.erase({troopCol, troopRow});

                        board[troopCol + 1][troopRow] = playerMove;
                        troops.insert({{troopCol + 1, troopRow}, troop});

                        troop.move(troopCol + 1, troopRow);
                    }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                        board[troopCol][troopRow] = 0;
                        troops.erase({troopCol, troopRow});

                        board[troopCol - 1][troopRow] = playerMove;
                        troops.insert({{troopCol - 1, troopRow}, troop});

                        troop.move(troopCol - 1, troopRow);
                    }

                    Sleep(0.2);
                }
                playerMove = 2;
            }else{

                for(Troop &troop : p2Troops){

                    int closestEnemy = 100;
                    Troop target;
                    int troopCol = troop.getCol();
                    int troopRow = troop.getRow();
                    for(int col = 0; col < 6; col++){

                        for(int row = 0; row < 6; row++){

                            if(board[col][row] == 1){

                                if((abs(col - troopCol) + abs(row - troopRow)) < closestEnemy){
                                    target = troops.at({col, row});
                                }

                            }

                        }

                    }
                    int targetCol = target.getCol();
                    int targetRow = target.getRow();

                    if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){

                        board[troopCol][troopRow] = 0;
                        troops.erase({troopCol, troopRow});

                        board[troopCol][troopRow + 1] = playerMove;
                        troops.insert({{troopCol, troopRow + 1}, troop});

                        troop.move(troopCol, troopRow + 1);
                    }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){

                        board[troopCol][troopRow] = 0;
                        troops.erase({troopCol, troopRow});

                        board[troopCol][troopRow - 1] = playerMove;
                        troops.insert({{troopCol, troopRow - 1}, troop});

                        troop.move(troopCol, troopRow - 1);
                    }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                        board[troopCol][troopRow] = 0;
                        troops.erase({troopCol, troopRow});

                        board[troopCol + 1][troopRow] = playerMove;
                        troops.insert({{troopCol + 1, troopRow}, troop});

                        troop.move(troopCol + 1, troopRow);
                    }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                        board[troopCol][troopRow] = 0;
                        troops.erase({troopCol, troopRow});

                        board[troopCol - 1][troopRow] = playerMove;
                        troops.insert({{troopCol - 1, troopRow}, troop});

                        troop.move(troopCol - 1, troopRow);
                    }

                    Sleep(0.2);
                }

                playerMove = 1;
            }

        }

        if(LCD.Touch(&x,&y)){
            if(backButton.Pressed(x,y,0)){
                break;
            }
            if(!troopSelected){
                if(soldierButton.Pressed(x,y,1)){
                    soldierButton.SetProperties("", 20, 30, 32, 32, YELLOW, WHITE);
                    soldierButton.Draw();
                    selectedTroop = "SOLDIER";
                    troopSelected = true;
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    LCD.SetFontColor(SCARLET);
                    LCD.WriteAt("Now choose an open space", 20, 190);
                }
            }else if((x >= leftGridPosition && x <= rightGridPosition) && (y >= topGridPosition && y <= bottomGridPosition)){
                int col = xToCol(x);
                int row = yToRow(y);
                if(playerMove == 1 && row <= 2 && board[col][row] == 0){

                    Troop newTroop{selectedTroop, playerMove, col, row};

                    board[col][row] = playerMove;
                    troops.insert({{col, row}, newTroop});
                    p1Troops.push_back(newTroop);

                    newTroop.drawTroop();

                    if(selectedTroop.compare("SOLDIER") == 0){
                        soldierButton.SetProperties("", 20, 30, 32, 32, WHITE, WHITE);
                        soldierButton.Draw();
                        p1Gold -= 1;
                        sprintf(buffer, "%d GOLD", p1Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
                    }
                    selectedTroop = "";
                    troopSelected = false;
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    goldIcon.Draw();
                }else if(playerMove == 2 && row >= 3 && board[col][row] == 0){
                    Troop newTroop{selectedTroop, playerMove, col, row};

                    board[col][row] = playerMove;
                    troops.insert({{col, row}, newTroop});
                    p2Troops.push_back(newTroop);

                    newTroop.drawTroop();

                    if(selectedTroop.compare("SOLDIER") == 0){
                        soldierButton.SetProperties("", 20, 30, 32, 32, WHITE, WHITE);
                        soldierButton.Draw();
                        p2Gold -= 1;
                        sprintf(buffer, "%d GOLD", p2Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
                    }
                    selectedTroop = "";
                    troopSelected = false;
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    goldIcon.Draw();
                }

                Sleep(0.25);
            }
            

        }else if(!LCD.Touch(&x, &y) && !troopSelected && (x >= 0 && x <= 65) && (y >= 0 && y <= Y_BOUND)){
            if(soldierButton.Pressed(x,y,1) || archerButton.Pressed(x,y,1)){
                hoverIcon.SetProperties("2 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();
                hoverIcon.SetProperties("1 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, WHITE, GOLDENROD);
                hoverIcon.Draw();
            }else if(mageButton.Pressed(x,y,1) || knightButton.Pressed(x,y,1)){
                hoverIcon.SetProperties("1 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();
                hoverIcon.SetProperties("2 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, WHITE, GOLDENROD);
                hoverIcon.Draw();
            }else{
                hoverIcon.SetProperties("1 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();
                hoverIcon.SetProperties("2 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, BLACK, BLACK);
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