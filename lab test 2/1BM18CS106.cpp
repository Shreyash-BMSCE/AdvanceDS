// PROGRAM NUMBER 2:
// Question : 
// Given a sequence of strings, write a program to find out the second most repeated/frequently
// occurring string in the given sequence. Consider that no two words are the second most
// repeated, there will be always a single word. Use hashing for implementation.
// Examples:
// Input : {"aaa", "bbb", "ccc", "bbb",
// "aaa", "aaa"}
// Output : bbb

#include <bits/stdc++.h>
using namespace std;
string freq_count(vector<string> &str)
{
    int freq1 = 0, freq2 = 0;
    unordered_map<string, int> table;
    for (int i = 0; i < str.size(); i++)
    {
        table[str[i]]++;
    }
    
    for (auto it : table)
    {
        freq1 = max(freq1, it.second);
        if (freq2 < it.second && it.second < freq1)
        {
            freq2 = it.second;
        }
    }
    for (auto it : table)
    {
        if (it.second == freq2)
        {
            return it.first;
        }
    }
}
int main()
{
    
    string s;
    int  n;
    vector<string> str;
    str.clear();
    cout<<"\n Enter the no. of elements :";
    cin>>n;
    cout<<"\n Enter the strings :";
    for(int i=0;i<n;i++)
    {
        cin >> s;
        str.push_back(s);
    }

    cout << "Second highest freq count is : " << freq_count(str) << "\n";
    return 0;
}