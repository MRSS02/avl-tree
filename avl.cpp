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

        void insert(int);
        void remove(int);
        void search(int);
        void left_right_rotation();
        void right_left_rotation();
        void double_left_rotation();
        void double_right_rotation();
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

            avl.insert(value);

            break;
        
        case 2:
            cout << "Digite o numero que deseja remover: ";
            cin >> value;

            avl.remove(value);

            break;

        case 3:
            cout << "Digite o numero que deseja buscar: ";
            cin >> value;

            avl.remove(value);

            break;

        case 4:
            return 0;

        default:
            cout << "Opcao invalida" << endl;
            break;
        }
    }
}

void avl_tree::insert(int value)
{
    //TODO
}

void avl_tree::remove(int value)
{
    //TODO
}

void avl_tree::search(int value)
{
    //TODO
}

void avl_tree::left_right_rotation()
{
    //TODO
}

void avl_tree::right_left_rotation()
{
    //TODO
}

void avl_tree::double_left_rotation()
{
    //TODO
}

void avl_tree::double_right_rotation()
{
    //TODO
}

