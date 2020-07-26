#include <jni.h>
#include <string>
#include <libguile.h>
#include <android/log.h>
#include <cstdio>
#include <sys/stat.h>

#define COPY_BUFFER_SIZE 1024

void copy_file(char *src_path, char *dst_path)
{
  char buf[BUFSIZ];
  size_t size;

  FILE* source = fopen(src_path, "rb");
  FILE* dest = fopen(dst_path, "wb");

  while ((size = fread(buf, 1, BUFSIZ, source))) {
    fwrite(buf, 1, size, dest);
  }

  fclose(source);
  fclose(dest);
}

int is_dir(char *path) {
  struct stat s;
  return stat(path, &s) == 0 && s.st_mode & S_IFDIR ? 1 : 0;
}

// TODO/FIXME wasteful
int is_file(char *path) {
  struct stat s;
  return stat(path, &s) == 0 && s.st_mode & S_IFREG ? 1 : 0;
}

char *concatenate_path(char *dir, char *name)
{
  char buffer[COPY_BUFFER_SIZE];
  strncpy(dir, buffer, COPY_BUFFER_SIZE);
  strncat(buffer, "/", COPY_BUFFER_SIZE);
  strncat(buffer, name, COPY_BUFFER_SIZE);
  return strdup(buffer);
}

void copy_tree(char *element, char *src_dir, char *dst_dir)
{
  char *src_path = concatenate_path(src_dir, element);
  char *dst_path = concatenate_path(dst_dir, element);
  if(is_file(src_path)) {
    copy_file(src_path, dst_path);
  } else {
    // List files
    
  }
  free(dst_path);
  free(src_path);
}



extern "C" JNIEXPORT jstring JNICALL
Java_it_couchgamessoftware_helloworld_metal_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject obj_this,
        jstring external_path) {

  const char *nativeString = env->GetStringUTFChars(external_path, 0);
  __android_log_print(ANDROID_LOG_VERBOSE, "HelloWorldNDK", "====== The string is: %s\n",nativeString);

  char guile_load_compiled_path[1000];
  if(sizeof(void*) == 8) {
    __android_log_print(ANDROID_LOG_VERBOSE, "HelloWorldNDK", "====== Configuring for 64 bits");
    snprintf(guile_load_compiled_path, 1000, "%s/arm64-v8a/local/lib/guile/2.2/ccache", nativeString);
  } else {
    __android_log_print(ANDROID_LOG_VERBOSE, "HelloWorldNDK", "====== Configuring for 32 bits");
    snprintf(guile_load_compiled_path, 1000, "%s/armeabi-v7a/local/lib/guile/2.2/ccache", nativeString);
  }

  setenv("LANG", "UTF-8", 1);
  setenv("GUILE_LOAD_COMPILED_PATH", guile_load_compiled_path, 1);
  //setenv("LD_LIBRARY_PATH", "...", 1);

  env->ReleaseStringUTFChars(external_path, nativeString);

  scm_init_guile();
  scm_c_eval_string("(define result \"Hello, from Guile! (evaluated)\n\")");
  SCM variable = scm_c_lookup("result");
  SCM referenced = scm_variable_ref(variable);
  char *cstring = scm_to_utf8_stringn(referenced, nullptr);
  fprintf(stderr, "Guile contains: '%s'", cstring);



  jstring android_result = env->NewStringUTF(cstring);
  free(cstring);
  return android_result;
}
