#include <jni.h>
#include <string>
#include <libguile.h>

extern "C" JNIEXPORT jstring JNICALL
Java_it_couchgamessoftware_helloworld_metal_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

  scm_init_guile();
  
  char *result = strdup("Header and Guile call");
  jstring android_result = env->NewStringUTF(result);
  free(result);
  return android_result;
}
