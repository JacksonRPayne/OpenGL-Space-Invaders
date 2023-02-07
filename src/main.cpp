#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Game.h"

int main()
{
    Game game(SCREEN_START_WIDTH, SCREEN_START_HEIGHT);
    game.Run("Michael Z!");
    return 0;
}