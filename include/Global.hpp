#ifndef GLOBAL_HPP
#define GLOBAL_HPP
#include <string>

class Global final
{
public:
    Global() = delete;
    Global(const Global& right) = delete;
    Global(Global&& right) = delete;
    Global& operator=(const Global& right) = delete;
    Global& operator=(Global&& right) = delete;
    ~Global() = delete;

    static const std::string EmptyStr;
    static const std::u32string EmptyStr32;

protected:
private:
};

#endif // GLOBAL_HPP
