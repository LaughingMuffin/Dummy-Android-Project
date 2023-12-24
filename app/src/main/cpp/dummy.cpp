//
// Modified by Laughing Muffin on 18/12/2023
//

#include <iostream>
#include <jni.h>
//==================================================================================================
#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
#include "Includes/Common.h"
#include "Includes/Hooks.h"

//==================================================================================================
void *hack_thread(void *) {
    Debug_Log(OBFUSCATE("Hello from hack thread!"));

    Debug_Log("==========================================================");
    Debug_Log("===================== Initial Hooks ======================");
    Debug_Log("==========================================================");

    Debug_Log("| 1 | dl_open libEGL");
    void *g_EGL = xdl_open(OBFUSCATE("libEGL.so"), 0);
    if(g_EGL) {
        Debug_Log("| 1 | pointer is 0x%08x", g_EGL);
        Debug_Log("| 1 | dl_sym eglSwapBuffers");
        void *swapSymbolPointer = (void *) xdl_sym(g_EGL, OBFUSCATE("eglSwapBuffers"), nullptr);
        if(swapSymbolPointer) {
            Debug_Log("| 1 | pointer is 0x%08x", swapSymbolPointer);
            Debug_Log("| 1 | hook eglSwapBuffers");
            DOOK(swapSymbolPointer, hook_swapBuffers, orig_swapBuffers);
        }
    }

    Debug_Log("| 2 | dl_open libinput");
    void *g_Input = xdl_open(OBFUSCATE("libinput.so"), 0);
    if (g_Input) {
        Debug_Log("| 2 | pointer is 0x%08x", g_Input);
        Debug_Log("| 2 | dl_sym _ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE");
        void *inputSymbolPointer = (void *) xdl_sym(g_Input, OBFUSCATE("_ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE"), nullptr);
        if(inputSymbolPointer) {
            Debug_Log("| 2 | pointer is 0x%08x", inputSymbolPointer);
            Debug_Log("| 2 | hook _ZN7android13InputConsumer21initializeMotionEventEPNS_11MotionEventEPKNS_12InputMessageE");
            DOOK(inputSymbolPointer, hook_Input, orig_Input);
        }
    }
    Debug_Log("| 2 | dl_close libinput");
    xdl_close(g_Input);

    Debug_Log("| 3 | dl_open libAndroid");
    void *g_Android = xdl_open(OBFUSCATE("libandroid.so"), 0);
    if (g_Android) {
        Debug_Log("| 3 | pointer is 0x%08x", g_Android);
        Debug_Log("| 3 | dl_sym ANativeWindow_getWidth");
        void *getWidthPointer = (void *) xdl_sym(g_Android, OBFUSCATE("ANativeWindow_getWidth"), nullptr);
        if(getWidthPointer) {
            Debug_Log("| 3 | pointer is 0x%08x", getWidthPointer);
            Debug_Log("| 3 | hook ANativeWindow_getWidth");
            DOOK(getWidthPointer, hook_getANativeWindow_getWidth, orig_getANativeWindow_getWidth);
        }

        Debug_Log("| 3 | dl_sym ANativeWindow_getHeight");
        void *getHeightPointer = (void *) xdl_sym(g_Android, OBFUSCATE("ANativeWindow_getHeight"), nullptr);
        if(getHeightPointer) {
            Debug_Log("| 3 | pointer is 0x%08x", getHeightPointer);
            Debug_Log("| 3 | hook ANativeWindow_getHeight");
            DOOK(getHeightPointer, hook_getANativeWindow_getHeight, orig_getANativeWindow_getHeight);
        }
    }

    return nullptr;
}

//==================================================================================================
__attribute__((constructor))
void lib_main() {

    Debug_Log(OBFUSCATE("Hello from constructor!"));

    // Create a new thread so it does not block the main thread, means the game would not freeze
    pthread_t ptid;
    pthread_create(&ptid, nullptr, hack_thread, nullptr);
}
//==================================================================================================
JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *reserved) {

    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_6) != JNI_OK) {
        Debug_Log("Error retrieving env!");
        return JNI_ERR;
    }

    Debug_Log(OBFUSCATE("Hello from JNI_OnLoad!"));

    return JNI_VERSION_1_6;
}
//==================================================================================================