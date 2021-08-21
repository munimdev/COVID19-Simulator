#pragma once
#include <vector>
#include <iostream>
#include <cmath>
#include <string>
#include "Country.h"
#include "Humans.h"
#include "SimulationRules.h"

class Simulator
{
  private:
    Country country; //simulator contains a country object
    int daysPassed = 0; //used to keep track of vaccine access + stats

  public:

    Simulator(){}; //default constructor, not defining as unnecessary (Qt was giving errors without it)

    Simulator( string countryName, int vaccinesPerDay ); //parameterized constructor for actual use

    //function that populates human vector, with as many infected, immune, or following SoPs as specified
    void populate( int population, double percentInfected, double percentImmune, double percentFollowingSOPs);

    std::vector <Human> people; //vector of humans

    void passDay(); //passes 1 day to update humans and their categories, basically updating simulation

    int getDaysPassed() const; //getter function
    
    Country::HealthStats getCountryStats(); //used to get the stats object stored in country

    Country getCountry(); //returns te Country object
};
