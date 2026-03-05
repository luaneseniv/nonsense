#include "framework/Logger.h"
#include <cstdarg>
#include <chrono>
#include <ctime>

namespace Nonsense
{

Logger::Logger()
    : mFile(nullptr), mInitialized(false)
{
}

Logger::~Logger()
{
    if (mFile)
    {
        fclose(mFile);
        mFile = nullptr;
    }
}

Logger& Logger::Get()
{
    static Logger instance;
    return instance;
}

void Logger::Init(const std::string& filename)
{
    std::lock_guard<std::mutex> lock(mMutex);
    if (mInitialized) return;

    mFile = fopen(filename.c_str(), "w");
    if (mFile)
    {
        mInitialized = true;
    }
}

void Logger::Log(const char* format, ...)
{
    std::lock_guard<std::mutex> lock(mMutex);

    // timestamp
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    char timebuf[64];
    std::strftime(timebuf, sizeof(timebuf), "%Y-%m-%d %H:%M:%S", std::localtime(&now_c));

    va_list args;
    va_start(args, format);

    // write to file
    if (mFile)
    {
        fprintf(mFile, "[%s] ", timebuf);
        vfprintf(mFile, format, args);
        fprintf(mFile, "\n");
        fflush(mFile);
    }

    // write to stdout
    printf("[%s] ", timebuf);
    vprintf(format, args);
    printf("\n");
    fflush(stdout);

    va_end(args);
}

} // namespace Nonsense
