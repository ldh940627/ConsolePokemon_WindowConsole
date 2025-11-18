// ConsoleUtils.h
#pragma once
#include <windows.h>

inline void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
