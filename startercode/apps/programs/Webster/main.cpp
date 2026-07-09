#include <iostream>
#include <string>

#include "Pair.h"
#include "List.h"
#include "Tree.h"
#include "Dictionary.h"

using namespace std;

int main()
{
    Dictionary<int, string> students;

    students.insert(1001, "Alice");
    students.insert(1002, "Bob");
    students.insert(1003, "Charlie");

    cout << "Dictionary Size: " << students.size() << endl;

    cout << "Student 1002: " << students.at(1002) << endl;

    students[1002] = "Robert";

    cout << "Updated Student 1002: " << students.at(1002) << endl;

    students[1004] = "David";

    cout << "After operator[] insertion:" << endl;
    cout << "Student 1004: " << students.at(1004) << endl << endl;

    cout << "Keys:" << endl;
    List<int> keyList = students.keys();
    keyList.print(); cout << endl;

    cout << "Values:" << endl;
    List<string> valueList = students.values();
    valueList.print(); cout << endl;

    students.erase(1001);

    cout << "After Erasing Key 1001:" << endl;
    cout << "Size: " << students.size() << endl;

    cout << "Keys:" << endl;
    students.keys().print(); cout << endl;

    //------------------------------------------------
    try
    {
        cout << students.at(9999) << endl;
    }
    catch (out_of_range& e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    cout << endl;

    //------------------------------------------------
    students.clear();

    cout << "Dictionary cleared." << endl;
    cout << "Is Empty? ";

    if (students.isEmpty())
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}