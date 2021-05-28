#ifndef KULKI_RESOURCE_HPP
#define KULKI_RESOURCE_HPP

#include <unordered_map>
#include <memory>
#include "../babel/babel.hpp"

template<typename Id, typename Resource>
requires(!babel::CONCEPTS::IS_ANY_POINTER<Resource>)
class ResourceHolder
{
    std::unordered_map<Id, std::unique_ptr<Resource>> _resource;
public:
    ResourceHolder() = default;
    ~ResourceHolder() = default;

    template<typename key,typename T>
    requires (
            !babel::CONCEPTS::IS_ANY_POINTER<T>
            && babel::CONCEPTS::IS_SAME_CONVERTIBLE<key, Id>
            && (babel::CONCEPTS::IS_SAME_CONVERTIBLE<key, Resource> || std::is_base_of_v<Resource, T>)
                    )
    void insert(key&& Key,T&& Value ) noexcept
    {
        _resource[std::forward<key>(Key)] = std::make_unique<T>(std::forward<T>(Value));
    }

    template<typename key, typename T>
    requires (
             babel::CONCEPTS::IS_SAME_CONVERTIBLE<key, Id>
            && std::is_base_of_v<Resource, T>
    )
    void insert(key&& Key, std::unique_ptr<T>&& ValuePTR ) noexcept
    {
        _resource[std::forward<key>(Key)] =  std::move(ValuePTR);
    }

    template<typename T>
    requires(std::is_base_of_v<Resource, T>)
    T& get_as(const Id& Key) noexcept
    {
        return *babel::ALGO::CAST::asType<T*>(_resource.at(Key).get());
    }

    template<typename T>
    requires(std::is_base_of_v<Resource, T>)
    const T& get_as(const Id& Key) const noexcept
    {
        return *babel::ALGO::CAST::asType<T*>(_resource.at(Key).get());
    }

    const decltype(_resource)& get_map() const noexcept
    {
        return _resource;
    }


};

#endif