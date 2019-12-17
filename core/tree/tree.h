#ifndef TREE_H
#define TREE_H

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
class TreeElementContainer {
    T*                                  value;
    TreeElementContainer<T>*            parent;
    vector<TreeElementContainer<T>*>*    children;

    TreeElementContainer(T* value);
public:
    ~TreeElementContainer();

    T*                                  getValue();
    TreeElementContainer<T>*            addChild(T* child);
    vector<TreeElementContainer<T>*>*   getChildren();
    TreeElementContainer<T>*            getParent();
    bool                                isRoot();
    void                                setParent(TreeElementContainer<T>* parent);

    static TreeElementContainer<T>*     createNode(T* value);
};

#endif
