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
    printf("Witaj w twojej liscie zakupow!\n");
    printf("Wybierz opcje:\n1. Dodaj produkt.\n2. Wyswietl liste zakupow.\n3. Zapisz Liste zakupow do pliku.\n4. Wczytaj liste zakupow z pliku");
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
            case 4:
                system("cls");
                Wczytaj(*ListaZakupow);
                break;
            default:
                printf("Wybierz odpowiednia opcje\n");
                break;
        }
    }
}

void PowrotDoMenu(Zakupy* ListaZakupow) {
    printf("\nNacisnij cokolwiek, aby wrocic...\n");
    getch();
    system("cls");
    Menu(&ListaZakupow);
}

void Dodawanie(Zakupy** ListaZakupow) {
    printf("Jaki produkt chcesz dodac?\n");
    char produkt[100];
    fgets(produkt, sizeof(produkt), stdin);
    produkt[strcspn(produkt, "\n")] = '\0';
    printf("Jaka ilosc?\n");
    int ile;
    scanf("%d", &ile);

    printf("Jaka jest cena za sztuke?\n");
    float cena;
    scanf("%fl", &cena);
    cena = round(cena * 100) / 100;

    // Dodawanie produktu do listy zakupow
    Zakupy* nowyProdukt = (Zakupy*)malloc(sizeof(Zakupy));
    if (nowyProdukt == NULL) {
        printf("Nie udalo sie dodac produktu!\n");
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
        printf("Lista zakupow jest pusta.\n");
        PowrotDoMenu(ListaZakupow);
    }

    //calaCena cos odpierdala i czasami musisz 2 razy wejsc w wyswietlanie listy huj wie czemo
    Zakupy* temp = ListaZakupow;
    while (temp != NULL) {
        calaCena = temp->Cena * temp->Ilosc;
        printf("Produkt: %s Ilosc: %d Cena za sztuke: %.2fzl Cena za wszystkie: %.2fzl\n", temp->Produkt, temp->Ilosc, temp->Cena, calaCena);
        temp = temp->next;
    }

    PowrotDoMenu(ListaZakupow);
}

void Zapisz(Zakupy* ListaZakupow) {
    FILE *plik = fopen("zakupy.txt", "w");
    if (plik == NULL) {
        printf("Blad zapisu!\n");
        PowrotDoMenu(ListaZakupow);
    }

    Zakupy* temp = ListaZakupow;
    while (temp != NULL) {
        fprintf(plik, "%s,%d,%d\n", temp->Produkt, temp->Ilosc, temp->Cena);
        temp = temp->next;
    }
    fclose(plik);
    printf("Lista zakupow zostala zapisana do pliku.\n");
    PowrotDoMenu(ListaZakupow);
}
void Wczytaj(Zakupy** ListaZakupow) {
    FILE* plik = fopen("zakupy.txt", "r");
    if (plik == NULL) {
        printf("Blad otwarcia pliku!\n");
        PowrotDoMenu(*ListaZakupow);
    }

    char linia[200];
    while (fgets(linia, sizeof(linia), plik)) {
        linia[strcspn(linia, "\n")] = '\0';

        char produkt[100];
        int ilosc;
        double cena;

        if (sscanf(linia, "%99[^,],%d,%lf", produkt, &ilosc, &cena) != 3) {
            printf("Blad w formacie pliku: %s\n", linia);
            continue;
        }

        Zakupy* nowyProdukt = (Zakupy*)malloc(sizeof(Zakupy));
        if (nowyProdukt == NULL) {
            printf("Blad alokacji pamieci!\n");
            fclose(plik);
            PowrotDoMenu(*ListaZakupow);
        }

        strcpy(nowyProdukt->Produkt, produkt);
        nowyProdukt->Ilosc = ilosc;
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
    }

    fclose(plik);
    printf("Lista zakupow zostala wczytana z pliku.\n");
    PowrotDoMenu(*ListaZakupow);
}





int main(int argc, char const *argv[]) {
    Zakupy* ListaZakupow = NULL;
    setlocale(LC_CTYPE, "Polish");
    system("color 0a");
    Menu(&ListaZakupow);
}
