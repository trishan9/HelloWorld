package main

import "fmt"

func BinarySearch(target int, nums []int) int {
    low, high := 0, len(nums) - 1
    for low < high {
        mid := low + (high - low ) / 2
        if nums[mid] == target{
            return mid
        }else if nums[mid] < target {
            low = mid + 1
        }else {
            high = mid - 1
        }
    }
    return -1
}


func main(){

    numbers := []int{7, 8, 9, 10, 11}
    target := 9
    result := BinarySearch(target,  numbers)

    if result == -1 {
        fmt.Println("Target not found in the numbers array")
    }
    fmt.Printf("Target '%d' found at index %d", target, result)
}

