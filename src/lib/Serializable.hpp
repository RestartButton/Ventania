#pragma once
#include <iostream>

class Serializable {
public:
    virtual void save(std::ostream& out) const = 0;
    virtual void load(std::istream& in) = 0;
    virtual ~Serializable() = default;
};