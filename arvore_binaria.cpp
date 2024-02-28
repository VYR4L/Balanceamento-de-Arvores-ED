#include <iostream>
#include <cmath>

using namespace std;


class List_Node{
public:
    int dado;
    List_Node *prox;

    List_Node(int val){
        dado = val;
        prox = nullptr;
    }
};

class ListaOrdenada{
private:
    List_Node *lista;

public:
    ListaOrdenada(){
        lista = nullptr;
    }

    void inserir(int val){
        List_Node *new_node_list = new List_Node(val);

        if (lista == nullptr || val < lista->dado){
            new_node_list->prox = lista;
            lista = new_node_list;
            return;
        }

        List_Node *atual = lista;
        while (atual->prox != nullptr && atual->prox->dado <= val){
            atual = atual->prox;
        }

        new_node_list->prox = atual->prox;
        atual->prox = new_node_list;
    }

    int get_node_value(int index) {
        List_Node *atual = lista;
        for (int i = 0; i < index; ++i) {
            if (atual == nullptr)
                throw out_of_range("Índice fora do alcance da lista.");
            atual = atual->prox;
        }
        if (atual == nullptr)
            throw out_of_range("Índice fora do alcance da lista.");
        return atual->dado;
    }


    void remover(int val){
        if (lista == nullptr){
            return;
        }
        if (lista->dado == val){
            List_Node *temp = lista;
            lista = lista->prox;
            delete temp;
            return;
        }
        List_Node *atual = lista;
        while (atual->prox != nullptr && atual->prox->dado != val){
            atual = atual->prox;
        }
        if (atual->prox != nullptr){
            List_Node *temp = atual->prox;
            atual->prox = atual->prox->prox;
            delete temp;
        }
    }

List_Node* encontrar_mediana(List_Node* inicio, int tamanho) {
    List_Node* atual = inicio;
    for (int i = 0; i < tamanho / 2; ++i) {
        atual = atual->prox;
    }
    return atual;
}

List_Node* mediana_recursiva(List_Node* inicio, int tamanho) {
    if (tamanho == 1) {
        return inicio;
    }

    int nova_tamanho = (tamanho + 1) / 2;
    List_Node* mediana = encontrar_mediana(inicio, tamanho);
    return mediana_recursiva(mediana, nova_tamanho);
}

void mediana() {
    int counter = 0;
    List_Node* atual = lista;
    while (atual != nullptr) {
        counter += 1;
        atual = atual->prox;
    }

    if (counter == 0) {
        cout << "Lista vazia." << endl;
        return;
    }

    List_Node* mediana = mediana_recursiva(lista, counter);
    cout << "Mediana: " << mediana->dado << endl;
}
    void imprimir(){
        List_Node *atual = lista;
        while (atual != nullptr){
            std::cout << atual->dado << " ";
            atual = atual->prox;
        }
        std::cout << std::endl;
    }
};


class Node{
private:
    Node *left, *right;
    int key;

public:
    Node(int key){
        this->key = key;
        left = NULL;
        right = NULL;
    }
    int get_key(){
        return key;
    }
    Node* get_left(){
        return left;
    }
    Node* get_right(){
        return right;
    }
    void set_left(Node *node){
        left = node;
    }
    void set_right(Node *node){
        right = node;
    }
    void set_key(int new_key) {
        key = new_key;
    }
};


class Tree{
    Node *root;

public:
    Tree(){
        root = NULL;
    }
    void insert(int key){
        if (root == NULL){
            root = new Node(key);
        }
        else{
            insert_aux(root, key);
        }
    }
    void insert_aux(Node *node, int key){
        if (key < node->get_key()){
            if (node->get_left() == NULL){
                Node *new_node = new Node(key);
                node->set_left(new_node);
            }
            else{
                insert_aux(node->get_left(), key);
            }
        }
        else if(key > node->get_key()){
            if (node->get_right() == NULL){
                Node *new_node = new Node(key);
                node->set_right(new_node);
            }
            else{
                insert_aux(node->get_right(), key);
            }
        }
        else if(key == node->get_key()){
            cout << "Number already exists";
        }
    }
    Node* get_root(){
        return root;
    }
    void in_order(Node* node){
        if (node != NULL){
            in_order(node->get_left());
            cout << node->get_key() << " ";
            in_order(node->get_right());
        }
    }

    void insert_in_order(Node* node, ListaOrdenada &lista){
        if (node != NULL){
            insert_in_order(node->get_left(), lista);
            lista.inserir(node->get_key());
            insert_in_order(node->get_right(), lista);
        }
    }

    void insert_pre_order(Node* node, ListaOrdenada &lista) {
    if (node != NULL) {
        lista.inserir(node->get_key());
        insert_pre_order(node->get_left(), lista);
        insert_pre_order(node->get_right(), lista);
    }
}

    void pre_order(Node* node){
        if (node != NULL){
            cout << node->get_key() << " ";
            pre_order(node->get_left());
            pre_order(node->get_right());
        }
    }
    void post_order(Node* node){
        if (node != NULL){
            post_order(node->get_left());
            post_order(node->get_right());
            cout << node->get_key() << " ";
        }
    }
    Node* search(Node* node, int key){
        if (node == NULL || node->get_key() == key)
            return node;
        if (key < node->get_key())
            return search(node->get_left(), key);
        return search(node->get_right(), key);
    }
    void remove(int key){
        root = remove_aux(root, key);
    }
    Node* remove_aux(Node* node, int key){
        if (node == NULL) return node;

        if (key < node->get_key())
            node->set_left(remove_aux(node->get_left(), key));
        else if (key > node->get_key())
            node->set_right(remove_aux(node->get_right(), key));
        else {
            if (node->get_left() == NULL) {
                Node* temp = node->get_right();
                delete node;
                return temp;
            }
            else if (node->get_right() == NULL) {
                Node* temp = node->get_left();
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->get_right());
            node->set_key(temp->get_key());
            node->set_right(remove_aux(node->get_right(), temp->get_key()));
        }
        return node;
    }
    Node* minValueNode(Node* node){
        Node* current = node;
        while (current && current->get_left() != NULL)
            current = current->get_left();
        return current;
    }
    int get_tree_size(Node* node) {
            if (node == NULL)
                return 0;
            else
                return get_tree_size(node->get_left()) + 1 + get_tree_size(node->get_right());
        }

        void balance_tree() {
            int size = get_tree_size(root);
            if (size < 5) {
                cout << "A arvore nao precisa de balanceamento." << endl;
                return;
            }
            ListaOrdenada lista;
            insert_pre_order(root, lista);
            delete_tree(root);
            root = build_balanced_tree(lista, 0, size - 1);
        }

        void delete_tree(Node* node) {
            if (node == NULL) return;
            delete_tree(node->get_left());
            delete_tree(node->get_right());
            delete node;
        }

        Node* build_balanced_tree(ListaOrdenada &lista, int start, int end) {
            if (start > end) return NULL;
            int mid = (start + end) / 2;
            Node* node = new Node(lista.get_node_value(mid));
            node->set_left(build_balanced_tree(lista, start, mid - 1));
            node->set_right(build_balanced_tree(lista, mid + 1, end));
            return node;
        }
    };


int main() {
    Tree tree;

    int num_nodes;
    cout << "Insira o numero de nos: ";
    cin >> num_nodes;

    cout << "Insira os valores dos nos:\n";
    for (int i = 0; i < num_nodes; ++i) {
        int value;
        cin >> value;
        tree.insert(value);
    }

    cout << "Arvore antes do balanceamento:";
    tree.pre_order(tree.get_root());
    tree.balance_tree();

    cout << endl;

    cout << "Arvore depois do balanceamento:";
    tree.pre_order(tree.get_root());

    cout << endl;

    return 0;
}