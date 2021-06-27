#ifndef BABEL_SYSTEM
#define BABEL_SYSTEM

#include "must_have.hpp"
namespace babel::SYSTEM{

    /**
*  @brief  Return number of threads
*  \Example_1 return 16
*  \Example_2 return 8
*  @return Number of processor thread
*/
    [[nodiscard]] std::size_t number_of_threads() noexcept
    {
        //TODO hardware_concurrency doesnt work on 32bit clang
        return babel::COMPILER_IS_64B ? std::thread::hardware_concurrency() : 0; //NOLINT
    }


    /**
*  @brief  Return thread id as string (default this_thread)
*  \Example_1 return 1
*  \Example_2 return 2
*  @return Return std::string
*/
    [[nodiscard]] std::string threadID_as_string(const std::thread::id ID =  std::this_thread::get_id()) noexcept
    {
        std::stringstream StringStream;
        StringStream << ID;
        return StringStream.str();
    }

    /**
*  @brief  Call function in another thread (Function must be void)
*  @param  Func Function to call
*  @param  Args Arguments to function
*  @return Return std::thread, remember to join this thread before end program
*/
    template<typename Func, typename ... Args>
    requires (babel::CONCEPTS::IS_VOID_RETURN<Func, Args...>)
    [[nodiscard]] std::thread call_function_on_another_thread(Func function, Args&& ... args) noexcept
    {
        std::thread t1(function, std::forward<Args>(args)...);
        return t1;
    }


}

#endif
