/*
 * Check sudoku matrix
 */
// https://code-with-me.jetbrains.com/T-MaGEo4Te-PLOnylrXdiA#p=CL&fp=0CDAA0C39202617B2EFD101BA64A86CD56240C07C08C227F2E27A42A222A1E68
#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;

const size_t SIZE = 9;

void print_sudoku(const unsigned sudoku[][SIZE]);
void sector_to_rows(const unsigned sudoku[][SIZE], unsigned temp[][SIZE]);

int basic_search(const unsigned v[], unsigned n_elements);

int check_rows(const unsigned sudoku[][SIZE]);
int check_cols(const unsigned sudoku[][SIZE]);
int check_regions(const unsigned sudoku[][SIZE]);
int check_sudoku(const unsigned sudoku[][SIZE]);
// Return:
//         1 if sudoku matrix complies to all Sudoku rules
//        -1 if a row violates the game rules
//        -2 if a column violates the game rules
//        -3 if a region violates the game rules
int search_key(const unsigned v[], unsigned n_elements, unsigned key);
void generate_sudoku(unsigned sudoku[][SIZE]);
// Create a Sudoku matrix by Lewis' Algorithm
// (https://en.wikipedia.org/wiki/Sudoku_solving_algorithms)

int main()
{
    // initialize a sudoku matrix
    unsigned sudoku[SIZE][SIZE] = {
            {1,2,3,4,5,6,7,8,9},
            {2,3,4,5,6,7,8,9,1},
            {3,4,5,6,7,8,9,1,2},
            {4,5,6,7,8,9,1,2,3},
            {5,6,7,8,9,1,2,3,4},
            {6,7,8,9,1,2,3,4,5},
            {7,8,9,1,2,3,4,5,6},
            {8,9,1,2,3,4,5,6,7},
            {9,1,2,3,4,5,6,7,8}
    };

    // print
    print_sudoku(sudoku);

    // check
    int res = check_sudoku(sudoku);
    cout << "check_sudoku returns: " <<  res << endl;

    // initialize another sudoku matrix
    unsigned sudoku2[SIZE][SIZE];
    generate_sudoku(sudoku2);

    // print
    print_sudoku(sudoku2);

    // check
    res = check_sudoku(sudoku2);
    cout << "check_sudoku returns: " <<  res << endl;

    return 0;
}

void print_sudoku(const unsigned sudoku[][SIZE]){
    cout << endl << "  ";

    for(size_t i = 0; i < SIZE; i++) {
        if(i % 3 == 0 && i != 0)
            cout << endl;
        for (size_t j = 0; j < SIZE; j++) {
            cout << sudoku[i][j] << std::setw(3);
            if( (j+1) % 3 == 0 && j != SIZE-1)
                cout << std::setw(4);
        }
        cout << endl;
    }
    cout << endl;
}
void sector_to_rows(const unsigned sudoku[][SIZE], unsigned temp[][SIZE]){
    /* tabellina valori che aggiungo per ribaltare " (i/3)*3 "
            {00,03,06},
            {30,33,36},
            {60,63,66}
    */
    for(size_t i=0; i<SIZE; i++)
        for(size_t j=0; j<SIZE; j++)
            temp[i][j] = sudoku[ (j/3)%3 + (i/3)*3 ][ j%3 + (i%3)*3 ];
        // Complicato ma funziona. Per pensarlo: inziare a notare che le righe i esime dei settori in colonna sono
        // invarianti in posizione. Il resto si provi con un esempio numerico e ci si fa una idea.
        // In particolare il % permette di avere la struttura ternaria che si ripete, senza dover usare altri indici.
        // La divisione è utile perchè, essendo int, non compare resto e quindi il risultato è 0,1,2.
}

int basic_search(const unsigned v[], unsigned n_elements)
{
    int occurence = 0;

    for(size_t num = 1; num <= n_elements; num++){ // per ogni numero 1:n_elements
        occurence = 0;
        if(search_key(v, n_elements, num) == 1) // scorro tutto il vettore (non ordinato!) e controllo se c'è il num
            occurence ++;
        if(occurence != 1)
            return 0;   // un numero o non compare o compare più di una volta
    }
    return 1; // tutto ok
}

int check_rows(const unsigned sudoku[][SIZE]){
    for(size_t i = 0; i < SIZE; i++){
        if(basic_search(sudoku[i], SIZE) == 0)
            return 0;
    }
    return 1;
}
int check_cols(const unsigned sudoku[][SIZE]){
    unsigned sudoku_t[SIZE][SIZE];

    for(size_t i=0; i<SIZE; i++) // trasposto del sudoku e riuso la funzione controlla righe
        for(size_t j=0; j<SIZE; j++)
            sudoku_t[i][j] = sudoku[j][i];

    return check_rows(sudoku_t);
}
int check_regions(const unsigned sudoku[][SIZE]){
    unsigned temp[SIZE][SIZE];

    for(size_t i=0; i<SIZE; i++)
        for(size_t j=0; j<SIZE; j++)
            temp[i][j] = sudoku[i][j];
    sector_to_rows(sudoku, temp);

    if(check_rows(temp) == 0) return 0;
    return 1;
}
int check_sudoku(const unsigned sudoku[][SIZE])
{
    if(check_rows(sudoku) == 0) return -1;
    else if(check_cols(sudoku) == 0) return -2;
    else if(check_regions(sudoku) == 0) return -3;
    else return 1;
}

int search_key(const unsigned v[], unsigned n_elements, unsigned key)
{
    for (size_t i=0; i<n_elements; ++i)
        if (v[i] == key)
            return 1;
    return 0;
}
void generate_sudoku(unsigned sudoku[][SIZE])
{
    int x = 0;
    for (size_t i=1; i<=3; ++i)
    {
        for (size_t j=1; j<=3; ++j)
        {
            for (size_t k=1; k<=SIZE; ++k)
            {
                sudoku[3*(i-1)+j-1][k-1] = (x % SIZE) + 1;
                x++;
            }
            x += 3;
        }
        x++;
    }
}

