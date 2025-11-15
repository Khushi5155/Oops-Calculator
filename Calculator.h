#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

// Calculator.h
// Header for OOP Interactive Calculator
// Contains class declaration, overloaded arithmetic functions,
// history tracking and utility methods.

class Calculator {
public:
    // --- Constructors / Destructor ---
    Calculator();
    ~Calculator();

    // --- Core overloaded calculation methods ---
    // Adds two doubles
    double calculate(double a, double b);

    // Adds two integers (demonstrates overload by different parameter types)
    double calculate(int a, int b);

    // Performs operation based on operator char: '+', '-', '*', '/'
    // Returns a special value (NaN) for invalid operator or errors — implementation handles errors.
    double calculate(double a, double b, char op);

    // Unary operation: returns square of the number
    double calculate(double a);

    // --- Extra overloaded / utility operations ---
    // Power: a ^ b
    double power(double base, double exponent);

    // Integer factorial (non-negative). Returns -1 for invalid input.
    long long factorial(int n);

    // Percentage: what is (part / whole) * 100
    double percentage(double part, double whole);

    // Root: nth root of value (n > 0)
    double root(double value, double n);

    // Modulus for integers
    int modulus(int a, int b);

    // --- History / Logging ---
    // Add an entry to operation history
    void addToHistory(const std::string &entry);

    // Retrieve the full history
    std::vector<std::string> getHistory() const;

    // Clear history
    void clearHistory();

    // --- Configuration / Helpers ---
    // Human-friendly formatting helper (returns formatted string)
    static std::string formatOperation(const std::string &op, double a, double b, const std::string &result);

private:
    // Stores operation history lines (most recent appended at back)
    std::vector<std::string> history_;
};

#endif // CALCULATOR_H
