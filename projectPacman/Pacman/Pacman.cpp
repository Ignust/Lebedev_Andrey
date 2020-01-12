#include <projectPacman/Tools/Types.hpp>

#include "Pacman.hpp"

//------------------------------------------------------------------------------------------
Pacman::Pacman()
    : mDescription_()
//------------------------------------------------------------------------------------------
{
    resetPosition();
}

//------------------------------------------------------------------------------------------
Pacman::~Pacman()
//------------------------------------------------------------------------------------------
{

}

//------------------------------------------------------------------------------------------
bool Pacman::move()
//------------------------------------------------------------------------------------------
{
    if (mDescription_.nextTile_ != BOUNDARY_SYMBOL) {
        switch (mDescription_.mDirection_) {
            case UP :
                mDescription_.posY_--;
                break;
            case LEFT :
                mDescription_.posX_--;
                break;
            case DOWN :
                mDescription_.posY_++;
                break;
            case RIGHT :
                mDescription_.posX_++;
                break;
            default:
                break;
        }
        return true;
    } else
        return false;
}

//------------------------------------------------------------------------------------------
void Pacman::resetPosition()
//------------------------------------------------------------------------------------------
{
    mDescription_.posX_ = START_X_PACMAN;
    mDescription_.posY_ = START_Y_PACMAN;
    mDescription_.mDirection_ = RIGHT;
    mDescription_.nextTile_ = OBJECT_EMPTY;
}

//------------------------------------------------------------------------------------------
uint8_t Pacman::getXpos()
//------------------------------------------------------------------------------------------
{
    return mDescription_.posX_;
}

//------------------------------------------------------------------------------------------
uint8_t Pacman::getYpos()
//------------------------------------------------------------------------------------------
{
    return mDescription_.posY_;
}

//------------------------------------------------------------------------------------------
void Pacman::goUp()
//------------------------------------------------------------------------------------------
{
    mDescription_.mDirection_ = UP;
}

//------------------------------------------------------------------------------------------
void Pacman::goLeft()
//------------------------------------------------------------------------------------------
{
    mDescription_.mDirection_ = LEFT;
}

//------------------------------------------------------------------------------------------
void Pacman::goDown()
//------------------------------------------------------------------------------------------
{
    mDescription_.mDirection_ = DOWN;
}

//------------------------------------------------------------------------------------------
void Pacman::goRight()
//------------------------------------------------------------------------------------------
{
    mDescription_.mDirection_ = RIGHT;
}

//------------------------------------------------------------------------------------------
void Pacman::setNextTile(uint8_t taile)
//------------------------------------------------------------------------------------------
{
    mDescription_.nextTile_ = taile;
}

