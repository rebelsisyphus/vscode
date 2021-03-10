#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_
#include <iostream>
#include <assert.h>
#include "tree.h"
using namespace std;
//二叉搜索树，实现逐个元素输入/查找/插入/删除功能
template <class T>
class BinSearchTree:public BinTree<T>{
    protected:
       BinTreeNode<T> * Insertnode(BinTreeNode<T> *subtree,T &x);
       BinTreeNode<T> * deletenode(BinTreeNode<T> *subtree,T &x);
       BinTreeNode<T> *  Maxnode(BinTreeNode<T> *subtree){
            BinTreeNode<T> *temp=subtree;
            while(temp->rightChild!=NULL){
                temp=temp->rightChild;
            }
            return temp;
       }
       BinTreeNode<T> *  Minnode(BinTreeNode<T> *subtree){
           BinTreeNode<T> *temp=subtree;
            while(temp->leftChild!=NULL){
                temp=temp->leftChild;
            }
            return temp;
       }
    public:
       /*BinSearchTree(){this->root=NULL;};
       BinSearchTree(T x){
           this->root=new BinTreeNode<T>(x);
       }
       ~BinSearchTree(){this->deleteall(this->root);}*/
       void buildBStree();
       BinTreeNode<T> * Findtreenode(const T &X);
       void Insertnode(T &x){ this->root=Insertnode(this->root,x);}
       void deletenode(T &x){ this->root=deletenode(this->root,x);}
       BinTreeNode<T> *  Maxnode(){return Maxnode(this->root);}
       BinTreeNode<T> *  Minnode(){return Minnode(this->root);}
};

//在二叉搜索树中查找一个值。返回其所在的树节点
template <class T>
BinTreeNode<T> * BinSearchTree<T>::Findtreenode(const T &x){
    BinTreeNode<T> *temp=this->getroot();     //调用基类函数要使用this指针
    if(temp==NULL) return NULL;
    while(temp!=NULL){
        if(x>temp->data) temp=temp->rightChild;
        else if(x<temp->data) temp=temp->leftChild;
        else return temp;
    }
}

//在二叉搜索树中插入一个值,返回插入正确与否
template<class T>
BinTreeNode<T> * BinSearchTree<T>::Insertnode(BinTreeNode<T> *subtree,T &x){  //可以改为 bool Insertnode(BinTreeNode<T> *&subtree,T &x),使用引用传递，则不需要下面的值传递
    if(!subtree){
        subtree=new BinTreeNode<T>(x);
    }
    else{
        if(x>subtree->data) subtree->rightChild=Insertnode(subtree->rightChild,x);    //因为函数形参是树节点指针的值传递，因此需要赋值操作
        else if(x<subtree->data) subtree->leftChild=Insertnode(subtree->leftChild,x);
    }
    return subtree;
}

//在二叉搜索树中删除一个元素，返回删除正确与否
template<class T>
BinTreeNode<T> * BinSearchTree<T>::deletenode(BinTreeNode<T> *subtree,T &x){
    if(!subtree){cout<<"can't find deletenode"<<endl;} //没找到
    else{
        if(x>subtree->data) subtree->rightChild=deletenode(subtree->rightChild,x);   //左子树递归删除
        else if(x<subtree->data) subtree->leftChild=deletenode(subtree->leftChild,x);
        else{   //找到删除的树节点
             BinTreeNode<T> *temp;
             if(subtree->leftChild && subtree->rightChild){   //若删除节点有左右子树
                  temp=Maxnode(subtree->rightChild);
                  subtree->data=temp->data;                    //找到右子树中的最大值，递归删除这个节点
                  subtree->rightChild=deletenode(subtree->rightChild,temp->data);    
             }
             else{
                 temp=subtree;                              //删除该节点
                 if(!subtree->leftChild) subtree=subtree->rightChild;
                 else subtree=subtree->leftChild;
                 delete temp; 
             }
        }  
    }
     return subtree;
}
template<class T>
void BinSearchTree<T>::buildBStree(){
    cout<<"please enter the element of bintree:"<<endl;
    BinTreeNode<T>* BT=NULL;
    T num;
    cin>>num;
    while(num!='#'){
      BT=Insertnode(BT,num);
      cin>>num;
    }
    this->root=BT;
}























#endif