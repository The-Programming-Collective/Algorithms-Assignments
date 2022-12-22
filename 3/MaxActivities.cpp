#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <vector>

bool pairSort(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return (a.second < b.second);
}

void findMaxActivities(std::pair<int, int> *arr, int s)
{
    int size = s;
    std::vector<std::pair<int, int>> vecTemp;
    std::vector<std::pair<int, int>> resultVec;
    for (int i = 0; i < size; i++)
    {
        vecTemp.push_back(arr[i]);
    }
    std::sort(vecTemp.begin(), vecTemp.end(), pairSort);
    resultVec.push_back(vecTemp[0]);
    for (int i = 1; i < size; i++)
    {
        if (vecTemp[i].first > resultVec[resultVec.size() - 1].second)
        {
            resultVec.push_back(vecTemp[i]);
        }
    }
    std::cout<<std::endl;
    std::cout << "Max Activities Number  = " << resultVec.size() << std::endl;
    for (int i = 0; i < resultVec.size(); i++)
    {
        std::cout << "{" << resultVec[i].first << "," << resultVec[i].second << "} ";
    }
}

int main()
{
    int size;
    std::cout<<"Enter number of activities: ";
    std::cin>>size;
    std::pair<int, int> arr[size];
    for (int i = 0; i < size; i++)
    {
        std::cout<<"Enter start time of activity "<<i+1<<": ";
        std::cin>>arr[i].first;
        std::cout<<"Enter finishing time of activity "<<i+1<<": ";
        std::cin>>arr[i].second;
    }
    

    findMaxActivities(arr, size);
    return 0;
}
