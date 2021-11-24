#include <iostream>

using namespace std;

struct node 
{
    int key;
    struct node *left_node;
    struct node *right_node;
    int height;
};

class avl_tree
{
    public: 
        node* root = NULL;

        int height (node*);
        node* insert(node*, int);
        node* remove(node*, int);
        node* search(node*, int);
        node* single_left_rotation(node*);
        node* single_right_rotation(node*);
        node* double_left_rotation(node*);
        node* double_right_rotation(node*);
};

int main() 
{
    avl_tree avl;
    int choice, value;

    while (true)
    {   
        cout << "-----------------------------------" << endl;
        cout << "                AVL                " << endl;
        cout << "-----------------------------------" << endl;
        cout << "  1 - Inserir elemento na arvore" << endl;
        cout << "  2 - Remover elemento na arvore" << endl;
        cout << "  3 - Buscar elemento na arvore" << endl;
        cout << "  4 - Encerrar o programa" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Digite o numero que deseja inserir: ";
            cin >> value;

            avl.root = avl.insert(avl.root, value);

            break;
        
        case 2:
            cout << "Digite o numero que deseja remover: ";
            cin >> value;

            avl.root = avl.remove(avl.root ,value);

            break;

        case 3:
            cout << "Digite o numero que deseja buscar: ";
            cin >> value;

            avl.search(avl.root, value);

            break;

        case 4:
            return 0;

        default:
            cout << "Opcao invalida" << endl;
            break;
        }
    }
}


int avl_tree::height(node* tree_node)
{
    return (tree_node == NULL ? -1 : tree_node->height);
}

node* avl_tree::insert(node* tree_node, int value)
{
    if (tree_node == NULL) 
    {
        tree_node = new node();

        tree_node->key = value;
        tree_node->height = 0;
        tree_node->left_node = tree_node->right_node = NULL;
    }
    else if (value < tree_node->key)
    {
        tree_node->left_node = insert(tree_node->left_node, value);
    }
    else
    {
        tree_node->right_node = insert(tree_node->right_node, value);
    }

    int left_height = height(tree_node->left_node);
    int right_height = height(tree_node->right_node);

    tree_node->height = (left_height >= right_height ? left_height : right_height) + 1;

    return tree_node;
}

node* avl_tree::remove(node* ,int value)
{
    //TODO
    return NULL;
}

node* avl_tree::search(node* ,int value)
{
    //TODO
    return NULL;
}

node* avl_tree::single_left_rotation(node*)
{
    //TODO
    return NULL;
}

node* avl_tree::single_right_rotation(node*)
{
    //TODO
    return NULL;
}

node* avl_tree::double_left_rotation(node*)
{
    //TODO
    return NULL;
}

node* avl_tree::double_right_rotation(node*)
{
    //TODO
    return NULL;
}

