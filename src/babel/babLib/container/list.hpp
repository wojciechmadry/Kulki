// Copyright [2021] <Wojtek>"
#ifndef BABLIB_CONTAINER_LIST_HPP_
#define BABLIB_CONTAINER_LIST_HPP_

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

        node *m_head = nullptr, *m_tail = nullptr;
        size_t m_size = 0;

        bool __remove(node *&to_del) noexcept //NOLINT
        {
            if (to_del == nullptr)
                return false;

            if (to_del == m_head)
                pop_front();
            else if (to_del == m_tail)
                pop_back();
            else
            {
                to_del->prev->next = to_del->next;
                to_del->next->prev = to_del->prev;
                delete to_del;
                to_del = nullptr;
                --m_size;
            }
            return true;
        }

        template<typename U = T, typename = is_s_c<U, T> >
        void __insert_in_order(U &&data, node *ins) noexcept //NOLINT
        {
            if (ins == m_head)
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
                ++m_size;
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
        list(size_t NEW_SIZE, U &&data) noexcept
        {
            while (NEW_SIZE-- > 0)
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
            if (m_head == other.m_head)
                return *this;
            clear();
            node *temp = other.m_head;
            while (temp)
            {
                push_back(temp->data);
                temp = temp->next;
            }
            return *this;
        }

        list &operator=(list &&other) noexcept
        {
            if (m_head == other.m_head)
                return *this;
            clear();
            m_head = other.m_head;
            m_tail = other.m_tail;
            m_size = other.m_size;
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0;
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
            return m_size;
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
            if (m_size > 1)
            {
                m_tail->next = new node{std::forward<U>(data)};
                m_tail->next->prev = m_tail;
                m_tail = m_tail->next;
            } else if (m_size == 1)
            {
                m_tail = new node{std::forward<U>(data)};
                m_tail->prev = m_head;
                m_head->next = m_tail;
            } else
            {
                m_head = new node{std::forward<U>(data)};
            }
            ++m_size;
        }

        // end a)
        // b)

        template<typename U = T, typename = is_s_c<U, T> >
        void push_front(U &&data) noexcept
        {
            if (m_size > 1)
            {
                m_head->prev = new node{std::forward<U>(data)};
                m_head->prev->next = m_head;
                m_head = m_head->prev;
            } else if (m_size == 1)
            {
                m_tail = m_head;
                m_head = new node{std::forward<U>(data)};
                m_tail->prev = m_head;
                m_head->next = m_tail;
            } else
            {
                m_head = new node{std::forward<U>(data)};
            }
            ++m_size;
        }

        // end b)
        // c)
        void pop_back() noexcept
        {
            if (m_size > 2)
            {
                m_tail = m_tail->prev;
                delete m_tail->next;
                m_tail->next = nullptr;
            } else if (m_size == 2)
            {
                m_head->next = nullptr;
                delete m_tail;
                m_tail = nullptr;
            } else if (m_size == 1)
            {
                delete m_head;
                m_head = nullptr;
            } else
                return;
            --m_size;
        }

        // end c)
        // d)
        void pop_front() noexcept
        {
            if (m_size > 2)
            {
                m_head = m_head->next;
                delete m_head->prev;
                m_head->prev = nullptr;
            } else if (m_size == 2)
            {
                delete m_head;
                m_head = m_tail;
                m_head->prev = nullptr;
                m_tail = nullptr;
            } else if (m_size == 1)
            {
                delete m_head;
                m_head = nullptr;
            } else
                return;
            --m_size;
        }

        // end d)
        // e) && f)
        T &operator[](size_t index)
        {
            if (index >= m_size)
                throw std::out_of_range("Index is out of range!");
            node *temp;
            if (index <= (m_size >> 1)) //NOLINT
            {
                temp = m_head;
                while (index-- > 0)
                    temp = temp->next;
            } else
            {
                index = m_size - index;
                temp = m_tail;
                while (index-- > 1)
                    temp = temp->prev;
            }
            return temp->data;
        }

        const T &operator[](size_t index) const
        {
            if (index >= m_size)
                throw std::out_of_range("Index is out of range!");
            node *temp;
            if (index <= (m_size >> 1)) //NOLINT
            {
                temp = m_head;
                while (index-- > 0)
                    temp = temp->next;
            } else
            {
                index = m_size - index;
                temp = m_tail;
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
            node *temp = m_head;
            while (temp && !comparator(temp->data))
                temp = temp->next;
            if (temp)
                return &temp->data;
            return nullptr;
        }

        T *find(const T &data) noexcept
        {
            node *temp = m_head;
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
            node *temp = m_head;
            while (temp && !comparator(temp->data))
                temp = temp->next;
            if (temp)
                return &temp->data;
            return nullptr;
        }

        const T *find(const T &data) const noexcept
        {
            node *temp = m_head;
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
            node *temp = m_head;
            while (temp && !comparator(temp->data))
                temp = temp->next;
            return __remove(temp);
        }

        bool remove(const T &data) noexcept
        {
            node *temp = m_head;
            while (temp && temp->data != data)
                temp = temp->next;
            return __remove(temp);
        }

        // end h)
        // i)

        template<typename Cmp, typename U = T, typename = is_s_c<U, T>>
        void push_in_order(U &&data, const Cmp &comparator) noexcept
        {
            node *temp = m_head;
            while (temp && comparator(data, temp->data))
                temp = temp->next;
            __insert_in_order(std::forward<U>(data), temp);
        }

        // end i)
        // j)
        void clear() noexcept
        {
            if (m_size == 1)
            {
                delete m_head;
                m_head = nullptr;
                m_size = 0;
                return;
            }
            m_size = 0;
            while (m_head)
            {
                delete m_head->prev;
                m_head = m_head->next;
            }
            delete m_tail;
            m_head = nullptr;
            m_tail = nullptr;
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
                    std::string("Size : ") + std::to_string(m_size) + '\n'
                    + "Head : " + p_to_s(m_head) + '\n'
                    + "Tail : " + p_to_s(m_tail) + '\n';
            if (to_string_conv)
            {
                if (m_head)
                    res += "First element : " + std::to_string(m_head->data) + "\n";
                if ((m_size >> 1) > 1) //NOLINT
                    res += "Middle element : " + std::to_string(operator[](m_size >> 1)) + "\n"; //NOLINT
                if (m_tail)
                    res += "Last element : " + std::to_string(m_tail->data) + "\n";
            }
            return res;
        }
        // end k)

        iterator begin()
        {
            return iterator(m_head);
        }

        iterator end()
        {
            return iterator(nullptr);
        }

        iterator rbegin()
        {
            return m_tail ? iterator(m_tail) : iterator(m_head);
        }

        iterator rend()
        {
            return iterator(nullptr);
        }
    };
}  // namespace babel::CONTAINER

#endif  // BABLIB_CONTAINER_LIST_HPP_
