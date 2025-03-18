#include <iostream>
#define CLAY_IMPLEMENTATION
#include "../vendor/clay/clay.h"
#include "../vendor/clay/renderers/raylib/clay_renderer_raylib.c"

void HandleClayErrors(Clay_ErrorData errorData)
{
  printf("%s", errorData.errorText.chars);
}

int main(void)
{
  Clay_Raylib_Initialize(720, 480, "Template v0.0.0", FLAG_WINDOW_RESIZABLE);

  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena clayMemory = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, (char *)malloc(totalMemorySize));
  Clay_Initialize(clayMemory, Clay_Dimensions{.width = (float)GetScreenWidth(), .height = (float)GetScreenHeight()}, Clay_ErrorHandler{HandleClayErrors});

  while (!WindowShouldClose())
  {
    Clay_SetLayoutDimensions(Clay_Dimensions{.width = (float)GetScreenWidth(), .height = (float)GetScreenHeight()});

    Clay_BeginLayout();
    // Build UI here
    CLAY(
      CLAY_RECTANGLE({.color = {43, 41, 51, 255}}),
      CLAY_LAYOUT({
        .layoutDirection = CLAY_TOP_TO_BOTTOM,
        .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
        .sizing = {
          .width = CLAY_SIZING_GROW(),
          .height = CLAY_SIZING_GROW(),
        }
      })
    ) {
      CLAY(
        CLAY_RECTANGLE ({.color = { 148, 148, 148, 255 }, .cornerRadius = CLAY_CORNER_RADIUS(8)}),
        CLAY_LAYOUT({
          .sizing = {
          .width = CLAY_SIZING_PERCENT(0.4),
          .height = CLAY_SIZING_PERCENT(0.4),
        }
        })
      ) {}
    }


    Clay_RenderCommandArray renderCommands = Clay_EndLayout();

    BeginDrawing();
    ClearBackground(BLACK);
    Clay_Raylib_Render(renderCommands);
    EndDrawing();
  }

  return 0;
}