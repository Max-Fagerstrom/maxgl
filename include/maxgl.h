#pragma once
#include "color.h"

struct Point {
    float x;
    float y;
    Point() {
        x = 0;
        y = 0;
    }
    Point(float x, float y) {
        this->x = x;
        this->y = y;
    }
    void Truncate() {
        x = (int)x;
        y = (int)y;
    }
};

struct Vector {
    float x,y,z;
    Vector() {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};


int Initialize();
void Cleanup();

int Update();
void GetResolution(int* width, int* height);
void ClearScreen();
float GetDeltaTime();


// drawing functions
void SetDrawColor(Color color);
void DrawPixel(int x, int y);
void DrawLine(int x0, int y0, int x1, int y1);
void DrawRectangle(int x0, int y0, int x1, int y1);

void DrawPixel(Point p);
void DrawLine(Point p0, Point p1);
void DrawRectangle(Point p0, Point p1);
void DrawTriangle(Point p0, Point p1, Point p2);

