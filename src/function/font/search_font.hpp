#ifndef KULKI_SEARCH_FONT_HPP
#define KULKI_SEARCH_FONT_HPP

#include "BabelLib/babel.hpp"

// Finding fonts in disc
[[nodiscard]] babel::OPT::optional<std::string> search_font() noexcept;

#endif
