#include<iostream>
using namespace std;

string LPsubString(string word){

    //keeps track of the start index and the length of the palindrome subString
    int start = 0;
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
    for (int subLength = 3; subLength <= word.size(); subLength++) {

        //check from the subStart to subEnd
        for (int subStart = 0; subStart < word.size() - subLength + 1; subStart++) {
            int subEnd = subStart + subLength - 1;

            //if start and end chars are equal
            //and if the middle part is a palindrome
            if (word[subStart] == word[subEnd] && matrix[subStart + 1][subEnd - 1]) {
                matrix[subStart][subEnd] = true;

                //if a longer palindromic subString is found
                //set the start and the length
                if (subLength > length) {
                    start = subStart;
                    length = subLength;
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