#ifndef TREE_H_
#define TREE_H_
#include <iostream>
#include "quene.h"
#include "stack.h"
using namespace std;
template <class T>
struct BinTreeNode{
    T data;
    int height;
    BinTreeNode<T> *leftChild,*rightChild;
    BinTreeNode():leftChild(NULL),rightChild(NULL),height(-1){};
    BinTreeNode(T x,BinTreeNode<T> *l=NULL,BinTreeNode<T> *r=NULL){
        data=x;
        leftChild=l;
        rightChild=r;
        height=0;
    }
};
/*************************************************************************
 二叉树类，实现二叉树的建造，求树高/元素数，四种遍历方式，不进行插入删除操作
***********************************************************************/
template <class T>
class BinTree{
    protected:
       BinTreeNode<T> *root;
       void deleteall(BinTreeNode<T> *subtree);
       int getheight(BinTreeNode<T> *subtree);  //树高
       int getsize(BinTreeNode<T> *subtree);  //树内元素数
       void Inorder(BinTreeNode<T> *subtree,void (*visit)(BinTreeNode<T> *s));     //中序遍历
       void Preorder(BinTreeNode<T> *subtree,void (*visit)(BinTreeNode<T> *s));    //前序遍历
       void Postorder(BinTreeNode<T> *subtree,void (*visit)(BinTreeNode<T> *s));   //后序遍历
       void Levelorder(BinTreeNode<T> *subtree,void (*visit)(BinTreeNode<T> *s));  //层序遍历
       /************************************************************************
        若遍历函数使用递归实现，那么形参需要二叉树与visit函数，root需要作为形参，
        而考虑到程序的封装性，我们并不希望主函数可以直接访问数据
        因此我们将递归函数设置为私有，在公有函数中设置接口，调用递归函数，visit函数可以由主函数提供
        增强其封装性
        ***********************************************************************/
    public:
       BinTree():root(NULL){};
       BinTree(T x){
           root=new BinTreeNode<T>(x);
       }
       ~BinTree(){deleteall(root);}
       void createtree(); //构造二叉树,输入参数为树节点指针的引用传递
       int height(){return getheight(root);}
       int getsize(){return getsize(root);}  //树内元素数
       bool isempty(){return (root==NULL)?true:false;}
       BinTreeNode<T> * getroot(){return root;}
       void Inorder(void (*visit)(BinTreeNode<T> *s)){Inorder(this->root,visit);}
       void Preorder(void (*visit)(BinTreeNode<T> *s)){Preorder(this->root,visit);}
       void Postorder(void (*visit)(BinTreeNode<T> *s)){ Postorder(this->root,visit);}
       void Levelorder(void (*visit)(BinTreeNode<T> *s)){Levelorder(this->root,visit);}
};
template <class T>            //后序遍历删除每一个树节点
void BinTree<T>::deleteall(BinTreeNode<T> *subtree){   
    if(subtree){
        deleteall(subtree->leftChild);
        deleteall(subtree->rightChild);
        delete subtree;
    }
}

template <class T>     //通过广义表输入二叉树.例如A(B(D,E),C )；D，E是B的儿子，B，C是A的儿子
void BinTree<T>::createtree(){      //因为广义表需要使用括号，所以T设置为char
    liststack<BinTreeNode<char>*> s;       
    BinTreeNode<char>* BT=NULL;
    char ch;
    BinTreeNode<char> *temp,*newnode;
    int k;
    cout<<"please enter binarytree by using generalize list ;end with #"<<endl;
    cin>>ch;
    while(ch!='#'){
        switch (ch)
        {
        case '(':          //如果是（，那么前一个输入节点是子树根节点，进栈，记录所有根节点，最近的根节点永远在栈顶
            s.Push(newnode);
            k=1;           //标记为1 代表之后处理的是左子树                                                                                                                              
            break;
        case ',':         //，代表要处理右子树，标记为2
            k=2;
            break;
        case ')':
            s.Pop(temp);    //如果是 ），那么代表右子树处理完，需要将根节点出栈  处理完一个子树之后才会出栈                                                                                                                                   
            break;
        default:
            newnode=new BinTreeNode<char>(ch);
            if(BT==NULL)    BT=newnode;
            else if(k==1){  //处理左子树
                s.getTop(temp);  //取根节点
                temp->leftChild=newnode;
            }   
            else{
               s.getTop(temp);
               temp->rightChild=newnode;
            }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
            break;
        }
        cin>>ch;
    }
    root=BT;
}

//求树高
template <class T>
int BinTree<T>::getheight(BinTreeNode<T> *subtree){
    if(subtree==NULL) return 0;
    int leftheight=getheight(subtree->leftChild);
    int rightheight=getheight(subtree->rightChild);
    return (leftheight>=rightheight)?leftheight+1:rightheight+1;
}

//二叉树的元素数
template <class T>
int BinTree<T>::getsize(BinTreeNode<T> *subtree){
    if(subtree==NULL) return 0;
    int leftsize=getsize(subtree->leftChild);
    int rightsize=getsize(subtree->rightChild);
    return leftsize+rightsize+1;
}

//中序遍历
template <class T>
void BinTree<T>::Inorder(BinTreeNode<T> *subtree,void (*visit)(BinTreeNode<T> *s)){
    /*********************************************
    if(subtree!=NULL) {
    Inorder(subtree->leftChild,visit);
    (*visit)(subtree);
    Inorder(subtree->rightChild,visit);
    }
    **************************************************/
    liststack<BinTreeNode<T> *> s0;        //中序遍历在访问完左子树后再进行visit
    BinTreeNode<T> *tnode=subtree;
    while(tnode||!s0.Isempty()){     //当tnode不为空或者栈内还有树节点时开始循环
       while(tnode){              //左子树全部进栈
           s0.Push(tnode);
           tnode=tnode->leftChild;
       }
       if(!s0.Isempty()){     //最后一个节点的父节点弹出
           s0.Pop(tnode);
           visit(tnode);      //访问节点
           tnode=tnode->rightChild;    //指向右子树   如果右子树不为空，那么执行压栈循环， 为空就执行栈的弹出继续往上
       }
   }
}
template<class T>
void BinTree<T>::Preorder(BinTreeNode<T> *subtree,void (*visit)(BinTreeNode<T> *s)){
    /************************************
    if(subtree!=NULL){
        visit(subtree);
        Preorder(subtree->leftChild,visit);
        Preorder(subtree->rightChild,visit);
    }
    ********************************************/
   liststack<BinTreeNode<T> *> s0;
   BinTreeNode<T> *tnode=subtree;
   while(tnode||!s0.Isempty()){     //当tnode不为空或者栈内还有树节点时开始循环
       while(tnode){              //左子树边压栈边visit  //再次进入循环体，tnode为空或者右子树
           s0.Push(tnode);
           visit(tnode);
           tnode=tnode->leftChild;
       }
       if(!s0.Isempty()){     //最后一个节点的父节点弹出
           s0.Pop(tnode);
           tnode=tnode->rightChild;    //指向右子树   如果右子树不为空，那么执行压栈循环， 为空就执行栈的弹出继续往上
       }
   }
}
template<class T> 
void BinTree<T>::Postorder(BinTreeNode<T> *subtree,void (*visit)(BinTreeNode<T> *s)){  //后序遍历，根节点需要在右子树后访问，有所不同   
    /**************************************
    if(subtree!=NULL){
        Postorder(subtree,visit);
        Postorder(subtree,visit);
        visit(subtree);
    }
    *******************************************/
   if(subtree==NULL) return;
   liststack<BinTreeNode<T> *> s0;
   BinTreeNode<T> *tnode=subtree;
   BinTreeNode<T> *curnode=NULL;      //记录上一次出栈节点
   BinTreeNode<T> *top;               //记录栈顶元素
   while(tnode||!s0.Isempty()){
       while(tnode){                 //左子树进栈
           s0.Push(tnode);
           tnode=tnode->leftChild;
       }
       if(!s0.Isempty()){
           s0.getTop(top);        //栈顶元素top
           if(top->rightChild &&(top->rightChild!=curnode))  tnode=top->rightChild;   //如果有右子树且未进栈，转至右子树 ，进行压栈操作
                                                                                  //如果栈顶元素的右子树为上次出栈的元素，说明已经访问过右子树，可以出栈
                                                                                  //经过上面的循环体后，左子树必定全部进栈，因此只需要判定右子树有无进栈
           else{
               s0.Pop(tnode);                       
               curnode=tnode;                       //每次出栈，记录出栈元素
               visit(tnode);    
               tnode=NULL;            //访问完之后设为NULL，以免重复进栈 
           } 
       }
   }

}
template<class T>      
void BinTree<T>::Levelorder(BinTreeNode<T> *subtree,void (*visit)(BinTreeNode<T> *s)){
    if(subtree==NULL) return;
    listquene<BinTreeNode<T> *> q;
    BinTreeNode<T> *p;
    q.enquene(subtree);
    while(!q.isempty()){
        q.dequene(p);
        visit(p);
        if(p->leftChild) q.enquene(p->leftChild);
        if(p->rightChild) q.enquene(p->rightChild);
    }
    
}

#endif