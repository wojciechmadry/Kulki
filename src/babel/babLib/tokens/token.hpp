// Copyright [2021] <Wojtek>"
#ifndef BABLIB_TOKENS_TOKEN_HPP_
#define BABLIB_TOKENS_TOKEN_HPP_

namespace babel::TOKEN
{
    class token
    {
        bool m_taken;
    public:
        token() : m_taken(false)
        {

        }

        ~token()
        {
            release();
        }

        [[nodiscard]] bool is_taken() const noexcept
        {
            return m_taken;
        }

        void take() noexcept
        {
            if(!m_taken)
                m_taken = true;
        }
        void release() noexcept
        {
            m_taken = false;
        }
    };
}  // namespace babel::TOKEN

#endif // BABLIB_TOKENS_TOKEN_HPP_