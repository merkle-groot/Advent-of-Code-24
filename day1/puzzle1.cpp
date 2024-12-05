#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

int similarity_score(vector<int> list1, vector<int> list2)
{
    map<int, int> freq;
    for (int i = 0; i < list2.size(); ++i)
    {
        freq[list2[i]] += 1;
    }

    int similarity_score = 0;

    for (int i = 0; i < list1.size(); ++i)
    {
        similarity_score += list1[i] * freq[list1[i]];
    }

    return similarity_score;
}

int find_diff(vector<int> list1, vector<int> list2)
{
    int diff = 0;
    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    for (int i = 0; i < list1.size(); ++i)
    {
        diff += abs(list1[i] - list2[i]);
    }

    return diff;
}

int main()
{
    ifstream input_file("./input1.txt");
    string line;
    vector<int> list1;
    vector<int> list2;

    if (!input_file)
    {
        cout << "error while loading the file" << endl;
        return 1;
    }

    while (getline(input_file, line))
    {
        istringstream string_stream(line);
        int num1, num2;
        string_stream >> num1 >> num2;
        list1.push_back(num1);
        list2.push_back(num2);
    }

    cout << "puzzle 1 result: " << find_diff(list1, list2) << endl;
    cout << "puzzle 2 result: " << similarity_score(list1, list2) << endl;

    return 0;
}