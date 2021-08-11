// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ANY_HPP_
#define BABLIB_ANY_HPP_

#include <memory>
#include "concepts/concepts.hpp"

namespace babel::ANY{
    namespace VoidAny{ class any; } //NOLINT
    namespace PolAny{ class any; } //NOLINT

    /**
*  @brief  Cast Any to T type
*  @param  Any Any to cast
*  @return Return Any casted to T type
*/
    template< typename T, typename Any >
    requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
             babel::CONCEPTS::IS_SAME<Any, PolAny::any>
    [[nodiscard]] inline T &cast_any(Any &any);

    /**
*  @brief  Cast Any to T type
*  @param  const Any const Any to cast
*  @return Return const Any casted to const T type
*/
    template< typename T, typename Any >
    requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
             babel::CONCEPTS::IS_SAME<Any, PolAny::any>
    [[nodiscard]] inline const T &cast_any(const Any &any);

    /**
*  @brief
     Void any is faster then PolAny by approx 30-40%
     USE RULES:
     1. One ANY object can't be another ANY(lvalue, like std::unique_ptr)
     2. When you create ANY object (data is not NULLPTR) then you must use destroy_any to avoid memory leak !
*/
    namespace VoidAny{

        class any
        {
            template< typename T, typename Any >
            requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
                     babel::CONCEPTS::IS_SAME<Any, PolAny::any>
            friend T &babel::ANY::cast_any(Any &any); //NOLINT
            template< typename T, typename Any >
            requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
                     babel::CONCEPTS::IS_SAME<Any, PolAny::any>
            friend const T &babel::ANY::cast_any(const Any &any);//NOLINT

            void *m_data;

            template< typename T >
            friend any make_any(T &&object) noexcept;

        public:

            any() noexcept: m_data(nullptr)
            { }

            template< typename T, typename U = typename std::decay_t<T>>
            requires babel::CONCEPTS::IS_NOT_SAME<T, any>
            explicit any(T &&obj) noexcept : m_data(new U(std::forward<T>(obj))) //NOLINT
            { }

            any(const any &other) = delete;

            any(any &&other) noexcept: m_data(other.m_data)
            {
                other.m_data = nullptr;
            }

            ~any() = default;

            [[nodiscard]] constexpr bool has_value() const noexcept
            {
                return m_data != nullptr;
            }

            void swap(any &other) noexcept
            {
                void *temp = m_data;
                m_data = other.m_data;
                other.m_data = temp;
            }

            /**
*  @brief  cast void* to T&
*  @return Casted stored object to T&
*/
            template< typename T >
            [[nodiscard]] T &cast()
            {
                if ( m_data )
                    return *static_cast<T *>(m_data);
                throw std::invalid_argument("Data is nullptr");
            }

            /**
*  @brief  cast void* to const T&
*  @return Casted stored object to  const T&
*/
            template< typename T >
            [[nodiscard]] const T &cast() const
            {
                if ( m_data )
                    return *static_cast<T *>(m_data);
                throw std::invalid_argument("Data is nullptr");
            }

            template< typename T, typename U = typename std::decay_t<T>>
            requires babel::CONCEPTS::IS_NOT_SAME<T, any>
            any &operator=(T &&object)
            {
                if ( m_data )
                    throw std::invalid_argument("Memory leak. Destroy void any first.");
                m_data = new U {std::forward<T>(object)};
                return *this;
            }

            any &operator=(const any &) = delete;

            any &operator=(any &&_any) //NOLINT
            {
                if ( _any.m_data == m_data )
                    return *this;
                if ( m_data )
                    throw std::invalid_argument("Memory leak. Destroy void any first.");
                m_data = _any.m_data;
                _any.m_data = nullptr;
                return *this;
            }

            /**
*  @brief  Destroy VoidAny -> its required when you end deal with it
*/
            template< typename T >
            void destroy_any() noexcept
            {
                delete static_cast<T *>(m_data);
                m_data = nullptr;
            }
        };


        template< typename T >
        [[nodiscard]] inline any make_any(T &&object) noexcept
        {
            return any(std::forward<T>(object));
        }

    }  // namespace VoidAny"

    /**
*  @brief
        Object must by copyable and constructible other way use VoidAny
       You dont need to remember to destroy a object,
       but its a little slower (about 30-40%).
       Its safer to avoid memory leak.
*/
    namespace PolAny{
        class any;

        template< typename T >
        [[nodiscard]] inline any make_any(T &&data) noexcept;

        class any
        {
            template< typename T, typename Any >
            requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
                     babel::CONCEPTS::IS_SAME<Any, PolAny::any>
            friend const T &babel::ANY::cast_any(const Any &any);//NOLINT
            template< typename T, typename Any >
            requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
                     babel::CONCEPTS::IS_SAME<Any, PolAny::any>
            friend T &babel::ANY::cast_any(Any &any); //NOLINT

            struct __base__any //NOLINT
            {
                virtual ~__base__any() = default;

                [[nodiscard]]  virtual std::unique_ptr<__base__any> duplicate() const noexcept = 0;
            };

            template< typename T >
            struct _data : public __base__any
            {
                T m_data;

                template< typename U = T >
                requires babel::CONCEPTS::IS_NOT_SAME<U, _data> && babel::CONCEPTS::IS_NOT_SAME<U, __base__any>
                explicit _data(U &&__data) noexcept: m_data(std::forward<U>(__data)) //NOLINT
                { }

                [[nodiscard]] std::unique_ptr<__base__any> duplicate() const noexcept override
                {
                    return std::make_unique<_data<T>>(m_data);
                }
            };

            std::unique_ptr<__base__any> m_storage;
        public:
            any() = default;

            template< typename T, typename U = typename std::decay_t<T>>
            requires babel::CONCEPTS::IS_NOT_SAME<T, any>
            explicit any(T &&object) noexcept : m_storage(std::make_unique<_data<U>>(std::forward<T>(object))) //NOLINT
            { }

            any(const any &other) noexcept: m_storage(other.m_storage->duplicate())
            {
            }

            any(any &&other) noexcept: m_storage(std::move(other.m_storage))
            {
                other.m_storage = nullptr;
            }

            ~any() noexcept
            {
                m_storage.reset();
            }


            /**
*  @brief  cast PolAny to T&
*  @return Casted stored object to T&
*/
            template< typename T >
            [[nodiscard]] T &cast()
            {
                if ( auto st = dynamic_cast<_data<T> *>(m_storage.get()) )
                    return st->m_data;
                else
                    throw std::bad_cast();
            }

            /**
*  @brief  cast PolAny to const T&
*  @return Casted stored object to const T&
*/
            template< typename T >
            [[nodiscard]] const T &cast() const
            {
                if ( auto st = dynamic_cast<_data<T> *>(m_storage.get()) )
                    return st->m_data;
                else
                    throw std::bad_cast();
            }

            /**
*  @brief  Check if stored element is T type
*  @return true -> stored object is type T, otherwise false
*/
            template< typename T >
            [[nodiscard]] bool is() const noexcept
            {
                return static_cast<bool>( dynamic_cast<_data<T> *>(m_storage.get()));
            }

            /**
*  @brief  Compare type of storage object and if they are the same, then compare object (full safe)
*  @return true -> If stored element are the same T, otherwise false
*/
            template< typename T >
            [[nodiscard]] bool cmp(const any &other) const noexcept
            {
                try
                {
                    if ( *this == other )
                        return cast_any<T>(*this) == cast_any<T>(other);
                    return false;
                }
                catch ( const std::bad_cast & )
                {
                    return false;
                }
            }

            /**
*  @brief  Compare type of storage object
*  @return true -> If stored element have the same type
*/
            [[nodiscard]] bool operator==(const any &other) const noexcept
            {
                if ( ( m_storage && other.m_storage ) == 0 )
                    return m_storage == other.m_storage;
                return typeid(m_storage.get()) == typeid(other.m_storage.get());
            }

            template< typename T, typename U = typename std::decay_t<T>>
            requires babel::CONCEPTS::IS_NOT_SAME<T, any>
            any &operator=(T &&object) noexcept
            {
                m_storage = std::make_unique<_data<U>>(std::forward<T>(object));
                return *this;
            }

            any &operator=(const any &other) noexcept
            {
                if ( this == &other )
                    return *this;
                m_storage = other.m_storage->duplicate();
                return *this;
            }

            any &operator=(any &&other) noexcept
            {
                if ( m_storage == other.m_storage )
                    return *this;
                m_storage = std::move(other.m_storage);
                other.m_storage = nullptr;
                return *this;
            }

            /**
*  @brief  Check if PolAny has value
*  @return true if has value, false in otherwise
*/
            [[nodiscard]] bool has_value() const noexcept
            {
                return m_storage != nullptr;
            }

            void reset() noexcept
            {
                m_storage.reset();
            }

            void swap(any &other) noexcept
            {
                std::swap(m_storage, other.m_storage);
            }

            template< typename T, typename ... Args, typename = typename std::enable_if<std::is_copy_constructible<T>::value>::type >
            void emplace(Args &&...args) noexcept
            {
                m_storage = std::make_unique<_data<T>>(std::forward<Args>(args)...);
            }

            [[nodiscard]]const std::type_info &type() const noexcept
            {
                return typeid(m_storage.get());
            }
        };

        template< typename T >
        [[nodiscard]] inline any make_any(T &&data) noexcept
        {
            return any(std::forward<T>(data));
        }
    }  // namespace PolAny

    template< typename T, typename Any >
    requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
             babel::CONCEPTS::IS_SAME<Any, PolAny::any>
    [[nodiscard]] inline T &cast_any(Any &any)
    {
        if constexpr ( babel::CONCEPTS::IS_SAME<Any, VoidAny::any> )
            return *static_cast<T *>(any.m_data);
        if constexpr ( babel::CONCEPTS::IS_SAME<Any, PolAny::any> )
        {
            if ( auto st = dynamic_cast<PolAny::any::_data<T> *>(any.m_storage.get()) )
                return st->m_data;
            else
                throw std::bad_cast();
        }
    }

    template< typename T, typename Any >
    requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
             babel::CONCEPTS::IS_SAME<Any, PolAny::any>
    [[nodiscard]] inline const T &cast_any(const Any &any)
    {
        if constexpr ( babel::CONCEPTS::IS_SAME<Any, VoidAny::any> )
            return *static_cast<T *>(any.m_data);
        if constexpr ( babel::CONCEPTS::IS_SAME<Any, PolAny::any> )
        {
            if ( auto st = dynamic_cast<PolAny::any::_data<T> *>(any.m_storage.get()) )
                return st->m_data;
            else
                throw std::bad_cast();
        }
    }

    /**
*  @brief  Destroy VoidAny or PolAny, Its requires whe you work with VoidAny
 *  @param Any Any class to destroy
*/
    template< typename T = void, typename Any >
    requires babel::CONCEPTS::IS_SAME<Any, PolAny::any>
             ||
             ( babel::CONCEPTS::IS_SAME<Any, VoidAny::any> &&
               babel::CONCEPTS::IS_NOT_SAME<T, void> )
    inline void destroy_any(Any &any)
    {
        if constexpr ( babel::CONCEPTS::IS_SAME<Any, VoidAny::any> )
            any.template destroy_any<T>();
        if constexpr ( babel::CONCEPTS::IS_SAME<Any, PolAny::any> )
            any.reset();
    }
}  // namespace babel::ANY

#endif  // BABLIB_ANY_HPP_
