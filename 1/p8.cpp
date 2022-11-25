#include<iostream>

using namespace std;

int Merge(int arr[],int l,int m,int r){
    int i=l , j=m+1 ,k=l;
    int temp[r+1];
    int counter = 0;
    while (i<=m && j<=r){
        if(arr[i]>arr[j]){
            counter+=(m+1)-i;
            temp[k++]=arr[j++];
        }
        else{
            temp[k++]=arr[i++];
        }
    }

    while(i<=m)
        temp[k++]=arr[i++];

    while(j<=r)
        temp[k++]=arr[j++];

    for(int n=l ; n<=r ; n++)
        arr[n]=temp[n];

    return counter; 
}

//Basically mergesort
int InverseCount(int arr[] , int l , int r){
    int counter=0;
    if(l<r){
    int mid = (l+r)/2;
    counter += InverseCount(arr,l,mid);
    counter += InverseCount(arr,mid+1,r);
    counter += Merge(arr,l,mid,r);
    }
    return counter;
}

int main(){
    int Size;
    cout<<"Enter the array size : ";
    cin>>Size;
    int* arr= new int[Size];
    for(int i=0 ; i<Size ; i++){
        cout<<"Element "<<i<<" : ";
        cin>>arr[i];
    }
    //int arr[]={10, 10, 10};
    //int Size=sizeof(arr)/sizeof(int);
    cout<<"Inverse count : "<<InverseCount(arr,0,Size-1);
}