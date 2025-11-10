# Boolean Expression Simplifier

A small C++ command-line tool that parses, evaluates, and simplifies Boolean logic expressions.

# 🔧 Features
- Parses expressions with &, |, ^, ~, !, ', and parentheses () [] {} using a recursive algorithm
- Generates full truth tables
- Simplifies expressions using a basic minterm combination algorithm
- Supports flags:
  - -h  — help
  - -t  — truth table only
  - -s  — simplified form only
  - -v  — include non-prime implicants
  - -d  — disable combination
  - -c  — cute cat
- Detects when simplification is impractical for 6+ variables
- Cute cat

# 🧮 Example
run:
./KarnaughCat "(A & B & ~C) | (A & ~B & C) | (~A & B & C) | (A & B & C)"

output:

A B C  result
_____________
0 0 0    0
1 0 0    0
0 1 0    0
1 1 0    1
0 0 1    0
1 0 1    1
0 1 1    1
1 1 1    1

Simplified (A & B & ~C) | (A & ~B & C) | (~A & B & C) | (A & B & C) (minimal SOP form):

A & B  |  A & C  |  B & C

Execution time: 0.000156041 seconds

# 🏗️ build
cd into the KarnaughCat directory and run make
this will compile using g++. Change in makefile if necessary

# 🏃 run
on windows execute:
KarnaughCat.exe followed by the desired logical expression in double brackets ""
on everything else execute:
./KarnaughCat   followed by the desired logical expression in double brackets ""


# 🚀 Performance
For up to 5 variables, simplification runs instantly.
Beyond that, the algorithm becomes exponentialy slower, so I prevented it from wasting our time.

# 🧠 Future Work
- Optimize combining logic
- Optimize truthtable logic
- POS format and further minimisation

-------------------------------------------------------------

*(Built entirely from scratch in C++ as a learning project.)*
