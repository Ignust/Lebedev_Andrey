#include<thread>
#include <istream>

#include "projectPacman/headers/Manager.hpp"
#include "projectPacman/headers/FactoryCharacter.hpp"

//------------------------------------------------------------------------------------------
Manager::Manager()
    : mField_(),
      mKeybord_(),
      //mPacman_(FactoryCharacter::create(E_CHARACTER::PACMAN)),
      mPacman_(),
      mScore_(INIT_SCORE()),
      mLives_(INIT_LIVES()),
      mSmallPoints_(SMALLPOINT_AMOUNT()),
      mMazeLevel_(INIT_MAZE_LEVEL()),
      mGameOver_(false),
      //mBlinky_(FactoryCharacter::create(E_CHARACTER::BLINKY))
      mBlinky_()
//------------------------------------------------------------------------------------------
{
    CharacterFactory factory;
    mPacman_= factory.createPacman();
    mBlinky_ = factory.createBlinky();
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
        updatePacman();
        updateGhosts();
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
    mLives_ = INIT_LIVES();
    mMazeLevel_ = INIT_MAZE_LEVEL();
    mScore_ = {INIT_SCORE()};//INIT_SCORE();
    mGameOver_ = false;
}

//------------------------------------------------------------------------------------------
void Manager::processingPressedButton()
//------------------------------------------------------------------------------------------
{
    switch (mKeybord_.getButtons()) {
    case A_Button:
    case Left_Button:
        characterGoLeft(mPacman_);
        break;
    case D_Button:
    case Right_Button:
        characterGoRight(mPacman_);
        break;
    case S_Button:
    case Down_Button:
        characterGoDown(mPacman_);
        break;
    case W_Button:
    case UP_Button:
        characterGoUp(mPacman_);
        break;
    default:
        break;
    }
}

//------------------------------------------------------------------------------------------
void Manager::wipeObject(const CHARACTER character)
//------------------------------------------------------------------------------------------
{
    mField_.setChar(character->getCoordinates(),character->getTileInMyPosition());
}

//------------------------------------------------------------------------------------------
void Manager::checkScore()
//------------------------------------------------------------------------------------------
{
    if (mField_.getChar(mPacman_->getCoordinates()) == SMALLPOINT_SYMBOL()) {
        mScore_ += SMALLPOINT_SCORE();
        mField_.printScore(mScore_);
        mSmallPoints_--;
        //std::cout << static_cast<int>(mSmallPoints_) << " ";
    }
    if (mField_.getChar(mPacman_->getNextTileCoordinates()) == ENERGIZER_SYMBOL()) {
        mScore_ += ENERGIZER_SCORE();
        mField_.printScore(mScore_);
    }
}

//------------------------------------------------------------------------------------------
void Manager::checkTunnel()
//------------------------------------------------------------------------------------------
{
    uint8_t x = mPacman_->getCoordinates().first;
    uint8_t y = mPacman_->getCoordinates().second;
    if (x == TUNNEL_1_X() && y == TUNNEL_1_Y()) {
        mPacman_->goTunnel(TUNNEL_1);
    }
    if (x == TUNNEL_2_X() && y == TUNNEL_2_Y()) {
        mPacman_->goTunnel(TUNNEL_2);
    }
}

//------------------------------------------------------------------------------------------
bool Manager::checkRotation(const COORDINATES& rotation)
//------------------------------------------------------------------------------------------
{
    return mField_.getChar(rotation) != BOUNDARY_SYMBOL();
}

//------------------------------------------------------------------------------------------
void Manager::nextLevel()
//------------------------------------------------------------------------------------------
{
    mMazeLevel_++;
    if (mMazeLevel_ > MAZE_LEVEL_AMOUNT()){
        mGameOver_ = true;
        return;
    }

    resetLevel();
}

//------------------------------------------------------------------------------------------
void Manager::resetLevel()
//------------------------------------------------------------------------------------------
{
    wipeObject(mPacman_);
    wipeObject(mBlinky_);
    mField_.resetField();
    mField_.showField();
    mPacman_->resetPosition();
    mBlinky_->resetPosition();
    mSmallPoints_ = SMALLPOINT_AMOUNT();
}

//------------------------------------------------------------------------------------------
void Manager::characterGoLeft(const CHARACTER character)
//------------------------------------------------------------------------------------------
{
    COORDINATES rotation(character->getCoordinates());
    rotation.first--;
    if (checkRotation(rotation)) {
        character->goLeft();
    }
}

//------------------------------------------------------------------------------------------
void Manager::characterGoRight(const CHARACTER character)
//------------------------------------------------------------------------------------------
{
    COORDINATES rotation(character->getCoordinates());
    rotation.first++;
    if (checkRotation(rotation)) {
        character->goRight();
    }
}

//------------------------------------------------------------------------------------------
void Manager::characterGoDown(const CHARACTER character)
//------------------------------------------------------------------------------------------
{
    COORDINATES rotation(character->getCoordinates());
    rotation.second++;
    if (checkRotation(rotation)) {
        character->goDown();
    }
}

//------------------------------------------------------------------------------------------
void Manager::characterGoUp(const CHARACTER character)
//------------------------------------------------------------------------------------------
{
    COORDINATES rotation(character->getCoordinates());
    rotation.second--;
    if (checkRotation(rotation)) {
        character->goUp();
    }
}

//------------------------------------------------------------------------------------------
void Manager::updatePacman()
//------------------------------------------------------------------------------------------
{
    updateCharacterDirection(mPacman_);
    wipeObject(mPacman_);
    if (mPacman_->move()) {
        checkCollisionWithCharacters(mPacman_);
        checkScore();
        checkTunnel();
    }
    drawCharacter(mPacman_);
}

//------------------------------------------------------------------------------------------
void Manager::updateGhosts()
//------------------------------------------------------------------------------------------
{
    COORDINATES BlinkyCoor = mBlinky_->getCoordinates();

    bool canGoUp = (BOUNDARY_SYMBOL() != mField_.getChar(BlinkyCoor.first,BlinkyCoor.second - 1));
    bool canGoDown = (BOUNDARY_SYMBOL() != mField_.getChar(BlinkyCoor.first,BlinkyCoor.second +1));
    bool canGoLeft = (BOUNDARY_SYMBOL() != mField_.getChar(BlinkyCoor.first - 1,BlinkyCoor.second));
    bool canGoRight = (BOUNDARY_SYMBOL() != mField_.getChar(BlinkyCoor.first + 1,BlinkyCoor.second));

    wipeObject(mBlinky_);
    mBlinky_->makeMove(canGoUp, canGoDown, canGoLeft, canGoRight);
    checkCollisionWithCharacters(mBlinky_);
    drawCharacter(mBlinky_);
/*
    updateCharacterDirection(mBlinky_);
    wipeObject(mBlinky_);
    while (!mBlinky_->move()) {
        updateCharacterDirection(mBlinky_);
    }
    checkCollisionWithCharacters(mBlinky_);
    drawCharacter(mBlinky_);
*/
}

//------------------------------------------------------------------------------------------
void Manager::drawCharacter(const CHARACTER character)
//------------------------------------------------------------------------------------------
{
    if (character->getPrintSymbol() != PACMAN_SYMBOL()) {
        character->setTileInMyPosition(mField_.getChar(character->getCoordinates()));
    }
    mField_.setChar(character->getCoordinates(), character->getPrintSymbol());
}

//------------------------------------------------------------------------------------------
void Manager::updateCharacterDirection(const CHARACTER character)
//------------------------------------------------------------------------------------------
{
    character->setNextTile(mField_.getChar(character->getNextTileCoordinates()));
}

//------------------------------------------------------------------------------------------
void Manager::checkCollisionWithCharacters(const CHARACTER character)
//------------------------------------------------------------------------------------------
{
    if (character->getPrintSymbol() == PACMAN_SYMBOL()) {
        if (mField_.getChar(character->getCoordinates()) == BLINKY_SYMBOL()) {
            decrementLives();
        }
    } else {
        if (mField_.getChar(character->getCoordinates()) == PACMAN_SYMBOL()) {
            decrementLives();
            character->setTileInMyPosition(OBJECT_EMPTY());
        }
    }
}

//------------------------------------------------------------------------------------------
void Manager::decrementLives()
//------------------------------------------------------------------------------------------
{
    mLives_--;
    mField_.printLives(mLives_);
    if (!mLives_){
        mGameOver_ = true;
    }
    resetLevel();
}


