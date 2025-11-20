#include "FEHLCD.h"

int main()
{
    LCD.WriteLine("Hello World!");
    int counter = 1;
    while (1) {
        LCD.Update();
        LCD.WriteLine(counter);
        counter++;
        // Never end
    }
    return 0;
}