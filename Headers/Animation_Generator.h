# pragma once
# include <vector>
# include <string>
# include <iostream>


namespace Animation {
    void moveCurser(int dX, int dY);

    void printChar(char character, int howMany);

    void printFrame(std::string& title, int screenWidth, int screenHeight);

    void resetCurser();

    void clearScreen();

    std::pair <int, int> getConsoleSize();

    void ShowConsoleCursor(bool showFlag);

    class ASCII_Art
    {
    private:
        std::vector <std::string> Art;
        int ScreenWidth, ScreenHeight;
        int PosX, PosY;
        int ObjWidth, ObjHeight;

        enum Direction
        {
            forward = 1, backward = -1
        };

        Direction PrintDirection = forward;
        Direction VerticalDirection;
        Direction HorizontalDirection = forward;

    public:
        ASCII_Art(std::vector <std::string> art, int screenWidth, int screenHeight);

        void swapDirection(Direction& dir);

        void calObjectSize();

        std::pair <int, int> getObjSize();

        void setPosition(int x, int y);

        std::pair <int, int> getPos();

        void moveAlongY(int dY);

        void moveAlongX(int dX);

        void print();

        bool hasCollidedWith(ASCII_Art obj);
    };

}