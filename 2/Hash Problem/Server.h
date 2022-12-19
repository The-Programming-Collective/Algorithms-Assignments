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

    // Destructor
    ~Server()
    {
        delete[] table;
    }

    // Function to load credentials from an existing credential file
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

    // Function to store all new or changed credentials in the credentials file
    void store_credentials()
    {
        vector<int> tempV;
        ifstream tempFile(credentials_file_path, ios::in);
        string indx, fileName;

        // Takes all credential file content and checks for change
        // In order to only appends new credentials
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

    // Hash function to return a hashed index from username and password
    int Hash(string un, string ps)
    {
        unsigned long long int temp1 = 0;
        unsigned long long int temp2 = 0;
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

    /*!
     * @function    Insert a secret note.
     *
     * @brief       This function takes a user name and password
     *              and creates a file if a file doesnt already exist
     *              and inserts a secret note into it.
     *
     * @param       un    Username for an account.
     * @param       ps    Password for account.
     * @param       sN    Secret note to be inserted.
     *
     */
    void insert_secret_notes(string un, string ps, string sN)
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
        }
        catch (const std::exception &e)
        {
            cout << "Error occured" << endl;
        }
    }

    /*!
     * @function    Show secret note contents
     *
     * @brief       This function takes a user name and password
     *              and if the credentials match an account
     *              presents its contents.
     *
     * @param       un    Username for an account.
     * @param       ps    Password for account.
     *
     */
    void show_secret_notes(string un, string ps)
    {
        int indx = Hash(un, ps);
        if (table[indx] == "NULL")
        {
            cout << "Invalid credentials" << endl;
        }
        else
        {
            cout << "Username and passwords match for file: " << table[indx] << endl;
            ifstream tempFile(to_string(indx) + ".txt", ios::in);
            string secretNote;
            cout << "Contents: " << endl;
            while (tempFile >> secretNote)
                cout << secretNote << endl;
            tempFile.close();
        }
    }

    /*!
     * @function    Delete a secret note
     *
     * @brief       This function takes a user name and password
     *              and deletes the file containing the secret
     *              and updates the credentials file
     *
     * @param       un    Username for an account.
     * @param       ps    Password for account.
     *
     */
    void delete_secret_notes(string un, string ps)
    {
        int indx = Hash(un, ps);
        if (table[indx] != "NULL")
        {
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

                // Required conversion for remove function to work properly (from string to char array)
                // The previous conversions casted both file paths into char arrays
                // The conversions were used to delete the secret file and update the credentials file
                const char oldName[] = "temp.txt";
                const char *x = credentials_file_path.c_str();
                const char *y = (to_string(indx) + ".txt").c_str();
                remove(x);
                rename(oldName, x);
                remove(y);
                table[indx] = "NULL";
                cout << "Secrets have been deleted!" << endl;
            }
            catch (const std::exception &e)
            {
                cout << "Failed operation." << endl;
            }
        }
        else
        {
            cout << "Failed operation." << endl;
        }
    }

    // print function for testing
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