#include <cstdio>
#include <ctype.h>

using namespace std;

short clear_connected_points(char* array, unsigned long long x, unsigned long long y, unsigned long long N)
{
    static unsigned long long neighbours[][2] = {
        { -1, -1 },     // top left
        { -1,  0 },     // left
        { -1,  1 },     // bottom left
        {  0, -1 },     // top
        {  0,  1 },     // bottom
        {  1, -1 },     // top right
        {  1,  0 },     // right
        {  1,  1 },     // bottom right
    };

    if (array[x * N + y] != '1')
    {
        return 0;
    }

    array[x * N + y] = '0';
    for (unsigned long long index = 0; index < sizeof(neighbours) / sizeof(unsigned long long[2]); ++index)
    {
        const unsigned long long i = x + neighbours[index][0];
        const unsigned long long j = y + neighbours[index][1];
        if (0 <= i && i < N && 0 <= j && j < N)
        {
            clear_connected_points(array, i, j, N);
        }
    }
    return 1;
}

int main()
{
    unsigned long long T;
    unsigned long long N;
    scanf("%llu", &T);

    while (T--)
    {
        scanf("%llu", &N);
        char* array = new char[N * N];
        for (unsigned long long i = 0; i < N; ++i)
        {
            for (unsigned long long j = 0; j < N; ++j)
            {
                scanf("%c", &array[i * N + j]);
                if (isspace(array[i * N + j]))
                {
                    scanf("%c", &array[i * N + j]);
                }
            }
        }
        unsigned long long count = 0;
        for (unsigned long long i = 0; i < N; ++i)
        {
            for (unsigned long long j = 0; j < N; ++j)
            {
                count += clear_connected_points(array, i, j, N);
            }
        }
        printf("%llu\n", count);
        delete array;
    }

    return 0;
}
