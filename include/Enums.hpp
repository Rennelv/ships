#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class ShipSegmentState {
    INTACT = 2,
    DAMAGED = 1,
    DESTROYED = 0,
};

enum class ShipOrientation {
    HORIZONTAL,
    VERTICAL,
};

enum class CellVisibilityState {
    UNKNOWN,
    BLANK,
    SHIP,
};

enum class Stage {
    NOT_STARTED,
    CREATING_FIELD,
    CREATING_SHIPS,
    PLACING_SHIPS,
    PLAYER_TURN,
    AI_TURN,
    GAME_OVER,
    EXIT,
};

#endif  // ENUMS_HPP