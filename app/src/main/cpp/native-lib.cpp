#include <jni.h>
#include <string>
#include <lua.h>
#include <lauxlib.h>

void lua_something() {
  lua_State *L = luaL_newstate();
}

extern "C" JNIEXPORT jstring JNICALL
Java_it_couchgamessoftware_helloworld_metal_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

  lua_something();
  
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
