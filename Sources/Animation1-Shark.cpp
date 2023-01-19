/*
* ASCII Animation Generator
* Code By Miaad Kimiagari
* 12/28/2022
*/

# include "../Headers/Animation_Generator.h"
# include <windows.h>

using namespace std;

int main()
{
    system("pause");             // Wait for user input to start

    vector <string> fishArt = { " o                                 ",                // Source: https://www.asciiart.eu/animals/fish
                                "o      ______/~/~/~/__           /((",
                                "  o  // __            ====__    /_((",
                                " o  //  @))       ))))      ===/__((",
                                "    ))           )))))))        __((",
                                "    \\     \\)     ))))    __===\\ _((",
                                "     \\_______________====      \\_((",
                                "                                 \\((" };

    vector <string> sharkArt = { "   /  \\                                      ",    // Source: http://www.ascii-art.de/ascii/s/sharks.txt
                                    "   : ,'(                                     ",
                                    "   |( `.\\                                   ",
                                    "   : \\  `\\       \\.                       ",
                                    "    \\ `.         | `.                       ",
                                    "     \\  `-._     ;   \\                     ",
                                    "      \\     ``-.'.. _ `._                   ",
                                    "       `. `-.            ```-...__           ",
                                    "        .'`.        --..          ``-..____  ",
                                    "      ,'.-'`,_-._            ((((   <o.   ,' ",
                                    "           `' `-.)``-._-...__````  ____.-'   ",
                                    "            ,'    _,'.--,---------'          ",
                                    "           _.-' _..-'   ),'                  ",
                                    "          ``--''        `                    " };

    // Variables
    string title = "Shark VS Fish";
    int widthMargin = 7, heightMargin = 4;
    int screenWidth = Animation::getConsoleSize().first - widthMargin;
    int screenHeight = Animation::getConsoleSize().second - heightMargin;
    int sharkVelocity = 8, fishVelocity = -2;
    int refreshRate = 2;
    bool hasBeenEaten = false;

    // Objects
    Animation::ASCII_Art fish(fishArt, screenWidth, screenHeight);
    fish.setPosition(screenWidth - fish.getObjSize().first, 1);

    Animation::ASCII_Art shark(sharkArt, screenWidth, screenHeight);
    shark.setPosition(3, screenHeight - shark.getObjSize().second);

    // Main loop
    Animation::clearScreen();
    Animation::ShowConsoleCursor(false);

    while (1)
    {
        Animation::printFrame(title, screenWidth, screenHeight);

        if (!hasBeenEaten)
            fish.print();

        shark.print();

        fish.moveAlongX(fishVelocity);
        shark.moveAlongX(sharkVelocity);

        Sleep((1.0 / (float)refreshRate) * 1000);  // Convert seconds to milliseconds
        Animation::clearScreen();

        if (shark.hasCollidedWith(fish))
            hasBeenEaten = true;
    }
}