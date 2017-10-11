/* ---------------------------------------------------------------------------
** This software is made for using in combination with the FMI component in 
** Terra. 
**
** logging.cpp
** This file contains the implementation of the log funtions which are used by
** by the FMI component in TERRA. In total when using these functions, two 
** different files are generated. One file contains information about the 
** status of the FMI. The other file contains the values which are send through 
** the FMI.
**
** Author: K.J. Kok
** Version: 1.0 (27-05-16)
** -------------------------------------------------------------------------*/

#include "logger.h"
#include <cstdarg>
#include <ctime>

using namespace std;

std::string FMILogger_LevelController::_fileNameSimulationLog;
std::string FMILogger_LevelController::_fileNameSystemLog;

FMILogger_LevelController::FMILogger_LevelController(void)
{

}

FMILogger_LevelController::~FMILogger_LevelController(void)
{
}

void FMILogger_LevelController::initLogger(std::string fileNameSimulationLog, std::string fileNameSystemLog,std::string measurementNames)
{
	// Set the variables
	_fileNameSimulationLog = fileNameSimulationLog;
	_fileNameSystemLog = fileNameSystemLog;

	// Open the file with the measurements
	FILE * measurementFile;
	measurementFile = fopen(fileNameSimulationLog.c_str(),"w");

	// Write measurement header names to file
	fprintf(measurementFile,"%s\n",measurementNames.c_str());

	// Close the file
	fclose(measurementFile);
}

void FMILogger_LevelController::fmiLog(fmi2ComponentEnvironment componentEnvironment, fmi2String instanceName, fmi2Status status, fmi2String category, fmi2String message, ...)
{
	// Save system time for logging
	time_t current_time = time(NULL);
	char* c_time_string;
	c_time_string = strtok(ctime(&current_time),"\n"); // Remove the end line character

	// Open the file and write at the end of the file
	FILE * _systemLog;
	_systemLog = fopen(_fileNameSystemLog.c_str(),"a");

	// Print message on screen and in the log file
	fprintf(stderr,"%s [%s] Instance '%s' in environment '%p' with status '%s' gives the following message: ", c_time_string,category,instanceName, componentEnvironment, enumStatusToString(status));
	fprintf(_systemLog,"%s [%s] Instance '%s' in environment '%p' with status '%s' gives the following message: " ,c_time_string,category,instanceName, componentEnvironment, enumStatusToString(status));
	
	// Print the message with variables on the screen and in the file
	va_list argptr;
	va_start(argptr, message);
	vfprintf(stderr,message,argptr);
	vfprintf(_systemLog,message,argptr);
	va_end(argptr);
	
	// Print a new line on the screen and in the file
	fprintf(stderr,"\n");
	fprintf(_systemLog,"\n");

	// Close file
	fclose(_systemLog);
}

void FMILogger_LevelController::saveMeasurementPoint(std::string measurementValues)
{
	// Open the file with the measurements and put the new data on the end of the file
	FILE * measurementFile;
	measurementFile = fopen(_fileNameSimulationLog.c_str(),"a");

	// Print the last variable with a new line in the file
	fprintf(measurementFile,"%s\n",measurementValues.c_str());

	// Close the file
	fclose(measurementFile);

}


fmi2String FMILogger_LevelController::enumStatusToString(fmi2Status status)
{
	fmi2String tempString;
	switch(status) 
  	{
  		case fmi2OK: tempString = "fmi2OK"; break;
  		case fmi2Warning: tempString = "fmi2Warning"; break;
  		case fmi2Discard: tempString = "fmi2Discard"; break;
  		case fmi2Error: tempString = "fmi2Error"; break;
  		case fmi2Fatal: tempString = "fmi2Fatal"; break;
  		case fmi2Pending: tempString = "fmi2Pending"; break;
  		default: tempString = "unknown"; break;
  	}
  	return tempString;
 }


