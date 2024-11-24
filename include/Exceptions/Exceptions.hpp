#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace exceptions {

class GameException : public std::exception {
    std::string msg;

   public:
    explicit GameException(const std::string& message) : msg(message) {
    }
    const char* what() const noexcept override {
        return msg.c_str();
    }
};

class NoAbilityAvailableException : public GameException {
   public:
    NoAbilityAvailableException() : GameException("No abilities available") {
    }
    NoAbilityAvailableException(const std::string& message) : GameException(message) {
    }
};

class ShipPlacementConflictException : public GameException {
   public:
    ShipPlacementConflictException() : GameException("Ship placement conflict detected") {
    }
    ShipPlacementConflictException(const std::string& message) : GameException(message) {
    }
};

class OutOfBoundsAttackException : public GameException {
   public:
    OutOfBoundsAttackException() : GameException("Attack out of bounds") {
    }
    OutOfBoundsAttackException(const std::string& message) : GameException(message) {
    }
};
}  // namespace exceptions

#endif  // EXCEPTIONS_HPP
