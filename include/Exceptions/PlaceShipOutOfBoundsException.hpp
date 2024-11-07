#ifndef PLACE_SHIP_OUT_OF_BOUNDS_EXCEPTION_HPP
#define PLACE_SHIP_OUT_OF_BOUNDS_EXCEPTION_HPP

#include "BaseException.hpp"

namespace exceptions {

class PlaceShipOutOfBoundsException : public BaseException {
   public:
    PlaceShipOutOfBoundsException() : BaseException("Out of bounds") {
    }
    explicit PlaceShipOutOfBoundsException(const std::string& message) : BaseException(message) {
    }
    explicit PlaceShipOutOfBoundsException(const char* message) : BaseException(message) {
    }
};

}  // namespace exceptions

#endif  // OUT_OF_BOUNDS_EXCEPTION_HPP