#ifndef NO_ABILITIES_EXCEPTION_HPP
#define NO_ABILITIES_EXCEPTION_HPP

#include "BaseException.hpp"

namespace exceptions {

class NoAbilitiesException : public BaseException {
   public:
    NoAbilitiesException() : BaseException("No abilities available") {
    }
    explicit NoAbilitiesException(const std::string& message) : BaseException(message) {
    }
    explicit NoAbilitiesException(const char* message) : BaseException(message) {
    }
};

}  // namespace exceptions

#endif  // NO_ABILITIES_EXCEPTION_HPP