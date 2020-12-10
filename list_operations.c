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
    verifica se a lista est� vazia
*/
bool isEmpty(List *list);

/*
    retorna um n� de uma posi��o index
*/
Node *atPos(List *list, int index);

/*
    retorna a posi��o de n�
*/
int indexOf(List *list, Node* node);

/*
    apaga o n� informado
*/
void erase(List *list, int index);

/*
    inverte as posi��es do nodeA com o nodeB.
*/
void exchange(List *list, Node* nodeA, Node* nodeB);

/*
    retorna o n� com o conteudo de valor m�nimo.
*/
Node* min(List *list, int index);

/*
    retorna o n� com o conteudo de valor m�ximo.
*/
Node *max(List *list, int index);

/*
    organiza os n�s da lista em ordem crescente em rela��o ao conteudo delas
*/
List* incSort(List* list);

/*
    organiza os n�s da lista em ordem decrescente em rela��o ao conteudo delas
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

// trocamos as posi��es do n� A com o n� B, sempre de A para B.
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
        a vari�vel nodeA passa a armazenar o endere�o(ou o n� mesmo) do nodeB
        e a vari�vel nodeB passa a armazenar o endere�o(ou o n� mesmo) do nodeA
        � como uma troca de nomes apenas, o conteudo nodeA e nodeB est�o na mesma posi��o
        isso ser� �til para fazer a opera��o apenas uma vez para o caso de nodeA ou nodeB na frente.
        Observe em [1]
        */

        // invertemos os indexs tamb�m
        indexA = indexB;
        indexB = indexOf(list, nodeB);
    }

    // previus nodeB
    Node* pb = atPos(list, indexB - 1);

    if(nodeA == list->head){
            // caso nodeA seja a cabe�a, ent�o o nodeB passa a ser a cabe�a.
        list->head = nodeB;

    } else {
        // Node *previusNodeA armazena o endere�o do n� anterior ao n� A.
        Node* pa      = atPos(list, indexA -1);
        pa -> next    = nodeB;
    }

    // o pr�ximo do n� anterior a b, vai se o n� A
    pb -> next      = nodeA;

    // nodeA passa a apontar para o n� que nodeB aponta
    // nodeB passa a apontar para o n� que nodeA apontava.
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
