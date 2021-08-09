// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ALGORITHM_CRYPT_SHA_SHA512T_HPP_
#define BABLIB_ALGORITHM_CRYPT_SHA_SHA512T_HPP_

#include "sha_array.hpp"
#include <string>
#include "../../../concepts/concepts.hpp"
#include <bit>
#include "../../cast.hpp"
#include "sha512.hpp"

namespace babel::ALGO::CRYPT{
    template< std::size_t T >
    std::string sha512t(const std::string &HASH) noexcept
    {
        using WORD = babel::CONCEPTS::type_of_number<8, false>::type;

        constexpr const WORD CHUNK_LENGTH = 1024;
        constexpr const WORD ROUNDS = 80;

        static_assert(sizeof(WORD) == 8);
        static_assert(T != 384 && T < 512 && T != 0);

        constexpr const auto &K = _BABEL_PRIVATE_DO_NOT_USE::_PRIVATE_BABEL::PRIME_SHA_ARRAY_64;

        std::array<WORD, 8> H = {
                0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1,
                0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179
        };
        std::for_each(H.begin(), H.end(),
                      [](auto &Date) {
                          Date ^= 0xa5a5a5a5a5a5a5a5;
                      });

        // IV Generate function
        auto NewH = sha512(std::string("SHA-512/") + std::to_string(T), H);
        auto Hiter = std::begin(H);
        for ( std::size_t i = 0 ; i < NewH.size() ; i += 16, ++Hiter )
            *Hiter = std::stoull(NewH.substr(i, 16), nullptr, 16);


        auto len = HASH.size() << 3;
        _BABEL_PRIVATE_DO_NOT_USE::_PRIVATE_BABEL::INT_HOLDER<WORD> holder;
        for ( auto c : HASH )
            holder.push<int8_t>(c);
        holder.push<bool>(true);
        while ( holder.number_of_bits() % CHUNK_LENGTH != 896 )
            holder.push<bool>(false);
        holder.push<uint64_t>(0);
        holder.push<uint64_t>(len);

        std::vector<WORD> MSG = holder.get_vec();

        std::array<WORD, ROUNDS> w {0};
        std::size_t i;

        for ( auto iterator = std::begin(MSG) ; iterator < std::end(MSG) ; iterator += 16 )
        {
            std::copy(iterator, iterator + 16, w.begin());

            for ( i = 16 ; i < ROUNDS ; ++i )
            {
                auto s0 = std::rotr(w[i - 15], 1) ^ std::rotr(w[i - 15], 8) ^ ( w[i - 15] >> 7 );
                auto s1 = std::rotr(w[i - 2], 19) ^ std::rotr(w[i - 2], 61) ^ ( w[i - 2] >> 6 );

                w[i] = w[i - 16] + s0 + w[i - 7] + s1;
            }

            auto a = H[0];
            auto b = H[1];
            auto c = H[2];
            auto d = H[3];
            auto e = H[4];
            auto f = H[5];
            auto g = H[6];
            auto h = H[7];


            for ( i = 0 ; i < ROUNDS ; ++i )
            {
                auto s1 = std::rotr(e, 14) ^ std::rotr(e, 18) ^ std::rotr(e, 41);
                auto ch = ( e & f ) ^ ( ( ~e ) & g );
                auto s0 = std::rotr(a, 28) ^ std::rotr(a, 34) ^ std::rotr(a, 39);
                auto temp1 = h + s1 + ch + K[i] + w[i];
                auto maj = ( a & b ) ^ ( a & c ) ^ ( b & c );
                auto temp2 = s0 + maj;
                h = g;
                g = f;
                f = e;
                e = d + temp1;
                d = c;
                c = b;
                b = a;
                a = temp1 + temp2;
            }

            H[0] += a;
            H[1] += b;
            H[2] += c;
            H[3] += d;
            H[4] += e;
            H[5] += f;
            H[6] += g;
            H[7] += h;
        }

        std::string BITS;
        BITS.reserve(T);
        for ( i = 0 ; i < H.size() ; ++i )
        {
            std::bitset<sizeof(WORD) * 8> bits(H[i]);
            BITS += bits.to_string();
            if ( BITS.size() >= T )
                break;
        }
        if ( BITS.size() > T )
        {
            BITS.erase(T, BITS.size() - T);
        }

        // Convert to HEX
        if ( BITS.size() % 4 == 0 )
        {
            std::string HEX;
            HEX.reserve(BITS.size() >> 2);
            for ( i = 0 ; i < BITS.size() ; i += 4 )
            {
                auto b0 = static_cast<WORD>(BITS[i] - '0') << 3;
                auto b1 = static_cast<WORD>(BITS[i + 1] - '0') << 2;
                auto b2 = static_cast<WORD>(BITS[i + 2] - '0') << 1;
                auto b3 = static_cast<WORD>(BITS[i + 3] - '0');
                auto sum = b0 + b1 + b2 + b3;
                if ( sum < 10 )
                    HEX.push_back(static_cast<char>(sum + '0'));
                else
                    HEX.push_back(static_cast<char>(sum + 87));
            }
            BITS = std::move(HEX);
        }
        return BITS;
    }
}  // namespace babel::ALGO::CRYPT
#endif  // BABLIB_ALGORITHM_CRYPT_SHA_SHA512T_HPP_

