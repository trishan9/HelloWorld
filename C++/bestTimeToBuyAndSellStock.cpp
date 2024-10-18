
// problem link:-https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/description/


// You are given an array prices where prices[i] is the price of a given stock on the ith day.

// Find the maximum profit you can achieve. You may complete at most two transactions.

// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

 

// Example 1:

// Input: prices = [3,3,5,0,0,3,1,4]
// Output: 6
// Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
// Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
int find(int day,int trans ,int n,vector<int>&prices,vector<vector<int>>&dp){
    //base condition
    if(day==n || trans>3)return 0;
     
     //memoaization
     if(dp[day][trans]!=-1)return dp[day][trans];

    //option-01 if buy exists means we have to buy the stock
    int profit=0;
    if(trans%2==0){
        // so, we buy the stock so, we subtract the prices in our overall answer
    profit=max(-prices[day]+find(day+1,trans+1,n,prices,dp),find(day+1,trans,n,prices,dp));//we buy the stock and now we go for the sell so, buy becomes zero 
    // trans only compalte we do a complete buy and sell
    }
    else{//when buy becomes 0 so it means we need to sell it and 
    // and our ine transaction get completed so trans-1 
    //  now we need to buy it , so we make our buy to 1 
    profit=max(prices[day]+find(day+1,trans+1,n,prices,dp),find(day+1,trans,n,prices,dp));
// we go for next  day to sell it 

    }
return dp[day][trans]=profit;
}
int maxProfit(vector<int>& prices) {
int n=prices.size();
//find(day, no.of Transaction,size ,prices)
// 3D dp of day(0 to n) ,trans(1 to 4) (when 1 amd 3 we buy it else we sell it)
vector<vector<int>>dp(n+1,vector<int>(4,-1));
return find(0,0,n,prices,dp);
    }
};