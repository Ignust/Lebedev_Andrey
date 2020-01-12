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
                mDescription_.mCoordinates_.second--;
                break;
            case LEFT :
                mDescription_.mCoordinates_.first--;
                break;
            case DOWN :
                mDescription_.mCoordinates_.second++;
                break;
            case RIGHT :
                mDescription_.mCoordinates_.first++;
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
    mDescription_.mDirection_ = RIGHT;
    mDescription_.nextTile_ = OBJECT_EMPTY;
    mDescription_.mCoordinates_.first = START_X_PACMAN;
    mDescription_.mCoordinates_.second = START_Y_PACMAN;
}

//------------------------------------------------------------------------------------------
COORDINATES Pacman::getCoordinates()
//------------------------------------------------------------------------------------------
{
    return mDescription_.mCoordinates_;
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

//------------------------------------------------------------------------------------------
COORDINATES Pacman::getNextTileCoordinates()
//------------------------------------------------------------------------------------------
{
    COORDINATES nextTaile (mDescription_.mCoordinates_);
    if (mDescription_.mDirection_ == LEFT) {
        nextTaile.first--;
    }
    if (mDescription_.mDirection_ == RIGHT) {
        nextTaile.first++;
    }
    if (mDescription_.mDirection_ == UP) {
        nextTaile.second--;
    }
    if (mDescription_.mDirection_ == DOWN) {
        nextTaile.second++;
    }
    return nextTaile;
}

