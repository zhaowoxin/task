#include <jni.h>
#include <android/log.h>
#include <dlfcn.h>
#include <stdio.h>

#define  LOG_TAG    "LLBTRuntime"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

#if 0
void output (JNIEnv **env, jstring input) {
  char *abc = (**env)->GetStringUTFChars(*env, input, 0);
  LOGI("%s", abc);
}
#endif

jint Java_com_example_test_Test_test(
    JNIEnv* env, jobject thiz) {

    void *libadd;
    void (*printf_call)();
    char *error_text;

    //if(libadd = dlopen("./libadd.so", RTLD_LAZY))
    if(libadd = dlopen("/data/data/com.example.test/lib/libadd.so", RTLD_LAZY))
    {
      printf_call = dlsym(libadd, "add");
      (*printf_call)("hello world");
      LOGI("add is %lx\n", *(long *)(printf_call));
      LOGI("add - libadd = %lx", *(long *)(printf_call) - *(long *)libadd);
      dlclose(libadd);
      return 0;
    }

    error_text = (char *)dlerror();
    LOGI(error_text);

    return -1;
}

