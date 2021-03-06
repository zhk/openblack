#pragma once

// Generated compiled shaders using shaderc with the bin2c option
#include <generated/shaders/imgui/fs_imgui_image.sc.glsl.bin.h>
#include <generated/shaders/imgui/fs_imgui_image.sc.spv.bin.h>
#if defined(_WIN32)
#include <generated/shaders/imgui/fs_imgui_image.sc.dx11.bin.h>
#include <generated/shaders/imgui/fs_imgui_image.sc.dx9.bin.h>
#endif //  defined(_WIN32)
#if __APPLE__
#include <generated/shaders/imgui/fs_imgui_image.sc.mtl.bin.h>
#endif // __APPLE__
