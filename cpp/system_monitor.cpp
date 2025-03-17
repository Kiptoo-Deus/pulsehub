#include <windows.h>
#include <iostream>

#define EXPORT __declspec(dllexport)

extern "C" {
    EXPORT double get_cpu_usage() {
        FILETIME idleTime, kernelTime, userTime;
        if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
            return -1.0;
        }

        static ULARGE_INTEGER prevIdle = {0}, prevKernel = {0}, prevUser = {0};
        ULARGE_INTEGER currIdle, currKernel, currUser;
        currIdle.LowPart = idleTime.dwLowDateTime;
        currIdle.HighPart = idleTime.dwHighDateTime;
        currKernel.LowPart = kernelTime.dwLowDateTime;
        currKernel.HighPart = kernelTime.dwHighDateTime;
        currUser.LowPart = userTime.dwLowDateTime;
        currUser.HighPart = userTime.dwHighDateTime;

        if (prevIdle.QuadPart == 0) {
            prevIdle = currIdle;
            prevKernel = currKernel;
            prevUser = currUser;
            Sleep(100);
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
        return 100.0 * (totalDiff - idleDiff) / totalDiff;
    }

    EXPORT double get_memory_usage() {
        MEMORYSTATUSEX memInfo;
        memInfo.dwLength = sizeof(MEMORYSTATUSEX);
        if (!GlobalMemoryStatusEx(&memInfo)) {
            return -1.0;
        }
        double total = static_cast<double>(memInfo.ullTotalPhys);
        double avail = static_cast<double>(memInfo.ullAvailPhys);
        return 100.0 * (total - avail) / total;
    }
}

int main() {
    std::cout << "CPU Usage: " << get_cpu_usage() << "%\n";
    Sleep(1000);
    std::cout << "CPU Usage: " << get_cpu_usage() << "%\n";
    std::cout << "Memory Usage: " << get_memory_usage() << "%\n";
    return 0;
}