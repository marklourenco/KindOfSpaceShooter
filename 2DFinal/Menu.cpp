#include "Menu.h"
#include "raylib.h"
#include <string>

using namespace std;

void Menu::Draw() {
    string singleTxt = "play";
    string exitTxt = "exit";
    string titleTxt = "KIND OF SPACE SHOOTER";
    DrawRectangleRounded(asteroidGame, 2, 10, WHITE);
    DrawRectangleRounded(exit, 2, 10, WHITE);

    float txtWidth = MeasureText(singleTxt.c_str(), fontSize);
    txtPos = { asteroidGame.x + asteroidGame.width / 2 - txtWidth / 2,
               asteroidGame.y + asteroidGame.height / 2 - fontSize / 2 };
    DrawText(singleTxt.c_str(), txtPos.x, txtPos.y, fontSize, txtColor);

    txtWidth = MeasureText(exitTxt.c_str(), fontSize);
    txtPos = { exit.x + exit.width / 2 - txtWidth / 2,
               exit.y + exit.height / 2 - fontSize / 2 };
    DrawText(exitTxt.c_str(), txtPos.x, txtPos.y, fontSize, txtColor);

    txtWidth = MeasureText(titleTxt.c_str(), 200);
    txtPos = { exit.x + exit.width / 2 - txtWidth / 2,
               exit.y + exit.height / 2 - fontSize / 2 };
    DrawText(titleTxt.c_str(), txtPos.x + 840, 160, 80, WHITE);
}