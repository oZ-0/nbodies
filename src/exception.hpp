#pragma once

#include <exception>
#include <stdexcept>

using namespace std;

class division_by_zero : public runtime_error {

public:
  division_by_zero() : runtime_error("Division by zero") {}
};