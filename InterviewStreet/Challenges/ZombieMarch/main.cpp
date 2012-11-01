#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <array>
#include <list>
#include <map>

using namespace std;

typedef unsigned long long int data_type;
typedef double floating_type;

int main()
{
    data_type T;
    data_type N, M, K;

    vector<vector<data_type>> grid;
    vector<floating_type> probabilities;
    vector<floating_type> population;

    cin >> T;
    while (T--)
    {
        cin >> N >> M >> K;

        for_each(grid.begin(), grid.end(), [] (vector<data_type>& s) { s.clear(); });
        grid.resize(N);
        probabilities.resize(N);
        population.resize(N);

        while (M--)
        {
            data_type start, end;
            cin >> start >> end;
            if (!binary_search(grid[start].begin(), grid[start].end(), end))
            {
                auto insertPosition = upper_bound(grid[start].begin(), grid[start].end(), end);
                grid[start].insert(insertPosition, end);
            }
            if (!binary_search(grid[end].begin(), grid[end].end(), start))
            {
                auto insertPosition = upper_bound(grid[end].begin(), grid[end].end(), start);
                grid[end].insert(insertPosition, start);
            }
        }

        for (data_type i = 0; i < N; ++i)
        {
            cin >> population[i];
        }

        for (data_type step = 0, noUpdateCount = 0; step < K && noUpdateCount < 100; ++step)
        {
            for (size_t node = 0; node < N; ++node)
            {
                probabilities[node] = population[node] / grid[node].size();
            }

            bool updated = false;
            for (size_t node = 0; node < N; ++node)
            {

                floating_type update = accumulate(grid[node].begin(), grid[node].end(),
                            0.0,
                            [&probabilities] (floating_type const& lhs, floating_type const& rhs) {
                                return lhs + probabilities[rhs];
                            }
                );
                updated = updated || (abs(population[node] - update) > 1E-6);
                population[node] = update;
            }
            noUpdateCount += updated ? 0 : 1;
        }

        typedef map<floating_type, size_t> topper_map_type;
        topper_map_type topper;
        for (auto const& count : population)
        {
            ++topper[count];
            if (topper.size() > 5)
            {
                topper.erase(topper.rend().base());
            }
        }

        size_t printable = 0;
        for (auto it = topper.rbegin(); it != topper.rend(); ++it)
        {
            for (size_t z = 0; printable < 5 && z < it->second; ++z)
            {
                cout << (printable ? " " : "") << nearbyint(it->first);
                ++printable;
            }
        }
        cout << endl;
    }
}
