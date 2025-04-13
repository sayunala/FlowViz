
#ifndef igwHierarchicalGridWidget_h
#define igwHierarchicalGridWidget_h

#include <QScopedPointer>    // for ivar
#include <QWidget>

class igwHierarchicalGridWidget : public QWidget
{
  Q_OBJECT
  typedef QWidget Superclass;

public:
  igwHierarchicalGridWidget(QWidget* parent = nullptr);
  ~igwHierarchicalGridWidget() override;

  ///@{
  /**
   * Enable/disable interactive resizing of the layout.
   * Default is enabled.
   */
  void setUserResizability(bool);
  bool userResizability() const;
  ///@}

  /**
   * handle cursor changes on mouse move
   */
  bool eventFilter(QObject* caller, QEvent* evt) override;

Q_SIGNALS:
  void splitterMoved(int location, double splitFraction);

protected:
  void mouseMoveEvent(QMouseEvent* evt) override;
  void mousePressEvent(QMouseEvent* evt) override;
  void mouseReleaseEvent(QMouseEvent* evt) override;

private:
  Q_DISABLE_COPY(igwHierarchicalGridWidget);

  class pqInternals;
  QScopedPointer<pqInternals> Internals;
  friend class pqInternals;
  void setSplitFraction(int location, double fraction);

  friend class igwHierarchicalGridLayout;

  /**
   * Provides information about splitters, their direction, their location and
   * their range.
   */
  struct SplitterInfo
  {
    Qt::Orientation Direction;
    QRect Bounds;
    int Location;
    int Position;
  };

  void setSplitters(const QVector<SplitterInfo>& splitters);
};

#endif
