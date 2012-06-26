#include <iostream>
#include <algorithm>
#include <sstream>
#include <deque>
#include <cstring>
#include <tuple>
#include <set>
#include <unordered_map>

using namespace std;

typedef pair<unsigned long long, unsigned long long> Position;
typedef deque<Position> Positions;
typedef deque<Positions> WordPositions;
typedef tuple<unsigned long long, unsigned long long, unsigned long, bool> Minima;
typedef unordered_map<unsigned long long, unsigned long long> WordCounts;

Minima minima(-1, 0, 0, false);
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

inline void get_smallest_para(std::string const& line, WordPositions& wordPositions, unsigned long long minimum, unsigned long long maximum,
        WordCounts const& wordCounts, unsigned long long level)
{
    if (level == wordPositions.size())
    {
        const unsigned long long wordCount = wordCounts.find(maximum)->second - wordCounts.find(minimum)->second + 1;
        if (get<0>(minima) > wordCount)
        {
//          cout << "set ---- " << minimum << " " << maximum << " " << get<0>(minima) << "->" << wordCount << endl;
            get<0>(minima) = wordCount;
            get<1>(minima) = minimum;
            get<2>(minima) = maximum;
            get<3>(minima) = true;
        }
        return;
    }

//  sort(wordPositions[level].begin(), wordPositions[level].end(), [minimum, maximum, &wordCounts] (Position const& lhs, Position const& rhs) {
//          const unsigned long long wordCount_1 = wordCounts.find(std::max(maximum, lhs.second + 1))->second - wordCounts.find(std::min(minimum, lhs.first))->second + 1;
//          const unsigned long long wordCount_2 = wordCounts.find(std::max(maximum, rhs.second + 1))->second - wordCounts.find(std::min(minimum, rhs.first))->second + 1;
//          return wordCount_1 < wordCount_2;
//  });

    bool createdMinima = false;
    for (unsigned long long index = 0; index < wordPositions[level].size(); ++index)
    {
        Position const& position = wordPositions[level][index];

        if (!createdMinima && get<3>(minima) && get<1>(minima) < position.first)
        {
//          cout << get<1>(minima) << " " << position.first << endl;
            return;
        }

        const unsigned long long localMinimum = std::min(minimum, position.first);
        const unsigned long long localMaximum = std::max(maximum, position.second + 1);

//      const unsigned long long wordCount = wordCounts.find(localMaximum)->second - wordCounts.find(localMinimum)->second + 1;
//      if (get<0>(minima) <= wordCount)
//      {
//          continue;
//      }

        // invalidate the minima
        get<3>(minima) = false;

//      cout << "=====" << localMinimum << " " << localMaximum << " " << level << endl;
        get_smallest_para(line, wordPositions, localMinimum, localMaximum, wordCounts, level + 1);
        createdMinima = get<1>(minima) == position.first;
//      cout << "check----" << get<1>(minima) << " " << position.first << " " << level << " " << createdMinima << endl;
    }
}

int main()
{
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

//  sort(wordPositions.begin(), wordPositions.end(), [](Positions const& lhs, Positions const& rhs) { return lhs.size() < rhs.size(); });

    get_smallest_para(line, wordPositions, -1, 0, wordCounts, 0);

    char const* start = line.c_str() + get<1>(minima);
    line[get<2>(minima)] = 0;
    cout << start << endl;

    return 0;
}
