#ifndef IGWVTKVIEW_H
#define IGWVTKVIEW_H

#include "igwView.h"
class igwVtkView : public igwView  
{
    
    Q_OBJECT
    typedef igwView Superclass;
public:
    igwVtkView(vtkView* view, QObject* parent);
    igwVtkView(QObject *parent);

    ~igwVtkView() override;
    QWidget* createWidget() override;
    void render();
};

#endif // IGWVTKVIEW_H
