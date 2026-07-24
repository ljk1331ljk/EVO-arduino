#ifndef EVO_H
#define EVO_H

#define EVO_LIBRARY_VERSION "2.0.0-beta"

#include "controllers/ControllerDefinition.h"
#include "controllers/SelectedController.h"
#include "controllers/EvoControllerBase.h"

#if defined(EVO_BOARD_X1E)

#include "controllers/EvoX1E.h"

#elif defined(EVO_BOARD_X1P)

#include "controllers/EvoX1P.h"

#else

#error "No EVO controller selected."

#endif

#endif
