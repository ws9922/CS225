/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * root = t->right;
    t->right = root->left;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    root->left = t;
    root->height = std::max(heightOrNeg1(root->left), heightOrNeg1(root->right)) + 1;
    t = root;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * root = t->left;
    t->left = root->right;
    t->height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
    root->right = t;
    root->height = std::max(heightOrNeg1(root->left), heightOrNeg1(root->right)) + 1;
    t = root;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == NULL) {
        return;
    }
    if (subtree->right != NULL && subtree->right->right != NULL && heightOrNeg1(subtree->right->right) - heightOrNeg1(subtree->left) >= 1) {
        rotateLeft(subtree);
        return;
    }
    if (subtree->right != NULL && subtree->right->left != NULL && heightOrNeg1(subtree->right->left) - heightOrNeg1(subtree->left) >= 1) {
        rotateRightLeft(subtree);
        return;
    }
    if (subtree->left != NULL && subtree->left->left != NULL && heightOrNeg1(subtree->left->left) - heightOrNeg1(subtree->right) >= 1) {
        rotateRight(subtree);
        return;
    }
    if (subtree->left != NULL && subtree->left->right != NULL && heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->right) >= 1) {
        rotateLeftRight(subtree);
        return;
    }

}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL) {
        subtree = new Node(key, value);
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
        subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    } else {
        insert(subtree->right, key, value);
        subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            Node * tmp = subtree;
            subtree = NULL;
            delete tmp;
            tmp = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * IOP = subtree->left;
            while(IOP->right != NULL) {
                IOP = IOP->right;
            }
            swap(subtree, IOP);
            remove(subtree->left, key);
            subtree->height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left != NULL) {
                swap(subtree, subtree->left);
                delete subtree->left;
                subtree->left = NULL;
            } else {
                swap(subtree, subtree->right);
                delete subtree->right;
                subtree->right = NULL;
            }
            subtree->height --;
        }
        // your code here
    }
    rebalance(subtree);
}
