import java.util.Arrays;

public class InsertionSort {
    public static void main(String[] args) {
        int[] arr = {2, 55, 7, 4, 13, 17};
        // Calling the method
        InsertionSort(arr);
        System.out.println(Arrays.toString(arr));
    }

    // Method for Insertion Sort
    static void InsertionSort(int[] num){
        for (int i = 0; i < num.length-1; i++) {
            for (int j = i+1; j >0 ; j--) {
                if (num[j] < num[j-1]){
                    int temp = num[j];
                    num[j] = num[j-1];
                    num[j-1] = temp;
                }
                else {
                    break;
                }
            }
        }
    }
}