#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include "Humans.h"
#include "SimulationRules.h"

using namespace std;

class Country
{
  private:
    std::string name;
    bool travelPermission; //Tells if the country allows travels
    int travelInCount; //people travelled Inside a country
    int TravelOutCount;// people travelled outside of this country
    std::vector <Human> people; //vector of Human objects to store the people in a country    
    int DaysSinceLockdownStart = 0; //allows us to do lockdown logic
    bool lockdownStatus=false; //country starts with no lockdown in place

    int DailyVaccines; // moved over from sim rules, used to give vaccines
    int DaysSinceStart; //used to count days for runHealthActions() vaccination portion

  public:
    class HealthStats
    {
      private:
        string name = ""; //country name
        unsigned int healthy;  //number of people not infected
        unsigned int infected; //number of people infected
        unsigned int sick;     //number of sick people
        unsigned int dead;     // D E A T H S
        unsigned int immune;   //number of immune people
        unsigned int vaccinated;    //number of vacccinated people
        unsigned int infectious;    //number of infected people
        unsigned int visiblyInfectious;
        unsigned int population;    //stores population of the country
        unsigned int followingSOPs; //stores people following sops
        
      public:
        void addStats(HealthStats); //adds stats to a given object of stats
        HealthStats getStats(); //returns a HealthStats object
        string getData(); //returns stats in the form of a string
        //returns healhthy, infected, sick, numbers, etc
        
        //getters for stats, returns count of number of person which have each status
        unsigned int getHealthy();
        unsigned int getInfected();
        unsigned int getSick();
        unsigned int getDead();
        unsigned int getImmune();
        unsigned int getVaccinated();
        unsigned int getInfectious();
        unsigned int getVisiblyInfectious();
        unsigned int getFollowingSOPs();
        unsigned int getPopulation(); //returns population count

        //setters for stats
        void setPopulation( int );
        void setHealthy( int );
        void setInfected( int );
        void setSick( int );
        void setDead( int );
        void setImmune( int );
        void setVaccinated( int );
        void setInfectious( int );
        void setVisiblyInfectious( int );
        void setFollowingSOPs( int );
    };
  
  private:
  HealthStats stats; //including a stats object in country.
  
  public:
    //setters for country
    void setName( string name );
    void setDailyVaccines( int vaccines );
    void setDaysSinceStart();

    void addHumans( Human person ); //adds a certain number of humans
    void populate( vector <Human> ); //initializes human vector
    void removeHumans( Human person ); //removes number of humans
    //add/remove functions for each of following status
    void addHealthy(int);
    void removeHealthy(int);
    void addInfected(int);
    void removeInfected(int);
    void addDead(int);

    void runHealthActions(); //carries out vaccination process, lockdown, runs passDay() for each human
    void updateHealthStats(); //updates current stats for sake of plotting
    void ImposeLockDown(); //imposes lockdown by significantly increasing % following SoPs
    void LiftLockDown(); //removes lockdown by reverting the effeect
    vector <Human> residents();

    //getters for country
    string getName();
    HealthStats getStats();
    bool getLockdownStatus() {return lockdownStatus;}
    int getDaysSinceStart();
};


