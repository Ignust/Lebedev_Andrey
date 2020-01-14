#include<thread>
#include <istream>

#include "Manager.hpp"

//------------------------------------------------------------------------------------------
Manager::Manager()
    : mField_(),
      mKeybord_(),
      mPacman_(),
      mScore_(0),
      mLives_(INIT_LIVES),
      mSmallPoints_(SMALLPOINT_AMOUNT),
      mMazeLevel_(INIT_MAZE_LEVEL),
      mGameOver_(false)
//------------------------------------------------------------------------------------------
{

}

//------------------------------------------------------------------------------------------
Manager::~Manager()
//------------------------------------------------------------------------------------------
{

}

//------------------------------------------------------------------------------------------
void Manager::checkUserAction()
//------------------------------------------------------------------------------------------
{
    if (mKeybord_.checkButtons()) {
        processingPressedButton();
    }
}

//------------------------------------------------------------------------------------------
void Manager::update()
//------------------------------------------------------------------------------------------
{
    //std::this_thread::sleep_for(std::chrono::milliseconds(30));
    if (mSmallPoints_ > 0) {
        updatePacmanDirection();
        wipeObject(mPacman_.getCoordinates());
        if (mPacman_.move()) {
            checkScore();
            checkTunnel();
            //updatePacmanDirection();
        }
        drawPacman();
    } else {
        nextLevel();
    }
}

//------------------------------------------------------------------------------------------
void Manager::showField()
//------------------------------------------------------------------------------------------
{
    mField_.printScore(mScore_);
    mField_.printLives(mLives_);
    mField_.showField();

}

//------------------------------------------------------------------------------------------
bool Manager::gameOver()
//------------------------------------------------------------------------------------------
{
    return mGameOver_;
}

//------------------------------------------------------------------------------------------
void Manager::resetGame()
//------------------------------------------------------------------------------------------
{
    resetLevel();
    mLives_ = INIT_LIVES;
    mMazeLevel_ = INIT_MAZE_LEVEL;
    mGameOver_ = false;
}

//------------------------------------------------------------------------------------------
void Manager::drawPacman()
//------------------------------------------------------------------------------------------
{
    mField_.setChar(mPacman_.getCoordinates(),PACMAN_SYMBOL);
}

//------------------------------------------------------------------------------------------
void Manager::processingPressedButton()
//------------------------------------------------------------------------------------------
{
    COORDINATES rotation(mPacman_.getCoordinates());
    switch (mKeybord_.getButtons()) {
    case A_Button:
    case Left_Button:
        rotation.first--;
        if (checkRotation(rotation)) {
            mPacman_.goLeft();
            //updatePacmanDirection();

        }
        break;
    case D_Button:
    case Right_Button:
        rotation.first++;
        if (checkRotation(rotation)) {
            mPacman_.goRight();
            //updatePacmanDirection();

        }
        break;
    case S_Button:
    case Down_Button:
        rotation.second++;
        if (checkRotation(rotation)) {
            mPacman_.goDown();
            //updatePacmanDirection();

        }
        break;
    case W_Button:
    case UP_Button:
        rotation.second--;
        if (checkRotation(rotation)) {
            mPacman_.goUp();
            //updatePacmanDirection();

        }
        break;
    default:
        break;
    }
}

//------------------------------------------------------------------------------------------
void Manager::wipeObject(const COORDINATES coord)
//------------------------------------------------------------------------------------------
{
    mField_.setChar(coord,OBJECT_EMPTY);
}

//------------------------------------------------------------------------------------------
void Manager::updatePacmanDirection()
//------------------------------------------------------------------------------------------
{
    mPacman_.setNextTile(mField_.getChar(mPacman_.getNextTileCoordinates()));
}

//------------------------------------------------------------------------------------------
void Manager::checkScore()
//------------------------------------------------------------------------------------------
{
    if (mField_.getChar(mPacman_.getNextTileCoordinates()) == SMALLPOINT_SYMBOL) {
        mScore_ += 10;
        mField_.printScore(mScore_);
        mSmallPoints_--;
        //std::cout << static_cast<int>(mSmallPoints_) << " ";
    }
    if (mField_.getChar(mPacman_.getNextTileCoordinates()) == ENERGIZER_SYMBOL) {
        mScore_ += 50;
        mField_.printScore(mScore_);
    }
}

//------------------------------------------------------------------------------------------
void Manager::checkTunnel()
//------------------------------------------------------------------------------------------
{
    uint8_t x = mPacman_.getCoordinates().first;
    uint8_t y = mPacman_.getCoordinates().second;
    if (x == TUNNEL_1_X && y == TUNNEL_1_Y) {
        mPacman_.goTunnel(TUNNEL_1);
    }
    if (x == TUNNEL_2_X && y == TUNNEL_2_Y) {
        mPacman_.goTunnel(TUNNEL_2);
    }
}

//------------------------------------------------------------------------------------------
bool Manager::checkRotation(const COORDINATES rotation)
//------------------------------------------------------------------------------------------
{
    if (mField_.getChar(rotation) != BOUNDARY_SYMBOL) {
        return true;
    }
    return  false;
}

//------------------------------------------------------------------------------------------
void Manager::nextLevel()
//------------------------------------------------------------------------------------------
{
    mMazeLevel_++;
    if (mMazeLevel_ > MAZE_LEVEL_AMOUNT){
        mGameOver_ = true;
        return;
    }

    resetLevel();
}

//------------------------------------------------------------------------------------------
void Manager::resetLevel()
//------------------------------------------------------------------------------------------
{
    wipeObject(mPacman_.getCoordinates());
    mField_.resetField();
    mField_.showField();
    mPacman_.resetPosition();
    mSmallPoints_ = SMALLPOINT_AMOUNT;
}
