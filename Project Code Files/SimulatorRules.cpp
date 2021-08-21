#include "SimulationRules.h"

//int SimulatorRules::DailyVaccines = 0;

//define basic values for disease timeline
int SimulatorRules::DaysUntilVaccineAccess = 200; //defines the number of days after which people can get access to vaccines
int SimulatorRules::DaysUntilSick = 6; //defines the number of days after which they start showing symptoms when they first get infected
int SimulatorRules::DaysUntilDeathChance = 9; //days after a person can die if he or she is sick
int SimulatorRules::DaysOfImmunity = 30; //days person gets immunity from the virus if they recover and do not die
int SimulatorRules::DaysOfInfectious = 15; //person is infectious for 15 days

//default values for chances
double SimulatorRules::probToTransmitVirus = 0.20;
double SimulatorRules::probToDie = 0.00300;
