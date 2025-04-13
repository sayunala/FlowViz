#include "igwTimeKeeper.h"
#include "vtkObjectFactory.h"
#include "vtkDoubleArray.h"
vtkStandardNewMacro(igwTimeKeeper)
void igwTimeKeeper::PrintSelf(std::ostream &os, vtkIndent indent)
{

}

void igwTimeKeeper::SetTime(double Time)
{
    if(this->Time != Time)
    {
        this->Time = Time;
    }
}

std::vector<double> &igwTimeKeeper::GetTimeValues()
{
    return this->TimeSteps;
}

void igwTimeKeeper::AddTimeStpes(vtkDoubleArray *timeStpes)
{
    this->TimeStepsSource.insert(timeStpes);
    this->UpdateTimeSteps();
}

igwTimeKeeper::igwTimeKeeper()
{
    this->Time = 0.0;
    this->DeferUpdateTimeSteps = false;
    this->TimeRange[0] = 0.0;
    this->TimeRange[1] = 1.0;
}

igwTimeKeeper::~igwTimeKeeper()
{

}

void igwTimeKeeper::UpdateTimeSteps()
{
    if (this->DeferUpdateTimeSteps)
    {
      return;
    }

    std::set<double> timesteps;
    double timerange[2] = { VTK_DOUBLE_MAX, VTK_DOUBLE_MIN };

    TimesType::iterator iter;
    for(iter = this->TimeStepsSource.begin(); iter != this->TimeStepsSource.end();++iter)
    {
        vtkDoubleArray* times = iter->GetPointer();
        if(times)
        {
            for(int i = 0; i < times->GetNumberOfTuples(); ++i)
            {
                double cur_elem = times->GetTuple1(i);
                timesteps.insert(cur_elem);
                timerange[0] = timerange[0] > cur_elem ? cur_elem : timerange[0];
                timerange[1] = timerange[1] < cur_elem ? cur_elem : timerange[1];
            }
        }
    }
    if (timerange[0] == VTK_DOUBLE_MAX && timerange[1] == VTK_DOUBLE_MIN)
    {
      timerange[0] = 0.0;
      timerange[1] = 1.0;
    }
    // TODO: 发送TimeRange更改的事件或者信号
    this->TimeRange[0] = timerange[0];
    this->TimeRange[1] = timerange[1];
    this->InvokeEvent(igwTimeKeeper::TimeRangeChangedEvent);
    std::vector<double> timesteps_vector;
    timesteps_vector.insert(timesteps_vector.begin(), timesteps.begin(), timesteps.end());
    this->TimeSteps.clear();
    this->TimeSteps.insert(TimeSteps.begin(), timesteps.begin(), timesteps.end());
    // TODO: 发送TimeValue更改的事件或者信号
    this->InvokeEvent(igwTimeKeeper::TimeValuesChangedEvent);




}

