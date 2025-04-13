#ifndef IGWFILEDIALOG_H
#define IGWFILEDIALOG_H


#include <QFileDialog>
#include <QPointer>

class QLabel;
class QLineEdit;


class igwFileDialog : public QFileDialog
{
    Q_OBJECT


public:
    enum EditMode{
        EDITING_GRID_FILE,
        EDITING_RESULT_FILE
    };

    enum FileFilterType{
        CUSTOM_FILE,
        ETKF_FILE
    };

    explicit igwFileDialog(QWidget *parent = nullptr);
    ~igwFileDialog();
protected slots:
    void onCurrentUrlChanged(const QUrl& url);
    void onSelectedFileChangde(const QString& file);

    void onFilterSelected(const QString& filter);
    void onCurrentChanged(const QString& path);

    bool eventFilter(QObject *watched, QEvent *);
private:
    /**
     * @brief BuildFileDialog: 为文件对话框添加新的widget，主要用于网格 + 结果文件输入的形式
     */
    void BuildFileDialog();

    /**
     * @brief BuildETKFUi: 构建ETKF文件相关UI(包括网格和属性文件)
     */
    void BuildETKFUi();
    void BuildNameFilters();

    QPointer<QLabel> ResultFileLabel;
    QPointer<QLineEdit> ResultFileEdit;

    static QStringList NameFilters;
    QString LastNameFilter;

    EditMode Mode;
    FileFilterType Type;

};

#endif // IGWFILEDIALOG_H
