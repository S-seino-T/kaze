#include "out.hpp"

Output &Output::operator-()
{
    output = -output;
    return *this;
}