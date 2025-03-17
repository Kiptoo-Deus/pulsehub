#include <iostream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

extern "C" {
    double get_cpu_usage() {
      
        #ifdef _WIN32
        Sleep(100); // Windows sleep
        #else
        usleep(100000); // Unix sleep
        #endif
        return 42.5; // Dummy value
    }
}

int main() {
    std::cout << "CPU Usage: " << get_cpu_usage() << "%\n";
    return 0;
}