// Copyright [2021] <Wojtek>"
#ifndef BABEL_HPP_
#define BABEL_HPP_

#include "babLib/algorithm/algorithm.hpp"
#include "babLib/any.hpp"
#include "babLib/char.hpp"
#include "babLib/file_system.hpp"
#include "babLib/optional.hpp"
#include "babLib/time.hpp"
#include "babLib/text.hpp"
#include "babLib/wraper.hpp"
#include "babLib/matrix/matrix.hpp"
#include "babLib/request/request.hpp"
#include "babLib/graphics/graphics.hpp"
#include "babLib/tokens/tokenization.hpp"
#include "babLib/system/system.hpp"
#include "babLib/iterators/iterator.hpp"
#include "babLib/container/container.hpp"

namespace babel{
    constexpr const char *VERSION = "1.3";
    constexpr const bool COMPILER_IS_64B = ( sizeof(void *) == 8 ); //NOLINT
    constexpr const bool COMPILER_IS_32B = ( sizeof(void *) == 4 ); //NOLINT
}  // namespace babel
#endif  // BABEL_HPP_
