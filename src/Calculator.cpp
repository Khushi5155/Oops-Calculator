#include "../Calculator.h"
#include <cmath>
#include <limits>
#include <sstream>
#include <iomanip>

// Calculator.cpp
// Implementation for OOP Interactive Calculator

Calculator::Calculator() {
    // reserve small history capacity to avoid frequent reallocations
    history_.reserve(64);
}

Calculator::~Calculator() {
    // nothing special to cleanup
}

// Adds two doubles
double Calculator::calculate(double a, double b) {
    double res = a + b;
    addToHistory(formatOperation("+", a, b, std::to_string(res)));
    return res;
}

// Adds two integers
double Calculator::calculate(int a, int b) {
    long long res = static_cast<long long>(a) + static_cast<long long>(b);
    addToHistory(formatOperation("+ (int)", static_cast<double>(a), static_cast<double>(b), std::to_string(res)));
    return static_cast<double>(res);
}

// Performs operation based on operator char
double Calculator::calculate(double a, double b, char op) {
    double result = std::numeric_limits<double>::quiet_NaN();
    std::ostringstream out;

    switch (op) {
        case '+':
            result = a + b;
            out << result;
            break;
        case '-':
            result = a - b;
            out << result;
            break;
        case '*':
            result = a * b;
            out << result;
            break;
        case '/':
            if (b == 0.0) {
                out << "Error: Division by zero";
                addToHistory(formatOperation("/", a, b, out.str()));
                return std::numeric_limits<double>::quiet_NaN();
            }
            result = a / b;
            out << std::setprecision(12) << result;
            break;
        default:
            out << "Error: Invalid operator";
            addToHistory(formatOperation(std::string(1, op), a, b, out.str()));
            return std::numeric_limits<double>::quiet_NaN();
    }

    addToHistory(formatOperation(std::string(1, op), a, b, out.str()));
    return result;
}

// Unary operation: returns square of the number
double Calculator::calculate(double a) {
    double res = a * a;
    addToHistory(formatOperation("square", a, 0.0, std::to_string(res)));
    return res;
}

// Power: a ^ b
double Calculator::power(double base, double exponent) {
    double res = std::pow(base, exponent);
    std::ostringstream out; out << std::setprecision(12) << res;
    addToHistory(formatOperation("power", base, exponent, out.str()));
    return res;
}

// Integer factorial (non-negative). Returns -1 for invalid input.
long long Calculator::factorial(int n) {
    if (n < 0) {
        addToHistory(formatOperation("factorial", n, 0.0, std::string("Error: negative input")));
        return -1;
    }
    long long res = 1;
    for (int i = 2; i <= n; ++i) {
        res *= i;
        // avoid overflow detection (simple) — if it becomes negative, overflow
        if (res < 0) break;
    }
    std::ostringstream out; out << res;
    addToHistory(formatOperation("factorial", n, 0.0, out.str()));
    return res;
}

// Percentage: what is (part / whole) * 100
double Calculator::percentage(double part, double whole) {
    if (whole == 0.0) {
        addToHistory(formatOperation("%", part, whole, std::string("Error: divide by zero")));
        return std::numeric_limits<double>::quiet_NaN();
    }
    double res = (part / whole) * 100.0;
    std::ostringstream out; out << std::setprecision(8) << res << "%";
    addToHistory(formatOperation("%", part, whole, out.str()));
    return res;
}

// Root: nth root of value (n > 0)
double Calculator::root(double value, double n) {
    if (n == 0.0) {
        addToHistory(formatOperation("root", value, n, std::string("Error: zero root")));
        return std::numeric_limits<double>::quiet_NaN();
    }
    // handle negative values for odd roots
    double res = std::pow(value, 1.0 / n);
    std::ostringstream out; out << std::setprecision(12) << res;
    addToHistory(formatOperation("root", value, n, out.str()));
    return res;
}

// Modulus for integers
int Calculator::modulus(int a, int b) {
    if (b == 0) {
        addToHistory(formatOperation("modulus", a, b, std::string("Error: modulus by zero")));
        return 0; // convention: return 0 on error
    }
    int res = a % b;
    addToHistory(formatOperation("modulus", a, b, std::to_string(res)));
    return res;
}

// Add an entry to operation history
void Calculator::addToHistory(const std::string &entry) {
    history_.push_back(entry);
}

// Retrieve the full history
std::vector<std::string> Calculator::getHistory() const {
    return history_;
}

// Clear history
void Calculator::clearHistory() {
    history_.clear();
}

// Human-friendly formatting helper (returns formatted string)
std::string Calculator::formatOperation(const std::string &op, double a, double b, const std::string &result) {
    std::ostringstream out;

    // pretty format based on operation
    if (op == "square") {
        out << "square(" << a << ") = " << result;
    } else if (op == "factorial") {
        out << "factorial(" << static_cast<int>(a) << ") = " << result;
    } else if (op == "power") {
        out << a << " ^ " << b << " = " << result;
    } else if (op == "%") {
        out << "percentage: " << a << " of " << b << " = " << result;
    } else if (op == "root") {
        out << b << "th root of " << a << " = " << result;
    } else if (op == "modulus") {
        out << static_cast<int>(a) << " % " << static_cast<int>(b) << " = " << result;
    } else {
        // default binary op formatting
        out << a << " " << op << " " << b << " = " << result;
    }

    return out.str();
}