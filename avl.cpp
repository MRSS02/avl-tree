#include <iostream>

using namespace std;

typedef struct node 
{
    int key;
    struct node *left_node;
    struct node *right_node;
    int height;
} node;

class avl_tree
{
    public: 
        node* root = NULL;

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


node* avl_tree::insert(node* ,int value)
{
    //TODO
    return NULL;
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

