#ifndef EVO_SELECTED_CONTROLLER_H
#define EVO_SELECTED_CONTROLLER_H
#include "ControllerDefinition.h"
#if defined(EVO_BOARD_X1E) && defined(EVO_BOARD_X1P)
#error "Multiple EVO controllers selected."
#elif defined(EVO_BOARD_X1E)
class EvoX1E;
using SelectedEvoController = EvoX1E;
#elif defined(EVO_BOARD_X1P)
class EvoX1P;
using SelectedEvoController = EvoX1P;
#else
#error "No EVO controller selected. Define EVO_BOARD_X1E or EVO_BOARD_X1P."
#endif
#endif
