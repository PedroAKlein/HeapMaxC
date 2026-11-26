#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 150

typedef struct heap {
    int heap[MAX];
    int tam;
} Heap;

void menu(int *opc);
void leInt(char* text, int *valor);
void leStr(char* text, char *s);
int checkStr(char* str);
void criaHeap(Heap *h);
int pai(int i);
int esquerda(int i);
int direita(int i);
void troca(Heap *h, int i);
void insere(Heap *h);
void upHeap(Heap *h, int i);
void imprime(Heap *h);
void removeHeap(Heap *h);
int buscaNo(Heap *h, int v);
void downHeap(Heap *h, int i);

int main(){
    Heap h;
    int opc = -1;
    
    criaHeap(&h);

    while(opc != 0){
        menu(&opc);

        switch(opc){
            case 1: insere(&h); break;
            case 2: removeHeap(&h); break;
            case 3: imprime(&h); break;
            case 0: printf("Saindo...\n\n"); break;
            default: printf("\nOpcao invalida!"); break;
        }
    }

    return 0;
}

void menu(int *opc){
    printf("\n---=== HEAP DE MAXIMO ===---\n");
    printf(" 1 - Inserir\n");
    printf(" 2 - Remover\n");
    printf(" 3 - Imprimir\n");
    printf(" 0 - Sair\n");
    leInt("Opcao", opc);
}

void leInt(char* text, int *valor){
    printf("%s: ", text);
    scanf("%d", valor);
    getchar();
}

void leStr(char* text, char *str){
    printf("%s: ", text);
    fgets(str, 32, stdin);

    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

int checkStr(char* str){
    if(str[0] == '-') return 1;
    if(str[0] == '1') return 1;
    if(str[0] == '2') return 1;
    if(str[0] == '3') return 1;
    if(str[0] == '4') return 1;
    if(str[0] == '5') return 1;
    if(str[0] == '6') return 1;
    if(str[0] == '7') return 1;
    if(str[0] == '8') return 1;
    if(str[0] == '9') return 1;
    if(str[0] == '0') return 1;
    if(str[0] == 'S') return 1;
    if(str[0] == 's') return 1;

    return 0;
}

void criaHeap(Heap *h){
    h->tam = 0;
}

int pai(int i){
    return (i - 1) / 2;
}

int esquerda(int i){
    return 2*i + 1;
}

int direita(int i){
    return 2*i + 2;
}

void troca(Heap *h, int i){
    int aux = h->heap[i];
    h->heap[i] = h->heap[pai(i)];
    h->heap[pai(i)] = aux;
}

void insere(Heap *h){
    char str[32];
    int v;
    
    printf("\n---=== INSERCAO ===---\n");

    while(1){
        if(h->tam == MAX){
            printf("Heap cheio!\n");
            return;
        }
    
        leStr("Inteiro para inserir (s/S para sair)", str);

        if(!checkStr(str)){
            printf("Entrada invalida!\n");
            continue;
        }

        if(str[0] == 's' || str[0] == 'S') break;
    
        v = atoi(str);
    
        h->heap[h->tam++] = v;
        upHeap(h, h->tam - 1);
    }
}

void upHeap(Heap *h, int i){
    while(i > 0){

        if(h->heap[i] > h->heap[pai(i)]){
            troca(h, i);
            i = pai(i);

        } else break;
    }
}

void imprime(Heap *h){
    printf("\n---=== IMPRESSAO ===---");

    if(h->tam == 0){
        printf("\nHeap vazio!");
        return;
    }

    for(int i = 0; i < h->tam; i++){
        int e = esquerda(i);
        int d = direita(i);

        printf("\nNo %d (%d): ", i, h->heap[i]);

        printf("Esq: ");
        if(e < h->tam) printf("%d", h->heap[e]);
        else printf("#");

        printf(" Dir: ");
        if(d < h->tam) printf("%d", h->heap[d]);
        else printf("#");
    }

    printf("\n");
}

void removeHeap(Heap *h){
    char str[32];
    int v;
    int i;

    printf("\n---=== REMOCAO ===---\n");

    while(1){
        if(h->tam == 0){
            printf("Heap vazio!\n");
            return;
        }
    
        leStr("Inteiro para remover (s/S para sair)", str);
    
        if(str[0] == 's' || str[0] == 'S') break;
        
        v = atoi(str);

        i = buscaNo(h, v);

        if(i == -1){
            printf("No nao existe!\n");
            continue;
        }

        if(i != h->tam - 1){
            h->heap[i] = h->heap[h->tam-1];
        }
        
        h->tam--;
        
        if(i < h->tam){
            upHeap(h, i);
            downHeap(h, i); 
        } 
    }
}

int buscaNo(Heap *h, int v){
    for(int i = 0; i < h->tam; i++){
        if(h->heap[i] == v){
            return i;
        }
    }

    return -1;
}

void downHeap(Heap *h, int i){
    int maiorFilho;
    while(1){
        int d = direita(i);
        int e = esquerda(i);

        if(d < h->tam){
            if(h->heap[d] > h->heap[e]) maiorFilho = d;
            else maiorFilho = e;
        
        } else if(e < h->tam) maiorFilho = e;

        else break; 

        if(h->heap[i] >= h->heap[maiorFilho]) break;
        else troca(h, maiorFilho);

        i = maiorFilho;
    }
}