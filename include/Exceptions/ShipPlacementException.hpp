#ifndef SHIP_PLACEMENT_EXCEPTION_HPP
#define SHIP_PLACEMENT_EXCEPTION_HPP

#include "BaseException.hpp"

namespace exceptions {

class ShipPlacementException : public BaseException {
   public:
    ShipPlacementException() : BaseException("Ship placement failed") {
    }
    explicit ShipPlacementException(const std::string& message) : BaseException(message) {
    }
    explicit ShipPlacementException(const char* message) : BaseException(message) {
    }
};

}  // namespace exceptions

#endif  // SHIP_PLACEMENT_EXCEPTION_HPP