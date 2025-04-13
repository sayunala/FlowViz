/*=========================================================================

   Program: ParaView
   Module:    igwCoreUtilities.cxx

   Copyright (c) 2005,2006 Sandia Corporation, Kitware Inc.
   All rights reserved.

   ParaView is a free software; you can redistribute it and/or modify it
   under the terms of the ParaView license version 1.2.

   See License_v1.2.txt for the full ParaView license.
   A copy of this license can be obtained by contacting
   Kitware Inc.
   28 Corporate Drive
   Clifton Park, NY 12065
   USA

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHORS OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

========================================================================*/
#include "igwCoreUtilities.h"

#include <QAbstractButton>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QPalette>
#include <QString>
#include <QStringList>

#include "vtkObject.h"

#include "vtkWeakPointer.h"
#include "vtksys/SystemTools.hxx"

#include <cassert>
#include <cmath>
#include <cstdlib>

QPointer<QWidget> igwCoreUtilities::MainWidget = nullptr;

namespace
{
bool ApplicationIsRunningInDashboard()
{
  return vtksys::SystemTools::GetEnv("DASHBOARD_TEST_FROM_CTEST") != nullptr;
}
}

//-----------------------------------------------------------------------------
QWidget* igwCoreUtilities::findMainWindow()
{
  Q_FOREACH (QWidget* widget, QApplication::topLevelWidgets())
  {
    if (widget->isWindow() && widget->isVisible() && qobject_cast<QMainWindow*>(widget))
    {
      return widget;
    }
  }

  // Find any window (even if not visible).
  Q_FOREACH (QWidget* widget, QApplication::topLevelWidgets())
  {
    if (widget->isWindow() && qobject_cast<QMainWindow*>(widget))
    {
      return widget;
    }
  }

  return nullptr;
}

//-----------------------------------------------------------------------------
QString igwCoreUtilities::getParaViewUserDirectory()
{
//  pqSettings* settings = pqApplicationCore::instance()->settings();
//  return QFileInfo(settings->fileName()).path();
    return NULL;
}

//-----------------------------------------------------------------------------
QString igwCoreUtilities::getParaViewApplicationDirectory()
{
  return QApplication::applicationDirPath();
}

//-----------------------------------------------------------------------------
QStringList igwCoreUtilities::findParaviewPaths(
  QString directoryOrFileName, bool lookupInAppDir, bool lookupInUserDir)
{
  QStringList allPossibleDirs;
  if (lookupInAppDir)
  {
    allPossibleDirs.push_back(
      getParaViewApplicationDirectory() + QDir::separator() + directoryOrFileName);
    allPossibleDirs.push_back(getParaViewApplicationDirectory() + "/../" + directoryOrFileName);
    // Mac specific begin
    allPossibleDirs.push_back(
      getParaViewApplicationDirectory() + "/../Support/" + directoryOrFileName);
    allPossibleDirs.push_back(
      getParaViewApplicationDirectory() + "/../../../Support/" + directoryOrFileName);
    // This one's for when running from the build directory.
    allPossibleDirs.push_back(
      getParaViewApplicationDirectory() + "/../../../" + directoryOrFileName);
    // Mac specific end
  }

  if (lookupInUserDir)
  {
    allPossibleDirs.push_back(getParaViewUserDirectory() + QDir::separator() + directoryOrFileName);
  }

  // Filter with only existing ones
  QStringList existingDirs;
  Q_FOREACH (QString path, allPossibleDirs)
  {
    if (QFile::exists(path))
      existingDirs.push_back(path);
  }

  return existingDirs;
}

//-----------------------------------------------------------------------------
QString igwCoreUtilities::getNoneExistingFileName(QString expectedFilePath)
{
  QDir dir = QFileInfo(expectedFilePath).absoluteDir();
  QString baseName = QFileInfo(expectedFilePath).fileName();

  // Extract extension
  QString extension;
  if (baseName.lastIndexOf(".") != -1)
  {
    extension = baseName;
    extension.remove(0, baseName.lastIndexOf("."));
    baseName.chop(extension.size());
  }

  QString fileName = baseName + extension;
  int index = 1;
  while (dir.exists(fileName))
  {
    fileName = baseName;
    fileName.append("-").append(QString::number(index)).append(extension);
    index++;
  }

  return dir.absolutePath() + QDir::separator() + fileName;
}

//-----------------------------------------------------------------------------
class igwCoreUtilitiesEventHelper::pqInternal
{
public:
  vtkWeakPointer<vtkObject> EventInvoker;
  unsigned long EventID;
  pqInternal()
    : EventID(0)
  {
  }

  ~pqInternal()
  {
    if (this->EventInvoker && this->EventID > 0)
    {
      this->EventInvoker->RemoveObserver(this->EventID);
    }
  }
};

//-----------------------------------------------------------------------------
igwCoreUtilitiesEventHelper::igwCoreUtilitiesEventHelper(QObject* object)
  : Superclass(object)
  , Interal(new igwCoreUtilitiesEventHelper::pqInternal())
{
}

//-----------------------------------------------------------------------------
igwCoreUtilitiesEventHelper::~igwCoreUtilitiesEventHelper()
{
  delete this->Interal;
}

//-----------------------------------------------------------------------------
void igwCoreUtilitiesEventHelper::executeEvent(vtkObject* obj, unsigned long eventid, void* calldata)
{
  Q_EMIT this->eventInvoked(obj, eventid, calldata);
}

//-----------------------------------------------------------------------------
unsigned long igwCoreUtilities::connect(vtkObject* vtk_object, int vtk_event_id, QObject* qobject,
  const char* signal_or_slot, Qt::ConnectionType type /* = Qt::AutoConnection*/)
{
  assert(vtk_object != nullptr);
  assert(qobject != nullptr);
  assert(signal_or_slot != nullptr);
  if (vtk_object == nullptr || qobject == nullptr || signal_or_slot == nullptr)
  {
    // qCritical is Qt's 'print error message' stream
    qCritical() << "Error: Cannot connect to or from NULL.";
    return 0;
  }

  igwCoreUtilitiesEventHelper* helper = new igwCoreUtilitiesEventHelper(qobject);
  unsigned long eventid =
    vtk_object->AddObserver(vtk_event_id, helper, &igwCoreUtilitiesEventHelper::executeEvent);
  helper->Interal->EventID = eventid;
  helper->Interal->EventInvoker = vtk_object;

  QObject::connect(
    helper, SIGNAL(eventInvoked(vtkObject*, unsigned long, void*)), qobject, signal_or_slot, type);

  // * When qobject is deleted, helper is deleted. igwCoreUtilitiesEventHelper in
  // its destructor ensures that the observer is removed from the vtk_object if
  // it exists.
  // * When VTK-object is deleted, it removes the observer, but cannot delete
  // helper. Since igwCoreUtilitiesEventHelper::Interal keeps a weak-pointer to
  // the vtk_object, that gets cleared. So eventually when qobject is destroyed,
  // the igwCoreUtilitiesEventHelper is deleted, but since the vtk_object is
  // already deleted, it doesn't do anything special.
  return eventid;
}






