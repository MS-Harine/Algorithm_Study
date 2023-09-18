#include <iostream>

template <typename T>
class WeightedRBTree {
private:
    enum Color { RED, BLACK };
    class Node {
    public:
        T value;
        int weight;
        Color color;
        Node *left;
        Node *right;
        Node *parent;

        Node(T value, int weight) {
            this->value = value;
            this->weight = weight;
            this->color = RED;
            this->left = nullptr;
            this->right = nullptr;
            this->parent = nullptr;
        }
    };

    Node *root;
    Node *nil;
    int weight_sum;

private:
    void leftRotation(Node *target) {
        if (target == nil || target->right == nil)
            return;
        
        Node *temp = target->right;
        target->right = temp->left;
        temp->left = target;
        
        if (target->right != nil)
            target->right->parent = target;
        temp->parent = target->parent;
        target->parent = temp;
        
        if (temp->parent != nil) {
            if (temp->parent->left == target)
                temp->parent->left = temp;
            else
                temp->parent->right = temp;
        }

        if (root == target)
            root = temp;
    }

    void rightRotation(Node *target) {
        if (target == nil || target->left == nil)
            return;
        
        Node *temp = target->left;
        target->left = temp->right;
        temp->right = target;

        if (target->left != nil)
            target->left->parent = target;
        temp->parent = target->parent;
        target->parent = temp;

        if (temp->parent != nil) {
            if (temp->parent->left == target)
                temp->parent->left = temp;
            else
                temp->parent->right = temp;
        }

        if (root == target)
            root = temp;
    }

    Node *getGrand(Node *target) {
        return target->parent->parent;
    }

    Node *getUncle(Node *target) {
        if (target->parent == getGrand(target)->left)
            return getGrand(target)->right;
        else
            return getGrand(target)->left;
    }

    void reconstruction(Node *target) {
        bool validate = (target->color == RED) && 
                        (target->parent->color == RED) && 
                        (getUncle(target)->color == BLACK);
        if (!validate)
            return;
        
        if (isRightChild(target)) {
            leftRotation(target->parent);
            target = target->left;
        }

        target->parent->color = BLACK;
        getGrand(target)->color = RED;
        rightRotation(getGrand(target));
    }

    void recoloring(Node *target) {
        bool validate = (target->color == RED) &&
                        (target->parent->color == RED) &&
                        (getUncle(target)->color == RED);
        if (!validate)
            return;
        
        target->parent->color = BLACK;
        getGrand(target)->color = RED;
        getUncle(target)->color = BLACK;

        recoloring(getGrand(target));
    }

    bool isLeftChild(Node *target) {
        return target->parent->left == target;
    }

    bool isRightChild(Node *target) {
        return target->parent->right == target;
    }

public:
    WeightedRBTree() : root(nullptr), nil(new Node(0, 0)), weight_sum(0) {
        nil->left = nil->right = nil->parent = nil;
        nil->color = BLACK;
    }

    void insert(T data, int weight) {
        Node *newNode = new Node(data, weight);
        newNode->left = newNode->right = newNode->parent = nil;

        if (root == nullptr) {
            newNode->color = BLACK;
            root = newNode;
        }
        else {
            Node *point = root;
            while (true) {
                if (data < point->value) {
                    if (point->left == nil)
                        break;
                    point = point->left;
                }
                else {
                    if (point->right == nil)
                        break;
                    point = point->right;
                }
            }
            
            if (data < point->value)
                point->left = newNode;
            else
                point->right = newNode;
            newNode->parent = point;
        }

        if (newNode->parent->color == RED) {
            reconstruction(newNode);
            recoloring(newNode);
        }
    }

    void remove(T data) {
        Node *delNode = root;
        while (delNode->value != data || delNode != nil) {
            if (data < delNode->value)
                delNode = delNode->left;
            else
                delNode = delNode->right;
        }

        if (delNode == nil)
            return;
        if (delNode == root) {
            delete delNode;
            root = nil;
            return;
        }
        
remove_from_node:
        switch (delNode->color) {
        case RED:
            if (delNode->left == nil && delNode->right == nil) {
                if (isLeftChild(delNode))
                    delNode->parent->left = nil;
                else
                    delNode->parent->right = nil;
            }
            else if (delNode->left != nil && delNode->right != nil) {
                Node *successor = delNode->left;
                while (successor->right != nil)
                    successor = successor->right;
                
                swap(successor->value, delNode->value);
                swap(successor->weight, delNode->weight);
                delNode = successor;
                goto remove_from_node;
            }
            else {
                if (delNode->left != nil) {
                    if (isLeftChild(delNode))
                        delNode->parent->left = delNode->left;
                    else
                        delNode->parent->right = delNode->left;
                    delNode->left->parent = delNode->parent;
                }
                else {
                    if (isLeftChild(delNode))
                        delNode->parent->left = delNode->right;
                    else
                        delNode->parent->right = delNode->right;
                    delNode->right->parent = delNode->parent;
                }
            }
            break;
        case BLACK:
            break;
        }
    }
};
