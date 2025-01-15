#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct ListElement {
    int Ilosc;
    double Cena;
    char Produkt[100];
    struct ListElement* next;
} Zakupy;

//Glowne menu aplikacji, wybieramy co chcemy zrobic (dodac produkt, wyswietlic liste zakupow, zapisac lub wczytac ja)
void Menu(Zakupy** ListaZakupow) {
    printf("Witaj w twojej liscie zakupow!\n");
    printf("Wybierz opcje:\n1. Dodaj produkt.\n2. Wyswietl liste zakupow.\n3. Zapisz swoja liste zakupow.\n4. Wczytaj liste zakupow\n");
    int wybor;
    while(1){
        scanf("%d", &wybor);
        while (getchar() != '\n');
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

//Funkcja pozwala na powrot do glownego menu po kliknieciu jakiegokolwiek przycisku
void PowrotDoMenu(Zakupy* ListaZakupow) {
    printf("\nNacisnij cokolwiek, aby wrocic...\n");
    getch();
    system("cls");
    Menu(&ListaZakupow);
}

//Funkcja przyjmuje dane o produkcie i wywoluje funkcje ktora go dodaje do listy zakupow
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

    DodawanieProduktu(ListaZakupow, produkt, ile, cena);
    PowrotDoMenu(*ListaZakupow);
}

//funkcja przyjmuje informacje o produkcie i dodaje go do listy zakupow
void DodawanieProduktu(Zakupy** ListaZakupow, const char* produkt, int ilosc, double cena) {
    Zakupy* nowyProdukt = (Zakupy*)malloc(sizeof(Zakupy));
    if (nowyProdukt == NULL) {
        printf("Nie udalo sie dodac produktu!\n");
        return;
    }

    strcpy(nowyProdukt->Produkt, produkt);
    nowyProdukt->Ilosc = ilosc;
    nowyProdukt->Cena = cena;
    nowyProdukt->next = NULL;

    if (*ListaZakupow == NULL) {
        *ListaZakupow = nowyProdukt;
    } else {
        Zakupy* AktualnyProdukt = *ListaZakupow;
        while (AktualnyProdukt->next != NULL) {
            AktualnyProdukt = AktualnyProdukt->next;
        }
        AktualnyProdukt->next = nowyProdukt;
    }
    printf("Dodano produkt!\n");
}

//Funkcja wyswietla cala liste zakupow oraz oblicza cene calej listy zakupow. Wywoluje takze funkcje do obliczenia reszty.
void Wyswietl(Zakupy* ListaZakupow) {
    double calaCena;
    double CenaWszystkiego = 0;
    if (ListaZakupow == NULL) {
        printf("Lista zakupow jest pusta.\n");
        PowrotDoMenu(ListaZakupow);
    }

    Zakupy* temp = ListaZakupow;
    while (temp != NULL) {
        calaCena = temp->Cena * temp->Ilosc;
        CenaWszystkiego += calaCena;
        printf("Produkt: %s Ilosc: %d Cena za sztuke: %.2fzl Cena za wszystkie: %.2fzl\n", temp->Produkt, temp->Ilosc, temp->Cena, calaCena);
        temp = temp->next;
    }

    ObliczReszte(CenaWszystkiego);
    PowrotDoMenu(ListaZakupow);
}
//Funkcja przyjmuje cene calej listy zakupow i oblicza reszte z kwoty podanej przez uzytkownika
void ObliczReszte(double CenaWszystkiego){
    printf("\nPodaj jakim budzetem dysponujesz, aby obliczyc reszte jaka Ci zostanie po zakupach:\n");
    double budzet;
    scanf("%lf", &budzet);
    budzet = round(budzet * 100) / 100;
    double reszta;
    reszta = budzet - CenaWszystkiego;
    if(reszta < 0){
        printf("Nie stac Cie na te zakupy :( Brakuje ci: %.2fzl", -reszta);
    }
    else{
        printf("Reszta jaka zostanie Ci z zakupow: %.2fzl", reszta);
    }
}

//Funkcja zapisuje liste zakupow do pliku
void Zapisz(Zakupy* ListaZakupow) {
    FILE *plik = fopen("zakupy.txt", "w");
    if (plik == NULL) {
        printf("Blad zapisu!\n");
        PowrotDoMenu(ListaZakupow);
    }

    Zakupy* temp = ListaZakupow;
    while (temp != NULL) {
        fprintf(plik, "%s,%d,%.2f\n", temp->Produkt, temp->Ilosc, temp->Cena);
        temp = temp->next;
    }
    fclose(plik);
    printf("Lista zakupow zostala zapisana do pliku.\n");
    PowrotDoMenu(ListaZakupow);
}

//Funkcja wczytuje liste zakupow z pliku
void Wczytaj(Zakupy* ListaZakupow){

}

int main(int argc, char const *argv[]) {
    Zakupy* ListaZakupow = NULL;
    Menu(&ListaZakupow);
}
