// using union-find algo
 
#include<iostream>
#include<vector>


using namespace std;
class UnionFind
{ 
	int n; 
	vector<int> r,par;
	public: 
	UnionFind(int n) 
	{ 
		r.resize(n); 
		par.resize(n); 
		this->n = n; 
		for (int i = 0; i < n; i++) 
			par[i] = i;
	}
    void Union(int x, int y)
	{ 
		int a = find(x); 
		int b = find(y); 

		if (a == b) 
			return; 

		if (r[a] < r[b]) 
			par[a] = b; 

		else if (r[b] < r[a]) 
			par[b] = a; 

		else {
			par[b] = a; 
			r[a] = r[a] + 1; 
		} 
	} 
	int find(int x) 
	{ 
		if (par[x] != x) 
		{ 
			return find(par[x]); 
		} 
		return x; 
	} 
}; 

int island(vector<vector<int>>a) 
{ 
	int n = a.size(); 
	int m = a[0].size(); 
    int root;
	UnionFind *temp = new UnionFind(n * m); 
	for (int j = 0; j < n; j++) 
    { 
		for (int k = 0; k < m; k++) 
		{ 
			if (!a[j][k]) 
				continue; 
            root = j * (m) + k;
			if (j + 1 < n && a[j + 1][k])     //checking all 8 sides 
				temp->Union(root, (j + 1) * m + k); 
			if (j - 1 >= 0 && a[j - 1][k]) 
				temp->Union(root, (j - 1) * m + k); 
			if (k + 1 < m && a[j][k + 1]) 
				temp->Union(root, (j) * m + k + 1); 
			if (k - 1 >= 0 && a[j][k - 1]) 
				temp->Union(root, (j) * m + k - 1); 
			if (j + 1 < n && k + 1 < m && a[j + 1][k + 1]) 
				temp->Union(root, (j + 1) * m + k + 1); 
			if (j + 1 < n && k - 1 >= 0 && a[j + 1][k - 1]) 
				temp->Union(root, (j + 1) * m + k - 1); 
			if (j - 1 >= 0 && k + 1 < m && a[j - 1][k + 1]) 
				temp->Union(root, (j - 1) * m + k + 1); 
			if (j - 1 >= 0 && k - 1 >= 0 && a[j - 1][k - 1]) 
				temp->Union(root, (j - 1) * m + k - 1); 
		} 
	} 
	int *f = new int[n * m];    // by default all frequencies are taken as zero 
	int count = 0; 
	for (int i = 0; i < n; i++) 
	{ 
		for (int j = 0; j < m; j++) 
		{ 
			if (a[i][j] == 1) 
			{ 
				int x = temp->find(i*m + j); 
				if (f[x] == 0) 
				{ 
					count++; 
					f[x]++;
					//cout<<"here" ;
				} 
				else
					f[x]++; 
			} 
		} 
	} 
	return count; 
} 

int main(void) 
{ 
	vector<vector<int>>a; //={{1, 1, 0, 0, 0}, 
    //                                  {0, 1, 0, 0, 1}, 
    //                                  {1, 0, 0, 1, 1}, 
    //                                  {0, 0, 0, 0, 0}, 
    //                                  {1, 0, 1, 0, 1}}; 

	int n,m,num;
	cout<<"No of rows : ";
	cin>>n;
	cout<<"No of cols : ";
	cin>>m;
	for(int i=0;i<n;i++)
	{
		vector<int> v1;
		for(int j=0;j<m;j++)
		{
			cin>>num;
			v1.push_back(num);
		}
		a.push_back(v1);
	}
	cout << "Number of Islands is: "<< island(a); 
} 
