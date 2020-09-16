#include<iostream>

using namespace std;
class node
{
    public: int data;
    node* next;
};

node *rev(node *head,int k)
{
    node* curr = head;
    node* front = NULL;
    node* prev = NULL;
    int count = 1;
    while(curr!=NULL && count <= k)
    {
        front = curr->next;
        curr->next = prev;
        prev = curr;
        curr = front;
        count++;
    }
    if(front!= NULL)
    head->next = rev(front,k);
    return prev; 
}

node *push(node *head, int data)
{
    if(head==NULL)
    {
        head->data = data;
        return head;
    }
    node *Node = head;
    node *newnode = new node();
    newnode->data = data;
    newnode->next = NULL;
    while(Node->next!= NULL)
    Node = head->next;
    head->next = newnode;
    return head;
}

void print(node *head)
{
    while(head->next!=NULL)
    {
        cout<<head->data<<"->";
        head = head->next;
    }
    cout<<head->data;
}

int main()
{
    node *head = NULL;
    int data,k;
    cout<<"\nInsert data:  ||  0 to quit\n";
    while(1)
    {
        cin>>data;
        head = push(head,data);
        if(data==0)
        break;
    }
    cout<<"Enter k";
    cin>>k;
    cout<<"the list is: ";
    print(head);
    cout<<"the reversed list is:";
    head = rev(head,k);
    print(head);
    return 0;
}


