#ifndef IGWSAVESPREADSHEETREACTION_H
#define IGWSAVESPREADSHEETREACTION_H

#include "igwReaction.h"
#include "vtkDataObject.h"
class igwSaveSpreadSheetReaction : public igwReaction
{
    Q_OBJECT
    typedef igwReaction SupperClass;
public:
    igwSaveSpreadSheetReaction(QAction* parent);

    static void SaveSpreadSheet();

    static void WriteTable(vtkDataObject* data, const char* fileName);
protected:
    void onTriggered(bool value);
private:
    Q_DISABLE_COPY(igwSaveSpreadSheetReaction);

};

#endif // IGWSAVESPREADSHEETREACTION_H
