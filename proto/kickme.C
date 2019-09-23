#include <jni.h>
#include <stdio.h>
#include "KickMe.h"


JNIEXPORT jstring JNICALL Java_KickMe_sayKickMe(JNIEnv *env, jobject thisObj, jstring _XS) {

  const char *XS = env->GetStringUTFChars(_XS, NULL);

  printf("Kick Me! - '%s'\n",XS);

  return env->NewStringUTF("Yo, whasup?");
}

