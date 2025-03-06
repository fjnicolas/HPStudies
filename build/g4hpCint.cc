// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME g4hpCint

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/hptuple.hh"
#include "/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/TrackInfo_t.hh"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_ProdPart(void *p = 0);
   static void *newArray_ProdPart(Long_t size, void *p);
   static void delete_ProdPart(void *p);
   static void deleteArray_ProdPart(void *p);
   static void destruct_ProdPart(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ProdPart*)
   {
      ::ProdPart *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ProdPart >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ProdPart", ::ProdPart::Class_Version(), "", 25,
                  typeid(::ProdPart), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ProdPart::Dictionary, isa_proxy, 4,
                  sizeof(::ProdPart) );
      instance.SetNew(&new_ProdPart);
      instance.SetNewArray(&newArray_ProdPart);
      instance.SetDelete(&delete_ProdPart);
      instance.SetDeleteArray(&deleteArray_ProdPart);
      instance.SetDestructor(&destruct_ProdPart);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ProdPart*)
   {
      return GenerateInitInstanceLocal((::ProdPart*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ProdPart*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HPTuple(void *p = 0);
   static void *newArray_HPTuple(Long_t size, void *p);
   static void delete_HPTuple(void *p);
   static void deleteArray_HPTuple(void *p);
   static void destruct_HPTuple(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HPTuple*)
   {
      ::HPTuple *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HPTuple >(0);
      static ::ROOT::TGenericClassInfo 
         instance("HPTuple", ::HPTuple::Class_Version(), "", 44,
                  typeid(::HPTuple), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HPTuple::Dictionary, isa_proxy, 4,
                  sizeof(::HPTuple) );
      instance.SetNew(&new_HPTuple);
      instance.SetNewArray(&newArray_HPTuple);
      instance.SetDelete(&delete_HPTuple);
      instance.SetDeleteArray(&deleteArray_HPTuple);
      instance.SetDestructor(&destruct_HPTuple);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HPTuple*)
   {
      return GenerateInitInstanceLocal((::HPTuple*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::HPTuple*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_TrackInfo_t(void *p = 0);
   static void *newArray_TrackInfo_t(Long_t size, void *p);
   static void delete_TrackInfo_t(void *p);
   static void deleteArray_TrackInfo_t(void *p);
   static void destruct_TrackInfo_t(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::TrackInfo_t*)
   {
      ::TrackInfo_t *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::TrackInfo_t >(0);
      static ::ROOT::TGenericClassInfo 
         instance("TrackInfo_t", ::TrackInfo_t::Class_Version(), "", 11,
                  typeid(::TrackInfo_t), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::TrackInfo_t::Dictionary, isa_proxy, 4,
                  sizeof(::TrackInfo_t) );
      instance.SetNew(&new_TrackInfo_t);
      instance.SetNewArray(&newArray_TrackInfo_t);
      instance.SetDelete(&delete_TrackInfo_t);
      instance.SetDeleteArray(&deleteArray_TrackInfo_t);
      instance.SetDestructor(&destruct_TrackInfo_t);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::TrackInfo_t*)
   {
      return GenerateInitInstanceLocal((::TrackInfo_t*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::TrackInfo_t*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr ProdPart::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ProdPart::Class_Name()
{
   return "ProdPart";
}

//______________________________________________________________________________
const char *ProdPart::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ProdPart*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ProdPart::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ProdPart*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ProdPart::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ProdPart*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ProdPart::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ProdPart*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HPTuple::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *HPTuple::Class_Name()
{
   return "HPTuple";
}

//______________________________________________________________________________
const char *HPTuple::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HPTuple*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int HPTuple::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HPTuple*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HPTuple::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HPTuple*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HPTuple::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HPTuple*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr TrackInfo_t::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *TrackInfo_t::Class_Name()
{
   return "TrackInfo_t";
}

//______________________________________________________________________________
const char *TrackInfo_t::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TrackInfo_t*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int TrackInfo_t::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::TrackInfo_t*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *TrackInfo_t::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TrackInfo_t*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *TrackInfo_t::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::TrackInfo_t*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void ProdPart::Streamer(TBuffer &R__b)
{
   // Stream an object of class ProdPart.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ProdPart::Class(),this);
   } else {
      R__b.WriteClassBuffer(ProdPart::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ProdPart(void *p) {
      return  p ? new(p) ::ProdPart : new ::ProdPart;
   }
   static void *newArray_ProdPart(Long_t nElements, void *p) {
      return p ? new(p) ::ProdPart[nElements] : new ::ProdPart[nElements];
   }
   // Wrapper around operator delete
   static void delete_ProdPart(void *p) {
      delete ((::ProdPart*)p);
   }
   static void deleteArray_ProdPart(void *p) {
      delete [] ((::ProdPart*)p);
   }
   static void destruct_ProdPart(void *p) {
      typedef ::ProdPart current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ProdPart

//______________________________________________________________________________
void HPTuple::Streamer(TBuffer &R__b)
{
   // Stream an object of class HPTuple.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HPTuple::Class(),this);
   } else {
      R__b.WriteClassBuffer(HPTuple::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HPTuple(void *p) {
      return  p ? new(p) ::HPTuple : new ::HPTuple;
   }
   static void *newArray_HPTuple(Long_t nElements, void *p) {
      return p ? new(p) ::HPTuple[nElements] : new ::HPTuple[nElements];
   }
   // Wrapper around operator delete
   static void delete_HPTuple(void *p) {
      delete ((::HPTuple*)p);
   }
   static void deleteArray_HPTuple(void *p) {
      delete [] ((::HPTuple*)p);
   }
   static void destruct_HPTuple(void *p) {
      typedef ::HPTuple current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::HPTuple

//______________________________________________________________________________
void TrackInfo_t::Streamer(TBuffer &R__b)
{
   // Stream an object of class TrackInfo_t.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(TrackInfo_t::Class(),this);
   } else {
      R__b.WriteClassBuffer(TrackInfo_t::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_TrackInfo_t(void *p) {
      return  p ? new(p) ::TrackInfo_t : new ::TrackInfo_t;
   }
   static void *newArray_TrackInfo_t(Long_t nElements, void *p) {
      return p ? new(p) ::TrackInfo_t[nElements] : new ::TrackInfo_t[nElements];
   }
   // Wrapper around operator delete
   static void delete_TrackInfo_t(void *p) {
      delete ((::TrackInfo_t*)p);
   }
   static void deleteArray_TrackInfo_t(void *p) {
      delete [] ((::TrackInfo_t*)p);
   }
   static void destruct_TrackInfo_t(void *p) {
      typedef ::TrackInfo_t current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::TrackInfo_t

namespace ROOT {
   static TClass *vectorlEProdPartgR_Dictionary();
   static void vectorlEProdPartgR_TClassManip(TClass*);
   static void *new_vectorlEProdPartgR(void *p = 0);
   static void *newArray_vectorlEProdPartgR(Long_t size, void *p);
   static void delete_vectorlEProdPartgR(void *p);
   static void deleteArray_vectorlEProdPartgR(void *p);
   static void destruct_vectorlEProdPartgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<ProdPart>*)
   {
      vector<ProdPart> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<ProdPart>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<ProdPart>", -2, "vector", 214,
                  typeid(vector<ProdPart>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEProdPartgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<ProdPart>) );
      instance.SetNew(&new_vectorlEProdPartgR);
      instance.SetNewArray(&newArray_vectorlEProdPartgR);
      instance.SetDelete(&delete_vectorlEProdPartgR);
      instance.SetDeleteArray(&deleteArray_vectorlEProdPartgR);
      instance.SetDestructor(&destruct_vectorlEProdPartgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<ProdPart> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<ProdPart>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEProdPartgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<ProdPart>*)0x0)->GetClass();
      vectorlEProdPartgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEProdPartgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEProdPartgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ProdPart> : new vector<ProdPart>;
   }
   static void *newArray_vectorlEProdPartgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<ProdPart>[nElements] : new vector<ProdPart>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEProdPartgR(void *p) {
      delete ((vector<ProdPart>*)p);
   }
   static void deleteArray_vectorlEProdPartgR(void *p) {
      delete [] ((vector<ProdPart>*)p);
   }
   static void destruct_vectorlEProdPartgR(void *p) {
      typedef vector<ProdPart> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<ProdPart>

namespace {
  void TriggerDictionaryInitialization_g4hpCint_Impl() {
    static const char* headers[] = {
"/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/hptuple.hh",
"/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/TrackInfo_t.hh",
0
    };
    static const char* includePaths[] = {
"/cvmfs/larsoft.opensciencegrid.org/products/root/v6_10_08b/Linux64bit+3.10-2.17-e15-nu-prof/include",
"/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/build/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "g4hpCint dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/hptuple.hh")))  ProdPart;
class __attribute__((annotate("$clingAutoload$/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/hptuple.hh")))  HPTuple;
class __attribute__((annotate("$clingAutoload$/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/TrackInfo_t.hh")))  TrackInfo_t;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "g4hpCint dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/hptuple.hh"
#include "/exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/include/TrackInfo_t.hh"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"HPTuple", payloadCode, "@",
"ProdPart", payloadCode, "@",
"TrackInfo_t", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("g4hpCint",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_g4hpCint_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_g4hpCint_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_g4hpCint() {
  TriggerDictionaryInitialization_g4hpCint_Impl();
}
