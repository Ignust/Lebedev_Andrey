#include <conio.h>

#include "projectPacman/headers/Keybord.hpp"

//------------------------------------------------------------------------------------------
Keybord::Keybord()
//------------------------------------------------------------------------------------------
{

}

//------------------------------------------------------------------------------------------
Keybord::~Keybord()
//------------------------------------------------------------------------------------------
{

}

//------------------------------------------------------------------------------------------
bool Keybord::checkButtons()
//------------------------------------------------------------------------------------------
{
    return _kbhit();
}

//------------------------------------------------------------------------------------------
uint32_t Keybord::getButtons()
//------------------------------------------------------------------------------------------
{
    return getch();
}
