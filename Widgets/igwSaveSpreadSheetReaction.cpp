#include "igwSaveSpreadSheetReaction.h"

#include "../IO/igwCSVWriter.h"
#include "../Components/igwActiveObjects.h"
#include "igwFileDialog.h"
#include "vtkSmartPointer.h"

#include <QFileDialog>
igwSaveSpreadSheetReaction::igwSaveSpreadSheetReaction(QAction *parent)
    :SupperClass(parent)
{

}

void igwSaveSpreadSheetReaction::SaveSpreadSheet()
{

    vtkDataObject* data = igwActiveObjects::GetInstance().GetActiveData();
    if(data == nullptr)
    {
        return;
    }

    QString filter = QString("CSV(*.csv);;TXT(*.txt)");
    QFileDialog fileDialog;
    fileDialog.setNameFilter(filter);
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setAcceptMode(QFileDialog::AcceptSave);
//    fileDialog.setOption(QFileDialog::DontUseNativeDialog, true);
//    fileDialog.setOption(QFileDialog::DontUseCustomDirectoryIcons, false);
    if(fileDialog.exec() != QDialog::Accepted)
    {
        return ;
    }
    QString location = fileDialog.selectedFiles()[0];

    WriteTable(data, location.toUtf8().data());



}

void igwSaveSpreadSheetReaction::WriteTable(vtkDataObject *data, const char *fileName)
{
    if(data == nullptr)
    {
        return;
    }
    if(fileName == nullptr)
    {
        return;
    }

    std::string suffix = vtksys::SystemTools::GetFilenameExtension(fileName);
    suffix = vtksys::SystemTools::LowerCase(suffix);

    igwCSVWriter* writer = igwCSVWriter::New();

    if(suffix == ".csv")
    {
        writer->SetFieldDelimiter(",");

    }
    else
    {
        writer->SetFieldDelimiter(" ");
    }
    writer->SetAddMetaData(true);
    writer->SetFileName(fileName);
    writer->SetInputData(data);
    writer->Update();

    writer->Delete();


}

void igwSaveSpreadSheetReaction::onTriggered(bool value)
{
    igwSaveSpreadSheetReaction::SaveSpreadSheet();
}
