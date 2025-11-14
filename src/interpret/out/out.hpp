#pragma once
#include "../../pch.hpp"

class Output
{
public:
    long long output;

    Output() {};
    Output(long long v) : output(v) {}
    Output(const Output &o) : output(o.output) {}

    Output &operator-();
};