#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

#include <limits>
#include <thread>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include "../Calculator.h"

#ifdef _WIN32
    #define CLEAR_CMD "cls"
#else
    #define CLEAR_CMD "clear"
#endif

using namespace std;

// Utility: pause for milliseconds
void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
void showBanner(const std::string &path = "assets/banner.txt") {
    std::ifstream f(path);
    if (!f.is_open()) {
        std::cout << "=== OOP INTERACTIVE CALCULATOR ===\n";
        return;
    }

    std::string line;
    while (std::getline(f, line)) {
        std::cout << line << '\n';
    }
    f.close();

    // Wait for a keypress (simple cross-platform)
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // If previous input left a newline in the buffer, consume it:
    if (std::cin.peek() == '\n') std::cin.get();
}

// Simple loading animation
void loadingAnimation(const string &msg = "Processing") {
    cout << msg;
    for (int i = 0; i < 6; ++i) {
        cout << ".";
        cout.flush();
        sleep_ms(120);
    }
    cout << "\n";
}

// Print ASCII header
void printHeader() {
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════════╗\n";
    cout << "║              ✨ OOP INTERACTIVE CALCULATOR ✨            ║\n";
    cout << "╠════════════════════════════════════════════════════════╣\n";
}

// Print footer line
void printFooter() {
    cout << "╚════════════════════════════════════════════════════════╝\n";
}

// Safe input reading for double
bool readDouble(double &out) {
    while (true) {
        if (cin >> out) return true;
        if (cin.eof()) return false;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a number: ";
    }
}

// Safe input reading for int
bool readInt(int &out) {
    while (true) {
        if (cin >> out) return true;
        if (cin.eof()) return false;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer: ";
    }
}

// Menu printing
void printMainMenu() {
    printHeader();
    cout << "  1) Basic Operations ( + - * / )\n";
    cout << "  2) Advanced Operations (power, square, root, percentage, modulus, factorial)\n";
    cout << "  3) View History\n";
    cout << "  4) Clear History\n";
    cout << "  5) Settings (Theme)\n";
    cout << "  6) Exit\n";
    printFooter();
    cout << "Enter choice: ";
}

// Theme change (Windows only). On other OS this will attempt system call but may do nothing.
void setTheme(const string &code) {
#ifdef _WIN32
    string cmd = "color " + code; // e.g., "0A"
    system(cmd.c_str());
#else
    // On Unix-like terminals we can try ANSI sequences for simple color change (foreground only)
    // but avoid forcing as users may not want it. We'll do a subtle bold.
    if (code == "bold") cout << "\033[1m"; // enable bold
#endif
}

int main() {
    showBanner();
    Calculator calc;
    int choice = 0;

    // default theme (Windows-only); users may change in settings
#ifdef _WIN32
    setTheme("0A"); // Green text on black
#endif

    while (true) {
        system(CLEAR_CMD);
        printMainMenu();
        if (!readInt(choice)) break; // EOF handling

        if (choice == 1) {
            // Basic operations
            system(CLEAR_CMD);
            printHeader();
            cout << "-- Basic Operations --\n";
            cout << "Enter first number: ";
            double a, b;
            if(!readDouble(a)) break;
            cout << "Enter second number: ";
            if(!readDouble(b)) break;
            cout << "Enter operator (+ - * /): ";
            char op; cin >> op;

            loadingAnimation();
            double res = calc.calculate(a, b, op);
            if (std::isnan(res)) {
                cout << "\nResult: Error (see history for details)\n";
            } else {
                cout << fixed << setprecision(8);
                cout << "\nResult: " << a << " " << op << " " << b << " = " << res << "\n";
            }

            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (choice == 2) {
            // Advanced operations
            system(CLEAR_CMD);
            printHeader();
            cout << "-- Advanced Operations --\n";
            cout << "  a) Power (a^b)\n";
            cout << "  b) Square (x^2)\n";
            cout << "  c) Root (n-th root)\n";
            cout << "  d) Percentage (part of whole)\n";
            cout << "  e) Modulus (int % int)\n";
            cout << "  f) Factorial (int)\n";
            cout << "Choose option: ";
            char sub; cin >> sub;

            if (sub == 'a') {
                cout << "Enter base: "; double base; if(!readDouble(base)) break;
                cout << "Enter exponent: "; double exp; if(!readDouble(exp)) break;
                loadingAnimation();
                double r = calc.power(base, exp);
                cout << "\nResult: " << base << " ^ " << exp << " = " << fixed << setprecision(8) << r << "\n";
            }
            else if (sub == 'b') {
                cout << "Enter number: "; double x; if(!readDouble(x)) break;
                loadingAnimation();
                double r = calc.calculate(x);
                cout << "\nResult: square(" << x << ") = " << fixed << setprecision(8) << r << "\n";
            }
            else if (sub == 'c') {
                cout << "Enter value: "; double v; if(!readDouble(v)) break;
                cout << "Enter n (nth root): "; double n; if(!readDouble(n)) break;
                loadingAnimation();
                double r = calc.root(v, n);
                if (std::isnan(r)) cout << "\nResult: Error (see history)\n";
                else cout << "\nResult: " << n << "th root of " << v << " = " << fixed << setprecision(8) << r << "\n";
            }
            else if (sub == 'd') {
                cout << "Enter part: "; double part; if(!readDouble(part)) break;
                cout << "Enter whole: "; double whole; if(!readDouble(whole)) break;
                loadingAnimation();
                double r = calc.percentage(part, whole);
                if (std::isnan(r)) cout << "\nResult: Error (divide by zero)\n";
                else cout << "\nResult: " << part << " is " << fixed << setprecision(6) << r << "% of " << whole << "\n";
            }
            else if (sub == 'e') {
                cout << "Enter integer a: "; int a; if(!readInt(a)) break;
                cout << "Enter integer b: "; int b; if(!readInt(b)) break;
                loadingAnimation();
                int r = calc.modulus(a, b);
                cout << "\nResult: " << a << " % " << b << " = " << r << "\n";
            }
            else if (sub == 'f') {
                cout << "Enter non-negative integer: "; int n; if(!readInt(n)) break;
                loadingAnimation();
                long long r = calc.factorial(n);
                if (r < 0) cout << "\nResult: Error (invalid input)\n";
                else cout << "\nResult: " << n << "! = " << r << "\n";
            }
            else {
                cout << "Invalid option. Returning to main menu.\n";
            }

            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (choice == 3) {
            // View history
            system(CLEAR_CMD);
            printHeader();
            cout << "-- Operation History --\n\n";
            auto hist = calc.getHistory();
            if (hist.empty()) {
                cout << "(No history yet)\n";
            } else {
                int i = 1;
                for (const auto &line : hist) {
                    cout << setw(3) << i << ") " << line << "\n";
                    ++i;
                }
            }
            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (choice == 4) {
            // Clear history
            cout << "Are you sure you want to clear history? (y/n): ";
            char c; cin >> c;
            if (c == 'y' || c == 'Y') {
                calc.clearHistory();
                cout << "History cleared.\n";
            } else {
                cout << "Operation cancelled.\n";
            }
            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (choice == 5) {
            // Settings
            system(CLEAR_CMD);
            printHeader();
            cout << "-- Settings: Theme --\n";
            cout << "1) Default\n";
            cout << "2) Green (Windows)\n";
            cout << "3) Blue (Windows)\n";
            cout << "4) Yellow (Windows)\n";
            cout << "Choose theme (1-4): ";
            int t; if(!readInt(t)) break;
            if (t == 1) {
#ifdef _WIN32
                setTheme("0F"); // white on black
#endif
                cout << "Theme set to default.\n";
            } else if (t == 2) {
#ifdef _WIN32
                setTheme("0A");
#endif
                cout << "Theme set to green.\n";
            } else if (t == 3) {
#ifdef _WIN32
                setTheme("09");
#endif
                cout << "Theme set to blue.\n";
            } else if (t == 4) {
#ifdef _WIN32
                setTheme("0E");
#endif
                cout << "Theme set to yellow.\n";
            } else {
                cout << "Invalid theme.\n";
            }
            cout << "\nPress Enter to return to menu...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
        else if (choice == 6) {
            cout << "Are you sure you want to exit? (y/n): ";
            char ex; cin >> ex;
            if (ex == 'y' || ex == 'Y') {
                cout << "Goodbye!\n";
                break;
            }
        }
        else {
            cout << "Invalid choice. Press Enter to try again...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }

    return 0;
}
