// Copyright [2021] <Wojtek>"
#ifndef BABLIB_TOKENS_TOKENIZATION_HPP_
#define BABLIB_TOKENS_TOKENIZATION_HPP_

#include "token.hpp"
#include <condition_variable>
#include <mutex>
#include <vector>

namespace babel::TOKEN{

    class tokenizer
    {
    public:
        using TOKEN_TYPE = babel::TOKEN::token;
        using CONTAINER = std::vector<TOKEN_TYPE>;
    private:
        CONTAINER m_tokens;
        std::mutex m_mutex;
        std::condition_variable m_cv;
    public:

        tokenizer() = delete;

        explicit tokenizer(const std::size_t number_of_tokens) noexcept: m_tokens(number_of_tokens)
        {
        }

        ~tokenizer() = default;

        auto get_token(const std::size_t id_token) noexcept
        {
            std::unique_lock<std::mutex> lockGuard(m_mutex);
            while ( m_tokens[id_token].is_taken() )
            {
                m_cv.wait(lockGuard, [&]() { return !m_tokens[id_token].is_taken(); });
            }
            m_tokens[id_token].take();
            class AccessToken
            {
                friend class babel::TOKEN::tokenizer;
            protected:
                babel::TOKEN::token* m_token = nullptr;
                std::condition_variable* m_cv;
                std::mutex* m_mutex;
                AccessToken(babel::TOKEN::token& Token, std::condition_variable& cv, std::mutex& mutex) noexcept : m_token(&Token), m_cv(&cv), m_mutex(&mutex)
                {

                }
            public:
                AccessToken() = delete;
                AccessToken(AccessToken&) = delete;
                AccessToken(AccessToken&& Token) noexcept
                {
                    *this = std::move(Token);
                }

                AccessToken& operator=(AccessToken&) = delete;

                AccessToken& operator=(AccessToken&& Token) noexcept
                {
                    if(this == &Token)
                        return *this;
                    m_token = Token.m_token;
                    Token.m_token = nullptr;
                    m_cv = Token.m_cv;
                    Token.m_cv = nullptr;
                    m_mutex = Token.m_mutex;
                    Token.m_mutex = nullptr;
                    return *this;
                }

                ~AccessToken()
                {
                    release();
                }

                void release()
                {
                    if (m_token != nullptr)
                    {
                        std::lock_guard<std::mutex> lockGuard(*m_mutex);
                        m_token->release();
                        m_cv->notify_all();
                    }
                    m_token = nullptr;
                    m_cv = nullptr;
                    m_mutex = nullptr;
                }
            };
            return AccessToken{m_tokens[id_token], m_cv, m_mutex};
        }
    };
}  // namespace babel::TOKEN

#endif // BABLIB_TOKENS_TOKENIZATION_HPP_