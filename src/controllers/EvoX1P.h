#ifndef EVO_X1P_H
#define EVO_X1P_H

#include "EvoControllerBase.h"

class EvoX1P : public EvoControllerBase
{
public:
    EvoX1P() : EvoControllerBase()
    {
        static_assert(
            EvoBoard::ID == EvoBoardId::X1P,
            "EvoX1P requires Evo X1P to be selected under Tools > Board.");
    }
};

#endif
