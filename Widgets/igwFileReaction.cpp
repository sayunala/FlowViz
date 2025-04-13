#include "igwFileReaction.h"

#include "vtkDataObject.h"

#include <QFileDialog>
#include <QList>
#include <QFileInfo>
#include <QMap>
#include <vtkMultiBlockDataSet.h>
#include "vtkCompositeDataSet.h"
#include "vtkObjectFactory.h"
//#include "vtkExtractDataSets.h"
#include "vtkDataObjectTreeIterator.h"
#include "vtkGroupDataSetsFilter.h"
#include "vtkGroupTimeStepsFilter.h".h"
#include "igwFileDialog.h"
#include "vtkExtractBlock.h"

#include "../IO/igwIOCore.h"

// 打开文件对话框显示的下拉框
QStringList igwFileReaction::FileNameFilter = {QString::fromLocal8Bit("All(*)"),
                                               QString::fromLocal8Bit("VTK标准文件(*.vtk *.vtp *.vtu *.vtm *.vts *.vtr)"),
                                               QString::fromLocal8Bit("ETKF算法文件 (*.etkf *.cas *.etkfg)"),
                                               QString::fromLocal8Bit("Tecplot文件(*.tec *.plt *.dat *.hot)"),
//                                               QString::fromLocal8Bit("STL文件 (*.stl)"),
                                               QString::fromLocal8Bit("CGNS文件 (*.cgns)"),
                                               QString::fromLocal8Bit("OpenFOAM文件 (*.foam)"),
                                               QString::fromLocal8Bit("iGreatWorks 文件(*.igws)")};
// 文件类型与后缀映射
QMap<igwIOCore::FileType, QString> igwFileReaction::FilterMap= {
    {igwIOCore::FileType::CGNS, "cgns"},
    {igwIOCore::FileType::OPENFOAM, "foam"},
    {igwIOCore::FileType::VTK_SERIES, "vtm"},
    {igwIOCore::FileType::IGW_SERIES, "igws"},
    {igwIOCore::FileType::LEGENCY_VTK, "vtk"}

};
igwFileReaction::igwFileReaction(QAction* parent)
    :SupperClass(parent)
{

}

const char *igwFileReaction::GetOpenFileName()
{

    igwFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setFileMode(QFileDialog::ExistingFile);

    if(fileDialog.exec() != QDialog::Accepted)
    {
        return nullptr;
    }
    QString location = fileDialog.selectedFiles()[0];
    return location.toUtf8().data();


}

//vtkDataObject* igwFileReaction::LoadData()
//{
//    igwFileDialog fileDialog;
//    fileDialog.setFileMode(QFileDialog::AnyFile);
//    fileDialog.setFileMode(QFileDialog::ExistingFile);

//    if(fileDialog.exec() != QDialog::Accepted)
//    {
//        return nullptr;
//    }
//    const QStringList fileList = fileDialog.selectedFiles();
//    QString location = fileList[0];



//}

QList<vtkDataObject *> igwFileReaction::LoadData(const QStringList &files)
{
    QList<vtkDataObject*> datas;
    for(const QString& file : files)
    {
        vtkDataObject* data = igwFileReaction::LoadFile(file);

        // 需要过一遍compositeDataSet to DataSets
        vtkCompositeDataSet* compositeData = vtkCompositeDataSet::SafeDownCast(data);


        if( compositeData!=nullptr)
        {
            auto iter = compositeData->NewIterator();
            iter->SetDataSet(compositeData);
            iter->SkipEmptyNodesOn();
//            iter->VisitOnlyLeavesOn();
//            iter->SetTraverseSubTree(false);
            for (iter->InitTraversal(); !iter->IsDoneWithTraversal();
                   iter->GoToNextItem())
              {
                vtkDataObject* dso = iter->GetCurrentDataObject();
//                dso->ShallowCopy(iter->GetCurrentDataObject());
//                datas.push_back(dso);

              }
            datas.push_back(compositeData);
//

        }
        else datas.push_back(data);

    }
    return datas;
}

QList<vtkDataObject *> igwFileReaction::LoadData()
{
    igwFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::AnyFile);
    fileDialog.setFileMode(QFileDialog::ExistingFile);

    if(fileDialog.exec() != QDialog::Accepted)
    {
        return QList<vtkDataObject*>();
    }
    const QStringList fileList = fileDialog.selectedFiles();
    return igwFileReaction::LoadData(fileList);
}

vtkDataObject *igwFileReaction::LoadFile(const QString &file)
{
    vtkDataObject *data;
    QFileInfo fileInfo(file);
    const QString& suffix = fileInfo.suffix();

    igwIOCore::FileType fileType = FilterMap.key(suffix);
    data = igwIOCore::GetInstance()->ReadFile(file.toUtf8().data(), fileType);

    return data;

}

void igwFileReaction::onTriggered(bool value)
{

    QList<vtkDataObject*> datas = this->LoadData();
    vtkDataObject* data;
//    data->Print(std::cout);
    Q_FOREACH(data, datas)
    {
        // 遍历datas中的所有data

        Q_EMIT this->loadedData(data);
    }

}

void igwFileReaction::updateEnableState()
{

}
