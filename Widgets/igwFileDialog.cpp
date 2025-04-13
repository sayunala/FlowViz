#include "igwFileDialog.h"


#include <QDialogButtonBox>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QMetaObject>
#include <QLineEdit>
#include <QUrl>
#include <iostream>
#include <QWidget>|
#include <QFileDialog>
#include <QEvent>

QStringList igwFileDialog::NameFilters = {QString::fromLocal8Bit("All(*)"),
                                          QString::fromLocal8Bit("VTK标准文件(*.vtk *.vtp *.vtu *.vtm *.vts *.vtr)"),
//                                          QString::fromLocal8Bit("ETKF算法文件 (*.etkf *.cas *.etkfg)"),
//                                          QString::fromLocal8Bit("Tecplot文件(*.tec *.plt *.dat *.hot)"),
//                                          QString::fromLocal8Bit("STL文件 (*.stl)"),
                                          QString::fromLocal8Bit("CGNS文件 (*.cgns)"),
                                          QString::fromLocal8Bit("OpenFOAM文件 (*.foam)"),
                                          QString::fromLocal8Bit("iGreatWorks 文件(*.igws)")};

igwFileDialog::igwFileDialog(QWidget *parent) :
    QFileDialog(parent)
{

    Mode = EditMode::EDITING_GRID_FILE;
    Type = FileFilterType::CUSTOM_FILE;
//    ui->setupUi(this);
    this->setOption(QFileDialog::DontUseNativeDialog, true);


    QDialogButtonBox *buttonBox = this->findChild<QDialogButtonBox *>("buttonBox");
    if (QPushButton *button = buttonBox->button(QDialogButtonBox::Open)){
        button->setStyleSheet("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #00BAFF, stop: 1 #00A1FF);font-size: 12px;color: #FFFFFF;border-radius:2px;}"
                              "QPushButton:hover{background: #00C1FF;font-size: 12px;color: #FFFFFF;border-radius:2px;}"
                              "QPushButton:disabled{background: #F0F0F0;border: 1px solid #DDDDDD;font-size: 12px;color: #BBBBBB;border-radius:2px;}");
        button->setFixedSize(68, 24);
        button->setText(QString::fromLocal8Bit("打开"));
    }
    if (QPushButton *button = buttonBox->button(QDialogButtonBox::Save)){
        button->setStyleSheet("QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #00BAFF, stop: 1 #00A1FF);font-size: 12px;color: #FFFFFF;border-radius:2px;}"
                              "QPushButton:hover{background: #00C1FF;font-size: 12px;color: #FFFFFF;border-radius:2px;}"
                              "QPushButton:disabled{background: #F0F0F0;border: 1px solid #DDDDDD;font-size: 12px;color: #BBBBBB;border-radius:2px;}");
        button->setFixedSize(68, 24);
        button->setText(QString::fromLocal8Bit("保存"));

    }
    if (QPushButton *button = buttonBox->button(QDialogButtonBox::Cancel)){
        button->setStyleSheet("QPushButton{border: 1px solid #DDDDDD;font-size: 12px;color: #666666;border-radius:2px;}"
                              "QPushButton:hover{font-size: 12px;color: #00A1FF;border: 1px solid #00A1FF;border-radius:2px;}"
                              "QPushButton:disabled{background: #F0F0F0;border: 1px solid #DDDDDD;font-size: 12px;color: #BBBBBB;border-radius:2px;}");
        button->setText(QString::fromLocal8Bit("取消"));
        button->setFixedSize(68, 24);
    }

    this->BuildFileDialog();

    this->BuildETKFUi();

    this->BuildNameFilters();
}

igwFileDialog::~igwFileDialog()
{
    //    delete ui;

    delete ResultFileEdit;
    delete ResultFileLabel;
}

void igwFileDialog::onCurrentUrlChanged(const QUrl &url)
{
    std::cout << "url change" << url.toString().toStdString() << std::endl;
}

void igwFileDialog::onSelectedFileChangde(const QString &file)
{
    std::cout << "file change" << file.toStdString() << std::endl;
}

void igwFileDialog::onFilterSelected(const QString &filter)
{

    QGridLayout* layout = qobject_cast<QGridLayout*>(this->layout());

    if(filter == NameFilters[2] && LastNameFilter != NameFilters[2])
    {
        // 从别的NameFilters切换到ETKF，Filter

        this->setLabelText(FileName, QString::fromLocal8Bit("网格文件: "));//替换file name 为网格文件

        QWidget* w0 = layout->itemAtPosition(3, 0)->widget();
        QWidget* w1 = layout->itemAtPosition(3, 1)->widget();


        layout->addWidget(ResultFileLabel, 3, 0);
        layout->addWidget(ResultFileEdit, 3, 1);
        layout->addWidget(w0, 4, 0);
        layout->addWidget(w1, 4, 1);
        ResultFileEdit.data()->show();
        ResultFileLabel.data()->show();

        // 增加一行结果文件到filename 下方
        // 添加到窗口中
        Type = ETKF_FILE;
    }
    else if(LastNameFilter == NameFilters[2] && filter != NameFilters[2]){
        // 从ETKF Filter切换到别的Filter
        this->setLabelText(FileName, QString::fromLocal8Bit("文件名:"));

        ResultFileEdit.data()->hide();
        ResultFileLabel.data()->hide();
        QWidget* w0 = layout->itemAtPosition(4, 0)->widget();
        QWidget* w1 = layout->itemAtPosition(4, 1)->widget();
        layout->replaceWidget(ResultFileLabel, w0);
        layout->replaceWidget(ResultFileEdit, w1);
        Type = CUSTOM_FILE;

    }
    LastNameFilter = filter;
}

void igwFileDialog::onCurrentChanged(const QString &path)
{

    QGridLayout* layout = qobject_cast<QGridLayout*>(this->layout());
    QWidget* w0 = layout->itemAtPosition(2, 1)->widget();
    QLineEdit* edit = qobject_cast<QLineEdit*>(w0);
    QStringList files = selectedFiles();
    switch (Mode) {
    case EDITING_GRID_FILE:
        edit->setText(path);
        std::cout << "EDITIN GRID" << std::endl;
//        files[0] = path;
        break;
    case EDITING_RESULT_FILE:
        ResultFileEdit->setText(path);

        std::cout << "EDITIN result" << std::endl;
        break;
    default:
        break;
    }

}

bool igwFileDialog::eventFilter(QObject* watched, QEvent* event)
{
    QGridLayout* layout = qobject_cast<QGridLayout*>(this->layout());
    QWidget* w0 = layout->itemAtPosition(2, 1)->widget();
    QLineEdit* fileNameEdit = qobject_cast<QLineEdit*>(w0);
    if (watched == fileNameEdit)
    {
        if(event->type() == QEvent::FocusIn){
            Mode = EDITING_GRID_FILE;

        }
    }
    if (watched == ResultFileEdit)
    {
        if(event->type() == QEvent::FocusIn){
            Mode = EDITING_RESULT_FILE;
            fileNameEdit->setReadOnly(true);
            fileNameEdit->disconnect();

        }
    }
    return QFileDialog::eventFilter(watched, event);
}

void igwFileDialog::BuildFileDialog()
{
    QGridLayout* layout = qobject_cast<QGridLayout*>(this->layout());

    //设置相关label
    this->setLabelText(FileName, QString::fromLocal8Bit("文件名:"));
    this->setLabelText(FileType, QString::fromLocal8Bit("文件类型:"));

    QWidget* w0 = layout->itemAtPosition(2, 1)->widget();
    QLineEdit* fileNameEdit = qobject_cast<QLineEdit*>(w0);

    fileNameEdit->installEventFilter(this);


}

void igwFileDialog::BuildETKFUi()
{

    this->ResultFileLabel = new QLabel(this);
    this->ResultFileEdit = new QLineEdit(this);
    this->ResultFileEdit->hide();
    this->ResultFileLabel->hide();
    ResultFileLabel->setText(QString::fromLocal8Bit("ETKF结果文件:"));

    QObject::connect(this, &igwFileDialog::filterSelected, this, &igwFileDialog::onFilterSelected);
    QObject::connect(this, &igwFileDialog::currentChanged, this, &igwFileDialog::onCurrentChanged);

    ResultFileEdit->installEventFilter(this);

}

void igwFileDialog::BuildNameFilters()
{
    // 构建文件名过滤器
    setNameFilters(NameFilters);
    LastNameFilter = NameFilters[0];

}
