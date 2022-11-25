#include <iostream>
#include <stdio.h>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

//partition the array descending around the last element as pivot
int partition(int arr[], int start, int end){
    int i = start, j, x = arr[end], temp;
    for (j = start ; j < end ; j++){
        if (arr[j] >= x){
            temp = arr[i];
            arr[i++] = arr[j];
            arr[j] = temp;
        }
    }
    temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
    return i;
}

int KthLargest(int arr[], int start, int end, int k){
    // position of sorted pivot array
    int position = partition(arr, start, end);
    // If position value is same as k (base case)
    if (position - start == k - 1)
        return arr[position];
    // If position value is more, recur for left subarray
    if (position - start > k - 1)
        return KthLargest(arr, start, position - 1, k);
    // Else recur for right subarray
    return KthLargest(arr, position + 1, end, k - position + start - 1);
}

int main(){
    //used to filter duplicates from the input array
    int s,x;
    vector<int> tmp;
    cout<<"Enter the size of the array : ";
    cin>>s;
    for(int i=0 ; i<s ; i++){
        cout<<"Enter element "<<i<<" : ";
        cin>>x;
        if(find(tmp.begin(),tmp.end(),x)==tmp.end())
            tmp.push_back(x);
    }
    int Size=tmp.size(),k;
    int a[Size];
    for(int i=0 ; i<Size ; i++){
        a[i]=tmp[i];
    }

    do{
    cout<<"Enter Kth element to find (1-"<<Size<<") : ";
    cin>>k;
    }while(k>Size);
    // int k=5;
	// int a[]={18,15,3,1,2,6,16};
    // //5 ,6 ,8 ,10 ,12 ,14 ,25
	// int Size = 7;
    cout <<k<<" Largest element is : "<< KthLargest(a, 0, Size - 1, k);
}