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
typedef tuple<unsigned long long, unsigned long long, unsigned long> Minima;
typedef unordered_map<unsigned long long, unsigned long long> WordCounts;
typedef vector<unsigned long long> UsedIndexes;

const int COUNT = 0;
const int MIN = 1;
const int MAX = 2;

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
            positions.push_back({startIndex, startIndex + word.length()});
            index += word.length();
        }
        else
        {
            index += 1;
        }
    }
}

unsigned long long get_words_between(WordCounts const& wordCounts, unsigned long long minimum, unsigned long long maximum)
{
    return wordCounts.find(maximum)->second - wordCounts.find(minimum)->second + 1;
}

inline void get_smallest_para(std::string const& line, WordPositions const& wordPositions, Minima& minima,
        unsigned long long minimum, unsigned long long maximum, WordCounts const& wordCounts,
        unsigned long long level, UsedIndexes& usedIndexes)
{
    if (level == wordPositions.size())
    {
for (size_t i = 0; i < level; ++i) cout << "\t";
        const unsigned long long wordCount = get_words_between(wordCounts, minimum, maximum);
        if (get<COUNT>(minima) > wordCount)
        {
            minima = tie(wordCount, minimum, maximum);
cout << "set " << minimum << "-" << maximum << endl;
        }
else cout << "try " << get<MIN>(minima) << "-" << get<MAX>(minima) << "[" << get<COUNT>(minima) << "]" << " " << minimum << "-" << maximum << "[" << wordCount << "]" << endl;
        return;
    }

    bool createdMinima = true;
    for (unsigned long long index = usedIndexes[level]; index < wordPositions[level].size(); ++index)
    {
        Position const& position = wordPositions[level][index];
        const unsigned long long localMinimum = std::min(minimum, position.first);
        const unsigned long long localMaximum = std::max(maximum, position.second + 1);

for (size_t i = 0; i < level; ++i) cout << "\t";
cout << position.first << "-" << position.second << (createdMinima ? "+" : "");
        if (!createdMinima)
        {
            if (localMinimum <= get<MIN>(minima) && get<MAX>(minima) <= localMaximum)
            {
cout << " " << minimum << "-" << maximum << " " << localMinimum << "-" << localMaximum << " (skip_2)" << endl;
                return;
            }
            if (get<COUNT>(minima) <= get_words_between(wordCounts, localMinimum, localMaximum))
            {
cout << " " << get<MIN>(minima) << "-" << get<MAX>(minima) << "[" << get<COUNT>(minima) << "] " << localMinimum << "-" << localMaximum << "[" << get_words_between(wordCounts, localMinimum, localMaximum) << "] (skip_3)" << endl;
                if (localMinimum != position.first)
                {
                    return;
                }
                else
                {
                    continue;
                }
            }
        }
cout << endl;

        usedIndexes[level] = index;
        get_smallest_para(line, wordPositions, minima, localMinimum, localMaximum, wordCounts, level + 1, usedIndexes);
        createdMinima = get<MIN>(minima) == position.first;
    }
}

int main(int argc, char* argv[])
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
            while ((i < line.length() - 1) && !isalpha(line[i + 1])) ++i;
            wordCounts[i + 1] = wordCount;
        }
    }
    wordCounts[0] = 0;
    wordCounts[line.length() + 1] = wordCount + 1;

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

    Minima minima(-1, 0, line.length() + 1);
    UsedIndexes usedIndexes(wordPositions.size(), 0);
    get_smallest_para(line, wordPositions, minima, -1, 0, wordCounts, 0, usedIndexes);

    char const* start = line.c_str() + get<MIN>(minima);
    line[get<MAX>(minima) - 1] = 0;
    cout << start << endl;

    return 0;
}
