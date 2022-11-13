#include <iostream>
#include <stdio.h>
#include <vector>
#include<bits/stdc++.h>
using namespace std;

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

int KthLargest(int arr[], int start, int end, int k)
{
    // Checking if user input(k) falls within the indexes in the array.
    // Example if indexes are : 0 1 2 3, k can have values: 1,2,3,4 (4 = 3-0+1)
    //if (k > 0 && k <= end - start + 1)
    {
        // Partition the array around last element and get
        // position of pivot element in sorted array
        int position = partition(arr, start, end);
        // If position value is same as k
        if (position - start == k - 1)
            return arr[position];
        // If position value is more, recur for left subarray
        if (position - start > k - 1)
            return KthLargest(arr, start, position - 1, k);
        // Else recur for right subarray
        return KthLargest(arr, position + 1, end, k - position + start - 1);
    }
    // If k is more than number of elements in array
    return -1;
}

int main()
{
    //used to filter duplicates from the input array
    // int s,x;
    // vector<int> tmp;
    // cout<<"Enter the size of the array : ";
    // cin>>s;
    // for(int i=0 ; i<s ; i++){
    //     cout<<"Enter element "<<i<<" : ";
    //     cin>>x;
    //     if(find(tmp.begin(),tmp.end(),x)==tmp.end())
    //         tmp.push_back(x);
    // }

    // int n=tmp.size(),k;
    // int a[n];
    // for(int i=0 ; i<n ; i++){
    //     a[i]=tmp[i];
    // }
    // do{
    // cout<<"Enter Kth element to find (1-"<<n<<") : ";
    // cin>>k;
    // }while(k>n);
    int k=3;
	int a[]={14,5,6,12,8,10,25};
    //5 ,6 ,8 ,10 ,12 ,14 ,25
	int Size = 7;
    cout <<k<<" Largest element is : "<< KthLargest(a, 0, Size - 1, k);
    return 0;
}