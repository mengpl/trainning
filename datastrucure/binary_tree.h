#ifndef __CTREE_H__
#define __CTREE_H__

template<typename T>
class CBinaryNode
{
public:
    CBinaryNode(const T & theElement, CBinaryNode * lt,CBinaryNode * rt):element(theElement),left(lt),right(rt)
    {};
    CBinaryNode();
    virtual ~CBinaryNode();

private:
    CBinaryNode *left;
    CBinaryNode *right;
    T element;
};

template<typename T>
class CBinarySearchTree
{
public:
    CBinarySearchTree();
    virtual ~CBinarySearchTree();
public:
    const T findMax() const;
    const T findMin() const;
    bool contains(const T & t) const;
    bool isEmpty() const;
    void printTree() const;

    void makeEmpty();
    void insert(const T & t);
    void remove(const T & t);

    const CBinarySearchTree & operator = (const CBinarySearchTree & rhs);

private:
    CBinaryNode<T> * root;

    void insert(const T & t ,CBinaryNode<T> * & tree) const;
    void remove(const T & t ,CBinaryNode<T> * & tree) const;
    CBinaryNode<T> * findMin(CBinaryNode<T> * t) const;
    CBinaryNode<T> * findMax(CBinaryNode<T> * t) const;
    bool contains(const T & t,CBinaryNode<T> * tree) const;
    void makeEmpty(CBinaryNode<T> * & t);
    void printTree(CBinaryNode<T> * t) const;
    CBinaryNode<T> * clone(CBinaryNode<T> * t) const;
};


#endif /*__CTREE_H__ */