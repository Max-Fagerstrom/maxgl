// 2d drawing on screen
#include <maxgl.h>
#include <screen.h>
#include <stdlib.h>

// basic ones just pass through to screen functions
void SetDrawColor(Color color) {
    Screen::SetDrawColor(color);
}

void DrawPixel(int x, int y) {
    Screen::DrawPixel(x, y);
}

// point struct wrappers
void DrawPixel(Point p) {
    DrawPixel(p.x, p.y);
}
void DrawLine(Point p0, Point p1) {
    DrawLine(p0.x, p0.y, p1.x, p1.y);
}

// line drawing
static void drawLineLow(int x0, int y0, int x1, int y1) {
    int dx, dy, D, x, y, yi;
    dx = x1 - x0;
    dy = y1 - y0;

    yi = 1;

    if (dy < 0) {
        yi = -1;
        dy = -dy;
    }
    D = (2 * dy) - dx;
    y = y0;
    x = x0;

    while (x <= x1) {
        Screen::DrawPixel(x, y);
        if (D >= 0) {
            y = y + yi;
            D = D + (2 * (dy - dx));
        } else {
            D = D + 2 * dy;
        }
        x++;
    }
}

static void drawLineHigh(int x0, int y0, int x1, int y1) {
    int dx, dy, D, x, y, xi;
    dx = x1 - x0;
    dy = y1 - y0;

    xi = 1;

    if (dx < 0) {
        xi = -1;
        dx = -dx;
    }
    D = (2 * dx) - dy;
    x = x0;
    y = y0;

    while (y <= y1) {
        Screen::DrawPixel(x, y);
        if (D >= 0) {
            x = x + xi;
            D = D + (2 * (dx - dy));
        } else {
            D = D + 2 * dx;
        }
        y++;
    }
}

void DrawLine(int x0, int y0, int x1, int y1) {
    if (abs(y1 - y0) < abs(x1 - x0)) {
        if (x0 > x1) {
            drawLineLow(x1, y1, x0, y0);
        }
        else {
            drawLineLow(x0, y0, x1, y1);
        }
    } else {
        if (y0 > y1) {
            drawLineHigh(x1, y1, x0, y0);
        }
        else {
            drawLineHigh(x0, y0, x1, y1);
        }
    }

}