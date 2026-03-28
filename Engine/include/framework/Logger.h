#pragma once
#include <string>
#include <mutex>
#include <cstdio>

namespace Nonsense
{

class Logger
{
public:
    static Logger& Get();

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;
    Logger(Logger&&) = delete;
    Logger& operator=(Logger&&) = delete;

    void Init(const std::string& filename);
    void Log(const char* format, ...);

private:
    Logger();
    ~Logger();

private:
    FILE* mFile;
    std::mutex mMutex;
    bool mInitialized;
};

} // namespace Nonsense