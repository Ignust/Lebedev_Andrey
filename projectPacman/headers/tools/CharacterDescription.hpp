#ifndef CHARACTERDESCRIPTION_HPP
#define CHARACTERDESCRIPTION_HPP

#include <cstdint>
#include <iostream>

enum E_DIRECTION {
     UP =       0
    , LEFT =    1
    , DOWN =    2
    , RIGHT =   3
};

struct CharacterDescription {
    E_DIRECTION mDirection_;
    uint8_t tileInMyPosition;
    std::pair<uint8_t,uint8_t> mCoordinates_;
    uint8_t mPrintSymbol_;
};

#endif // CHARACTERDESCRIPTION_HPP
