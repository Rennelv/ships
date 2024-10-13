#ifndef ENUMS_HPP
#define ENUMS_HPP

enum class ShipSegmentState { INTACT = 2, DAMAGED = 1, DESTROYED = 0 };
enum class ShipOrientation { HORIZONTAL, VERTICAL };
enum class CellVisibilityState { UNKNOWN, BLANK, SHIP };
enum class MenuResult { Nothing, Exit, Play };

#endif  // ENUMS_HPP