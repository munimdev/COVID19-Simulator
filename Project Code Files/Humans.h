#pragma once
#include <iostream>
#include "SimulationRules.h"

class Human : public SimulatorRules //inheriting for access to daysUntilX data-members for passDay() function
{ 
  private:
    //statuses
    bool Healthy;
    bool Infected;
    bool Infectious;
    bool Sick;
    bool Immune; 
    bool Deceased;
    bool FollowingSOPs;
    bool Vaccinated; //sets immunity to permanently true
    
    short int daysSinceInfected; //keeps track of when human was infected. will be used to keep track of all statuses
    //short to minimize size of each human object, to allow more humans to be created without slowing down

  public:

    //overriding SimulatorRules ChanceRoll() functions:
    bool deathChanceRoll(); //rolls for a chance of dying
    bool TransmitVirusChanceRoll(); //rolls for a chance of spreading infection
    bool TransmitVirusChanceRollSOP(); //rolls for a chance of spreading infection if person is following SoPs

    void passDay(); //updates status based on days passed

    //setters
    void setHealthy( bool );
    void setInfected( bool );
    void setInfectious( bool );
    void setSick( bool );
    void setImmune( bool );
    void setDeceased( bool );
    void setVaccinated( bool );
    void setIfFollowingSOPs( bool );
    void setDaysSinceInfected( int );

    //getters
    bool IsHealthy( ) const;
    bool IsInfected( ) const;
    bool IsInfectious( ) const;
    bool IsSick( ) const;
    bool IsImmune( ) const;
    bool IsDeceased( ) const;
    bool IsVaccinated( ) const;
    bool IsFollowingSOPs() const;
    int getDaysSinceInfected() const;




    //constructor
    Human() 
    { //all Humans are healthy by default, some are converted to infected/immune by simulator at the start
      Healthy = true;
      Infected = false;
      Infectious = false;
      Sick = false;
      Immune = false; 
      Deceased = false;
      Vaccinated = false;
      daysSinceInfected = 0;
    }
};

