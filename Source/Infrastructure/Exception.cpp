#include <Infrastructure/Exception.hpp>

Exception::Exception(const std::string& m) :
    std::runtime_error { m.c_str() }
{}
