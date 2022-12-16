#ifndef SERVER_H
#define SERVER_H

#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

// 1'000'007
using namespace std;

class Server
{
private:
    string Username, Password, credentials_file_path;
    int table_size = 1'000'007;
    string *table;

public:
    Server(string cfp)
    {
        credentials_file_path = cfp;
        table = new string[table_size];
        for (int i = 0; i < table_size; i++)
        {
            table[i] = "NULL";
        }

        fstream file(credentials_file_path, ios::in | ios::out);
        load_credentials();
        if (file.fail())
        {
            ofstream file(credentials_file_path);
            cout << "New Credentials File Created" << endl;
        }
        else
            cout << "Credintials File opened!" << endl;
        file.close();
    }
    ~Server()
    {
        delete[] table;
    }
    void load_credentials()
    {
        ifstream tempFile(credentials_file_path, ios::in);
        string indx, fileName;
        if (tempFile.is_open())
        {
            while (tempFile >> indx >> fileName)
                table[stoi(indx)] = fileName;
        }
        tempFile.close();
    }
    void store_credentials()
    {
        vector<int> tempV;
        ifstream tempFile(credentials_file_path, ios::in);
        string indx, fileName;
        if (tempFile.is_open())
        {
            while (tempFile >> indx >> fileName)
                tempV.push_back(stoi(indx));
        }
        ofstream file(credentials_file_path, ios_base::app);
        for (int i = 0; i < table_size; i++)
        {
            if (find(tempV.begin(), tempV.end(), i) == tempV.end())
            {
                if (table[i] != "NULL")
                    file << i << " " << to_string(i) + ".txt" << endl;
            }
        }
        tempFile.close();
        file.close();
    }
    int Hash(string un, string ps)
    {
        unsigned long long temp1 = 0;
        unsigned long long temp2 = 0;
        int result = 0;
        for (int i = 0; i < un.size(); i++)
        {
            temp1 = temp1 + (int(un[i]) * pow(263, i));
        }
        for (int i = 0; i < ps.size(); i++)
        {
            temp2 = temp2 + (int(ps[i]) * pow(263, i));
        }
        result = (temp1 + temp2) % table_size;
        return result;
    }
    bool insert_secret_notes(string un, string ps, string sN)
    {
        int indx = Hash(un, ps);
        try
        {
            fstream tempFile(to_string(indx) + ".txt");
            if (tempFile.fail())
            {
                cout << "Secret File created and secret note inserted!" << endl;
                ofstream tempFile(to_string(indx) + ".txt", ios::out | ios::trunc);
                table[indx] = to_string(indx) + ".txt";
                tempFile << sN << endl;
                tempFile.close();
            }
            else
            {
                cout << "Secret File opened and secret note inserted!" << endl;
                ofstream tempFile(to_string(indx) + ".txt", ios::app);
                tempFile << sN << endl;
                tempFile.close();
            }
            store_credentials();
            return 1;
        }
        catch (const std::exception &e)
        {
            cout<<"Error occured"<<endl;
            return 0;
        }
    }
    bool show_secret_notes(string un, string ps)
    {
        int indx = Hash(un, ps);
        if (table[indx] == "NULL")
        {
            cout << "Invalid credentials" << endl;
            return 0;
        }
        else
        {
            cout << "Username and passwords match for file: " << table[indx] << endl;
            ifstream tempFile(to_string(indx) + ".txt", ios::in);
            string secretNote;
            while (tempFile >> secretNote)
                cout << secretNote << endl;
            tempFile.close();
            return 1;
        }
    }
    void delete_secret_notes(string un, string ps)
    {
        int indx = Hash(un, ps);
        string deleteLine = to_string(indx) + " " + to_string(indx) + ".txt";
        string line;
        ifstream inFile(credentials_file_path);
        ofstream outFile("temp.txt");
        vector<string> tempV;
        try
        {
            while (getline(inFile, line))
                tempV.push_back(line);
            for (int i = 0; i < tempV.size(); i++)
            {
                if (tempV[i] != deleteLine)
                    outFile << tempV[i] << endl;
            }
            inFile.close();
            outFile.close();
            //
            // required conversion for remove function to work properly (from string to char array)
            // the previous conversions casted both file paths into char arrays
            const char oldName[] = "temp.txt";
            const char *x = credentials_file_path.c_str();
            const char *y = (to_string(indx) + ".txt").c_str();
            remove(x);
            rename(oldName, x);
            remove(y);
            cout << "Secrets have been deleted!" << endl;
        }
        catch (const std::exception &e)
        {
            cout << "Failed operation." << endl;
        }
    }
    void print()
    {
        for (int i = 0; i < table_size; i++)
        {
            if (table[i] != "NULL")
                cout << i << table[i] << " ";
        }
    }
};
#endif