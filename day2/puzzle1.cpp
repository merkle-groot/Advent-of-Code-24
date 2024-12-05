#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

int safe_count(const vector<vector<int>> &input)
{
    int safe_count = 0;

    for (const auto &levels : input)
    {
        int direction = levels[0] < levels[1] ? 1 : 0;
        int is_safe = 1;
        for (int j = 1; j < levels.size(); ++j)
        {
            int diff = levels[j] - levels[j - 1];

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

        pair<int, int> direction_pair(0, 0);

        for (int i = 1; i < levels.size(); ++i)
        {
            if (levels[i] > levels[i - 1])
            {
                direction_pair.first += 1;
            }
            else
            {
                direction_pair.second += 1;
            }
        }

        int direction = direction_pair.first > direction_pair.second ? 1 : 0;
        int status = 0;
        int unsafe_count = 0;
        // 0 - no change
        // 1 - error related to >1 and <3
        // 2 - error related to diff
        for (int i = 1; i < levels.size(); ++i)
        {
            int diff;
            if (status == 2)
            {
                diff = levels[i] - levels[i - 2];

                if (abs(diff) > 3)
                {
                    diff = levels[i] - levels[i - 1];

                    if (abs(diff) > 3)
                    {
                        unsafe_count += 1;
                        break;
                    }
                }
            }
            else if (status == 1)
            {
                diff = levels[i] - levels[i - 2];
            }
            else
            {
                diff = levels[i] - levels[i - 1];
            }

            if ((direction == 1 && diff < 0) || (direction == 0 && diff > 0))
            {
                // cout << "reaches here 2" << endl;
                status = 2;
                unsafe_count += 1;

                if (unsafe_count > 1)
                {
                    break;
                }

                continue;
            }

            if (abs(diff) > 3 || diff == 0)
            {
                // cout << "reaches here 1" << endl;
                status = 1;
                unsafe_count += 1;

                if (unsafe_count > 1)
                {
                    break;
                }

                continue;
            }
        }

        if (unsafe_count < 2)
        {
            safe_count += 1;
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