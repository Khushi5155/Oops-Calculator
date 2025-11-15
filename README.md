# OOP Interactive Calculator (C++)

A fully upgraded, terminal-based **OOP Interactive Calculator** written in C++.

This project demonstrates Object-Oriented Programming, function overloading, clean file separation, and a polished interactive command-line UI with features such as:

* Color themes (Windows `system("color XX")`)
* Small loading/animation effects
* Operation history and history management
* Input validation and division-by-zero handling
* Advanced overloaded functions (power, root, factorial, percentage, modulus)
* Attractive ASCII UI and formatted output
* Clean project structure suitable for submission or GitHub

---

## Folder structure

```
OOP_Interactive_Calculator/
│
├── include/
│   └── Calculator.h         # class declaration
│
├── src/
│   ├── Calculator.cpp       # class implementation
│   └── main.cpp             # interactive UI and program entry point
│
├── assets/
│   └── banner.txt           # optional ASCII banner (loaded at runtime)
│
├── build/                   # generated after compilation
│
└── README.md
```

---

## Requirements

* A C++17-compatible compiler (e.g. `g++`, `clang++`, or MSVC).
* No external libraries are required.

---

## Build & Run (Linux / macOS)

Open a terminal in the project root and run:

```bash
mkdir -p build
g++ -std=c++17 src/Calculator.cpp src/main.cpp -I include -o build/calculator
./build/calculator
```

> Note: On macOS and many Linux distros, terminal color-theme commands used for Windows will be ignored. The program still runs fine.

## Build & Run (Windows with MinGW)

Open Command Prompt (or Git Bash) and run:

```powershell
mkdir build
g++ -std=c++17 src/Calculator.cpp src/main.cpp -I include -o build\calculator.exe
build\calculator.exe
```

If you use MSVC (Visual Studio), create a console project and add the files under the project `include/` and `src/` folders.

---

## Files

* `include/Calculator.h` — class declaration, prototypes, and history interface.
* `src/Calculator.cpp` — full implementations of overloaded functions and history logging.
* `src/main.cpp` — interactive menu, UI, animations, input validation, and wiring to `Calculator`.
* `assets/banner.txt` — optional ASCII art shown on startup (add your own designs).

---

## Features & How to Use

1. **Basic operations**: Choose Menu -> Basic Operations, input two numbers and an operator (`+`, `-`, `*`, `/`).
2. **Advanced operations**: Power, square, nth root, percentage, modulus, factorial.
3. **History**: All performed operations are logged. View and clear history from the menu.
4. **Settings**: Change terminal theme (Windows only).
5. **Input validation**: The program re-prompts on invalid numeric input and prevents crashes.

Example workflow:

* Run program
* Select `1) Basic Operations`
* Enter `12.5`, `3`, and `*`
* The program shows a loading animation and prints `12.5 * 3 = 37.5` and adds the operation to history
* Go to View History to see the record

---

## Notes & Tips

* Terminal colors use Windows `system("color")` commands. On Unix-like terminals the program avoids forcing colors and uses bold text where appropriate.
* Factorial uses a simple 64-bit `long long` implementation; very large inputs may overflow.
* The program uses `std::numeric_limits<double>::quiet_NaN()` to indicate errors for floating operations where appropriate; these errors are also recorded into history with human-readable messages.

---

## Extending the Project

Ideas to expand:

* Add a GUI using a framework (Qt, wxWidgets, Dear ImGui)
* Persist history to a file (CSV or JSON)
* Add expression parsing (evaluate `3 + 4 * (2 - 1)`)
* Add unit tests using a test framework (Catch2, GoogleTest)

---

## License

This project is MIT-style: feel free to reuse, modify, and include in your portfolios or assignments. If you publish it, please keep a small credit line.

---

