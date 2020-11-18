
#include<iostream> 
using namespace std; 

 
class TreeChild 
{ 
	int *keys; 
	int t;	 
	TreeChild **C;
	int n;	
	bool leaf; 
public: 
	TreeChild(int _t, bool _leaf); 
	void insertnotfull(int k); 
	void splitChild(int i, TreeChild *y); 
	void traverse(); 

	TreeChild *search(int k); 


friend class Tree; 
}; 


class Tree 
{ 
	TreeChild *root; 
	int t; 
public: 
	
	Tree(int _t) 
	{ root = NULL; t = _t; } 

	
	void traverse() 
	{ if (root != NULL) root->traverse(); } 

	
	TreeChild* search(int k) 
	{ return (root == NULL)? NULL : root->search(k); } 

	
	void insertion(int k); 
}; 


TreeChild::TreeChild(int t1, bool leaf1) 
{ 

	t = t1; 
	leaf = leaf1; 

	
	keys = new int[2*t-1]; 
	C = new TreeChild *[2*t]; 

	n = 0; 
} 


void TreeChild::traverse() 
{ 
	
	int i; 
	for (i = 0; i < n; i++) 
	{ 
		
		if (leaf == false) 
			C[i]->traverse(); 
		cout << " " << keys[i]; 
	} 

	
	if (leaf == false) 
		C[i]->traverse(); 
} 


TreeChild *TreeChild::search(int k) 
{ 
	
	int i = 0; 
	while (i < n && k > keys[i]) 
		i++; 

	if (keys[i] == k) 
		return this; 

	if (leaf == true) 
		return NULL; 

	return C[i]->search(k); 
} 

void Tree::insertion(int k) 
{ 
	
	if (root == NULL) 
	{ 
		
		root = new TreeChild(t, true); 
		root->keys[0] = k; 
		root->n = 1; 
	} 
	else 
	{ 
		
		if (root->n == 2*t-1) 
		{ 
			
			TreeChild *s = new TreeChild(t, false); 

			
			s->C[0] = root; 

			
			s->splitChild(0, root); 

			
			int i = 0; 
			if (s->keys[0] < k) 
				i++; 
			s->C[i]->insertnotfull(k); 

			
			root = s; 
		} 
		else 
			root->insertnotfull(k); 
	} 
} 

void TreeChild::insertnotfull(int k) 
{ 
	
	int i = n-1; 


	if (leaf == true) 
	{ 
		
		while (i >= 0 && keys[i] > k) 
		{ 
			keys[i+1] = keys[i]; 
			i--; 
		} 

		
		keys[i+1] = k; 
		n = n+1; 
	} 
	else 
	{ 
		
		while (i >= 0 && keys[i] > k) 
			i--; 

	
		if (C[i+1]->n == 2*t-1) 
		{ 
		
			splitChild(i+1, C[i+1]); 

			if (keys[i+1] < k) 
				i++; 
		} 
		C[i+1]->insertnotfull(k); 
	} 
} 


void TreeChild::splitChild(int i, TreeChild *y) 
{ 
	
	TreeChild *z = new TreeChild(y->t, y->leaf); 
	z->n = t - 1; 
	for (int j = 0; j < t-1; j++) 
		z->keys[j] = y->keys[j+t]; 
	if (y->leaf == false) 
	{ 
		for (int j = 0; j < t; j++) 
			z->C[j] = y->C[j+t]; 
	} 

	
	y->n = t - 1; 

	for (int j = n; j >= i+1; j--) 
		C[j+1] = C[j]; 

	
	C[i+1] = z; 

	for (int j = n-1; j >= i; j--) 
		keys[j+1] = keys[j]; 

	keys[i] = y->keys[t-1]; 

	n = n + 1; 
} 

int main() 
{
    int n,k,o;
    cout<<"Enter the order :";
    cin>>o;
    Tree t(o); 
	cout<<"Enter the number of elements : ";
	cin>>n;
	cout<<"Enter the elements : ";
	for(int i=0; i<n; i++)
	{
		cin>>k;
		t.insertion(k);
	}
	cout << "\n The tree constructed is : \n";
    t.traverse();
	return 0; 
} 
