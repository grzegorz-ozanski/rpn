#pragma once

#if defined(_WIN32)
#include <windows.h>
void set_utf8_console() {
    SetConsoleOutputCP(CP_UTF8);
}
#else
void set_utf8_console() {
    // UTF-8 is usually default in modern Linux/macOS terminals
}
#endif