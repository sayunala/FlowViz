#ifndef IGWSAVESCREENSHOTREACTION_H
#define IGWSAVESCREENSHOTREACTION_H

#include "igwReaction.h"
#include "vtkImageData.h"
#include "vtkSmartPointer.h"
class igwSaveScreenShotReaction : public igwReaction
{
    Q_OBJECT
    typedef igwReaction SupperClass;
public:
    igwSaveScreenShotReaction(QAction* parent, bool clipboardMode = false);

    // 保存屏幕截图到剪贴板或者文件中
    static bool SaveScreenShot(bool clipboardMode = false);

    // 将当前View中RenderWindow转换为vtkImageData
    static vtkSmartPointer<vtkImageData> TakeScreenShot(const QSize& size);

    // 将当前View窗口可视化内容复制到粘贴板
    static bool CopyScreenShotToClipboard(const QSize& size);

    // 将vtkImageData转换为 QImage
    static bool ImageDataToQImage(vtkImageData* vtkImage, QImage& qImage);

    // 将vtkImageData写入 fileName代表的文件
    static bool WriteImage(vtkImageData* image, const char* fileName);
protected slots:
    void onTriggered(bool value) override{igwSaveScreenShotReaction::SaveScreenShot(this->ClipboardMode);};


private:
    bool ClipboardMode;
    Q_DISABLE_COPY(igwSaveScreenShotReaction)
};

#endif // IGWSAVESCREENSHOTREACTION_H
