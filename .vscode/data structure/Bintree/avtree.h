#ifndef AVTREE_H_
#define AVTREE_H_
#include <iostream>
#include "tree.h"
#include "BinarySearchTree.h"
using namespace std;
int Max(int a,int b){
    return (a>b)?a:b;
}

/*平衡二叉树：二叉搜索树在插入删除之后不注意左右子树高度的平衡，在进行搜索操作时会使搜索用时增大
  因此需要对每次插入删除之后的树进行调整，使左右子树的树高差不超过1
  含有左右单旋，左右双旋，右左双旋/插入删除操作           */
template <class T>
class AvlTree:public BinTree<T>{
    protected:
       BinTreeNode<T> * Insertnode(BinTreeNode<T> *subtree,T &x);
       BinTreeNode<T> * Deletenode(BinTreeNode<T> *subtree,T &x);
       BinTreeNode<T> * SingleLeftRotation(BinTreeNode<T> *subtree);
       BinTreeNode<T> * SingleRightRotation(BinTreeNode<T> *subtree);
       BinTreeNode<T> * LeftRightRotation(BinTreeNode<T> *subtree);
       BinTreeNode<T> * RightLeftRotation(BinTreeNode<T> *subtree);
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
       void buildavltree();
       void Insertnode(T &x){ this->root=Insertnode(this->root,x);}
       void Deletenode(T &x){ this->root=Deletenode(this->root,x);}
       BinTreeNode<T> *  Maxnode(){return Maxnode(this->root);}
       BinTreeNode<T> *  Minnode(){return Minnode(this->root);}
};

//左左单旋，麻烦节点在发现者的左子树的左子树
template <class T>
BinTreeNode<T> * AvlTree<T>::SingleLeftRotation(BinTreeNode<T> *subtree){
    BinTreeNode<T> *temp=subtree->leftChild;
    subtree->leftChild=temp->rightChild;
    temp->rightChild=subtree;
    subtree->height=Max(this->getheight(subtree->leftChild),this->getheight(subtree->rightChild))+1;
    temp->height=Max(this->getheight(temp->leftChild),this->getheight(temp->rightChild))+1;
    return temp;
}

//右右单旋，麻烦节点在发现者的右子树的右子树
template<class T>
BinTreeNode<T> * AvlTree<T>::SingleRightRotation(BinTreeNode<T> *subtree){
    BinTreeNode<T> *temp=subtree->rightChild;
    subtree->rightChild=temp->leftChild;
    temp->leftChild=subtree;
    subtree->height=Max(this->getheight(subtree->leftChild),this->getheight(subtree->rightChild))+1;
    temp->height=Max(this->getheight(temp->leftChild),this->getheight(temp->rightChild))+1;
    return temp;
}

//左右双旋，麻烦节点在发现者的左子树的右子树
template<class T>
BinTreeNode<T> * AvlTree<T>::LeftRightRotation(BinTreeNode<T> *subtree){
    subtree->leftChild=SingleRightRotation(subtree->leftChild);   
    return SingleLeftRotation(subtree);
}

//右左双旋，麻烦节点在发现者的右子树的左子树
template<class T>
BinTreeNode<T> * AvlTree<T>::RightLeftRotation(BinTreeNode<T> *subtree){
    subtree->rightChild=SingleLeftRotation(subtree->rightChild);   
    return SingleRightRotation(subtree);
}

//插入操作
template<class T>
BinTreeNode<T> * AvlTree<T>::Insertnode(BinTreeNode<T> *subtree,T &x){
    if(!subtree) subtree=new BinTreeNode<T>(x);   
    else{
        if(x>subtree->data){             //插在右子树，肯定有右旋
            subtree->rightChild=Insertnode(subtree->rightChild,x);     //先插入
            if((this->getheight(subtree->rightChild)-this->getheight(subtree->leftChild))==2){        
                //判断语句在递归之后，先建立树节点，之后递归出栈，从最早发现不平衡的子树开始调整
                 if(x>subtree->rightChild->data) subtree=SingleRightRotation(subtree);   //确定是哪一种旋转操作，右子树的右子树，右单旋
                 else subtree=RightLeftRotation(subtree);       //右子树的左子树，右左双旋
            }
        }
        else if(x<subtree->data){    //插在左子树，肯定有左旋
            subtree->leftChild=Insertnode(subtree->leftChild,x);
            if((this->getheight(subtree->leftChild)-this->getheight(subtree->rightChild))==2){        
                //判断语句在递归之后，先建立树节点，之后递归出栈，从最早发现不平衡的子树开始调整
                 if(x<subtree->leftChild->data) subtree=SingleLeftRotation(subtree);   //左子树的左子树
                 else subtree=LeftRightRotation(subtree);                //左子树的右子树
            }
        }
        //else x=subtree->data 不插入
    }
    subtree->height=Max(this->getheight(subtree->rightChild),this->getheight(subtree->leftChild))+1;
    return subtree;
}


//删除操作  判断方式与插入操作相反
template <class T>
BinTreeNode<T> * AvlTree<T>::Deletenode(BinTreeNode<T> *subtree,T &x){
    if(!subtree){cout<<"can't find deletenode"<<endl;} //没找到
    else{
        if(x>subtree->data){   //删除的是右子树的节点
            subtree->rightChild=Deletenode(subtree->rightChild,x);   //右子树递归删除
            if((this->getheight(subtree->leftChild)-this->getheight(subtree->rightChild))==2){      //右子树删除，本来是平衡的，只有删除的那边才可能破坏平衡，预估其树高较矮   
                if(this->getheight(subtree->leftChild->leftChild)>this->getheight(subtree->leftChild->rightChild)) //由树高判断麻烦节点在左子树的左子树，左单旋
                       subtree=SingleLeftRotation(subtree); 
                else   subtree=LeftRightRotation(subtree);
            }
        }
        else if(x<subtree->data){
            subtree->leftChild=Deletenode(subtree->leftChild,x);
            if((this->getheight(subtree->rightChild)-this->getheight(subtree->leftChild))==2){      //右子树删除，本来是平衡的，只有删除的那边才可能破坏平衡，预估其树高较矮   
                if(this->getheight(subtree->rightChild->leftChild)<this->getheight(subtree->rightChild->rightChild)) //由树高判断麻烦节点在y右子树的右子树，右单旋
                       subtree=SingleRightRotation(subtree); 
                else   subtree=RightLeftRotation(subtree);
            }
        }
        else{   //找到删除的树节点
             BinTreeNode<T> *temp;
             if(subtree->leftChild && subtree->rightChild){   //若删除节点有左右子树
                  temp=Maxnode(subtree->rightChild);
                  subtree->data=temp->data;                    //找到右子树中的最大值，递归删除这个节点
                  subtree->rightChild=Deletenode(subtree->rightChild,temp->data);    
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
//
template <class T>
void AvlTree<T>::buildavltree(){
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