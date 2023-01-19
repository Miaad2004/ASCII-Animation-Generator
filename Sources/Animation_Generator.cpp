/*
* ASCII Animation Generator
* Code By Miaad Kimiagari
* 12/28/2022
*/

# include <vector>
# include <string>
# include <iostream>
# include <math.h>
# include <windows.h>

# include "../Headers/Animation_Generator.h"


using namespace std;

namespace Animation {
    void moveCurser(int dX, int dY)
    {
        for (int i = 0; i < dY; i++)
            cout << endl;

        cout << "||";
        for (int i = 0; i < dX; i++)
            cout << " ";
    }

    void printChar(char character, int howMany)
    {
        for (int i = 0; i < howMany; i++)
            cout << character;
    }

    void printFrame(string& title, int screenWidth, int screenHeight)
    {
        printChar(' ', (screenWidth - title.size()) / 2);
        cout << title;
        printChar(' ', (screenWidth / 2 - title.size() / 2));
        printChar('\n', 1);

        printChar('=', screenWidth + 4);

        for (int i = 0; i < screenHeight + 1; i++)
        {
            cout << "\n" << "||";
            printChar(' ', screenWidth + 1);
            cout << "||";
        }

        printChar('\n', 2);
        printChar('=', screenWidth + 4);
    }

    void resetCurser()
    {
        // Source: https://stackoverflow.com/questions/15770853/how-to-use-setconsolecursorposition-func
        COORD coord;
        coord.X = 2;
        coord.Y = 2;
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsole, coord);
    }

    void clearScreen()
    {
        system("cls");
    }

    pair <int, int> getConsoleSize()
    {
        // Source: https://stackoverflow.com/questions/6812224/getting-terminal-size-in-c-for-windows/12642749#12642749
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        int width, height;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        pair <int, int> consoleSize = { width, height };

        return consoleSize;
    }

    void ShowConsoleCursor(bool showFlag)
    {
        // Source: https://stackoverflow.com/questions/18028808/remove-blinking-underscore-on-console-cmd-prompt
        HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_CURSOR_INFO     cursorInfo;

        GetConsoleCursorInfo(out, &cursorInfo);
        cursorInfo.bVisible = showFlag; // set the cursor visibility
        SetConsoleCursorInfo(out, &cursorInfo);
    }


    ASCII_Art::ASCII_Art(vector <string> art, int screenWidth, int screenHeight)
    {
        this->Art = art;
        this->ScreenWidth = screenWidth;
        this->ScreenHeight = screenHeight;
        calObjectSize();
    }

    void ASCII_Art::swapDirection(Direction& dir)
    {
        if (dir == forward)
            dir = backward;

        else
            dir = forward;
    }

    void ASCII_Art::calObjectSize()
    {
        // Calculate height
        ObjHeight = Art.size();

        // Calculate width
        int maxWidth = 0;
        for (auto row : Art)
            if (row.size() > maxWidth)
                maxWidth = row.size();

        ObjWidth = maxWidth;
    }

    pair <int, int> ASCII_Art::getObjSize()
    {
        pair <int, int> objSize = { ObjWidth, ObjHeight };
        return objSize;
    }

    void ASCII_Art::setPosition(int x, int y)
    {
        PosX = x;
        PosY = y;
        if (y <= 10)
            this->VerticalDirection = forward;

        else
            this->VerticalDirection = backward;
    }

    pair <int, int> ASCII_Art::getPos()
    {
        pair <int, int> position = { PosX, PosY };
        return position;
    }

    void ASCII_Art::moveAlongY(int dY)
    {
        if (PosY < 0 || PosY + ObjHeight + (dY * VerticalDirection)> ScreenHeight)
            swapDirection(VerticalDirection);

        PosY += dY * VerticalDirection;
    }

    void ASCII_Art::moveAlongX(int dX)
    {
        if (PosX < 0 || PosX + ObjWidth + (dX * HorizontalDirection) > ScreenWidth)
        {
            swapDirection(PrintDirection);
            swapDirection(HorizontalDirection);
            moveAlongY(ObjHeight);
        }

        PosX += dX * HorizontalDirection;
    }

    void ASCII_Art::print()
    {
        resetCurser();
        moveCurser(PosX, PosY);

        for (auto row : Art)
        {
            if (PrintDirection == backward)
                for (auto itr = row.rbegin(); itr != row.rend(); itr++)
                    cout << *itr;

            else
                for (auto character : row)
                    cout << character;

            moveCurser(PosX, 1);        // Move curser 1 line down
        }
    }

    bool ASCII_Art::hasCollidedWith(ASCII_Art obj)
    {
        if (abs(PosY - obj.getPos().second) <= 5 && PosX > obj.getPos().first)
            return true;
        return false;
    }
}