#ifndef igwHierarchicalGridLayout_h
#define igwHierarchicalGridLayout_h

#include <QLayout>
#include <QScopedPointer> // for ivar

#include "vtkCGNSFileSeriesReader.h"
class igwHierarchicalGridLayout : public QLayout
{
  Q_OBJECT
  typedef QLayout Superclass;

public:
  igwHierarchicalGridLayout(QWidget* parent = nullptr);
  ~igwHierarchicalGridLayout() override;

  ///@{
  /**
   * pure virtual methods from QLayout
   */
  void addItem(QLayoutItem* item) override;
  QLayoutItem* itemAt(int index) const override;
  QLayoutItem* takeAt(int index) override;
  int count() const override;
  ///@}

  ///@{
  /**
   * recommended overrides from QLayout
   */
  QSize minimumSize() const override;
  void setGeometry(const QRect& rect) override;
  QSize sizeHint() const override;
  ///@}

  ///@{
  /**
   * Returns true if the location points to a valid reachable location.
   */
  bool isLocationValid(int location) const;
  ///@}

  ///@{
  /**
   * Adds a splitter item. \c location specified must be valid and reachable.
   */
  void split(int location, Qt::Orientation direction, double splitFraction);
  void splitAny(int location, double splitFraction);
  void splitVertical(int location, double splitFraction)
  {
    this->split(location, Qt::Vertical, splitFraction);
  }
  void splitHorizontal(int location, double splitFraction)
  {
    this->split(location, Qt::Horizontal, splitFraction);
  }
  ///@}

  /**
   * Specify the split fraction for a location. \c location must be valid and
   * reachable.
   */
  void setSplitFraction(int location, double splitFraction);
  ///@}

  ///@{
  /**
   * Maximize any cell location. Set to 0 to return to default un-maximized state.
   * Invalid location i.e. negative or referring to a non-existent or
   * unreachable cell will be ignored with a warning message.
   */
  void maximize(int location);
  ///@}

  class Item
  {
  public:
    Item(Qt::Orientation direction, double fraction)
      : Direction(direction)
      , Fraction(fraction)
    {
    }
    Item(QWidget* widget = nullptr)
      : Widget(widget)
    {
    }

  private:
    QWidget* Widget = nullptr;
    Qt::Orientation Direction = Qt::Horizontal;
    double Fraction = -1.0;
    friend class igwHierarchicalGridLayout;
  };

  QVector<QWidget*> rearrange(const QVector<Item>& layout);
  void removeLocation(int location);

  unsigned int getMaxChildIndex(unsigned int parent);

  void moveSubtree(int, int);
  void shrink();

  class pqInternals;
  QScopedPointer<pqInternals> Internals;
private:
  Q_DISABLE_COPY(igwHierarchicalGridLayout);


};

#endif
