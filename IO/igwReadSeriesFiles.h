#ifndef IGWREADSERIESFILES_H
#define IGWREADSERIESFILES_H

#include <QString>
#include <QVector>
//#include "igwIOCore.h"
#include "igwReadFile.h"
#include "vtkSmartPointer.h"

class vtkDataObject;
class vtkCGNSFileSeriesReader;
typedef struct
{
    QString filePath;
    QString fileType;
    QString timeStep;

} SeriesFileInFo;
class igwReadSeriesFiles : public igwReadFile
{
public:
    vtkTypeMacro(igwReadSeriesFiles, igwReadFile)
    igwReadSeriesFiles();
    ~igwReadSeriesFiles();

    static igwReadSeriesFiles* New();
    void PrintSelf(ostream&fstream, vtkIndent indent);
    virtual vtkDataObject *ReadFile(const char *filename) override;
    virtual void SetTimeValue(double time);

protected:
   QList<SeriesFileInFo> loadConfigFile(const QString& configFile);

   QVector<vtkDataObject*> Datas;
   vtkSmartPointer<vtkCGNSFileSeriesReader> SeriesReader;

private:
    igwReadSeriesFiles(const igwReadSeriesFiles&) = delete;
    void operator =(const igwReadSeriesFiles&) = delete;
};

#endif // IGWREADSERIESFILES_H
