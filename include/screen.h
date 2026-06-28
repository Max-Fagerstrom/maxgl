

enum ScreenColorMode {
    UINT8_256,
    FLOAT,
};

class Screen {

    class Color {
        float r;
        float g;
        float b;

    };

    static void Initialize();
    static void Cleanup();

    static void SetResolution(int width, int height);
    static int GetWidth();
    static int GetHeight();

    static void SetPixel(int x, int y, Color color);
    

};