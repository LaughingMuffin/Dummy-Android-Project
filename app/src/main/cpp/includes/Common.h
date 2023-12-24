//
// Created by Laughing Muffin on 04.08.2023
//

#pragma once
//==================================================================================================
#include <cstring>
#include <jni.h>
#include <link.h>
#include <pthread.h>
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <dlfcn.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/inotify.h>
#include <sys/uio.h>
#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include <sys/system_properties.h>
#include <inttypes.h>
#include <map>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <libgen.h>
#include <fcntl.h>
#include <elf.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <cstdio>
#include <codecvt>
#include <locale>
//==================================================================================================
#include "obfuscate.h"
#include "XorString.h"
#include "Logger.h"
#include "../libs/dobby/include/dobby.h"
#include "../libs/xdl/xdl.h"
#include "../imgui/imgui.h"
#include "../imgui/backends/imgui_impl_android.h"
#include "../imgui/backends/imgui_impl_opengl3.h"
//==================================================================================================
#define JNI_VERSION_1_6 0x00010006
//==================================================================================================
#define HOOK_DEF(ret, func, ...) \
  ret (*orig_##func)(__VA_ARGS__); \
  ret hook_##func(__VA_ARGS__)
//==================================================================================================
#define DOOK(target, ptr, orig) DobbyHook((void *)target,(void *)ptr,(void **)&orig)
#define DOOK_SYM_LIB(symName, libName, ptr, orig) DobbyHook(dlsym(dlopen(libName, 4), symName),(void *)ptr,(void **)&orig)
//==================================================================================================