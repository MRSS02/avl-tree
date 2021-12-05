#include <iostream>
#include <string>
#include <limits>

using namespace std;

class node
{
public:
    int key;
    string data;
    node *parent_node;
    node *left_node;
    node *right_node;
    int height;
};

class avl_tree
{
public:
    node *root = NULL;

    int height(node *);
    int balance_factor(node *);
    void cleanup(node *);
    void display(node *, int);
    node *balance_node(node *);

    node *insert(node *, int, string);
    node *remove(node *, int);
    node *search(node *, int);
    node *append_and_balance(node *, node *);

    node *single_left_rotation(node *);
    node *single_right_rotation(node *);
    node *double_left_rotation(node *);
    node *double_right_rotation(node *);
};

int main()
{
    avl_tree avl;
    int choice, key;
    string data;
    node *found = NULL;

    while (true)
    {
        choice = key = 0;
        data = "";
        found = NULL;

        cout << "-----------------------------------" << endl;
        cout << "                AVL                " << endl;
        cout << "-----------------------------------" << endl;
        cout << "  1 - Inserir elemento na arvore" << endl;
        cout << "  2 - Remover elemento da arvore" << endl;
        cout << "  3 - Buscar elemento na arvore" << endl;
        cout << "  4 - Mostrar a arvore" << endl;
        cout << "  5 - Encerrar o programa" << endl
             << endl;
        cout << "Escolha uma operacao: ";

        cin >> choice;
        if (cin.fail())
        {
            cout << "Opcao invalida" << endl;

            cin.clear();

            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            continue;
        }

        switch (choice)
        {
        case 1:
            cout << "Digite o valor da chave que deseja inserir: ";
            cin >> key;

            if (cin.fail())
            {
                cout << "Opcao invalida, por favor insira um numero inteiro" << endl;

                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                break;
            }

            found = avl.search(avl.root, key);
            if (found == NULL)
            {
                cout << endl
                     << "Digite o dado que deseja guardar nesse no: ";

                cin.ignore();
                getline(cin, data);
                avl.root = avl.insert(avl.root, key, data);
            }
            else
                cout << "O no " << key << " ja se encontra na árvore.";

            break;

        case 2:
        {
            cout << "Digite a chave do no que deseja remover: ";
            cin >> key;

            if (cin.fail())
            {
                cout << "Opcao invalida" << endl;

                cin.clear();

                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                break;
            }

            found = avl.search(avl.root, key);
            if (found == NULL)
            {
                cout << "O no " << key << " não foi encontrado.";
            }
            else
            {
                avl.root = avl.remove(avl.root, key);
                cout << "O no " << key << " foi removido com sucesso.";
            }
        }
        break;

        case 3:
            cout << "Digite a chave do no que deseja buscar: ";
            cin >> key;

            found = avl.search(avl.root, key);
            if (found == NULL)
            {
                cout << "O no " << key << " nao foi encontrado.";
            }
            else
            {
                cout << "O no " << key << " guarda o valor " << found->data << ".";
            }

            break;

        case 4:
            cout << "--------------Direita--------------" << endl;
            avl.display(avl.root, 1);
            cout << endl
                 << endl
                 << "--------------Esquerda-------------" << endl;
            break;

        case 5:
            avl.cleanup(avl.root);
            return 0;

        default:
            cout << "Operacao invalida";
            break;
        }

        cout << endl
             << endl;
    }
}

void avl_tree::display(node *tree_node, int level)
{
    if (tree_node != NULL)
    {
        display(tree_node->right_node, level + 1);

        cout << endl;

        if (tree_node == root)
        {
            cout << "Raiz -> ";
        }

        for (int i = 0; i < level && tree_node != root; i++)
        {
            cout << "        ";
        }

        cout << tree_node->key;

        display(tree_node->left_node, level + 1);
    }
}

// Liberar memória dinamicamente alocada com o operador new
void avl_tree::cleanup(node *tree_node)
{
    if (tree_node == NULL)
    {
        return;
    }

    cleanup(tree_node->left_node);
    cleanup(tree_node->right_node);

    delete tree_node;
}

int avl_tree::height(node *tree_node)
{
    if (tree_node == NULL)
    {
        return -1;
    }

    int left_height = height(tree_node->left_node);
    int right_height = height(tree_node->right_node);

    return (left_height >= right_height ? left_height : right_height) + 1;
}

node *avl_tree::insert(node *tree_node, int key, string data)
{
    if (tree_node == NULL)
    {
        tree_node = new node();

        tree_node->key = key;
        tree_node->data = data;
        tree_node->height = 0;
        tree_node->left_node = tree_node->right_node = NULL;
    }
    else if (key < tree_node->key)
    {
        tree_node->left_node = insert(tree_node->left_node, key, data);
        tree_node->left_node->parent_node = tree_node;
    }
    else
    {
        tree_node->right_node = insert(tree_node->right_node, key, data);
        tree_node->right_node->parent_node = tree_node;
    }

    tree_node->height = height(tree_node);

    return balance_node(tree_node);
}

node *avl_tree::remove(node *tree_node, int key)
{
    if (tree_node->key < key)
    {
        tree_node->right_node = remove(tree_node->right_node, key);
    }
    else if (tree_node->key > key)
    {
        tree_node->left_node = remove(tree_node->left_node, key);
    }

    if (tree_node->key == key)
    {

        if (tree_node->left_node == NULL && tree_node->right_node == NULL)
        {
            delete tree_node;
            return NULL;
        }
        else if (tree_node->left_node == NULL)
        {
            tree_node->right_node->parent_node = tree_node->parent_node;
            node *node = tree_node->right_node;

            delete tree_node;
            return node;
        }
        else if (tree_node->right_node == NULL)
        {
            tree_node->left_node->parent_node = tree_node->parent_node;
            node *node = tree_node->left_node;

            delete tree_node;
            return node;
        }
        else
        {
            if (tree_node->parent_node->key < key)
            {
                tree_node->parent_node->right_node = tree_node->right_node;

                return append_and_balance(tree_node->right_node, tree_node->left_node);
            }
            else
            {
                tree_node->parent_node->left_node = tree_node->right_node;

                return append_and_balance(tree_node->right_node, tree_node->left_node);
            }
        }
    }

    return balance_node(tree_node);
}

node *avl_tree::append_and_balance(node *tree_node, node *node_to_append)
{
    if (tree_node == NULL)
    {
        return node_to_append;
    }

    tree_node->left_node = balance_node(append_and_balance(tree_node->left_node, node_to_append));
    return tree_node;
}

node *avl_tree::search(node *tree_node, int key)
{
    if (tree_node == NULL)
    {
        return NULL;
    }
    else if (tree_node->key == key)
    {
        return tree_node;
    }
    else if (key > tree_node->key)
    {
        return search(tree_node->right_node, key);
    }
    else
    {
        return search(tree_node->left_node, key);
    }
}

int avl_tree::balance_factor(node * tree_node)
{
    if (tree_node == NULL)
    {
        return 0;
    }

    return height(tree_node->left_node) - height(tree_node->right_node);
}

node *avl_tree::balance_node(node *tree_node)
{
    int balance = balance_factor(tree_node);
    int left_balance = balance_factor(tree_node->left_node);
    int right_balance = balance_factor(tree_node->right_node);

    if (balance > 1 && left_balance > 0)
        return single_right_rotation(tree_node);

    if (balance < -1 && right_balance < 0)
        return single_left_rotation(tree_node);

    if (balance > 1 && left_balance < 0)
    {
        tree_node->left_node = single_left_rotation(tree_node->left_node);
        return single_right_rotation(tree_node);
    }

    if (balance < -1 && right_balance > 0)
    {
        tree_node->right_node = single_right_rotation(tree_node->right_node);
        return single_left_rotation(tree_node);
    }

    return tree_node;
}

node *avl_tree::single_left_rotation(node *tree_node)
{
    node *right_node = tree_node->right_node;
    node *temp = right_node->left_node;

    right_node->left_node = tree_node;
    tree_node->right_node = temp;

    right_node->parent_node = tree_node->parent_node;
    tree_node->parent_node = right_node;

    tree_node->height = height(tree_node);
    right_node->height = height(right_node);

    return right_node;
}

node *avl_tree::single_right_rotation(node *tree_node)
{
    node *left_node = tree_node->left_node;
    node *temp = left_node->right_node;

    left_node->right_node = tree_node;
    tree_node->left_node = temp;

    left_node->parent_node = tree_node->parent_node;
    tree_node->parent_node = left_node;

    tree_node->height = height(tree_node);
    left_node->height = height(left_node);

    return left_node;
}

node *avl_tree::double_left_rotation(node *tree_node)
{
    tree_node->right_node = single_right_rotation(tree_node->right_node);
    return single_left_rotation(tree_node);
}

node *avl_tree::double_right_rotation(node *tree_node)
{
    tree_node->left_node = single_left_rotation(tree_node->left_node);
    return single_right_rotation(tree_node);
}
