#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

bool is_x(const vector<string> input, int x, int y)
{
    int cross = 0;

    if ((input[x - 1][y - 1] == 'M' && input[x + 1][y + 1] == 'S') ||
        (input[x - 1][y - 1] == 'S' && input[x + 1][y + 1] == 'M'))
    {
        cross++;
    }

    if ((input[x - 1][y + 1] == 'M' && input[x + 1][y - 1] == 'S') ||
        (input[x - 1][y + 1] == 'S' && input[x + 1][y - 1] == 'M'))
    {
        cross++;
    }

    if (cross == 2)
    {
        // cout << "(" << x << "," << y << ") :" << count << endl;
        return true;
    }
    else
    {
        return false;
    }
}

int find_no_of_xmas(const vector<string> input, regex pattern)
{
    int count = 0;
    for (int i = 1; i < input.size(); ++i)
    {
        smatch match;
        auto iterator = input[i].cbegin() + 1;
        while (regex_search(iterator, input[i].cend() - 1, match, pattern))
        {
            auto position_in_line = distance(input[i].cbegin(), iterator) + match.position(0);
            // cout << "(" << i << "," << position_in_line << ")" << endl;
            count += is_x(input, i, position_in_line) ? 1 : 0;

            iterator = match.suffix().first;
        }
    }

    return count;
}

int main()
{
    ifstream input_file("./input.txt");
    string line;
    vector<string> input;

    if (!input_file)
    {
        cout << "error while loading the file" << endl;
        return 1;
    }

    while (getline(input_file, line))
    {
        int i = 0;
        string curr_line = "";

        for (char c : line)
        {
            curr_line.push_back(c);
        }

        input.push_back(curr_line);
    }

    regex pattern("(A)");
    cout << find_no_of_xmas(input, pattern) << endl;
    return 0;
}