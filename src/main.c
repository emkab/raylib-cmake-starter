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
  Clay_Context *clayContext = Clay_Initialize(arena, (Clay_Dimensions){.width = (float)GetScreenWidth(), .height = (float)GetScreenHeight()}, (Clay_ErrorHandler) {HandleClayErrors});
  Clay_SetMeasureTextFunction(Raylib_MeasureText, fonts);

  while (!WindowShouldClose())
  {
    Clay_SetLayoutDimensions((Clay_Dimensions) {.width = (float)GetScreenWidth(), .height = (float)GetScreenHeight()});

    Clay_BeginLayout();
    // Build UI here

    Clay_String fpsString = Clay__IntToString((int32_t) GetFPS()); 

    CLAY({
      .id = CLAY_ID("body"),
      .backgroundColor = {43, 41, 51, 255},
      .layout = {
        .layoutDirection = CLAY_TOP_TO_BOTTOM,
        .childAlignment = {.x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP},
        .sizing = {
          .width = CLAY_SIZING_GROW(),
          .height = CLAY_SIZING_GROW(),
        }
      }
    }) 
    {
      CLAY({
        .id = CLAY_ID("hello"),
        .layout = {
          .sizing = {
          .width = CLAY_SIZING_FIXED(GetScreenWidth() / 2.5),
          .height = CLAY_SIZING_FIXED(GetScreenHeight() / 2.5),
          },
          .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER}
        },
        .floating = {.attachTo = CLAY_ATTACH_TO_PARENT, .zIndex = 1, .attachPoints = {CLAY_ATTACH_POINT_CENTER_CENTER, CLAY_ATTACH_POINT_CENTER_CENTER}, .offset = {0, 0}},
        .backgroundColor = {148, 146, 148, 255},
        .cornerRadius = 4
      }) {
        CLAY_TEXT(
          CLAY_STRING("Hello, world!"),
          CLAY_TEXT_CONFIG({ .fontId = 0, .fontSize = 48, .textColor = {25,25,25,255}, .textAlignment = CLAY_TEXT_ALIGN_CENTER })
        );
      }

      CLAY({
        .id = CLAY_ID("fps"),
        .layout = {
          .sizing = {
            .width = CLAY_SIZING_PERCENT(0.1),
            .height = CLAY_SIZING_PERCENT(0.1)
          },
          .padding = {10, 5, 10, 5},
          .childAlignment = {.x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP}
        },
        // .backgroundColor = {148, 146, 148, 255},
        // .cornerRadius = 4
      }) {
        CLAY_TEXT(
          fpsString,
          CLAY_TEXT_CONFIG({ .fontId = 0, .fontSize = 18, .textColor = {148, 146, 148, 255}, .textAlignment = CLAY_TEXT_ALIGN_CENTER })
        );
      }
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