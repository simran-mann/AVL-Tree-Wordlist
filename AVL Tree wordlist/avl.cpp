#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>


using namespace std;


//practice inplementation of n acl tree storing int values 


struct node{
    int height;
    node* left;
    node* right;
    int key;

};

class avlTree{

private:
    node* root;

    // int height(node* n){
    //     if (n==nullptr){
    //         return 0;
    //     }
    //     return n->height;
    // }
  
    node* right_rotation(node* z){
        node* y=z->left;
        z->left=y->right;
        y->right=z;
        y->height= 1 + max(y->left->height, y->right->height);;
        z->height= 1 + max(z->left->height, z->right->height);;
        return y;
    }
    node* left_rotation(node* z){
        node* y= z->right;
        z->right=y->left;
        y->left=z;
        y->height= 1 + max(y->left->height, y->right->height);
        z->height= 1 + max(z->left->height, z->right->height);
        return y;
    }
public:
    avlTree() { }
    bool is_empty(){
        return root==nullptr;
    }
    node* insert(node* z, int val){

        if (z==nullptr){

            node* new_node=new node{1,nullptr,nullptr,val};//inserting a new leaf has height 1 

            return new_node;
        }
        //regular BST insertion
        if (val<z->key){
            z->left=insert(z->left,val);
        }else{
            z->right=insert(z->right, val);
        }
        //update the height of current node 
        if (z->right->height==0){
                cout<<"0 heihgt"<<endl; 
        }
        cout<<"after"<<endl;
        
        z->height= 1 +max(z->left->height, z->right->height);; //update the height 

        //calculate the balance factor 
        int bal = z->left->height-z->right->height;

        if (bal>1){//right subtree is higher 
            if (val<z->left->key){
                return right_rotation(z);
            }else{
                z->left=left_rotation(z->left);
                return right_rotation(z);
            }
        }else if (bal<-1){//left subtree is higher 
            if (val>z->right->key){
                return left_rotation(z);
            }else{
                z->right=right_rotation(z->right);
                return left_rotation(z);
            }
        }
        //if height balance proerpty is satisfied, return z
        return z;
    }
    void print_in_order(node* n){
        if (n==nullptr){
            return;
        }
        print_in_order(n->left);
        cout<<n->key<<endl;
        print_in_order(n->right);
    }
    void add(int val){
        cout<<"inside"<<endl;
        root= insert(root,val);
        cout<<"after"<<endl;
    }
};

 
int main(){
    avlTree T;
    cout<<"created"<<endl;
    T.add(7);
    T.add(5);
    T.add(10);
    T.add(2);
}