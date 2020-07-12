#include <jni.h>
#include <string>
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}

char* lua_something() {
  lua_State *L = luaL_newstate();
  luaL_openlibs(L);
  lua_pushstring(L, "Hello, from Lua!");
  const char *result = lua_tostring(L, 1);
  lua_pop(L, 1);
  
  lua_close(L);
  return strdup(result);
}

extern "C" JNIEXPORT jstring JNICALL
Java_it_couchgamessoftware_helloworld_metal_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

  char *result = lua_something();
  jstring android_result = env->NewStringUTF(result);
  free(result);
  return android_result;
}
