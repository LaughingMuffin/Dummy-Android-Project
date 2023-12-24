//
// Created by Laughing Muffin on 04.08.2023
//

#pragma once
//==================================================================================================
#include "Common.h"
#include "MyFont.hpp"

//==================================================================================================
bool isDrawn = false;
int glWidth = 0;
int glHeight = 0;
int screenWidth = 0;
int screenHeight = 0;
auto windowWidth = 300;
//==================================================================================================
HOOK_DEF(void, Input, void *thiz, void *ex_ab, void *ex_ac) {
    orig_Input(thiz, ex_ab, ex_ac);
    if (isDrawn)
        ImGui_ImplAndroid_HandleInputEvent((AInputEvent *) thiz,
                                           {(float) screenWidth / (float) glWidth,
                                            (float) screenHeight / (float) glHeight},
                                           true
        );
}

//==================================================================================================
void initImGuiMenu() {
    if (isDrawn) return;

    ImGui::CreateContext();
    ImGuiStyle *style = &ImGui::GetStyle();
    style->WindowTitleAlign = ImVec2(0, 0.50);
    style->FrameBorderSize = 1;
    style->WindowRounding = 5.3f;
    style->ScrollbarRounding = 0;
    style->FramePadding = ImVec2(8, 6);
    style->ScaleAllSizes(2.0f);
    style->ScrollbarSize /= 1;
    style->WindowMinSize = ImVec2(400, 180);

    ImGuiIO *io = &ImGui::GetIO();

    ImGui_ImplAndroid_Init();
    ImGui_ImplOpenGL3_Init(OBFUSCATE("#version 100"));

    ImFontConfig font_cfg;
    io->Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t *>(myFont), sizeof(myFont), 26.0f);

    font_cfg.SizePixels = 26.0f;
    io->Fonts->AddFontDefault(&font_cfg);

    isDrawn = true;
}

//==================================================================================================
void drawMenu() {

    if (!isDrawn) return;

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    float winWidth = glWidth < 850 ? glWidth * 0.95f : 850.0f;

    ImGui::SetNextWindowPos(ImVec2(glWidth * 0.05f, glHeight * 0.10f), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize({winWidth, 0.0f});
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_::ImGuiCond_Once);

    ImGuiStyle *style = &ImGui::GetStyle();
    ImVec4 *colors = style->Colors;

    ImGui::Begin(OBFUSCATE("@androidrepublic.org - Hello from inside"));
    ImGui::Columns(2);

    ImGui::SetColumnWidth(-1, windowWidth);

    ImGui::SeparatorText(OBFUSCATE("##TOP_SPACE"));
    ImGui::Text("GAY!");

    ImGui::SeparatorText(OBFUSCATE("##GAY_SEPARATOR_1"));
    ImGui::Spacing();

    ImGui::Spacing();
    ImGui::SeparatorText(OBFUSCATE("##GAY_SEPARATOR_2"));
    ImGui::SeparatorText(OBFUSCATE("##BOT_SPACE_A"));


    ImGui::End();

    ImGui::Render();
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
//==================================================================================================
HOOK_DEF(EGLBoolean, swapBuffers, EGLDisplay eglDisplay, EGLSurface eglSurface) {
    EGLint w, h;
    eglQuerySurface(eglDisplay, eglSurface, EGL_WIDTH, &w);
    eglQuerySurface(eglDisplay, eglSurface, EGL_HEIGHT, &h);

    glWidth = w;
    glHeight = h;

    initImGuiMenu();

    drawMenu();

    return orig_swapBuffers(eglDisplay, eglSurface);
}
//==================================================================================================
HOOK_DEF(int32_t, getANativeWindow_getWidth, ANativeWindow* window) {
    screenWidth = orig_getANativeWindow_getWidth(window);
    return screenWidth;
}
//==================================================================================================
HOOK_DEF(int32_t, getANativeWindow_getHeight, ANativeWindow* window) {
    screenHeight = orig_getANativeWindow_getHeight(window);
    return screenHeight;
}
//==================================================================================================