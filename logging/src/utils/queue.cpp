#include <utils.hpp>  // Copyright 2025 wiserin
#include <logging/schemas.hpp>


bool LogComparator::operator()(const Log& a, const Log& b) const {
    return static_cast<int>(a.priority) < static_cast<int>(b.priority);
}

