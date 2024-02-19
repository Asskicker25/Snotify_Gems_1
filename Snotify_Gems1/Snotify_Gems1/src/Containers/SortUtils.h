#pragma once

namespace Sorting
{
    template <typename T>
    void Swap(T& a, T& b) 
    {
        T temp = a;
        a = b;
        b = temp;
    }

    template <typename T>
    int Partition(T* arr, int low, int high, bool (*compare)(T&, T&)) 
    {
        T pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; j++) 
        {
            if (compare(arr[j], pivot)) 
            {
                i++;
                Swap(arr[i], arr[j]);
            }
        }
        Swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    template <typename T>
    void QuickSort(T* arr, int low, int high, bool (*compare)(T&, T&)) 
    {
        if (low < high)
        {
            int pi = Partition(arr, low, high, compare);
            QuickSort(arr, low, pi - 1, compare);
            QuickSort(arr, pi + 1, high, compare);
        }
    }

}