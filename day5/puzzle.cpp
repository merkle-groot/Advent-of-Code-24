#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

enum Mode
{
    smaller,
    larger
};

vector<int> split(string line, char delimiter)
{
    istringstream string_stream(line);
    vector<int> numbers;
    string current_number;
    while (getline(string_stream, current_number, delimiter))
    {
        numbers.push_back(stoi(current_number));
        current_number = "";
    }

    return numbers;
}

pair<int, int> check_if_valid(map<int, map<int, Mode>> rules, vector<vector<int>> lists)
{
    pair<int, int> sum(0, 0);
    for (vector<int> list : lists)
    {
        vector<int> actual_ordering(list.size());

        for (int i = 0; i < list.size(); ++i)
        {
            int less_than = 0;
            int more_than = 0;
            for (int j = 0; j < list.size(); ++j)
            {
                if (i != j)
                {
                    if (rules[list[i]][list[j]] == smaller)
                    {
                        more_than++;
                    }
                    else
                    {
                        less_than++;
                    }
                }
            }

            actual_ordering[less_than] = list[i];
        }

        bool matches = true;
        for (int i = 0; i < list.size(); ++i)
        {
            // cout << actual_ordering[i] << " " << list[i] << endl;
            if (list[i] != actual_ordering[i])
            {
                matches = false;
            }
        }

        if (matches && !list.empty())
        {
            int mid = list.size() / 2;
            sum.first += list[mid];
        }
        else if (!actual_ordering.empty())
        {
            int mid = actual_ordering.size() / 2;
            sum.second += actual_ordering[mid];
        }
    }

    return sum;
}

int main()
{
    ifstream input_file("./input.txt");
    string line;
    vector<vector<int>> input;

    if (!input_file)
    {
        cout << "error while loading the file" << endl;
        return 1;
    }

    bool array_mode = false;
    map<int, map<int, Mode>> rules;
    vector<vector<int>> lists;
    while (getline(input_file, line))
    {
        if (line.empty())
        {
            array_mode = true;
        }

        if (!array_mode)
        {
            vector<int> rules_array = split(line, '|');

            rules[rules_array[0]][rules_array[1]] = smaller;
            rules[rules_array[1]][rules_array[0]] = larger;
        }
        else
        {
            vector<int> entry = split(line, ',');
            lists.push_back(entry);
        }
    }

    pair<int, int> sum = check_if_valid(rules, lists);
    cout << "Correct ordering sum: " << sum.first << endl;
    cout << "Incorrect ordering sum: " << sum.second << endl;
}