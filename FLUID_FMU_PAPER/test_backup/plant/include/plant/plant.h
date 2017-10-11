/**
 * Header file for the plant model
 * Generated by the TERRA CSPm2LUNA generator version 1.1.3
 *
 * protected region document description on begin
 *
 * protected region document description end
 */

#pragma once

#include "csp/CSP.h"

// Models
#include "FMI_plant.h"

// protected region additional headers on begin
// Each additional header should get a corresponding dependency in the Makefile
// protected region additional headers end

using namespace LUNA::CSP;

namespace plant { 

class plant : public Sequential
{

public:
  // Define constructor and destructor
  plant(ChannelOut<double> *control, ChannelIn<double> *height);
  virtual ~plant();

private:

  // Class variables
  double v_control;
  double v_height;

  // Model objects
  FMI_plant::FMI_plant *myFMI_plant;
  Reader<double> *myr_control;
  Writer<double> *myw_height;

  // Model groups
  Parallel *myIO;



  // protected region additional class members or functions on begin
  // protected region additional class members or functions end
};

// Close namespace(s)
} 
