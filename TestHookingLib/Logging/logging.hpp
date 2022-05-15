#pragma once

namespace L
{
    void AttachConsole();
    void DetachConsole();
    bool ConsolePrint(const char* fmt, ...);
}