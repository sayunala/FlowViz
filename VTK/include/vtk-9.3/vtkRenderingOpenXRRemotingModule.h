
#ifndef VTKRENDERINGOPENXRREMOTING_EXPORT_H
#define VTKRENDERINGOPENXRREMOTING_EXPORT_H

#ifdef VTKRENDERINGOPENXRREMOTING_STATIC_DEFINE
#  define VTKRENDERINGOPENXRREMOTING_EXPORT
#  define VTKRENDERINGOPENXRREMOTING_NO_EXPORT
#else
#  ifndef VTKRENDERINGOPENXRREMOTING_EXPORT
#    ifdef RenderingOpenXRRemoting_EXPORTS
        /* We are building this library */
#      define VTKRENDERINGOPENXRREMOTING_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define VTKRENDERINGOPENXRREMOTING_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef VTKRENDERINGOPENXRREMOTING_NO_EXPORT
#    define VTKRENDERINGOPENXRREMOTING_NO_EXPORT 
#  endif
#endif

#ifndef VTKRENDERINGOPENXRREMOTING_DEPRECATED
#  define VTKRENDERINGOPENXRREMOTING_DEPRECATED __declspec(deprecated)
#endif

#ifndef VTKRENDERINGOPENXRREMOTING_DEPRECATED_EXPORT
#  define VTKRENDERINGOPENXRREMOTING_DEPRECATED_EXPORT VTKRENDERINGOPENXRREMOTING_EXPORT VTKRENDERINGOPENXRREMOTING_DEPRECATED
#endif

#ifndef VTKRENDERINGOPENXRREMOTING_DEPRECATED_NO_EXPORT
#  define VTKRENDERINGOPENXRREMOTING_DEPRECATED_NO_EXPORT VTKRENDERINGOPENXRREMOTING_NO_EXPORT VTKRENDERINGOPENXRREMOTING_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKRENDERINGOPENXRREMOTING_NO_DEPRECATED
#    define VTKRENDERINGOPENXRREMOTING_NO_DEPRECATED
#  endif
#endif

/* VTK-HeaderTest-Exclude: vtkRenderingOpenXRRemotingModule.h */

/* Include ABI Namespace */
#include "vtkABINamespace.h"

#endif /* VTKRENDERINGOPENXRREMOTING_EXPORT_H */
