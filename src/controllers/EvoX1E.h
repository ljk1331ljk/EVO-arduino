#ifndef EVO_X1E_H
#define EVO_X1E_H

#include "EvoControllerBase.h"

class EvoX1E : public EvoControllerBase
{
public:
    EvoX1E() : EvoControllerBase()
    {
        static_assert(
            EvoBoard::ID == EvoBoardId::X1E,
            "EvoX1E requires Evo X1E to be selected under Tools > Board."
        );
    }
};

#endif
