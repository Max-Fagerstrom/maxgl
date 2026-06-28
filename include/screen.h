#pragma once
#include <color.h>

class Screen {
public:
    static int Initialize();
    static void Cleanup();
    // swap buffers, do events, close app on return != 0
    static int Update();

    static void SetResolution(int width, int height);
    static int GetWidth();
    static int GetHeight();
    static void GetResolution(int* width, int* height);

    static void SetWindowTitle(const char* title);

    static void SetPixel(int x, int y, Color color);
    static void Clear(); 
    
    // super basic drawing functions
    static void SetDrawColor(Color color);
    static void DrawPixel(int x, int y);
};