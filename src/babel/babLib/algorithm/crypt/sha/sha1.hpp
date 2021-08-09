// Copyright [2021] <Wojtek>"
#ifndef BABLIB_ALGORITHM_CRYPT_SHA_SHA1_HPP_
#define BABLIB_ALGORITHM_CRYPT_SHA_SHA1_HPP_

#include <string>
#include <bit>
#include <array>
#include <vector>
#include "../../cast.hpp"
#include "../../../concepts/concepts.hpp"
#include "sha_array.hpp"

namespace babel::ALGO::CRYPT{
    std::string sha1(const std::string &HASH) noexcept
    {
        using WORD = babel::CONCEPTS::type_of_number<4, false>::type;

        constexpr const WORD CHUNK_LENGTH = 512;
        constexpr const WORD ROUNDS = 80;

        static_assert(sizeof(WORD) == 4);

        std::array<WORD, 5> H = {
                0x67452301, 0xEFCDAB89,
                0x98BADCFE, 0x10325476,
                0xC3D2E1F0
        };


        auto len = HASH.size() << 3;

        _BABEL_PRIVATE_DO_NOT_USE::_PRIVATE_BABEL::INT_HOLDER<WORD> holder;

        for ( auto c : HASH )
            holder.push<int8_t>(c);

        holder.push<bool>(true);

        while ( holder.number_of_bits() % CHUNK_LENGTH != 448 )
            holder.push<bool>(false);
        holder.push<uint64_t>(len);

        std::vector<WORD> MSG = holder.get_vec();

        std::array<WORD, ROUNDS> w {0};
        std::size_t i;
        for ( auto iterator = std::begin(MSG) ; iterator < std::end(MSG) ; iterator += 16 )
        {
            std::copy(iterator, iterator + 16, w.begin());

            for ( i = 16 ; i < ROUNDS ; ++i )
            {
                w[i] = std::rotl(
                        w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
            }

            auto a = H[0];
            auto b = H[1];
            auto c = H[2];
            auto d = H[3];
            auto e = H[4];

            decltype(e) f, k;

            for ( i = 0 ; i < ROUNDS ; ++i )
            {
                if ( i <= 19 )
                {
                    f = ( b & c ) | ( ( ~b ) & d );
                    k = 0x5A827999;
                } else if ( i <= 39 )
                {
                    f = b ^ c ^ d;
                    k = 0x6ED9EBA1;
                } else if ( i <= 59 )
                {
                    f = ( b & c ) | ( b & d ) | ( c & d );
                    k = 0x8F1BBCDC;
                } else
                {
                    f = b ^ c ^ d;
                    k = 0xCA62C1D6;
                }
                auto temp = std::rotl(a, 5) + f + e + k + w[i];
                e = d;
                d = c;
                c = std::rotl(b, 30);
                b = a;
                a = temp;
            }

            H[0] += a;
            H[1] += b;
            H[2] += c;
            H[3] += d;
            H[4] += e;
        }

        std::string res;
        res.reserve(40);
        for ( i = 0 ; i < H.size() ; ++i )
        {
            res += babel::ALGO::CAST::to_hex(H[i]);
        }

        return res;
    }
}  // namespace babel::ALGO::CRYPT

#endif  // BABLIB_ALGORITHM_CRYPT_SHA_SHA1_HPP_
