#ifndef TOOLS_H
#define TOOLS_H

#include <map>
#include <string>

class Tools
{
    public:
        inline static std::map<std::string, std::string> ft = {
            { "red", "\x1B[31m" },
            { "green", "\033[32m" },
            { "magenta", "\033[35m" },
            { "yellow", "\033[33m" },
            { "underline", "\033[4m" },
            { "endf", "\033[0m" } };
        static void waitMs(int ms);
        static void clearConsole();
        static std::string lower(std::string st);
        static std::string insertChars(std::string c, int t);
};

#endif // !TOOLS_H
