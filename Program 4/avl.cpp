#include<iostream>

using namespace std; 

class Avl 
{ 
	public: 
	int data; 
	Avl *left; 
	Avl *right; 
	int ht; 
}; 


int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

int ht(Avl *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->ht; 
} 



Avl* newAvl(int data) 
{ 
	Avl* _Avl = new Avl(); 
	_Avl->data = data; 
	_Avl->left = NULL; 
	_Avl->right = NULL; 
	_Avl->ht = 1; 
	return(_Avl); 
} 


Avl *rightRot(Avl *y) 
{ 
	Avl *x = y->left; 
	Avl *T2 = x->right; 

	
	x->right = y; 
	y->left = T2; 

	
	y->ht = max(ht(y->left), 
					ht(y->right)) + 1; 
	x->ht = max(ht(x->left), 
					ht(x->right)) + 1; 

	
	return x; 
} 


Avl *leftRot(Avl *x) 
{ 
	Avl *y = x->right; 
	Avl *T2 = y->left; 

	
	y->left = x; 
	x->right = T2; 


	x->ht = max(ht(x->left), 
					ht(x->right)) + 1; 
	y->ht = max(ht(y->left), 
					ht(y->right)) + 1; 


	return y; 
} 


int bal(Avl *N) 
{ 
	if (N == NULL) 
		return 0; 
	return ht(N->left) - 
		ht(N->right); 
} 

Avl* insert(Avl* _Avl, int data) 
{ 
	
	if (_Avl == NULL) 
		return(newAvl(data)); 

	if (data < _Avl->data) 
		_Avl->left = insert(_Avl->left, data); 
	else if (data > _Avl->data) 
		_Avl->right = insert(_Avl->right, data); 
	else 
		return _Avl; 

	
	_Avl->ht = 1 + max(ht(_Avl->left), 
						ht(_Avl->right)); 

	
	int balance = bal(_Avl); 

	
	
	if (balance > 1 && data < _Avl->left->data) 
		return rightRot(_Avl); 


	if (balance < -1 && data > _Avl->right->data) 
		return leftRot(_Avl); 

	
	if (balance > 1 && data > _Avl->left->data) 
	{ 
		_Avl->left = leftRot(_Avl->left); 
		return rightRot(_Avl); 
	} 

	
	if (balance < -1 && data < _Avl->right->data) 
	{ 
		_Avl->right = rightRot(_Avl->right); 
		return leftRot(_Avl); 
	} 

	
	return _Avl; 
} 


Avl * minAvl(Avl* _Avl) 
{ 
	Avl* current = _Avl; 


	while (current->left != NULL) 
		current = current->left; 

	return current; 
} 


Avl* del(Avl* root, int data) 
{ 
	
	
	if (root == NULL) 
		return root; 

	
	if ( data < root->data ) 
		root->left = del(root->left, data); 

	
	else if( data > root->data ) 
		root->right = del(root->right, data); 

	
	else
	{ 
		
		if( (root->left == NULL) || 
			(root->right == NULL) ) 
		{ 
			Avl *temp = root->left ? 
						root->left : 
						root->right; 

			
			if (temp == NULL) 
			{ 
				temp = root; 
				root = NULL; 
			} 
			else 
			*root = *temp; 
						
			free(temp); 
		} 
		else
		{ 
			
			Avl* temp = minAvl(root->right); 

			
			root->data = temp->data; 

			
			root->right = del(root->right, 
									temp->data); 
		} 
	} 

	
	if (root == NULL) 
	return root; 

	
	root->ht = 1 + max(ht(root->left), 
						ht(root->right)); 

	
	int balance = bal(root); 

	
	
	if (balance > 1 && 
		bal(root->left) >= 0) 
		return rightRot(root); 

	
	if (balance > 1 && 
		bal(root->left) < 0) 
	{ 
		root->left = leftRot(root->left); 
		return rightRot(root); 
	} 

	
	if (balance < -1 && 
		bal(root->right) <= 0) 
		return leftRot(root); 

	
	if (balance < -1 && 
		bal(root->right) > 0) 
	{ 
		root->right = rightRot(root->right); 
		return leftRot(root); 
	} 

	return root; 
} 


void output(Avl *root) 
{ 
	if(root != NULL) 
	{ 
		cout << root->data << " "; 
		output(root->left); 
		output(root->right); 
	} 
} 


int main() 
{ 
	Avl *root = NULL; 
	int ch=0,n,data;
	while(ch!=3)
	{
		cout<<"\n Enter choice: 1. Insert 2.Delete 3.Exit :";
		cin>>ch;
		if (ch==1)
		{
			cout<<"\n Enter n:";
			cin>>n;
			for(int i=0;i<n;i++)
			{
				cout<<"\nEnter data: ";
				cin>>data;
				root = insert(root, data);  
			}
		}

		else if(ch==2)
		{
			cout<<"\n Enter data to delete:";
			cin>>data;
			root = del(root, data);
		}
		
		cout << "AVL tree is \n"; 
		output(root);
	}
	return 0; 
} 


