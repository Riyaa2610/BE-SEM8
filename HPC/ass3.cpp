// Implement Min, Max, Sum and Average operations using Parallel Reduction.
// Measure the performance of sequential and parallel algorithms

#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>
using namespace std;

long long arr_max_parallel(vector<long long> arr)
{
    long long maxi = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction(max : maxi)
    for (long long i = 0; i < arr.size(); i++)
    {
        // maxi = max(maxi, arr[i]);
        if (arr[i] > maxi)
        {
            maxi = arr[i];
        }
    };
    double end = omp_get_wtime();
    cout << "Parallel max reduction time: " << end - start << endl;
    cout << "Max: " << maxi;
    cout << endl;

    return maxi;
}
long long arr_max_seq(vector<long long> arr)
{
    long long maxi = arr[0];
    double start = omp_get_wtime();
    for (long long i = 0; i < arr.size(); i++)
    {
        // maxi = max(maxi, arr[i]);
        if (arr[i] > maxi)
        {
            maxi = arr[i];
        }
    };
    double end = omp_get_wtime();
    cout << "Seq max reduction time: " << end - start << endl;
    cout << "Max: " << maxi;
    cout << endl;

    return maxi;
}
long long arr_min_parallel(vector<long long> arr)
{
    long long mini = arr[0];
    double start = omp_get_wtime();

#pragma omp parallel for reduction(min : mini)
    for (long long i = 0; i < arr.size(); i++)
    {
        // mini = min(mini, arr[i]);
        if (arr[i] < mini)
        {
            mini = arr[i];
        }
    };
    double end = omp_get_wtime();
    cout << "Parallel min reduction time: " << end - start << endl;
    cout << "Min: " << mini;
    cout << endl;

    return mini;
}
long long arr_min_seq(vector<long long> arr)
{
    long long mini = arr[0];
    double start = omp_get_wtime();
    for (long long i = 0; i < arr.size(); i++)
    {
        // mini = min(mini, arr[i]);
        if (arr[i] < mini)
        {
            mini = arr[i];
        }
    };
    double end = omp_get_wtime();
    cout << "Seq min reduction time: " << end - start << endl;
    cout << "Min: " << mini;
    cout << endl;

    return mini;
}

long long arr_sum_parallel(vector<long long> arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double end = omp_get_wtime();
    cout << "Sum reduction time: " << end - start << endl;
    cout << "Sum: " << endl;
    cout << endl;

    return sum;
}

long long arr_sum_seq(vector<long long> arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double end = omp_get_wtime();
    cout << "Seq sum reduction time: " << end - start << endl;
    cout << "Sum: " << sum;
    cout << endl;

    return sum;
}

double arr_avg_parallel(vector<long long> arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
#pragma omp parallel for reduction(+ : sum)
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double avg = sum / arr.size();
    double end = omp_get_wtime();
    cout << "Parallel avg reduction time: " << end - start << endl;
    cout << "Avg: " << avg;
    cout << endl;

    return avg;
}

long long arr_avg_seq(vector<long long> arr)
{
    long long sum = 0;
    double start = omp_get_wtime();
    for (long long i = 0; i < arr.size(); i++)
    {
        sum += arr[i];
    }
    double avg = sum / arr.size();
    double end = omp_get_wtime();
    cout << "Sequential avg reduction time: " << end - start << endl;
    cout << "Avg: " << avg;
    cout << endl;

    return avg;
}

int main()
{
    long long n = 9000000;
    vector<long long> arr = {1, 2, 4, 5, 7, 2, 6, 0};
    for (long long i = 0; i < n; i++)
    {
        arr.push_back(rand() % 1000);
    }
    arr_max_parallel(arr);
    arr_max_seq(arr);
    cout << endl;

    arr_min_parallel(arr);
    arr_min_seq(arr);
    cout << endl;

    arr_sum_parallel(arr);
    arr_sum_seq(arr);
    cout << endl;

    arr_avg_parallel(arr);
    arr_avg_seq(arr);
    cout << endl;

    return 0;
}