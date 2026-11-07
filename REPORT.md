# Assignment 3 Report - Constructors, Destructors and Operator Overloading

**Student:** Mohamed Haarun M.H  
**Register number:** 192524430  
**Repository:** https://github.com/192524430simats-cmyk/DSA0101-192524430-Assignment3  
**Compiler / version:** Zig 0.17.1, bundled Clang 22.1.8, used for syntax-only checks; full linking/running remains pending.  
**Syntax-check command:** `zig c++ -std=c++17 -Wall -Wextra -Wpedantic -fsyntax-only <source.cpp>`  
**Intended build flags:** `g++ -std=c++17 -Wall -Wextra -Wpedantic`.

> Execution integrity: All source files received a C++17 syntax-only check with bundled Clang. The environment did not produce a runnable executable, so output listings below are predictions derived from source and are not captured program output. Sanitizer output, benchmark values, and screenshots must be generated on a full C++ toolchain before final submission.

## Q1 - Constructors

`Task01/main.cpp` uses one canonical parameterized constructor, while default and title-only overloads delegate to it. Every constructor initializes members through a member-initializer list. The `checked` helper rejects a negative copy count before the object finishes construction. The three final states are: `empty = (Untitled, Unknown, 0)`, `donated = (The Hobbit, Unknown, 1)`, `complete = (Dune, Frank Herbert, 4)`.

The compiler only supplies a default constructor when no constructor is user-declared. Once a constructor is declared, an implicit default constructor is not generated. Initializer lists directly initialize members and are required for references, const members, and members without default constructors; assignment in the body first default-constructs then assigns. Members initialize in declaration order regardless of their order in the list. The implementation centralizes validation in one constructor path, so creation is O(1) time and O(1) extra space.

An `explicit` single-argument constructor prevents implicit conversions. Without `explicit`, `Book b = "The Hobbit";` can use the title constructor; with it, that copy-initialization is rejected while `Book b("The Hobbit");` remains valid. A single constructor with default arguments would reduce overload count, but can make call intent less clear; validation should still be centralized and object construction remains O(1) time/space.

Required experiments still to capture: remove the default constructor and compile a `Book books[2];` declaration (expected diagnostic: no matching/default constructor); make initializer-list order disagree with declaration order and compile with `-Wreorder` (expected warning); run the negative-copy case. The exact compiler text depends on compiler version.

## Q2 - Copy constructors

`Task02/main.cpp` implements the assignment's completed class: deep-copy constructor, self-assignment-safe copy assignment, and `delete[]` destructor. Copy construction and assignment both allocate a separate array and copy each string, O(n) time and O(n) storage. The self-assignment guard prevents reading from storage after it has been released. The `std::vector<std::string>` alternative follows Rule of Zero: the vector's generated copy operation already copies its elements independently.

For a shallow copy, both objects hold the same array address. Mutating through either object changes shared data; destruction then attempts to release one allocation twice, which is undefined behavior and commonly reported as double-free by AddressSanitizer. Deep copying has distinct buffers and independent contents. Rule of Three: if a class owns a resource and needs a destructor, it usually needs custom copy construction and copy assignment too. Copy construction occurs on initialization from another object, when a value parameter is initialized, and when a value is returned (though copy elision can remove some copies). A `const&` parameter does not copy the object.

Predicted output from the supplied complete-code program's first line: `Ibuprofen ORS | Paracetamol Cetirizine | Paracetamol ORS`. Sanitizer logs and copy timings for 10, 1,000, and 100,000 items are pending measurement. The shallow-copy sanitizer run must be isolated because its failure is intentional.

## Q3 - Dynamic construction and destruction

`Task03/main.cpp` allocates one dynamic row per seat row and stores each allocation in `unique_ptr<bool[]>`, so exceptions and scope exits release completed allocations safely. This RAII form preserves row allocation behavior while avoiding a handwritten destructor. For a raw pointer implementation, each row must be released with `delete[]`, followed by the row-pointer array with `delete[]`; forgetting `delete` leaks memory, and scalar `delete` on an array is undefined behavior. A destructor has no arguments and no return type; it cannot be overloaded because there is only one destruction event per object.

Local and block objects are destroyed in reverse construction order at scope exit. A heap object remains alive until `delete`; a pointer going out of scope does not destroy its pointee. The seat grid can be represented as row-pointer allocations (rows+1 allocations including the pointer array), one contiguous allocation (one allocation, index `r*seats+s`), or nested vectors (managed allocations). Access is O(1) in each; contiguous storage avoids per-row allocations and pointer-table space. Storage is O(rows*seats); row-pointer form adds O(rows) pointers.

The requested exact prediction for the handout's Logger program is listed in **Appendix A**. Memory measurements for 10x20, 100x200, and 1,000x2,000 and sanitizer runs are pending execution. Zero rows are included in the program.

## Q4 - Money operators

`Task04/main.cpp` stores a signed total number of paise, avoiding binary floating-point currency representation. `+` returns a new value; `+=` mutates and returns `Money&`, enabling chaining without an additional result object. Arithmetic/comparison operators are members; stream insertion/extraction are friends because the left operand is an `ostream`/`istream`, not a `Money`. `a+b` translates to `a.operator+(b)`. Multiplying two currency amounts has no natural billing meaning; scalar multiplication is more sensible if a use case defines rounding.

Predicted supplied program output:

```text
Rs 200.00
true
```

The added carry case predicts `Rs 1.25`; subtraction predicts `-Rs 1.00`. Integer arithmetic and double arithmetic each take O(1) per operation and O(1) storage. One million additions and the comparison against a double implementation require timing on the target compiler/machine; no benchmark is fabricated. The constructor accepts rupees and paise; production code should additionally validate paise range and overflow.

## Q5 - Increment, comparison and subscript

`Task05/main.cpp` uses the dummy `int` parameter to distinguish postfix `operator++(int)` from prefix `operator++()`. Prefix updates and returns a reference. Postfix saves and returns the prior value, so it requires a copy for class types. Checked `operator[]` has const and mutable overloads; both throw `std::out_of_range` for invalid indices. An index of `-1` converts to a large unsigned value and is rejected by the range check. Formatting 3,599 elapsed seconds and incrementing once gives the expected `01:00:00` rollover.

For the supplied Counter code, prediction is `5 7 7`: `a` receives the old value 5, then prefix increments the counter to 7 and `b` receives 7. Prefix avoids the old-value copy. Playlist access and its check are both O(1); measure the comparison cost over 10,000,000 accesses rather than assuming a machine-specific duration. The included simulation exercises invalid access; exhaustive rollover and -O0/-O2 timings remain to be run.

## Q6 - Text and operator rules

`Task06/main.cpp` owns a null-terminated character array and implements all three Rule of Three functions. Assignment allocates replacement storage before releasing the old allocation, and self-assignment is guarded. Concatenation and comparison are value operations; stream insertion is a friend non-member so `ostream << Text` works. The code's `+` constructs a joined temporary; a `+=`-based implementation can reduce intermediate allocations when concatenating repeatedly.

Operators that cannot be overloaded include `::`, `.`, `.*`, `?:`, and `sizeof`. Overloading cannot alter precedence, associativity, or operand count, and at least one operand must be a user-defined type. Assignment must be a member. A friend is appropriate when a non-member needs private access, often for symmetric operators or stream operations. For left-associated `a+b+c`, the first concatenation copies approximately n1+n2 characters to produce the temporary; the next copies approximately n1+n2+n3. Peak live storage includes the original operands and a growing temporary. `std::string` is normally preferred; handwritten ownership is mainly justified for learning, specialized representation, or explicit control needs. Sanitizer and 100,000-concatenation timings are pending.

## Q7 - Complex impedance

`Task07/main.cpp` uses real and imaginary doubles, default/real/two-component constructors, `+ - * / == <<`, and `magnitude()`. Multiplication uses `(ac-bd)+(ad+bc)j`; division uses `((ac+bd)+(bc-ad)j)/(c^2+d^2)`. Division checks a zero denominator and throws `std::domain_error`. Stream insertion is a friend; arithmetic and equality are members. The series example is `10 - j5 ohm`, magnitude `11.18 ohm`; the parallel R-L example is `2.00 + j4.00 ohm`. These values are hand calculations from the specified example values. `std::complex<double>` has O(1) time and two-double storage like this class, offers a thoroughly exercised standard implementation, and division-by-zero policy still needs to be handled at the application layer. Exact `==` on floating point is a limitation; a tolerance-based comparison is often more appropriate.

## Complexity summary

| Task / operation | Time | Additional space |
|---|---:|---:|
| Q1 create Book | O(1) | O(1) |
| Q2 copy n medicines | O(n) | O(n) |
| Q3 allocate rows x seats | O(rows*seats) | O(rows*seats + rows) pointers |
| Q4 Money arithmetic | O(1) | O(1) |
| Q5 Time increment / playlist access | O(1) | O(1) |
| Q6 concatenate lengths n and m | O(n+m) | O(n+m) |
| Q7 complex arithmetic | O(1) | O(1) |

## Appendix A - Handout Logger output prediction

Written as source-level prediction before execution. Logger construction prints `+name`; copying appends `c`; destruction prints `-name`.

```text
+A +B -B copyAc use -Ac +P -P end -A
```

Object trace: `a` is constructed first; `b` is constructed and destroyed at the end of its nested block. Passing `a` by value copies it as `Ac`; the parameter is destroyed after `use` returns. The dynamically allocated `P` is destroyed by `delete`. `a` is destroyed at the end of `main`.

## Pending evidence checklist

- Compile all seven programs with the exact compiler/version and warning flags; fix any diagnostics.
- Run each program and save terminal screenshots under `evidence/`.
- Run the intentional shallow-copy and correct deep-copy versions under AddressSanitizer; save logs.
- Capture `-Wreorder` and missing-default-constructor diagnostics.
- Measure requested copy, allocation, and increment/concatenation benchmarks, recording platform, compiler flags, and repeats.
- Commit progressively by task and push to the linked GitHub repository; confirm the URL shows the completed work.

