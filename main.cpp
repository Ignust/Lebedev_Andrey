#include <windows.h>

#include <projectPacman/PacmanMachine/PacmanMachine.hpp>

int main()
{
    std::system("mode con cols=40 lines=40");
    PacmanMachine game;
    game.run();

    return 0;
}
