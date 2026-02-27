#pragma once
#include <memory>
#include <map>
#include <unordered_map>
#include <stdio.h>
#include <string>
#include <vector>
#include <optional>

namespace Nonsense
{
////////////////////////////////////////////////////////////

// common data types
template <typename T>
using TUniquePtr = std::unique_ptr<T>;

template <typename T>
using TSharedPtr = std::shared_ptr<T>;

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
// TODO: create a logger, disable the log in the Shipping build
#define NS_LOG(Message, ...) printf(Message "\n", ##__VA_ARGS__)



} // namespace Nonsense