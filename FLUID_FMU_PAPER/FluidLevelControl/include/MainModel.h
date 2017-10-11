/**
 * Header file for the MainModel model
 * Generated by the TERRA Arch2LUNA generator version 1.0.1
 *
 * protected region document description on begin
 *
 * protected region document description end
 */

#pragma once

#include "csp/CSP.h"

// Models
#include "LevelController/LevelController.h"
#include "plant/plant.h"

using namespace LUNA::CSP;

namespace MainModel { 

class MainModel : public Recursion<CSProcess>
{

public:
  // Define constructor and destructor
  MainModel();
  virtual ~MainModel();

private:

  // Channel definitions
  UnbufferedChannel<double, One2In, Out2One> *myLevelControllerout_to_plantcontrolChannel;
  UnbufferedChannel<double, One2In, Out2One> *myplantheight_to_LevelControllerinChannel;

  // Model objects
  LevelController::LevelController *myLevelController;
  plant::plant *myplant;

  // Model groups
  Parallel *parallelGroup;
};

// Close namespace(s)
} 
