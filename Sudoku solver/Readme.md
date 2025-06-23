# 🧩 Sudoku Solver (C++ - Dancing Links)

![Algorithm X Visualization](https://upload.wikimedia.org/wikipedia/commons/thumb/e/e0/Sudoku_Puzzle_by_L2G-20050714_standardized_layout.svg/250px-Sudoku_Puzzle_by_L2G-20050714_standardized_layout.svg.png)

A high-performance Sudoku solver implementing Donald Knuth's Algorithm X (Dancing Links) in C++. This implementation efficiently solves even the most challenging 9×9 Sudoku puzzles from your input files with millisecond-level performance.

## 🚀 Key Features

- ⚡ **Dancing Links Implementation** - Optimized Algorithm X for exact cover problems
- 🔍 **Complete Solution Space** - Finds all possible solutions when they exist
- 📊 **Professional Grid Formatting** - Human-readable output with box borders
- ⏱️ **Precision Timing** - Microsecond-accurate performance measurement
- 📂 **Batch Processing** - Solves multiple puzzles from a single input file
- ✔️ **Rigorous Validation** - Ensures only valid Sudoku puzzles are processed

## 🛠️ Compilation & Usage

### Compilation Command
```
g++ -O2 -std=c++11 -o sudokusolver main.cpp
```
Execution Modes

### Run (Interactive Input)

```
./sudokusolver
```
Prompts for puzzle entry row-by-row (0 for empty cells)

### File Input Mode (Console Output)

```
./sudokusolver input.txt
```

### File I/O Mode (File Output):

```
./sudokusolver input.txt output.txt
```
All solutions for each puzzle will be written to `output.txt`.

### File Format Specifications
Input File Format (input.txt)
Exactly 9 lines per puzzle, space-separated numbers (0-9), with puzzles separated by blank lines:

input.txttext
0 2 0 0 0 5 0 8 0
3 0 0 0 7 0 1 0 0
7 9 0 0 0 0 0 0 0
0 0 0 0 3 6 0 0 4
0 4 0 9 8 0 0 0 0
2 0 0 0 0 0 0 0 1
0 0 0 0 0 8 3 5 0
6 5 0 0 0 2 0 0 0
0 0 0 5 0 0 2 1 0

0 0 8 0 1 0 0 0 9
6 0 1 0 9 0 3 2 0
0 4 0 0 3 7 0 0 5
0 3 5 0 0 8 2 0 0
0 0 2 6 5 0 8 0 0
0 0 4 0 0 1 7 5 0
5 0 0 3 4 0 0 8 0
0 9 7 0 8 0 5 0 6
1 0 0 0 6 0 9 0 0

0 0 0 2 6 0 7 0 1
6 8 0 0 7 0 0 9 0
1 9 0 0 0 4 5 0 0
8 2 0 1 0 0 0 4 0
0 0 4 6 0 2 9 0 0
0 5 0 0 0 3 0 2 8
0 0 9 3 0 0 0 7 4
0 4 0 0 5 0 0 3 6
7 0 3 0 1 8 0 0 0

Output File Format (output.txt)
Detailed solution report with timing:

text
Puzzle 1:
Solution 1:
4 2 6 | 1 9 5 | 7 8 3 
3 8 5 | 6 7 4 | 1 2 9 
7 9 1 | 8 2 3 | 4 6 5 
------+-------+------
1 7 8 | 2 3 6 | 5 9 4 
5 4 3 | 9 8 1 | 6 7 2 
2 6 9 | 4 5 7 | 8 3 1 
------+-------+------
9 1 2 | 7 4 8 | 3 5 6 
6 5 7 | 3 1 2 | 9 4 8 
8 3 4 | 5 6 9 | 2 1 7 

1 solution found
Solved in 0.004105 seconds.

Puzzle 2:
Solution 1:
3 5 8 | 2 1 6 | 4 7 9 
6 7 1 | 5 9 4 | 3 2 8 
2 4 9 | 8 3 7 | 6 1 5 
------+-------+------
9 3 5 | 4 7 8 | 2 6 1 
7 1 2 | 6 5 3 | 8 9 4 
8 6 4 | 9 2 1 | 7 5 3 
------+-------+------
5 2 6 | 3 4 9 | 1 8 7 
4 9 7 | 1 8 2 | 5 3 6 
1 8 3 | 7 6 5 | 9 4 2 

1 solution found
Solved in 0 seconds.

Puzzle 3:
Solution 1:
4 3 5 | 2 6 9 | 7 8 1 
6 8 2 | 5 7 1 | 4 9 3 
1 9 7 | 8 3 4 | 5 6 2 
------+-------+------
8 2 6 | 1 9 5 | 3 4 7 
3 7 4 | 6 8 2 | 9 1 5 
9 5 1 | 7 4 3 | 6 2 8 
------+-------+------
5 1 9 | 3 2 6 | 8 7 4 
2 4 8 | 9 5 7 | 1 3 6 
7 6 3 | 4 1 8 | 2 5 9 

1 solution found
Solved in 0.005072 seconds.


Dancing Links:

Toroidal doubly-linked list structure

O(1) column covering/uncovering operations

Backtracking:

Recursive depth-first search

Minimum-remaining-values heuristic

## 📊 Performance Metrics
Puzzle Type	Avg. Solve Time	Solutions Found
Easy	0.0012s	1
Medium	0.0035s	1
Hard	0.0089s	1
Multi-Sol	0.0217s	2+

## Project Structure
- `solvercpp` — Main source code
- `Readme.md` — This  file
- `input.txt` — Example input file

## Author
- saikiran9346
- [Your GitHub Profile](https://github.com/saikiran9346)
