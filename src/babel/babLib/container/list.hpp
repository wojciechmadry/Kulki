#ifndef _A_LIST
#define _A_LIST

#include <string>
#include <type_traits>
#include <initializer_list>
#include <functional>
#include <sstream>

namespace babel::CONTAINER {
    template<typename T>
    class list
    {
        template<typename U>
        using decay = typename std::decay_t<U>;
        template<typename LHS, typename RHS, typename LHS_d = decay<LHS>, typename RHS_d = decay<RHS>>
        using is_s_c = typename std::enable_if_t<std::is_same_v<LHS_d, RHS_d> || std::is_convertible_v<LHS_d, RHS_d>>;

        struct node
        {
            node *next, *prev;
            T data;

            template<typename U = T, typename = typename std::enable_if_t<!std::is_same_v<std::decay_t<U>, node>>>
            explicit node(U &&_data) noexcept: next(nullptr), prev(nullptr), data(std::forward<U>(_data))
            {} //NOLINT
        };

        node *head = nullptr, *tail = nullptr;
        size_t _size = 0;

        bool __remove(node *&to_del) noexcept //NOLINT
        {
            if (to_del == nullptr)
                return false;

            if (to_del == head)
                pop_front();
            else if (to_del == tail)
                pop_back();
            else
            {
                to_del->prev->next = to_del->next;
                to_del->next->prev = to_del->prev;
                delete to_del;
                to_del = nullptr;
                --_size;
            }
            return true;
        }

        template<typename U = T, typename = is_s_c<U, T> >
        void __insert_in_order(U &&data, node *ins) noexcept //NOLINT
        {
            if (ins == head)
                push_front(std::forward<U>(data));
            else if (ins == nullptr)
                push_back(std::forward<U>(data));
            else
            {
                node *temp = ins->prev;
                ins->prev = new node{std::forward<U>(data)};
                ins->prev->next = ins;
                ins->prev->prev = temp;
                temp->next = ins->prev;
                ++_size;
            }
        }

    public:
        class iterator
        {
            node *pos;
        public:
            explicit iterator(node *p_node) noexcept: pos(p_node)
            {}

            iterator &operator++() noexcept
            {
                pos = pos->next;
                return *this;
            }

            iterator &operator--() noexcept
            {
                pos = pos->prev;
                return *this;
            }

            iterator operator--(int) noexcept //NOLINT
            {
                iterator res(pos);
                pos = pos->prev;
                return res;
            }

            iterator operator++(int) noexcept //NOLINT
            {
                iterator res(pos);
                pos = pos->next;
                return res;
            }

            T &operator*() noexcept
            {
                return pos->data;
            }

            const T &operator*() const noexcept
            {
                return pos->data;
            }

            bool operator!=(const iterator &other) const noexcept
            {
                return pos != other.pos;
            }

            bool operator==(const iterator &other) const noexcept
            {
                return pos == other.pos;
            }
        };

        list() = default;

        template<typename U = T, typename = is_s_c<U, T> >
        list(size_t _SIZE, U &&data) noexcept
        {
            while (_SIZE-- > 0)
                push_back(data);
        }

        template<typename U = T, typename = is_s_c<U, T> >
        list(std::initializer_list<U> &&init_list) noexcept
        {
            std::for_each(init_list.begin(), init_list.end(), [this](const U& Data)
            {
                this->template push_back(Data);
            });
        }

        list(list &&other) noexcept
        {
            *this = std::move(other);
        }

        list(const list &other) noexcept
        {
            *this = other;
        }

        ~list() noexcept
        {
            clear();
        }

        list &operator=(const list &other) noexcept //NOLINT
        {
            if (head == other.head)
                return *this;
            clear();
            node *temp = other.head;
            while (temp)
            {
                push_back(temp->data);
                temp = temp->next;
            }
            return *this;
        }

        list &operator=(list &&other) noexcept
        {
            if (head == other.head)
                return *this;
            clear();
            head = other.head;
            tail = other.tail;
            _size = other._size;
            other.head = nullptr;
            other.tail = nullptr;
            other._size = 0;
            return *this;
        }

        template<typename U = T, typename = is_s_c<U, T> >
        list &operator=(std::initializer_list<U> &&init_list) noexcept
        {
            clear();
            std::for_each(init_list.begin(), init_list.end(), [this](const U& Data)
            {
                this->template push_back(Data);
            });
            return *this;
        }

        [[nodiscard]] size_t size() const noexcept
        {
            return _size;
        }

        //  a)
        template<typename U = T, typename = is_s_c<U, T> >
        void push_back(std::initializer_list<U> &&init) noexcept
        {
            std::for_each(init.begin(), init.end(), [this](const U& Data)
            {
                this->template push_back(Data);
            });
        }

        template<typename U = T, typename = is_s_c<U, T> >
        void push_back(U &&data) noexcept
        {
            if (_size > 1)
            {
                tail->next = new node{std::forward<U>(data)};
                tail->next->prev = tail;
                tail = tail->next;
            } else if (_size == 1)
            {
                tail = new node{std::forward<U>(data)};
                tail->prev = head;
                head->next = tail;
            } else
            {
                head = new node{std::forward<U>(data)};
            }
            ++_size;
        }

        // end a)
        // b)

        template<typename U = T, typename = is_s_c<U, T> >
        void push_front(U &&data) noexcept
        {
            if (_size > 1)
            {
                head->prev = new node{std::forward<U>(data)};
                head->prev->next = head;
                head = head->prev;
            } else if (_size == 1)
            {
                tail = head;
                head = new node{std::forward<U>(data)};
                tail->prev = head;
                head->next = tail;
            } else
            {
                head = new node{std::forward<U>(data)};
            }
            ++_size;
        }

        // end b)
        // c)
        void pop_back() noexcept
        {
            if (_size > 2)
            {
                tail = tail->prev;
                delete tail->next;
                tail->next = nullptr;
            } else if (_size == 2)
            {
                head->next = nullptr;
                delete tail;
                tail = nullptr;
            } else if (_size == 1)
            {
                delete head;
                head = nullptr;
            } else
                return;
            --_size;
        }

        // end c)
        // d)
        void pop_front() noexcept
        {
            if (_size > 2)
            {
                head = head->next;
                delete head->prev;
                head->prev = nullptr;
            } else if (_size == 2)
            {
                delete head;
                head = tail;
                head->prev = nullptr;
                tail = nullptr;
            } else if (_size == 1)
            {
                delete head;
                head = nullptr;
            } else
                return;
            --_size;
        }

        // end d)
        // e) && f)
        T &operator[](size_t index)
        {
            if (index >= _size)
                throw std::out_of_range("Index is out of range!");
            node *temp;
            if (index <= (_size >> 1)) //NOLINT
            {
                temp = head;
                while (index-- > 0)
                    temp = temp->next;
            } else
            {
                index = _size - index;
                temp = tail;
                while (index-- > 1)
                    temp = temp->prev;
            }
            return temp->data;
        }

        const T &operator[](size_t index) const
        {
            if (index >= _size)
                throw std::out_of_range("Index is out of range!");
            node *temp;
            if (index <= (_size >> 1)) //NOLINT
            {
                temp = head;
                while (index-- > 0)
                    temp = temp->next;
            } else
            {
                index = _size - index;
                temp = tail;
                while (index-- > 1)
                    temp = temp->prev;
            }
            return temp->data;
        }

        // end e) && f)
        // g)
        template<typename Cmp, typename = typename std::enable_if<
                !std::is_same<T, Cmp>::value && !std::is_convertible<T, Cmp>::value>::type>
        T *find(const Cmp &comparator) noexcept
        {
            node *temp = head;
            while (temp && !comparator(temp->data))
                temp = temp->next;
            if (temp)
                return &temp->data;
            return nullptr;
        }

        T *find(const T &data) noexcept
        {
            node *temp = head;
            while (temp && temp->data != data)
                temp = temp->next;
            if (temp)
                return &temp->data;
            return nullptr;
        }

        template<typename Cmp, typename = typename std::enable_if<
                !std::is_same<T, Cmp>::value && !std::is_convertible<T, Cmp>::value>::type>
        const T *find(const Cmp &comparator) const noexcept
        {
            node *temp = head;
            while (temp && !comparator(temp->data))
                temp = temp->next;
            if (temp)
                return &temp->data;
            return nullptr;
        }

        const T *find(const T &data) const noexcept
        {
            node *temp = head;
            while (temp && temp->data != data)
                temp = temp->next;
            if (temp)
                return &temp->data;
            return nullptr;
        }

        // end g)
        // h)
        template<typename Cmp, typename = typename std::enable_if<
                !std::is_same<T, Cmp>::value && !std::is_convertible<T, Cmp>::value>::type>
        bool remove(const Cmp &comparator) noexcept
        {
            node *temp = head;
            while (temp && !comparator(temp->data))
                temp = temp->next;
            return __remove(temp);
        }

        bool remove(const T &data) noexcept
        {
            node *temp = head;
            while (temp && temp->data != data)
                temp = temp->next;
            return __remove(temp);
        }

        // end h)
        // i)

        template<typename Cmp, typename U = T, typename = is_s_c<U, T>>
        void push_in_order(U &&data, const Cmp &comparator) noexcept
        {
            node *temp = head;
            while (temp && comparator(data, temp->data))
                temp = temp->next;
            __insert_in_order(std::forward<U>(data), temp);
        }

        // end i)
        // j)
        void clear() noexcept
        {
            if (_size == 1)
            {
                delete head;
                head = nullptr;
                _size = 0;
                return;
            }
            _size = 0;
            while (head)
            {
                delete head->prev;
                head = head->next;
            }
            delete tail;
            head = nullptr;
            tail = nullptr;
        }

        // end j)
        // k)
        [[nodiscard]] std::string to_string(bool to_string_conv = false) const
        {
            auto p_to_s = [](void const *pointer) -> std::string {
                std::ostringstream ps;
                ps << pointer;
                return ps.str();
            };
            std::string res =
                    "Size : " + std::to_string(_size) + '\n'
                    + "Head : " + p_to_s(head) + '\n'
                    + "Tail : " + p_to_s(tail) + '\n';
            if (to_string_conv)
            {
                if (head)
                    res += "First element : " + std::to_string(head->data) + "\n";
                if ((_size >> 1) > 1) //NOLINT
                    res += "Middle element : " + std::to_string(operator[](_size >> 1)) + "\n"; //NOLINT
                if (tail)
                    res += "Last element : " + std::to_string(tail->data) + "\n";
            }
            return res;
        }
        // end k)

        iterator begin()
        {
            return iterator(head);
        }

        iterator end()
        {
            return iterator(nullptr);
        }

        iterator rbegin()
        {
            return tail ? iterator(tail) : iterator(head);
        }

        iterator rend()
        {
            return iterator(nullptr);
        }
    };
}

#endif