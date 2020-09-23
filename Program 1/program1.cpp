#include<iostream>
//#include<stdio.h>
using namespace std;

class Node
{
    public: int data;
    Node *xnext;
};

Node *XOR(Node *x, Node *y)
{
    return (Node*) ((uintptr_t)(x) ^ (uintptr_t)(y));
}

void insert(Node **head, int data)
{
    Node *new_node = new Node();
    new_node -> data = data;
    new_node->xnext = (*head);
    if(*head != NULL)
    {
        (*head) -> xnext = XOR(new_node,(*head)->xnext);
    }
    *head = new_node;
}

void insert_end(Node **head, int data)
{
    Node *new_node = new Node();
    new_node->data = data;
    new_node->xnext = NULL;
    if(*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        Node *curr = *head;
        Node *prev = NULL;
        Node *next;
        while(curr!=NULL)
        {
            next = XOR(prev,curr->xnext);
            prev = curr;
            curr = next;
        }
        curr = new_node;
    }
}

/* void del(Node **head, int num)
{
    int count = 0;
    
} */
void print(Node *head)
{
    Node *curr = head;
    Node *prev = NULL;
    Node *next;
    while(curr->xnext!= NULL)
    {
        cout<<curr->data<<" -> ";
        curr = XOR(prev,curr->xnext);
    }
}

int main()
{
    Node *head = NULL;
    int ch=0,data;
    while(ch!=3)
    {
        cout<<"1. Insert 2.Print 3. Exit ";
        cin>>ch;
        if (ch==1)
        {
            cout<<"\n Enter the data:";
            cin>>data;
            insert(&head,data);
        }
        else if(ch==2)
        {
            print(head);
        }
    }
    return 0;
    //getch();
}