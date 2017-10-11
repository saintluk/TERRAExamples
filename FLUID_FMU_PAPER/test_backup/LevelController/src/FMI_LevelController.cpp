/**
 * Source file for the FMI_LevelController model
 * Generated by the TERRA CSPm2LUNA generator version 1.1.3
 *
 * FMI C++ glue code to connect to LevelController
 * Modifying this file is absolutely not recommended!
 *
 * protected region document description on begin
 *
 * protected region document description end
 */

#include "FMI_LevelController.h"
// protected region additional headers on begin
// Each additional header should get a corresponding dependency in the Makefile
#include "xxmodel.h"
// protected region additional headers end

namespace LevelController { namespace FMI_LevelController { 

FMI_LevelController::FMI_LevelController(double &in, double &out, fmi2FMUstate &FMUstate) :
    CodeBlock(), in(in), out(out), FMUstate(FMUstate){
  SETNAME(this, "FMI_LevelController");

// Create the text for the header of the measurement log
std::string measurementNames = "Time,in,out";
  
// Initialization of the log functions
logger->initLogger("measurement_LevelController.csv","log.txt",measurementNames);

// Load shared lib
handle = dlopen("/usr/local/lib/libSOLevelController.so",RTLD_LAZY);

// Instantiation of the FMU
f_instantiate = (fp_instantiate)dlsym(handle,"fmi2Instantiate");
s1 = f_instantiate("LevelController", fmi2CoSimulation,"{d6f9df54-1689-46cc-b366-77379034dd53}", "", &cbf, fmi2True, fmi2False);
if(s1 == NULL)
{
   logger->fmiLog(NULL, "LevelController", fmi2Error, "error", "fmi2Instatiate is not created.");
}  
else
{
   logger->fmiLog(NULL, "LevelController", fmi2OK, "info","fmi2Instatiate is created correctly.");
}

// Set variables for simulation
timeStep = 0.001;
currentTime = 0.0;
status = fmi2OK;
simulationFinished = false;

fmi2ValueReference parameterRealRef[6] = {0,1,2,3,4,5};
fmi2Real parameterRealVal[6] = {1.5,10.0,0.5,0.0,0.0,1.5};
fmi2SetReal(s1,parameterRealRef,6,parameterRealVal);

f_setup = (fp_setup)dlsym(handle,"fmi2SetupExperiment");
f_setup(s1,fmi2False, 0.0, 0.0, fmi2True, 20.0);

f_enterInit = (fp_enterInit)dlsym(handle,"fmi2EnterInitializationMode");
f_enterInit(s1);

//f_exit = (fp_exit)dlsym(handle,"fmi2ExitInitializationMode");
//f_exit(s1);

fmi2ValueReference outputRealRef[1] = {15};
fmi2Real outputRealVal[1] = {0};
fmi2GetReal(s1,outputRealRef,1,outputRealVal);
out = outputRealVal[0];

//printf("init out is %f\n", out);

}

FMI_LevelController::~FMI_LevelController()
{
fmi2Terminate(s1);
fmi2FreeInstance(s1);
}

void FMI_LevelController::execute()
{
static long long i = 0;

//skip 1st iteration, to sync initial states
if (i++ == 0){
	fmi2ValueReference inputRealRef[1] = {14};
	fmi2Real inputRealVal[1] = {in};
	fmi2SetReal(s1,inputRealRef,1,inputRealVal);

	f_exit = (fp_exit)dlsym(handle,"fmi2ExitInitializationMode");
	f_exit(s1);

	fmi2ValueReference outputRealRef[1] = {15};
	fmi2Real outputRealVal[1] = {0};
	fmi2GetReal(s1,outputRealRef,1,outputRealVal);
	out = outputRealVal[0];

	printf("init out is %f\n", out);
}
else
{
	if(simulationFinished == false && status == fmi2OK)
	{

	  fmi2ValueReference inputRealRef[1] = {14};
	  fmi2Real inputRealVal[1] = {in};
	  fmi2SetReal(s1,inputRealRef,1,inputRealVal);

	  // Save the values of the input and output to a file
	   logger->saveMeasurementPoint(std::to_string(currentTime) + "," + std::to_string(in) + "," + std::to_string(out));


	  //insert event, tune parameter -> reference amplitude when currentTime == 10.0
	  if(currentTime > 9.9999)
	  {
		  fmi2ValueReference parameterRealRef[1] = {4};
		  fmi2Real parameterRealVal[1] = {1.0};
		  fmi2SetReal(s1,parameterRealRef,1,parameterRealVal);
	  }

	  //change integration step size to 0.01, too large, response too slow at 10.01
	  //((xx_ModelInstance*)s1)->step_size = 0.01;


	  if(currentTime < 20.0)
	  {
	    fmi2GetFMUstate(s1, &FMUstate);
	    printf("FMUstate time is %f\n", ((xx_ModelInstance*)s1)->time);

	  	f_doStep = (fp_doStep)dlsym(handle,"fmi2DoStep");
	    if(f_doStep(s1,currentTime,timeStep,fmi2True) != fmi2OK)
	    {
	      printf("FMI: Error no simulation\n");
	    }


	    fmi2ValueReference outputRealRef[1] = {15};
	    fmi2Real outputRealVal[1] = {0};
	    fmi2GetReal(s1,outputRealRef,1,outputRealVal);
	    out = outputRealVal[0];// + eventAdding;

	    currentTime = currentTime + timeStep;

	    fmi2SetFMUstate(s1, FMUstate);
		printf("Restored time is %f\n", ((xx_ModelInstance*)s1)->time);

	  }
	  else
	  {
	    simulationFinished = true;
	  }
	}
	else if(status != fmi2OK)
	{
	  printf("FMU: The simulation is stopped because of an error\n");
	  exit();
	}
	else
	{
	  printf("FMU: Simulation is done\n");
	  fmi2Terminate(s1);
	  fmi2FreeInstance(s1);
	  exit();
	}
 }

}

// protected region additional functions on begin
// protected region additional functions end

// Close namespace(s)
} } 
