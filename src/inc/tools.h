#ifndef TOOLS_H
#define TOOLS_H

#include <map>
#include <string>

class Tools
{
    public:
        static void clearConsole();
        static void waitMs(int ms);
        static std::string lower(std::string st);
        static std::string insertChars(std::string c, int t);
        inline static std::map<std::string, std::string> ft = {
            { "red", "\x1B[31m" },
            { "green", "\033[32m" },
            { "magenta", "\033[35m" },
            { "yellow", "\033[33m" },
            { "underline", "\033[4m" },
            { "endf", "\033[0m" } };
};

#endif // !TOOLS_H
