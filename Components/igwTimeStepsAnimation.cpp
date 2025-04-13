#include "igwTimeStepsAnimation.h"

igwTimeStepsAnimation::igwTimeStepsAnimation()
{
    TimeSteps = new std::set<double>;

}
igwTimeStepsAnimation::~igwTimeStepsAnimation()
{
    delete TimeSteps;
}

void igwTimeStepsAnimation::AddTimeStep(double time)
{
    this->TimeSteps->insert(time);
}

void igwTimeStepsAnimation::RemoveTimeStep(double time)
{
    std::set<double>::iterator iter = this->TimeSteps->find(time);
    if (iter != this->TimeSteps->end())
    {
      this->TimeSteps->erase(iter);
    }
}
