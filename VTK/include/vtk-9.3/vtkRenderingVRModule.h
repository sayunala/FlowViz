
#ifndef VTKRENDERINGVR_EXPORT_H
#define VTKRENDERINGVR_EXPORT_H

#ifdef VTKRENDERINGVR_STATIC_DEFINE
#  define VTKRENDERINGVR_EXPORT
#  define VTKRENDERINGVR_NO_EXPORT
#else
#  ifndef VTKRENDERINGVR_EXPORT
#    ifdef RenderingVR_EXPORTS
        /* We are building this library */
#      define VTKRENDERINGVR_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define VTKRENDERINGVR_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef VTKRENDERINGVR_NO_EXPORT
#    define VTKRENDERINGVR_NO_EXPORT 
#  endif
#endif

#ifndef VTKRENDERINGVR_DEPRECATED
#  define VTKRENDERINGVR_DEPRECATED __declspec(deprecated)
#endif

#ifndef VTKRENDERINGVR_DEPRECATED_EXPORT
#  define VTKRENDERINGVR_DEPRECATED_EXPORT VTKRENDERINGVR_EXPORT VTKRENDERINGVR_DEPRECATED
#endif

#ifndef VTKRENDERINGVR_DEPRECATED_NO_EXPORT
#  define VTKRENDERINGVR_DEPRECATED_NO_EXPORT VTKRENDERINGVR_NO_EXPORT VTKRENDERINGVR_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKRENDERINGVR_NO_DEPRECATED
#    define VTKRENDERINGVR_NO_DEPRECATED
#  endif
#endif

/* VTK-HeaderTest-Exclude: vtkRenderingVRModule.h */

/* Include ABI Namespace */
#include "vtkABINamespace.h"
/* AutoInit dependencies. */
#include "vtkIOImageModule.h"
#include "vtkInteractionStyleModule.h"
#include "vtkRenderingOpenGL2Module.h"
#include "vtkRenderingVolumeOpenGL2Module.h"


/* AutoInit implementations. */
#ifdef vtkRenderingVR_AUTOINIT_INCLUDE
#include vtkRenderingVR_AUTOINIT_INCLUDE
#endif
#ifdef vtkRenderingVR_AUTOINIT
#include "vtkAutoInit.h"
VTK_MODULE_AUTOINIT(vtkRenderingVR)
#endif

#endif /* VTKRENDERINGVR_EXPORT_H */
