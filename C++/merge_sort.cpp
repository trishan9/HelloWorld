#include<iostream>
using namespace std;
void merge(int arr[], int si, int mid, int ei){

    int a = (ei-si+1);  int x=0; int merged[a];  //we created a new array which will store the sorted elements.
    int indx1 = si; int indx2 = mid+1;
  
    while(indx1<= mid && indx2<=ei){
        if(arr[indx1]<arr[indx2]){
            merged[x++]=arr[indx1++];
        }
        else{
            merged[x++]=arr[indx2++];
        }
    }
    while(indx1 <= mid)
     merged[x++]=arr[indx1++];
    while(indx2<=ei)
     merged[x++]=arr[indx2++];

    for(int i=0, j=si; i<a; i++,j++){
        arr[j]=merged[i];

    }

}
    
    
void divide(int arr[], int si, int ei){
    if(si>=ei){
        return;
    }
    int mid = si +(ei-si)/2;  //we write this because it helps in better space complexity.
    divide(arr, si,mid);
    divide(arr,mid+1,ei);
    merge(arr,si,mid,ei);
    
}
int main(){
    int arr[]={6,3,9,5,2,8};
    int n = sizeof(arr)/sizeof(arr[0]);
    divide(arr,0,n-1);
    for(int i=0; i<n; i++){
        cout<<arr[i]<<endl;
    }
    return 0;
}