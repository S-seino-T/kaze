#include "out.hpp"

Output Output::operator-() const
{

    if (output < 0 && output < -std::numeric_limits<long long>::max())
    {
        throw InterpretException("Overflow in calculation unary '-'");
    }
    return Output(-output);
}

Output Output::operator+(const Output &rhs) const
{
    if (rhs.output > 0 && output > std::numeric_limits<long long>::max() - rhs.output)
    {
        throw InterpretException("Overflow in calculation binary '+'");
    }
    else if (rhs.output < 0 && output < std::numeric_limits<long long>::min() - rhs.output)
    {
        throw InterpretException("Underflow in calculation binary '+'");
    }

    return Output(output + rhs.output);
}

Output Output::operator-(const Output &rhs) const
{
    if (rhs.output < 0 && output > std::numeric_limits<long long>::max() + rhs.output)
    {
        throw InterpretException("Overflow in calculation binary '-'");
    }
    else if (rhs.output > 0 && output < std::numeric_limits<long long>::min() + rhs.output)
    {
        throw InterpretException("Underflow in calculation binary '-'");
    }
    return Output(output - rhs.output);
}

Output Output::operator*(const Output &rhs) const
{
    if ((output / std::abs(output)) * (rhs.output / std::abs(rhs.output)) > 0)
    {
        if (rhs.output > 0 && output > std::numeric_limits<long long>::max() / rhs.output)
        {
            throw InterpretException("Overflow in calculation binary '*'");
        }
        else if (rhs.output < 0 && output < std::numeric_limits<long long>::max() / rhs.output)
        {
            throw InterpretException("Overflow in calculation binary '*'");
        }
    }
    else if ((output / std::abs(output)) * (rhs.output / std::abs(rhs.output)) < 0)
    {
        if (rhs.output < 0 && output >= std::numeric_limits<long long>::min() / rhs.output)
        {
            throw InterpretException("Underflow in calculation binary '*'");
        }
        else if (rhs.output > 0 && output <= std::numeric_limits<long long>::min() / rhs.output)
        {
            throw InterpretException("Underflow in calculation binary '*'");
        }
    }
    return Output(output * rhs.output);
}

Output Output::operator/(const Output &rhs) const
{
    if (rhs.output == 0)
    {
        throw InterpretException("Zero Division.");
    }
    return Output(output / rhs.output);
}

Output Output::___mod___(const Output &rhs) const
{
    if (rhs.output == 0)
    {
        throw InterpretException("Zero Division.");
    }
    return Output(output % rhs.output);
}

std::strong_ordering Output::operator<=>(const Output &rhs) const
{
    return output <=> rhs.output;
}