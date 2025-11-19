

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, LIBID_ProjectFramework,0x0D49BDDB,0xC6E9,0x4DE6,0xBD,0x08,0xFD,0xFE,0x9E,0x37,0x94,0xCA);


MIDL_DEFINE_GUID(IID, IID_IPlugin,0xA5F2B3C4,0xD5E6,0x47F8,0x9A,0x0B,0x1C,0x2D,0x3E,0x4F,0x5A,0x6B);


MIDL_DEFINE_GUID(IID, IID_I3DObject,0xB6F3C4D5,0xE6F7,0x48A9,0x0B,0x1C,0x2D,0x3E,0x4F,0x5A,0x6B,0x7C);


MIDL_DEFINE_GUID(IID, DIID_IProjectFramework,0x68DA994E,0xAF0D,0x4ECB,0x81,0x10,0x00,0xB1,0xFB,0xED,0x4F,0x1C);


MIDL_DEFINE_GUID(CLSID, CLSID_CProjectFrameworkDoc,0x97C65011,0xD049,0x4BC1,0xA5,0x7A,0x20,0xB7,0x91,0xC4,0xD3,0x14);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



