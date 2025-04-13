#ifndef IGWREACTION_H
#define IGWREACTION_H

#include <QAction>
#include <QObject>
class igwReaction : public QObject
{
    Q_OBJECT
    typedef QObject SupperClass;
public:
    explicit igwReaction(QAction *parent = nullptr, Qt::ConnectionType type = Qt::AutoConnection);
    ~igwReaction() override;

    QAction* parentAction() const {return qobject_cast<QAction*>(this->parent());}
protected Q_SLOTS:
    virtual void onTriggered(bool value){};
    virtual void updateEnableState(){};
private:
    Q_DISABLE_COPY(igwReaction);
};

#endif // IGWREACTION_H
