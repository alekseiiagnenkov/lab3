cmake_minimum_required(VERSION 3.17)
# set the projectX name to the name of your project
project(Game)

set(CMAKE_CXX_STANDARD 17)
# set(SOURCE_FILES main.cpp)

add_executable(
        Game main.cpp

        lib/tinyxml2/tinyxml2.h
        lib/tinyxml2/tinyxml2.cpp

        src/Scene/GameScene.cpp
        src/Scene/GameScene.h

        src/Level/Level.h
        src/Level/Level.cpp

        src/Lair/Lair.cpp
        src/Lair/Lair.h

        src/Unit/Unit.cpp
        src/Unit/Unit.h
        src/Unit/Cleaner/Cleaner.cpp
        src/Unit/Cleaner/Cleaner.h
        src/Unit/Hunter/Hunter.cpp
        src/Unit/Hunter/Hunter.h
        src/Unit/Stormtrooper/Stormtrooper.cpp
        src/Unit/Stormtrooper/Stormtrooper.h
        src/Unit/Usual/Usual.cpp
        src/Unit/Usual/Usual.h

        src/Colony/Colony.cpp
        src/Colony/Colony.h

        src/ResourcePoint/ResourcePoint.cpp
        src/ResourcePoint/ResourcePoint.h
        src/ResourcePoint/AcidPoint/AcidPoint.cpp
        src/ResourcePoint/AcidPoint/AcidPoint.h
        src/ResourcePoint/FoodPoint/FoodPoint.cpp
        src/ResourcePoint/FoodPoint/FoodPoint.h
        src/ResourcePoint/SaltPoint/SaltPoint.cpp
        src/ResourcePoint/SaltPoint/SaltPoint.h

        src/Table/Table.cpp
        src/Table/Table.h

        src/Cell/Cell.cpp
        src/Cell/Cell.h

        src/TableOfUnits/TableOfUnits.cpp
        src/TableOfUnits/TableOfUnits.h

        src/Object/Object.cpp
        src/Object/Object.h

        src/Army/Army.cpp
        src/Army/Army.h

        src/TableOfResource/TableOfResource.cpp
        src/TableOfResource/TableOfResource.h

        lib/MyContainer/Container.h
)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system window graphics network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()