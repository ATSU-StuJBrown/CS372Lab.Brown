#include <iostream>
#include <vector>
#include <chrono>
#include <random>

using namespace std;

int giveMeARandomInt(int start, int end)
{
    std::random_device r;
    std::default_random_engine eng1(r());
    std::uniform_int_distribution<int> uniGenerator(start, end);

    return uniGenerator(eng1);
}

// Selection Sort
void selectsort(vector<int>& a)
{
    int n = a.size();

    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[minIndex])
            {
                minIndex = j;
            }
        }

        swap(a[i], a[minIndex]);
    }
}

// Bubble Sort
void bubblesort(vector<int>& a)
{
    int n = a.size();

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
}

// Insertion Sort
void insertsort(vector<int>& a)
{
    int n = a.size();

    for (int i = 1; i < n; i++)
    {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && a[j] > key)
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

int partition(vector<int>& a, int low, int high)
{
    int pivot = a[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j] <= pivot)
        {
            i++;
            swap(a[i], a[j]);
        }
    }

    swap(a[i + 1], a[high]);
    return i + 1;
}

// Recursive QuickSort
void quicksort(vector<int>& a, int low, int high)
{
    if (low < high)
    {
        int p = partition(a, low, high);

        quicksort(a, low, p - 1);
        quicksort(a, p + 1, high);
    }
}

int main()
{
    vector<int> sizearr = {10, 50, 100, 500, 1000, 5000, 10000, 50000, 100000, 250000};

    for (int size : sizearr)
    {
        cout << "\n==============================\n";
        cout << "Array Size: " << size << endl;

        vector<int> original(size);

        for (int i = 0; i < size; i++)
        {
            original[i] = giveMeARandomInt(1, 1000000);
        }

        vector<int> data;

        // SELECT
        data = original;

        auto start = chrono::steady_clock::now();
        selectsort(data);
        auto end = chrono::steady_clock::now();

        chrono::duration<double> elapsed = end - start;

        cout << "Selection Sort | " << elapsed.count() << " seconds" << endl;

        // BUBBLE
        data = original;

        start = chrono::steady_clock::now();
        bubblesort(data);
        end = chrono::steady_clock::now();

        elapsed = end - start;

        cout << "   Bubble Sort | " << elapsed.count() << " seconds" << endl;

        // INSERT
        data = original;

        start = chrono::steady_clock::now();
        insertsort(data);
        end = chrono::steady_clock::now();

        elapsed = end - start;

        cout << "Insertion Sort | " << elapsed.count() << " seconds" << endl;

        // QUICK
        data = original;

        start = chrono::steady_clock::now();
        quicksort(data, 0, data.size() - 1);
        end = chrono::steady_clock::now();

        elapsed = end - start;

        cout << "    Quick Sort | " << elapsed.count() << " seconds" << endl;
    }

    return 0;
}