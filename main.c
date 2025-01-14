#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct ListElement {
    int Ilosc;
    double Cena;
    char Produkt[100];
    struct ListElement* next;
} Zakupy;

void Menu(Zakupy** ListaZakupow) {
    printf("Witaj w twojej liœcie zakupów!\n");
    printf("Wybierz opcje:\n1. Dodaj produkt.\n2. Wyœwietl listê zakupów.\n3. Oblicz reszte z podanej kwoty.\n");
    int wybor;
    while(1){
        scanf("%d", &wybor);
        getchar();
        switch (wybor) {
            case 1:
                system("cls");
                Dodawanie(ListaZakupow);
                break;
            case 2:
                system("cls");
                Wyswietl(*ListaZakupow);
                break;
            case 3:
                system("cls");
                Zapisz(*ListaZakupow);
                break;
            default:
                printf("Wybierz odpowiedni¹ opcje\n");
                break;
        }
    }
}

void PowrotDoMenu(Zakupy* ListaZakupow) {
    printf("\nNaciœnij cokolwiek, aby wróciæ...\n");
    getch();
    system("cls");
    Menu(&ListaZakupow);
}

void Dodawanie(Zakupy** ListaZakupow) {
    printf("Jaki produkt chcesz dodaæ?\n");
    char produkt[100];
    fgets(produkt, sizeof(produkt), stdin);
    produkt[strcspn(produkt, "\n")] = '\0';
    printf("Jak¹ iloœæ?\n");
    int ile;
    scanf("%d", &ile);

    printf("Jaka jest cena za sztukê?\n");
    float cena;
    scanf("%fl", &cena);
    cena = round(cena * 100) / 100;

    // Dodawanie produktu do listy zakupów
    Zakupy* nowyProdukt = (Zakupy*)malloc(sizeof(Zakupy));
    if (nowyProdukt == NULL) {
        printf("Nie uda³o siê dodaæ produktu!\n");
        PowrotDoMenu(*ListaZakupow);
    }

    strcpy(nowyProdukt->Produkt, produkt);
    nowyProdukt->Ilosc = ile;
    nowyProdukt->Cena = cena;
    nowyProdukt->next = NULL;

    if (*ListaZakupow == NULL) {
        *ListaZakupow = nowyProdukt;
    } else {
        Zakupy* temp = *ListaZakupow;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nowyProdukt;
    }
    printf("Dodano produkt!\n");
    PowrotDoMenu(*ListaZakupow);
}

void Wyswietl(Zakupy* ListaZakupow) {
    double calaCena;
    if (ListaZakupow == NULL) {
        printf("Lista zakupów jest pusta.\n");
        PowrotDoMenu(ListaZakupow);
    }

    //calaCena cos odpierdala i czasami musisz 2 razy wejsc w wyswietlanie listy huj wie czemó
    Zakupy* temp = ListaZakupow;
    while (temp != NULL) {
        calaCena = temp->Cena * temp->Ilosc;
        printf("Produkt: %s Iloœæ: %d Cena za sztukê: %.2fz³ Cena za wszystkie: %.2fz³\n", temp->Produkt, temp->Ilosc, temp->Cena, calaCena);
        temp = temp->next;
    }

    PowrotDoMenu(ListaZakupow);
}

void Zapisz(Zakupy* ListaZakupow) {
    FILE *plik = fopen("zakupy.txt", "w");
    if (plik == NULL) {
        printf("B³¹d zapisu!\n");
        PowrotDoMenu(ListaZakupow);
    }

    Zakupy* temp = ListaZakupow;
    while (temp != NULL) {
        fprintf(plik, "%s,%d,%d\n", temp->Produkt, temp->Ilosc, temp->Cena);
        temp = temp->next;
    }
    fclose(plik);
    printf("Lista zakupów zosta³a zapisana do pliku.\n");
    PowrotDoMenu(ListaZakupow);
}

int main(int argc, char const *argv[]) {
    Zakupy* ListaZakupow = NULL;
    setlocale(LC_CTYPE, "Polish");
    Menu(&ListaZakupow);
}
