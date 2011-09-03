// Source: http://www.gild.com/challenges/details/235
// Code: https://github.com/samjam86/coding-competition/blob/master/Gild/2011/August/BowlingScoreCalculation/bowling.cpp
#include <stdio.h>
#include <cstdlib>

int main(int argc, const char *argv[])
{
    short valueMap['Z' - '/'] = { 0x0 }, bonusMap['Z' - '/'] = { 0x0 };

    for (short i = 0; i < 10; ++i) valueMap[i + '0' - '/'] = i;
    valueMap['X' - '/'] = 10;

    FILE* inFile = fopen(argv[1], "r");

    char* readLine = (char*)malloc(200);
    for (size_t readCount, score = 0, len = 200; (readCount = getline(&readLine, &len, inFile)) != -1 && readCount > 1; score = 0)
    {
        readLine[readCount + 1] = readLine[readCount + 3] = 'A';

        char* line = readLine;
        for (short frames = 0, attempts = 0, c; frames < 10; line += 2)
        {
            c = valueMap[*line - '/'];
            valueMap['/' - '/'] = 10 - (bonusMap['/' - '/'] = valueMap[line[2] - '/']);
            bonusMap['X' - '/'] = bonusMap['/' - '/'] + valueMap[line[4] - '/'];
            score += c + bonusMap[*line - '/'];
            valueMap['/' - '/'] = 10 - c;
            bool f = ((*line == 'X') || (*line == '/'));
            frames += (f | (++attempts == 2));
            attempts = !((attempts == 2) | f);
        }
        printf("%d\n", score);
    }
    free(readLine);
    fclose(inFile);
}
