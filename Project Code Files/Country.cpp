#include "Country.h"

//setters
void Country::setName( string name )
{
  this->name = name;
}
void Country::setDailyVaccines( int vaccines )
{
  DailyVaccines = vaccines;
}
void Country::setDaysSinceStart()
{
  DaysSinceStart = 0;
}
int Country::getDaysSinceStart()
{
  return DaysSinceStart;
}

//impose lockdown function
void Country::ImposeLockDown()
{
  for (int i = 0; i < stats.getPopulation()*0.7; i++) //based on current population
  { //randomly set a large portion of them to be following SoPs
    int x=QRandomGenerator::global()->generate() % stats.getPopulation();
    if(  !( people.at(x).IsDeceased() ) ) //if they are still alive
      people.at(x).setIfFollowingSOPs( true );
  }
  lockdownStatus = true; //when run, set lockdown status to true
}

//remove lockdown status function
void Country::LiftLockDown()
{
  for (int i = 0; i < stats.getPopulation()*0.7; i++)
  { //randomly set a portion of the population to be not following SoPs anymore
    int x=QRandomGenerator::global()->generate() % stats.getPopulation();
    if(  !( people.at(x).IsDeceased() ) ) //as long as they are alive
      people.at(x).setIfFollowingSOPs( false );
  }
  lockdownStatus = false; //set bool of status to be false
}

//function to vaccinate humans, run human.passDay() for each human, and do lockdown logic.
void Country::runHealthActions()
{

  if (lockdownStatus == true) //if a lockdown is currently happening
    DaysSinceLockdownStart++; //increment tracker

  if ( (double)stats.getInfected()/stats.getPopulation() >=0.1 && lockdownStatus == false)
  { //if over 5% of the population is infected, and a lockdown is not already in place
    ImposeLockDown(); //impose a lockdown
  }


  if ( (double)stats.getInfected()/stats.getPopulation() <= 0.05 && lockdownStatus == true && DaysSinceLockdownStart > 28 )
  { //if total active cases are currently over 5% of total population, and a lockdown has already continued for 14 days
    LiftLockDown(); //lift lockdown
    DaysSinceLockdownStart = 0; //and reset days tracker
  }


  //traverse through the whole human array and pass day for each
  for (Human &person : people) {
    person.passDay(); //run passDay(), which updates status of each human.
  }

  int tempVaccines = DailyVaccines; //to run vaccine logic every day
  for (Human &person : people) //for each human in array
  {
    if ( DaysSinceStart > person.getDaysUntilVaccineAccess() && person.IsHealthy() && !(person.IsVaccinated()) && tempVaccines > 0)
    { //if vaccines are accessible, and a person is healthy, and not already vaccinated, and sufficient vaccines are available
      person.setVaccinated(true); //set the person to be vaccinated
      person.setDaysSinceInfected(0); //ensures that the person does not fall into logic of "immunity from disease" period
      //and retains permanent immunity

      tempVaccines--; //decrease vaccines available for the day
    }
  }

  DaysSinceStart++; //used to administer vaccines after set number of days in sim rules
  //and used to keep track of stats for each day in plotting
}

// Called to create a snapshot each time a day passes
void Country::updateHealthStats()
{
  HealthStats tempStats; //create a temporary stats object for sake of recording values from scratch

  //count through each human in vector, recording total humans with each status
  tempStats.setHealthy( count_if(people.begin(), people.end(), [](Human &person) { return person.IsHealthy() == true;}) ); //counts number of healthy people in the people vector, and passes it as argument to setter

  tempStats.setInfected( count_if(people.begin(), people.end(), [](Human &person) { return person.IsInfected() == true;}) );

  tempStats.setDead( count_if(people.begin(), people.end(), [](Human &person) { return person.IsDeceased() == true;}) );

  tempStats.setImmune( count_if(people.begin(), people.end(), [](Human &person) { return person.IsImmune() == true;}) );

  tempStats.setVaccinated( count_if(people.begin(), people.end(), [](Human &person) { return person.IsVaccinated() == true;}) );

  tempStats.setInfectious( count_if(people.begin(), people.end(), [](Human &person) { return person.IsInfectious() == true;}) );

  tempStats.setSick( count_if(people.begin(), people.end(), [](Human &person) { return person.IsSick() == true;}) );

  tempStats.setFollowingSOPs( count_if(people.begin(), people.end(), [](Human &person) { return person.IsFollowingSOPs() == true;}) );

  tempStats.setPopulation( people.size() - tempStats.getDead() ); //population is (total size of vector - dead humans)

  stats = tempStats; //assign this temporary stats object to the one in country
}


void Country::HealthStats::addStats(Country::HealthStats stats)
{ //simply adds stats of another stats object to calling stats object
  this->healthy += stats.healthy;
  this->infected += stats.infected;
  this->sick += stats.sick;
  this->dead += stats.dead;
  this->immune += stats.immune;
  this->vaccinated += stats.vaccinated;
  this->infectious += stats.infectious;
  this->visiblyInfectious += stats.visiblyInfectious;
  this->population = stats.population;
}

string Country::HealthStats::getData()
{ //text based portion to print stats
  string stats = "";
  stats += "Alive: " + std::to_string( population ) + '\n';
  stats += "Healthy: " + std::to_string( healthy ) + '\n';
  stats += "Infectious: " + std::to_string( infectious ) + '\n';
  stats += "Infected: " + std::to_string( infected ) + '\n';
  stats += "Sick: " + std::to_string( sick ) + '\n';
  stats += "Immune: " + std::to_string( immune ) + '\n';
  stats += "Deaths: " + std::to_string( dead ) + '\n';
  stats += "Vaccinated: " + std::to_string( vaccinated ) + '\n';
  stats += "People following SOPs: " + std::to_string( followingSOPs ) + '\n';

  return stats; //for plotting, returns stats object, so that each individual status can be read as needed
};

Country::HealthStats Country::getStats() //returns stats object in country to read all of a day's stats
{
  return stats;
}

//HealthStats getter functions
unsigned int Country::HealthStats::getHealthy(){ return healthy; }
unsigned int Country::HealthStats::getInfected() { return infected; }
unsigned int Country::HealthStats::getSick() { return sick; }
unsigned int Country::HealthStats::getDead() { return dead; }
unsigned int Country::HealthStats::getImmune() { return immune; }
unsigned int Country::HealthStats::getVaccinated() { return vaccinated; }
unsigned int Country::HealthStats::getInfectious() { return infectious; }
unsigned int Country::HealthStats::getVisiblyInfectious() { return visiblyInfectious; }
unsigned int Country::HealthStats::getPopulation() { return population; }
unsigned int Country::HealthStats::getFollowingSOPs() { return followingSOPs; }

//HealthStats setter functions
void Country::HealthStats::setHealthy( int num ) { healthy = num; }
void Country::HealthStats::setInfected( int num ) { infected = num; }
void Country::HealthStats::setSick( int num ) { sick = num; }
void Country::HealthStats::setDead( int num ) { dead = num; }
void Country::HealthStats::setImmune( int num ) { immune = num; }
void Country::HealthStats::setVaccinated( int num ) { vaccinated = num; }
void Country::HealthStats::setInfectious( int num ) { infectious = num; }
void Country::HealthStats::setVisiblyInfectious( int num ) { visiblyInfectious = num; }
void Country::HealthStats::setPopulation( int num ) { population = num; }
void Country::HealthStats::setFollowingSOPs( int num) { followingSOPs = num; }

//return the vector of humans
vector <Human> Country::residents()
{
  return this->people;
}

//getter for name
string Country::getName()
{
  return this->name;
}

//add or remove humans as necessary
void Country::addHumans( Human person )
{
  people.push_back( person );
}
void Country::removeHumans( Human person )
{
    auto itr = remove_if( people.begin(), people.end(), [&]( Human &human ){return &human == &person; } );
    people.erase( itr, people.end() );
    //goes through the entire vector to find an object that has the same pointer as the person,
    //and if there's a match, that object will get erased from the vector
}

void Country::populate( vector <Human> population )
{
  people = population;
}
