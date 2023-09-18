#include <iostream>

enum Color
{
    RED,
    BLACK
};
struct node
{
    int key;
    int weight;
    node *left = nullptr;
    node *right = nullptr;
    node *parent = nullptr;
    Color color = BLACK;
};

typedef node *NodePtr;

class RBTREE
{
private:
    NodePtr root;     //루트 노드
    NodePtr leafNode; //단말노드
    int weight_sum;

    //key값이 있는지 없는지 검사 있으면 pointer 값, 없으면 nullptr
    NodePtr IsKey(int item)
    {
        NodePtr t = root;
        NodePtr parent = NULL;

        /*key값을 찾거나 없다면 break*/
        while (t != NULL && t->key != item)
        {
            parent = t;
            t = (item < parent->key) ? parent->left : parent->right;
        }
        return t;
    }

    void InsertFixUp(NodePtr z)
    {
        /*root 노드가 아니고 부모 색이 red라면*/
        while (z != root && z->parent->color == RED)
        {
            NodePtr grandparent = z->parent->parent;
            NodePtr uncle = (z->parent == grandparent->left) ? grandparent->right : grandparent->left;
            bool side = (z->parent == grandparent->left) ? true : false; //if p[z]가 p[p[z]]의 왼쪽 자식이면 1 / 오른쪽이면 0

            /*case 1*/
            if (uncle && uncle->color == RED)
            {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }

            /*case 2
                side == true ) p[z]는 p[p[z]]의 왼쪽 자식 인 경우이다.
                side == false ) p[z]는 p[p[z]]의 오른쪽 자식 인 경우이다. */
            else
            {
                /*case 2-1*/
                if (z == (side ? z->parent->right : z->parent->left))
                {
                    z = z->parent;
                    side ? RotateLeft(z) : RotateRight(z);
                }
                /*case 2-2*/
                z->parent->color = BLACK;
                grandparent->color = RED;
                side ? RotateRight(grandparent) : RotateLeft(grandparent);
            }
        }
        root->color = BLACK;
    }

    void DelteFixUp(NodePtr x)
    {
        NodePtr s; //형제노드 s

        //root이거나 double black 이 깨질때 까지
        while (x != root && x->color == BLACK)
        {
            /* x가 p[x]의 왼쪽자식인 경우 */
            if (x == x->parent->left)
            {
                s = x->parent->right;
                // case 1
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    RotateLeft(x->parent);
                    s = x->parent->right;
                }

                // case 2
                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    // case 3
                    if (s->right->color == BLACK)
                    {
                        s->left->color = BLACK;
                        s->color = RED;
                        RotateRight(s);
                        s = x->parent->right;
                    }

                    // case 4
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    RotateLeft(x->parent);
                    x = root;
                }
            }

            /*x가 p[x]의 오른쪽 자식인 경우*/
            else
            {
                s = x->parent->left;
                // case 1
                if (s->color == RED)
                {
                    s->color = BLACK;
                    x->parent->color = RED;
                    RotateRight(x->parent);
                    s = x->parent->left;
                }

                // case 2
                if (s->left->color == BLACK && s->right->color == BLACK)
                {
                    s->color = RED;
                    x = x->parent;
                }
                else
                {
                    // case 3
                    if (s->left->color == BLACK)
                    {
                        s->right->color = BLACK;
                        s->color = RED;
                        RotateLeft(s);
                        s = x->parent->left;
                    }
                    // case 4
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    RotateRight(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
        root->color = BLACK;
    }

    /* u의 위치에 v를 이식 */
    void Transplant(NodePtr u, NodePtr v)
    {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        v->parent = u->parent;
    }
    /*x를 중심으로 왼쪽으로 회전*/
    void RotateLeft(NodePtr x)
    {
        NodePtr y;

        y = x->right;
        x->right = y->left;
        if (y->left != leafNode)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;

        if (!x->parent)
        {
            root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        x->parent = y;
        y->left = x;
    }
    /*x를 중심으로 오른쪽으로 회전*/
    void RotateRight(NodePtr y)
    {
        NodePtr x;

        x = y->left;
        y->left = x->right;
        if (x->right != leafNode)
        {
            x->right->parent = y;
        }
        x->parent = y->parent;

        if (!y->parent)
        {
            root = x;
        }
        else if (y == y->parent->left)
        {
            y->parent->left = x;
        }
        else
        {
            y->parent->right = x;
        }
        y->parent = x;
        x->right = y;
    }

public:
    RBTREE()
    {
        leafNode = new node;
        leafNode->color = BLACK;
        leafNode->left = nullptr;
        leafNode->right = nullptr;
        leafNode->parent = nullptr;
        root = leafNode;
    }
    //최솟값 찾기
    NodePtr tree_minimum(NodePtr x)
    {
        while (x->left != leafNode)
        {
            x = x->left;
        }
        return x;
    }
    //최댓값 찾기
    NodePtr tree_maximum(NodePtr x)
    {
        while (x->right != leafNode)
        {
            x = x->right;
        }
        return x;
    }

    void Insert(int item, int weight)
    {
        // x : 삽입할 곳 찾기위한 포인터 | y : 삽입할 곳의 부모노드
        NodePtr x = this->root, y = nullptr;
        NodePtr z = new node();
        z->key = item;
        z->color = RED;
        z->parent = nullptr;
        z->left = leafNode;
        z->right = leafNode;
        z->weight = weight;

        /*BST의 일반 삽입 연산*/
        while (x != leafNode)
        {
            y = x;
            if (x->key < item)
                x = x->right;
            else
                x = x->left;
        }

        z->parent = y;

        if (y == nullptr)
            root = z;
        else if (z->key > y->key)
            y->right = z;
        else
            y->left = z;

        //z가 root노드라면
        if (z->parent == nullptr)
        {
            z->color = BLACK;
            return;
        }
        // z의 부모노드가 root노드라면 Fix Up 필요없이 red컬러로 붙여주면 된다.
        if (z->parent->parent == nullptr)
        {
            return;
        }
        InsertFixUp(z);

        return;
    }

    bool Delete(int item)
    {
        NodePtr z = IsKey(item);
        if (!z)
            return false;
        else
        {
            NodePtr x, y;
            Color OriginalColor = z->color;

            /*자식이 없거나 1개인 경우
                    삭제할 노드(z)가 블랙이면 doulbe red이므로 fix*/
            if (z->left == leafNode)
            {
                x = z->right;
                Transplant(z, z->right);
            }
            else if (z->right == leafNode)
            {
                x = z->left;
                Transplant(z, z->left);
            }
            else
            {
                y = tree_minimum(z->right);
                OriginalColor = y->color;
                x = y->right; //y의 왼쪽 자식은 없다.

                if (y->parent == z)
                {                  //z의 오른쪽 자식이 가장 작은 key
                    x->parent = y; // x가 leafnode일 때, fix하게 될 때 사용
                }
                else
                {
                    Transplant(y, y->right);
                    y->right = z->right;
                    y->right->parent = y;
                }
                Transplant(z, y);
                y->left = z->left;
                y->left->parent = y;
                y->color = z->color;
            }
            delete z;
            if (OriginalColor == BLACK)
            {
                DelteFixUp(x);
            }
        }
        return true;
    }
};

