using namespace std;
#include <iostream>
#include <chrono>
using namespace std::chrono;

void moveDisks(int, int, int, int);
void printIt(int , int , int );

int main()
{
    const int FROMPEG = 1;
    const int TOPEG = 3;
    const int TEMPPEG = 2;
    const int NUMDISKS = 3;

    for (auto numdisks: {5,10,15,20,25,30,35})
    {

        cout << "Numdisks: " << numdisks << endl;

        auto start = high_resolution_clock::now();
        moveDisks(numdisks, FROMPEG, TOPEG, TEMPPEG);
        auto end = high_resolution_clock::now();

        duration<double> elapsed = end - start;

        cout << "Moved " << numdisks << " pegs" << " from peg " << FROMPEG << " to peg " << TOPEG << endl;
        cout << "Elapsed time: " << elapsed.count() << " seconds" << endl;
    }
}

void moveDisks(int num, int fromPeg, int toPeg, int tempPeg)
{
    if (num > 0)
    {
        moveDisks(num -1, fromPeg, tempPeg, toPeg);
        printIt(num, fromPeg, toPeg);
        moveDisks(num-1, tempPeg, toPeg, fromPeg);
    }
}

void printIt(int disk, int fromPeg, int toPeg)
{
    // Do nothing for timing test...
}