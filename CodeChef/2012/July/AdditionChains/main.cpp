#include <iostream>
#include <cstdlib>
#include <stack>
#include <tr1/unordered_map>

using namespace std;
using namespace tr1;

size_t get_least_power_of_2(size_t number)
{
    size_t iter = 1 << (sizeof(size_t) * 8 - 1);
    while (!(iter & number)) iter >>= 1;
    return iter;
}

void print_chain(size_t number, size_t end)
{
    stack<pair<size_t, size_t> > indexes;
    unordered_map<size_t, int> numberToIndex;

    while (number > end)
    {
        size_t first = get_least_power_of_2(number);
        size_t second = number - first;

        if (first != number)
        {
            numberToIndex[number] = indexes.size();
            indexes.push(make_pair(first, second));
        }
        while (first > second)
        {
            numberToIndex[first] = indexes.size();
            first /= 2;
            if (first)
            {
                indexes.push(make_pair(first, first));
            }
        }
        number = second;
    }

    size_t count = indexes.size();
    cout << count << endl;
    while (!indexes.empty())
    {
        pair<size_t, size_t> p = indexes.top();
        cout << count - numberToIndex[p.first] << " " << count - numberToIndex[p.second] << endl;
        indexes.pop();
    }
}

int main(int argc, char* argv[])
{
    size_t N = atoll(argv[1]);
    print_chain(N, 0);
    return 0;
}
