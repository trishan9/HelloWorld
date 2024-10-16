bool isposible(vector<int> &stalls, int k,int mid){
    int cow = 1;
    int last = stalls[0];
    for(int i=0 ; i<stalls.size();i++){
        if(stalls[i]-last>=mid){
         cow++;
         if (cow == k) {
              return true;
            }
            last = stalls[i];
        }
    }
    return false;
}
int aggressiveCows(vector<int> &stalls, int k)
{
    //    Write your code here.
    sort(stalls.begin(),stalls.end());
    int s = 0;
    int maxi = -1;
    for(int i=0 ; i< stalls.size() ;i++){
        maxi = max(maxi , stalls[i]);
    }
    int e = maxi;
    int ans = -1;
    int mid = s + (e-s)/2;
    while(e>=s){
        if(isposible(stalls,k,mid)){
            ans=mid;
            s = mid+1;
        }
        else{
            e = mid-1;
        }
        mid = s + (e-s)/2;
    }
    return ans;
}