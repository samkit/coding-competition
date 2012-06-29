#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstring>
#include <tuple>
#include <set>
#include <unordered_map>

using namespace std;

typedef pair<unsigned long long, unsigned long long> Position;
typedef vector<Position> Positions;
typedef vector<Positions> WordPositions;
typedef tuple<unsigned long long, unsigned long long, unsigned long, bool> Minima;
typedef unordered_map<unsigned long long, unsigned long long> WordCounts;
typedef vector<unsigned long long> UsedIndexes;

bool debug = false;

void search_pattern(std::string const& line, std::string const& word, Positions& positions)
{
    char const* start = line.c_str();
    char const* end = start + line.length();
    char const* index = start;
    while ((index = strcasestr(index, word.c_str())))
    {
        if ((index == start || isspace(index[-1]))
            &&
            (index + word.length() >= end || isspace(index[word.length()])))
        {
            int startIndex = index - start;
            positions.push_back(make_pair(startIndex, startIndex + word.length()));
            index += word.length();
        }
        else
        {
            index += 1;
        }
    }
}

inline void get_smallest_para(std::string const& line, WordPositions& wordPositions, Minima& minima,
        unsigned long long minimum, unsigned long long maximum, WordCounts const& wordCounts,
        unsigned long long level, UsedIndexes& usedIndexes)
{
    if (level == wordPositions.size())
    {
        const unsigned long long wordCount = wordCounts.find(maximum)->second - wordCounts.find(minimum)->second + 1;
        if (get<0>(minima) > wordCount)
        {
            if (debug) cout << "set ---- " << minimum << " " << maximum << " " << get<0>(minima) << "->" << wordCount << "[" << line.substr(minimum, maximum - minimum - 1) << "]" << endl;
            get<0>(minima) = wordCount;
            get<1>(minima) = minimum;
            get<2>(minima) = maximum;
            get<3>(minima) = true;

            if (debug) cout << " [";
            for_each(usedIndexes.begin(), usedIndexes.end(), [] (unsigned long long i) { if (debug) cout << i << " "; });
            if (debug) cout << "]" << endl;
        }
        static int count = 0;
        if (debug) cout << ++count << endl;
        return;
    }

    bool createdMinima = false;
    for (unsigned long long index = usedIndexes[level]; index < wordPositions[level].size(); ++index)
    {
        Position const& position = wordPositions[level][index];

        if (debug) cout << "check1 " << get<3>(minima) << " " << position.first << " " << get<2>(minima) << " " << level << endl;
        if (!createdMinima && get<3>(minima) && get<2>(minima) < position.first)
        {
            return;
        }

        usedIndexes[level] = index;
        if (!createdMinima && get<3>(minima) && position.second < get<2>(minima))
        {
            if (debug) cout << "check2 " << get<3>(minima) << " " << position.second << " " << get<2>(minima) << " " << level << endl;
            continue;
        }

        if (!createdMinima && get<3>(minima) && get<1>(minima) <= position.first)
        {
            if (debug) cout << "skip " << get<1>(minima) << " < " << position.first << " " << level << endl;
            return;
        }
        if (debug) cout << "consider [" << index << "]@[" << level << "]" << endl;

        const unsigned long long localMinimum = std::min(minimum, position.first);
        const unsigned long long localMaximum = std::max(maximum, position.second + 1);

        // invalidate the minima
        if (get<3>(minima))
        {
            if (debug) cout << "=====" << position.first << " " << localMinimum << " " << level << endl;
        }
        get<3>(minima) = false;

        get_smallest_para(line, wordPositions, minima, localMinimum, localMaximum, wordCounts, level + 1, usedIndexes);
        createdMinima = get<1>(minima) == position.first;
        if (debug) cout << "check----" << get<1>(minima) << " " << position.first << " " << level << " " << createdMinima << endl;
        if (debug) cout << "check----" << get<1>(minima) << " " << position.first << " " << index << " " << level << " " << createdMinima << endl;
    }
}

int main(int argc, char* argv[])
{
    debug = argc >= 2;
    string line;
    getline(cin, line);

    string::iterator iter;
    while ((iter = find_if(line.begin(), line.end(), [] (char c) {
            return !(('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || isspace(c));
        })) != line.end())
    {
        line.erase(iter);
    }

    WordCounts wordCounts;
    wordCounts.max_load_factor(1);

    unsigned wordCount = 0;
    for (size_t i = 0; i < line.length(); ++i)
    {
        if (isspace(line[i]))
        {
            ++wordCount;
            wordCounts[i + 1] = wordCount;
        }
    }
    wordCounts[0] = 0;
    wordCounts[line.length() + 1] = wordCount;
//  cout << "[" << line << "]" << endl; for_each(wordCounts.begin(), wordCounts.end(), [](pair<const unsigned long long, unsigned long long> const& pi) { cout << pi.first << "->" << pi.second << endl; });

    unsigned long long K = 0;
    cin >> K;

    WordPositions wordPositions;
    while (K--)
    {
        std::string word;
        Positions positions;

        cin >> word;

        search_pattern(line, word, positions);
        if (positions.empty())
        {
            cout << "NO SUBSEGMENT FOUND" << endl;
            return 0;
        }

        wordPositions.push_back(std::move(positions));
    }

//  sort(wordPositions.begin(), wordPositions.end(), [](Positions const& lhs, Positions const& rhs) { return lhs.size() > rhs.size(); });

    Minima minima(-1, 0, 0, false);
    UsedIndexes usedIndexes(wordPositions.size(), 0);
    get_smallest_para(line, wordPositions, minima, -1, 0, wordCounts, 0, usedIndexes);

//  cout << "left [";
//  for_each(usedIndexes.begin(), usedIndexes.end(), [] (unsigned long long i) { cout << i << " "; });
//  cout << "]" << endl;

    char const* start = line.c_str() + get<1>(minima);
    line[get<2>(minima)] = 0;
    cout << start << endl;

    return 0;
}
