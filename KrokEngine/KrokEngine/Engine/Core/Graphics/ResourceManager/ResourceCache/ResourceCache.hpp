#pragma once
#include <unordered_map>
#include <iostream>
#include <type_traits>
#include "../../core/counted/Counted.hpp"

template<typename TResource, typename TKey>

class ResourceCache
{
protected:
    // A hash map to store the mapping from resource paths to indices in the resources vector
    std::unordered_map <TKey, unsigned int> m_resourceMap;
    // A vector to store the resources
    std::vector<TResource> m_resources;

public:
    virtual ~ResourceCache() { Clear(); }

protected:
    // For debug purposes
    TKey findByValue(const unsigned int a_value)
    {
        for (auto it : m_resourceMap) {
            if (it.second == a_value) return it.first;
        }

        throw std::invalid_argument("Value was not found in resourceMap");
    }

public:
    inline TResource& Get(const TKey& a_key) { return m_resources[m_resourceMap[a_key]]; };
    
    bool Exists(const TKey& a_key) const
    {
        auto it = m_resourceMap.find(a_key);
        if (it != m_resourceMap.end()) {
            return true;
        }

        return false;
    };

    void Clear()
    {
        while (!m_resources.empty()) {
            if (!m_resources.back().IsLast()) {
                std::cerr << "Warning: resource " << findByValue(((unsigned int)m_resources.size()) - 1) << " in cache is NOT the last resource, this means it cannot be cleaned up propperly" << std::endl;
            }

            m_resources.pop_back();
        }

        m_resourceMap.clear();
    }

    virtual void AddNewResource(const TKey& a_key, const TResource a_resource)
    {
        if (Exists(a_key)) throw std::invalid_argument("Key already existst, cannot add new resource, make sure to check using `Exists(TKey)`");

        m_resources.push_back(a_resource);
        m_resourceMap[a_key] = ((unsigned int)m_resources.size()) - 1;
    };
};