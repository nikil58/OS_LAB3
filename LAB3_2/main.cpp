#include <iostream>
#include <Windows.h>
using namespace std;

double pi = 0.0;
#define blockSize 930715

int main()
{
    int N = 100000000;
    int threadCount;
    cout << "Enter the number of threads count: ";
    cin >> threadCount;
    long double x = 0;
    long double sum = 0;
    DWORD timeStart = GetTickCount();

#pragma omp parallel for schedule(dynamic,blockSize) default (none) private(x) shared(N) num_threads(threadCount) reduction (+ : sum)
        for (long long i = 0; i < N; i++)
        {
            x = (i + 0.5) / N;
            sum += 4 / (1 + x * x);
        }

        pi = sum / N;

    DWORD timeEnd = GetTickCount();

    cout << "Total time: " <<  timeEnd - timeStart << endl;
    cout.precision(10);
    cout << "Calculated pi: " << pi << endl;
    system("pause");
    return 0;
}
