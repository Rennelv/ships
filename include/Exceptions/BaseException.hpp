#ifndef BASE_EXCEPTION_HPP
#define BASE_EXCEPTION_HPP

#include <exception>
#include <string>

namespace exceptions {

class BaseException : public std::exception {
   protected:
    std::string message;

   public:
    explicit BaseException(const std::string& message) : message(message) {
    }
    explicit BaseException(const char* message) : message(message) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

}  // namespace exceptions

#endif  // BASE_EXCEPTION_HPP