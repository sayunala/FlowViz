#include "igwReaction.h"

igwReaction::igwReaction(QAction *parent, Qt::ConnectionType type) : SupperClass(parent)
{
    QObject::connect(parent, SIGNAL(triggered(bool)), this, SLOT(onTriggered(bool)), type);
}

igwReaction::~igwReaction() = default;
