/**********************************************
* @projectName   IGreatWorks
* @file          igwTimer.h
* @brief         简单的计时器，主要用于igwTransferFunctionWidget组件中
* @author        ZYB
* @date          2023-09-24
* @version       1.0
**********************************************/

#ifndef __igwTimer_h
#define __igwTimer_h


#include <QTimer>

/// igwTimer is a extension for QTimer which ensures that the timer is registered
/// with the pqEventDispatcher. Register timers with pqEventDispatcher ensures
/// that when tests are being played back, the timer will be ensured to have
/// timed out if active after every step in the playback. This provides a means
/// to reproduce the timer behaviour in the real world, during test playback.
class  igwTimer : public QTimer
{
  Q_OBJECT
  typedef QTimer Superclass;

public:
  igwTimer(QObject* parent = 0);
  ~igwTimer() override;

  /// This static function calls a slot after a given time interval.
  static void singleShot(int msec, QObject* receiver, const char* member);

protected:
  /// overridden to support blocking timer events in future (current
  /// implementation merely forwards to superclass).
  void timerEvent(QTimerEvent* evt) override;

private:
  Q_DISABLE_COPY(igwTimer)
};

#endif
