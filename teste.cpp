#include <iostream>
#include <cmath>

using namespace std;

struct Date {
    int day;
    int month;
};

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
    Date date;

public:
    Node(Date date) {
        this->date = date;
        left = NULL;
        right = NULL;
    }

    Date get_date() {
        return date;
    }

    void set_date(Date new_date) {
        this->date = new_date;
    }

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
    void insert(Date date) {
    if (root == NULL) {
        root = new Node(date);
    } else {
        insert_aux(root, date);
    }
}

void insert_aux(Node *node, Date date) {
    if (compare_dates(date, node->get_date()) < 0) {
        if (node->get_left() == NULL) {
            Node *new_node = new Node(date);
            node->set_left(new_node);
        } else {
            insert_aux(node->get_left(), date);
        }
    } else {
        if (node->get_right() == NULL) {
            Node *new_node = new Node(date);
            node->set_right(new_node);
        } else {
            insert_aux(node->get_right(), date);
        }
    }
}

int compare_dates(Date date1, Date date2) {
    if (date1.month < date2.month) {
        return -1;
    } else if (date1.month > date2.month) {
        return 1;
    } else {
        return date1.day - date2.day;
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

    void insert_in_tree(Node* node, ListaOrdenada &lista) {
        if (node != NULL) {
            lista.inserir(node->get_date().day * 100 + node->get_date().month);
            insert_in_tree(node->get_left(), lista);
            insert_in_tree(node->get_right(), lista);
        }
    }


    void pre_order(Node* node){
    if (node != NULL){
        cout << node->get_date().day << "/" << node->get_date().month << " ";
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

    void update_value(Node* node, Date old_date, Date new_date) {
        if (node == nullptr) {
            return;
    }

    if (node->get_date().day == old_date.day && node->get_date().month == old_date.month) {
        node->set_date(new_date);
        return;
    }

    update_value(node->get_left(), old_date, new_date);
    update_value(node->get_right(), old_date, new_date);
    }

    void update_date(Date old_date, Date new_date) {
        update_value(root, old_date, new_date);
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
        insert_in_tree(root, lista);
        delete_tree(root);
        root = build_balanced_tree(lista, 0, size - 1);
    }

    Node* build_balanced_tree(ListaOrdenada &lista, int start, int end) {
        if (start > end) return NULL;
            int mid = (start + end) / 2;
            int mid_value = lista.get_node_value(mid);
            int day = mid_value / 100;
            int month = mid_value & 100;
            Date date = {day, month};
            Node *node = new Node(date);

            node->set_left(build_balanced_tree(lista, start, mid));
            node->set_right(build_balanced_tree(lista, mid +1, end));
            return node;
    }


    void delete_tree(Node* node) {
        if (node == NULL) return;
        delete_tree(node->get_left());
        delete_tree(node->get_right());
        delete node;
    }
    
    void encontrar_no(Node* node, Date target_date, Node*& result_node) {
        result_node = NULL;
        if (node == NULL) {
            return;
        }

        if (node->get_date().day == target_date.day && node->get_date().month == target_date.month) {
            result_node = node;
            return;
        }

        encontrar_no(node->get_left(), target_date, result_node);
        encontrar_no(node->get_right(), target_date, result_node);
    }
};


int main() {
    Tree tree;
    bool sair = false;

    while (!sair) {
        cout << "Escolha uma opcao:" << endl;
        cout << "a) Inserir valores na arvore" << endl;
        cout << "b) Balancear a arvore" << endl;
        cout << "c) Exibir arvore" << endl;
        cout << "d) Atualizar arvore" << endl;
        cout << "e) Sair do programa" << endl;

        char opcao;
        cin >> opcao;

        switch (opcao) {
            case 'a': {
                int num_nodes;
                cout << "Insira o numero de nos: ";
                cin >> num_nodes;

                cout << "Insira os valores dos nos (dia e mes separados por espaco):\n";
                for (int i = 0; i < num_nodes; ++i) {
                    int day, month;
                    cin >> day >> month;
                    Date date = {day, month};
                    tree.insert(date);
                }

                if (num_nodes >= 5) {
                    cout << "Balanceando a arvore automaticamente..." << endl;
                    tree.balance_tree();
                }
                break;
            }
            case 'b': {
                cout << "Balanceando a arvore..." << endl;
                tree.balance_tree();
                break;
            }
            case 'c': {
                if (tree.get_root() == NULL) {
                    cout << "Arvore vazia." << endl;
                } else {
                    cout << "Arvore:" << endl;
                    tree.pre_order(tree.get_root());
                    cout << endl;
                }
                break;
            }
            case 'd': {
                int day, month;
                int new_day, new_month;
                cout << "Digite a data que deseja alterar:" << endl;
                cin >> day >> month;
                Date old_date = {day, month};
                Node *old_date_node = NULL;
                tree.encontrar_no(tree.get_root(), old_date, old_date_node);
                if (old_date_node != NULL) {
                    cout << "Insira a nova data:" << endl;
                    cin >> new_day >> new_month;
                    Date new_date = {new_day, new_month};
                    old_date_node->set_date(new_date);
                    cout << "Data atualizada com sucesso!" << endl;
                } else {
                    cout << "Data nao encontrada na arvore." << endl;
                }
                break;
            }
            case 'e': {
                sair = true;
                break;
            }

            default: {
                cout << "Opcao invalida. Por favor, escolha novamente." << endl;
                break;
            }
        }
    }
    return 0;
}
