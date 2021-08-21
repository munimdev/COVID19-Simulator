#include "Humans.h"

//getters
int Human::getDaysSinceInfected() const
{
  return daysSinceInfected;
}
bool Human::IsHealthy() const
{
  return this->Healthy;
}
bool Human::IsInfected() const
{
  return this->Infected;
}
bool Human::IsInfectious() const
{
  return this->Infectious;
}
bool Human::IsSick() const
{
  return this->Sick;
}
bool Human::IsImmune() const
{
  return this->Immune;
}
bool Human::IsDeceased() const
{
  return this->Deceased;
}
bool Human::IsVaccinated() const
{
  return this->Vaccinated;
}
bool Human::IsFollowingSOPs() const
{
  return this->FollowingSOPs;
}


//setters, set more than just named status, also set other statuses so that logic is easier to
//handle for disease timeline
void Human::setDaysSinceInfected( int days )
{
  daysSinceInfected = days;
}
void Human::setInfectious( bool state )
{
  if ( state == true )
  {
    this->Infected = true;
    this->Infectious = true;
  }
  else
  {
    this->Infectious = false;
  }
}
void Human::setHealthy( bool state )
{
  if ( state == true )
  {
    this->Healthy = true;
    this->Sick = false;
    this->Infectious = false;
    this->Infected = false;
    this->Immune = true; //temporary immunity after recovery
  }
  else
  {
    this->Healthy = false;
  }
}
void Human::setInfected( bool state )
{
  if ( state == true )
  {
    this->Infected = true;
    this->Infectious = true;
  }
  else
  {
    this->Infected=false;
  }
}
void Human::setSick( bool state)
{
  if ( state == true )
  {
    this->Sick = true;
    this->Infected = true;
    this->Infectious = true;
    this->Healthy = false;
  }
  else
  {
    this->Sick = false;
  }
}
void Human::setDeceased( bool state)
{
  if ( state == true ) //setting everything else to false to ease logic in passDay()
  {
    this->Deceased = true;
    this->Sick = false;
    this->Healthy = false;
    this->Immune = false;
    this->Vaccinated = false;
    this->Infected = false;
    this->Infectious = false;
    this->FollowingSOPs = false;
  }
  else
  {
    this->Deceased = false;
  }
}
void Human::setVaccinated( bool state)
{
  if ( state == true ) //immediately makes person super healthy
  {
    this->Vaccinated = true;
    this->Immune = true;
    this->Healthy = true;
    this->Infected = false;
    this->Infectious = false;
    this->Sick = false;
  }
  else
  {
    this->Vaccinated = false;
  }
}
void Human::setImmune( bool state)
{
  if ( state == true )
  {
    this->Immune = true;
    this->Infected = false;
    this->Infectious = false;
    this->Healthy = true;
    this->Sick = false;
  }
  else
  {
    this->Immune = false;
  }
}
void Human::setIfFollowingSOPs( bool state )
{
  if ( state == true )
  {
    this->FollowingSOPs = true;
  }
  else
  {
    this->FollowingSOPs = false;
  }
}

//logic portion of disease timeline. passDay() keeps track of a person's position in disease timeline
void Human::passDay()
{

  //following are conditions for incrementing days:
  //if person is in infectious period, increment day
  //if person is in immunity period, increment day
  //otherwise make sure daysSinceInfected remains 0

  if ( this->IsInfectious() && daysSinceInfected <= getDaysOfInfectious() )
  { //if a person is infectious, and they are in the first portion of disease timeline, where they are still infectious
    daysSinceInfected++; //increment days since infected
  }
  else if ( this->IsImmune() && daysSinceInfected <= ( getDaysOfInfectious() + getDaysOfImmunity() ) && daysSinceInfected > 0 )
  { //if they have become immune, and their days count is after infectious period, and before immunity period runs ou
    daysSinceInfected++; //increment days tracker
  }
  else daysSinceInfected = 0; //otherwise, reset to 0, as person is out of disease timeline.


  if (this->IsInfected() && daysSinceInfected == getDaysUntilSick() )
  { //if a person has been infected, and their days tracker == days until they become sick (in Sim Rules)
    setSick(true); //set them as sick
  }
  else if ( this->IsSick() && daysSinceInfected <= getDaysOfInfectious() && daysSinceInfected >= getDaysUntilDeathChance()  && deathChanceRoll() )
  { //if they are sick, and they are in the period of death, and they roll true for deathChance(),
    setDeceased(true); //set them as deceased
  }
  else if (this->IsInfected() && daysSinceInfected == (getDaysOfInfectious() + 1) )
  { //if the person is out of sickness period, set them to healthy
    setHealthy(true);
  }
  else if ( this->IsImmune() && daysSinceInfected == (getDaysOfImmunity() + getDaysOfInfectious() ) )
  { //if person is immune, and their immunity period has run out
      if(!(IsVaccinated())) setImmune(false); //and if they aren't vaccinated, set their immunity to false
      else setImmune(true); //if they are vaccinated, keep them immune
  }
}


bool Human::deathChanceRoll() //gives true then person dies, depends upon prob value we set
    {
      double x = (double)(QRandomGenerator::global()->generate() % 1000) / 1000;
      if (x < getprobToDie() )
        return true;
      else
        return false;
    }

bool Human::TransmitVirusChanceRoll() //gives true if infecting someone else, depends on probability set
    {
      double x = (double)(QRandomGenerator::global()->generate() % 1000) / 1000;
      if (x < getprobToTransmitVirus() )
        return true;
      else
        return false;
    }

bool Human::TransmitVirusChanceRollSOP() //same as above, but has lower chance of infecting someone else,
//if they are following SoPs
    {
      double x = (double)(QRandomGenerator::global()->generate() % 1000) / 1000;
      if (x < (double)(getprobToTransmitVirus()/5) )
        return true;
      else
        return false;
    }
