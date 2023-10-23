package com.aditya;

public class ReverseNo {
    public static void main(String[] args) {
        System.out.println(rev(1234));
    }

    public static int rev(int n) {

        int digits =(int) (Math.log10(n) + 1);
        return helper(n,digits);
    }

    private static int helper(int n, int digits) {

        if(n==n%10){
            return n;
        }

        int rem = n%10;
        return (int) (rem*Math.pow(10,digits-1) + helper(n/10,digits-1));
    }
}