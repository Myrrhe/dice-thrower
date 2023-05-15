#include "System.hpp"
#include "Global.hpp"
#include "func.hpp"

System::System()
{

}

System::~System()
{

}

System::System(const System& /*other*/)
{

}

System& System::operator=(const System& rhs)
{
    if (this == &rhs)
    {
        return *this;
    }
    return *this;
}
