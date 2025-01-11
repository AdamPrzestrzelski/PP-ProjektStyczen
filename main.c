#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ListElement {
    int data;
    struct ListElement * next;
} ListElement_type;

void Dodawanie(){}
void Oblicz_cene(){}
void Oblicz_reszte(){}

int main(int argc, char const *argv[])
{ //B!tch I ain't commenting shit!!!
    ListElement_type* ListaZakupow =(ListElement_type*)malloc(sizeof(ListElement_type));
    printf("Wybierz opcje:\n1. Dodaj produkt.\n2. Oblicz cene zakupow.\n3. Oblicz reszte z podanej kwoty.");
    char wybor=' ';
    scanf("%s",(char*)wybor);

    switch (wybor)
    {
    case '1':
        Dodawanie();
        break;
    
    case '2':
        Oblicz_cene();
        break;
    
    case '3':
        Oblicz_reszte();
        break;
    
    default:
        system("clear");
        break;
    }
free(ListaZakupow);
    return 0;   
}
