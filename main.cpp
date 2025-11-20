#include "FEHLCD.h"
#include "FEHUtility.h"
#define GOLDEN_RATIO 1.618
#define X_BOUND 319
#define Y_BOUND 239
using namespace FEHIcon;

//window x bounds : (0,319)
//window y bounds : (0, 239)

void drawMainMenu(){
    int height = 40;
    int width = 150;
    int centerPosition = X_BOUND/2 - width/2;
    Icon playButton;
    Icon instructionsButton;
    Icon statButton;
    Icon creditsButton;

    playButton.SetProperties("Play", centerPosition, 10, width, height, WHITE, RED);
    instructionsButton.SetProperties("Instructions", centerPosition, 70, width, height, WHITE, BLUE);
    statButton.SetProperties("Statistics", centerPosition, 130, width, height, WHITE, GREEN);
    creditsButton.SetProperties("Credits", centerPosition, 190, width, height, WHITE, YELLOW);

    playButton.Draw();
    instructionsButton.Draw();
    statButton.Draw();
    creditsButton.Draw();
    
}

int main()
{
    drawMainMenu();
    return 0;
}