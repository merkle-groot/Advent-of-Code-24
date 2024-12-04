#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
#include <map>
using namespace std;

int regex_pattern_finder(string line, regex pattern)
{
    int count = 0;
    smatch match;

    // Forward search
    auto iterator = line.cbegin();
    while (regex_search(iterator, line.cend(), match, pattern))
    {
        count++;
        iterator = match.suffix().first;
    }

    // Backward search
    reverse(line.begin(), line.end());
    iterator = line.cbegin();
    while (regex_search(iterator, line.cend(), match, pattern))
    {
        count++;
        iterator = match.suffix().first;
    }

    return count;
}

int horizontal_search(vector<string> input, regex pattern)
{
    int count = 0;
    for (const string &line : input)
    {
        count += regex_pattern_finder(line, pattern);
    }
    return count;
}

int diagonal_search(vector<string> input, regex pattern)
{
    int count = 0;
    for (int i = 0; i < input[0].size(); ++i)
    {
        string line = "";
        int j = 0;
        int k = i;
        while (k < input[0].size() && j < input.size())
        {
            line.push_back(input[j][k]);
            k++;
            j++;
        }
        count += regex_pattern_finder(line, pattern);
    }

    for (int i = 1; i < input[0].size(); ++i)
    {
        string line = "";
        int j = i;
        int k = 0;
        while (k < input[0].size() && j < input.size())
        {
            line.push_back(input[j][k]);
            k++;
            j++;
        }
        count += regex_pattern_finder(line, pattern);
    }

    for (int i = 1; i < input[0].size(); ++i)
    {
        string line = "";
        int j = 0;
        int k = i;
        while (j < input.size() && k >= 0)
        {
            line.push_back(input[j][k]);
            j++;
            k--;
        }
        count += regex_pattern_finder(line, pattern);
    }

    for (int i = input.size() - 1; i > 0; --i)
    {
        string line = "";
        int j = input.size() - 1;
        int k = i;
        while (j >= 0 && k < input.size())
        {
            line.push_back(input[j][k]);
            j--;
            k++;
        }

        count += regex_pattern_finder(line, pattern);
    }

    return count;
}

int vertical_search(vector<string> input, regex pattern)
{
    int count = 0;
    for (int i = 0; i < input[0].size(); ++i)
    {
        string line = "";
        for (int j = 0; j < input.size(); ++j)
        {
            line.push_back(input[j][i]);
        }

        count += regex_pattern_finder(line, pattern);
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

    regex pattern("(XMAS)");

    cout << diagonal_search(input, pattern) + horizontal_search(input, pattern) + vertical_search(input, pattern) << endl;
    return 0;
}