#include<iostream>

using namespace std;
# define max 10
typedef struct hash
{
    int data;
    struct hash *next;
} node_type;
node_type *ptr[max],*root[max],*temp[max];
class Dict
{
public:
    int index;
    Dict();
    void insert(int);
    void delete_ele(int);
    void print();
};
Dict::Dict()
{
    index=-1;
    for(int i=0; i<max; i++)
    {
        root[i]=NULL;
        ptr[i]=NULL;
        temp[i]=NULL;
    }
}

void Dict::insert(int key)
{
    index=int(key%max);
    ptr[index]=(node_type*)malloc(sizeof(node_type));
    ptr[index]->data=key;
    if(root[index]==NULL)
    {
        root[index]=ptr[index];
        root[index]->next=NULL;
        temp[index]=ptr[index];
    }
    else
    {
        temp[index]=root[index];
        while(temp[index]->next!=NULL)
            temp[index]=temp[index]->next;
        temp[index]->next=ptr[index];
    }
}

void Dict::delete_ele(int key)
{
    index=int(key%max);
    temp[index]=root[index];
    while(temp[index]->data!=key && temp[index]!=NULL)
    {
        ptr[index]=temp[index];
        temp[index]=temp[index]->next;
    }
    ptr[index]->next=temp[index]->next;
    cout<<"\n"<<temp[index]->data<<" was deleted.";
    temp[index]->data=-1;
    temp[index]=NULL;
    free(temp[index]);
}

int main()
{
    int val,ch,n,num;
    char c;
    Dict d;
    do
    {
        cout<<"\nENTER CHOICE: \n1.Add a value";
        cout<<"\n2.Delete \n";
        cin>>ch;
        switch(ch)
        {
        case 1:
            cout<<"\nEnter the number of elements:";
            cin>>n;
            cout<<"\nEnter the elements:";
            for(int i=0; i<n; i++)
            {
                cin>>num;
                d.insert(num);
            }
            break;
        case 2:
            cout<<"\nEnter the element to be deleted:";
            cin>>n;
            d.delete_ele(n);
            break;
        default:
            cout<<"\nInvalid Choice.";
        }
        cout<<"\nContinue ? y/n:";
        cin>>c;
    }
    while(c=='y');
    return 0;
}