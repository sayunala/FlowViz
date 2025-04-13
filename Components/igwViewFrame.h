#ifndef IGWVIEWFRAME_H
#define IGWVIEWFRAME_H

#include <QWidget>
#include <QUuid>
#include <QMap>
#include <QScopedPointer>
#include <QPointer>
class QDragEnterEvent;
class QDragMoveEvent;
class QDropEvent;
class QFrame;
class QLabel;
class QMenu;
class QToolBar;
class QToolButton;
class igwView;

namespace Ui {
class igwViewFrame;
}

class igwViewFrame : public QWidget
{
    Q_OBJECT
    typedef QWidget Superclass;
public:
    explicit igwViewFrame(QWidget *parent = nullptr);

    ~igwViewFrame() override;

    void setCentralWidget(QWidget* widget, igwView* view = nullptr);
    QWidget* centralWidget();


    enum StandardButton
    {
      NoButton = 0x0000,
      SplitHorizontal = 0x0001,
      SplitVertical = 0x0002,
      Maximize = 0x0004,
      Restore = 0x0008,
      Close = 0x0010
    };

    //
    Q_DECLARE_FLAGS(StandardButtons, StandardButton)

    void setStandardButtons(StandardButtons buttons);
    StandardButtons standardButtons() const {return this->Buttons;}

    QUuid uniqueID() const {return this->uniqueID();}

Q_SIGNALS:
    void buttonPressed(int button);

    void actionTriggered(QAction* action);

    void swapPositions(const QString& other);

    void finishDrag(igwViewFrame *source);

public Q_SLOTS:

    bool eventFilter(QObject *watched, QEvent *event) override;
protected:

//    virtual void updateComponentVisibilities();

    void drag();
    void dragEnter(QDragEnterEvent*);
    void drop(QDropEvent*);

protected Q_SLOTS:
    void buttonClicked();
    void customContextMenuRequested(const QPoint &pos);

protected:
    bool DecorationsVisible;
    bool TitleBarVisible;
    bool BorderVisible;
    QColor BorderColor;
    StandardButtons Buttons;

    QPointer<QToolBar> ToolBar;
    QPointer<QWidget> CentralWidget;
    QPointer<QMenu> ContexMenu;

    QUuid UniqueID;
    QPoint DragStartPosition;

    typedef QMap<StandardButton, QPointer<QToolButton>> StandardToolButtonsMap;
      StandardToolButtonsMap StandardToolButtons;

    QPalette PaletteWithBorder;
    QPalette PaletteWithoutBorder;
    QString PlainTitle;



private:
    Ui::igwViewFrame *ui;

    Q_DISABLE_COPY(igwViewFrame)

    QToolButton* createButton(QAction* action);

private Q_SLOTS:
    void finishedDrag(igwViewFrame* source);
};
Q_DECLARE_OPERATORS_FOR_FLAGS(igwViewFrame::StandardButtons);
#endif // IGWVIEWFRAME_H
