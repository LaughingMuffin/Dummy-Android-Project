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
#include "Includes/Logger.h"
#include "Includes/obfuscate.h"

//==================================================================================================
void *hack_thread(void *) {
    Debug_Log(OBFUSCATE("Hello from hack thread!"));
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