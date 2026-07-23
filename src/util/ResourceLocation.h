#pragma once

#include <string>
#include <functional>

class ResourceLocation {
public:
    static const std::string DEFAULT_NAMESPACE;

    ResourceLocation(const std::string& fullPath);
    ResourceLocation(const std::string& namespaceName, const std::string& path);
    ResourceLocation(const char* fullPath);

    const std::string& getNamespace() const { return mNamespace; }
    const std::string& getPath() const { return mPath; }
    
    std::string getFullPath() const { return mNamespace + ":" + mPath; }

    bool operator==(const ResourceLocation& other) const;
    bool operator!=(const ResourceLocation& other) const;
    bool operator<(const ResourceLocation& other) const;

private:
    std::string mNamespace;
    std::string mPath;

    void parse(const std::string& fullPath);
};

namespace std {
    template <>
    struct hash<ResourceLocation> {
        size_t operator()(const ResourceLocation& k) const {
            return hash<string>()(k.getFullPath());
        }
    };
}
