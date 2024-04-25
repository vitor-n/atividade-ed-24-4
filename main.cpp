#include <iostream>

using std::endl;
using std::cout;
using std::cin;
using std::string;

typedef struct Node
{
    int iPayload;
    Node* ptrNext;
    Node* ptrPrev;
} Node;

// Não precisa ter uma struct pra lista encadeada.
// Fazer uma estrutura deixa mais organizado, mas não é obrigatório

Node* createNode(int);
Node* searchNodebyValue(Node** head, int iValue);
// Retornamos um ponteiro pra ponteiro

void insertFront(Node**, int);
void insertEnd(Node**, int);
void insertAfter(Node*, int);
void insertBefore(Node*, int);
void deleteNode (Node**, Node*);
void displayList(Node*);
void deleteNodebyValue(Node** head, int iValue);

int main()
{
    Node* head = nullptr;
    displayList(head);
    cout << "===============" << endl;
    insertEnd(&head, 0);
    insertEnd(&head, 1);
    insertEnd(&head, 3);
    insertEnd(&head, 7);
    // Verificando se foi corretamente adicionado a main
    displayList (head);

    cout << "===============" << endl;
    cout << "===============\n" << endl;

    displayList(head);
    cout << "Inserindo antes do 3: " << endl;
    insertBefore(searchNodebyValue(&head, 3), 42);
    displayList(head);

    cout << "\nInserindo antes do 7: " << endl;
    insertBefore(searchNodebyValue(&head, 7), 37);
    displayList(head);

    cout << "===============" << endl;

    cout << "Deletando node com valor 3:" << endl;
    deleteNodebyValue(&head, 3);
    displayList(head);

    cout << "===============" << endl;

    cout << "Procurando node com valor 42:" << endl;
    Node* temp = searchNodebyValue(&head, 42);

    cout << "Endereço: " << temp << endl;
    if (temp != nullptr) {
        cout << "Payload: " << temp->iPayload << endl;
    }
    else {
        cout << "Valor não encontrado" << endl;
    }

    return 0;
}

Node* createNode(int iPayload){
    Node* temp = (Node*) malloc(sizeof(Node));
    temp -> iPayload = iPayload;
    temp -> ptrNext = nullptr;
    temp -> ptrPrev = nullptr;
    return temp;
};

void displayList(Node* node)
{
    // Imprimimos que a lista está vazia
    if (node == nullptr){
        cout << "A lista esta vazia" << endl;
        return;
    }
    // Se não recebemos o head, não printamos
    if (node -> ptrPrev != nullptr){
        cout << "Meio ou fim da lista : não é possível realizar o display list" << endl;
        return;
    }
    Node* temp = node;
    
    cout << "Payload: ";
    // Percorremos a lista até seu fim
    while (temp != nullptr)
    {
        cout << temp->iPayload << " ";
        temp = temp->ptrNext;
    }
    cout << " " << endl;
    return;
};

void insertFront(Node** head , int iPayload ){
    Node* newNode = createNode(iPayload);
    // newNode->ptrPrev = nullptr;

    // Quando tivermos algo na lista
    if (*head != nullptr)
    {
        // Colocando o antes do atual head como new node
        (*head) -> ptrPrev = newNode;
        // Colocando o next do new node como head
        newNode -> ptrNext = (*head);
        // Colocando o head como new node
        (*head) = newNode; 

        return;
    }
    else 
    {
        // Basta setar
        (*head) = newNode; 
    }


}; // Todo;

void insertEnd(Node** head, int iPayload){
    Node* newNode = createNode(iPayload);
    // NewNode->ptrNext = nullptr;

    if (*head == nullptr)
    {
        // NewNode->ptrPrev = nullptr;

        // Derreferenciando um ponteiro
        (*head) = newNode;
        return;
    }

    Node* temp = (*head);

    // Percorremos a lista até seu fim
    while (temp -> ptrNext != nullptr)
    {
        // Vai para frente até ser nulo (último nó)
        temp = temp->ptrNext;
    }

    newNode -> ptrPrev = temp; // newNode aponta para o fim da lista
    temp -> ptrNext = newNode; // Antigo último elemento aponto para o ultimo nó
    return;
};

void insertAfter(Node* ptrLocation, int iPayload)
{
    if (ptrLocation == nullptr)
    {
        cout << "O no escolhido e nulo. Impossivel inserir" << endl;
        return;
    }
    else 
    {
        Node* newNode = createNode(iPayload);
        
        // Corrigir o nó a ser inserido
        newNode->ptrNext = ptrLocation -> ptrNext;
        newNode -> ptrPrev = ptrLocation;

        // Corrigir a lista
        ptrLocation -> ptrNext = newNode;

        // Checando se ele aponta para nulo
        if (newNode -> ptrNext != nullptr)
        {
            newNode -> ptrNext -> ptrPrev = newNode;

        }
    }
};

void deleteNode(Node** head, Node* ptrDelete)
{
	if (*head == nullptr || ptrDelete == nullptr)
	{
		cout << " Não foi possível remover." << endl;
		return;
	}

	// Caso o ptrDelete seja o primeiro elemento da lista
	if (*head == ptrDelete) (*head) = ptrDelete->ptrNext;

	// Se o ptrDelete não é o último nó
	if (ptrDelete->ptrNext != nullptr) ptrDelete->ptrNext->ptrPrev = ptrDelete->ptrPrev;

	// Se o ptrDelete não é o primeiro nó
	if (ptrDelete->ptrPrev != nullptr) ptrDelete->ptrPrev->ptrNext = ptrDelete->ptrNext;

	free(ptrDelete);
}

// Exercício 1. Elaborar a função void método insertBefore(Node*, int);
// Exercício 2. Elaborar a função void deleteNodebyValue(Node**, int);
// Exercício 3. Elaborar a função Node* searchNodebyValue(Node**, int);

void insertBefore(Node* ptrLocation, int iPayload) {
    if (ptrLocation == nullptr) {
        cout << "O no escolhido e nulo. Impossivel inserir" << endl;
        return;
    }

    else {
        Node* newNode = createNode(iPayload);
        
        // Corrigir o nó a ser inserido
        newNode->ptrPrev = ptrLocation->ptrPrev;
        newNode->ptrNext = ptrLocation;

        // Corrigir a lista
        ptrLocation -> ptrPrev = newNode;

        // Checando se ele aponta para nulo
        if (newNode->ptrPrev != nullptr) {
            newNode->ptrPrev->ptrNext = newNode;
        }
    }
};

void deleteNodebyValue(Node** head, int iValue) {
    if (*head == nullptr) {
        cout << "Nao e possivel procurar pois head e nulo" << endl;
        return;
    }
    if ((*head)->ptrPrev != nullptr) {
        cout << "Meio ou fim da lista: não é possível realizar a busca" << endl;
        return;
    }

    Node* temp = searchNodebyValue(head, iValue);
    if (temp == nullptr) {
        cout << "Valor nao encontrado" << endl;
        return;
    } else {
        deleteNode(head, temp);
    }
};

Node* searchNodebyValue(Node** head, int iValue) {
    /*
    Retorna um ponteiro para o nó que contém o valor desejado.
    */
    if (*head == nullptr) {
        cout << "Nao e possivel procurar pois head e nulo" << endl;
        return nullptr;
    } 
    if ((*head)->ptrPrev != nullptr) {
        cout << "Meio ou fim da lista: não é possível realizar a busca" << endl;
        return nullptr;
    }

    Node* temp = *head; // Ponteiro temporario para percorrer a lista
    Node* ptrSearch = nullptr; // Ponteiro para armazenar o nó com o valor desejado

    while (temp != nullptr) {
        if (temp->iPayload == iValue) {
            ptrSearch = temp; // Armazenamos o nó com o valor desejado
            break;
        }
        temp = temp->ptrNext; // Avança para o próximo nó
    }

    return ptrSearch;
};

