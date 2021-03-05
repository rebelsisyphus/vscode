#include <iostream>
#include "list1.h"
template <class T> class Tree{
    public:
    virtual void preorder()=0;
    virtual void inorder()=0;
    virtual void postorder()=0;
    virtual int getheight()=0;
    
}