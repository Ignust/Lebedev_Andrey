#include <iostream>
#include <windows.h>
#include <thread>

#include "projectPacman/headers/PacmanMachine.hpp"
#include "projectPacman/headers/Timer.hpp"

constexpr uint8_t SPEED(){return 240;}

//------------------------------------------------------------------------------------------
PacmanMachine::PacmanMachine()
    : mManager_()
//------------------------------------------------------------------------------------------
{

}

//------------------------------------------------------------------------------------------
PacmanMachine::~PacmanMachine()
//------------------------------------------------------------------------------------------
{

}

//------------------------------------------------------------------------------------------
void PacmanMachine::run()
//------------------------------------------------------------------------------------------
{
    showMenu();
}

//------------------------------------------------------------------------------------------
void PacmanMachine::showMenu()
//------------------------------------------------------------------------------------------
{
    int selectOption = 0;
    std::cout << "1. Start Game \n"
                 "2. Show Statistics \n"
                 "3. Quit\n\n\n"
                 "Select option:" << std::endl;
    std::cin >>  selectOption;
    system("cls");
    switch (selectOption) {
        case 1 :
            startGame();
            break;
        case 2 :
            showStatistics();
            break;
        case 3 :
            quitProgram();
            break;
        default:
            std::cout << "invalid option" << std::endl;
            system("pause");
            system("cls");
            showMenu();
            break;
    }
    showMenu();
}

//------------------------------------------------------------------------------------------
void PacmanMachine::startGame()
//------------------------------------------------------------------------------------------
{
    utils::Timer timer;

    mManager_.showField();
    system("pause");
    timer.start(std::chrono::milliseconds(SPEED()),[this](){ mManager_.update();});
    while (!mManager_.gameOver()) {
        mManager_.checkUserAction();
        //mManager_.update();
    }
    timer.stop();
    mManager_.resetGame();

    system("cls");
    std::cout << "GAME OVER" << std::endl;
    system("pause");
    system("cls");
}

//------------------------------------------------------------------------------------------
void PacmanMachine::showStatistics()
//------------------------------------------------------------------------------------------
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//------------------------------------------------------------------------------------------
void PacmanMachine::addPlayerToDatatbase()
//------------------------------------------------------------------------------------------
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

//------------------------------------------------------------------------------------------
void PacmanMachine::quitProgram()
//------------------------------------------------------------------------------------------
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    exit(0);
}

