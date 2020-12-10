/// ************************************************

/*      TRATAMENTO DA LISTA

*/
/// *************************************************

typedef struct dataNode{
    int value;
} DataNode;

typedef struct node {
    DataNode data;
    struct node *next;
} Node;

typedef struct list {
    int size;
    Node* head;
} List;

BITMAP* printList(List *list);
/*
    cria lista
*/
List *newList();

/*
    adiciona novo valor a lista na frente
*/
void push(List *list, DataNode data);

/*
    apaga o primeiro elemento da lista
*/
void pop(List *list);

/*
    verifica se a lista está vazia
*/
bool isEmpty(List *list);

/*
    retorna um nó de uma posição index
*/
Node *atPos(List *list, int index);

/*
    retorna a posição de nó
*/
int indexOf(List *list, Node* node);

/*
    apaga o nó informado
*/
void erase(List *list, int index);

/*
    inverte as posições do nodeA com o nodeB.
*/
void exchange(List *list, Node* nodeA, Node* nodeB);

/*
    retorna o nó com o conteudo de valor mínimo.
*/
Node* min(List *list, int index);

/*
    retorna o nó com o conteudo de valor máximo.
*/
Node *max(List *list, int index);

/*
    organiza os nós da lista em ordem crescente em relação ao conteudo delas
*/
List* incSort(List* list);

/*
    organiza os nós da lista em ordem decrescente em relação ao conteudo delas
*/
void decSort(List* list);
/*
    limpa a lista
*/
void destroyList(List *list);


void destroyList(List* list){
    Node* pointer = list -> head;
    while(pointer != NULL){
        pop(list);
        pointer = pointer -> next;
    }
}

List *newList(){
    List *list = (List*) malloc(sizeof(List));

    list -> size = 0;
    list -> head = NULL;

    return list;
}

void push(List *list, DataNode data){
    Node* node = (Node*) malloc(sizeof(Node));

    node -> data = data;
    node -> next = NULL;

    if(isEmpty(list))
        list -> head = node;
    else {
        Node* last = atPos(list, (list -> size)-1);
        last -> next = node;
    }

    list -> size++;
}


bool isEmpty(List *list){
    return (list->size == 0);
}

void pop(List *list){
    if(!isEmpty(list)){
        Node *pointer   = list -> head;
        list -> head    = pointer -> next;

        free(pointer);

        list -> size--;
    }
}

Node *atPos(List *list, int index){
    if(index > -1 && (list -> size) > index){
        Node *node = list -> head;

        int i;

        for(i = 0; i < index; i++){

            node = node -> next;
        }

        return node;
    }
    return NULL;
}

int indexOf(List *list, Node* node){
    if(!isEmpty(list) && node != NULL){

        int i = 0;
        Node *n = list -> head;
        while(n -> next != NULL){
            if(node == n){
                return i;
            }
            n = n -> next;
            i++;
        }

        return -1;
    }

    return -1;
}

// trocamos as posições do nó A com o nó B, sempre de A para B.
void exchange(List *list, Node* nodeA, Node* nodeB){

    if(nodeA == nodeB)
        return;

    int indexA  = indexOf(list, nodeA);
    int indexB  = indexOf(list, nodeB);

    if(indexA == -1 || indexB == -1)
        return;

        // como iremos trocar de
    if(indexA > indexB){
            // se o nodeA estiver depois do nodeB
        nodeA = nodeB;
        nodeB = atPos(list, indexA);

        /*
        a variável nodeA passa a armazenar o endereço(ou o nó mesmo) do nodeB
        e a variável nodeB passa a armazenar o endereço(ou o nó mesmo) do nodeA
        é como uma troca de nomes apenas, o conteudo nodeA e nodeB estão na mesma posição
        isso será útil para fazer a operação apenas uma vez para o caso de nodeA ou nodeB na frente.
        Observe em [1]
        */

        // invertemos os indexs também
        indexA = indexB;
        indexB = indexOf(list, nodeB);
    }

    // previus nodeB
    Node* pb = atPos(list, indexB - 1);

    if(nodeA == list->head){
            // caso nodeA seja a cabeça, então o nodeB passa a ser a cabeça.
        list->head = nodeB;

    } else {
        // Node *previusNodeA armazena o endereço do nó anterior ao nó A.
        Node* pa      = atPos(list, indexA -1);
        pa -> next    = nodeB;
    }

    // o próximo do nó anterior a b, vai se o nó A
    pb -> next      = nodeA;

    // nodeA passa a apontar para o nó que nodeB aponta
    // nodeB passa a apontar para o nó que nodeA apontava.
    Node *pointer   = nodeA -> next;
    nodeA -> next   = nodeB -> next;
    nodeB -> next   = pointer;
}

Node *max(List *list, int index){
    Node *pointer = atPos(list, index);
    if(pointer != NULL){

        Node *maxNode = pointer;

        while(pointer != NULL){
            if(pointer -> data.value > maxNode -> data.value)
                maxNode = pointer;
            pointer = pointer -> next;
        }

        return maxNode;
    }

    return NULL;
}

void decSort(List* list){
    int i;

    for(i = 0; i <= (list -> size); i++){

        exchange(list, atPos(list, i), max(list, i));
    }

}
