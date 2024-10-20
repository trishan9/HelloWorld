#include<stdio.h>
int main()
{
    //this is the program to implement linear search in c language.


    printf("Enter the number of elements in the array. \n");
    int n,search,flag = 0,position = -1;


    /**search - It will store the element to be searched
     * flag - If its 0 it means that the element is not found and if its 1 then it means that we have found the element.
     * n - Number of elements in the array
     * position - It will store the position at which the element is found.
     */


    scanf(" %d",&n);
    int array[n];
    int i;                //counter variable

    printf("Enter the elements of the array. \n");
    for(i =0;i<n;i++)
    {
        scanf(" %d",&array[i]);
    }
    printf("Enter the element to search.\n");
    scanf(" %d",&search);


    /*This is the linear search algorithm in c language*/
    
    for(i = 0;i<n;i++)
    {
        if(array[i]==search)
        {
            flag = 1;
            position = i+1;
            break;
        }
    }
    if(flag)
    {
        printf("Element found at position %d. \n",position);
    }
    else
    {
        printf("Element not found. \n");
    }
}
