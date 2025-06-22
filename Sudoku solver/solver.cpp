#include <iostream>
#include <cmath>
#include <string>
#include <chrono>
#include <fstream>
#include <sstream>
using namespace std;

#define SIZE 9
#define rowB 9 * 9 * 9
#define colB 9 * 9 * 4
struct node
{
public:
    struct node *left;
    struct node *right;
    struct node *up;
    struct node *down;
    struct node *head;
    int rowid;
    int colid;
    int nodecount;
    int val;
};

bool matrix[rowB][colB] = {{0}};
int getRight(int i) { return (i + 1) % SIZE; }
int getLeft(int i) { return (i - 1 < 0) ? SIZE - 1 : i - 1; }
int getUp(int i) { return (i - 1 < 0) ? SIZE : i - 1; }
int getDown(int i) { return (i + 1) % (SIZE + 1); }
bool is_solved = false;

struct node Head;
struct node *HeadNode = &Head;

struct node *orig_values[1000] = {nullptr};
struct node *solution[1000] = {nullptr};

bool find_all_solutions = false;
int solution_count = 0;

bool readPuzzleFromFile(const string& filename, int grid[SIZE][SIZE]) {
    ifstream infile(filename);
    if (!infile.is_open()) return false;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            infile >> grid[i][j];
    infile.close();
    return true;
}

void writeGridToFile(const string& filename, int grid[SIZE][SIZE]) {
    ofstream outfile(filename);
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0 && i != 0)
            outfile << "------+-------+------\n";
        for (int j = 0; j < SIZE; j++) {
            if (j % 3 == 0 && j != 0)
                outfile << "| ";
            outfile << grid[i][j] << " ";
        }
        outfile << endl;
    }
    outfile.close();
}

int lastSolvedGrid[SIZE][SIZE];

void mapsolutiontogrid(int grid[SIZE][SIZE])
{
    for(int i=0;solution[i]!=NULL;i++)
    {
        grid[solution[i]->rowid-1][solution[i]->colid-1] = solution[i]->val;
    }
    for(int i=0;orig_values[i]!=NULL;i++)
    {
        grid[orig_values[i]->rowid-1][orig_values[i]->colid-1] = orig_values[i]->val;
    }
    for(int i=0;i<SIZE;i++)
        for(int j=0;j<SIZE;j++)
            lastSolvedGrid[i][j] = grid[i][j];
}

void printgrid(int grid[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------\n";
        for (int j = 0; j < SIZE; j++)
        {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}
void coverColumn(node *col)
{
    col->left->right = col->right;
    col->right->left = col->left;
    for (node *node1 = col->down; node1 != col; node1 = node1->down)
    {
        for (node *temp = node1->right; temp != node1; temp = temp->right)
        {
            temp->down->up = temp->up;
            temp->up->down = temp->down;
            temp->head->nodecount--;
        }
    }
}

void uncoverColumn(node *col)
{
    for (node *node1 = col->up; node1 != col; node1 = node1->up)
    {
        for (node *temp = node1->left; temp != node1; temp = temp->left)
        {
            temp->head->nodecount++;
            temp->down->up = temp;
            temp->up->down = temp;
        }
    }
    col->left->right = col;
    col->right->left = col;
}

void search(int k, ostream& out)
{
    if(HeadNode->right == HeadNode)
    {
        int grid[SIZE][SIZE] = {{0}};
        mapsolutiontogrid(grid);
        solution_count++;
        out << "Solution " << solution_count << ":\n";
        for (int i = 0; i < SIZE; i++) {
            if (i % 3 == 0 && i != 0)
                out << "------+-------+------\n";
            for (int j = 0; j < SIZE; j++) {
                if (j % 3 == 0 && j != 0)
                    out << "| ";
                out << grid[i][j] << " ";
            }
            out << endl;
        }
        out << endl;
        is_solved = true;
        if (!find_all_solutions) return;
        return;
    }
    node *col = HeadNode->right;
    for (node *temp = col->right; temp != HeadNode; temp = temp->right)
    {
        if (temp->nodecount < col->nodecount)
            col = temp;
    }
    coverColumn(col);
    for(node *temp=col->down;temp!=col;temp=temp->down)
    {
        solution[k] = temp;
        for(node *node1 = temp->right;node1!=temp;node1=node1->right)
        {
            coverColumn(node1->head);
        }
        search(k+1, out);
        temp = solution[k];
        solution[k] = NULL;
        col = temp->head;
        for(node *node1 = temp->left;node1!=temp;node1=node1->left)
        {
            uncoverColumn(node1->head);
        }
    }
    uncoverColumn(col);
}

void create_constraints_matrix(bool matrix[rowB][colB])
{
    int j = 0, counter = 0;
    for (int i = 0; i < rowB; i++)
    {
        matrix[i][j] = 1;
        counter++;
        if (counter >= SIZE)
        {
            j++;
            counter = 0;
        }
    }

    int x = 0;
    counter = 1;
    for (j = SIZE * SIZE; j < 2 * SIZE * SIZE; j++)
    {
        for (int i = x; i < counter * SIZE * SIZE; i += SIZE)
            matrix[i][j] = 1;

        if ((j + 1) % SIZE == 0)
        {
            x = counter * SIZE * SIZE;
            counter++;
        }
        else
            x++;
    }

    j = 2 * SIZE * SIZE;
    for (int i = 0; i < rowB; i++)
    {
        matrix[i][j] = 1;
        j++;
        if (j >= 3 * SIZE * SIZE)
            j = 2 * SIZE * SIZE;
    }

    x = 0;
    for (j = 3 * SIZE * SIZE; j < colB; j++)
    {

        for (int l = 0; l < sqrt(SIZE); l++)
        {
            for (int k = 0; k < sqrt(SIZE); k++)
                matrix[x + l * SIZE + k * SIZE * SIZE][j] = 1;
        }

        int temp = j + 1 - 3 * SIZE * SIZE;

        if (temp % (int)(sqrt(SIZE) * SIZE) == 0)
            x += (sqrt(SIZE) - 1) * SIZE * SIZE + (sqrt(SIZE) - 1) * SIZE + 1;
        else if (temp % SIZE == 0)
            x += SIZE * (sqrt(SIZE) - 1) + 1;
        else
            x++;
    }
}
void create_toroidal_matrix(bool matrix[rowB][colB])
{
    node *header = new node;
    header->left = header;
    header->right = header;
    header->down = header;
    header->up = header;
    header->nodecount = -1;
    header->head = header;
    node *temp = header;

    for (int i = 0; i < colB; i++)
    {
        node *newnode = new node;
        newnode->left = temp;
        newnode->right = header;
        newnode->down = newnode;
        newnode->up = newnode;
        newnode->head = newnode;
        newnode->nodecount = 0;
        temp->right = newnode;
        temp = newnode;
    }

    int id[3] = {0, 1, 1};
    for (int i = 0; i < rowB; i++)
    {
        node *top = header->right;
        node *prev = NULL;

        if (i != 0 && i % (SIZE*SIZE) == 0)
        {
            id[0] -= SIZE - 1;
            id[1]++;
            id[2] -= SIZE - 1;
        }
        else if (i != 0 && i % (SIZE) == 0)
        {
            id[0] -= SIZE - 1;
            id[2]++;
        }
        else
            id[0]++;

        for (int j = 0; j < colB; j++, top = top->right)
        {
            if (matrix[i][j])
            {
                node *newnode = new node;
                newnode->val = id[0];
                newnode->rowid = id[1];
                newnode->colid = id[2];
                if (prev == NULL)
                {
                    prev = newnode;
                    prev->right = newnode;
                }
                newnode->left = prev;
                newnode->right = prev->right;
                newnode->right->left = newnode;
                prev->right = newnode;
                newnode->head = top;
                newnode->down = top;
                newnode->up = top->up;
                top->up->down = newnode;
                top->nodecount++;
                top->up = newnode;
                if (top->down == top)
                    top->down = newnode;
                prev = newnode;
            }
        }
    }
    HeadNode = header;
}
void TransformListToCurrentGrid(int Puzzle[][SIZE])
{
    int index = 0;
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            if (Puzzle[i][j] > 0)
            {
                node *Col = NULL;
                node *temp = NULL;
                for (Col = HeadNode->right; Col != HeadNode; Col = Col->right)
                {
                    for (temp = Col->down; temp != Col; temp = temp->down)
                        if (temp->val == Puzzle[i][j] && (temp->rowid - 1) == i && (temp->colid - 1) == j)
                            goto ExitLoops;
                }
            ExitLoops:
                coverColumn(Col);
                orig_values[index] = temp;
                index++;
                for (node *node1 = temp->right; node1 != temp; node1 = node1->right)
                {
                    coverColumn(node1->head);
                }
            }
}

void SolveSudoku(int puzzle[][SIZE], ostream& out)
{
    for (int i = 0; i < 1000; ++i) {
        solution[i] = NULL;
        orig_values[i] = NULL;
    }
    is_solved = false;
    solution_count = 0;

    create_constraints_matrix(matrix);
    create_toroidal_matrix(matrix);
    TransformListToCurrentGrid(puzzle);
    search(0, out);
    if (!is_solved)
        out << "No Solution Exists" << endl;
}

bool isValidInput(int grid[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (grid[i][j] < 0 || grid[i][j] > 9)
                return false;
    return true;
}

bool readNextPuzzle(istream& in, int grid[SIZE][SIZE]) {
    string line;
    int row = 0;
    while (row < SIZE && getline(in, line)) {
        if (line.empty()) continue;
        istringstream iss(line);
        for (int col = 0; col < SIZE; ++col) {
            if (!(iss >> grid[row][col])) return false;
        }
        ++row;
    }
    return row == SIZE;
}

int main(int argc, char* argv[])
{
    int Puzzle[9][9];
    bool inputFromFile = false;
    string inputFile, outputFile;
    if (argc >= 2) {
        inputFromFile = true;
        inputFile = argv[1];
    }
    if (argc >= 3) {
        outputFile = argv[2];
    }
    bool valid = false;
    if (inputFromFile) {
        ifstream infile(inputFile);
        if (!infile.is_open()) {
            cerr << "Failed to read puzzle from file: " << inputFile << endl;
            return 1;
        }
        ofstream outfile;
        if (!outputFile.empty()) {
            outfile.open(outputFile);
            if (!outfile.is_open()) {
                cerr << "Failed to open output file: " << outputFile << endl;
                return 1;
            }
        }
        int puzzleCount = 0;
        find_all_solutions = false;
        while (readNextPuzzle(infile, Puzzle)) {
            ++puzzleCount;
            if (!isValidInput(Puzzle)) {
                cout << "Puzzle " << puzzleCount << ": Invalid input. Skipping.\n";
                if (outfile.is_open()) outfile << "Puzzle " << puzzleCount << ": Invalid input. Skipping.\n";
                continue;
            }
            auto start = chrono::high_resolution_clock::now();
            cout << "Puzzle " << puzzleCount << ":\n";
            if (outfile.is_open()) outfile << "Puzzle " << puzzleCount << ":\n";
            SolveSudoku(Puzzle, outfile.is_open() ? outfile : cout);
            auto end = chrono::high_resolution_clock::now();
            chrono::duration<double> diff = end - start;
            if (is_solved) {
                cout << solution_count << (solution_count == 1 ? " solution found\n" : " solutions found\n");
                if (outfile.is_open()) outfile << solution_count << (solution_count == 1 ? " solution found\n" : " solutions found\n");
            } else {
                cout << "No Solution Exists\n";
                if (outfile.is_open()) outfile << "No Solution Exists\n";
            }
            cout << "Solved in " << diff.count() << " seconds.\n\n";
            if (outfile.is_open()) outfile << "Solved in " << diff.count() << " seconds.\n\n";
        }
        if (puzzleCount == 0) {
            cout << "No puzzles found in input file." << endl;
            if (outfile.is_open()) outfile << "No puzzles found in input file." << endl;
        }
        if (outfile.is_open()) outfile.close();
    } else {
        cout << "==============================\n";
        cout << "Sudoku Solver - Interactive Mode\n";
        cout << "==============================\n";
        cout << "Enter the Sudoku puzzle (0 for empty cells):\n";
        cout << "(Enter 9 lines, each with 9 numbers separated by spaces)\n";
        for(int i=0;i<9;i++) {
            cout << "Row " << (i+1) << ": ";
            for(int j=0;j<9;j++)
                cin >> Puzzle[i][j];
        }
        valid = isValidInput(Puzzle);
        if (!valid) {
            cerr << "Invalid input. Please enter numbers between 0 and 9." << endl;
            return 1;
        }
        char allsol;
        cout << "\nFind all possible solutions? (y/n): ";
        cin >> allsol;
        find_all_solutions = (allsol == 'y' || allsol == 'Y');
        cout << "\nSolving the puzzle...\n";
        auto start = chrono::high_resolution_clock::now();
        SolveSudoku(Puzzle, cout);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = end - start;
        cout << "\n==============================\n";
        if (is_solved) {
            cout << solution_count << (solution_count == 1 ? " solution found!\n" : " solutions found!\n");
        } else {
            cout << "No Solution Exists for the given puzzle.\n";
        }
        cout << "Solved in " << diff.count() << " seconds.\n";
        cout << "==============================\n";
    }
    return 0;
}
