/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class quickfix_MSSQLStoreFactory */

#ifndef _Included_quickfix_MSSQLStoreFactory
#define _Included_quickfix_MSSQLStoreFactory
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     quickfix_MSSQLStoreFactory
 * Method:    create
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_quickfix_MSSQLStoreFactory_create__
  (JNIEnv *, jobject);

/*
 * Class:     quickfix_MSSQLStoreFactory
 * Method:    destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_quickfix_MSSQLStoreFactory_destroy
  (JNIEnv *, jobject);

/*
 * Class:     quickfix_MSSQLStoreFactory
 * Method:    create
 * Signature: (Lquickfix/SessionID;)Lquickfix/MessageStore;
 */
JNIEXPORT jobject JNICALL Java_quickfix_MSSQLStoreFactory_create__Lquickfix_SessionID_2
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
