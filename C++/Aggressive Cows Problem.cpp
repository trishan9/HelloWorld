#include<iostream>
#include<algorithm>
using namespace std;

bool isPossible(int arr[], int k, int mid, int n){

int cowCount = 1;
int lastPos = arr[0];

for(int i =0; i<n; i++){

    if(arr[i]-lastPos >= mid){
        cowCount++;
        if(cowCount==k){
            return true;
        }
        lastPos = arr[i];
    }
}
return false;
}



int aggressiveCow(int arr[], int k, int n){
    sort(arr, arr + n);
    int s = 0;
    int maxi = -1;
    for(int i = 0; i<n; i++){
        maxi = max(maxi, arr[i]);
    }
    int e = maxi;
    int ans = -1;
    int mid = s + (e-s)/2;

    while(s<=e){
        if(isPossible(arr, k, mid, n)){
            ans = mid;
            s = mid + 1;
        }
        else{
            e = mid -1;
        }
        mid = s + (e-s)/2;
    }
    return ans;
}

int main(){

int arr[5] = {4,2,3,1,5};
cout<< aggressiveCow(arr, 2, 5);

}
