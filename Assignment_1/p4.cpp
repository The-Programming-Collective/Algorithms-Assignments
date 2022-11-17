/*
Recurrence formula = 2T(n/2) + cn

Divide the array in two halves recurssively

Using the master method :

a = 2
b = 2 
d of f(n) = 1

n^log(b)a = n^log(2)2  == n^d = n^1

Both sides are equal so complexity = n^d*log(b)n = (n^1)*log(2)n == n log(n)
*/
#include<iostream>
using namespace std;

//Creating a struct sArr(SubArray) to track the
//max sum with its start and end
struct sArr{
    int sum;
    int start;
    int end;
};

//compares sArr sum and return the largest
sArr Max(sArr a, sArr b, sArr c){
    if(a.sum>=b.sum){
        if(a.sum>=c.sum)
            return a;
        return c;
    }
    else{
        if(b.sum>=c.sum)
            return b;
        return c;
    }
}

//finds the max crossing subArray from the midpoint
sArr getMaxCrossingSubArray(int nums[], int l,int m,int h){
    sArr sArr{0,0,0};
    int lSum=-99999;
    int sum=0;
    int tempLi,tempRi;

    //gets the max sub array from mid point
    //to the left
    for(int i=m; i>=l; i--){
        sum+=nums[i];
        if(sum>lSum){
            lSum=sum;
            tempLi=i;
        }
    }
    sArr.sum+=lSum;
    sArr.start=tempLi;

    sum=0;
    int rSum=-99999;

    //gets the max sub array from mid point
    //to the right
    for(int i=m+1; i<=h; i++){
        sum+=nums[i];
        if(sum>rSum){
            rSum=sum;
            tempRi=i;
        }
    }
    sArr.sum+=rSum;
    sArr.end=tempRi;
    return sArr;
}

//divides the array and gets the max subarray 
//from left and right and crossing
//while keeping the start and end indicies saved
sArr getMaxSumArr(int nums[], int l, int h){
    if(l==h)
        return sArr{nums[l],l,h};
    
    int m = (l+h)/2;
    sArr LMax = getMaxSumArr(nums, l, m);
    sArr RMax = getMaxSumArr(nums, m+1, h);
    sArr CMax = getMaxCrossingSubArray(nums, l, m, h);
    
    return Max(LMax, RMax, CMax);
}

int main(){
    int size;
    cout<<"Enter the array size : ";
    cin>>size;
    int* nums= new int[size];
    for(int i=0 ; i<size ; i++){
        cout<<"Element "<<i<<" : ";
        cin>>nums[i];
    }
    // int nums[]={-1,6,3,2,-1,2};
    // int size=6;

    //gets subArray start and end location and sum
    sArr ans = getMaxSumArr(nums,0,size-1);

    //creates the subarray
    int subArraySize = ans.end-ans.start+1;
    int subArray[subArraySize];
    for(int i=0,start=ans.start ; i<subArraySize ; i++ , start++)
        subArray[i]=nums[start];

    cout<<"Max sub array starts from "<<ans.start<<" ends at "<<ans.end<<" : [";
    for(int i=0 ; i<subArraySize ; i++){
        cout<<subArray[i]<<(i+1==subArraySize ? "]" : ",");
    }
}