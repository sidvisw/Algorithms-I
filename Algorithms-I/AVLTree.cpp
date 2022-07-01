#include<bits/stdc++.h>
using namespace std;
class node{
    public:
    int data;
    int ht;
    node*left,*right,*parent;
    node(int data=0){
        this->data=data;
        left=right=parent=NULL;
        ht=-1;
    }
};
class BBST{
    public:
    node*root;
    BBST(){
        root=NULL;
    }
    void right_rotate(node*&y){
        node*temp=y->left;
        y->left=temp->right;
        if(temp->right)
            temp->right->parent=y;
        temp->right=y;
        temp->parent=y->parent;
        y->parent=temp;
        y->ht=max(((y->left)?y->left->ht:-1),((y->right)?y->right->ht:-1))+1;
        temp->ht=max(((temp->left)?temp->left->ht:-1),((temp->right)?temp->right->ht:-1))+1;
        y=temp;
    }
    void left_rotate(node*&y){
        node*temp=y->right;
        y->right=temp->left;
        if(temp->left)
            temp->left->parent=y;
        temp->left=y;
        temp->parent=y->parent;
        y->parent=temp;
        y->ht=max(((y->left)?y->left->ht:-1),((y->right)?y->right->ht:-1))+1;
        temp->ht=max(((temp->left)?temp->left->ht:-1),((temp->right)?temp->right->ht:-1))+1;
        y=temp;
    }
    void insert(int num){
        if(!root){
            root=new node(num);
            return;
        }
        node*cur=root;
        while(cur){
            if(num<cur->data){
                if(!cur->left){
                    break;
                }
                cur=cur->left;
            }
            else if(num>cur->data){
                if(!cur->right){
                    break;
                }
                cur=cur->right;
            }
        }
        if(num<cur->data){
            cur->left=new node(num);
            cur->left->parent=cur;
        }
        else if(num>cur->data){
            cur->right=new node(num);
            cur->right->parent=cur;
        }
        int prevbal=0;
        int bal;
        while(cur){
            cur->ht=max(((cur->left)?cur->left->ht:-1),((cur->right)?cur->right->ht:-1))+1;
            bal=(((cur->right)?cur->right->ht:-1)-((cur->left)?cur->left->ht:-1));
            if(bal==-2&&prevbal==-1){
                right_rotate(cur);
                if(!cur->parent)root=cur;
                else cur->parent->left=cur;
                break;
            }
            else if(bal==-2&&prevbal==1){
                left_rotate(cur->left);
                right_rotate(cur);
                if(!cur->parent)root=cur;
                else cur->parent->left=cur;
                break;
            }
            else if(bal==2&&prevbal==1){
                left_rotate(cur);
                if(!cur->parent)root=cur;
                else cur->parent->right=cur;
                break;
            }
            else if(bal==2&&prevbal==-1){
                right_rotate(cur->right);
                left_rotate(cur);
                if(!cur->parent)root=cur;
                else cur->parent->right=cur;
                break;
            }
            prevbal=bal;
            cur=cur->parent;
        }
    }
    void inorder_helper(node*cur){
        if(!cur){
            return;
        }
        inorder_helper(cur->left);
        cout<<cur->data<<" ";
        inorder_helper(cur->right);
    }
    void inorder(){
        inorder_helper(root);
    }
};
int main(){
    int n;
    cin>>n;
    BBST t;
    for(int i=0;i<n;i++){
        int num;
        cin>>num;
        t.insert(num);
    }
    t.inorder();
}