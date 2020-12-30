// Given an aay of N distinct elements, the task is to find all elements in aay except two greatest elements.

#include<bits/stdc++.h> 
#define MAX 50
void printsoln(int a[], int n) 
{ 
	std::sort(a, a + n); 
	for (int i = 0; i < n - 2; i++) 
	    std::cout << a[i] << " "; 
} 

int main() 
{
	int a[MAX]; 
    int t, n,c=1;
    //test cases
    std::cin>>t;
    do
    {
        std::cout<<"\nCase "<<c<<": ";
        c++;
        std::cin>>n;
        for(int i=0;i<n;i++)
            std::cin>>a[i];
        printsoln(a, n);
        t--;
    } while (t!=0);
	return 0; 
} 
