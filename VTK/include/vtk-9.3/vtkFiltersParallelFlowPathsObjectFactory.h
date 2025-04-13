// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause

#ifndef vtkFiltersParallelFlowPathsObjectFactory_h
#define vtkFiltersParallelFlowPathsObjectFactory_h

#include "vtkFiltersParallelFlowPathsModule.h" // For export macro
#include "vtkObjectFactory.h"

VTK_ABI_NAMESPACE_BEGIN

class VTKFILTERSPARALLELFLOWPATHS_EXPORT vtkFiltersParallelFlowPathsObjectFactory : public vtkObjectFactory
{
public:
  static vtkFiltersParallelFlowPathsObjectFactory * New();
  vtkTypeMacro(vtkFiltersParallelFlowPathsObjectFactory, vtkObjectFactory);

  const char * GetDescription() override { return "vtkFiltersParallelFlowPaths factory overrides."; }

  const char * GetVTKSourceVersion() override;

  void PrintSelf(ostream &os, vtkIndent indent) override;

protected:
  vtkFiltersParallelFlowPathsObjectFactory();

private:
  vtkFiltersParallelFlowPathsObjectFactory(const vtkFiltersParallelFlowPathsObjectFactory&) = delete;
  void operator=(const vtkFiltersParallelFlowPathsObjectFactory&) = delete;
};

VTK_ABI_NAMESPACE_END

#endif // vtkFiltersParallelFlowPathsObjectFactory_h
