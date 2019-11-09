/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.38
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

namespace BerkeleyDB.Internal {

using System;
using System.Runtime.InteropServices;

internal class DB_LOCKREQ : IDisposable {
  private HandleRef swigCPtr;
  protected bool swigCMemOwn;

  internal DB_LOCKREQ(IntPtr cPtr, bool cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = new HandleRef(this, cPtr);
  }

  internal static HandleRef getCPtr(DB_LOCKREQ obj) {
    return (obj == null) ? new HandleRef(null, IntPtr.Zero) : obj.swigCPtr;
  }

  ~DB_LOCKREQ() {
    Dispose();
  }

  public virtual void Dispose() {
    lock(this) {
      if(swigCPtr.Handle != IntPtr.Zero && swigCMemOwn) {
        swigCMemOwn = false;
        libdb_csharpPINVOKE.delete_DB_LOCKREQ(swigCPtr);
      }
      swigCPtr = new HandleRef(null, IntPtr.Zero);
      GC.SuppressFinalize(this);
    }
  }

  internal db_lockop_t op {
    set {
      libdb_csharpPINVOKE.DB_LOCKREQ_op_set(swigCPtr, (int)value);
    } 
    get {
      db_lockop_t ret = (db_lockop_t)libdb_csharpPINVOKE.DB_LOCKREQ_op_get(swigCPtr);
      return ret;
    } 
  }

  internal db_lockmode_t mode {
    set {
      libdb_csharpPINVOKE.DB_LOCKREQ_mode_set(swigCPtr, (int)value);
    } 
    get {
      db_lockmode_t ret = (db_lockmode_t)libdb_csharpPINVOKE.DB_LOCKREQ_mode_get(swigCPtr);
      return ret;
    } 
  }

  internal uint timeout {
    set {
      libdb_csharpPINVOKE.DB_LOCKREQ_timeout_set(swigCPtr, value);
    } 
    get {
      uint ret = libdb_csharpPINVOKE.DB_LOCKREQ_timeout_get(swigCPtr);
      return ret;
    } 
  }

  internal DatabaseEntry obj {
    set {
      libdb_csharpPINVOKE.DB_LOCKREQ_obj_set(swigCPtr, DBT.getCPtr(DatabaseEntry.getDBT(value)));
    } 
    get {
      IntPtr cPtr = libdb_csharpPINVOKE.DB_LOCKREQ_obj_get(swigCPtr);
      DatabaseEntry ret = (cPtr == IntPtr.Zero) ? null : DatabaseEntry.fromDBT(new DBT(cPtr, false));
      return ret;
    } 
  }

  internal DB_LOCK lck {
    set {
      libdb_csharpPINVOKE.DB_LOCKREQ_lck_set(swigCPtr, DB_LOCK.getCPtr(value));
    } 
    get {
      IntPtr cPtr = libdb_csharpPINVOKE.DB_LOCKREQ_lck_get(swigCPtr);
      DB_LOCK ret = (cPtr == IntPtr.Zero) ? null : new DB_LOCK(cPtr, false);
      return ret;
    } 
  }

  internal DB_LOCKREQ() : this(libdb_csharpPINVOKE.new_DB_LOCKREQ(), true) {
  }

}

}
