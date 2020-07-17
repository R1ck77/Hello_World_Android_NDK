#include <jni.h>
#include <string>
#include <libguile.h>

extern "C" JNIEXPORT jstring JNICALL
Java_it_couchgamessoftware_helloworld_metal_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

  void* x = (void*) scm_c_define;

  char buffer[1000];
  snprintf(buffer, 1000, "Header AND object reference (0x%lx)!", (unsigned long) x);
  
  char *result = strdup(buffer);
  jstring android_result = env->NewStringUTF(result);
  free(result);
  return android_result;
}
