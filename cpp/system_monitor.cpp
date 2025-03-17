#include <iostream>

#ifdef _WIN32
#include <windows.h>
#define EXPORT __declspec(dllexport)
#else
#include <unistd.h>
#define EXPORT
#endif

extern "C" {
    EXPORT double get_cpu_usage() {
        #ifdef _WIN32
        Sleep(100);
        #else
        usleep(100000);
        #endif
        return 42.5;
    }
}

int main() {
    std::cout << "CPU Usage: " << get_cpu_usage() << "%\n";
    return 0;
}