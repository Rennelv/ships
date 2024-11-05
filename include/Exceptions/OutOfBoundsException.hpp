#ifndef OUT_OF_BOUNDS_EXCEPTION_HPP
#define OUT_OF_BOUNDS_EXCEPTION_HPP

#include "BaseException.hpp"

namespace exceptions {

class OutOfBoundsException : public BaseException {
   public:
    OutOfBoundsException() : BaseException("Out of bounds") {
    }
    explicit OutOfBoundsException(const std::string& message) : BaseException(message) {
    }
    explicit OutOfBoundsException(const char* message) : BaseException(message) {
    }
};

}  // namespace exceptions

#endif  // OUT_OF_BOUNDS_EXCEPTION_HPP