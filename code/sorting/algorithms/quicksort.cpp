//QuickSort (With Code in Python/C++/Java/C). (s. f.). https://www.programiz.com/dsa/quick-sort
// Quick sort in C++

#include <iostream>
#include <vector>
using namespace std;

// function to swap elements
void swapQuick(int *a, int *b) {
  int t = *a;
  *a = *b;
  *b = t;
}

// function to rearrange array (find the partition point)
int partition(vector<int>& array, int low, int high) {
    
  // select the rightmost element as pivot
  int pivot = array[high];
  
  // pointer for greater element
  int i = (low - 1);

  // traverse each element of the array
  // compare them with the pivot
  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
        
      // if element smaller than pivot is found
      // swap it with the greater element pointed by i
      i++;
      
      // swap element at i with element at j
      swapQuick(&array[i], &array[j]);
    }
  }
  
  // swap pivot with the greater element at i
  swapQuick(&array[i + 1], &array[high]);
  
  // return the partition point
  return (i + 1);
}

void quickSort(vector<int>& array, int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);

    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}