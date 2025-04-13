// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause

#ifndef vtkAcceleratorsVTKmFiltersObjectFactory_h
#define vtkAcceleratorsVTKmFiltersObjectFactory_h

#include "vtkAcceleratorsVTKmFiltersModule.h" // For export macro
#include "vtkObjectFactory.h"

VTK_ABI_NAMESPACE_BEGIN

class VTKACCELERATORSVTKMFILTERS_EXPORT vtkAcceleratorsVTKmFiltersObjectFactory : public vtkObjectFactory
{
public:
  static vtkAcceleratorsVTKmFiltersObjectFactory * New();
  vtkTypeMacro(vtkAcceleratorsVTKmFiltersObjectFactory, vtkObjectFactory);

  const char * GetDescription() override { return "vtkAcceleratorsVTKmFilters factory overrides."; }

  const char * GetVTKSourceVersion() override;

  void PrintSelf(ostream &os, vtkIndent indent) override;

protected:
  vtkAcceleratorsVTKmFiltersObjectFactory();

private:
  vtkAcceleratorsVTKmFiltersObjectFactory(const vtkAcceleratorsVTKmFiltersObjectFactory&) = delete;
  void operator=(const vtkAcceleratorsVTKmFiltersObjectFactory&) = delete;
};

VTK_ABI_NAMESPACE_END

#endif // vtkAcceleratorsVTKmFiltersObjectFactory_h
