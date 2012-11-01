#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

typedef unsigned long long int data_type;
typedef double floating_type;

int main()
{
    data_type T;
    data_type N, M, K;

    cin >> T;

    while (T--)
    {
        cin >> N >> M >> K;

        unordered_map<data_type, unordered_set<data_type>> grid;
        while (M--)
        {
            data_type start, end;
            cin >> start >> end;
            grid[start].insert(end);
            grid[end].insert(start);
        }

        vector<floating_type> population;
        population.resize(N);
        for (data_type i = 0; i < N; ++i)
        {
            cin >> population[i];
        }

        for (data_type step = 0; step < K; ++step)
        {
            unordered_map<data_type, floating_type> probabilities;
            for (auto const& nodeNeighbour : grid)
            {
                probabilities[nodeNeighbour.first] = population[nodeNeighbour.first] / nodeNeighbour.second.size();
            }

            for (size_t node = 0; node < population.size(); ++node)
            {

                population[node] = accumulate(grid[node].begin(), grid[node].end(),
                            0.0,
                            [&probabilities] (floating_type const& lhs, floating_type const& rhs) {
                                return lhs + probabilities[rhs];
                            }
                );
            }
        }

        std::sort(population.begin(), population.end(), [] (floating_type const& lhs, floating_type const& rhs) {
            return lhs > rhs;
        });

        size_t printable = std::min(size_t(5), population.size());
        for (size_t node = 0; node < printable; ++node)
        {
            cout << (node ? " " : "") << nearbyint(population[node]);
        }
        cout << endl;
    }
}
