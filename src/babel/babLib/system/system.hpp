// Copyright [2021] <Wojtek>
#ifndef BABLIB_SYSTEM_SYSTEM_HPP_
#define BABLIB_SYSTEM_SYSTEM_HPP_

#include <sstream>
#include <thread>
#include "../concepts/concepts.hpp"

#ifdef _WIN32
#include "windows.hpp"
#endif  // _WIN32

#ifdef linux

#include "linux.hpp"

#endif  // linux

namespace babel::SYSTEM{

    /**
*  @brief  Return number of threads
*  \Example_1 return 16
*  \Example_2 return 8
*  @return Number of processor thread
*/
    [[nodiscard]] inline auto number_of_threads() noexcept
    {
        if constexpr( sizeof(void *) == 8 )
        {
            return std::thread::hardware_concurrency();
        } else
        {
#ifdef _WIN32
            SYSTEM_INFO SysInfo;
            GetSystemInfo(&SysInfo);
            return SysInfo.dwNumberOfProcessors;
#endif
#ifdef linux
            return sysconf(_SC_NPROCESSORS_ONLN);
#endif
        }
    }


    /**
*  @brief  Return thread id as string (default this_thread)
*  \Example_1 return 1
*  \Example_2 return 2
*  @return Return std::string
*/
    [[nodiscard]] inline std::string threadID_as_string(const std::thread::id ID = std::this_thread::get_id()) noexcept
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
    template< typename Func, typename ... Args >
    requires(babel::CONCEPTS::IS_VOID_RETURN<Func, Args...>)
    [[nodiscard]] inline std::thread call_function_on_another_thread(Func
                                                                     function,
                                                                     Args &&... args
    ) noexcept
    {
        std::thread thTemporaryThread(function, std::forward<Args>(args)...);
        return
                thTemporaryThread;
    }

    namespace DISPLAY{
        [[nodiscard]] inline std::pair<std::size_t, std::size_t> get_screen_resolution() noexcept
        {
#ifdef linux
            return babel::LINUX::DISPLAY::get_screen_resolution();
#elif _WIN32
            return babel::WINDOWS::DISPLAY::get_screen_resolution();
#endif
        }
    }  // namespace DISPLAY

    namespace SYSTEM{
        inline std::vector<std::string> all_discs() noexcept
        {
#ifdef linux
            return babel::LINUX::SYSTEM::all_discs();
#elif _WIN32
            return babel::WINDOWS::SYSTEM::all_discs();
#endif
        }
    }  // namespace SYSTEM

}  // namespace babel::SYSTEM
#endif  // BABLIB_SYSTEM_SYSTEM_HPP_
