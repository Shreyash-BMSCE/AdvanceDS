
#include <iostream>
using namespace std;

class TreeNode {
  int *keys;   //array of keys
  TreeNode **child;  //child array
  int n;    //current keys
  bool leaf;   //node is leaf or not

   public:
            TreeNode(bool _leaf);
            void traverse();    
            void insertNotFull(int k);    // insert when not full 
            void splitChild(int i, TreeNode *y);   // split child from middle 
            void removeNode(int k);    
            void fill(int idx);    // fill keys if lesser than req 
            void getPrevChild(int idx);  // borrow child from prev node
            void getNextChild(int idx);  // borrow child from next node
            void merge(int idx);  
            friend class Tree;
};

class Tree {
  TreeNode *root = NULL;
  int t;

  public:
          void traverse() {
            if (root != NULL)
              root->traverse();
          }

          void insertion(int k);

          void removeNode(int k);
};


TreeNode::TreeNode(bool leaf1) {
  leaf = leaf1;

  keys = new int[3];
  child = new TreeNode *[4];

  n = 0;
}




void TreeNode::removeNode(int k) {
  int idx = 0;
  while (idx < n && keys[idx] < k)
    ++idx;

  if (idx < n && keys[idx] == k) {
    if (leaf)
    {
        for (int i = idx + 1; i < n; ++i)
            keys[i - 1] = keys[i];
        n--;
    }
    else
    {
        int k = keys[idx];

        if (child[idx]->n >= 2) {
            TreeNode *cur = child[idx];
            while (!cur->leaf)
                cur = cur->child[cur->n];
            int pred = cur->keys[cur->n - 1];
            keys[idx] = pred;
            child[idx]->removeNode(pred);
        }

        else if (child[idx + 1]->n >= 2) {
            TreeNode *cur = child[idx + 1];
            while (!cur->leaf)
                cur = cur->child[0];
            int succ = cur->keys[0];
            keys[idx] = succ;
            child[idx + 1]->removeNode(succ);
        }

        else {
            merge(idx);
            child[idx]->removeNode(k);
        }
    }  
  } 
  else {
    if (leaf) {
      cout << "The key " << k << " is does not exist in the tree\n";
      return;
    }

    bool flag = ((idx == n) ? true : false);

    if (child[idx]->n < 2)
      fill(idx);

    if (flag && idx > n)
      child[idx - 1]->removeNode(k);
    else
      child[idx]->removeNode(k);
  }
  return;
}



void TreeNode::fill(int idx) {
  if (idx != 0 && child[idx - 1]->n >= 2)
    getPrevChild(idx);

  else if (idx != n && child[idx + 1]->n >= 2)
    getNextChild(idx);

  else {
    if (idx != n)
      merge(idx);
    else
      merge(idx - 1);
  }
  return;
}


void TreeNode::getPrevChild(int idx) {
  TreeNode *childnew = child[idx];
  TreeNode *sibling = child[idx - 1];

  for (int i = childnew->n - 1; i >= 0; --i)
    childnew->keys[i + 1] = childnew->keys[i];

  if (!childnew->leaf) {
    for (int i = childnew->n; i >= 0; --i)
      childnew->child[i + 1] = childnew->child[i];
  }

  childnew->keys[0] = keys[idx - 1];

  if (!childnew->leaf)
    childnew->child[0] = sibling->child[sibling->n];

  keys[idx - 1] = sibling->keys[sibling->n - 1];

  childnew->n += 1;
  sibling->n -= 1;

  return;
}


void TreeNode::getNextChild(int idx) {
  TreeNode *childnew = child[idx];
  TreeNode *sibling = child[idx + 1];

  childnew->keys[(childnew->n)] = keys[idx];

  if (!(childnew->leaf))
    childnew->child[(childnew->n) + 1] = sibling->child[0];

  keys[idx] = sibling->keys[0];

  for (int i = 1; i < sibling->n; ++i)
    sibling->keys[i - 1] = sibling->keys[i];

  if (!sibling->leaf) {
    for (int i = 1; i <= sibling->n; ++i)
      sibling->child[i - 1] = sibling->child[i];
  }

  childnew->n += 1;
  sibling->n -= 1;

  return;
}


void TreeNode::merge(int idx) {
  TreeNode *childnew = child[idx];
  TreeNode *sibling = child[idx + 1];

  childnew->keys[1] = keys[idx];

  for (int i = 0; i < sibling->n; ++i)
    childnew->keys[i + 2] = sibling->keys[i];

  if (!childnew->leaf) {
    for (int i = 0; i <= sibling->n; ++i)
      childnew->child[i + 2] = sibling->child[i];
  }

  for (int i = idx + 1; i < n; ++i)
    keys[i - 1] = keys[i];

  for (int i = idx + 2; i <= n; ++i)
    child[i - 1] = child[i];

  childnew->n += sibling->n + 1;
  n--;

  delete (sibling);
  return;
}


void Tree::insertion(int k) {
  if (root == NULL) {
    root = new TreeNode(true);
    root->keys[0] = k;
    root->n = 1;
  } else {
    if (root->n == 3) {
      TreeNode *s = new TreeNode(false);

      s->child[0] = root;

      s->splitChild(0, root);

      int i = 0;
      if (s->keys[0] < k)
        i++;
      s->child[i]->insertNotFull(k);

      root = s;
    } 
    else
      root->insertNotFull(k);
  }
}


void TreeNode::insertNotFull(int k) {
  int i = n - 1;

  if (leaf == true) {
    while (i >= 0 && keys[i] > k) {
      keys[i + 1] = keys[i];
      i--;
    }

    keys[i + 1] = k;
    n = n + 1;
  } else {
    while (i >= 0 && keys[i] > k)
      i--;

    if (child[i + 1]->n == 3) {
      splitChild(i + 1, child[i + 1]);

      if (keys[i + 1] < k)
        i++;
    }
    child[i + 1]->insertNotFull(k);
  }
}


void TreeNode::splitChild(int i, TreeNode *y) {
  TreeNode *z = new TreeNode(y->leaf);
  z->n = 1;

  for (int j = 0; j < 1; j++)
    z->keys[j] = y->keys[j + 2];

  if (y->leaf == false) {
    for (int j = 0; j < 2; j++)
      z->child[j] = y->child[j + 2];
  }

  y->n = 1;

  for (int j = n; j >= i + 1; j--)
    child[j + 1] = child[j];

  child[i + 1] = z;

  for (int j = n - 1; j >= i; j--)
    keys[j + 1] = keys[j];

  keys[i] = y->keys[1];

  n = n + 1;
}


void TreeNode::traverse() {
  cout<<"\n";
  int i;
  for (i = 0; i < n; i++) 
  {
    if (leaf == false)
      child[i]->traverse();
    cout << " " << keys[i];
  }

  if (leaf == false)
    child[i]->traverse();

  cout<<"\n";
}


void Tree::removeNode(int k) {
  if (!root) {
    cout << "The tree is empty\n";
    return;
  }

  root->removeNode(k);

  if (root->n == 0) {
    TreeNode *tmp = root;
    if (root->leaf)
      root = NULL;
    else
      root = root->child[0];

    delete tmp;
  }
  return;
}

int main() {
  Tree t;
	int n,k;
	cout<<"Enter the number of elements : ";
	cin>>n;
	cout<<"Enter the keys : ";
	for(int i=0; i<n; i++)
	{
		cin>>k;
		t.insertion(k);
	}
	cout << "\n The tree constructed is : \n";
    	t.traverse();
	cout<<"\n Enter the key to be deleted :";
	cin>>k;
	t.removeNode(k);
	cout<<"\n Tree after deletion is :";
	t.traverse();
  return 0;
}