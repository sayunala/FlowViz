#ifndef IGWFILEREACTION_H
#define IGWFILEREACTION_H

#include "igwReaction.h"
#include "vtkAlgorithmOutput.h"
#include "IO/igwIOCore.h"
class vtkDataObject;

class igwFileReaction : public igwReaction
{
    Q_OBJECT
    typedef igwReaction SupperClass;
public:
    igwFileReaction(QAction* parent);

    static const char* GetOpenFileName();


//    static vtkDataObject* LoadData(const QStringList& fileList);
    static vtkDataObject *LoadFile(const QString& file);
    static QList<vtkDataObject*> LoadData(const QStringList& files);

    static QList<vtkDataObject*> LoadData();


//    static QList<vtkDataObject*> LoadData();
//    static QList<vtkDataObject*> LoadData(const  );
Q_SIGNALS:
    void loadedData(vtkDataObject*);

protected slots:
    void onTriggered(bool value) override;
    void updateEnableState() override;
private:
    static QMap<igwIOCore::FileType, QString> FilterMap;
    static QStringList FileNameFilter;
    Q_DISABLE_COPY(igwFileReaction);


};

#endif // IGWFILEREACTION_H
