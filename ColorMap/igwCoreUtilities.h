
#ifndef igwCoreUtilities_h
#define igwCoreUtilities_h
/**********************************************
* @projectName   IGreatWorks
* @file          igwCoreUtilities.h
* @brief         工具类，来自paraiew，主要使用connect，将vtk事件和qt的槽连接起来
* @author        ZYB
* @date          2023-09-23
* @version       1.0
**********************************************/


#include <QDir>
#include <QEventLoop>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QPointer>
#include <QString>
#include <QStringList>
#include <QWidget>

class QPalette;
class vtkObject;

/**
 * INTERNAL CLASS (DO NOT USE). This is used by
 * igwCoreUtilities::connectWithVTK() methods.
 */
class  igwCoreUtilitiesEventHelper : public QObject
{
  Q_OBJECT;
  typedef QObject Superclass;

public:
  igwCoreUtilitiesEventHelper(QObject* parent);
  ~igwCoreUtilitiesEventHelper() override;

Q_SIGNALS:
  void eventInvoked(vtkObject*, unsigned long, void*);

private:
  Q_DISABLE_COPY(igwCoreUtilitiesEventHelper)

  void executeEvent(vtkObject*, unsigned long, void*);
  class pqInternal;
  pqInternal* Interal;
  friend class igwCoreUtilities;
};

/**
 * igwCoreUtilities is a collection of arbitrary utility functions that can be
 * used by the application.
 */
class  igwCoreUtilities : public QObject
{
  Q_OBJECT
public:
  /**
   * When popping up dialogs, it's generally better if we set the parent
   * widget for those dialogs to be the QMainWindow so that the dialogs show up
   * centered correctly in the application. For that purpose this convenience
   * method is provided. It locates a QMainWindow and returns it.
   */
  static void setMainWidget(QWidget* widget) { igwCoreUtilities::MainWidget = widget; }
  static QWidget* mainWidget()
  {
    if (!igwCoreUtilities::MainWidget)
    {
      igwCoreUtilities::MainWidget = igwCoreUtilities::findMainWindow();
    }
    return igwCoreUtilities::MainWidget;
  }


  /**
   * Return the path of the root ParaView user specific configuration directory
   */
  static QString getParaViewUserDirectory();

  /**
   * Return the path of the launched application
   */
  static QString getParaViewApplicationDirectory();

  /**
   * Return the list of full available path that exists inside the shared
   * application path and the user specific one
   */
  static QStringList findParaviewPaths(
    QString directoryOrFileName, bool lookupInAppDir, bool lookupInUserDir);
  static QString getNoneExistingFileName(QString expectedFilePath);

  /**
   * Method used to connect VTK events to Qt slots (or signals).
   * This is an alternative to using vtkEventQtSlotConnect. This method gives a
   * cleaner API to connect vtk-events to Qt slots. It manages cleanup
   * correctly i.e. either vtk-object or the qt-object can be deleted and the
   * observers will be cleaned up correctly. One can disconnect the connection
   * made explicitly by vtk_object->RemoveObserver(eventId) where eventId is
   * the returned value.
   */

  /**
   * @brief 用于将 VTK 事件连接到 Qt 插槽（或信号）的方法。是vtkEventQtSlotConnect的替代
   * @param vtk_object
   * @param vtk_event_id
   * @param qobject
   * @param signal_or_slot
   * @param type
   * @return
   */
  static unsigned long connect(vtkObject* vtk_object, int vtk_event_id, QObject* qobject,
    const char* signal_or_slot, Qt::ConnectionType type = Qt::AutoConnection);



private:
  static QWidget* findMainWindow();
  static QPointer<QWidget> MainWidget;
};

#endif
