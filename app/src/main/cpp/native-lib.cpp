#include <jni.h>
#include <string>
#include <libguile.h>
#include <android/log.h>
#include <cstdio>

extern "C" JNIEXPORT jstring JNICALL
Java_it_couchgamessoftware_helloworld_metal_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject obj_this,
        jstring external_path) {

  const char *nativeString = env->GetStringUTFChars(external_path, 0);
  __android_log_print(ANDROID_LOG_VERBOSE, "HelloWorldNDK", "====== The string is: %s\n",nativeString);

  char guile_load_compiled_path[1000];
  snprintf(guile_load_compiled_path, 1000, "%s/arm64-v8a/local/lib/guile/2.2/ccache", nativeString);

  setenv("LANG", "UTF-8", 1);
  setenv("GUILE_LOAD_COMPILED_PATH", guile_load_compiled_path, 1);
  //setenv("LD_LIBRARY_PATH", "...", 1);

  env->ReleaseStringUTFChars(external_path, nativeString);
  
  scm_init_guile();
   
  char *result = strdup("Header and Guile call");
  jstring android_result = env->NewStringUTF(result);
  free(result);
  return android_result;
}
