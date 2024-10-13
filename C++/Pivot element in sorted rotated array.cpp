#include <iostream>
using namespace std;
int getpivot(int arr[], int n){
    int s =0;
    int e = n-1;
    int mid = s + (e-s)/2;
    while(s<e){
        if(arr[mid] >= arr[0]){
            s = mid+1;
        }
        else{
            e = mid;
        }
        mid = s + (e-s)/2;
    }
    return s;
}
int Binarysearch(int arr[], int s, int e, int key){
    int start = s;
    int end = e;
    int mid = start + (end-start)/2;
    while(start<end){
        if(arr[mid] == arr[key]){
            return mid;
        }
        else{
            if(arr[mid]>arr[key]){
                end =  mid -1;
            }
            else{
                start = mid +1;
                }
            mid = start + (end-start)/2;
        }
        
    }
    return -1;
}
int main() {
    int arr[5] = {7,9,1,2,3};
    int pivot = getpivot(arr, 5);
    int key = 2;
    cout<< "Pivot is at index " << pivot<< endl;
    if(arr[key]>= arr[pivot]){
        cout<< "given elememt is at index " << Binarysearch(arr, pivot, 4, 2) << endl;}
    else{
    cout<< "given elememt is at index " << Binarysearch(arr, 0, 4, 2) << endl;
}
}
