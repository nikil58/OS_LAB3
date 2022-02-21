#include <iostream>
#include <Windows.h>
#include <vector>
#include <atomic>

using namespace std;

#define N 100000000
#define blockSize 930715
atomic_int counter =  0;
double pi = 0;
DWORD WINAPI calculatePi(LPVOID lpParam);

int main()
{
    int threadCount;
    cout << "Enter the number of threads count: ";
    cin >> threadCount;
    vector<HANDLE> threads(threadCount);
        vector<long double> subtotals(threadCount);
    for (size_t i = 0; i < threadCount; ++i)
    {
        threads[i] = CreateThread(nullptr, 0, calculatePi, &subtotals[i], CREATE_SUSPENDED, nullptr);
    }
    DWORD timeStart = GetTickCount();
    for (HANDLE &thread : threads)
    {
        ResumeThread(thread);
    }
    WaitForMultipleObjects(threadCount, threads.data(), TRUE, INFINITE);
    double res = 0;
    for (int i = 0; i < threadCount; i++) {
        res += subtotals[i];
    }
    res = res / N;
    DWORD timeEnd = GetTickCount();
    cout << "Total time: " << timeEnd - timeStart << endl;
    cout.precision(10);
    cout << "Calculated pi: " << res << endl;
    system("pause");
    for (int i = 0; i < threadCount; ++i)
    {
        CloseHandle(threads[i]);
    }
    return 0;
}

DWORD WINAPI calculatePi(LPVOID lpParam){
    long double* interimResult = static_cast<long double*>(lpParam);
    size_t start = 0;
    size_t end = 0;
    long double x = 0;
    long double sum = 0;
    start = blockSize * counter;
    end = blockSize * (counter+1);

    do {
        counter+=1;
        sum = 0;
        for (size_t i = start; i < N && i < end; ++i)
        {
            x = (i + 0.5) / N;
            sum += (4 / (1 + x*x));
        }
        *interimResult += sum;
        start = blockSize * counter;
        end = blockSize * (counter+1);
    } while (start < N);
    return 0;
}