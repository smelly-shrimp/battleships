#ifndef FMAN_H
#define FMAN_H

#include <string>
#include <vector>

class Fman
{
    public:
        static std::vector<std::string> read(std::string file);
        static void playAnim(std::string file, bool isClean, bool isPingPong, int ms = 500);
        static void readData();
        static void writeData();
    private:
        inline static std::vector<std::string> _frames{};
        static void _pingPong(std::vector<std::string> f, int i);
};

#endif // !FMAN_H
