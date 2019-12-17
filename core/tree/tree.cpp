#include "tree.h"
#include "../employee/employee.h"

template <typename T>
TreeElementContainer<T>::TreeElementContainer(T* value) {
    this->value         = value;
    this->parent        = NULL;
    this->children      = new vector<TreeElementContainer<T>*>();
}

template <typename T>
TreeElementContainer<T>::~TreeElementContainer() {
    delete value;

    for (TreeElementContainer<T>* node : *children) {
        delete node;
    }

    delete children;
}

template <typename T>
T* TreeElementContainer<T>::getValue() {
    return this->value;
}

template <typename T>
void TreeElementContainer<T>::setParent(TreeElementContainer<T>* parent) {
    this->parent = parent;
}

template<class T>
TreeElementContainer<T>* TreeElementContainer<T>::addChild(T* child) {
    TreeElementContainer<T>* node = TreeElementContainer<T>::createNode(child);

    node->setParent(this);

    this->children->push_back(node);

    return node;
}

template<class T>
vector<TreeElementContainer<T>*>* TreeElementContainer<T>::getChildren() {
    return this->children;
}

template<class T>
bool TreeElementContainer<T>::isRoot() {
    return  this->parent == NULL;
}

template <typename T>
TreeElementContainer<T>* TreeElementContainer<T>::createNode(T* value) {
    return new TreeElementContainer(value);
}

template <typename T>
TreeElementContainer<T>* TreeElementContainer<T>::getParent() {
    return this->parent;
}

template class TreeElementContainer<Employee>;
