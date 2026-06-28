
#include "maxgl.h"
#include "screen.h"

void GetResolution(int* width, int* height) {
    Screen::GetResolution(width, height);
}

void ClearScreen() {
    Screen::Clear();
}

int number() {
    return 7;
}

int Initialize() {
    return Screen::Initialize();
}
void Cleanup() {
    Screen::Cleanup();
}

int Update() {
    return Screen::Update();
}
