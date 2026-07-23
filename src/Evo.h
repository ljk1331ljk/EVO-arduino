#ifndef EVO_H
#define EVO_H

#define LIBRARY_VERSION "2.0.0-beta"

#include "boards/SelectedBoard.h"

#include "controllers/EvoControllerBase.h"
#include "controllers/EvoX1E.h"
#include "controllers/EvoX1P.h"

#include "helper/EvoHC05.h"
#include "helper/OTAHandler.h"
#include "helper/EvoPWMDriver.h"

#include "motors/EvoMotor.h"
#include "motors/EvoServo.h"

#include "robotics/EvoMotorPair.h"
#include "robotics/EvoTrace.h"

#include "sensors/EV3ColorSensor.h"
#include "sensors/EV3TouchSensor.h"
#include "sensors/EvoRGBColorSensor.h"
#include "sensors/EvoTOF.h"
#include "sensors/EvoIMU.h"
#include "sensors/EvoHuskyLens.h"
#include "sensors/EvoOLED.h"
#include "sensors/EvoLineLeader.h"
#include "sensors/EvoTriButton.h"

#endif
