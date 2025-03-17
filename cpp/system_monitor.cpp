#include <windows.h>
#include <iostream>

#define EXPORT __declspec(dllexport)

extern "C" {
    EXPORT double get_cpu_usage() {
        FILETIME idleTime, kernelTime, userTime;
        if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
            return -1.0; // Error
        }

        static ULARGE_INTEGER prevIdle = {0}, prevKernel = {0}, prevUser = {0};
        ULARGE_INTEGER currIdle, currKernel, currUser;
        currIdle.LowPart = idleTime.dwLowDateTime;
        currIdle.HighPart = idleTime.dwHighDateTime;
        currKernel.LowPart = kernelTime.dwLowDateTime;
        currKernel.HighPart = kernelTime.dwHighDateTime;
        currUser.LowPart = userTime.dwLowDateTime;
        currUser.HighPart = userTime.dwHighDateTime;

        if (prevIdle.QuadPart == 0) { // First call, no previous data
            prevIdle = currIdle;
            prevKernel = currKernel;
            prevUser = currUser;
            Sleep(100); // Wait for a baseline
            return 0.0;
        }

        ULONGLONG idleDiff = currIdle.QuadPart - prevIdle.QuadPart;
        ULONGLONG kernelDiff = currKernel.QuadPart - prevKernel.QuadPart;
        ULONGLONG userDiff = currUser.QuadPart - prevUser.QuadPart;
        ULONGLONG totalDiff = kernelDiff + userDiff;

        prevIdle = currIdle;
        prevKernel = currKernel;
        prevUser = currUser;

        if (totalDiff == 0) return 0.0;
        double cpuUsage = 100.0 * (totalDiff - idleDiff) / totalDiff;
        return cpuUsage;
    }
}

int main() {
    std::cout << "CPU Usage: " << get_cpu_usage() << "%\n";
    Sleep(1000);
    std::cout << "CPU Usage: " << get_cpu_usage() << "%\n";
    return 0;
}