// Source: http://www.gild.com/challenges/details/235
// Code: https://github.com/samjam86/coding-competition/blob/master/Gild/2011/August/BowlingScoreCalculation/bowling.cpp
#include <stdio.h>
#include <cstdlib>

int main(int argc, const char *argv[])
{
    short valueMap['Z' - '/'] = { 0, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }, bonusMap['Z' - '/'] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    valueMap['X' - '/'] = 10;

    FILE* inFile = fopen(argv[1], "r");

    char* readLine = (char*)malloc(200);
    short readCount, score;
    for (size_t len = 200; (readCount = getline(&readLine, &len, inFile)) > 1; score = 0)
    {
        readLine[readCount + 1] = readLine[readCount + 3] = 'A';

        char* line = readLine;
        for (short frames = 0, attempts = 0, c; frames < 10; line += 2)
        {
            c = valueMap[*line - '/'];
            bonusMap[0] = valueMap[line[2] - '/'];
            valueMap[0] = 10 - bonusMap[0];
            bonusMap['X' - '/'] = bonusMap[0] + valueMap[line[4] - '/'];
            score += c + bonusMap[*line - '/'];
            valueMap[0] = 10 - c;
            ++attempts;
            attempts = (attempts != 2);
            attempts &= (*line != 'X');
            attempts &= (*line != '/');
            frames += !attempts;
        }
        printf("%d\n", score);
    }
    free(readLine);
    fclose(inFile);
}
