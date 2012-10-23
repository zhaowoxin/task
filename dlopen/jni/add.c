#include <stdio.h>
#include <jni.h>
#include <android/log.h>

#define  LOG_TAG    "LLBTRuntime"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGW(...)  __android_log_print(ANDROID_LOG_WARN,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

int add(char *abc)
{
  LOGI("real add is %lx", *(long *)add);
  LOGI("%s\n", abc);

  return 0;
}
