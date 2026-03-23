#pragma once
#include <memory>
#include <map>
#include <unordered_map>
#include <stdio.h>
#include <string>
#include <vector>
#include <optional>
#include "framework/Logger.h"

namespace Nonsense
{
////////////////////////////////////////////////////////////

// common data types
template <typename T>
using TUniquePtr = std::unique_ptr<T>;

template <typename T, typename... Args>
TUniquePtr<T> MakeUniquePtr(Args&&... args)
{
	return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T>
using TSharedPtr = std::shared_ptr<T>;

template <typename T, typename... Args>
TSharedPtr<T> MakeSharePtr(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}

template <typename T>
using TWeakPtr = std::weak_ptr<T>;

template <typename T>
using TOptional = std::optional<T>;

template <typename T>
using TArray = std::vector<T>;

template <typename keyType, typename valueType, typename pre = std::less<keyType>>
using TMap = std::map<keyType, valueType, pre>;

template <typename keyType, typename valueType, typename hasher = std::hash<keyType>>
using TDict = std::unordered_map<keyType, valueType, hasher>;

using FString = std::string;



////////////////////////////////////////////////////////////

// Simple log for the engine
// Uses Logger to write to a file next to the executable. In non-shipping builds
// the log will also be printed to stdout.
// Default NS_LOG uses the Logger singleton
// #define NS_LOG(Message, ...) printf(Message "\n", ##__VA_ARGS__)

#define NS_LOG(Message, ...) \
	do { \
		Nonsense::Logger::Get().Log(Message, ##__VA_ARGS__); \
	} while(0)



} // namespace Nonsense