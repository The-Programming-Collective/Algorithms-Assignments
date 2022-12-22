#include <bits/stdc++.h>
#include <iostream>
#include <utility>
#include <vector>

// Function that compares between the activities finishing times
bool pairSort(const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return (a.second < b.second);
}

// Main max activities algorithm
void findMaxActivities(std::pair<int, int> *arr, int s)
{
    int size = s;
    std::vector<std::pair<int, int>> vecTemp;
    std::vector<std::pair<int, int>> resultVec;

    // Creating a temp vector with all activities and sorting based on finishing time
    for (int i = 0; i < size; i++)
    {
        vecTemp.push_back(arr[i]);
    }
    std::sort(vecTemp.begin(), vecTemp.end(), pairSort);

    // Creating the result vector with all the activities that fit the condition
    resultVec.push_back(vecTemp[0]);
    for (int i = 1; i < size; i++)
    {
        // Checks if the start time for the next activity is greater than or equal to the finishing time for the previous one
        // in order to add it into the result vector
        if (vecTemp[i].first >= resultVec[resultVec.size() - 1].second)
        {
            resultVec.push_back(vecTemp[i]);
        }
    }

    // Print results
    std::cout << std::endl;
    std::cout << "Max Activities Number  = " << resultVec.size() << std::endl;
    for (int i = 0; i < resultVec.size(); i++)
    {
        std::cout << "{" << resultVec[i].first << "," << resultVec[i].second << "} ";
    }
}

int main()
{
    int size;
    std::cout << "Enter number of activities: ";
    std::cin >> size;
    std::pair<int, int> arr[size];

    //Assinment document example
    // std::pair<int, int> arr[] = {{1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}};
    
    for (int i = 0; i < size; i++)
    {
        std::cout << "Enter start time of activity " << i + 1 << ": ";
        std::cin >> arr[i].first;
        std::cout << "Enter finishing time of activity " << i + 1 << ": ";
        std::cin >> arr[i].second;
    }

    findMaxActivities(arr, size);
    return 0;
}
