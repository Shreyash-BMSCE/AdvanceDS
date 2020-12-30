
#include<bits/stdc++.h> 

void printsoln(int l, int r) 
{ 
    for (int i=l ; i<=r ; i++) 
    { 
        int n = i; 
        int arr[10] = {0}; 
        while (n) 
        { 
            if (arr[n % 10]) 
                break; 
            arr[n%10] = 1; 
            n = n/10; 
        }  
        if (n == 0) 
            std::cout << i << " "; 
    } 
} 

int main() 
{ 
    int l, r; 
    std::cin>>l;
    std::cin>>r;
    printsoln(l, r); 
    return 0; 
} 