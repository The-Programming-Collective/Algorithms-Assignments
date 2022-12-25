#include<iostream>
using namespace std;

string LPsubString(string word){

    int start = 1;
    int length = 1;
    bool matrix[word.size()][word.size()];

    //initial state of the matrix
    //each 1 char is a palindrome on its own
    for(int i=0 ; i<word.size() ; i++){
        for(int j=0 ; j<word.size() ; j++){
            if(i==j)
                matrix[i][j]=1;
            else
                matrix[i][j]=0;
        }
    }

    //check if the next char is the same as the first
    //if so then make it true
    for(int i=0 ; i<word.size()-1 ; i++){
        if(word[i]==word[i+1]){
            matrix[i][i+1]=1;
            length=2;
            start=i;
        }
    }

    //check from 3 to the end of the string
    for (int subSize = 3; subSize <= word.size(); subSize++) {

        for (int subStart = 0; subStart < word.size() - subSize + 1; subStart++) {
            int subEnd = subStart + subSize - 1;

            if (matrix[subStart + 1][subEnd - 1] && word[subStart] == word[subEnd]) {
                matrix[subStart][subEnd] = true;

                if (subSize > length) {
                    start = subStart;
                    length = subSize;
                }
            }
        }
    }
    return word.substr(start,length);
}



int main(){
    string s = "cbbd";
    cout<<"Enter string: ";
    cin>>s;
    cout<<"Max palindromic substring: "<<LPsubString(s);
}