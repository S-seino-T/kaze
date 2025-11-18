#pragma once
#include "../../pch.hpp"
#include "../../utils/common.hpp"

class Output
{
public:
    long long output;
    // using QandA = std::pair<std::string, std::function<Output(long long)>>;
    // bool func_flag;
    // QandA output;

    Output() {};
    Output(long long v) : output(v) {}
    // Output(std::string var) : output() {}
    Output(const Output &o) : output(o.output) {}

    Output operator-() const;
    Output operator+(const Output &rhs) const;
    Output operator-(const Output &rhs) const;
    Output operator*(const Output &rhs) const;
    Output operator/(const Output &rhs) const;
    Output ___mod___(const Output &rhs) const;
    std::strong_ordering operator<=>(const Output &rhs) const;
};

template <typename T>
class Config
{
    std::unordered_map<std::string, T> let_dict;

public:
    T value;
    std::string variable;
    T search_let(std::string var) const
    {
        try
        {
            return let_dict.at(var);
        }
        catch (const std::out_of_range &e)
        {
            throw VariableException("`" + var + "` is not defined.");
        }
    }
    bool try_add_let_dict(std::string var, T value)
    {
        auto ret = let_dict.emplace(var, value);
        return ret.second;
    }
};