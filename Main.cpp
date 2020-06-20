
#include <iostream>
#include <algorithm>

#include "Tree.h";
#include "Main.h";

using namespace std;

double CalculateMedian(vector<Base_item> baseItems)
{
    vector<int> completed_vector;

    for (Base_item item : baseItems)
    {
        if (item.completed != NULL && item.completed != -1) 
        {
            completed_vector.push_back(item.completed);
        }
    }

    sort(completed_vector.begin(), completed_vector.end());

    int size = completed_vector.size();
    int mid = size / 2;
    double median = 0;

    if (size % 2 == 0)
    {
        if (mid - 1 >= 0)
            median = (static_cast<double>(completed_vector[mid]) + static_cast<double>(completed_vector[mid - 1])) / 2;
    }
    else
    {
        median = (double)completed_vector[mid];
    }

    return median;
}

int main()
{
    Tree tree;

    cout << "\nMedian of Completed property from items is : " << CalculateMedian(base_items_vector) << endl;
    cout << endl;

    tree.MakeTreeFromItemsVector(base_items_vector);
    tree.PrintAllNodesToConsole();
    tree.RecalculateCompletedProperty();
    tree.CreateAndWriteToCsvFile();


}


