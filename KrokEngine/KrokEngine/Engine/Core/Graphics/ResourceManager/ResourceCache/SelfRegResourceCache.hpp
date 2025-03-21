#pragma once
#include "ResourceCache.hpp"
#include "../../core/counted/Counted.hpp"

template<typename TResource, typename TKey>
class SelfRegResourceCache : public ResourceCache<TResource, TKey>
{
    static_assert(std::is_base_of<Counted, TResource>::value);

public:
    virtual void AddNewResource(const TKey& a_key, const TResource a_resource) override
    {
        if (this->Exists(a_key)) throw std::invalid_argument("Key already exists, cannot add new resource, make sure to check using `Exists(TKey)`");

        // Try to find a lonely resource to overwrite
        const unsigned int index = findLonely();

        // If there are not lonely resources add the resource to the cache
        if (index == this->m_resources.size())
        {
            this->m_resources.push_back(a_resource);
        }
        else {
            std::cout << "Found a lonely Resouce, will be overwritten by a new one!" << std::endl;
            const TKey& previous = this->findByValue(index);
            this->m_resources[index] = a_resource;
            this->m_resourceMap.erase(previous);
        }

        // Add the path and index to the resource map
        this->m_resourceMap[a_key] = index;
    };

private:

    // Returns the first resource that only has one refrence (this cache)
    unsigned int findLonely()
    {
        const unsigned int size = (unsigned int)this->m_resources.size();

        for (unsigned int i = 0; i < size; i++)
        {
            // If a resource is lonely (its count is 1), return its index
            if (this->m_resources[i].IsLast()) return i;
        }

        // If no lonely resource is found, return the size of the resources vector
        return size;
    };
};

