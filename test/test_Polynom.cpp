#include "Polynom.h"

#include <gtest.h>



TEST(Polynom, can_create_Polynom)
{
	ASSERT_NO_THROW(Polynom Pol);

	//if the degree of one of the arguments of the polynomial is greater than 9 or less than 0, then the behavior of the program is undefined
}

TEST(Polynom, can_change_Polynom)
{
	Polynom Pol1;
	Polynom Pol2("x");
	Pol1.parse("x");
	ASSERT_EQ(Pol1, Pol2);
}


TEST(Polynom, can_add_Polynom)
{
	Polynom Pol1("2x");
	Polynom Pol2("x");
	Polynom Pol3;
	ASSERT_NO_THROW(Pol3 = Pol1 + Pol2);
	Polynom Pol("3x");
	ASSERT_EQ(Pol3, Pol);
}

TEST(Polynom, can_sub_Polynom)
{
	Polynom Pol1("2x");
	Polynom Pol2("x");
	Polynom Pol3;
	ASSERT_NO_THROW(Pol3 = Pol2 - Pol1);
	Polynom Pol("-x");
	ASSERT_EQ(Pol3, Pol);
}

TEST(Polynom, can_mult_Polynom)
{
	Polynom Pol1("2x");
	Polynom Pol2("x");
	Polynom Pol3;
	ASSERT_NO_THROW(Pol3 = Pol1 * Pol2);
	Polynom Pol("2x^2");
	ASSERT_EQ(Pol3, Pol);
}

TEST(Polynom, can_cmult_Polynom)
{
	Polynom Pol1("2x");
	int C = 6;
	Polynom Pol3;
	ASSERT_NO_THROW(Pol3 = Pol1 * C);
	Polynom Pol("12x");
	ASSERT_EQ(Pol3, Pol);
}

TEST(Polynom, cant_mult_Polynom)
{
	Polynom Pol1("2x^9");
	Polynom Pol2("x");
	Polynom Pol3;
	ASSERT_ANY_THROW(Pol3 = Pol1 * Pol2);

}