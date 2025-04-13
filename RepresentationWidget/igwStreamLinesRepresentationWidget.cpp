#include "igwStreamLinesRepresentationWidget.h"
#include "ui_igwStreamLinesRepresentationWidget.h"

#include "igwLineParametersWidget.h"
#include "igwPlaneParametersWidget.h"
#include "Representation/igwStreamLinesRepresentation.h"

#include "vtkEventQtSlotConnect.h"
#include "vtkSmartPointer.h"
#include "vtkObjectFactory.h"
#include "vtkPlaneWidget.h"
#include "vtkLineWidget.h"
#include "vtkPointData.h"
#include <QComboBox>
#include <QSpinBox>

#include <iostream>
igwStreamLinesRepresentationWidget::igwStreamLinesRepresentationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::igwStreamLinesRepresentationWidget)
{
    ui->setupUi(this);


    this->ConnetPlaneSignalAndSlot();
    this->ConnetLineSignalAndSlot();
}

igwStreamLinesRepresentationWidget::~igwStreamLinesRepresentationWidget()
{
    delete ui;
    std::cout << "End StreamLinesRepWidget" << std::endl;
}

void igwStreamLinesRepresentationWidget::SetRepresentation(igwStreamLinesRepresentation *rep)
{
    this->m_igwStreamLinesRepresentation = rep;
    ui->PlaneWidget->SetPlane(rep->GetPlane());
    m_Connect = vtkSmartPointer<vtkEventQtSlotConnect>::New();

    // 连接 PlaneWidget 交互事件 与 UI的参数显示
    m_Connect->Connect(m_igwStreamLinesRepresentation->GetPlaneWidget(),
                       vtkCommand::EndInteractionEvent, this, SLOT(PlaneWidgetEndInterActorSlot()));

    // 连接 LineWidget 交互事件 与 UI的参数显示
    m_Connect->Connect(m_igwStreamLinesRepresentation->GetLineWidget(), vtkCommand::EndInteractionEvent,
                       ui->LineWidget, SLOT(updateLineWidgetSlot()));

//    ui->PlaneWidget->SetVisibility(rep->GetPlaneVisibility());
    ui->LineWidget->SetLineWidget(m_igwStreamLinesRepresentation->GetLineWidget());
//    ui->LineWidget->SetVisibility(rep->GetLineVisibility());
    m_igwStreamLinesRepresentation->SetSeedType(static_cast<SeedWidget>(m_igwStreamLinesRepresentation->GetSeedType()));
    //初始化
    this->InitDataArrayComboBox();
    this->Init();
}

void igwStreamLinesRepresentationWidget::SetNormalToXAxis()
{
    std::cout << "Normal x" << std::endl;
    this->m_igwStreamLinesRepresentation->SetPlaneNormalToXAxis();
    Q_EMIT this->Applied();
}

void igwStreamLinesRepresentationWidget::SetNormalToYAxis()
{
    std::cout << "Normal x" << std::endl;
    this->m_igwStreamLinesRepresentation->SetPlaneNormalToYAxis();
    Q_EMIT this->Applied();
}

void igwStreamLinesRepresentationWidget::SetNormalToZAxis()
{
    this->m_igwStreamLinesRepresentation->SetPlaneNormalToZAxis();
    Q_EMIT this->Applied();
}

void igwStreamLinesRepresentationWidget::SetPlaneNormal(double x, double y, double z)
{
    this->m_igwStreamLinesRepresentation->SetPlaneNormal(x, y, z);
    Q_EMIT this->Applied();
}

void igwStreamLinesRepresentationWidget::SetPlaneOrigin(double x, double y, double z)
{
    this->m_igwStreamLinesRepresentation->SetPlaneOrigin(x, y, z);
    Q_EMIT this->Applied();
}

void igwStreamLinesRepresentationWidget::PlaneWidgetEndInterActorSlot()
{
    double* origin = m_igwStreamLinesRepresentation->GetPlaneOrigin();
    double* normal = m_igwStreamLinesRepresentation->GetPlaneNormal();
    Q_EMIT this->UpdatePlaneParametersWidget(origin[0], origin[1], origin[2], normal[0], normal[1], normal[2]);
}

void igwStreamLinesRepresentationWidget::LineWidgetChangedSlot()
{
    Q_EMIT this->Applied();
}

void igwStreamLinesRepresentationWidget::ApplySetting()
{
    m_igwStreamLinesRepresentation->UpdateSeed();
    Q_EMIT Applied();
}

void igwStreamLinesRepresentationWidget::ConnetPlaneSignalAndSlot()
{
    QObject::connect(ui->PlaneWidget, SIGNAL(XNormalButton_clicked()), this, SLOT(SetNormalToXAxis()));
    QObject::connect(ui->PlaneWidget, SIGNAL(YNormalButton_clicked()), this, SLOT(SetNormalToYAxis()));
    QObject::connect(ui->PlaneWidget, SIGNAL(ZNormalButton_clicked()), this, SLOT(SetNormalToZAxis()));

    QObject::connect(ui->PlaneWidget, SIGNAL(showPlaneCheckBox_stateChanged(int)),
                     this, SLOT(SetPlaneEnable(int)));

    QObject::connect(ui->PlaneWidget, SIGNAL(OriginChanged(double,double,double)),
                     this, SLOT(SetPlaneOrigin(double,double,double)));
    QObject::connect(ui->PlaneWidget, SIGNAL(NormalChanged(double,double,double)),
                     this, SLOT(SetPlaneNormal(double,double,double)));

    QObject::connect(this, SIGNAL(UpdatePlaneParametersWidget(double,double,double,double,double,double)),
                     ui->PlaneWidget, SLOT(UpdatePlane(double,double,double,double,double,double)));
}

void igwStreamLinesRepresentationWidget::ConnetLineSignalAndSlot()
{
    QObject::connect(ui->LineWidget, SIGNAL(LineWidgetChanged()), this, SLOT(LineWidgetChangedSlot()));
}

void igwStreamLinesRepresentationWidget::InitDataArrayComboBox()
{
    ui->DataArrayComboBox->blockSignals(true);
    vtkDataSet* dataSet = m_igwStreamLinesRepresentation->GetDataSet();
    vtkPointData* pointData = dataSet->GetPointData();
    int numberOfArrays = pointData->GetNumberOfArrays();
    for (int i = 0; i < numberOfArrays; i++)
    {
        ui->DataArrayComboBox->addItem(QString(pointData->GetArrayName(i)));
    }
    ui->DataArrayComboBox->blockSignals(false);
    const char* arrayName = m_igwStreamLinesRepresentation->GetPointColorArrayName();
    ui->DataArrayComboBox->setCurrentText(QString(arrayName));
}

void igwStreamLinesRepresentationWidget::Init()
{

    ui->comboBox->setCurrentIndex(m_igwStreamLinesRepresentation->GetSeedType());
//    ui->StreamTypeComboBox->blockSignals(true);
    ui->StreamTypeComboBox->setCurrentIndex(m_igwStreamLinesRepresentation->GetStreamLineType());
//    ui->StreamTypeComboBox->blockSignals(false);

    ui->DirectionComboBox->setCurrentIndex(m_igwStreamLinesRepresentation->GetDirection());

    ui->WidthSpinBox->setValue(m_igwStreamLinesRepresentation->GetStreamLineWidth() * 100);//
    ui->NumOfLineSeedsSpinBox->setValue(m_igwStreamLinesRepresentation->GetResolution());
    ui->PlaneXAxisSpinBox->setValue(m_igwStreamLinesRepresentation->GetNumberOfXResolution());
    ui->PlaneYAxisSpinBox->setValue(m_igwStreamLinesRepresentation->GetNumberOfYResolution());


}

void igwStreamLinesRepresentationWidget::SetPlaneEnable(int type)
{

    if(type == 0)
        this->m_igwStreamLinesRepresentation->PlaneWidgetOff();
    else this->m_igwStreamLinesRepresentation->PlaneWidgetOn();
    this->m_igwStreamLinesRepresentation->SetPlaneVisibility(type);
    Q_EMIT this->Applied();
}



void igwStreamLinesRepresentationWidget::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
    case 0:
        // 切换为使用平面进行种子生成
//        this->m_igwStreamLinesRepresentation->LineWidgetOff();
//        this->m_igwStreamLinesRepresentation->PlaneWidgetOn();
        this->m_igwStreamLinesRepresentation->SetSeedType(USE_PLANE_WIDGET);
        ui->NumOfLineSeedsSpinBox->setEnabled(false);
        ui->PlaneXAxisSpinBox->setEnabled(true);
        ui->PlaneYAxisSpinBox->setEnabled(true);
        // 进行切换就可见
        this->m_igwStreamLinesRepresentation->SetPlaneVisibility(true);
        ui->PlaneWidget->SetVisibility(true);
        break;
    case 1:
        //切换为使用线进行平面生成
//        this->m_igwStreamLinesRepresentation->LineWidgetOn();
//        this->m_igwStreamLinesRepresentation->PlaneWidgetOff();
        this->m_igwStreamLinesRepresentation->SetSeedType(USE_LINE_WIDGET);
        ui->NumOfLineSeedsSpinBox->setEnabled(true);
        ui->PlaneXAxisSpinBox->setEnabled(false);
        ui->PlaneYAxisSpinBox->setEnabled(false);
        this->m_igwStreamLinesRepresentation->SetLineVisibility(true);
        ui->LineWidget->SetVisibility(true);
    default:
        break;
    }
    Q_EMIT Applied();
}


void igwStreamLinesRepresentationWidget::on_DataArrayComboBox_currentIndexChanged(const QString &arrayName)
{
    m_igwStreamLinesRepresentation->SetInputArrayToProcess(0, 0, 0, vtkDataObject::FIELD_ASSOCIATION_POINTS, arrayName.toStdString().c_str());
    Q_EMIT this->Applied();
}


void igwStreamLinesRepresentationWidget::on_StreamTypeComboBox_currentIndexChanged(int index)
{

    // 使用switch增强可读性
    // 0: 流线 | 1: 流管 | 2: 流带 | 3: 流面
    switch (index) {
    case 0:
        this->m_igwStreamLinesRepresentation->SetStreamLineType(STREAM_LINE);
        ui->WidthSpinBox->setEnabled(false);
        break;
    case 1:
        this->m_igwStreamLinesRepresentation->SetStreamLineType(STREAM_TUBE);
        ui->WidthSpinBox->setEnabled(true);
        break;
    case 2:
        this->m_igwStreamLinesRepresentation->SetStreamLineType(STREAM_RIBBON);
        ui->WidthSpinBox->setEnabled(true);
        break;
    case 3:
        this->m_igwStreamLinesRepresentation->SetStreamLineType(STREAM_SURFACE);
        ui->WidthSpinBox->setEnabled(false);
        break;
    default:
        break;
    }
    Q_EMIT Applied();
}


void igwStreamLinesRepresentationWidget::on_DirectionComboBox_currentIndexChanged(int index)
{
    // 切换积分方向
    // 0: +正向 | -1: +反向 | 2: +/-双向
    this->m_igwStreamLinesRepresentation->SetStreamLineDirection(index);
    Q_EMIT Applied();
}


void igwStreamLinesRepresentationWidget::on_WidthSpinBox_valueChanged(int arg1)
{
    double width = double(arg1);
    this->m_igwStreamLinesRepresentation->SetWidth(width);
    Q_EMIT Applied();
}


void igwStreamLinesRepresentationWidget::on_LengthSpinBox_valueChanged(int arg1)
{
    this->m_igwStreamLinesRepresentation->SetLength(arg1);
//    this->m_igwStreamLinesRepresentation->UpdateSeed();
    Q_EMIT Applied();
}

void igwStreamLinesRepresentationWidget::on_PlaneXAxisSpinBox_valueChanged(int arg1)
{
    this->m_igwStreamLinesRepresentation->SetPlaneSeedXResolution(arg1);
    this->m_igwStreamLinesRepresentation->UpdateSeed();
    Q_EMIT Applied();
}


void igwStreamLinesRepresentationWidget::on_PlaneYAxisSpinBox_valueChanged(int arg1)
{
    this->m_igwStreamLinesRepresentation->SetPlaneSeedYResolution(arg1);
    this->m_igwStreamLinesRepresentation->UpdateSeed();
    Q_EMIT Applied();
}



void igwStreamLinesRepresentationWidget::on_NumOfLineSeedsSpinBox_valueChanged(int arg1)
{
    this->m_igwStreamLinesRepresentation->SetLineSeedResolution(arg1);
    this->m_igwStreamLinesRepresentation->UpdateSeed();
    Q_EMIT Applied();
}

