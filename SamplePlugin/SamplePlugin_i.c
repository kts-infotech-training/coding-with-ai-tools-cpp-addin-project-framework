

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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

MIDL_DEFINE_GUID(IID, LIBID_SamplePluginLib,0xCA4AF95C,0xE63B,0x4F71,0xAF,0x72,0x0C,0x5C,0x5E,0xC2,0xD8,0x93);


MIDL_DEFINE_GUID(CLSID, CLSID_VehiclePlugin,0xB1C2D3E4,0xF5A6,0x7890,0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0x01);


MIDL_DEFINE_GUID(CLSID, CLSID_BusObject,0xB1C2D3E4,0xF5A6,0x7890,0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0x02);


MIDL_DEFINE_GUID(CLSID, CLSID_JCBObject,0xB1C2D3E4,0xF5A6,0x7890,0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0x03);


MIDL_DEFINE_GUID(CLSID, CLSID_TruckObject,0xB1C2D3E4,0xF5A6,0x7890,0x12,0x34,0x56,0x78,0x9A,0xBC,0xDE,0x04);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



