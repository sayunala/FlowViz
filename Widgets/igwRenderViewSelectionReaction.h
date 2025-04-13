#ifndef IGWRENDERVIEWSELECTIONREACTION_H
#define IGWRENDERVIEWSELECTIONREACTION_H

/**********************************************
* @projectName   iGreatWorks
* @file          igwRenderViewSelectionReaction.h
* @brief
* @author        ZYB
* @date          2024/06/15
* @version       1.0
**********************************************/

#include "igwSelectionReaction.h"
#include "vtkSmartPointer.h"
#include "vtkWeakPointer.h"
class vtkObject;
class igwRenderView;
class vtkIntArray;
static const char * zoom_xpm[] = {
"32 32 3 1",
" 	c None",
".	c #FFFFFF",
"+	c #000000",
"                                ",
"                                ",
"                                ",
"                                ",
"                                ",
"         .....                  ",
"       ..+++++..                ",
"      .++.....++.               ",
"      .+.     .+.               ",
"     .+.       .+.              ",
"     .+.       .+.              ",
"     .+.       .+.              ",
"     .+.       .+.              ",
"     .+.       .+.              ",
"      .+.     .+.               ",
"      .++.....+++.              ",
"       ..+++++.+++.             ",
"         ..... .+++.            ",
"                .+++.           ",
"                 .+++.          ",
"                  .+++.         ",
"                   .+++.        ",
"                    .+++.       ",
"                     .+++.      ",
"                      .+.       ",
"                       .        ",
"                                ",
"                                ",
"                                ",
"                                ",
"                                ",
"                                "};

class igwRenderViewSelectionReaction : public igwSelectionReaction
{
    Q_OBJECT
    typedef igwSelectionReaction SuperClass;

public:
    // 交互中的选择模式、如选择网格、选择点、框选放大等等
    enum class SelectionMode
    {
        SELECT_SURFACE_CELLS,
        SELECT_SURFACE_POINTS,
        ZOOM_TO_BOX,

    };


    igwRenderViewSelectionReaction(QAction* parentAction, igwRenderView* view, SelectionMode mode);
    ~igwRenderViewSelectionReaction() override;

Q_SIGNALS:
    void selectedCustomBox(int xmin, int ymin, int xmax, int ymax);
    void selectedCustomBox(const int region[4]);
    void selectedCustomPolygon(vtkIntArray* polygon);

protected Q_SLOTS:

    virtual void actionTriggered(bool val);

//    void updateEnableState() override;

    virtual void setView(igwRenderView* view);

    /**
     * @brief beginSelection:选择开始
     */
    virtual void beginSelection();

    /**
     * @brief endSelection:结束选择
     */
    virtual void endSelection();

protected:

    /**
     * @brief SelectionChanged： 回调函数，用于监听选择结束的事件
     * @param callData
     */
    virtual void SelectionChanged(vtkObject*, unsigned long, void* callData);

    virtual void ClearupObservers();
private:
    Q_DISABLE_COPY(igwRenderViewSelectionReaction)

    SelectionMode Mode;
    igwRenderView* View;
    QCursor ZoomCursor;

    vtkWeakPointer<vtkObject> ObservedObject;
    unsigned long ObserverIds[6];
    static QPointer<igwRenderViewSelectionReaction> ActiveReaction;

};

#endif // IGWRENDERVIEWSELECTIONREACTION_H
