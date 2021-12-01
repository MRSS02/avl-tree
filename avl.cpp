#include <iostream>
#include <string>

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
        node* root = NULL;

        int height (node*);
        void cleanup(node*);
        void display(node*, int);

        node* insert(node*, int, string);
        node* remove(node*, node*, bool);
        node* search(node*, int);

        node* single_left_rotation(node*);
        node* single_right_rotation(node*);
        node* double_left_rotation(node*);
        node* double_right_rotation(node*);
};

int main()
{
    avl_tree avl;
    int choice, key;
    string data;
    node* found = NULL;

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
        cout << "  5 - Encerrar o programa" << endl << endl;
        cout << "Escolha uma operacao: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Digite o valor da chave que deseja inserir: ";
            cin >> key;
            found = avl.search(avl.root, key);
            if (found == NULL) {
                cout << endl << "Digite o dado que deseja guardar nesse no: ";

                cin.ignore();
                getline(cin, data);
                avl.root = avl.insert(avl.root, key, data);
            } else cout << "O no " << key << " ja se encontra na árvore.";

            break;

        case 2: 
        {
            cout << "Digite a chave do no que deseja remover: ";
            cin >> key;

            found = avl.search(avl.root, key);
            avl.root = avl.remove(found, avl.root, true);
            if (found == NULL) cout << "O no " << key << " não foi encontrado.";
            else cout << "O no " << key << " foi removido com sucesso.";
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
            cout << endl << endl << "--------------Esquerda-------------" << endl;
            break;

        case 5:
            avl.cleanup(avl.root);
            return 0;

        default:
            cout << "Operacao invalida";
            break;
        }

        cout << endl << endl;
    }
}


int avl_tree::height(node* tree_node)
{
    return (tree_node == NULL ? -1 : tree_node->height);
}

void avl_tree::display(node* tree_node, int level)
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
            cout<<"        ";
        }

        cout << tree_node->key;

        display(tree_node->left_node, level + 1);
    }
}

// Liberar memória dinamicamente alocada com o operador new
void avl_tree::cleanup(node* tree_node)
{
    if (tree_node == NULL)
    {
        return;
    }

    cleanup(tree_node->left_node);
    cleanup(tree_node->right_node);

    delete tree_node;
}

// // A utility function to get the
// // height of the tree
int height(node *tree_node)
{
    if (tree_node == NULL)
        return 0;
    return tree_node->height;
}

// A utility function to get maximum
// of two integers
// int max(int a, int b)
// {
//     return (a > b)? a : b;
// }

int getHeight(node *tree_node) 
{
    int left_height = height(tree_node->left_node);
    int right_height = height(tree_node->right_node);
    return (left_height >= right_height ? left_height : right_height) + 1;
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
node *rightRotate(node *y)
{
    node *x = y->left_node;
    node *T2 = x->right_node;

    // Perform rotation
    if (x != NULL) x->right_node = y;
    y->parent_node = x;
    y->left_node = T2;
    if (T2 != NULL) T2->parent_node = y;

    // Update heights
    y->height = getHeight(y);
    x->height = getHeight(x);

    // Return new root
    return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
node *leftRotate(node *x)
{
    node *y = x->right_node;
    node *T2 = y->left_node;

    // Perform rotation
    if (y != NULL) y->left_node = x;
    x->parent_node = y;
    x->right_node = T2;
    if (T2 != NULL) T2->parent_node = x;

    // Update heights
    x->height = getHeight(x);
    y->height = getHeight(y);

    // Return new root
    return y;
}

int getBalance(node *tree_node)
{
    if (tree_node == NULL)
        return 0;
    return height(tree_node->left_node) - height(tree_node->right_node);
}

node* avl_tree::insert(node* tree_node, int key, string data)
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

    tree_node->height = getHeight(tree_node);

    int balance = getBalance(tree_node);
    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && tree_node->left_node != NULL && key < tree_node->left_node->key)
    {
        return rightRotate(tree_node);
    }
    // Right Right Case
    if (balance < -1 && tree_node->right_node != NULL && key > tree_node->right_node->key)
    {
        return leftRotate(tree_node);
    }
    // Left Right Case
    if (balance > 1 && tree_node->left_node != NULL && key > tree_node->left_node->key)
    {
        tree_node->left_node = leftRotate(tree_node->left_node);
        return rightRotate(tree_node);
    }

    // Right Left Case
    if (balance < -1 && tree_node->right_node != NULL && key < tree_node->right_node->key)
    {
        tree_node->right_node = rightRotate(tree_node->right_node);
        return leftRotate(tree_node);
    }

    // retorna o Nó não modificado.
    return tree_node;
}

node* avl_tree::remove(node* to_remove, node* root, bool needs_to_free)
{

    if (to_remove != NULL) 
        if (to_remove->left_node == NULL && to_remove->right_node == NULL) {
            if (to_remove == root) {
                root = NULL;
            } else {
                if (to_remove->parent_node->left_node == to_remove)
                    to_remove->parent_node->left_node = NULL;
                else to_remove->parent_node->right_node = NULL;

            }
        } else {
            if (to_remove->right_node == NULL && to_remove->left_node != NULL) { 
                if (to_remove == root) {
                    to_remove->left_node->parent_node = NULL;
                    root = to_remove->left_node;
                } else {
                    to_remove->left_node->parent_node = to_remove->parent_node;
                    if (to_remove->parent_node->left_node == to_remove)
                        to_remove->parent_node->left_node = to_remove->left_node;
                    else to_remove->parent_node->right_node = to_remove->left_node;

                }
            } else {
                if (to_remove->left_node == NULL && to_remove->right_node != NULL) { 
                    if (to_remove == root) {
                        to_remove->right_node->parent_node = NULL;
                        root = to_remove->right_node;
                    } else {
                        to_remove->right_node->parent_node = to_remove->parent_node;
                        if (to_remove->parent_node->left_node == to_remove)
                            to_remove->parent_node->left_node = to_remove->right_node;
                        else to_remove->parent_node->right_node = to_remove->right_node;
                    }
                } else {
                    node* replacement_node = to_remove->right_node;
                    while (replacement_node->left_node != NULL) 
                        replacement_node = replacement_node->left_node;
                    remove(replacement_node, root, false); 
                    if (to_remove == root) root = replacement_node;
                    else {
                        replacement_node->parent_node = to_remove->parent_node;
                        if (to_remove->parent_node->left_node == to_remove) to_remove->parent_node->left_node = replacement_node;
                        else to_remove->parent_node->right_node = replacement_node;
                    }
                    replacement_node->left_node = to_remove->left_node;
                    replacement_node->right_node = to_remove->right_node;
                    
                }
            }
        } 
        if (needs_to_free) free(to_remove);

    return root;
}

node* avl_tree::search(node* tree_node, int key)
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

