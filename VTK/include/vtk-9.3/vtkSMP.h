// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
#ifndef vtkSMP_h
#define vtkSMP_h

/* vtkSMPTools back-end */
#define VTK_SMP_STDThread
#define VTK_SMP_BACKEND "STDThread"

// Preprocessor symbols which indicate the availability of backends.
#define VTK_SMP_ENABLE_OPENMP 0
#define VTK_SMP_ENABLE_SEQUENTIAL 1
#define VTK_SMP_ENABLE_STDTHREAD 1
#define VTK_SMP_ENABLE_TBB 0

// Defines which indicate whether the default is a specific backend.
#define VTK_SMP_DEFAULT_IMPLEMENTATION_OPENMP 0
#define VTK_SMP_DEFAULT_IMPLEMENTATION_SEQUENTIAL 0
#define VTK_SMP_DEFAULT_IMPLEMENTATION_STDTHREAD 1
#define VTK_SMP_DEFAULT_IMPLEMENTATION_TBB 0

#endif
