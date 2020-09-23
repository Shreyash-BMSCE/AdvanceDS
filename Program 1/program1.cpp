#include<iostream>
#include <inttypes.h> 
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
    if(*head)
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
    if(!(*head))
    {
        *head = new_node;
    }
    else
    {
        Node *curr = *head;
        Node *prev = NULL;
        Node *next = XOR(prev,curr->xnext);
        while(next)
        {
            prev = curr;
            curr = next;
            next = XOR(prev,curr->xnext);
        }
        new_node->xnext = XOR(curr,next);
        curr->xnext = XOR(curr->xnext,new_node);
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
    while(curr)
    {
        cout<<curr->data<<" -> ";
        next = XOR(prev,curr->xnext);
        prev = curr;
        curr = next;
    }
}

int main()
{
    Node *head = NULL;
    int ch=0,data;
    while(ch!=3)
    {
        cout<<"\n 1. Insert front \n 2.Print \n 3. Exit \n 4. Insert End \t ";
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
        else if(ch==4)
        {
            cout<<"\n Enter the data:";
            cin>>data;
            insert_end(&head,data);
        }
    }
    return 0;
    //getch();
}