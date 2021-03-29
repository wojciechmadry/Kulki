#ifndef BABEL_ALGO
#define BABEL_ALGO

#include "must_have.hpp"

namespace babel::ALGO {

    template<typename T>
    constexpr T string_to(const std::string &_string)
    {
        if constexpr (babel::CONCEPTS::IS_SAME<T, int>)
            return std::stoi(_string);
        if constexpr (babel::CONCEPTS::IS_SAME<T, long>)
            return std::stol(_string);
        if constexpr (babel::CONCEPTS::IS_SAME<T, long long>)
            return std::stoll(_string);
        if constexpr (babel::CONCEPTS::IS_SAME<T, unsigned long long>)
            return std::stoull(_string);
        if constexpr (babel::CONCEPTS::IS_SAME<T, unsigned long>)
            return std::stoul(_string);
        if constexpr (babel::CONCEPTS::IS_SAME<T, float>)
            return std::stof(_string);
        if constexpr (babel::CONCEPTS::IS_SAME<T, double>)
            return std::stod(_string);
        if constexpr (babel::CONCEPTS::IS_SAME<T, long double>)
            return std::stold(_string);
        if constexpr (babel::CONCEPTS::IS_SAME<T, unsigned int>)
            return static_cast<unsigned int>(std::stoul(_string));
        if constexpr (babel::CONCEPTS::IS_SAME<T, char>)
            return static_cast<char>(std::stoi(_string));
        if constexpr (babel::CONCEPTS::IS_SAME<T, unsigned char>)
            return static_cast<unsigned char>(std::stoul(_string));
        if constexpr (babel::CONCEPTS::IS_SAME<T, short>)
            return static_cast<short>(std::stoi(_string));
        if constexpr (babel::CONCEPTS::IS_SAME<T, unsigned short>)
            return static_cast<unsigned short>(std::stoul(_string));
        if constexpr (babel::CONCEPTS::IS_SAME<T, bool>)
            return static_cast<bool>(std::stoul(_string));
        throw std::out_of_range("No visible conversion.");
    }

/*
 * auto et3 = "7269+732*(8-8-7)*497"; // NOT WORKING
    template<typename T>
    T eval(std::string eq)
    {
        constexpr std::array<char, 4> _op = {'*', '/', '+', '-'};
        auto is_op = [](const char _c) -> bool { return _c == '*' || _c == '/' || _c == '+' || _c == '-'; };
        if (!eq.empty() && is_op(eq[0]) && eq[0] != '-')
            eq.erase(eq.begin());
        constexpr char b_f = '(';
        constexpr char b_s = ')';
        size_t bracket = eq.find_last_of(b_f);
        while (bracket != std::string::npos)
        {
            size_t bracket_second = bracket + 1;
            while (eq[bracket_second] != b_s)
                ++bracket_second;
            if (bracket_second + 1 < eq.size() && eq[bracket_second + 1] > 47 && eq[bracket_second + 1] < 58)
                eq.insert(bracket_second + 1, "*");
            std::string _res = std::to_string(eval<T>(eq.substr(bracket + 1, bracket_second - bracket - 1)));

            eq.erase(eq.begin() + bracket, eq.begin() + bracket_second + 1);
            if (_res[0] == '-' && is_op(eq[bracket - 1]))
            {
                _res.erase(_res.begin());
                if (eq[bracket - 1] == '-')
                    eq[bracket - 1] = '+';
                else if (eq[bracket - 1] == '+')
                    eq[bracket - 1] = '-';
            }
            eq.insert(bracket, _res);
            if (bracket > 0 && eq[bracket - 1] > 47 && eq[bracket - 1] < 58)
                eq.insert(bracket, "*");
            bracket = eq.find_last_of(b_f);
        }
        if (!eq.empty() && is_op(eq[0]) && eq[0] != '-')
            eq.erase(eq.begin());
        if (eq.find(' ') != std::string::npos)
        {
            std::string _nspc = ""; //NOLINT
            auto _it = eq.begin();
            while (_it != eq.end())
            {
                if (*_it != ' ')
                    _nspc += *_it;
                ++_it;
            }
            eq = std::move(_nspc);
        }
        //	std::cout <<eq <<'\n';
        for (auto op : _op)
        {
            size_t found = eq.find_first_of(op);
            if (found == 0)
                found = eq.find_last_of(op);
            if (eq.size() == 2)
                return string_to<T>(eq);
            while (found != std::string::npos)
            {
                if (is_op(eq[0]) && eq[0] != '-')
                    eq.erase(eq.begin());
                else if (eq.size() == 1 || (eq.size() == 2 && eq[0] == '-'))
                    return string_to<T>(eq);
                T n1, n2, res;
                size_t go_left = found - 1;
                if (found == 0)
                    go_left = 0;
                size_t go_right = found + 1;
                while (go_left > 0 && !is_op(eq[go_left]))
                    --go_left;
                if (is_op(eq[go_right]) && is_op(eq[go_right - 1]))
                    ++go_right;
                while (go_right < eq.size() - 1 && !is_op(eq[go_right]))
                {
                    ++go_right;
                }
                if (is_op(eq[go_left]) && eq[go_left] != '-')
                    ++go_left;
                if (is_op(eq[go_right]))
                    --go_right;
                try
                {
                    n1 = string_to<T>(eq.substr(go_left, found - go_left));
                } catch (...)
                {
                    size_t _t = 1;
                    while (is_op(eq[_t++]));
                    try
                    {
                        n1 = string_to<T>(eq.substr(go_left, _t));
                    } catch (...)
                    {
                        n1 = 0;
                    }

                }

                try
                {
                    n2 = string_to<T>(eq.substr(found + 1, go_right - found));
                } catch (...)
                {
                    while (go_right < eq.size() && is_op(eq[go_right]))
                        ++go_right;
                    try
                    {
                        n2 = string_to<T>(eq.substr(found + 1, go_right - found));
                    } catch (...)
                    {
                        n2 = 0;
                    }

                }
                //std::cout << "BEF  :" << eq << '\n';
                eq.erase(eq.begin() + go_left, eq.begin() + go_right + 1);
                //std::cout << "AFT :" << eq << '\n';
                switch (op)
                {
                    case '*' :
                        res = n1 * n2;
                        break;
                    case '/' :
                        res = n1 / n2;
                        break;
                    case '+' :
                        res = n1 + n2;
                        break;
                    case '-' :
                        res = n1 - n2;
                        break;
                    default:
                        throw;
                }
                if (go_left > 0 && is_op(eq[go_left - 1]) && res >= 0)
                {//NOLINT
                    eq.insert(go_left, std::to_string(res));
                } else if (res < 0 && !is_op(eq[go_left]))
                {
                    eq.insert(go_left, std::to_string(res));
                } else if (res < 0)
                {
                    eq.insert(go_left, std::to_string(res));
                } else if (go_left != 0)
                {
                    eq.insert(go_left, "+" + std::to_string(res));
                } else
                {
                    eq.insert(go_left, std::to_string(res));
                }

                found = eq.find_first_of(op);
            }
        }
        return string_to<T>(eq);
    }

*/
    /**
     *  @brief  Convert negative number to positive.
     *  @param  v Number can be positive or negative.
     * Must be arithmetic
     *  @return Return absolute value of number
     */
    template<typename T>
    constexpr inline T abs(const T v)
    {
        return (v >= 0) ? v : -v;
    }

    /**
   *  @brief  Count element in data struct
   *  @param  begin Iterator to begin
   *  @param  end Iterator to end
   *  @param  element Element we want to count
   *  @return Return number of element in data structure
   */
    template<typename It, typename Elem>
    constexpr size_t count(It begin, const It end, const Elem &element)
    {
        size_t counter = 0;
        while (begin != end)
        {
            if (*begin == element)
                ++counter;
            ++begin;
        }
        return counter;
    }

    /**
   *  @brief  Count prediction element in data struct
   *  @param  begin Iterator to begin
   *  @param  end Iterator to end
   *  @param  pr Is function that return 1 if element count or 0 in otherwise
   *  @return Return number of element in data structure
   */
    template<typename It, typename Pr>
    constexpr size_t count_if(It begin, const It end, Pr pr)
    {
        size_t counter = 0;
        while (begin != end)
        {
            if (pr(*begin))
                ++counter;
            ++begin;
        }
        return counter;
    }

    /**
*  @brief  Check if number is automorphic
*  @param  n Number
*  @return Return 1 if n is automorphic or 0 if not.
*/
    constexpr bool is_automorphic(int64_t n)
    {
        n = abs(n);
        uint16_t digits = 0;
        for (int64_t cpy = n; cpy > 1; ++digits)
            cpy /= 10;
        return (static_cast<int64_t>(pow(n, 2)) % static_cast<int64_t>(pow(10, digits))) == n;
    }
}
#endif