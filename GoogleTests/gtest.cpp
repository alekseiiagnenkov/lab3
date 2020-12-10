#pragma once

#include "gtest/gtest.h"
//#include "SFML/Graphics.hpp"
#include "../src/Army/Army.cpp"
#include "../src/Cell/Cell.cpp"
#include "../src/Colony/Colony.cpp"
#include "../src/Lair/Lair.cpp"
//#include "../src/Level/Level.cpp"
#include "../src/Object/Object.cpp"
#include "../src/ResourcePoint/ResourcePoint.cpp"
#include "../src/ResourcePoint/AcidPoint/AcidPoint.cpp"
#include "../src/ResourcePoint/FoodPoint/FoodPoint.cpp"
#include "../src/ResourcePoint/SaltPoint/SaltPoint.cpp"
//#include "../src/Scene/GameScene.cpp"
#include "../src/Table/Table.cpp"
#include "../src/TableOfResource/TableOfResource.cpp"
#include "../src/TableOfUnits/TableOfUnits.cpp"
#include "../src/Unit/Unit.cpp"
#include "../src/Unit/Stormtrooper/Stormtrooper.cpp"
#include "../src/Unit/Usual/Usual.cpp"
#include "../src/Unit/Cleaner/Cleaner.cpp"
#include "../src/Unit/Hunter/Hunter.cpp"

TEST(ObjectConstructor, TestExceptions) {
    std::string color = "green";
    std::string name = "stormtrooper";
    std::string errorName = "errorName";
    ASSERT_ANY_THROW(Object object(name, name, color, -1, 1, 1, 1));
    ASSERT_ANY_THROW(Object object(name, name, color, 1, -1, 1, 1));
    ASSERT_ANY_THROW(Object object(name, name, color, 1, 1, -1, 1));
    ASSERT_ANY_THROW(Object object(name, name, color, 1, 1, 1, -1));
    ASSERT_ANY_THROW(Object object(errorName, name, color, 1, 1, 1, 1));
}

//TEST(ObjectsSetters, TestAccordances) {
//    ASSERT_EQ();
//}

TEST(CellConstructor, TestExceptions) {
    sf::Sprite sprite;
    ASSERT_ANY_THROW(Cell cell(-1, 1, nullptr, 1));
    ASSERT_ANY_THROW(Cell cell(1, -1, nullptr, 1));
    ASSERT_ANY_THROW(Cell cell(1, 1, nullptr, -1));
}

TEST(CellSetters, TestExceptions) {
    Cell cell(1, 1, nullptr, 1);
    ASSERT_ANY_THROW(cell.setX(-1));
    ASSERT_ANY_THROW(cell.setY(-1));
}

TEST(ColonyConstructor, TestExceptions) {
    std::string color = "green";
    ASSERT_ANY_THROW(Colony colony(-1, 1, 1, nullptr, color, nullptr));
}

TEST(ColonySetters, TestExceptions) {
    std::string color = "green";
    Colony colony(1, 1, 1, nullptr, color, nullptr);
    ASSERT_ANY_THROW(colony.setAcid(-1));
    ASSERT_ANY_THROW(colony.setFood(-1));
    ASSERT_ANY_THROW(colony.setSalt(-1));
}

TEST(LairConstructor, TestExceptions) {
    std::string color = "green";
    std::string name = "lair";
    ASSERT_ANY_THROW(Lair lair(name, name, color, 1, 1, 1, 1, -1, 100));
}

TEST(LairSetters, TestExceptions) {
    std::string color = "green";
    std::string name = "lair";
    Lair lair(name, name, color, 1, 1, 1, 1, 1, 100);
    ASSERT_ANY_THROW(lair.setMaxHealth(-1));
    ASSERT_ANY_THROW(lair.setLevel(-1));
}

TEST(ResourcesSetters, TestExceptions) {
    std::string color = "green";
    std::string name = "lair";
    SaltPoint salt(name, name, color,nullptr, 1, 1, 1, 1, 1);
    ASSERT_ANY_THROW(salt.setMaxHealth(-1));
    ASSERT_ANY_THROW(salt.setIncrease(-1));
    FoodPoint food(name, name, color,nullptr, 1, 1, 1, 1, 1);
    ASSERT_ANY_THROW(food.setMaxHealth(-1));
    ASSERT_ANY_THROW(food.setIncrease(-1));
    AcidPoint acid(name, name, color,nullptr, 1, 1, 1, 1, 1);
    ASSERT_ANY_THROW(acid.setMaxHealth(-1));
    ASSERT_ANY_THROW(acid.setIncrease(-1));
}

TEST(TableConstructor, TestExceptions) {
    std::vector<Cell *> cells;
    int height = 1, width = 1;
    for (int i = 0; i < width * height; i++) {
        cells.push_back(new Cell(1, 1, nullptr, 1));
    }
    ASSERT_ANY_THROW(Table table(width, -1, cells));
    cells.push_back(new Cell(1, 1, nullptr, 1));
    ASSERT_ANY_THROW(Table table(1, 1, cells));
}

TEST(TableSetters, TestExceptions) {
    std::vector<Cell *> cells;
    int height = 10, width = 10;
    for (int i = 0; i < width * height; i++) {
        cells.push_back(new Cell(1, 1, nullptr, 1));
    }
    Table table(width, height, cells);
    ASSERT_ANY_THROW(table.setHeight(0));
    ASSERT_ANY_THROW(table.setWidth(0));
    cells.push_back(new Cell(1, 1, nullptr, 1));
    ASSERT_ANY_THROW(table.setField(cells));
}

TEST(StormtrooperConstructor, TestExceptions) {
    std::string name = "stormtrooper";
    std::string color = "green";
    ASSERT_ANY_THROW(Stormtrooper stormtrooper(name,name,color,1,1,1,1,-1,1));
}

TEST(StormtrooperSetters, TestExceptions) {
    std::string name = "stormtrooper";
    std::string color = "green";
    Stormtrooper stormtrooper(name, name, color, 1, 1, 1, 1, 1, 1);
    ASSERT_ANY_THROW(stormtrooper.setDamage(-1));
    ASSERT_ANY_THROW(stormtrooper.setMaxHealth(-1));
    ASSERT_ANY_THROW(stormtrooper.setLevel(-1));
    ASSERT_ANY_THROW(stormtrooper.setDodge(-1));
    ASSERT_ANY_THROW(stormtrooper.setIntake(-1));
}


TEST(UsualConstructor, TestExceptions) {
    std::string name = "usual";
    std::string color = "green";
    ASSERT_ANY_THROW(Usual usual(name,name,color,1,1,1,1,-1,1));
}

TEST(UsualSetters, TestExceptions) {
    std::string name = "stormtrooper";
    std::string color = "green";
    Usual usual(name,name,color,1,1,1,1,1,1);
    ASSERT_ANY_THROW(usual.setDamage(-1));
    ASSERT_ANY_THROW(usual.setTake(-1));
    ASSERT_ANY_THROW(usual.setMaxHealth(-1));
    ASSERT_ANY_THROW(usual.setLevel(-1));
    ASSERT_ANY_THROW(usual.setDodge(-1));
    ASSERT_ANY_THROW(usual.setIntake(-1));
}

TEST(HunterConstructor, TestExceptions) {
    std::string name = "hunter";
    std::string color = "green";
    ASSERT_ANY_THROW(Hunter hunter(name,name,color,1,1,1,1,-1,1));
}

TEST(HunterSetters, TestExceptions) {
    std::string name = "stormtrooper";
    std::string color = "green";
    Hunter hunter(name, name, color, 1, 1, 1, 1, 1, 1);
    ASSERT_ANY_THROW(hunter.setDamage(-1));
    ASSERT_ANY_THROW(hunter.setMaxHealth(-1));
    ASSERT_ANY_THROW(hunter.setLevel(-1));
    ASSERT_ANY_THROW(hunter.setDodge(-1));
    ASSERT_ANY_THROW(hunter.setIntake(-1));
}

TEST(CleanerConstructor, TestExceptions) {
    std::string name = "cleaner";
    std::string color = "green";
    ASSERT_ANY_THROW(Cleaner cleaner(name,name,color,1,1,1,1,-1,1));
}

TEST(CleanerSetters, TestExceptions) {
    std::string name = "stormtrooper";
    std::string color = "green";
    Cleaner cleaner(name,name,color,1,1,1,1,1,1);
    ASSERT_ANY_THROW(cleaner.setTake(-1));
    ASSERT_ANY_THROW(cleaner.setMaxHealth(-1));
    ASSERT_ANY_THROW(cleaner.setLevel(-1));
    ASSERT_ANY_THROW(cleaner.setDodge(-1));
    ASSERT_ANY_THROW(cleaner.setIntake(-1));

}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

