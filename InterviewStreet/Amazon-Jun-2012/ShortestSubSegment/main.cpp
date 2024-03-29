#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstring>
#include <tuple>
#include <set>
#include <unordered_map>

using namespace std;

struct Position
{
    size_t start;
    size_t end;
    size_t count;
};

typedef vector<Position> Positions;
typedef vector<Positions> WordPositions;
typedef tuple<size_t, Position, Position> Minima;
typedef unordered_map<size_t, size_t> WordCounts;
typedef vector<size_t> UsedIndexes;

const int COUNT = 0;
const int MIN = 1;
const int MAX = 2;

inline bool operator< (Position const& lhs, Position const& rhs)
{
    return lhs.count < rhs.count;
}

inline size_t get_words_between(WordCounts const& wordCounts, size_t minimum, size_t maximum)
{
    return wordCounts.find(maximum)->second - wordCounts.find(minimum)->second + 1;
}

void search_pattern(std::string const& line, std::string const& word, WordCounts const& wordCounts, Positions& positions)
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
            size_t startIndex = index - start;
            size_t endIndex = startIndex + word.length();
            size_t wordCount = get_words_between(wordCounts, 0, endIndex + 1);
            positions.push_back({startIndex, endIndex, wordCount});
            index += word.length();
        }
        else
        {
            index += 1;
        }
    }
}

inline void get_smallest_para(WordPositions const& wordPositions, Minima& minima,
        Position const& minimum, Position const& maximum, WordCounts const& wordCounts,
        size_t level, UsedIndexes& usedIndexes)
{
    if (level == wordPositions.size())
    {
        const size_t wordCount = maximum.count - minimum.count + 1;
        if (get<COUNT>(minima) > wordCount)
        {
            minima = tie(wordCount, minimum, maximum);
        }
        return;
    }

    bool createdMinima = true;
    for (size_t index = usedIndexes[level]; index < wordPositions[level].size(); ++index)
    {
        Position const& position = wordPositions[level][index];
        Position const& localMinimum = std::min(minimum, position);
        Position const& localMaximum = std::max(maximum, position);
        if (!createdMinima && localMinimum.count <= get<MIN>(minima).count && get<MAX>(minima).count <= localMaximum.count)
        {
            return;
        }

        if (get<COUNT>(minima) <= localMaximum.count - localMinimum.count)
        {
            if (localMinimum.count != position.count)
            {
                return;
            }
            else
            {
                usedIndexes[level] = index;
                continue;
            }
        }

        usedIndexes[level] = index;
        get_smallest_para(wordPositions, minima, localMinimum, localMaximum, wordCounts, level + 1, usedIndexes);
        createdMinima = get<MIN>(minima).count == position.count;
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
    wordCounts[line.length() + 1] = ++wordCount;

    size_t K = 0;
    cin >> K;

    WordPositions wordPositions;
    while (K--)
    {
        std::string word;
        Positions positions;

        cin >> word;

        search_pattern(line, word, wordCounts, positions);
        if (positions.empty())
        {
            cout << "NO SUBSEGMENT FOUND" << endl;
            return 0;
        }

        wordPositions.push_back(std::move(positions));
    }

    Minima minima(-1, {-1, -1, 0}, {-1, -1, wordCount});
    UsedIndexes usedIndexes(wordPositions.size(), 0);
    get_smallest_para(wordPositions, minima, {-1, -1, wordCount + 1}, {-1, -1, 0}, wordCounts, 0, usedIndexes);

    char const* start = line.c_str() + get<MIN>(minima).start;
    line[get<MAX>(minima).end] = 0;
    cout << start << endl;

    return 0;
}
