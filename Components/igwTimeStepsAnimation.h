#ifndef IGWTIMESTEPSANIMATION_H
#define IGWTIMESTEPSANIMATION_H

#include "vtkAnimationCue.h"
#include <set>
class igwTimeStepsAnimation
{
public:
    igwTimeStepsAnimation();
    ~igwTimeStepsAnimation();

    void AddTimeStep(double time);
    void RemoveTimeStep(double time);
protected:
    std::set<double>* TimeSteps;

};

#endif // IGWTIMESTEPSANIMATION_H
