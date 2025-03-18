#define CLAY_IMPLEMENTATION
#include "../include/clay.h"
#include "../include/renderer/clay_renderer_raylib.c"

void HandleClayErrors(Clay_ErrorData errorData) {
    // See the Clay_ErrorData struct for more information
    printf("%s", errorData.errorText.chars);
    // switch(errorData.errorType) {
    //     // etc
    // }
}

int main()
{
  Clay_Raylib_Initialize(720, 480, "Template v0.0.0", FLAG_WINDOW_RESIZABLE);


  Font fonts[1];
  fonts[0] = LoadFontEx("res/fonts/Rubik/Rubik-VariableFont_wght.ttf", 48, 0, 400);
  SetTextureFilter(fonts[0].texture, TEXTURE_FILTER_BILINEAR);


  uint64_t totalMemorySize = Clay_MinMemorySize();
  Clay_Arena arena = Clay_CreateArenaWithCapacityAndMemory(totalMemorySize, (char *)malloc(totalMemorySize));
  Clay_Initialize(arena, (Clay_Dimensions){.width = (float)GetScreenWidth(), .height = (float)GetScreenHeight()}, (Clay_ErrorHandler) {HandleClayErrors});

  while (!WindowShouldClose())
  {
    Clay_SetLayoutDimensions((Clay_Dimensions) {.width = (float)GetScreenWidth(), .height = (float)GetScreenHeight()});

    Clay_BeginLayout();
    // Build UI here

    CLAY({
      .backgroundColor = {43, 41, 51, 255},
      .layout = {
        .layoutDirection = CLAY_TOP_TO_BOTTOM,
        .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
        .sizing = {
          .width = CLAY_SIZING_GROW(),
          .height = CLAY_SIZING_GROW(),
        }
      }
    }) 
    {
      CLAY({
        .backgroundColor = {148, 146, 148, 255},
        .cornerRadius = {8, 8, 8, 8},
        .layout = {
          .sizing = {
          .width = CLAY_SIZING_PERCENT(0.4),
          .height = CLAY_SIZING_PERCENT(0.4),
        }
      }
      }) {}
    }


    Clay_RenderCommandArray renderCommands = Clay_EndLayout();

    BeginDrawing();
    ClearBackground(BLACK);

    // Write Raylib renders here.


    Clay_Raylib_Render(renderCommands, &fonts[0]);
    EndDrawing();
  }

  return 0;
}