#include <iostream>
#include <string>

using namespace std;

template <typename T>
void displayArray (T arr[], int siz) {
    for (int i = 0; i < siz; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

template <typename T>
T sumArray (T arr[], int siz) {
    T sum = 0;
    for (int i = 0; i < siz; ++i)
        sum += arr[i];
    return sum;
}


int main()
{
    int array1[100];
    char array2[10];

    for (int i = 0; i < 100; ++i)
        array1[i] = i;

    for (int i = 0; i < 10; ++i)
        array2[i] = (char)i;

    displayArray(array1, 100);
    displayArray(array2, 10);

    cout << "Sum of array1: " << sumArray(array1, 100) << endl;
    cout << "Sum of array2: " << sumArray(array2, 256) << endl;

    return 0;
}
