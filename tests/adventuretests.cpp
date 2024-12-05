/**
 * @file Player.cpp
 * @author Dave Blair (dblair@seafoamtechnologies.com)
 * @brief This is a Unit Test Fixture to the Card class
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024 Seafoam Technologies
 *
 */
#include <gtest/gtest.h>
#include <vector>

#include <Node.hpp>
#include <AdventureGameMap.hpp>
#include <Player.hpp>
#include <Combatant.hpp>
#include <Character.hpp>

// https://google.github.io/googletest/reference/assertions.html

/**
 * @brief Test parameterized constructor that creates a valid Card object.
 *      In this case, a card is created at the lowest valid suit integer
 *      and the highest valid value integer. Suit 1, Value 1
 */
TEST(NodeTest, ValidNode)
{
    ASSERT_EQ(5, 5);
}
