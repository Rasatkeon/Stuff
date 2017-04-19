#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "Complex.hpp"
#include "DoubleSolver.hpp"
#include "ComplexSolver.hpp"

using namespace MyMath;
using namespace Solver;

#define pi std::acos(-1)

SCENARIO("Testing complex numbers") {
    GIVEN("A complex number") {
        WHEN("The number is constructed with no parameters") {
            Complex zero;
            THEN("It is a complex zero") {
                REQUIRE(zero.getRe() == Approx(0));
                REQUIRE(zero.getIm() == Approx(0));
            }
            AND_THEN("It's arg and phase are zero") {
                REQUIRE(zero.getArg()   == Approx(0));
                REQUIRE(zero.getPhase() == Approx(0));
            }
        }
        WHEN("The number is constructed with (1;1)") {
            Complex num(1,1);
            THEN("It's arg and phase are correct") {
                REQUIRE(num.getArg()   == Approx(std::sqrt(2)));
                REQUIRE(num.getPhase() == Approx(pi/4));
            }
        }
        AND_WHEN("This number is converted to string") {
            Complex num(1,1);
            std::string res = num.toString();
            THEN("It matches \"(1.000000;1.000000)\"") {
                REQUIRE(res == "(1.000000;1.000000)");
            }
        }
        WHEN("We have two numbers") {
            Complex num1(1,1), num2(1,1);
            THEN("Sum is correct") {
                Complex sum = num1 + num2;
                REQUIRE(sum.getRe() == Approx(2));
                REQUIRE(sum.getIm() == Approx(2));
            }
            AND_THEN("Difference is correct") {
                Complex dif = num1 - num2;
                REQUIRE(dif.getRe() == Approx(0));
                REQUIRE(dif.getIm() == Approx(0));
            }
            AND_THEN("Negation is correct") {
                Complex neg = -num1;
                REQUIRE(neg.getRe() == Approx(-1));
                REQUIRE(neg.getIm() == Approx(-1));
            }
            AND_THEN("Multiplication is correct") {
                Complex mul = num1 * num2;
                REQUIRE(mul.getRe() == Approx(0));
                REQUIRE(mul.getIm() == Approx(2));
            }
            AND_THEN("Division is correct") {
                Complex div = num1 / num2;
                REQUIRE(div.getRe() == Approx(1));
                REQUIRE(div.getIm() == Approx(0));
            }
            AND_THEN("Power is correct") {
                Complex Pow = Complex::pow(num1, 5);
                REQUIRE(Pow.getRe() == Approx(-4));
                REQUIRE(Pow.getIm() == Approx(-4));
            }
            AND_THEN("Sqrt is correct") {
                Complex Sqrt = Complex::sqrt(num1);
                REQUIRE(Sqrt.getArg()   == Approx(1.189).epsilon(0.001));
                REQUIRE(Sqrt.getPhase() == Approx(0.392).epsilon(0.001));
            }
        }
    }
}
SCENARIO("Testing Double Solver") {
    GIVEN("Double solver for (1, -2, 1)") {
        DoubleSolver solv(1, -2, 1);
        WHEN("Trying to compute some results") {
            auto res1 = solv.calculateY(4);
            auto res2 = solv.calculateY(-5);
            THEN("Results are correct") {
                REQUIRE(res1 == Approx(9));
                REQUIRE(res2 == Approx(36));
            }
        }
        AND_WHEN("Trying to find a solution") {
            auto sol = solv.solve();
            THEN("Result is correct") {
                REQUIRE(sol.size() == 1);
                REQUIRE(sol[0] == Approx(1));
            }
        }
    }
    GIVEN("Double solver for (1, 0, -1)") {
        DoubleSolver solv(1, 0, -1);
        WHEN("Trying to find a solution") {
            auto sol = solv.solve();
            THEN("Solution is correct") {
                REQUIRE(sol.size() == 2);
                REQUIRE(sol[0] == Approx(1));
                REQUIRE(sol[1] == Approx(-1));
            }
        }
    }
    GIVEN("Double solver for (1, 1, 1)") {
        DoubleSolver solv(1, 1, 1);
        WHEN("Trying to find a solution") {
            auto sol = solv.solve();
            THEN("Solution is correct") {
                REQUIRE(sol.size() == 1);
                REQUIRE(isnan(sol[0]));
            }
        }
    }
}
SCENARIO("Testing Complex Solver") {
    GIVEN("Complex solver for (1, 1, 1)") {
        ComplexSolver solv(1, 1, 1);
        WHEN("Trying to compute a result") {
            auto sol = solv.solve();
            THEN("Results are correct") {
                REQUIRE(sol.size() == 2);
                REQUIRE(sol[0].getRe() == Approx(-0.5));
                REQUIRE(sol[0].getIm() == Approx(0.866).epsilon(0.0001));
                REQUIRE(sol[1].getRe() == Approx(-0.5));
                REQUIRE(sol[1].getIm() == Approx(-0.866).epsilon(0.0001));
            }
        }
    }
}
