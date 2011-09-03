// Source: http://www.gild.com/challenges/details/235
// Code: https://github.com/samjam86/coding-competition/blob/master/Gild/2011/August/BowlingScoreCalculation/bowling.cpp
#include <cstdio>

short getScore(char const* line, short* valueMap, short* bonusMap)
{
    short score = 0;
    for (short i = 0, frames = 0, attempts = 0, temp = -1, c = -1; frames < 10; i += 2)
    {
        // this value
        c = valueMap[line[i]];
        temp = valueMap['/'] = 10 - c;

        // look ahead by 1
        bonusMap['/'] = valueMap[line[i + 2]];
        valueMap['/'] = 10 - bonusMap['/'];

        // look ahead by 2
        bonusMap['X'] = bonusMap['/'] + valueMap[line[i + 4]];

        score += c + bonusMap[line[i]];

        valueMap['/'] = temp;

        short s = ((line[i] == '/') || (line[i] == 'X'));
        frames += (s | (++attempts == 2)) & 0x1;
        attempts = !((attempts & 0x2) | s);
    }

    return score;
}

int main(int argc, const char *argv[])
{
    short valueMap['Z'] = { 0x0 };
    short bonusMap['Z'] = { 0x0 };

    for (short i = 0; i < 10; ++i)
    {
        valueMap[i + '0'] = i;
    }
    valueMap['X'] = 10;
    valueMap['A'] = 0;

    char const* filename = argv[1];

    FILE* inFile = std::fopen(filename, "r");

    char* line = 0;
    for (size_t len, readCount; (readCount = getline(&line, &len, inFile)) != -1 && readCount > 1;)
    {
        line[len + 1] = 'A';
        line[len + 3] = 'A';
        printf("%d\n", getScore(line, valueMap, bonusMap));
    }

    fclose(inFile);
}
