import java.util.Arrays;
public class CyclicSort {
    public static void main(String[] args) {
     int[] arr = {3, 5, 2, 1, 4};
        cyclicSort(arr);
        System.out.println(Arrays.toString(arr));
    }
    
    static void cyclicSort(int[] num){
            int i = 0;
            while(i < num.length) {
            int correct = num[i] - 1;
                if (num[i] != num[correct]){
                    swap(num, i , correct);
                }
                else {
                    i++;
                }
            }
    }

    static void swap(int [] num , int first , int second){
        int temp = num[first];
        num[first] = num[second];
        num[second] = temp;
    }
}
