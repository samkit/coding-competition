// Source: http://www.gild.com/challenges/details/235
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

static short valueMap['Z'] = { 0x0 };
static short bonusMap['Z'] = { 0x0 };

short getScore(char const* line)
{
    short score = 0;
    short frames = 0;
    short attempts = 0;
    short c;
    short temp;
    short s;
    for (short i = 0; frames < 10; i += 2)
    {
        // this value
        c = valueMap[line[i]];
        temp = valueMap['/'] = 10 - c;

        // look ahead by 1
        bonusMap['/'] = valueMap[line[i + 2]];
        valueMap['/'] = 10 - bonusMap['/'];

        // look ahead by 2
        bonusMap['X'] = bonusMap['/'] + valueMap[line[i + 4]];

        score += c;
        score += bonusMap[line[i]];

        valueMap['/'] = temp;

        s = ((line[i] == '/') || (line[i] == 'X'));
        frames += (s | (++attempts == 2)) & 0x1;
        attempts = !((attempts & 0x2) | s);
    }

    return score;
}

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    for (short i = 0; i < 10; ++i)
    {
        valueMap[i + '0'] = i;
    }
    valueMap['X'] = 10;
    valueMap['A'] = 0;

    char const* filename = argv[1];
    std::ifstream inFile(filename);

    char line[100];
    while (inFile.getline(line, sizeof(line)) || line[0])
    {
        if (!line[0])
            continue;

        size_t len = inFile.gcount();

        line[len + 1] = 'A';
        line[len + 3] = 'A';

        std::cout << getScore(line) << '\n';

        line[0] = 0;
    }

    inFile.close();

    return 0;
}
