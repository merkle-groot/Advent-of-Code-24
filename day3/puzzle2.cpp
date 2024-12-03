#include <regex>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int parse_number(const string &str)
{
    return stoi(str);
}

int line_sum(string &line, int &status)
{
    int line_sum = 0;
    std::regex instruction_pattern("(do\\(\\))|(don't\\(\\))|(mul\\(([0-9]+),([0-9]+)\\))");

    auto iter = sregex_iterator(line.begin(), line.end(), instruction_pattern);
    auto end = sregex_iterator();

    for (sregex_iterator i = iter; i != end; ++i)
    {
        smatch match = *i;

        if (match[1].matched)
        {
            status = 1;
        }
        else if (match[2].matched)
        {
            status = 0;
        }
        else if (match[3].matched)
        {
            if (status)
            {
                line_sum += parse_number(match[4]) * parse_number(match[5]);
            }
        }
    }

    return line_sum;
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

    int i = 0;
    int sum = 0;
    int status = 1;

    while (getline(input_file, line))
    {
        sum += line_sum(line, status);
    }

    cout << sum << endl;
}