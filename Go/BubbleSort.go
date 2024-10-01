package main

import "fmt"

// BubbleSort function that sorts an integer slice in ascending order
func BubbleSort(arr []int) {
    n := len(arr)
    for i := 0; i < n-1; i++ {
        // Flag to check if any swap happens
        swapped := false
        for j := 0; j < n-i-1; j++ {
            if arr[j] > arr[j+1] {
                // Swap arr[j] and arr[j+1]
                arr[j], arr[j+1] = arr[j+1], arr[j]
                swapped = true
            }
        }
        // If no elements were swapped, the array is already sorted
        if !swapped {
            break
        }
    }
}

func main() {
    arr := []int{64, 34, 25, 12, 22, 11, 90}
    fmt.Println("Unsorted array:", arr)
    BubbleSort(arr)
    fmt.Println("Sorted array:", arr)
}
