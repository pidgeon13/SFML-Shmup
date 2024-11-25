#include "pch.h"
#include "Geometry.h"

TEST(GeometryTests, Length2) {
	sf::Vector2f vector(4, 3);
	float length2 = Geometry::Length2(vector);
	EXPECT_EQ(length2, 25);
}