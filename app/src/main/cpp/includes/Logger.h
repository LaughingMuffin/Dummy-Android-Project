//
// Modified by Laughing Muffin on 18/12/2023
//

#ifndef Logger_h
#define Logger_h

#include <jni.h>
#include <android/log.h>

#define LOG_TAG OBFUSCATE("DUMMY-MUFFIN") //logger tag
#define DEBUG_BUILD //used to toggle logging

#ifdef DEBUG_BUILD
#define Debug_Log(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);
#define Error_Log(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);
#define Warning_Log(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__);
#define Info_Log(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);
#else
#define Debug_Log(...) //__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);
#define Error_Log(...) //__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);
#define Warning_Log(...) //__android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__);
#define Info_Log(...) //__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__);
#endif

#endif /* Logger_h */
