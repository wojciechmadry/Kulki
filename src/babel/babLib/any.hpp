#ifndef BABEL_ANY
#define BABEL_ANY

#include "must_have.hpp"
namespace babel::ANY {
    namespace VoidAny{ class any;};
    namespace PolAny{ class any;};
    template<typename T, typename Any>
    requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
              babel::CONCEPTS::IS_SAME<Any, PolAny::any>
    T& cast_any(Any& any);
    template<typename T, typename Any>
    requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
             babel::CONCEPTS::IS_SAME<Any, PolAny::any>
    const T& cast_any(const Any& any);

    template<size_t ID,typename T , typename U = typename std::decay_t<T>>
    auto make_any(T&& object) noexcept;
    /*
     Void any is faster then PolAny by approx 30-40%
     USE RULES:
     1. One ANY object can't be another ANY(lvalue, like smart pointers)
     2. When you create ANY object (data is not NULLPTR) then you must use destroy_any to avoid memory leak !
         */
    namespace VoidAny {

        class any
        {
            template<typename T, typename Any>
            requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
                     babel::CONCEPTS::IS_SAME<Any, PolAny::any>
            friend T& babel::ANY::cast_any(Any& any); //NOLINT
            template<typename T, typename Any>
            requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
                     babel::CONCEPTS::IS_SAME<Any, PolAny::any>
            friend const T& babel::ANY::cast_any(const Any& any);//NOLINT

            template<size_t ID,typename T , typename U>
            friend auto babel::ANY::make_any(T &&object) noexcept; //NOLINT
            void* data;

            template<typename T>
            friend any make_any(T&& object) noexcept;

            template<typename T>
            friend void destroy_any(any &_any) noexcept;


        public:
            any() noexcept: data(nullptr)
            {}

            template<typename T, typename U = typename std::decay_t<T>>
            requires babel::CONCEPTS::IS_NOT_SAME<T, any>
            explicit any(T &&obj) noexcept : data(new U(std::forward<T>(obj))) //NOLINT
            {}

            any(const any &other) = delete;

            any(any &&other) noexcept: data{other.data}
            {
                other.data = nullptr;
            }

            ~any() = default;

#ifndef NDEBUG

            [[nodiscard]] const void *view_pointer() const noexcept
            {
                return data;
            }

#endif

            [[nodiscard]] bool has_value() const noexcept
            {
                return data != nullptr;
            }

            void swap(any &other) noexcept
            {
                void *temp = data;
                data = other.data;
                other.data = temp;
            }

            template<typename T, typename U = typename std::decay_t<T>>
            requires babel::CONCEPTS::IS_NOT_SAME<T, any>
            any& operator=(T&& object)
            {
                if(data)
                    throw std::invalid_argument("Memory leak. Destroy void any first.");
                data = new U{std::forward<T>(object)};
                return *this;
            }
            any &operator=(const any &) = delete;

            any &operator=(any &&_any) //NOLINT
            {
                if (_any.data == data)
                    return *this;
                if(data)
                    throw std::invalid_argument("Memory leak. Destroy void any first.");
                data = _any.data;
                _any.data = nullptr;
                return *this;
            }
        };


        template<typename T>
        void destroy_any(any &_any) noexcept
        {
            delete static_cast<T *>(_any.data);
            _any.data = nullptr;
        }

        template<typename T>
        any make_any(T&& object) noexcept
        {
            return any(std::forward<T>(object));
        }

    }

    /*
        Object must by copyable and constructible other way use VoidAny
       You dont need to remember to destroy a object,
       but its a little slower (about 30-40%).
       Its safer to avoid memory leak.
       */
    namespace PolAny {
        class any;

        template<typename T, typename U = typename std::decay<T>::type, typename ... Args>
        any make_any(Args &&... args) noexcept;

        class any
        {
            template<typename T, typename Any>
            requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
                     babel::CONCEPTS::IS_SAME<Any, PolAny::any>
            friend const T& babel::ANY::cast_any(const Any& any);//NOLINT
            template<typename T, typename Any>
            requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
                      babel::CONCEPTS::IS_SAME<Any, PolAny::any>
            friend T& babel::ANY::cast_any(Any& any); //NOLINT

            template<size_t ID,typename T, typename U>
            friend auto babel::ANY::make_any(T&& object) noexcept; //NOLINT

            struct __base__any //NOLINT
            {
                virtual ~__base__any() = default;

                [[nodiscard]]  virtual __base__any *duplicate() const noexcept = 0;
            };

            template<typename T>
            struct _data : public __base__any
            {
                T data;

                template<typename U = T>
                requires babel::CONCEPTS::IS_NOT_SAME<U, _data> && babel::CONCEPTS::IS_NOT_SAME<U, __base__any>
                explicit _data(U &&__data) noexcept: data(std::forward<U>(__data)) //NOLINT
                {}

                [[nodiscard]] __base__any *duplicate() const noexcept override
                {
                    return new _data<T>(data);
                }

            };

            __base__any *storage = nullptr;
        public:
            any() = default;

            template<typename T, typename U = typename std::decay_t<T>>
            requires babel::CONCEPTS::IS_NOT_SAME<T, any>
            explicit any(T&& object) noexcept : storage(new _data<U>{std::forward<T>(object)}) //NOLINT
            {}
            any(const any &other) noexcept
            {
                storage = other.storage->duplicate();
            }

            any(any &&other) noexcept: storage(other.storage)
            {
                other.storage = nullptr;
            }

            ~any() noexcept
            {
                delete storage;
                storage = nullptr;
            }


            template<typename T>
            T &cast()
            {
                if (auto st = dynamic_cast<_data<T> *>(storage))
                    return st->data;
                else
                    throw std::bad_cast();
            }

            template<typename T>
            const T &cast() const
            {
                if (auto st = dynamic_cast<_data<T> *>(storage))
                    return st->data;
                else
                    throw std::bad_cast();
            }

            // Check if storage object is T
            template<typename T>
            [[nodiscard]] bool is() const noexcept
            {
                return (dynamic_cast<_data<T> *>(storage)) ? 1 : 0;
            }

            //Compare type of storage object and if they are the same, then compare object (full safe)
            template<typename T>
            [[nodiscard]] bool cmp(const any &other) noexcept
            {
                try
                {
                    if (*this == other)
                        return cast_any<T>(*this) == cast_any<T>(other);
                    return false;
                }
                catch (const std::bad_cast &)
                {
                    return false;
                }
            }

            //Compare type of storage object
            bool operator==(const any &other)
            {
                if ((storage && other.storage) == 0)
                    return storage == other.storage;
                return typeid(*storage) == typeid(*other.storage);
            }

            template<typename T, typename U = typename std::decay_t<T>>
            requires babel::CONCEPTS::IS_NOT_SAME<T, any>
            any& operator=(T&& object) noexcept
            {
                reset();
                storage = new _data<U>{std::forward<T>(object)};
                return *this;
            }
            any &operator=(const any &other) noexcept
            {
                if(this == &other)
                    return *this;
                reset();
                storage = other.storage->duplicate();
                return *this;
            }

            any &operator=(any &&other) noexcept
            {
                if (storage == other.storage)
                    return *this;
                reset();
                storage = other.storage;
                other.storage = nullptr;
                return *this;
            }

#ifndef NDEBUG

            const __base__any *view_pointer() const noexcept //NOLINT
            {
                return storage;
            }

#endif

            [[nodiscard]] bool has_value() const noexcept
            {
                return storage != nullptr;
            }

            void reset() noexcept
            {
                if (storage)
                {
                    delete storage;
                    storage = nullptr;
                }
            }

            void swap(any &other) noexcept
            {
                __base__any *temp = storage;
                storage = other.storage;
                other.storage = temp;
            }

            template<typename T, typename ... Args, typename = typename std::enable_if<std::is_copy_constructible<T>::value>::type>
            void emplace(Args &&...args) noexcept
            {
                if (storage) //NOLINT
                    delete storage;
                storage = new _data{T(std::forward<Args>(args)...)};
            }

            [[nodiscard]]const std::type_info &type() const noexcept
            {
                return typeid(*storage);
            }
        };


    }

    template<typename T, typename Any>
    requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
            babel::CONCEPTS::IS_SAME<Any, PolAny::any>
    T& cast_any(Any& any)
    {
        if constexpr (babel::CONCEPTS::IS_SAME<Any, VoidAny::any>)
            return *static_cast<T *>(any.data);
        if constexpr (babel::CONCEPTS::IS_SAME<Any, PolAny::any>)
        {
            if (auto st = dynamic_cast<PolAny::any::_data<T> *>(any.storage))
                return st->data;
            else
                throw std::bad_cast();
        }
    }
    template<typename T, typename Any>
    requires babel::CONCEPTS::IS_SAME<Any, VoidAny::any> ||
             babel::CONCEPTS::IS_SAME<Any, PolAny::any>
    const T& cast_any(const Any& any)
    {
        if constexpr (babel::CONCEPTS::IS_SAME<Any, VoidAny::any>)
            return *static_cast<T *>(any.data);
        if constexpr (babel::CONCEPTS::IS_SAME<Any, PolAny::any>)
        {
            if (auto st = dynamic_cast<PolAny::any::_data<T> *>(any.storage))
                return st->data;
            else
                throw std::bad_cast();
        }
    }

    template<typename T = void , typename Any>
    requires babel::CONCEPTS::IS_SAME<Any, PolAny::any>
             ||
             (babel::CONCEPTS::IS_SAME<Any, VoidAny::any> &&
                     babel::CONCEPTS::IS_NOT_SAME<T, void>)
    void destroy_any(Any& any)
    {
        if constexpr (babel::CONCEPTS::IS_SAME<Any, VoidAny::any>)
            VoidAny::destroy_any<T>(any);
        if constexpr (babel::CONCEPTS::IS_SAME<Any, PolAny::any>)
            any.reset();
    }

    template<size_t ID,typename T, typename U >
    auto make_any(T&& object) noexcept
    {
        static_assert(ID < 2, "ID : 0 - VoidAny, 1 - PolAny");
        if constexpr( ID == 0)
            return VoidAny::any(std::forward<T>(object));
        if constexpr(ID == 1)
            return PolAny::any { .storage = new PolAny::any::_data<U> { std::forward<T>(object) } };

    }
}

#endif