#include "ResourceLocation.h"

const std::string ResourceLocation::DEFAULT_NAMESPACE = "minecraft";

ResourceLocation::ResourceLocation(const std::string& fullPath) {
    parse(fullPath);
}

ResourceLocation::ResourceLocation(const std::string& namespaceName, const std::string& path)
    : mNamespace(namespaceName), mPath(path) {
}

ResourceLocation::ResourceLocation(const char* fullPath) {
    parse(std::string(fullPath));
}

void ResourceLocation::parse(const std::string& fullPath) {
    size_t colonPos = fullPath.find(':');
    if (colonPos != std::string::npos) {
        mNamespace = fullPath.substr(0, colonPos);
        mPath = fullPath.substr(colonPos + 1);
    } else {
        mNamespace = DEFAULT_NAMESPACE;
        mPath = fullPath;
    }
}

bool ResourceLocation::operator==(const ResourceLocation& other) const {
    return mNamespace == other.mNamespace && mPath == other.mPath;
}

bool ResourceLocation::operator!=(const ResourceLocation& other) const {
    return !(*this == other);
}

bool ResourceLocation::operator<(const ResourceLocation& other) const {
    if (mNamespace < other.mNamespace) return true;
    if (mNamespace > other.mNamespace) return false;
    return mPath < other.mPath;
}
