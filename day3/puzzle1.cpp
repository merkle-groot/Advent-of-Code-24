#include <regex>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int parse_number(const string &str)
{
    return stoi(str);
}

int line_sum(string &line)
{
    int line_sum = 0;
    regex mul_pattern(R"(mul\((\d+),(\d+)\))");
    string::const_iterator iterator(line.cbegin());
    smatch match;

    while (regex_search(iterator, line.cend(), match, mul_pattern))
    {
        int num1 = parse_number(match[1]);
        int num2 = parse_number(match[2]);
        line_sum += num1 * num2;

        iterator = match.suffix().first;
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

    while (getline(input_file, line))
    {
        sum += line_sum(line);
    }

    cout << sum << endl;
}