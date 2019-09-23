#include <jni.h>
#include <stdio.h>

#include "A64Sim.h"
#include "a64sim_interface.h"

using namespace std;

JNIEXPORT jbyteArray JNICALL Java_A64Sim_SimSerialAPI(JNIEnv *env, jobject thisObj, jbyteArray cmd_array) {
  int cmdbuf_len = env->GetArrayLength(cmd_array);
  unsigned char cmd_buf[cmdbuf_len];

  env->GetByteArrayRegion(cmd_array, 0, cmdbuf_len, reinterpret_cast<jbyte*>(cmd_buf));

  char response_buffer[16000];

  int res_buf_len;

  SimulatorQuery((void *) cmd_buf,cmdbuf_len, (void *) response_buffer, &res_buf_len);

  jbyteArray response_array = env->NewByteArray(res_buf_len);
  env->SetByteArrayRegion(response_array,0,res_buf_len,reinterpret_cast<jbyte*>(response_buffer));

  return response_array;
}

