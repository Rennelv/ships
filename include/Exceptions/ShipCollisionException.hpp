#ifndef SHIP_COLLISION_EXCEPTION_HPP
#define SHIP_COLLISION_EXCEPTION_HPP

#include <string>

#include "BaseException.hpp"

namespace exceptions {

class ShipCollisionException : public BaseException {
   public:
    ShipCollisionException() : BaseException("Ship collision detected") {
    }
    explicit ShipCollisionException(const std::string& message) : BaseException(message) {
    }
    explicit ShipCollisionException(const char* message) : BaseException(message) {
    }
};

}  // namespace exceptions

#endif  // SHIP_COLLISION_EXCEPTION_HPP