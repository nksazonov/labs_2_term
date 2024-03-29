#ifndef SORTING_H
#define SORTING_H
#include <cstddef>
#include <chrono>
#include <QDebug>
#include "random.h"
#include "table.h"
#include "binaryTree.h"
#include "visualize.h"

template <typename T>
void _swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
}

template <typename T>
void shuffle(T arr[], int size)
{
    for (int i = size-1; i > 0; i--)
    {
        int j = getRandomInt(0,i);
        _swap(arr[i], arr[j]);
    }
}

template <typename T>
void bubbleSort(T arr[], int size, bool vis, std::queue<visualization>* visuals)
{
    bool sorted = false;
    int lastSorted = size-1;

    while (!sorted)
    {
        sorted = true;

        for (int idx = 0; idx < lastSorted; idx++)
        {
            if (vis) visuals->push({0, idx, idx+1, ""});

            if (arr[idx] > arr[idx+1])
            {
                if (vis) visuals->push({1, idx, idx+1, ""});
                _swap(arr[idx], arr[idx+1]);
                sorted = false;
            }
        }

        lastSorted--;
    }
}

template <typename T>
void selectionSort(T arr[], int first, int last, bool vis, std::queue<visualization>* visuals)
{
    int sorted_idx = first,
        elem = first,
        min_idx = first;

    while(sorted_idx < last)
    {

        min_idx = sorted_idx;
        elem = sorted_idx + 1;

        while (elem < last+1)
        {
            if (vis) visuals->push({0, elem, min_idx, ""});

            if (arr[elem] < arr[min_idx])
            {
                min_idx = elem;
            }

            elem++;
        }

        if (vis) visuals->push({1, min_idx, sorted_idx, ""});;

        _swap(arr[min_idx], arr[sorted_idx]);

        sorted_idx++;
    }
}

template <typename T>
int medianOfThree(T arr[], int first, int last, bool vis, std::queue<visualization>* visuals)
{
    int med = (first+last)/2;

    int pivot = first;

    if (vis) {
        visuals->push({0, first, med, ""});
        visuals->push({0, med, last, ""});
        visuals->push({0, first, last, ""});
    }

    if ((arr[first] < arr[med] && arr[med] < arr[last]) ||
        (arr[last] < arr[med] && arr[med] < arr[first]))
    {
        pivot = med;

    } else if ((arr[first] < arr[last] && arr[last] < arr[med]) ||
               (arr[med] < arr[last] && arr[last] < arr[first]))
    {
        pivot = last;
    }

    return pivot;
}

template <typename T>
int partition(T arr[], int first, int last, bool vis, std::queue<visualization>* visuals)
{
    int pivotIdx = medianOfThree(arr, first, last, vis, visuals);
    int low = first-1, high = last+1;

    while (true) {

        do {
            low++;

            if (vis) visuals->push({0, low, pivotIdx, ""});

        } while (arr[low] < arr[pivotIdx]);

        do {
            high--;

            if (vis) visuals->push({0, high, pivotIdx, ""});

        } while(arr[high] > arr[pivotIdx]);

        if (low >= high)
        {
           return high;
        }


        _swap(arr[high], arr[low]);

        if (vis) visuals->push({1, high, low, ""});
    }
}

template <typename T>
void quicksort(T arr[], int first, int last, bool vis, std::queue<visualization>* visuals)
{
    if (first >= last) return;

    int pivot_idx = partition(arr, first, last, vis, visuals);
    quicksort(arr, first, pivot_idx, vis, visuals);
    quicksort(arr, pivot_idx+1, last, vis, visuals);
}

template <typename T>
T min(T a, T b)
{
    return (a < b ? a : b);
}

template <typename T>
void merge(T arr[], T temp[], int from, int mid, int to, bool vis, std::queue<visualization>* visuals)
{
//    int size = to-from;
//    T* temp = new T[size];
    //T temp[to-from];

    int temp_idx = 0, first_idx = from, second_idx = mid+1;

    while(first_idx <= mid && second_idx <= to) {

        if (vis) visuals->push({0, first_idx, second_idx, ""});

        if (arr[first_idx] <= arr[second_idx]) {
            temp[temp_idx++] = arr[first_idx++];
        } else {
            temp[temp_idx++] = arr[second_idx++];
        }

    }

    while(first_idx <= mid) {
        temp[temp_idx++] = arr[first_idx++];
    }

    while(second_idx <= to) {
        temp[temp_idx++] = arr[second_idx++];
    }

    for (int arr_idx = from, temp_idx = 0; arr_idx <= to; arr_idx++, temp_idx++) {
        arr[arr_idx] = temp[temp_idx];

        if (vis) visuals->push({2, arr_idx, 0, temp[temp_idx].getTwoRowsText()});
    }

}

template <typename T>
void mergesort(T arr[], T temp[], int n, bool vis, std::queue<visualization>* visuals)
{

    for (int curr_size = 1; curr_size <= n-1; curr_size *= 2)
        {
            for (int left_start = 0; left_start < n-1; left_start += 2*curr_size)
            {
                int from = left_start;
                int mid = min(left_start + curr_size - 1, n-1);
                int to = min(left_start + 2*curr_size - 1, n-1);

                //T temp[to-from];

                merge(arr, temp, from, mid, to, vis, visuals);
            }
        }
}

template <typename T>
void hybridQuicksort(T arr[], int first, int last, int step, bool vis, std::queue<visualization>* visuals)
{
    if (first >= last) return;

    if (last - first < step) {

        selectionSort(arr, first, last, vis, visuals);

    } else {

        int pivot_idx = partition(arr, first, last, vis, visuals);
        hybridQuicksort(arr, first, pivot_idx, step, vis, visuals);
        hybridQuicksort(arr, pivot_idx+1, last, step, vis, visuals);

    }

}

template <typename T>
void shakerSort(T arr[], int size, bool vis, std::queue<visualization>* visuals)
{
    if (size <= 1) return;
    bool arrSorted = false;

    int beg = -1;
    int end = size - 1;

    while (!arrSorted)
    {
        arrSorted = true;
        beg++;
        for (int elem = beg; elem < end; elem++)
        {
            if (vis) if (vis) visuals->push({0, elem, elem+1, ""});
            if (arr[elem] > arr[elem+1])
            {
                if (vis) if (vis) visuals->push({1, elem, elem+1, ""});
                _swap(arr[elem], arr[elem+1]);
                arrSorted = false;
            }
        }

        if (arrSorted) break;

        end--;
        for(int elem = end; elem > beg; elem--)
        {
            if (vis) if (vis) visuals->push({0, elem, elem-1, ""});
            if (arr[elem] < arr[elem-1])
            {
                if (vis) if (vis) visuals->push({1, elem, elem-1, ""});
                _swap(arr[elem], arr[elem-1]);
                arrSorted = false;
            }
        }

    }
}

template <typename T>
void heapify(T arr[], int size, int max, bool vis, std::queue<visualization>* visuals)
{
    int largest = max;
    int left = 2*max + 1;
    int right = 2*max + 2;

    if (left < size)
    {
        if (vis) visuals->push({0, left, largest, ""});
        if (arr[left] > arr[largest])
            largest = left;
    }

    if (right < size)
    {
        if (vis) visuals->push({0, right, largest, ""});
        if (arr[right] > arr[largest])
            largest = right;
    }

    if (largest != max)
    {
        if (vis) visuals->push({1, max, largest, ""});
        _swap(arr[max], arr[largest]);

        heapify(arr, size, largest, vis, visuals);
    }
}

template <typename T>
void heapSort(T arr[], int size, bool vis, std::queue<visualization>* visuals)
{
    for (int i = size / 2 - 1; i >= 0; i--)
            heapify(arr, size, i, vis, visuals);

    for (int i=size-1; i>0; i--)
        {
            if (vis) visuals->push({1, 0, i, ""});
            _swap(arr[0], arr[i]);

            heapify(arr, i, 0, vis, visuals);
        }
}

template <typename T>
void binaryTreeSort(T arr[], int size)
{
    Node<T> *root = new Node<T>(arr[0]);

    for (int idx = 1; idx < size; idx++)
    {
        root->insert(arr[idx]);
    }

    int elem = 0;
    root->BTtoArr(arr, elem);
}

template <typename T>
void combSort(T arr[], int size, bool vis, std::queue<visualization>* visuals)
{
    if(size <= 1) return;

    double factor = 1.2473;
    int step = size-1;
    while (step > 1)
    {
        for(int idx = 0; idx + step < size; idx++)
        {
            if(vis) visuals->push({0, idx, idx+step, ""});
            if (arr[idx] > arr[idx+step])
            {
                if(vis) visuals->push({1, idx, idx+step, ""});
                _swap(arr[idx], arr[idx+step]);
            }
        }

        step /= factor;
    }

    bubbleSort(arr, size, vis, visuals);
}

template <typename T>
void gnomeSort(T arr[], int size, bool vis, std::queue<visualization>* visuals)
{
    int idx = 0;

    while (idx < size) {
        if (idx == 0)
            idx++;

        if(vis) visuals->push({0, idx, idx-1, ""});

        if (arr[idx] >= arr[idx - 1])
            idx++;
        else {
            if(vis) visuals->push({1, idx, idx-1, ""});
            _swap(arr[idx], arr[idx - 1]);
            idx--;
        }
    }
}

template <typename T>
void oddEvenSort(T arr[], int size, bool vis, std::queue<visualization>* visuals)
{
    bool sorted = false;
    while(!sorted)
    {
        sorted = true;

        for(int idx = 0; idx <= size - 2; idx+=2)
        {
            if(vis) visuals->push({0, idx, idx+1, ""});
            if (arr[idx] > arr[idx+1])
            {
                if(vis) visuals->push({1, idx, idx+1, ""});
                _swap(arr[idx], arr[idx+1]);
                sorted = false;
            }
        }

        for(int idx = 1; idx <= size - 2; idx +=2)
        {
            if(vis) visuals->push({0, idx, idx+1, ""});
            if (arr[idx] > arr[idx+1])
            {
                if(vis) visuals->push({1, idx, idx+1, ""});
                _swap(arr[idx], arr[idx+1]);
                sorted = false;
            }
        }
    }
}

#endif // SORTING_H
