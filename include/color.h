#pragma once

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    Color() {
        r = 0;
        g = 0;
        b = 0;
    }
    Color(unsigned char R, unsigned char G, unsigned char B) {
        r = R;
        g = G;
        b = B;
    }
};