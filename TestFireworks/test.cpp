#include "pch.h"
#include "FireWorks.h"
#include "BasicTypes.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(FireWorks, Firework)
{
	Particles::Fireworks fireworks;
	Colour colour;
	colour = Colour(0, 0, 255, 255);

	EXPECT_EQ(colour, fireworks.setColourBlue());
	EXPECT_TRUE(true);
}