#include "igwSaveScreenShotReaction.h"
#include "../Representation/igwRenderView.h"
#include "../Components/igwActiveObjects.h"
#include "vtkRenderWindow.h"
#include "vtkWindowToImageFilter.h"

#include "vtkImageWriter.h"
#include "vtkPNGWriter.h"
#include "vtkBMPWriter.h"
#include "vtkJPEGWriter.h"

#include <QApplication>
#include <QMimeData>
#include <QClipboard>
#include <QFileDialog>
#include <QTextCodec>
igwSaveScreenShotReaction::igwSaveScreenShotReaction(QAction *parent, bool clipboardMode)
    :SupperClass(parent)
    , ClipboardMode(clipboardMode)
{

}

bool igwSaveScreenShotReaction::SaveScreenShot(bool clipboardMode)
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();

    if(view == nullptr)
    {
        return false;
    }
    int* size = view->GetRenderWindow()->GetScreenSize();
    vtkSmartPointer<vtkImageData> image = TakeScreenShot(QSize(size[0], size[1]));

    //截取当前View得图像到粘贴板中
    if(clipboardMode)
    {
        int* size = view->GetRenderWindow()->GetSize();

        const QSize pixelSize(size[0], size[1]);
        return igwSaveScreenShotReaction::CopyScreenShotToClipboard(pixelSize);
    }
    QString filter = QString("PNG(*.png);;BMP(*.bmp);;JPG(*.jpg *.jpeg)");
    QFileDialog fileDialog;
    fileDialog.setNameFilter(filter);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
    if(fileDialog.exec() != QDialog::Accepted)
    {
        return false;
    }

    QString location = fileDialog.selectedFiles()[0];

    // 中文路径解决
    QTextCodec *code = QTextCodec::codecForName("GB2312");
    std::string name = code->fromUnicode(location).data();

    WriteImage(image, location.toUtf8().data());
}

vtkSmartPointer<vtkImageData> igwSaveScreenShotReaction::TakeScreenShot(const QSize &size)
{
    igwRenderView* view = igwActiveObjects::GetInstance().GetActiveView();
    if(view == nullptr)
    {
        return false;
    }

    vtkSmartPointer<vtkImageData> image;


    vtkNew<vtkWindowToImageFilter> windowToImage;
    windowToImage->SetInput(view->GetRenderWindow());

    windowToImage->Update();
    image = windowToImage->GetOutput();

    return image;
}

bool igwSaveScreenShotReaction::CopyScreenShotToClipboard(const QSize &size)
{
    const vtkSmartPointer<vtkImageData> image = TakeScreenShot(size);

    if (image == nullptr)
    {
      return false;
    }
    QImage qImage;
    igwSaveScreenShotReaction::ImageDataToQImage(image, qImage);
    QMimeData* data = new QMimeData;
    data->setImageData(qImage);
    QApplication::clipboard()->setMimeData(data);

    return true;
}

bool igwSaveScreenShotReaction::ImageDataToQImage(vtkImageData *vtkImage, QImage &qImage)
{
    if (vtkImage->GetScalarType() != VTK_UNSIGNED_CHAR)
    {
      return false;
    }

    int extent[6];
    vtkImage->GetExtent(extent);
    int width = extent[1] - extent[0] + 1;
    int height = extent[3] - extent[2] + 1;
    int numcomponents = vtkImage->GetNumberOfScalarComponents();
    if (!(numcomponents == 3 || numcomponents == 4))
    {
      return false;
    }

    QImage newimg(width, height, QImage::Format_ARGB32);

    for (int i = 0; i < height; i++)
    {
      QRgb* bits = reinterpret_cast<QRgb*>(newimg.scanLine(i));
      unsigned char* row;
      row = static_cast<unsigned char*>(
        vtkImage->GetScalarPointer(extent[0], extent[2] + height - i - 1, extent[4]));
      for (int j = 0; j < width; j++)
      {
        unsigned char* data = &row[j * numcomponents];
        bits[j] = numcomponents == 4 ? qRgba(data[0], data[1], data[2], data[3])
                                     : qRgb(data[0], data[1], data[2]);
      }
    }

    qImage = newimg;
    return true;
}

bool igwSaveScreenShotReaction::WriteImage(vtkImageData* image, const char *fileName)
{
    if(image == nullptr)
    {
        return false;
    }
    if(fileName == nullptr)
    {
        return false;
    }
    std::string suffix = vtksys::SystemTools::GetFilenameExtension(fileName);
    suffix = vtksys::SystemTools::LowerCase(suffix);

    vtkImageWriter* writer = nullptr;
    if(suffix == ".png")
    {
        writer  = vtkPNGWriter::New();
    }
    else if(suffix == ".jpg" || suffix == ".jpeg")
    {
        writer  = vtkJPEGWriter::New();
    }
    else if(suffix == ".bmp")
    {
        writer = vtkBMPWriter::New();
    }

    writer->SetInputData(image);
    writer->SetFileName(fileName);
    writer->Write();
    writer->Delete();
    return true;
}
