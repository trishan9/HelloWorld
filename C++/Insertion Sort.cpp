#include<iostream>
using namespace std;

int InsertionSort(int arr[], int n){

   for(int i =1; i<n; i++){
    int temp = arr[i];
    int j =i-1;
     for(; j>=0; j--){
        if(arr[j]>temp){
            arr[j+1] = arr[j];
        }
        else{
            break;
        }
    }
    arr[j+1] = temp;
    }
    cout<< "Insertion Sorted Array : " << endl;
    for(int i = 0; i<n; i++ ){
        cout<< arr[i] << " ";
    }
}
int main(){
    int arr[5] = {6,5,4,2,3};
    cout << InsertionSort(arr, 5);

}
