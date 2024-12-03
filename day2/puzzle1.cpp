#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

int safe_count(vector<vector<int>> input)
{
    int safe_count = 0;

    for (int i = 0; i < input.size(); ++i)
    {
        int direction = input[i][0] < input[i][1] ? 1 : 0;
        int is_safe = 1;
        for (int j = 1; j < input[i].size(); ++j)
        {
            int diff = input[i][j] - input[i][j - 1];

            if (abs(diff) > 3 || diff == 0 || !direction && diff > 0 || direction && diff < 0)
            {
                is_safe = 0;
                break;
            }
        }

        if (is_safe)
        {
            safe_count += 1;
        }
    }

    return safe_count;
}

bool is_safe(const vector<int> &levels)
{
    int direction = levels[1] > levels[0] ? 1 : 0;

    for (size_t i = 1; i < levels.size(); ++i)
    {
        int diff = levels[i] - levels[i - 1];

        if (abs(diff) > 3 || diff == 0)
        {
            return false;
        }

        if ((direction == 1 && diff < 0) || (direction == 0 && diff > 0))
        {
            return false;
        }
    }

    return true;
}

int safe_count_w_dampner(const vector<vector<int>> &input)
{
    int safe_count = 0;

    for (const auto &levels : input)
    {
        if (is_safe(levels))
        {
            ++safe_count;
            continue;
        }

        for (int i = 0; i < levels.size(); ++i)
        {
            vector<int> new_levels = levels;
            new_levels.erase(new_levels.begin() + i);

            if (is_safe(new_levels))
            {
                ++safe_count;
                break;
            }
        }
    }

    return safe_count;
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

    while (getline(input_file, line))
    {
        istringstream string_stream(line);
        vector<int> entry;
        int num;

        while (string_stream >> num)
        {
            entry.push_back(num);
        }

        if (!entry.empty())
        {
            input.push_back(entry);
        }
    }
    // cout << "puzzle 1 result: " << safe_count(input) << endl;
    cout << "puzzle 1 result: " << safe_count_w_dampner(input) << endl;

    return 0;
}