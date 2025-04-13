#ifndef IGWREPRESENTATIONWIDGET_H
#define IGWREPRESENTATIONWIDGET_H

#include <QWidget>

class igwRenderedRepresentation;
class igwRepresentationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit igwRepresentationWidget(QWidget *parent = nullptr);
    virtual void setRepresentation(igwRenderedRepresentation* rep){};


};

#endif // IGWREPRESENTATIONWIDGET_H
