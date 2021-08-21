#pragma once
#include <iostream>

#include <QRandomGenerator>
//QRandomGenerator is a Qt library to produce random numbers,
//global()->generate() is what we will be using to generate
//random numbers, which are different for each run

using namespace std;

class SimulatorRules //abstract class, made so pure virtual ChanceRoll() functions
{
  private:
    static int DaysUntilVaccineAccess; //# of days till vaccine access
    static int DaysUntilSick; //these two manage interval
    static int DaysUntilDeathChance; //manages interval of person, along with daysOfSickness
    static int DaysOfImmunity; //time period after recovery in which person is immune
    static int DaysOfInfectious; //number of days person can infect others

    static double probToTransmitVirus; //daily chance a person has to transmit virus to someone else
    static double probToDie; //daily chance that a persosn will die if sick


public:

    //pure virtual functions, get overridden by Human class
    virtual bool deathChanceRoll() = 0;//gives true then person dies, depends upon prob value we set

    virtual bool TransmitVirusChanceRoll() = 0; //gives true if infecting someone else, depends on probability set

    virtual bool TransmitVirusChanceRollSOP() = 0; //same as above, but has lower chance of infecting someone else,
    //as they are following SoPs
    

    //getters
    double getprobToDie()
    {
    return probToDie;
    }
    double getprobToTransmitVirus()
    {
      return probToTransmitVirus;
    }
    static int getDaysUntilVaccineAccess()
    {
      return DaysUntilVaccineAccess;
    }
    static int getDaysUntilSick()
    {
      return DaysUntilSick;
    }
    static int getDaysUntilDeathChance()
    {
      return DaysUntilDeathChance;
    }
    static int getDaysOfImmunity()
    {
      return DaysOfImmunity;
    }
    static int getDaysOfInfectious()
    {
      return DaysOfInfectious;
    }

    //setters
    void setTransmissionChance(double percentInfectivityPerDay)
    {
        probToTransmitVirus = percentInfectivityPerDay;
    }
    void setDeathChance(double percentLethalityPerDay)
    {
        probToDie = percentLethalityPerDay;
    }
};

