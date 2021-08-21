#include "Simulator.h"
#include <QRandomGenerator>

Simulator::Simulator( string countryName, int vaccinesPerDay ) //parameterized constructor
{
  country.setName( countryName );
  country.setDailyVaccines( vaccinesPerDay );
  country.setDaysSinceStart(); //sets it to 0
}

void Simulator::populate( int population, double percentInfected, double percentImmune, double percentFollowingSOPs)//this function only runs at start of program
{
  //set infected count and immune count based on input parameters, rounded to nearest integer
  int infectedCount = round( ( (float) (percentInfected / 100.0)) * population);
  int immuneCount = round( ( (float) (percentImmune / 100.0)) * population);

  //exception handling:
  int SOPsFollowerCount = round( ( (float) (percentFollowingSOPs / 100.0)) * population);
  try
  {
    if( population <= 0 )
      throw "Invalid population input.";
    if( percentInfected > 100 || percentInfected < 0 )
      throw "Invalid percentInfected input.";
    if ( percentImmune > 100 || percentImmune < 0 )
      throw "Invalid percentImmune input.";
    if ( percentFollowingSOPs > 100 || percentFollowingSOPs < 0 )
      throw "Invalid percentFollowingSOPs input.";
    if ( percentFollowingSOPs > 100 )
      throw "Invalid percentFollowingSOPs input.";
    if ( immuneCount + infectedCount > population )
      throw "Invalid immune and infectedCount input.";
  }
  catch(const char* error)
  {
    cerr << "Error: " << error << endl;
  }


  vector <Human> people;//declaring human vector
  for (int i = 0; i < population; i++)
  {
    people.push_back( *new Human ); //populates the people vector according to population specified
  }

  for (int i = 0; i < infectedCount; i++) //infectedCount number of people infected at the start
  {
    int x= QRandomGenerator::global()->generate() % people.size();
    if ( !(people.at(x).IsInfected() ) ) //if person is not already infected
    {
      people.at(x).setInfected( true );
    }
  }

  for (int i = 0; i < immuneCount; i++) //at start of the program, an immuneCount number of people
  {
    int x = QRandomGenerator::global()->generate() % people.size();
    if ( !(people.at(x).IsImmune() ) )
      people.at(x).setImmune( true );
  }

  for (int i = 0; i < SOPsFollowerCount; i++) //at start of the program, an SOPsFollowers amount of people
  {
    int x = QRandomGenerator::global()->generate() % people.size();
    if ( !(people.at(x).IsFollowingSOPs() ) )
      people.at(x).setIfFollowingSOPs( true );
  }

  country.populate( people );
  country.updateHealthStats(); //update stats based on initial infected/immune/followingSoPs count
}


void Simulator::passDay() //run passDay, has logic to infect humans
{
  vector <Human> people = country.residents();

    int count = count_if(people.begin(), people.end(), [](Human &person) { return person.IsInfectious() == true;});
    for (int i = 0; i<count ; i++)
    { //run a for loop for each human who is infectious
      for (unsigned int j=0 ; j < QRandomGenerator::global()->generate() % 3 ; j++)
      { //they can infect anywhere from 0-2 people in a day at max
        int x = round (QRandomGenerator::global()->generate() % people.size() ); //select a random human from entire vector
        if ( !( people.at(j).IsDeceased() ) && !(people.at(x).IsFollowingSOPs()) && !( people.at(x).IsImmune() ) && !( people.at(x).IsInfected() ) && people.at(x).TransmitVirusChanceRoll() ) //it checks if the person is not infected already and then rolls the chance
        { //if they are not dead, not following SoPs, not immune, not infected, and roll true for transmissionChance()
          people.at(x).setInfected(true); //set them as infected
        }
        else
        {
          if( people.at(x).IsFollowingSOPs() && !(people.at(x).IsImmune()) && people.at(x).TransmitVirusChanceRollSOP() )
          { //if they are following SoPs, and roll true for transmissionChanceSOP(), which has much lower chance
            people.at(x).setInfected(true); //set them as infected
          }
        }
      }
    }
  country.populate( people );
  country.runHealthActions(); //run health actions function in country
  country.updateHealthStats(); //update stats for plotting
  daysPassed++; //keep track of days
}

//getters
int Simulator::getDaysPassed()  const
{
  return daysPassed;
}
Country Simulator::getCountry()
{
  return country;
}
