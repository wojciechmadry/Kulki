#ifndef _A_D_ARRAY
#define _A_D_ARRAY

#include <type_traits>
#include <string>
#include <initializer_list>

namespace babel::CONTAINER{
    template< typename T, size_t GROW = 2 >
    class dynamic_array
    {
        template< typename U >
        using decay = typename std::decay_t<U>;
        template< typename LHS, typename RHS, typename LHS_d = decay<LHS>, typename RHS_d = decay<RHS> >
        using is_s_c = typename std::enable_if_t<std::is_same_v<LHS_d, RHS_d> || std::is_convertible_v<LHS_d, RHS_d>>;
        static_assert(GROW >= 2, "GROW must be greater or equal than 2");
        T *_array = nullptr;
        size_t _size = 0, _max_size = 0;

        void __reallocate() //NOLINT
        {
            _max_size *= GROW;
            if (_max_size == 0)
                _max_size = GROW * GROW;

            T *temp = new T[_max_size];
            std::transform(_array, _array + _size, temp, [](T &Data) {
                return std::move(Data);
            });
            delete[] _array;
            _array = temp;
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

        dynamic_array() noexcept{}

        dynamic_array(const std::initializer_list<T> &init)
        {
            _max_size = init.size() + GROW;
            _array = new T[_max_size];
            std::for_each(init.begin(), init.end(), [this](const T &Element) {
                this->template push_back(Element);
            });
        }

        dynamic_array(size_t SIZE, const T &data)
        {
            _max_size = SIZE + GROW;
            _array = new T[_max_size];
            _size = SIZE;
            std::for_each(_array, _array + _size, [&data](T &ArrayElement) {
                ArrayElement = data;
            });
        }

        template< typename U = dynamic_array, typename = typename std::enable_if_t<std::is_same_v<std::decay_t<U>, dynamic_array>> >
        dynamic_array(U &&other) noexcept //NOLINT
        {
            *this = std::forward<U>(other);
        }

        ~dynamic_array() noexcept
        {
            delete[] _array;
            _array = nullptr;
        }

        [[nodiscard]] size_t size() const noexcept
        {
            return _size;
        }

        dynamic_array &operator=(dynamic_array &&other) noexcept
        {
            if ( _array == other._array )
                return *this;
            delete[] _array;
            _array = other._array;
            _size = other._size;
            _max_size = other._max_size;
            other._array = nullptr;
            other._size = 0;
            other._max_size = 0;
            return *this;
        }

        dynamic_array &operator=(const dynamic_array &other) noexcept
        {
            if ( _array == other._array )
                return *this;
            if ( other._size < _max_size )
            {
                _size = other._size;
                std::transform(other._array, other._array + _size, _array, [](const T &data) {
                    return data;
                });
            } else
            {
                std::transform(other._array, other._array + _size, _array, [](const T& data)
                {
                    return data;
                });
                std::size_t Size = other.size() - _size;
                std::for_each(other._array + _size, other._array + Size, [this](const T& data)
                {
                   this->template push_back(data);
                });
            }
            return *this;
        }

        // a)
        template< typename U = T, typename = is_s_c<U, T>>
        void push_back(U &&data) noexcept
        {
            if ( _size >= _max_size )
                __reallocate();
            _array[_size++] = std::forward<U>(data);
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
            if ( index >= _size )
                throw std::out_of_range("Array out of range!");
            return _array[index];
        }

        const T &operator[](const size_t index) const
        {
            if ( index >= _size )
                throw std::out_of_range("Array out of range!");
            return _array[index];
        }

        // end b) && c)
        // d)
        void clear() noexcept
        {
            delete[] _array;
            _size = 0;
            _max_size = GROW;
            _array = new T[_max_size];
        }

        // end d)
        // e)
        [[nodiscard]] std::string to_string() const noexcept
        {
            return "Size : " + std::to_string(_size)
                   + "\nMax Size : " + std::to_string(_max_size)
                   + "\nMemory usage : " + std::to_string(sizeof(dynamic_array<T>) + _max_size * sizeof(T)) + "\n";
        }

        // end e)


        template< typename ... Args >
        void emplace_back(Args &&... args) noexcept
        {
            if ( _size >= _max_size )
                __reallocate();
            _array[_size++] = T(std::forward<Args>(args)...);
        }

        template< typename ... Args >
        void emplace(size_t index, Args &&... args) noexcept
        {
            _array[index] = T(std::forward<Args>(args)...);
        }

        void pop_back() noexcept
        {
            if ( _size > 0 )
            {
                --_size;
                _array[_size].~T();
            }
        }

        iterator begin()
        {
            return iterator(_array);
        }

        iterator end()
        {
            return iterator(_array + _size);
        }

        iterator rbegin()
        {
            return iterator(_array + _size - 1);
        }

        iterator rend()
        {
            return iterator(_array - 1);
        }
    };
}

#endif