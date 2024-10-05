package main

import (
    "fmt"
)

func main() {
    var num1, num2 float64
    var operator string

    fmt.Print("Enter first number: ")
    fmt.Scanln(&num1)

    fmt.Print("Enter an operator (+, -, *, /): ")
    fmt.Scanln(&operator)

    fmt.Print("Enter second number: ")
    fmt.Scanln(&num2)

    // Check if both numbers are integers
    isNum1Int := num1 == float64(int(num1))
    isNum2Int := num2 == float64(int(num2))

    var result float64
    switch operator {
    case "+":
        result = num1 + num2
    case "-":
        result = num1 - num2
    case "*":
        result = num1 * num2
    case "/":
        if num2 != 0 {
            result = num1 / num2
        } else {
            fmt.Println("Error: Division by zero")
            return
        }
    default:
        fmt.Println("Error: Invalid operator")
        return
    }

    // Format output
    if isNum1Int && isNum2Int {
        fmt.Printf("%d %s %d = ", int(num1), operator, int(num2))
    } else {
        fmt.Printf("%.2f %s %.2f = ", num1, operator, num2)
    }
    
    // Display the result
    if result == float64(int(result)) {
        fmt.Println(int(result))
    } else {
        fmt.Printf("%.2f \n",result)
    }
}
