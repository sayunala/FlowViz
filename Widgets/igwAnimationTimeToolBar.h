#ifndef IGWANIMATIONTIMETOOLBAR_H
#define IGWANIMATIONTIMETOOLBAR_H

#include <QObject>
#include <QToolBar>
#include <QPointer>

class igwAnimationTimeWidget;
class igwAnimationScene;
class igwAnimationTimeToolBar : public QToolBar
{
    Q_OBJECT
public:
    igwAnimationTimeToolBar(const QString& _title, QWidget* _parent = nullptr)
      : QToolBar(_title, _parent)
    {
      this->constructor();
    }
    igwAnimationTimeToolBar(QWidget* _parent = nullptr)
      : QToolBar(_parent)
    {
      this->constructor();
    }
    igwAnimationTimeWidget* animationTImeWidget() const;
private:
    Q_DISABLE_COPY(igwAnimationTimeToolBar)
    void constructor();
    QPointer<igwAnimationTimeWidget> AnimationTimeWidget;
};

#endif // IGWANIMATIONTIMETOOLBAR_H
