// Copyright [2021] <Wojtek>"
#ifndef BABLIB_CONTAINER_DYNAMIC_ARRAY_HPP_
#define BABLIB_CONTAINER_DYNAMIC_ARRAY_HPP_

#include <type_traits>
#include <string>
#include <initializer_list>
#include <stdexcept>

namespace babel::CONTAINER{
    template< typename T, size_t GROW = 2 >
    class dynamic_array
    {
        template< typename U >
        using decay = typename std::decay_t<U>;
        template< typename LHS, typename RHS, typename LHS_d = decay<LHS>, typename RHS_d = decay<RHS> >
        using is_s_c = typename std::enable_if_t<std::is_same_v<LHS_d, RHS_d> || std::is_convertible_v<LHS_d, RHS_d>>;
        static_assert(GROW >= 2, "GROW must be greater or equal than 2");
        T *m_array = nullptr;
        size_t m_size = 0, m_max_size = 0;

        void __reallocate() //NOLINT
        {
            m_max_size *= GROW;
            if ( m_max_size == 0 )
                m_max_size = GROW * GROW;

            T *temp = new T[m_max_size];
            std::transform(m_array, m_array + m_size, temp, std::move<T &>);
            delete[] m_array;
            m_array = temp;
        }

    public:
        class iterator
        {
            T *_pos;

            explicit iterator(T *position) : _pos(position)
            { }

            friend class dynamic_array;

        public:
            T &operator*()
            {
                return *_pos;
            }

            const T &operator*() const
            {
                return *_pos;
            }

            iterator operator++(int) //NOLINT
            {
                return iterator(_pos++);
            }

            iterator operator--(int) //NOLINT
            {
                return iterator(_pos--);
            }

            iterator &operator++()
            {
                ++_pos;
                return *this;
            }

            iterator &operator--()
            {
                --_pos;
                return *this;
            }

            bool operator!=(const iterator &other) const
            {
                return _pos != other._pos;
            }

            bool operator==(const iterator &other) const
            {
                return _pos == other._pos;
            }
        };

        dynamic_array() = default;

        dynamic_array(const std::initializer_list<T> &init)
        {
            m_max_size = init.size() + GROW;
            m_array = new T[m_max_size];
            std::for_each(init.begin(), init.end(), [this](const T &Element) {
                this->template push_back(Element);
            });
        }

        dynamic_array(size_t NEW_SIZE, const T &data)
        {
            m_max_size = NEW_SIZE + GROW;
            m_array = new T[m_max_size];
            m_size = NEW_SIZE;
            std::for_each(m_array, m_array + m_size, [&data](T &ArrayElement) {
                ArrayElement = data;
            });
        }

        dynamic_array(dynamic_array &&other) noexcept
        {
            *this = std::move(other);
        }

        dynamic_array(const dynamic_array &other) noexcept
        {
            *this = other;
        }

        ~dynamic_array() noexcept
        {
            delete[] m_array;
            m_array = nullptr;
        }

        [[nodiscard]] size_t size() const noexcept
        {
            return m_size;
        }

        dynamic_array &operator=(dynamic_array &&other) noexcept
        {
            if ( this == &other )
                return *this;
            delete[] m_array;
            m_array = other.m_array;
            m_size = other.m_size;
            m_max_size = other.m_max_size;
            other.m_array = nullptr;
            other.m_size = 0;
            other.m_max_size = 0;
            return *this;
        }

        dynamic_array &operator=(const dynamic_array &other) noexcept
        {
            if ( this == &other )
                return *this;
            if ( other.m_size < m_max_size )
            {
                m_size = other.m_size;
                std::transform(other.m_array, other.m_array + m_size, m_array, [](const T &data) {
                    return data;
                });
            } else
            {
                std::transform(other.m_array, other.m_array + m_size, m_array, [](const T &data) {
                    return data;
                });
                std::size_t Size = other.size() - m_size;
                std::for_each(other.m_array + m_size, other.m_array + Size, [this](const T &data) {
                    this->template push_back(data);
                });
            }
            return *this;
        }

        // a)
        template< typename U = T, typename = is_s_c<U, T>>
        void push_back(U &&data) noexcept
        {
            if ( m_size >= m_max_size )
                __reallocate();
            m_array[m_size++] = std::forward<U>(data);
        }

        void push_back(std::initializer_list<T> &&init) noexcept
        {
            std::for_each(init.begin(), init.end(), [this](const T &data) {
                this->template push_back(data);
            });
        }

        // end a)
        // b) && c)
        T &operator[](const size_t index)
        {
            if ( index >= m_size )
                throw std::out_of_range("Array out of range!");
            return m_array[index];
        }

        const T &operator[](const size_t index) const
        {
            if ( index >= m_size )
                throw std::out_of_range("Array out of range!");
            return m_array[index];
        }

        // end b) && c)
        // d)
        void clear() noexcept
        {
            delete[] m_array;
            m_size = 0;
            m_max_size = GROW;
            m_array = new T[m_max_size];
        }

        // end d)
        // e)
        [[nodiscard]] std::string to_string() const noexcept
        {
            return "Size : " + std::to_string(m_size)
                   + "\nMax Size : " + std::to_string(m_max_size)
                   + "\nMemory usage : " + std::to_string(sizeof(dynamic_array<T>) + m_max_size * sizeof(T)) + "\n";
        }

        // end e)


        template< typename ... Args >
        void emplace_back(Args &&... args) noexcept
        {
            if ( m_size >= m_max_size )
                __reallocate();
            m_array[m_size++] = T(std::forward<Args>(args)...);
        }

        template< typename ... Args >
        void emplace(size_t index, Args &&... args) noexcept
        {
            m_array[index] = T(std::forward<Args>(args)...);
        }

        void pop_back() noexcept
        {
            if ( m_size > 0 )
            {
                --m_size;
                m_array[m_size].~T();
            }
        }

        iterator begin()
        {
            return iterator(m_array);
        }

        iterator end()
        {
            return iterator(m_array + m_size);
        }

        iterator rbegin()
        {
            return iterator(m_array + m_size - 1);
        }

        iterator rend()
        {
            return iterator(m_array - 1);
        }
    };
}  // namespace babel::CONTAINER"

#endif  // BABLIB_CONTAINER_DYNAMIC_ARRAY_HPP_
