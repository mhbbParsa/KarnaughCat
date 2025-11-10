# 🐱 KarnaughCat — Boolean Expression Simplifier

[![Language](https://img.shields.io/badge/language-C++-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Build](https://img.shields.io/badge/build-Makefile-brightgreen.svg)](https://www.gnu.org/software/make/)
[![Platform](https://img.shields.io/badge/platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey.svg)](#)
[![License](https://img.shields.io/badge/license-MIT-yellow.svg)](#)
[![Status](https://img.shields.io/badge/status-Experimental-orange.svg)](#)

A small C++ command-line tool that parses, evaluates, and simplifies Boolean logic expressions.
```bash
#          _                        
#          \`*-.                    
#           )  _`-.                 
#          .  : `. .                
#          : _   '  \               
#          ; *` _.   `*-._          
#          `-.-'          `-.       
#            ;       `       `.     
#            :.       .        \    
#            . \  .   :   .-'   .   
#            '  `+.;  ;  '      :   
#            :  '  |    ;       ;-. 
#            ; '   : :`-:     _.`* ;
#   [bug] .*' /  .*' ; .*`- +'  `*' 
#         `*-*   `*-*  `*-*'
```
      
## 🔧 Features
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
- Cute ASKII cat

## 🧮 Example
run:
```bash
./KarnaughCat "(A & B & ~C) | (A & ~B & C) | (~A & B & C) | (A & B & C)"
```

output:
```bash

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

```

## 🏗️ build
```bash
cd KarnaughCat
make
```
This will compile using g++. Change in makefile if necessary

## 🏃 run
windows:
```bash
KarnaughCat.exe "<expression>"
```
 
Linux/MacOS:
```bash
./KarnaughCat "<expression>"
```
Replace <expression> with your Boolean expression in double quotes.


## 🚀 Performance
- For up to 5 variables, simplification runs instantly.
- Beyond that, the algorithm becomes exponentialy slower, so I prevented it from wasting our time.

## 🧠 Future Work
- Optimize combining logic
- Optimize truthtable logic
- POS format and further minimisation

-------------------------------------------------------------

*(Built entirely from scratch in C++ as a learning project.)*
