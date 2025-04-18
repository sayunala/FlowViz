﻿// SPDX-FileCopyrightText: Copyright (c) Kitware Inc.
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   igwCSVWriter
 * @brief   CSV writer for vtkTable/vtkDataSet/vtkCompositeDataSet
 * Writes a vtkTable/vtkDataSet/vtkCompositeDataSet as a delimited text file (such as CSV).
 */

#ifndef igwCSVWriter_h
#define igwCSVWriter_h

#include "vtkDataObject.h"                  // for vtkDataObject::FieldAssociations

#include "vtkWriter.h"

#include <string> // for std::string
#include <vector> // for std::vector

class vtkDoubleArray;
class vtkMultiProcessController;
class vtkTable;

class igwCSVWriter : public vtkWriter
{
public:
  static igwCSVWriter* New();
  vtkTypeMacro(igwCSVWriter, vtkWriter);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Get/Set the controller to use. By default,
   * `vtkMultiProcessController::GetGlobalController` will be used.
   */
  void SetController(vtkMultiProcessController*);
  vtkGetObjectMacro(Controller, vtkMultiProcessController);
  ///@}

  ///@{
  /**
   * Get/Set the delimiter use to separate fields ("," by default.)
   */
  vtkSetStringMacro(FieldDelimiter);
  vtkGetStringMacro(FieldDelimiter);
  ///@}

  ///@{
  /**
   * Get/Set the delimiter used for string data, if any
   * eg. double quotes(").
   */
  vtkSetStringMacro(StringDelimiter);
  vtkGetStringMacro(StringDelimiter);
  ///@}

  ///@{
  /**
   * Get/Set the filename for the file.
   */
  vtkSetStringMacro(FileName);
  vtkGetStringMacro(FileName);
  ///@}

  ///@{
  /**
   * When WriteAllTimeSteps is turned ON, the writer is executed once for
   * each timestep available from the reader.
   *
   * The Default is OFF.
   */
  vtkSetMacro(WriteAllTimeSteps, bool);
  vtkGetMacro(WriteAllTimeSteps, bool);
  vtkBooleanMacro(WriteAllTimeSteps, bool);
  ///@}

  ///@{
  /**
   * When WriteAllTimeStepsSeparately is turned ON and WriteAllTimeSteps is ON,
   * the writer is executed once for each timestep available from its input,
   * and writes the timesteps to separate files, otherwise, the timesteps are written
   * in one file.
   *
   * The Default is OFF.
   */
  vtkSetMacro(WriteAllTimeStepsSeparately, bool);
  vtkGetMacro(WriteAllTimeStepsSeparately, bool);
  vtkBooleanMacro(WriteAllTimeStepsSeparately, bool);
  ///@}

  ///@{
  /**
   * Provides an option to pad the time step when writing out time series data.
   * Only allow this format: ABC%.Xd where ABC is an arbitrary string which may
   * or may not exist and d must exist and d must be the last character
   * '.' and X may or may not exist, X must be an integer if it exists.
   * Default is nullptr.
   */
  vtkGetStringMacro(FileNameSuffix);
  vtkSetStringMacro(FileNameSuffix);
  ///@}

  ///@{
  /**
   * Get/Set if StringDelimiter must be used for string data.
   * True by default.
   */
  vtkSetMacro(UseStringDelimiter, bool);
  vtkGetMacro(UseStringDelimiter, bool);
  ///@}

  ///@{
  /**
   * Get/Set the precision to use for printing numeric values.
   * Default is 5.
   */
  vtkSetClampMacro(Precision, int, 0, VTK_INT_MAX);
  vtkGetMacro(Precision, int);
  ///@}

  ///@{
  /**
   * Get/Set whether scientific notation is used for numeric values.
   */
  vtkSetMacro(UseScientificNotation, bool);
  vtkGetMacro(UseScientificNotation, bool);
  vtkBooleanMacro(UseScientificNotation, bool);
  ///@}

  ///@{
  /**
   * Get/set the attribute data to write if the input is either
   * a vtkDataSet or composite of vtkDataSets. 0 is for point data (vtkDataObject::POINT),
   * 1 is for cell data (vtkDataObject::CELL) and 2 is for field data (vtkDataObject::FIELD).
   * Default is 0.
   */
  vtkSetClampMacro(FieldAssociation, int, 0, vtkDataObject::NUMBER_OF_ASSOCIATIONS - 1);
  vtkGetMacro(FieldAssociation, int);
  ///@}

  ///@{
  /**
   * Get/Set whether to add additional meta-data to the field data such as
   * point coordinates (when point attributes are selected and input is pointset)
   * or structured coordinates etc. if the input is either a vtkDataSet or composite
   * of vtkDataSets.
   */
  vtkSetMacro(AddMetaData, bool);
  vtkGetMacro(AddMetaData, bool);
  vtkBooleanMacro(AddMetaData, bool);
  ///@}

  ///@{
  /**
   * When set to true (default is false), if the input data set has time, then the
   * time information will be saved under the column named "Time".
   */
  vtkSetMacro(AddTime, bool);
  vtkGetMacro(AddTime, bool);
  vtkBooleanMacro(AddTime, bool);
  ///@}

  ///@{
  /**
   * When set to true (default is false), if the input data set has time, then the
   * time-step information will be saved under the column named "TimeStep".
   */
  vtkSetMacro(AddTimeStep, bool);
  vtkGetMacro(AddTimeStep, bool);
  vtkBooleanMacro(AddTimeStep, bool);
  ///@}

  ///@{
  /**
   * Internal method: decorates the "string" with the "StringDelimiter" if
   * UseStringDelimiter is true.
   */
  std::string GetString(std::string string);
  ///@}

protected:
  igwCSVWriter();
  ~igwCSVWriter() override;

  void WriteData() override;

  // see algorithm for more info.
  // This writer takes in vtkTable, vtkDataSet or vtkCompositeDataSet.
  int FillInputPortInformation(int port, vtkInformation* info) override;

  int RequestInformation(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);
  int RequestUpdateExtent(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);
  int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;

  // see algorithm for more info. needed here so we can request pieces.
  int ProcessRequest(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector) override;

  char* FileName;
  bool WriteAllTimeSteps;
  bool WriteAllTimeStepsSeparately;
  char* FileNameSuffix;
  char* FieldDelimiter;
  char* StringDelimiter;
  bool UseStringDelimiter;
  int Precision;
  bool UseScientificNotation;
  int FieldAssociation;
  bool AddMetaData;
  bool AddTimeStep;
  bool AddTime;

  vtkMultiProcessController* Controller;

  vtkDoubleArray* TimeValues;
  int CurrentTimeIndex;
  int NumberOfTimeSteps;

private:
  igwCSVWriter(const igwCSVWriter&) = delete;
  void operator=(const igwCSVWriter&) = delete;

  class CSVFile;
};

#endif
