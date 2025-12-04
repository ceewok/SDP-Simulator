#include "FEHLCD.h"
#include "FEHUtility.h"
#include "FEHImages.h"
#include "FEHRandom.h"
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <list>
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
    LCD.WriteRC("Developers:", 3, 6);
    LCD.WriteRC("Alex Stuk", 5, 8);
    LCD.WriteRC("Nate Gradisher", 7, 8);
    LCD.WriteRC("Art:", 10, 6);
    LCD.WriteRC("SethBB on itch", 12, 8);

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

    //Specific bounds allow for a 6x6 grid of 32x32 boxes centered in the top of the screen
    int topGridPosition = 0;
    int bottomGridPosition = Y_BOUND - 53;
    int rightGridPosition = X_BOUND - 68;
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

//Draws 'fog' on the bottom half of the grid area, indicates to player one that their side of the board is the top
void drawPlayer2Fog(){
    int bottomGridPosition = Y_BOUND - 53;
    int rightGridPosition = X_BOUND - 68;
    int leftGridPosition = 65;
    int halfwayGridPositionY = 3 * 31;

    float numLines = 50;
    float xStep = (rightGridPosition - leftGridPosition) / numLines;
    float yStep = (bottomGridPosition - halfwayGridPositionY) / numLines;
    for(int i = 1; i <= numLines; i++){

        //Randomize the color, makes it look cool
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

//Draws 'fog' on the top half of the grid area, indicates to player two that their side of the board is the bottom
void drawPlayer1Fog(){
    int bottomGridPosition = Y_BOUND - 53;
    int rightGridPosition = X_BOUND - 68;
    int leftGridPosition = 65;
    int halfwayGridPositionY = 3 * 31;

    float numLines = 50;
    float xStep = (rightGridPosition - leftGridPosition) / numLines;
    float yStep = (bottomGridPosition - halfwayGridPositionY) / numLines;
    for(int i = 1; i <= numLines; i++){

        //Randomize the color, makes it look cool
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

//Helper functions to allow for grid --> coordinate and coordinate --> grid conversions easily (mostly used for rendering the sprites)
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

//Clears a specified grid space
void clearSpace(int col, int row){
    LCD.SetFontColor(BLACK);
    LCD.FillRectangle(colToX(col) + 1, rowToY(row) + 1, 30, 30);
}

//Colors a specified grid space, used for damage and indicating which troops are whos
void colorSpace(int col, int row, unsigned int color){
    LCD.SetFontColor(color);
    LCD.FillRectangle(colToX(col) + 1, rowToY(row) + 1, 30, 30);
}

void colorSquare(int col, int row, unsigned int color){
    LCD.SetFontColor(color);
    LCD.DrawRectangle(colToX(col), rowToY(row), 32, 32);
}

void resetSquare(int col, int row){
    LCD.SetFontColor(WHITE);
    LCD.DrawRectangle(colToX(col), rowToY(row), 32, 32);
}

//Troop class, contains data for each of the troops on the board
class Troop
{
private:
    int health;
    std::string troopType;
    FEHImage image;
    int player;
    int col;
    int row;
    int damPerHit;
    int id;
    float maxHealth;
public:
    Troop(std::string troopType, int plr, int c, int r, int id);
    Troop();
    ~Troop();

    void drawTroop();
    int getCol();
    int getRow();
    void move(int c, int r);
    std::string type();
    int damage(int dam);
    int getDamage();
    int isCharged = false;

    bool operator==(const Troop &otherTroop) const{
        return(this->id == otherTroop.id);
    }
};

//Constructor, takes the type of troop, the player who owns it and where it is in space
Troop::Troop(std::string type, int plr, int c, int r, int idNum){
    troopType = type;
    player = plr;
    col = c;
    row = r;
    id = idNum;

    //TODO: add other troop types with other behaviors
    if(type.compare("SOLDIER") == 0){
        health = 3;
        maxHealth = health;
        image.Open("sprites/soldier.png");
        damPerHit = 1;
    }else if(type.compare("ARCHER") == 0){
        health = 2;
        maxHealth = health;
        image.Open("sprites/archer.png");
        damPerHit = 1;
    }else if(type.compare("MAGE") == 0){
        health = 2;
        maxHealth = health;
        image.Open("sprites/mage.png");
        damPerHit = 3;
    }else if(type.compare("KNIGHT") == 0){
        health = 5;
        maxHealth = health;
        image.Open("sprites/knight.png");
        damPerHit = 1;
    }

}

//Default constructor, required for the vectors
Troop::Troop(){
    troopType = "NAN";
}

Troop::~Troop()
{
}

//Draws the troops sprite wherever it thinks it is on the board
void Troop::drawTroop(){
    if(player == 1){
        colorSquare(col, row, BLUE);
    }else if(player == 2){
        colorSquare(col, row, SCARLET);
    }
    if(isCharged){
        colorSpace(col, row, LIGHTBLUE);
    }else{
        clearSpace(col, row);
    }

    if(health > 0){
        int healthBarX = colToX(col) + 1;
        int healthBarBottomY = rowToY(row) + 30;
        float healthPercentage = (health / maxHealth);
        int healthBarTopY = healthBarBottomY - (29 * healthPercentage);
        LCD.SetFontColor(RED);
        LCD.DrawVerticalLine(healthBarX, healthBarBottomY, healthBarTopY);
    }

    image.Draw(colToX(col), rowToY(row));
}

//Gives the column of the troop
int Troop::getCol(){
    return col;
}

//Gives the row of the troop
int Troop::getRow(){
    return row;
}

//Returns the troops type
std::string Troop::type(){
    return troopType;
}

//Moves the troop, updates graphics & internals but DOES NOT update 2d array or map (very important)
void Troop::move(int c, int r){
    clearSpace(col, row);
    resetSquare(col, row);
    col = c;
    row = r;
    drawTroop();
}

//Damages the troop, has some rudementary graphics to show this + returns health to check if the troop is dead
int Troop::damage(int dam){
    health = health - dam;
    colorSpace(col, row, RED);
    Sleep(0.15);
    clearSpace(col, row);
    drawTroop();
    return health;
}

//Returns the troops damage per hit
int Troop::getDamage(){
    return damPerHit;
}

void projectile(int fromCol, int fromRow, int toCol, int toRow, unsigned int color){
    int fromX = colToX(fromCol) + 15;
    int fromY = rowToY(fromRow) + 15;
    int toX = colToX(toCol) + 15;
    int toY = rowToY(toRow) + 15; 
    LCD.SetFontColor(color);
    LCD.DrawLine(fromX, fromY, toX, toY);
}


void playGame(){
    //Clear the main menu
    LCD.Clear();

    //Let the players know it is player 1 turn
    LCD.SetFontColor(SCARLET);
    LCD.WriteRC("PLAYER 1 TURN", 6, 6);
    Sleep(1.0);
    LCD.Clear();

    //Old back button, unused currently
    Icon backButton;
    backButton.SetProperties("X", 0, 0, 15, 20, WHITE, SCARLET);

    //Grid position
    int topGridPosition = 0;
    int bottomGridPosition = Y_BOUND - 53;
    int rightGridPosition = X_BOUND - 68;
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

    //Hover icon to show troop prices
    Icon hoverIcon;

    //xy required for .touch() function
    int x,y;

    //2d array containing where the troops are on the board, primarily used to find the closest target for each troop
    int board[6][6] = {};
    //Map that links a col/row coordinate to a troop, used AFTER iterating the 2d array (which gives coordinate of closest troop, but not the troop class itself)
    std::map<std::pair<int, int>, Troop*> troops;

    //Vectors containing the player's troops, used to iterate through them and perform actions
    std::list<Troop> p1Troops;
    std::list<Troop> p2Troops;

    //selectedTroop contains troopType, used in building phase
    std::string selectedTroop;
    bool troopSelected = false;

    //id used to keep track of each troop, mostly used for comparison during removal from vector
    int id = 1;

    //Data to keep track of whos move it is, if we are in build/battle phase, as well as how many rounds have passed
    int playerMove = 1;
    bool battleStarted = false;
    int round = 1;

    //Starting gold values, can be changed any time
    const int startingGold = 3;
    int p1Gold = startingGold;
    int p2Gold = startingGold;

    //Drawing the player's gold icon to display how much gold they have
    Icon goldIcon;
    char buffer[20];
    sprintf(buffer, "%d GOLD", p1Gold);
    goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
    goldIcon.Draw();

    while(true){

        //If player one runs out of gold, end their build turn
        if(p1Gold <= 0){
            //Up their gold again so that this if statement doesn't run more than once per build stage
            p1Gold = startingGold;
            //Change the move to the second players
            playerMove = 2;

            //Clear the screen & hide player one's troops, then indicate it is player two's turn
            LCD.Clear();
            LCD.SetFontColor(SCARLET);
            LCD.WriteRC("PLAYER 2 TURN", 6, 7);
            Sleep(1.0);
            LCD.Clear();

            //Redraw the build stage icons
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

            //Draw player 2's gold icon
            sprintf(buffer, "%d GOLD", p2Gold);
            goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
            goldIcon.Draw();

        }else if(p2Gold <= 0){
            //This if statement only returns true if p1's gold is positive and p2's gold is <= 0, which is only possible if both players have placed their troops.

            //reset gold
            p2Gold = startingGold;
            //clear the screen, then ask for who wants to go first (can decide with rock paper scissors or something, we can also change this to random change quite easily as well)
            LCD.Clear();
            LCD.SetFontColor(SCARLET);
            LCD.WriteRC("WHO GOES FIRST?", 2, 5);

            //Creating the buttons to choose
            Icon p1Button;
            p1Button.SetProperties("P1", X_BOUND/2 - 65, 60, 60, 30, WHITE, SCARLET);
            p1Button.Draw();
            Icon p2Button;
            p2Button.SetProperties("P2", X_BOUND/2 + 5, 60, 60, 30, WHITE, SCARLET);
            p2Button.Draw();

            //Stop the execution until a choice is made
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
            //Clear the screen, redraw the grid (for battle) and then iterate through the 2d array and for each non-zero value, draw the troop that is placed at that coordinate
            LCD.Clear();
            drawGrid();
            for(int col = 0; col < 6; col++){

                for(int row = 0; row < 6; row++){
                    
                    if(board[col][row] != 0){
                        Troop *curTroop = troops.at({col, row});
                        curTroop->drawTroop();
                    }

                }

            }
            battleStarted = true;
        }

        //Only starts after build stage is done and battle screen is setup
        while(battleStarted){

            Sleep(1.0);

            //If player 1's troops move first
            if(playerMove == 1){

                //For each troop that p1 owns (& sets troop variable by reference, not copy)
                for(Troop &troop : p1Troops){

                    //find closest enemy
                    int closestEnemy = 100;
                    int troopCol = troop.getCol();
                    int troopRow = troop.getRow();
                    int targetCol = 0;
                    int targetRow = 0;
                    for(int col = 0; col < 6; col++){

                        for(int row = 0; row < 6; row++){

                            if(board[col][row] == 2){

                                if((abs(col - troopCol) + abs(row - troopRow)) < closestEnemy){
                                    targetCol = col;
                                    targetRow = row;
                                    closestEnemy = (abs(col - troopCol) + abs(row - troopRow));
                                }

                            }

                        }

                    }

                    //target is now the closest enemy to the current troop
                    Troop *target = troops.at({targetCol, targetRow});
                    if(troop.type().compare("SOLDIER") == 0){
                        if(abs(troopCol - targetCol) <= 1 && abs(troopRow - targetRow) <= 1){
                            //if within one space, attack target
                            int targetHealth = target->damage(troop.getDamage());

                            //if the targets health is below zero,
                            if(targetHealth <= 0){
                                //remove them from the 2d coordinate array
                                board[targetCol][targetRow] = 0;
                                //erase them from the map
                                troops.erase({targetCol, targetRow});
                                //delete their sprite
                                clearSpace(targetCol, targetRow);
                                resetSquare(targetCol, targetRow);

                                p2Troops.remove(*target);
                            }
                            //^ this essentially 'kills' the target as there is now no reference to it anymore and will not make any action as it is not in the p2Troops vector

                            //If the target is not close enough to attack,
                        }else if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){
                            //move DOWN
                            troop.move(troopCol, troopRow + 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow + 1] = playerMove;
                            troops.insert({{troopCol, troopRow + 1}, &troop});

                        }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){
                            //move UP
                            troop.move(troopCol, troopRow - 1);
                            
                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow - 1] = playerMove;
                            troops.insert({{troopCol, troopRow - 1}, &troop});

                        }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                            //move RIGHT
                            troop.move(troopCol + 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol + 1][troopRow] = playerMove;
                            troops.insert({{troopCol + 1, troopRow}, &troop});

                        }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                            //move LEFT
                            troop.move(troopCol - 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol - 1][troopRow] = playerMove;
                            troops.insert({{troopCol - 1, troopRow}, &troop});

                        }
                    }else if(troop.type().compare("ARCHER") == 0){
                        if(abs(troopCol - targetCol) <= 2 && abs(troopRow - targetRow) <= 2){

                            projectile(troopCol, troopRow, targetCol, targetRow, WHITE);
                            int targetHealth = target->damage(troop.getDamage());

                            //projectile cleanup
                            LCD.Clear();
                            drawGrid();
                            for(Troop &troop : p1Troops){
                                troop.drawTroop();
                            }
                            for(Troop &troop : p2Troops){
                                troop.drawTroop();
                            }

                            if(targetHealth <= 0){
                                board[targetCol][targetRow] = 0;
                                troops.erase({targetCol, targetRow});
                                clearSpace(targetCol, targetRow);
                                resetSquare(targetCol, targetRow);

                                p2Troops.remove(*target);
                            }
                            
                        }else if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){
                            //move DOWN
                            troop.move(troopCol, troopRow + 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow + 1] = playerMove;
                            troops.insert({{troopCol, troopRow + 1}, &troop});

                        }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){
                            //move UP
                            troop.move(troopCol, troopRow - 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow - 1] = playerMove;
                            troops.insert({{troopCol, troopRow - 1}, &troop});

                        }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                            //move RIGHT
                            troop.move(troopCol + 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol + 1][troopRow] = playerMove;
                            troops.insert({{troopCol + 1, troopRow}, &troop});

                        }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                            //move LEFT
                            troop.move(troopCol - 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol - 1][troopRow] = playerMove;
                            troops.insert({{troopCol - 1, troopRow}, &troop});

                        }
                    }else if(troop.type().compare("MAGE") == 0){
                        if(abs(troopCol - targetCol) <= 2 && abs(troopRow - targetRow) <= 2){
                            if(troop.isCharged){
                                projectile(troopCol, troopRow, targetCol, targetRow, LIGHTBLUE);
                                int targetHealth = target->damage(troop.getDamage());
                                troop.isCharged = false;

                                //projectile cleanup
                                LCD.Clear();
                                drawGrid();
                                for(Troop &troop : p1Troops){
                                    troop.drawTroop();
                                }
                                for(Troop &troop : p2Troops){
                                    troop.drawTroop();
                                }

                                if(targetHealth <= 0){
                                    board[targetCol][targetRow] = 0;
                                    troops.erase({targetCol, targetRow});
                                    clearSpace(targetCol, targetRow);
                                    resetSquare(targetCol, targetRow);

                                    p2Troops.remove(*target);
                                }
                            }else{
                                troop.isCharged = true;
                                troop.drawTroop();
                            }
                            
                        }else if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){
                            //move DOWN
                            troop.move(troopCol, troopRow + 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow + 1] = playerMove;
                            troops.insert({{troopCol, troopRow + 1}, &troop});

                        }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){
                            //move UP
                            troop.move(troopCol, troopRow - 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow - 1] = playerMove;
                            troops.insert({{troopCol, troopRow - 1}, &troop});

                        }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                            //move RIGHT
                            troop.move(troopCol + 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol + 1][troopRow] = playerMove;
                            troops.insert({{troopCol + 1, troopRow}, &troop});

                        }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                            //move LEFT
                            troop.move(troopCol - 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol - 1][troopRow] = playerMove;
                            troops.insert({{troopCol - 1, troopRow}, &troop});

                        }
                    }else if(troop.type().compare("KNIGHT") == 0){

                        //for loop gives knight TWO moves per turn instead of one, might need balancing as its kinda busted rn
                        for(int i = 0; i < 2; i++){
                            if(abs(troopCol - targetCol) <= 1 && abs(troopRow - targetRow) <= 1){
                                //if within one space, attack target
                                int targetHealth = target->damage(troop.getDamage());

                                //if the targets health is below zero,
                                if(targetHealth <= 0){
                                    //remove them from the 2d coordinate array
                                    board[targetCol][targetRow] = 0;
                                    //erase them from the map
                                    troops.erase({targetCol, targetRow});
                                    //delete their sprite
                                    clearSpace(targetCol, targetRow);
                                    resetSquare(targetCol, targetRow);

                                    p2Troops.remove(*target);

                                    //Since the knight just killed its target, we should stop its turn to avoid errors
                                    break;
                                }
                                //^ this essentially 'kills' the target as there is now no reference to it anymore and will not make any action as it is not in the p2Troops vector

                                //If the target is not close enough to attack,
                            }else if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){
                                //move DOWN
                                troop.move(troopCol, troopRow + 1);

                                board[troopCol][troopRow] = 0;
                                troops.erase({troopCol, troopRow});

                                board[troopCol][troopRow + 1] = playerMove;
                                troops.insert({{troopCol, troopRow + 1}, &troop});

                                troopRow += 1;

                            }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){
                                //move UP
                                troop.move(troopCol, troopRow - 1);
                                
                                board[troopCol][troopRow] = 0;
                                troops.erase({troopCol, troopRow});

                                board[troopCol][troopRow - 1] = playerMove;
                                troops.insert({{troopCol, troopRow - 1}, &troop});

                                troopRow -= 1;

                            }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                                //move RIGHT
                                troop.move(troopCol + 1, troopRow);

                                board[troopCol][troopRow] = 0;
                                troops.erase({troopCol, troopRow});

                                board[troopCol + 1][troopRow] = playerMove;
                                troops.insert({{troopCol + 1, troopRow}, &troop});

                                troopCol += 1;

                            }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                                //move LEFT
                                troop.move(troopCol - 1, troopRow);

                                board[troopCol][troopRow] = 0;
                                troops.erase({troopCol, troopRow});

                                board[troopCol - 1][troopRow] = playerMove;
                                troops.insert({{troopCol - 1, troopRow}, &troop});

                                troopCol -= 1;

                            }
                            Sleep(0.07);
                        }
                        //If this troop killed the final enemy, break to the end to avoid errors
                        if(p2Troops.size() == 0){
                            break;
                        }
                    }

                    //small sleep just to split up each of p1 troops' actions
                    Sleep(0.1);
                }
                //And then switch the turn to the other player
                playerMove = 2;

                //This is exactly the same as above just for p2 and not p1
            }else{

                for(Troop &troop : p2Troops){

                    //find closest enemy
                    int closestEnemy = 100;
                    int troopCol = troop.getCol();
                    int troopRow = troop.getRow();
                    int targetCol = 0;
                    int targetRow = 0;
                    for(int col = 0; col < 6; col++){

                        for(int row = 0; row < 6; row++){

                            if(board[col][row] == 1){

                                if((abs(col - troopCol) + abs(row - troopRow)) < closestEnemy){
                                    targetCol = col;
                                    targetRow = row;
                                    closestEnemy = (abs(col - troopCol) + abs(row - troopRow));
                                }

                            }

                        }

                    }

                    Troop *target = troops.at({targetCol, targetRow});

                    if(troop.type().compare("SOLDIER") == 0){
                        if(abs(troopCol - targetCol) <= 1 && abs(troopRow - targetRow) <= 1){

                            int targetHealth = target->damage(troop.getDamage());

                            if(targetHealth <= 0){
                                board[targetCol][targetRow] = 0;
                                troops.erase({targetCol, targetRow});
                                clearSpace(targetCol, targetRow);
                                resetSquare(targetCol, targetRow);

                                p1Troops.remove(*target);
                            }
                            
                        }else if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){
                            //move DOWN
                            troop.move(troopCol, troopRow + 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow + 1] = playerMove;
                            troops.insert({{troopCol, troopRow + 1}, &troop});

                        }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){
                            //move UP
                            troop.move(troopCol, troopRow - 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow - 1] = playerMove;
                            troops.insert({{troopCol, troopRow - 1}, &troop});

                        }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                            //move RIGHT
                            troop.move(troopCol + 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol + 1][troopRow] = playerMove;
                            troops.insert({{troopCol + 1, troopRow}, &troop});

                        }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                            //move LEFT
                            troop.move(troopCol - 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol - 1][troopRow] = playerMove;
                            troops.insert({{troopCol - 1, troopRow}, &troop});

                        }
                    }else if(troop.type().compare("ARCHER") == 0){
                        if(abs(troopCol - targetCol) <= 2 && abs(troopRow - targetRow) <= 2){

                            projectile(troopCol, troopRow, targetCol, targetRow, WHITE);
                            int targetHealth = target->damage(troop.getDamage());

                            //projectile cleanup
                            LCD.Clear();
                            drawGrid();
                            for(Troop &troop : p1Troops){
                                troop.drawTroop();
                            }
                            for(Troop &troop : p2Troops){
                                troop.drawTroop();
                            }

                            if(targetHealth <= 0){
                                board[targetCol][targetRow] = 0;
                                troops.erase({targetCol, targetRow});
                                clearSpace(targetCol, targetRow);
                                resetSquare(targetCol, targetRow);

                                p1Troops.remove(*target);
                            }
                            
                        }else if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){
                            //move DOWN
                            troop.move(troopCol, troopRow + 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow + 1] = playerMove;
                            troops.insert({{troopCol, troopRow + 1}, &troop});

                        }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){
                            //move UP
                            troop.move(troopCol, troopRow - 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow - 1] = playerMove;
                            troops.insert({{troopCol, troopRow - 1}, &troop});

                        }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                            //move RIGHT
                            troop.move(troopCol + 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol + 1][troopRow] = playerMove;
                            troops.insert({{troopCol + 1, troopRow}, &troop});

                        }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                            //move LEFT
                            troop.move(troopCol - 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol - 1][troopRow] = playerMove;
                            troops.insert({{troopCol - 1, troopRow}, &troop});

                        }
                    }else if(troop.type().compare("MAGE") == 0){
                        if(abs(troopCol - targetCol) <= 2 && abs(troopRow - targetRow) <= 2){
                            if(troop.isCharged){
                                projectile(troopCol, troopRow, targetCol, targetRow, LIGHTBLUE);
                                int targetHealth = target->damage(troop.getDamage());
                                troop.isCharged = false;

                                //projectile cleanup
                                LCD.Clear();
                                drawGrid();
                                for(Troop &troop : p1Troops){
                                    troop.drawTroop();
                                }
                                for(Troop &troop : p2Troops){
                                    troop.drawTroop();
                                }

                                if(targetHealth <= 0){
                                    board[targetCol][targetRow] = 0;
                                    troops.erase({targetCol, targetRow});
                                    clearSpace(targetCol, targetRow);
                                    resetSquare(targetCol, targetRow);

                                    p1Troops.remove(*target);
                                }
                            }else{
                                troop.isCharged = true;
                                troop.drawTroop();
                            }
                            
                        }else if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){
                            //move DOWN
                            troop.move(troopCol, troopRow + 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow + 1] = playerMove;
                            troops.insert({{troopCol, troopRow + 1}, &troop});

                        }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){
                            //move UP
                            troop.move(troopCol, troopRow - 1);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol][troopRow - 1] = playerMove;
                            troops.insert({{troopCol, troopRow - 1}, &troop});

                        }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                            //move RIGHT
                            troop.move(troopCol + 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol + 1][troopRow] = playerMove;
                            troops.insert({{troopCol + 1, troopRow}, &troop});

                        }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                            //move LEFT
                            troop.move(troopCol - 1, troopRow);

                            board[troopCol][troopRow] = 0;
                            troops.erase({troopCol, troopRow});

                            board[troopCol - 1][troopRow] = playerMove;
                            troops.insert({{troopCol - 1, troopRow}, &troop});

                        }
                    }else if(troop.type().compare("KNIGHT") == 0){

                        for(int i = 0; i < 2; i++){

                            if(abs(troopCol - targetCol) <= 1 && abs(troopRow - targetRow) <= 1){
                                //if within one space, attack target
                                int targetHealth = target->damage(troop.getDamage());

                                //if the targets health is below zero,
                                if(targetHealth <= 0){
                                    //remove them from the 2d coordinate array
                                    board[targetCol][targetRow] = 0;
                                    //erase them from the map
                                    troops.erase({targetCol, targetRow});
                                    //delete their sprite
                                    clearSpace(targetCol, targetRow);
                                    resetSquare(targetCol, targetRow);

                                    p1Troops.remove(*target);

                                    //Since the knight just killed its target, we should stop its turn to avoid errors
                                    break;
                                }
                                //^ this essentially 'kills' the target as there is now no reference to it anymore and will not make any action as it is not in the p2Troops vector

                                //If the target is not close enough to attack,
                            }else if(troopRow < targetRow && board[troopCol][troopRow + 1] == 0){
                                //move DOWN
                                troop.move(troopCol, troopRow + 1);

                                board[troopCol][troopRow] = 0;
                                troops.erase({troopCol, troopRow});

                                board[troopCol][troopRow + 1] = playerMove;
                                troops.insert({{troopCol, troopRow + 1}, &troop});

                                troopRow += 1;

                            }else if(troopRow > targetRow && board[troopCol][troopRow - 1] == 0){
                                //move UP
                                troop.move(troopCol, troopRow - 1);
                                
                                board[troopCol][troopRow] = 0;
                                troops.erase({troopCol, troopRow});

                                board[troopCol][troopRow - 1] = playerMove;
                                troops.insert({{troopCol, troopRow - 1}, &troop});

                                troopRow -= 1;

                            }else if(troopCol < targetCol && board[troopCol + 1][troopRow] == 0){
                                //move RIGHT
                                troop.move(troopCol + 1, troopRow);

                                board[troopCol][troopRow] = 0;
                                troops.erase({troopCol, troopRow});

                                board[troopCol + 1][troopRow] = playerMove;
                                troops.insert({{troopCol + 1, troopRow}, &troop});

                                troopCol += 1;

                            }else if(troopCol > targetCol && board[troopCol - 1][troopRow] == 0){
                                //move LEFT
                                troop.move(troopCol - 1, troopRow);

                                board[troopCol][troopRow] = 0;
                                troops.erase({troopCol, troopRow});

                                board[troopCol - 1][troopRow] = playerMove;
                                troops.insert({{troopCol - 1, troopRow}, &troop});

                                troopCol -= 1;

                            }
                            Sleep(0.07);
                        }

                    }
                    Sleep(0.1);

                    //if all enemy troops have been killed, end the turn early to avoid errors
                    if(p1Troops.size() == 0){
                        break;
                    }

                }

                playerMove = 1;
            }

            //NATE: this is where you should put win increment counter + check if either player has more than 3 wins to end the game loop and return to main menu
            if(p1Troops.size() == 0){
                //If p1 has no living troops, increment the round counter, increase the starting gold, and stop the battle stage
                round = round + 1;
                p1Gold = startingGold * round;
                p2Gold = startingGold * round;
                LCD.Clear();
                battleStarted = false;

                //Clear the array, map and the vector for p2
                memset(board, 0, sizeof(board));
                troops.clear();
                p2Troops.clear();


                //Show which player has won, and ask to play again
                LCD.SetFontColor(SCARLET);
                LCD.WriteRC("PLAYER 2 WINS", 2, 5);
                Icon playAgainButton;
                playAgainButton.SetProperties("PLAY AGAIN?", X_BOUND/2 - 50, 100, 100, 30, WHITE, SCARLET);
                playAgainButton.Draw();
                while(true){
                    if(LCD.Touch(&x, &y)){
                        if(playAgainButton.Pressed(x,y,1)){
                            break;
                        }
                    }
                }

                //Once they press play again, reset the build stage (exact same thing as above when p1 ran out of gold)
                playerMove = 1;
                LCD.Clear();
                LCD.SetFontColor(SCARLET);
                LCD.WriteRC("PLAYER 1 TURN", 6, 7);
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
                drawPlayer2Fog();

                sprintf(buffer, "%d GOLD", p1Gold);
                goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
                goldIcon.Draw();

            }else if(p2Troops.size() == 0){
                //Same thing as above but p2 has no troops, thus p1 has won
                round = round + 1;
                p1Gold = startingGold * round;
                p2Gold = startingGold * round;
                LCD.Clear();
                battleStarted = false;

                //Clear the array, map and the vector for p1
                memset(board, 0, sizeof(board));
                troops.clear();
                p1Troops.clear();

                LCD.SetFontColor(SCARLET);
                LCD.WriteRC("PLAYER 1 WINS", 2, 5);
                Icon playAgainButton;
                playAgainButton.SetProperties("PLAY AGAIN?", X_BOUND/2 - 50, 100, 100, 30, WHITE, SCARLET);
                playAgainButton.Draw();
                while(true){
                    if(LCD.Touch(&x, &y)){
                        if(playAgainButton.Pressed(x,y,1)){
                            break;
                        }
                    }
                }
                playerMove = 1;
                LCD.Clear();
                LCD.SetFontColor(SCARLET);
                LCD.WriteRC("PLAYER 1 TURN", 6, 7);
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
                drawPlayer2Fog();

                sprintf(buffer, "%d GOLD", p1Gold);
                goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
                goldIcon.Draw();
            }

        }

        //If the screen is clicked
        if(LCD.Touch(&x,&y)){

            //Back button, currently not used
            if(backButton.Pressed(x,y,0)){
                break;
            }

            //If a troop has not already been selected,
            if(!troopSelected){

                int buildingPlayersGold = 0;
                if(playerMove == 1){
                    buildingPlayersGold = p1Gold;
                }else if(playerMove == 2){
                    buildingPlayersGold = p2Gold;
                }

                //And the soldier button was pressed,
                if(buildingPlayersGold >= 1 && soldierButton.Pressed(x,y,1)){

                    //Highlight the soldier button to indicate that they have selected the soldier
                    soldierButton.SetProperties("", 20, 30, 32, 32, YELLOW, WHITE);
                    soldierButton.Draw();

                    //set selectedTroop to SOLDIER
                    selectedTroop = "SOLDIER";
                    troopSelected = true;

                    //And clear the bottom of the screen from the gold indicator, and tell the player to choose where they want to place their troop
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    LCD.SetFontColor(SCARLET);
                    LCD.WriteAt("Now choose an open space", 20, 190);

                //And the archer button was pressed
                }else if(buildingPlayersGold >= 1 && archerButton.Pressed(x,y,1)){

                    //Highlight the archer button to indicate that they have selected the archer
                    archerButton.SetProperties("", 20, 70, 32, 32, YELLOW, WHITE);
                    archerButton.Draw();

                    //set selectedTroop to ARCHER
                    selectedTroop = "ARCHER";
                    troopSelected = true;

                    //And clear the bottom of the screen from the gold indicator, and tell the player to choose where they want to place their troop
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    LCD.SetFontColor(SCARLET);
                    LCD.WriteAt("Now choose an open space", 20, 190);

                //And the mage button was pressed
                }else if(buildingPlayersGold >= 2 && mageButton.Pressed(x,y,1)){

                    //Highlight the mage button to indicate that they have selected the mage
                    mageButton.SetProperties("", 20, 110, 32, 32, YELLOW, WHITE);
                    mageButton.Draw();

                    //set selectedTroop to MAGE
                    selectedTroop = "MAGE";
                    troopSelected = true;

                    //And clear the bottom of the screen from the gold indicator, and tell the player to choose where they want to place their troop
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    LCD.SetFontColor(SCARLET);
                    LCD.WriteAt("Now choose an open space", 20, 190);

                }else if(buildingPlayersGold >= 2 && knightButton.Pressed(x,y,1)){

                    //Highlight the knight button to indicate that they have selected the knight
                    knightButton.SetProperties("", 20, 150, 32, 32, YELLOW, WHITE);
                    knightButton.Draw();

                    //set selectedTroop to KNIGHT
                    selectedTroop = "KNIGHT";
                    troopSelected = true;

                    //And clear the bottom of the screen from the gold indicator, and tell the player to choose where they want to place their troop
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    LCD.SetFontColor(SCARLET);
                    LCD.WriteAt("Now choose an open space", 20, 190);

                }
            //If a troop HAS been selected and the click is within the bounds of the grid,
            }else if((x >= leftGridPosition && x <= rightGridPosition) && (y >= topGridPosition && y <= bottomGridPosition)){

                //Calculate the row and column clicked
                int col = xToCol(x);
                int row = yToRow(y);

                //If it is player1's turn, they are clicking in their area and the space they are clicking is free
                if(playerMove == 1 && row <= 2 && board[col][row] == 0){

                    //Create a new troop at that location,
                    Troop newTroop{selectedTroop, playerMove, col, row, id++};

                    //Set it up in the 2d array, map, and vector
                    board[col][row] = playerMove;
                    p1Troops.push_back(newTroop);
                    troops.insert({{col, row}, &p1Troops.back()});

                    //Draw it on the board
                    newTroop.drawTroop();

                    //if the troop placed was a soldier,
                    if(selectedTroop.compare("SOLDIER") == 0){
                        //Unhighlight the soldier button
                        soldierButton.SetProperties("", 20, 30, 32, 32, WHITE, WHITE);
                        soldierButton.Draw();

                        //Subtract one gold
                        p1Gold -= 1;

                        //Update gold icon
                        sprintf(buffer, "%d GOLD", p1Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);

                    }else if(selectedTroop.compare("ARCHER") == 0){
                        //Unhighlight the archer button
                        archerButton.SetProperties("", 20, 70, 32, 32, WHITE, WHITE);
                        archerButton.Draw();

                        //Subtract one gold
                        p1Gold -= 1;

                        //Update gold icon
                        sprintf(buffer, "%d GOLD", p1Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);

                    }else if(selectedTroop.compare("MAGE") == 0){
                        //Unhighlight the mage button
                        mageButton.SetProperties("", 20, 110, 32, 32, WHITE, WHITE);
                        mageButton.Draw();

                        //Subtract two gold
                        p1Gold -= 2;

                        //Update gold icon
                        sprintf(buffer, "%d GOLD", p1Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);

                    }else if(selectedTroop.compare("KNIGHT") == 0){
                        //Unhighlight the mage button
                        knightButton.SetProperties("", 20, 150, 32, 32, WHITE, WHITE);
                        knightButton.Draw();

                        //Subtract two gold
                        p1Gold -= 2;

                        //Update gold icon
                        sprintf(buffer, "%d GOLD", p1Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
                    }
                    //And reset the necessary variables to allow for p1 to select another troop
                    selectedTroop = "";
                    troopSelected = false;

                    //Clear the previously written "Now choose an open space" text & redraw gold icon
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    goldIcon.Draw();

                //same thing as above but checks if it is player 2's turn and p2 is clicking within their area
                }else if(playerMove == 2 && row >= 3 && board[col][row] == 0){

                    Troop newTroop{selectedTroop, playerMove, col, row, id++};

                    board[col][row] = playerMove;
                    p2Troops.push_back(newTroop);
                    troops.insert({{col, row}, &p2Troops.back()});

                    newTroop.drawTroop();

                    //if the troop placed was a soldier,
                    if(selectedTroop.compare("SOLDIER") == 0){
                        //Unhighlight the soldier button
                        soldierButton.SetProperties("", 20, 30, 32, 32, WHITE, WHITE);
                        soldierButton.Draw();

                        //Subtract one gold
                        p2Gold -= 1;

                        //Update gold icon
                        sprintf(buffer, "%d GOLD", p2Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);

                    }else if(selectedTroop.compare("ARCHER") == 0){
                        //Unhighlight the archer button
                        archerButton.SetProperties("", 20, 70, 32, 32, WHITE, WHITE);
                        archerButton.Draw();

                        //Subtract one gold
                        p2Gold -= 1;

                        //Update gold icon
                        sprintf(buffer, "%d GOLD", p2Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);

                    }else if(selectedTroop.compare("MAGE") == 0){
                        //Unhighlight the mage button
                        mageButton.SetProperties("", 20, 110, 32, 32, WHITE, WHITE);
                        mageButton.Draw();

                        //Subtract two gold
                        p2Gold -= 2;

                        //Update gold icon
                        sprintf(buffer, "%d GOLD", p2Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);

                    }else if(selectedTroop.compare("KNIGHT") == 0){
                        //Unhighlight the mage button
                        knightButton.SetProperties("", 20, 150, 32, 32, WHITE, WHITE);
                        knightButton.Draw();

                        //Subtract two gold
                        p2Gold -= 2;

                        //Update gold icon
                        sprintf(buffer, "%d GOLD", p2Gold);
                        goldIcon.SetProperties(buffer, 20, 190, 80, 30, WHITE, GOLDENROD);
                    }

                    selectedTroop = "";
                    troopSelected = false;
                    LCD.SetFontColor(BLACK);
                    LCD.FillRectangle(0, 190, X_BOUND, Y_BOUND - 190);
                    goldIcon.Draw();
                }

                //Small cooldown for clicking so this function doesn't fire 10+ times for one click
                Sleep(0.25);
            }
            
        //IF the screen is NOT being clicked, a troop has not been selected, and the area being hovered over is on the left side of the screen(where the troop icons are)
        }else if(!LCD.Touch(&x, &y) && !troopSelected && (x >= 0 && x <= 65) && (y >= 0 && y <= Y_BOUND)){

            //And the soldier / archer button are being hovered over
            if(soldierButton.Pressed(x,y,1) || archerButton.Pressed(x,y,1)){
                //This was for visual artifacts when moving cursor fast
                hoverIcon.SetProperties("2 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();

                //Show the amount of gold the soldier and archer cost
                hoverIcon.SetProperties("1 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, WHITE, GOLDENROD);
                hoverIcon.Draw();
            //And the mage / knight button are being hovered over
            }else if(mageButton.Pressed(x,y,1) || knightButton.Pressed(x,y,1)){
                //Visual artifact fix
                hoverIcon.SetProperties("1 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, BLACK, BLACK);
                hoverIcon.Draw();

                //Show the amount of gold the mage and knight cost
                hoverIcon.SetProperties("2 GOLD", X_BOUND/2 - 80/2, 190, 80, 30, WHITE, GOLDENROD);
                hoverIcon.Draw();
            }else{
                //If you STOP hovering over an icon, hide the prices
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