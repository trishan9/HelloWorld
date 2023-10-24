struct item
{
    int value,weight;
};
bool cmp(item a,item b)
{
    double r1=(double)a.value/a.weight;
    double r2=(double)b.value/b.weight;
    return(r1>r2);
}
double fractionalknapsack(item A[],int Total_Capacity,int n)
{
    sort(A,A + n,cmp);
    int cur_weight = 0;
    double final_val = 0.0;
    for(int i=0;i<n;i++)
    {
        if(cur_weight + arr[i].weight <= Total_Capacity)
        {
            Cur_weight += A[i].weight;
            Final_val += A[i].value;
        }
        else
        {
            int remain = Total_capacity - cur_weight;
            Final_val += A[i].value * ((double)remain / A[i].weight);
        }
    }
    return final_val;
}
