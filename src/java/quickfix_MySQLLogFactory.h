/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class quickfix_MySQLLogFactory */

#ifndef _Included_quickfix_MySQLLogFactory
#define _Included_quickfix_MySQLLogFactory
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     quickfix_MySQLLogFactory
 * Method:    _create
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_quickfix_MySQLLogFactory__1create
  (JNIEnv *, jobject);

/*
 * Class:     quickfix_MySQLLogFactory
 * Method:    _destroy
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_quickfix_MySQLLogFactory__1destroy
  (JNIEnv *, jobject);

/*
 * Class:     quickfix_MySQLLogFactory
 * Method:    create
 * Signature: ()Lquickfix/Log;
 */
JNIEXPORT jobject JNICALL Java_quickfix_MySQLLogFactory_create__
  (JNIEnv *, jobject);

/*
 * Class:     quickfix_MySQLLogFactory
 * Method:    create
 * Signature: (Lquickfix/SessionID;)Lquickfix/Log;
 */
JNIEXPORT jobject JNICALL Java_quickfix_MySQLLogFactory_create__Lquickfix_SessionID_2
  (JNIEnv *, jobject, jobject);

#ifdef __cplusplus
}
#endif
#endif
