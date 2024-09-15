cmake_minimum_required(VERSION 3.10)

project(MyProject)

set(SOURCES
	main.cpp
	modules/Ship.cpp
    modules/ShipField.cpp
    modules/ShipManager.cpp
)

add_executable(MyProject ${SOURCES})