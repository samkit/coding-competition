#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <set>

using namespace std;

struct comparator
{
    template <class T>
    bool operator() (T const& lhs, T const& rhs) const
    {
        return lhs.first < rhs.first && lhs.second < rhs.second;
    }
};

std::string print(int time)
{
    if (time == (24*60))
    {
        return "00 00";
    }

    ostringstream oss;
    oss << setw(2) << setfill('0') << (time / 60) << " " << setw(2) << setfill('0') << (time % 60);
    return oss.str();
}

void printPair(pair<int, int> pi) { cout << print(pi.first) << "->" << print(pi.second) << endl; }

int main()
{
    const int startOfDay = 0;
    const int endOfDay = 24 * 60;

    int M = 0;
    int K = 0;

    cin >> M >> K;

    typedef set<pair<int, int>, comparator> set_type;
    set_type slots;

    while (M--)
    {
        int startHours, startMinutes, endHours, endMinutes;
        cin >> startHours >> startMinutes >> endHours >> endMinutes;
        int startTime = startHours * 60 + startMinutes;
        int endTime = endHours * 60 + endMinutes;

        bool inserted = false;
        while (!inserted)
        {
            set_type::iterator iter = slots.lower_bound(make_pair(startTime, endTime));
            if (iter == slots.end())
            {
                slots.insert(make_pair(startTime, endTime));
                inserted = true;
            }
            else
            {
                if (startTime < iter->first && endTime < iter->first)
                {
                    slots.insert(make_pair(startTime, endTime));
                    inserted = true;
                }
                else
                {
                    startTime = min(startTime, iter->first);
                    endTime = max(endTime, iter->second);
                    slots.erase(iter);
                    inserted = slots.insert(make_pair(startTime, endTime)).second;
                }
            }
        }
    }

    pair<int, int> last(startOfDay, startOfDay);
    for (set_type::const_iterator iter = slots.begin(); iter != slots.end(); ++iter)
    {
        if (iter->first - last.second >= K)
        {
            cout << print(last.second) << " " << print(iter->first) << endl;
        }
        last = *iter;
    }
    if (endOfDay - last.second >= K)
    {
        cout << print(last.second) << " " << print(endOfDay) << endl;
    }
}
