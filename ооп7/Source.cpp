#include <iostream>
#include <stdexcept>
#include <string>
#include <cstdlib>
class EmptyLinearEquationException {};
class CustomLinearException {
private:
    double a_value;
    std::string message;

public:
    CustomLinearException(double a, const std::string& msg)
        : a_value(a), message(msg) {
    }

    double getA() const {
        return a_value;
    }

    const char* what() const noexcept {
        return message.c_str();
    }
};
class DerivedLinearException : public std::runtime_error {
private:
    double a_value;
    double b_value;

public:
    DerivedLinearException(double a, double b, const std::string& msg)
        : std::runtime_error(msg), a_value(a), b_value(b) {
    }

    double getA() const {
        return a_value;
    }

    double getB() const {
        return b_value;
    }
};
double solveLinear1(double a, double b) {
    if (a == 0.0) {
        throw EmptyLinearEquationException();
    }
    return -b / a;
}
double solveLinear2(double a, double b) noexcept(false) {
    if (a == 0.0) {
        throw CustomLinearException(
            a,
            "Error: Coefficient A cannot be zero!"
        );
    }
    return -b / a;
}
double solveLinear3(double a, double b) {
    if (a == 0.0) {
        throw std::invalid_argument(
            "Error: A cannot be zero. Division by zero is impossible."
        );
    }
    return -b / a;
}
double solveLinear4(double a, double b) {
    if (a == 0.0) {
        throw DerivedLinearException(
            a,
            b,
            "Error: Invalid coefficients. A cannot be zero."
        );
    }
    return -b / a;
}

int main() {
    std::cout << "=== LINEAR EQUATION SOLVER ===\n";
    std::cout << "Equation: Ax + B = 0\n\n";
    std::cout << "1. Testing function without exception specification:\n";

    try {
        double a = 0.0, b = 5.0;

        std::cout << "Solving equation for A = " << a
            << ", B = " << b << "...\n";

        double x = solveLinear1(a, b);

        std::cout << "Root x = " << x << "\n";
    }
    catch (const EmptyLinearEquationException&) {
        std::cerr << "[CAUGHT] Empty custom exception: "
            << "Coefficient A is zero!\n\n";
    }
    std::cout << "2. Testing function with exception specification:\n";

    try {
        double a = 0.0, b = -3.0;

        std::cout << "Solving equation for A = " << a
            << ", B = " << b << "...\n";

        double x = solveLinear2(a, b);

        std::cout << "Root x = " << x << "\n";
    }
    catch (const CustomLinearException& e) {
        std::cerr << "[CAUGHT] Independent custom exception:\n"
            << "  Message: " << e.what() << "\n"
            << "  Invalid value of A = " << e.getA()
            << "\n\n";
    }
    std::cout << "3. Testing function with standard exception:\n";

    try {
        double a = 0.0, b = 8.0;

        std::cout << "Solving equation for A = " << a
            << ", B = " << b << "...\n";

        double x = solveLinear3(a, b);

        std::cout << "Root x = " << x << "\n";
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "[CAUGHT] Standard exception "
            << "(std::invalid_argument):\n"
            << "  Message: " << e.what() << "\n\n";
    }
    std::cout << "4. Testing function with custom derived exception:\n";

    try {
        double a = 0.0, b = 4.0;

        std::cout << "Solving equation for A = " << a
            << ", B = " << b << "...\n";

        double x = solveLinear4(a, b);

        std::cout << "Root x = " << x << "\n";
    }
    catch (const DerivedLinearException& e) {
        std::cerr << "[CAUGHT] Custom derived exception:\n"
            << "  Message: " << e.what() << "\n"
            << "  Value of A = " << e.getA() << "\n"
            << "  Value of B = " << e.getB() << "\n\n";
    }
    std::cout << "5. Successful calculation (without exceptions):\n";

    try {
        double a = 2.0, b = -6.0;

        std::cout << "Solving equation: 2.0x - 6.0 = 0\n";

        double x = solveLinear1(a, b);

        std::cout << "Result: x = " << x << "\n";
    }
    catch (...) {
        std::cerr << "Unexpected error occurred!\n";
    }
    return 0;
}