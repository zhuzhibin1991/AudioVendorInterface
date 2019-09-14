#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/resource.h>
#include <android/log.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <time.h>
#endif  // _WIND32

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "AudioVendorInterface", __VA_ARGS__))
#define LOGW(...) ((void)__android_log_print(ANDROID_LOG_WARN, "AudioVendorInterface", __VA_ARGS__))
