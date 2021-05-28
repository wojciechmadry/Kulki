#ifndef KULKI_RESOURCE_HPP
#define KULKI_RESOURCE_HPP

#include <unordered_map>
#include <memory>
#include "../babel/babel.hpp"

enum class ResourceType
{
    PICKED = 0, // Red box on screen
    RECORD = 1, // Record score number (10,20 etc.)
    RECORD_TEXT, // Record text "Record:"
    SCORE, //Actual score number (10,20 etc.)
    SCORE_TEXT, // Score text "Score:"
    NEW_GAME_BOX, // Box "New game"
    NEW_GAME_TEXT, // Text in box "New game"
    NEXT_THREE_TEXT, // Text "Next three balls"
    MAP_BEFORE_GRID, // Darker aquamarine before grid 9x9
    ENUM_SIZE
};

template< typename Resource >
requires ( !babel::CONCEPTS::IS_ANY_POINTER<Resource> )
class ResourceHolder
{
    [[nodiscard]] constexpr std::size_t cast(const ResourceType RT) const noexcept
    {
        return static_cast<std::size_t>(RT);
    }

    class Object
    {
        friend class ResourceHolder<Resource>;

        bool _autodraw; // Auto draw in loop every frame
        std::unique_ptr<Resource> _res;

        [[nodiscard]] Resource *_get() noexcept
        {
            return _res.get();
        }

        [[nodiscard]] const Resource *_get() const noexcept
        {
            return _res.get();
        }


    public:
        Object() noexcept
        {
            _res = nullptr;
            _autodraw = false;
        }

        explicit Object(std::unique_ptr<Resource> &&res, bool autodraw) noexcept
                : _autodraw(autodraw), _res(std::move(res))
        { }

        Object(Object &&Obj) noexcept
        {
            _autodraw = Obj._autodraw;
            _res = std::move(Obj._res);
        }

        Object(const Object &) = delete;

        ~Object() = default;

        Object &operator=(const Object &) = delete;

        Object &operator=(Object &&Obj) noexcept
        {
            _autodraw = Obj._autodraw;
            _res = std::move(Obj._res);
            return *this;
        }

        [[nodiscard]] explicit operator bool() const noexcept
        {
            return _autodraw && _res;
        }

        const Resource &operator*() const noexcept
        {
            return *_res;
        }

        Resource &operator*() noexcept
        {
            return *_res;
        }

    };

    std::vector<Object> _resource {cast(ResourceType::ENUM_SIZE)};
public:
    ResourceHolder() = default;

    ~ResourceHolder() = default;

    template< typename T >
    requires (
            !babel::CONCEPTS::IS_ANY_POINTER<T>
            && ( babel::CONCEPTS::IS_SAME_CONVERTIBLE<T, Resource> || std::is_base_of_v<Resource, T> )
    )
    void insert(const ResourceType Key, T &&Value, bool AutoDraw = true) noexcept
    {
        _resource[cast(Key)] = Object(std::make_unique<T>(std::forward<T>(Value)), AutoDraw);
    }

    template< typename T >
    requires(
            std::is_base_of_v<Resource, T>
    )
    void insert(const ResourceType Key, std::unique_ptr<T> &&ValuePTR, bool AutoDraw = true) noexcept
    {
        _resource[cast(Key)] = Object(std::move(ValuePTR), AutoDraw);
    }

    template< typename T >
    requires(std::is_base_of_v<Resource, T>)
    T & get_as(const ResourceType Key
    ) noexcept
    {
        return *babel::ALGO::CAST::asType<T *>(_resource[cast(Key)]._get());
    }

    template< typename T >
    requires(std::is_base_of_v<Resource, T>)
    const T &get_as(const ResourceType Key) const noexcept
    {
        return *babel::ALGO::CAST::asType<const T *>(_resource[cast(Key)]._get());
    }

    const decltype(_resource) &get_resources() const noexcept
    {
        return _resource;
    }


};

#endif