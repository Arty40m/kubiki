#pragma once
#include <iostream>
#include "stl_headers.hpp"


#define LOG_ON

namespace LOGGING
{
    #if __linux__

    #elif _WIN32
    #include <windows.h> 

    inline void setColor(int textColor) { 
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
        SetConsoleTextAttribute(hConsole, textColor); 
    }

    #define LOG_WHITE 7
    #define LOG_GREEN 2
    #define LOG_YELLOW 6
    #define LOG_RED 4

    #ifdef LOG_ON
        #define LOG_INFO(...)   LOGGING::printTimeStamp();\
                                std::cout << "[INFO] ";\
                                LOGGING::LOG(__VA_ARGS__);

        #define LOG_DEBUG(...) LOGGING::setColor(LOG_GREEN);\
                                LOGGING::printTimeStamp();\
                                std::cout << "[DEBUG] ";\
                                LOGGING::LOG(__VA_ARGS__);\
                                LOGGING::setColor(LOG_WHITE);

        #define LOG_WARN(...) LOGGING::setColor(LOG_YELLOW);\
                                LOGGING::printTimeStamp();\
                                std::cout << "[WARN] ";\
                                LOGGING::LOG(__VA_ARGS__);\
                                LOGGING::setColor(LOG_WHITE);

        #define LOG_ERROR(...) LOGGING::setColor(LOG_RED);\
                                LOGGING::printTimeStamp();\
                                std::cout << "[ERROR] ";\
                                LOGGING::LOG(__VA_ARGS__);\
                                LOGGING::setColor(LOG_WHITE);
    #endif

    #ifndef LOG_ON
        #define LOG_INFO(...) 
        #define LOG_DEBUG(...) 
        #define LOG_WARN(...) 
        #define LOG_ERROR(...) 
    #endif

    #else
    std::cout << "Hello, Other!" << '\n';
    #endif

    inline std::string _to_string(char* x){return std::string(x);}
    inline std::string _to_string(const char* x){return std::string(x);}
    inline std::string _to_string(const unsigned char* x){return std::string((const char*)x);}
    inline std::string _to_string(std::string& x){return x;}
    inline std::string _to_string(const std::string& x){return x;}

    template<typename T>
    inline std::string _to_string(T x){return std::to_string(x);}


    inline void printTimeStamp()
    {
        time_t timestamp = time(NULL);
        struct tm datetime = *localtime(&timestamp);
        char time_output[15];
        strftime(time_output, 15, "%I:%M:%S", &datetime);
        std::cout << '[' << time_output << "] ";
    }

    template <typename... Types>
    inline void LOG(const char* fmt, Types&& ... args)
    {
        size_t N = sizeof...(Types);
        std::vector<std::string> values;
        values.reserve(N);
        ([&]{values.push_back(_to_string(args));} (), ...);
        
        int i = 0;
        int j = 0;
        while (fmt[j] != 0)
        {
            if (fmt[j]=='{' && i<N)
            {
                std::cout << values[i++];
            } else if (fmt[j]!='}'){
                std::cout << fmt[j];
            }
            j++;
        }
        
        std::cout << std::endl;
    }

}