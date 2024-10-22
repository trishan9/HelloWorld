/**First of all lets understand what is binary search.
 * In this algorithm the array taken as input is pre-sorted in any order. 
 * 1- First of all we compare the search element with the element of the array.If its true then the search is complete.
 * 2-If its not , then if the search element is greater than the middle element then for the next time we will search only in the array starting
 * from the (mid+1) index and ending at the upperbound of the array.Here mid is the index of the middle element
 * 3 - If its less than the middle element then we will search in the array starting at the lowerbound of the array and ending at the index
 * (mid+1). 
 * 4- Thus every time we search in half the array of the previous array.
 * 5- Its time complexity is O(log n) which means that its a very efficient algorithm.
 * 
 * */

#include <stdio.h>
int main()
{
    int n,search =0,i = 0,flag = 0;
    /*n = Number of elements in the array.
      search = The element to search for.
      i  = The counter variable.
      flag = 0 if the element is not found and 1 if the element has been found*/

    printf("Enter the number of elements in the array.\n");
    scanf(" %d",&n);

    //Creating an array having n elements.

    int array[n];

    //Taking input into the array elements.

    printf("Enter the elements into the array in ascending order.\n");
    for(i = 0;i<n;i++)
    {
        scanf(" %d",&array[i]);
    }
    
    /*I have assumed that the array is initially sorted in ascending order . If its not sorted we can sort it using any sorting technique.Here
    I am only going to show you how the binary search actually works.*/

    printf("Enter the element to search for.\n");
    scanf(" %d",&search);
    int l = 0,u = n-1,m = (l+u)/2;

    //l = Lower bound of the array to search in.
    //u = Upper bound of the array to search in.
    //m = Middle element of the array with which we have to compare the search element.
    while(l<=u)
    {
        /*if the search element is greater than the middle element then we will search in the array starting
         from the (m+1) index and ending at the upperbound (u) of the array.*/
        
        if(search > array[m])
        {
            l= m+1;
        }

        /*If the search element is less than the middle element then we will search in the array starting at the lowerbound (l) of the array and 
        ending at the index (m+1). */

        else if(search < array[m])
        {
            u = m-1;
        }

        /*If the search element is equal to the middle element of the array then the search is complete.*/

        else
        {
            flag = 1;
            break;
        }
        //Reinitializing m for the next search.
        m = (l+u)/2;
    }
    if(flag)
    {
        printf("Element %d found at position %d.\n",search,m+1);
    }
    else
    {
        printf("Element not found");
    }
    

}
