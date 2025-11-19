

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Nov 08 21:16:13 2025
 */
/* Compiler settings for SamplePlugin.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __SamplePlugin_i_h__
#define __SamplePlugin_i_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __VehiclePlugin_FWD_DEFINED__
#define __VehiclePlugin_FWD_DEFINED__

#ifdef __cplusplus
typedef class VehiclePlugin VehiclePlugin;
#else
typedef struct VehiclePlugin VehiclePlugin;
#endif /* __cplusplus */

#endif 	/* __VehiclePlugin_FWD_DEFINED__ */


#ifndef __BusObject_FWD_DEFINED__
#define __BusObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class BusObject BusObject;
#else
typedef struct BusObject BusObject;
#endif /* __cplusplus */

#endif 	/* __BusObject_FWD_DEFINED__ */


#ifndef __JCBObject_FWD_DEFINED__
#define __JCBObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class JCBObject JCBObject;
#else
typedef struct JCBObject JCBObject;
#endif /* __cplusplus */

#endif 	/* __JCBObject_FWD_DEFINED__ */


#ifndef __TruckObject_FWD_DEFINED__
#define __TruckObject_FWD_DEFINED__

#ifdef __cplusplus
typedef class TruckObject TruckObject;
#else
typedef struct TruckObject TruckObject;
#endif /* __cplusplus */

#endif 	/* __TruckObject_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __SamplePluginLib_LIBRARY_DEFINED__
#define __SamplePluginLib_LIBRARY_DEFINED__

/* library SamplePluginLib */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_SamplePluginLib;

EXTERN_C const CLSID CLSID_VehiclePlugin;

#ifdef __cplusplus

class DECLSPEC_UUID("B1C2D3E4-F5A6-7890-1234-56789ABCDE01")
VehiclePlugin;
#endif

EXTERN_C const CLSID CLSID_BusObject;

#ifdef __cplusplus

class DECLSPEC_UUID("B1C2D3E4-F5A6-7890-1234-56789ABCDE02")
BusObject;
#endif

EXTERN_C const CLSID CLSID_JCBObject;

#ifdef __cplusplus

class DECLSPEC_UUID("B1C2D3E4-F5A6-7890-1234-56789ABCDE03")
JCBObject;
#endif

EXTERN_C const CLSID CLSID_TruckObject;

#ifdef __cplusplus

class DECLSPEC_UUID("B1C2D3E4-F5A6-7890-1234-56789ABCDE04")
TruckObject;
#endif
#endif /* __SamplePluginLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


