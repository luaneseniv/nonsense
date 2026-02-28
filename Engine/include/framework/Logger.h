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

    void Init(const std::string& filename);

    void Log(const char* format, ...);

private:
    Logger();
    ~Logger();

    FILE* mFile;
    std::mutex mMutex;
    bool mInitialized;
};

} // namespace Nonsense
