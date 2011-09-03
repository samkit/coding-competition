// Source: http://www.gild.com/challenges/details/235
// Code: https://github.com/samjam86/coding-competition/blob/master/Gild/2011/August/BowlingScoreCalculation/bowling.cpp
#include <stdio.h>

int main(int argc, const char *argv[])
{
    short valueMap['Z'] = { 0x0 }, bonusMap['Z'] = { 0x0 };

    for (short i = 0; i < 10; ++i) valueMap[i + '0'] = i;
    valueMap['X'] = 10;

    FILE* inFile = fopen(argv[1], "r");

    char* line = 0;
    for (size_t len, readCount, score = 0; (readCount = getline(&line, &len, inFile)) != -1 && readCount > 1 && (line[readCount + 1] = 'A') && (line[readCount + 3] = 'A'); score = 0)
    {
        for (short i = 0, frames = 0, attempts = 0, c; frames < 10; i += 2)
        {
            c = valueMap[line[i]];
            valueMap['/'] = 10 - (bonusMap['/'] = valueMap[line[i + 2]]);
            bonusMap['X'] = bonusMap['/'] + valueMap[line[i + 4]];
            score += c + bonusMap[line[i]];
            valueMap['/'] = 10 - c;
            frames += (((line[i] == '/') | (line[i] == 'X')) | (++attempts == 2)) & 0x1;
            attempts = !((attempts == 2) | ((line[i] == '/') || (line[i] == 'X')));
        }
        printf("%d\n", score);
    }
}
