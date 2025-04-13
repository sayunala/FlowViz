#ifndef IGWTIMEKEEPER_H
#define IGWTIMEKEEPER_H

#include "vtkObject.h"
#include "vtkCommand.h"
#include <set>
class vtkDoubleArray;
class igwTimeKeeper : public vtkObject
{
public:
    enum
    {
      // Fired whenever the vtkAnimationScene wants to request the
      // igwAnimationSceneProxy to update the start/end times.
      // The calldata is a vtkVector2d with the suggested time-range.
      TimeRangeChangedEvent = vtkCommand::UserEvent,
      TimeValuesChangedEvent = vtkCommand::UserEvent + 1
    };
    static igwTimeKeeper* New();
    vtkTypeMacro(igwTimeKeeper, vtkObject);
    void PrintSelf(ostream& os, vtkIndent indent) override;

    void SetTime(double Time);
    vtkGetMacro(Time, double);

    vtkGetVector2Macro(TimeRange, double);
    std::vector<double> &GetTimeValues();

    void AddTimeStpes(vtkDoubleArray* timeStpes);




protected:
    igwTimeKeeper();
    virtual ~igwTimeKeeper();


    void UpdateTimeSteps();
    double TimeRange[2];
    double Time;
    std::vector<double> TimeSteps;


private:
    igwTimeKeeper(const igwTimeKeeper&) = delete;
    void operator =(const igwTimeKeeper&) = delete;
    typedef std::set<vtkSmartPointer<vtkDoubleArray>> TimesType;
    TimesType TimeStepsSource;

    bool DeferUpdateTimeSteps;
};

#endif // IGWTIMEKEEPER_H
