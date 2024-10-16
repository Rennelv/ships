#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

// No Abilities Exception
class NoAbilitiesException : public std::runtime_error {
   public:
    NoAbilitiesException() : std::runtime_error("No abilities available to use!") {
    }
};

// Ship Placement Exception
class ShipPlacementException : public std::runtime_error {
   public:
    ShipPlacementException() : std::runtime_error("Invalid ship placement!") {
    }
};

// Out of Bounds Exception
class OutOfBoundsException : public std::runtime_error {
   public:
    OutOfBoundsException() : std::runtime_error("Attack out of bounds!") {
    }
};

#endif  // EXCEPTIONS_HPP