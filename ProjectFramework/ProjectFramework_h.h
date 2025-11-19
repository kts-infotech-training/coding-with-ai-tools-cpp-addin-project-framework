

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Sat Nov 08 21:13:23 2025
 */
/* Compiler settings for ProjectFramework.idl:
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


#ifndef __ProjectFramework_h_h__
#define __ProjectFramework_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IPlugin_FWD_DEFINED__
#define __IPlugin_FWD_DEFINED__
typedef interface IPlugin IPlugin;

#endif 	/* __IPlugin_FWD_DEFINED__ */


#ifndef __I3DObject_FWD_DEFINED__
#define __I3DObject_FWD_DEFINED__
typedef interface I3DObject I3DObject;

#endif 	/* __I3DObject_FWD_DEFINED__ */


#ifndef __IProjectFramework_FWD_DEFINED__
#define __IProjectFramework_FWD_DEFINED__
typedef interface IProjectFramework IProjectFramework;

#endif 	/* __IProjectFramework_FWD_DEFINED__ */


#ifndef __CProjectFrameworkDoc_FWD_DEFINED__
#define __CProjectFrameworkDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CProjectFrameworkDoc CProjectFrameworkDoc;
#else
typedef struct CProjectFrameworkDoc CProjectFrameworkDoc;
#endif /* __cplusplus */

#endif 	/* __CProjectFrameworkDoc_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __ProjectFramework_LIBRARY_DEFINED__
#define __ProjectFramework_LIBRARY_DEFINED__

/* library ProjectFramework */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_ProjectFramework;

#ifndef __IPlugin_INTERFACE_DEFINED__
#define __IPlugin_INTERFACE_DEFINED__

/* interface IPlugin */
/* [unique][dual][uuid][object] */ 


EXTERN_C const IID IID_IPlugin;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A5F2B3C4-D5E6-47F8-9A0B-1C2D3E4F5A6B")
    IPlugin : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPluginName( 
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetPluginVersion( 
            /* [retval][out] */ BSTR *pVersion) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetObjectCount( 
            /* [retval][out] */ long *pCount) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetObjectName( 
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE CreateObject( 
            /* [in] */ long index,
            /* [retval][out] */ IDispatch **ppObject) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Initialize( 
            /* [in] */ IDispatch *pHost) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Shutdown( void) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IPluginVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IPlugin * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IPlugin * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IPlugin * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IPlugin * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IPlugin * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IPlugin * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IPlugin * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetPluginName )( 
            IPlugin * This,
            /* [retval][out] */ BSTR *pName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetPluginVersion )( 
            IPlugin * This,
            /* [retval][out] */ BSTR *pVersion);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetObjectCount )( 
            IPlugin * This,
            /* [retval][out] */ long *pCount);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetObjectName )( 
            IPlugin * This,
            /* [in] */ long index,
            /* [retval][out] */ BSTR *pName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *CreateObject )( 
            IPlugin * This,
            /* [in] */ long index,
            /* [retval][out] */ IDispatch **ppObject);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Initialize )( 
            IPlugin * This,
            /* [in] */ IDispatch *pHost);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Shutdown )( 
            IPlugin * This);
        
        END_INTERFACE
    } IPluginVtbl;

    interface IPlugin
    {
        CONST_VTBL struct IPluginVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IPlugin_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IPlugin_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IPlugin_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IPlugin_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IPlugin_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IPlugin_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IPlugin_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IPlugin_GetPluginName(This,pName)	\
    ( (This)->lpVtbl -> GetPluginName(This,pName) ) 

#define IPlugin_GetPluginVersion(This,pVersion)	\
    ( (This)->lpVtbl -> GetPluginVersion(This,pVersion) ) 

#define IPlugin_GetObjectCount(This,pCount)	\
    ( (This)->lpVtbl -> GetObjectCount(This,pCount) ) 

#define IPlugin_GetObjectName(This,index,pName)	\
    ( (This)->lpVtbl -> GetObjectName(This,index,pName) ) 

#define IPlugin_CreateObject(This,index,ppObject)	\
    ( (This)->lpVtbl -> CreateObject(This,index,ppObject) ) 

#define IPlugin_Initialize(This,pHost)	\
    ( (This)->lpVtbl -> Initialize(This,pHost) ) 

#define IPlugin_Shutdown(This)	\
    ( (This)->lpVtbl -> Shutdown(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IPlugin_INTERFACE_DEFINED__ */


#ifndef __I3DObject_INTERFACE_DEFINED__
#define __I3DObject_INTERFACE_DEFINED__

/* interface I3DObject */
/* [unique][dual][uuid][object] */ 


EXTERN_C const IID IID_I3DObject;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("B6F3C4D5-E6F7-48A9-0B1C-2D3E4F5A6B7C")
    I3DObject : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetObjectName( 
            /* [retval][out] */ BSTR *pName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Draw( 
            /* [in] */ long hDC,
            /* [in] */ long rectLeft,
            /* [in] */ long rectTop,
            /* [in] */ long rectRight,
            /* [in] */ long rectBottom,
            /* [in] */ double angleX,
            /* [in] */ double angleY) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct I3DObjectVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            I3DObject * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            I3DObject * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            I3DObject * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            I3DObject * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            I3DObject * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            I3DObject * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            I3DObject * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetObjectName )( 
            I3DObject * This,
            /* [retval][out] */ BSTR *pName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Draw )( 
            I3DObject * This,
            /* [in] */ long hDC,
            /* [in] */ long rectLeft,
            /* [in] */ long rectTop,
            /* [in] */ long rectRight,
            /* [in] */ long rectBottom,
            /* [in] */ double angleX,
            /* [in] */ double angleY);
        
        END_INTERFACE
    } I3DObjectVtbl;

    interface I3DObject
    {
        CONST_VTBL struct I3DObjectVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define I3DObject_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define I3DObject_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define I3DObject_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define I3DObject_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define I3DObject_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define I3DObject_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define I3DObject_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define I3DObject_GetObjectName(This,pName)	\
    ( (This)->lpVtbl -> GetObjectName(This,pName) ) 

#define I3DObject_Draw(This,hDC,rectLeft,rectTop,rectRight,rectBottom,angleX,angleY)	\
    ( (This)->lpVtbl -> Draw(This,hDC,rectLeft,rectTop,rectRight,rectBottom,angleX,angleY) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __I3DObject_INTERFACE_DEFINED__ */


#ifndef __IProjectFramework_DISPINTERFACE_DEFINED__
#define __IProjectFramework_DISPINTERFACE_DEFINED__

/* dispinterface IProjectFramework */
/* [uuid] */ 


EXTERN_C const IID DIID_IProjectFramework;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("68DA994E-AF0D-4ECB-8110-00B1FBED4F1C")
    IProjectFramework : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IProjectFrameworkVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IProjectFramework * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IProjectFramework * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IProjectFramework * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IProjectFramework * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IProjectFramework * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IProjectFramework * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IProjectFramework * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } IProjectFrameworkVtbl;

    interface IProjectFramework
    {
        CONST_VTBL struct IProjectFrameworkVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IProjectFramework_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IProjectFramework_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IProjectFramework_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IProjectFramework_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IProjectFramework_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IProjectFramework_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IProjectFramework_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IProjectFramework_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CProjectFrameworkDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("97C65011-D049-4BC1-A57A-20B791C4D314")
CProjectFrameworkDoc;
#endif
#endif /* __ProjectFramework_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


