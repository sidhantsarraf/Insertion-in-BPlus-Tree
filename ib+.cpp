#include<bits/stdc++.h>
using namespace std;
#define MAX 50
#define ll long long
int temp;
int max_children;
struct block{
    int NIB=0;
    block *parent=NULL;
    int value[MAX];
    block *child[MAX];
    block(){
    	int i=0;
        while(i<MAX){
            value[i] = INT_MAX;
            child[i] = NULL;
            i++;
        }
    }
};
block *temp1;
block *root = new block();

void splitLeaf(block *current)
{
    int x, i, j;
    (max_children%2) ? x = (max_children+1)/2 : x = max_children/2;
    block *rblock = new block();
    block *lblock = new block();
    lblock->NIB=x;
    current->NIB = x;
    int y=max_children-x;
    rblock->NIB = y;
    lblock->parent=current->parent;
    rblock->parent = current->parent;
    i=x;
    while(i<max_children){    
        rblock->value[i-x] = current->value[i];
        current->value[i] = INT_MAX;
        i++;
    }
    int val = rblock->value[0];
    if(current->parent==NULL){
        block *parent = new block();
        parent->parent = NULL;
        parent->NIB=1;
        parent->value[0] = val;
        parent->child[0] = current;
        parent->child[1] = rblock;
        current->parent = rblock->parent = parent;
        root = parent;
        return;
    }
    else
    {
        current = current->parent;
        block *newchild = new block();
        block *newchild1 = new block();
        newchild = rblock; 
        i=0;
        while(i<=current->NIB){
            if(val < current->value[i]){
            	temp=current->value[i];
            	current->value[i]=val;
            	val=temp;
            }
            i++;
        }
        current->NIB++;
        i=0;
        while(i<current->NIB){
            if(newchild->value[0] < current->child[i]->value[0]){
            	temp1=current->child[i];
            	current->child[i]=newchild;
            	newchild=temp1;
            }
            i++;
        }
        current->child[i] = newchild;
        i=0;
        while(current->child[i]!=NULL){
            current->child[i]->parent = current;
            i++;
        }
    }

}

void splitNonLeaf(block *current)
{
    int x, i, j;
    x = max_children/2;
    block *rblock = new block();
    current->NIB = x;
    rblock->NIB = max_children-x-1;
    rblock->parent = current->parent;
    i=x;
    while(i<=max_children)
    {
        rblock->value[i-x] = current->value[i];
        rblock->child[i-x] = current->child[i];
        current->value[i] = INT_MAX;
        if(i!=x)current->child[i] = NULL;
        i++;
    }
    int val = rblock->value[0];
    memcpy(&rblock->value, &rblock->value[1], sizeof(int)*(rblock->NIB+1));
    memcpy(&rblock->child, &rblock->child[1], sizeof(root)*(rblock->NIB+1));
    i=0;
    while(rblock->child[i]!=NULL){
        rblock->child[i]->parent = rblock;
        i++;
    }
    i=0;
    while(current->child[i]!=NULL){
        current->child[i]->parent = current;
        i++;
    }
    if(current->parent==NULL){
        block *parent = new block();
        parent->parent = NULL;
        parent->NIB=1;
        parent->value[0] = val;
        parent->child[0] = current;
        parent->child[1] = rblock;
        current->parent = rblock->parent = parent;
        root = parent;
        return;
    }
    else{
        current = current->parent;
        block *newchild = new block();
        newchild = rblock;
        i=0;
        while(i<=current->NIB){
            if(val < current->value[i]){
                temp=current->value[i];
            	current->value[i]=val;
            	val=temp;
            	 i++;
            }
            else 
            	i++;
           
        }
        current->NIB++;i=0;
        while(i<current->NIB){
            if(newchild->value[0] < current->child[i]->value[0] && newchild->value[0] >= current->child[i]->value[0]){
               	temp1=current->child[i];
            	current->child[i]=newchild;
            	newchild=temp1;
            	i++;
            }
            else
            	i++;
            
        }
        current->child[i] = newchild;i=0;
         while(current->child[i]!=NULL){
            current->child[i]->parent = current;
            i++;
        }
    }

}

void insertNode(block *current, int val)
{
	int i=0;
    while( i<=current->NIB)
    {
        if(val < current->value[i] && current->child[i]!=NULL)
        {
            insertNode(current->child[i], val);
            if(current->NIB==max_children)
                splitNonLeaf(current);
            return;
        }
        else if(val < current->value[i] && current->child[i]==NULL)
        {

            temp=current->value[i];
            current->value[i]=val;
            val=temp;
            if(i==current->NIB)
            {
                    current->NIB++;
                    break;
            }
        }
        i++;
    }
    if(current->NIB==max_children){
		splitLeaf(current);
    }
}



void print(vector < block* > blocks){
    vector < block* > nblock;
    for(int i=0; i<blocks.size(); i++){ 
        block *current = blocks[i];

        cout <<"[|";
        int j;
        for(j=0; j<current->NIB; j++){
            cout << current->value[j] << "|";
            if(current->child[j]!=NULL)
            nblock.push_back(current->child[j]);
        }
        if(current->value[j]==INT_MAX && current->child[j]!=NULL)
            nblock.push_back(current->child[j]);

        cout << "]  ";
    }

    if(nblock.size()==0){ 
    	cout<<endl;
    	cout<<endl;
        blocks.clear();
    }
    else 
    { 
    	cout<<endl;
    	cout<<endl;
        blocks.clear();
        print(nblock);                                          
    }
}


int main()
{
    ll choice,num;
    vector < block* > blocks;
    cout<<"Enter max no. of children a block can point to:"<<endl;
    cin>>max_children;
    while(1)
    {
        cout<<"Enter 1 to insert a number in b+ tree"<<endl;
        cout<<"Enter 2 to print the b+ tree"<<endl;
        cout<<"Enter 3 to exit"<<endl;
        cout<<"Enter your choice"<<endl;
        cin>>choice;

        switch(choice)
        {
            case 1:cout<<"Enter the number to insert"<<endl;
                cin>>num;
                insertNode(root, num);
                break;
            case 2:blocks.clear();
            blocks.push_back(root);
            print(blocks);
            break;
            case 3:exit(1);
        }
    }


}  
