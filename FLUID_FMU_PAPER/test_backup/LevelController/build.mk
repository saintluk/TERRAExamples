# build.mk file for LevelController.cspm, provide information to 'project MakeFile' 
# Generated by the TERRA CSPm2LUNA generator version 1.1.3
#
# protected region document description on begin
# protected region document description end

TARGETS+=lib/libLevelController.a

LevelController/lib/libLevelController.a:
	@echo
	@echo "Building $@"
	@make -C LevelController --no-print-directory

lib/libLevelController.a: LevelController/lib/libLevelController.a | lib
	@cp $^ $@
	@echo "Build $@"

# Additional dependencies to ensure that lib/libLevelController.a gets properly rebuild
LevelController/lib/libLevelController.a: LevelController/src/LevelController.cpp LevelController/include/LevelController/LevelController.h
LevelController/lib/libLevelController.a: LevelController/src/FMI_LevelController.cpp LevelController/include/LevelController/FMI_LevelController.h LevelController/include/LevelController/fmi2Functions.h LevelController/include/LevelController/logger.h

# protected region additional dependencies on begin
# protected region additional dependencies end