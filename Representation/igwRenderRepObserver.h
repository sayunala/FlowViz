#ifndef IGWRENDERREPOBSERVER_H
#define IGWRENDERREPOBSERVER_H

#include "igwCommand.h"
#include "vtkRenderWindowInteractor.h"
#include "../Representation/igwRenderedRepresentation.h"

class igwRenderRepObserver : public vtkCommand
{
public:
  vtkTypeMacro(igwRenderRepObserver, vtkCommand)
  static igwRenderRepObserver* New()
  {
    return new igwRenderRepObserver;
  }
  igwRenderRepObserver(){

  }

  void setRepresentation(igwRenderedRepresentation * rep){
      if(rep != nullptr)
      {
           m_Rep = rep;
      }
      return ;

  }

  void Execute(vtkObject* caller, unsigned long eventId,
               void* callData) override
  {
      switch (eventId) {
      case iGreatWorks::ETKFDataUpdateEvent:
          m_Rep->UpdateDataSet(callData);
          break;
      default:
          break;
      }

    vtkRenderWindowInteractor* iren = static_cast<vtkRenderWindowInteractor*>(caller);
    iren->Render();
  }
   ~igwRenderRepObserver(){
      m_Rep = 0;
  }

private:

  igwRenderedRepresentation* m_Rep;

};



#endif // IGWRENDERREPOBSERVER_H
