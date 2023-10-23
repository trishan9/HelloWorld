package main

import "fmt"

// Recursive function to calculate the factorial of a number
func factorial(n int) int {
    if n <= 1 {
        return 1
    }
    return n * factorial(n-1)
}

func main() {
    // Input a number for which you want to calculate the factorial
    var num int
    fmt.Print("Enter a number: ")
    fmt.Scanf("%d", &num)

    if num < 0 {
        fmt.Println("Factorial is not defined for negative numbers.")
    } else {
        result := factorial(num)
        fmt.Printf("The factorial of %d is %d\n", num, result)
    }
}
