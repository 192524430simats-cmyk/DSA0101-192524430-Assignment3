# Assignment 3 - DSA0101

**Student:** Mohamed Haarun M.H  
**Register number:** 192524430  
**Compiler:** Pending execution on a system with GCC; recommended g++ 13 or newer  
**Standard:** C++17

## Compile and run

From the repository root, compile each task with:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic Task01/main.cpp -o Task01/task01
./Task01/task01
```

Replace `Task01` / `task01` with `Task02` / `task02` through `Task07` / `task07`. For memory checks, add `-fsanitize=address -fno-omit-frame-pointer -g` to the compile command. For timing comparisons, use separate `-O0` and `-O2` builds and record machine/compiler details. Windows users can run the executable as `Task01\task01.exe`.

## Task notes

| Task | Implementation and result note |
|---|---|
| Q1 | `Task01/main.cpp` demonstrates delegated default, title-only and full constructors; negative copies throw `std::invalid_argument`. |
| Q2 | `Task02/main.cpp` implements deep copy, copy assignment and destruction; `Prescription` copies own independent arrays. |
| Q3 | `Task03/main.cpp` dynamically creates seat rows, books/cancels seats and uses RAII row owners; scope exit prints event closure. |
| Q4 | `Task04/main.cpp` stores paise in an integer and overloads arithmetic, comparison and stream operators; includes carry and negative results. |
| Q5 | `Task05/main.cpp` implements prefix/postfix increment and checked const/non-const playlist subscripting. |
| Q6 | `Task06/main.cpp` implements a dynamically allocated `Text` with Rule of Three, concatenation, comparison and output. |
| Q7 | `Task07/main.cpp` implements complex arithmetic, rectangular output, magnitude, RLC examples and checked division by zero. |

## Evidence status

The provided GitHub repository was empty when fetched. This checkout now contains the seven task programs and an explanatory report at `REPORT.md`. The current execution environment does not expose `g++`, `clang++`, or `cl`, so no C++ run, compiler diagnostic, sanitizer log, timing measurement, or genuine output screenshot is claimed here. `evidence/` is reserved for screenshots and logs after execution with a C++17 compiler. The output text in the report is a source-level prediction and must be checked against actual runs before submission.

GitHub repository: https://github.com/192524430simats-cmyk/DSA0101-192524430-Assignment3

## Commit history

The remote repository now has progressive commits covering Tasks 1-7. The connected GitHub integration created the repository commits because this shell had no GitHub credentials. The local checkout also has one commit per task. These commits include source and predicted output files; they do not imply the C++ programs were executed.

```sh
git add Task01 && git commit -m "Complete Task 1 constructors"
```

The local history is visible with `git log --oneline`.

