#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
const int os = 0;
#else
#include <unistd.h>
const int os = 1;
#endif

typedef struct Ogrenci{char ogrID[9]; char ad[30]; char soyad[30]; int puan; struct Ogrenci *next; struct Ogrenci *prev;}OGRENCI;
typedef struct Yazar{int yazarID; char ad[30]; char soyad[30]; struct Yazar *next;}YAZAR;
typedef struct KitapOrnek{char etiketNo[20]; char durum[9]; struct KitapOrnek *next;}KITAPORNEK;
typedef struct Kitap{char kitapAdi[30]; char ISBN[14]; int adet; struct Kitap *next; struct KitapOrnek *head;}KITAP;
typedef struct KitapYazar{char ISBN[14]; int yazarID;}KITAPYAZAR;
typedef struct Tarih{int gun:5; int ay:4; int yil:12;}TARIH;
typedef struct KitapOdunc{char etiketNo[20]; char ogrID[9]; int islemTipi:1; struct Tarih islemTarihi; struct KitapOdunc *next}KITAPODUNC;
void openMenu(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi);
void clearScreen();

void updateOduncler(KITAP **head, KITAP **tail, KITAPODUNC **headOdunc, KITAPODUNC **tailOdunc);

// Menu Islemleri Tanimlamalari
void ogrenciIslemleri(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi);
void kitapIslemleri(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi);
void yazarIslemleri(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi);

// Ogrenci Islemleri Tanimlamalari
void ogrenciEkleSilGuncelle(OGRENCI **head, OGRENCI **tail);
void ogrenciBilgisiGoruntuleme(OGRENCI **head, OGRENCI **tail);
void kitapTeslimEtmemisOgrencileriListele();
void cezaliOgrencileriListele(OGRENCI **head, OGRENCI **tail);
void tumOgrencileriListele(OGRENCI **head, OGRENCI **tail);
void kitapOduncAlTeslimEt();

// Kitap Islemleri Tanimlamalari
void kitapEkleSilGuncelle(KITAP **head, KITAP **tail);
void kitapBilgisiGoruntuleme();
void raftakiKitaplariListele(KITAP **head, KITAP **tail);
void zamanindaTeslimEdilmeyenKitaplariListele(KITAP **head, KITAP **tail, KITAPODUNC **headOdunc, KITAPODUNC **tailOdunc);
void kitapYazarEslestir();
void kitabinYazariniGuncelle(KITAPYAZAR **dizi);
void tumKitaplariListele(KITAP **head, KITAP **tail, KITAPYAZAR **dizi, YAZAR **yazarHead);

// Yazar Islemleri Tanimlamalari
void yazarEkleSilGuncelle(YAZAR** head, YAZAR** tail);
void yazarBilgisiGoruntuleme(YAZAR **head, YAZAR **tail);

void saveFile(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi);


int readFile(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi);
int readOgrenci(OGRENCI **head, OGRENCI **tail);
int readKitap(KITAP **head, KITAP **tail);
int readYazar(YAZAR **head, YAZAR **tail);
int readKitapOdunc(KITAPODUNC **head, KITAPODUNC **tail);
int readKitapYazar(KITAPYAZAR **dizi);

void saveOgrenci(OGRENCI **head, OGRENCI **tail);
void saveKitap(KITAP **head, KITAP **tail);
void saveYazar(YAZAR **head, YAZAR **tail);
void saveKitapOdunc(KITAPODUNC **head, KITAPODUNC **tail);
void saveKitapYazar(KITAPYAZAR **dizi);


int main(){
    OGRENCI *ogrenciHead = NULL;
    OGRENCI *ogrenciTail = NULL;

    YAZAR *yazarHead = NULL;
    YAZAR *yazarTail = NULL;

    KITAP *kitapHead = NULL;
    KITAP *kitapTail = NULL;

    KITAPODUNC *kitapOduncHead = NULL;
    KITAPODUNC *kitapOduncTail = NULL;

    KITAPYAZAR **kitapYazarDizi = NULL;

    clearScreen();
    int status;
    status = readFile(&ogrenciHead, &ogrenciTail, &kitapHead, &kitapTail, &yazarHead, &yazarTail, &kitapOduncHead, &kitapOduncTail, &kitapYazarDizi);
    if (status == 0)
    {
        printf("Dosya okuma basarisiz. Program sonlandiriliyor.\n");
        return 0;
    }
    updateOduncler(&kitapHead, &kitapTail, &kitapOduncHead, &kitapOduncTail);
    openMenu(ogrenciHead, ogrenciTail, kitapHead, kitapTail, yazarHead, yazarTail, kitapOduncHead, kitapOduncTail, kitapYazarDizi);
    saveFile(&ogrenciHead, &ogrenciTail, &kitapHead, &kitapTail, &yazarHead, &yazarTail, &kitapOduncHead, &kitapOduncTail, &kitapYazarDizi);

    return 0;
}

void openMenu(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi){
    int secim;
    int bos = 1;

    while(bos == 1){
    clearScreen();
    printf ("1. Ogrenci Islemleri;\n");
    printf ("2. Kitap Islemleri;\n");
    printf ("3. Yazar Islemleri;\n");
    printf ("4. Kaydet ve Cik;\n");

    scanf("%d", &secim);

    while (secim < 1 || secim > 4)
    {
        printf("Hatali secim yaptiniz. Tekrar deneyiniz.\n");
        scanf("%d", &secim);
    }

    switch(secim){
        case 1:
            ogrenciIslemleri(ogrenciHead, ogrenciTail, kitapHead, kitapTail, yazarHead, yazarTail, kitapOduncHead, kitapOduncTail, kitapYazarDizi);
            break;
        case 2:
            kitapIslemleri(ogrenciHead, ogrenciTail, kitapHead, kitapTail, yazarHead, yazarTail, kitapOduncHead, kitapOduncTail, kitapYazarDizi);
            break;
        case 3:
            yazarIslemleri(ogrenciHead, ogrenciTail, kitapHead, kitapTail, yazarHead, yazarTail, kitapOduncHead, kitapOduncTail, kitapYazarDizi);
            break;
        case 4:
            bos = 0;
            break;
    }
    }
}

void ogrenciIslemleri(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi){
    int secim;
    int bos = 1;
    while (bos == 1)
    {
    clearScreen();
    printf("1. Ogrenci Ekle, Sil, Guncelle\n");
    printf("2. Ogrenci Bilgisi Goruntuleme\n");
    printf("3. Kitap Teslim Etmemis Ogrencileri Listele\n");
    printf("4. Cezali Ogrencileri Listele\n");
    printf("5. Tum Ogrencileri Listele\n");
    printf("6. Kitap Odunc al/Teslim et\n");
    printf("7. Ana Menuye Don\n");
    scanf("%d", &secim);
    while (secim < 1 || secim > 7)
    {
        printf(("Hatali secim yaptiniz. Tekrar deneyiniz.\n"));
        scanf("%d", &secim);
    }
    switch(secim){
        case 1:
            ogrenciEkleSilGuncelle(&ogrenciHead, &ogrenciTail);
            break;
        case 2:
            ogrenciBilgisiGoruntuleme(&ogrenciHead, &ogrenciTail);
            break;
        case 3:
            kitapTeslimEtmemisOgrencileriListele();
            break;
        case 4:
            cezaliOgrencileriListele(&ogrenciHead, &ogrenciTail);
            break;
        case 5:
            tumOgrencileriListele(&ogrenciHead, &ogrenciTail);
            break;
        case 6:
            kitapOduncAlTeslimEt(&kitapHead, &kitapTail, &ogrenciHead, &ogrenciTail, &kitapOduncHead, &kitapOduncTail);
            break;
        case 7:
            bos = 0;
            break;
    }
    updateOduncler(&kitapHead, &kitapTail, &kitapOduncHead, &kitapOduncTail);
    }
}
void kitapIslemleri(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi){
    int secim;
    int bos = 1;

    while(bos == 1){
    clearScreen();
    printf("1. Kitap Ekle, Sil, Guncelle;\n");
    printf("2. Kitap Bilgisi Goruntuleme\n");
    printf("3. Raftaki Kitaplari Listele\n");
    printf("4. Zamaninda Teslim Edilmeyen Kitaplari Listele\n");
    printf("5. Kitap-Yazar Eslestir\n");
    printf("6. Kitabin yazarini Guncelle\n");
    printf("7. Tum Kitaplari Listele\n");
    printf("8. Ana Menuye Don\n");

    scanf("%d", &secim);

    while(secim < 1 || secim > 8)
    {
        printf("Hatali secim yaptiniz. Tekrar deneyiniz.\n");
        scanf("%d", &secim);
    }

    switch(secim){
        case 1:
            kitapEkleSilGuncelle(&kitapHead, &kitapTail);
            break;
        case 2:
            kitapBilgisiGoruntuleme(&kitapHead, &kitapTail);
            break;
        case 3:
            raftakiKitaplariListele(&kitapHead, &kitapTail);
            break;
        case 4:
            zamanindaTeslimEdilmeyenKitaplariListele(&kitapHead, &kitapTail, &kitapOduncHead, &kitapOduncTail);
            break;
        case 5:
            kitapYazarEslestir(&kitapYazarDizi);
            break;
        case 6:
            kitabinYazariniGuncelle(&kitapYazarDizi);
            break;
        case 7:
            tumKitaplariListele(&kitapHead, &kitapTail, &kitapYazarDizi, &yazarHead);
            break;
        case 8:
            bos = 0;
            break;
    }
    updateOduncler(&kitapHead, &kitapTail, &kitapOduncHead, &kitapOduncTail);
    }
}
void yazarIslemleri(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi){
    int secim;
    int bos = 1;
    while (bos == 1)
    {
    clearScreen();
    printf("1. Yazar Ekle, Sil, Guncelle;\n");
    printf("2. Yazar Bilgisi Goruntuleme\n");
    printf("3. Ana Menuye Don\n");

    scanf("%d", &secim);

    while(secim < 1 || secim > 3)
    {
        scanf("%d", &secim);
    }    

    switch(secim){
        case 1:
            yazarEkleSilGuncelle(&yazarHead, &yazarTail);
            break;
        case 2:
            yazarBilgisiGoruntuleme(&yazarHead, &yazarTail);
            break;
        case 3:
            bos = 0;
            break;
    }
    updateOduncler(&kitapHead, &kitapTail, &kitapOduncHead, &kitapOduncTail);
    }
}

// Ogrenci Islemleri
void ogrenciEkleSilGuncelle(OGRENCI **head, OGRENCI **tail){
    clearScreen();
    int secim;
    int i;
    int bos;

    printf("1. Ogrenci Ekle\n");
    printf("2. Ogrenci Sil\n");
    printf("3. Ogrenci Guncelle\n");
    scanf("%d", &secim);

    switch (secim)
    {
    case 1:
        clearScreen();
        int ogrenciSayisi;

        printf("Ogrenci Ekleme\n");
        printf("Eklemek istediginiz ogrenci sayisini giriniz:");
        scanf("%d", &ogrenciSayisi);

        for (i = 0; i < ogrenciSayisi; i++)
        {
            OGRENCI *tmp = (OGRENCI *)malloc(sizeof(OGRENCI));
            printf("\n%d. Ogrenci No Giriniz:",i+1);
            scanf("%s", tmp->ogrID);
            printf("%d. Ogrenci Adi Giriniz:",i+1);
            scanf("%s", tmp->ad);
            printf("%d .Ogrenci Soyadi Giriniz:",i+1);
            scanf("%s", tmp->soyad);
            tmp->puan = 100;

            if (*head == NULL)
            {
                *head = tmp;
                *tail = tmp;
                tmp->next = NULL;
            }
            else
            {
                tmp->prev = *tail;
                (*tail)->next = tmp;
                *tail = tmp;
                tmp->next = NULL;
            }
        }
        printf("\n");
        printf("%d tane ogrenci eklendi\n",ogrenciSayisi);
        break;
    case 2:
        clearScreen();
        char ogrNo[9];
        OGRENCI *tmp = NULL;
        int check = 1;

        printf("Ogrenci Silme\n");
        printf("Silmek istediginiz ogrenci no giriniz:");
        scanf("%s", ogrNo);
        tmp = (*head);
        
        while (check == 1)
        {
            if (strcmp(tmp->ogrID, ogrNo) == 0)
            {
                if (tmp->next == NULL && tmp->prev == NULL)
                {
                    *head = NULL;
                    *tail = NULL;
                }
                else if (tmp->next == NULL)
                {
                    (*tail) = tmp->prev;
                    (*tail)->next = NULL;
                }
                else if (tmp->prev == NULL)
                {
                    (*head) = tmp->next;
                    (*head)->prev = NULL;
                }
                else
                {
                    tmp->prev->next = tmp->next;
                    tmp->next->prev = tmp->prev;
                }
                printf("Ogrenci silindi\n");
                check = 0;
            }
            else{
                if (tmp->next != NULL)
                {
                    tmp = tmp->next;
                }
                else
                {
                    printf("Ogrenci bulunamadi\n");
                    check = 0;
                }
            }
        }
        break;
    case 3:
        clearScreen();
        char ogrNo2[9];
        OGRENCI *tmp2 = NULL;
        int check2 = 1;

        printf("Ogrenci Guncelleme\n");
        printf("Guncellemek istediginiz ogrenci no giriniz:");
        scanf("%s", ogrNo2);
        tmp2 = (*head);

        while (check2 == 1)
        {
            if (strcmp(tmp2->ogrID, ogrNo2) == 0)
            {
                printf("Ogrenci No: %s\n", tmp2->ogrID);
                printf("Ogrenci Adi: %s\n", tmp2->ad);
                printf("Ogrenci Soyadi: %s\n", tmp2->soyad);
                printf("Ogrenci Puan: %d\n", tmp2->puan);
                printf("Yeni Ogrenci No Giriniz:");
                scanf("%s", tmp2->ogrID);
                printf("Yeni Ogrenci Adi Giriniz:");
                scanf("%s", tmp2->ad);
                printf("Yeni Ogrenci Soyadi Giriniz:");
                scanf("%s", tmp2->soyad);
                printf("Yeni Ogrenci Puan Giriniz:");
                scanf("%d", &tmp2->puan);
                check2 = 0;
            }
            else{
                if (tmp2->next != NULL)
                {
                    tmp2 = tmp2->next;
                }
                else
                {
                    printf("Ogrenci bulunamadi\n");
                    check2 = 0;
                }
            }
        }
        
        break;
    default:
        break;
    }
    printf("\nGeri donmek icin 1 giriniz:");
    scanf("%d", &bos);

}
void ogrenciBilgisiGoruntuleme(OGRENCI **head, OGRENCI **tail){
    clearScreen();
    int bos;
    char ogrNo[9];
    OGRENCI *tmp = NULL;

    printf("Ogrenci No Giriniz:");

    scanf("%s", ogrNo);
    tmp = (*head);

    while (tmp->next != NULL && strcmp(tmp->ogrID, ogrNo) != 0)
    {
        tmp = tmp->next;
    }
    if (strcmp(tmp->ogrID, ogrNo) == 0)
    {
        printf("Ogrenci No: %s\n", tmp->ogrID);
        printf("Ogrenci Adi: %s\n", tmp->ad);
        printf("Ogrenci Soyadi: %s\n", tmp->soyad);
        printf("Ogrenci Puani: %d\n", tmp->puan);
        printf("\n");
    }
    else
    {
        printf("Ogrenci bulunamadi.\n");
    }
    printf("\nGeri donmek icin 1 giriniz:");
    scanf("%d", &bos);

}
void kitapTeslimEtmemisOgrencileriListele(){
    clearScreen();
}
void cezaliOgrencileriListele(OGRENCI **head, OGRENCI **tail){
    clearScreen();

    OGRENCI *tmp = NULL;
    tmp = (*head);
    int check = 1;
    int bos;
    printf("Cezali Ogrenciler:\n");
    while (check)
    {
        if (tmp->puan < 0)
        {
            printf("\n");
            printf("Ogrenci No: %s\n", tmp->ogrID);
            printf("Ogrenci Adi: %s\n", tmp->ad);
            printf("Ogrenci Soyadi: %s\n", tmp->soyad);
            printf("Ogrenci Puani: %d\n", tmp->puan);
            printf("\n");
        }
        if (tmp->next == NULL)
        {
            check = 0;
        }
        else
        {
            tmp = tmp->next;
        }
    }

    printf("Geri donmek icin 1 giriniz:");
    scanf("%d", &bos);
    
}
void tumOgrencileriListele(OGRENCI **head, OGRENCI **tail){
    clearScreen();
    int check = 1;
    int bos;

    OGRENCI *tmp = NULL;
    tmp = (*head);

    if (tmp == NULL)
    {
        printf("Liste bos.\n");
    }
    
    while (check)
    {
        printf("Ogrenci No: %s\n", tmp->ogrID);
        printf("Ogrenci Adi: %s\n", tmp->ad);
        printf("Ogrenci Soyadi: %s\n", tmp->soyad);
        printf("Ogrenci Puani: %d\n", tmp->puan);
        printf("\n");

        if (tmp->next == NULL)
        {
            check = 0;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    printf("\nGeri donmek icin 1 giriniz:");
    scanf("%d", &bos);
}
void kitapOduncAlTeslimEt(KITAP **head, KITAP **tail, OGRENCI **head2, OGRENCI **tail2,KITAPODUNC **head3, KITAPODUNC **tail3){
    clearScreen();
    printf("1. Kitap Odunc Al\n");
    printf("2. Kitap Teslim Et\n");
    int secim;
    int bos;
    scanf("%d", &secim);
    switch (secim)
    {
        case 1:
            clearScreen();
            printf("Kitap Odunc Alma\n");
            char kitapISBN[14];
            char ogrNo[9];
            int check = 1;
            int check2 = 1;
            int check3 = 1;
            KITAP *tmp = NULL;
            OGRENCI *tmp2 = NULL;
            KITAPORNEK *tmpORNEK = NULL;
            KITAPODUNC *tmp3 = NULL;
            tmp = (*head);
            tmp2 = (*head2);
            tmp3 = (*head3);

            int check4 = 1;

            
            printf("Kitap ISBN Giriniz:");
            scanf("%s", kitapISBN);
            printf("Ogrenci No Giriniz:");
            scanf("%s", ogrNo);
            
            while (check)
            {
                if (strcmp(tmp->ISBN, kitapISBN) == 0)
                {
                    check2 = 1;
                    while(check2){
                        if (strcmp(tmp2->ogrID, ogrNo) == 0)
                        {
                            tmpORNEK = tmp->head;
                            check3 = 1;
                            while(check3 == 1){
                                if (strcmp(tmpORNEK->durum,"Rafta") == 0 && check4 == 1)
                                {
                                    strcpy(tmpORNEK->durum,tmp2->ogrID);
                                    KITAPODUNC *yeni = (KITAPODUNC*)malloc(sizeof(KITAPODUNC));
                                    strcpy(yeni->etiketNo,tmpORNEK->etiketNo);

                                    int gun,ay,yil;
                                    gun = 1;
                                    ay = 1;
                                    yil = 2023;
                                    yeni->islemTarihi.gun = gun;
                                    yeni->islemTarihi.ay = ay;
                                    yeni->islemTarihi.yil = yil;
                                    yeni->islemTipi = 1;
                                    strcpy(yeni->ogrID,tmp2->ogrID);

                                    (*tail3)->next = yeni;
                                    yeni->next = NULL;
                                    (*tail3) = yeni;
                                    printf("%s Etiketli Kitap Odunc Alindi.\n",tmpORNEK->etiketNo);
                                    check4 = 0;
                                    
                                }
                                else
                                {
                                    if (tmpORNEK->next == NULL)
                                    {
                                        check3 = 0;
                                        check2 = 0;
                                        check = 0;
                                        
                                    }
                                    else
                                    {
                                        tmpORNEK = tmpORNEK->next;
                                    }
                                }
                                
                            }
                            
                        }
                        else
                        {
                            if (tmp2->next != NULL)
                            {
                                tmp2 = tmp2->next;
                            }
                            else
                            {
                                printf("Ogrenci bulunamadi\n");
                                check2 = 0;
                                check = 0;
                            }
                        }
                    }
                    
                }
                else
                {
                    if (tmp->next != NULL)
                    {
                        tmp = tmp->next;
                    }
                    else
                    {
                        printf("Kitap bulunamadi\n");
                        check = 0;
                    }
                }
            }

        break;

        case 2:
            clearScreen();
        break;

        default:
        break;
    }
    printf("Geri donmek icin 1 giriniz:");
    scanf("%d", &bos);

}

// Kitap Islemleri
void kitapEkleSilGuncelle(KITAP **head, KITAP **tail){
    clearScreen();
    printf("1. Kitap Ekle\n");
    printf("2. Kitap Sil\n");
    printf("3. Kitap Guncelle\n");
    KITAP *yeni = (KITAP*) malloc(sizeof(KITAP));
    int secim;
    int bos;
    char kitapAdi[30];

    char updateISBN[14];
    char updateKitapAdi[30];
    int updateAdet;
    scanf("%d", &secim);
    
    switch(secim){
        case 1:
            clearScreen();
            printf("Kitap Ekleme\n");
            printf("Kitap Adi:");
            scanf("%s", yeni->kitapAdi);
            printf("Kitap ISBN:");
            scanf("%s", yeni->ISBN);
            printf("Kitap Adedi:");
            scanf("%d", &yeni->adet);
            int i;
            KITAPORNEK *prev = NULL;
            for (i = 0; i < yeni->adet; i++)
            {
                KITAPORNEK *tmpOrnek = (KITAPORNEK*) malloc(sizeof(KITAPORNEK));
                if (i == 0)
                {
                    yeni->head = tmpOrnek;
                }
                else
                {
                    prev->next = tmpOrnek;
                }
                strcpy(tmpOrnek->durum,"Rafta");
                sprintf(tmpOrnek->etiketNo,"%s_%d",yeni->ISBN,i+1);
                prev = tmpOrnek;
            }
            (*tail)->next = yeni;
            (*tail) = yeni;
            break;

        case 2:
            clearScreen();
            printf("Kitap Silme\n");
            printf("Kitap ISBN:");
            scanf("%s",kitapAdi);
            KITAP *tmp = NULL;
            tmp = (*head);

            int check = 1;
            while(check == 1){
                if(strcmp(tmp->ISBN,kitapAdi) == 0){
                    printf("\nKitap bulundu.\n");
                    printf("Kitap Adi: %s\n",tmp->kitapAdi);
                    printf("Kitap ISBN: %s\n",tmp->ISBN);
                    printf("Kitap Adedi: %d\n",tmp->adet);
                    printf("Kitap Silinsin mi? (1-0)");
                    int sil;
                    scanf("%d",&sil);
                    if(sil == 1){
                        KITAP *tmp2 = NULL;
                        tmp2 = (*head);
                        if (tmp2 == tmp)
                        {
                            (*head) = tmp->next;
                        }
                        else
                        {
                            while(tmp2->next != tmp)
                            {
                                tmp2 = tmp2->next;
                            }
                            tmp2->next = tmp->next;
                        }
                        
                        printf("Kitap silindi.\n");
                    }
                    else{
                        printf("Kitap silinmedi.\n");
                    }
                    check = 0;
                }
                else{
                    if(tmp->next == NULL){
                        printf("Kitap bulunamadi.\n");
                        check = 0;
                    }
                    else{
                        tmp = tmp->next;
                    }
                }
            }
            break;
        case 3:
            clearScreen();
            printf("Kitap Guncelleme\n");

            printf("Kitap ISBN:");
            scanf("%s",updateISBN);
            KITAP *tmp3 = NULL;
            tmp3 = (*head);

            int check2 = 1;
            while(check2 == 1){
                if(strcmp(tmp3->ISBN,updateISBN) == 0){
                    printf("\nKitap bulundu.\n");
                    printf("Kitap Adi: %s\n",tmp3->kitapAdi);
                    printf("Kitap ISBN: %s\n",tmp3->ISBN);
                    printf("Kitap Adedi: %d\n",tmp3->adet);
                    printf("Kitap Guncellensin mi? (1-0)");
                    int guncelle;
                    scanf("%d",&guncelle);
                    if(guncelle == 1){
                        printf("Kitap Adi:");
                        scanf("%s",updateKitapAdi);
                        strcpy(tmp3->kitapAdi,updateKitapAdi);
                        printf("Kitap guncellendi.\n");
                    }
                    else{
                        printf("Kitap guncellenmedi.\n");
                    }
                    check2 = 0;
                }
                else{
                    if(tmp3->next == NULL){
                        printf("Kitap bulunamadi.\n");
                        check2 = 0;
                    }
                    else{
                        tmp3 = tmp3->next;
                    }
                }
            }
            break;
        default:
            break;
    }
    printf("Geri donmek icin 1 giriniz:");
    scanf("%d", &bos);
}
void kitapBilgisiGoruntuleme(KITAP **head, KITAP **tail){
    clearScreen();
    printf("Kitap Bilgisi Goruntuleme\n");
    char kitapISBN[14];
    printf("Kitap ISBN:");
    scanf("%s",kitapISBN);
    KITAP *tmp = NULL;
    tmp = (*head);
    int check = 1;

    while(check == 1){
        if(strcmp(tmp->ISBN,kitapISBN) == 0){
            printf("\nKitap bulundu.\n");
            printf("Kitap Adi: %s\n",tmp->kitapAdi);
            printf("Kitap ISBN: %s\n",tmp->ISBN);
            printf("Kitap Adedi: %d\n",tmp->adet);
            KITAPORNEK *tmpOrnek = NULL;
            tmpOrnek = tmp->head;

            int check2 = 1;
            while(check2 == 1){
                printf("Kitap Ornek No: %s\n",tmpOrnek->etiketNo);
                printf("Kitap Ornek Durumu: %s\n",tmpOrnek->durum);
                if(tmpOrnek->next == NULL){
                    check2 = 0;
                }
                else{
                    tmpOrnek = tmpOrnek->next;
                }
            }
            check = 0;
        }
        else{
            if(tmp->next == NULL){
                printf("Kitap bulunamadi.\n");
                check = 0;
            }
            else{
                tmp = tmp->next;
            }
        }
    }
    int bos;
    printf("Geri donmek icin 1 giriniz:");
    scanf("%d", &bos);
}
void raftakiKitaplariListele(KITAP **head, KITAP **tail){
    clearScreen();
    
    int bos;
    int check = 1;
    KITAP *tmp = NULL;
    KITAPORNEK *tmpOrnek = NULL;

    tmp = (*head);
    if (tmp == NULL)
    {
        printf("Liste bos.\n");
    }

    while (check)
    {
        tmpOrnek = tmp->head;
        while (tmpOrnek != NULL)
        {
            if (strcmp(tmpOrnek->durum, "Rafta") == 0)
            {
                printf("Kitap Etiket No: %s\n", tmpOrnek->etiketNo);
                printf("Kitap Durumu: %s\n", tmpOrnek->durum);
                printf("\n");
            }
            tmpOrnek = tmpOrnek->next;
        }
        if (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        else
        {
            check = 0;
        }
    }

    printf("\nGeri donmek icin 1 giriniz:");
    scanf("%d", &bos);
}
void zamanindaTeslimEdilmeyenKitaplariListele(KITAP **head, KITAP **tail, KITAPODUNC **headOdunc, KITAPODUNC **tailOdunc){
    clearScreen();
    printf("Zamaninda Teslim Edilmeyen Kitaplari Listeleme\n");
    int bos;
    int gun1, gun2, ay1, ay2, yil1, yil2;
    KITAP *tempKitap = NULL;
    KITAPORNEK *tempOrnek = NULL;

    int check = 1;
    while (check == 1)
    {
        
    }
    

    printf("Geri donmek icin 1 giriniz:");
    scanf("%d", &bos);
}
void kitapYazarEslestir(KITAPYAZAR **dizi){
    clearScreen();
    printf("Kitap Yazar Eslestirme\n");
    int check = 1;
    while (check == 1)
    {
        printf("Kitap ISBN:");
        char kitapISBN[14];
        scanf("%s",kitapISBN);
        printf("Yazar ID:");
        int yazarID;
        scanf("%d",&yazarID);
        int i = 0;
        while (dizi[i] != NULL)
        {
            if (strcmp(dizi[i]->ISBN,kitapISBN) == 0)
            {
                printf("Kitap zaten eslestirilmis.\n");
                check = 0;
            }
            else{
                i++;
            }
        }
        if (check == 1)
        {
            KITAPYAZAR *tmp = (KITAPYAZAR*)malloc(sizeof(KITAPYAZAR));
            strcpy(tmp->ISBN,kitapISBN);
            tmp->yazarID = yazarID;
            dizi[i] = tmp;
            check = 0;
        }
    }
}
void kitabinYazariniGuncelle(KITAPYAZAR **dizi){
    clearScreen();
    printf("%s\n",dizi[0]->ISBN);
    printf("%d\n",dizi[0]->yazarID);
    int check = 1;
    while (check == 1)
    {
        printf("Kitap ISBN:");
        char kitapISBN[14];
        scanf("%s",kitapISBN);
        printf("Yazar ID:");
        int yazarID;
        scanf("%d",&yazarID);
        int i = 0;
        while (dizi[i] != NULL)
        {
            if (strcmp(dizi[i]->ISBN,kitapISBN) == 0)
            {
                dizi[i]->yazarID = yazarID;
                printf("Yazar guncellendi.\n");
                check = 0;
            }
            i++;
        }
        if (dizi[i] == NULL)
        {
            printf("Kitap bulunamadi.\n");
            check = 0;
        }
    }


    int bos;
    printf("Geri donmek icin 1 giriniz:");
    scanf("%d", &bos);
}
void tumKitaplariListele(KITAP **head, KITAP **tail, KITAPYAZAR **dizi, YAZAR **yazarHead){
    clearScreen();

    int i;
    int j;
    int k = 0;
    char yazarinAdi[30];
    char yazarinSoyadi[30];

    int yazarCount = 0;

    int bos;
    int check = 1;
    KITAP *tmp = NULL;
    KITAPORNEK *tmpOrnek = NULL;
    KITAPYAZAR **tmpYazar = NULL;
    YAZAR *indexYazar  = NULL;
    indexYazar = (*yazarHead);
    int finish = 0;
    tmpYazar = dizi;

    tmp = (*head);
    if (tmp == NULL)
    {
        printf("Liste bos.\n");
    }
    
    while (check)
    {
        yazarCount = 0;
        
        printf("---------------------\n");
        printf("Kitap Adi: %s\n", tmp->kitapAdi);
        printf("Kitap ISBN: %s\n", tmp->ISBN);
        if(yazarCount == 1){
            printf("Kitap Yazar: %s\n", yazarinAdi);
            printf("Kitap Yazar: %s\n", yazarinSoyadi);
        }
        printf("\nKitap Ornekleri\n");
        tmpOrnek=tmp->head;
        while(tmpOrnek!=NULL){
            printf("Kitap Etiket No: %s\n", tmpOrnek->etiketNo);
            printf("Kitap Ornek Durumu: %s\n", tmpOrnek->durum);
            printf("\n");
            tmpOrnek=tmpOrnek->next;
        }
        printf("---------------------\n");

        if (tmp->next == NULL)
        {
            check = 0;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    printf("\nGeri donmek icin 1 giriniz:");
    scanf("%d", &bos);
}

// Yazar Islemleri
void yazarEkleSilGuncelle(YAZAR** head, YAZAR** tail){
    clearScreen();
    printf("Yazar Islemleri\n");
    printf("1. Yazar Ekle\n");
    printf("2. Yazar Sil\n");
    printf("3. Yazar Guncelle\n");
    YAZAR *yeniYazar = (YAZAR*)malloc(sizeof(YAZAR));
    int secim;
    scanf("%d", &secim);
    switch(secim){
        case 1:
            printf("Yazar Ekleme\n");
            printf("Yazar Adi:");
            scanf("%s", yeniYazar->ad);
            printf("Yazar Soyadi:");
            scanf("%s", yeniYazar->soyad);

            int check = 1;
            YAZAR *tmp = NULL;
            int i = 0;
            while(check == 1){
                if (i == 0)
                {
                    tmp = (*head);
                }
                if (tmp->next == NULL)
                {
                    yeniYazar->yazarID = tmp->yazarID + 1;
                    printf("Yazar ID: %d\n", yeniYazar->yazarID);
                    tmp->next = yeniYazar;
                    check = 0;
                }
                else
                {
                    tmp = tmp->next;
                }
                i++;
            }
            
            
            
            break;
        case 2:
            printf("Yazar Silme\n");
            printf("Yazar ID:");
            int yazarID;
            scanf("%d", &yazarID);
            YAZAR *tmp2 = NULL;
            tmp2 = (*head);
            int check2 = 1;
            while (check2)
            {
                if (tmp2->next->yazarID == yazarID)
                {
                    tmp2->next = tmp2->next->next;
                    printf("Yazar silindi.\n");
                    check2 = 0;
                }
                else
                {
                    tmp2 = tmp2->next;
                }
            }
            break;
        case 3:
            printf("Yazar Guncelleme\n");
            printf("Yazar ID:");
            int yazarID2;
            scanf("%d", &yazarID2);
            YAZAR *tmp3 = NULL;
            tmp3 = (*head);
            int check3 = 1;
            while (check3)
            {
                if (tmp3->yazarID == yazarID2)
                {
                    printf("Yazar Adi:");
                    scanf("%s", tmp3->ad);
                    printf("Yazar Soyadi:");
                    scanf("%s", tmp3->soyad);
                    printf("Yazar guncellendi.\n");
                    check3 = 0;
                }
                else
                {
                    tmp3 = tmp3->next;
                }
            }
            
            break;
        default:
            printf("Hatali secim.\n");
            break;
    }
    int bos;
    printf("Geri donmek icin 1 giriniz:");
    scanf("%d", &bos);
}
void yazarBilgisiGoruntuleme(YAZAR **head, YAZAR **tail){
    clearScreen();
    int bos;
    int check = 1;
    YAZAR *tmp = NULL;
    tmp = (*head);
    if (tmp == NULL)
    {
        printf("Liste bos.\n");
    }
    while (check)
    {
        printf("Yazar ID: %d\n", tmp->yazarID);
        printf("Yazar Adi: %s\n", tmp->ad);
        printf("Yazar Soyadi: %s\n", tmp->soyad);
        printf("\n");

        if (tmp->next == NULL)
        {
            check = 0;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    printf("\nGeri donmek icin 1 giriniz:");
    scanf("%d", &bos);

    
}

int readFile(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi){
    int ogr = readOgrenci(ogrenciHead, ogrenciTail);
    int kitap = readKitap(kitapHead, kitapTail);
    int yazar = readYazar(yazarHead, yazarTail);
    int kitapOdunc = readKitapOdunc(kitapOduncHead, kitapOduncTail);
    int kitapYazar = readKitapYazar(kitapYazarDizi);
    
    if (ogr == 0 || kitap == 0 || yazar == 0 || kitapOdunc == 0 || kitapYazar == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
int readOgrenci(OGRENCI **head, OGRENCI **tail)
{
    FILE *fp = fopen("Ogrenciler.csv", "r");

    if (fp == NULL)
    {
        return 0;
    }
    while (!feof(fp))
    {
        OGRENCI *ogr = (OGRENCI *)malloc(sizeof(OGRENCI));
        fscanf(fp,"%8[^,],%30[^,],%30[^,],%d\n",ogr->ogrID,ogr->ad,ogr->soyad,&ogr->puan);
        if ((*head) == NULL)
        {
            (*head) = ogr;
            (*tail) = ogr;
        }
        else
        {
            ogr->prev= (*tail);
            (*tail)->next = ogr;
            (*tail) = ogr;
        }
    }

    fclose(fp);
    return 1;
}

int readKitap(KITAP **head, KITAP **tail)
{
    int i;
    FILE *fp = fopen("Kitaplar.csv", "r");

    if (fp == NULL)
    {
        return 0;
    }
    
    while (!feof(fp))
    {
        KITAPORNEK *temp;
        KITAP *kitap = (KITAP *)malloc(sizeof(KITAP));
        
        fscanf(fp,"%30[^,],%13[^,],%d\n",kitap->kitapAdi,kitap->ISBN,&kitap->adet);

        if ((*head) == NULL)
        {
            (*head) = kitap;
            (*tail) = kitap;
        }
        else
        {
            (*tail)->next = kitap;
            (*tail) = kitap;
        }

        for (i = 0; i < kitap->adet; i++)
        {   
            KITAPORNEK *ornekler = (KITAPORNEK *) malloc(sizeof(KITAPORNEK));
            strcpy(ornekler->durum,"Rafta");
            sprintf(ornekler->etiketNo,"%s_%d",kitap->ISBN,i+1);

            if (i == 0)
            {
                kitap->head = ornekler;
                temp=ornekler;
            }
            else{
                temp->next = ornekler;
                temp = ornekler;
            }
        }
        printf("\n\n");
    }

    fclose(fp);
    return 1;
}

int readYazar(YAZAR **head, YAZAR **tail)
{
    FILE *fp = fopen("Yazarlar.csv", "r");
    if (fp == NULL)
    {
        return 0;
    }
    while (!feof(fp))
    {
        YAZAR *yazar = (YAZAR *)malloc(sizeof(YAZAR));
        fscanf(fp,"%d , %29[^,] , %29[^,\n]",&yazar->yazarID,yazar->ad,yazar->soyad);
        
        if ((*head) == NULL)
        {
            (*head) = yazar;
            (*tail) = yazar;
        }
        else
        {
            (*tail)->next = yazar;
            (*tail) = yazar;
        }
    }

    fclose(fp);
    return 1;
}

int readKitapOdunc(KITAPODUNC **head, KITAPODUNC **tail)
{
    FILE *fp = fopen("KitapOdunc.csv", "r");
    if (fp == NULL)
    {
        return 0;
    }
    int gun,ay,yil,islem;
    while (!feof(fp))
    {
        KITAPODUNC *kitapOdunc = (KITAPODUNC *)malloc(sizeof(KITAPODUNC));
        fscanf(fp,"%[^,],%[^,],%d,%d.%d.%d\n",kitapOdunc->etiketNo,kitapOdunc->ogrID,&islem,&gun,&ay,&yil);
        kitapOdunc->islemTipi = islem;
        kitapOdunc->islemTarihi.gun = gun;
        kitapOdunc->islemTarihi.ay = ay;
        kitapOdunc->islemTarihi.yil = yil;



        if ((*head) == NULL)
        {
            (*head) = kitapOdunc;
            (*tail) = kitapOdunc;
        }
        else
        {
            (*tail)->next = kitapOdunc;
            (*tail) = kitapOdunc;
        }
    }
    fclose(fp);
    return 1;
}

int readKitapYazar(KITAPYAZAR **dizi)
{
    int i = 0;
    FILE *fp = fopen("KitapYazar.csv", "r");
    if (fp == NULL)
    {
        return 0;
    }

    KITAPYAZAR **kitapYazarlar = (KITAPYAZAR**) malloc(sizeof(KITAPYAZAR*));
    while (!feof(fp))
    {
        if (i != 0)
        {
            kitapYazarlar = realloc(kitapYazarlar, sizeof(KITAPYAZAR*) * (i+1));
        }
        kitapYazarlar[i] = (KITAPYAZAR*) malloc(sizeof(KITAPYAZAR));
        fscanf(fp,"%[^,],%d\n",kitapYazarlar[i]->ISBN,&kitapYazarlar[i]->yazarID);
        i++;
    }
    dizi = kitapYazarlar;
    fclose(fp);
    return 1;

}


void updateOduncler(KITAP **head, KITAP **tail, KITAPODUNC **headOdunc, KITAPODUNC **tailOdunc){
    KITAP *temp = (*head);
    KITAPORNEK *tempOrnek;
    KITAPODUNC *tempOdunc = (*headOdunc);
    while(temp != NULL){
        tempOrnek = temp->head;
        while(tempOrnek != NULL){
            tempOdunc = (*headOdunc);
            while(tempOdunc != NULL){
                if(strcmp(tempOrnek->etiketNo,tempOdunc->etiketNo) == 0){
                    if(tempOdunc->islemTipi ==0){
                        strcpy(tempOrnek->durum,tempOdunc->ogrID);
                    }
                    else{
                        strcpy(tempOrnek->durum,"Rafta");
                    }
                }
                tempOdunc = tempOdunc->next;
            }
            tempOrnek = tempOrnek->next;
        }
        temp = temp->next;
    }
}

void saveFile(OGRENCI **ogrenciHead, OGRENCI **ogrenciTail, KITAP **kitapHead, KITAP **kitapTail, YAZAR **yazarHead, YAZAR **yazarTail, KITAPODUNC **kitapOduncHead, KITAPODUNC **kitapOduncTail, KITAPYAZAR **kitapYazarDizi){
    saveOgrenci(ogrenciHead, ogrenciTail);
    saveKitap(kitapHead, kitapTail);
    saveYazar(yazarHead, yazarTail);
    saveKitapOdunc(kitapOduncHead, kitapOduncTail);
    //saveKitapYazar(kitapYazarDizi);
}
void saveOgrenci(OGRENCI **head, OGRENCI **tail){
    FILE *fp = fopen("Ogrenciler.csv", "w");
    OGRENCI *tmp= NULL;
    tmp = (*head);
    int check = 1;
    
    while (check == 1)
    {
        fprintf(fp,"%s,%s,%s,%d\n",tmp->ogrID,tmp->ad,tmp->soyad,tmp->puan);
        if(tmp->next == NULL){
            check = 0;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    fclose(fp);
}
void saveKitap(KITAP **head, KITAP **tail){
    FILE *fp = fopen("Kitaplar.csv", "w");
    KITAP *tmp= (*head);
    int check = 1;
    while (check == 1)
    {
        fprintf(fp,"%s,%s,%d\n",tmp->kitapAdi,tmp->ISBN,tmp->adet);
        if(tmp->next == NULL){
            check = 0;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    fclose(fp);
}
void saveYazar(YAZAR **head, YAZAR **tail){
    FILE *fp = fopen("Yazarlar.csv", "w");
    YAZAR *tmp= (*head);
    int check = 1;
    while (check == 1)
    {
        fprintf(fp,"%d,%s,%s\n",tmp->yazarID,tmp->ad,tmp->soyad);
        if(tmp->next == NULL){
            check = 0;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    fclose(fp);
}
void saveKitapOdunc(KITAPODUNC **head, KITAPODUNC **tail){
    FILE *fp = fopen("KitapOdunc.csv", "w");
    KITAPODUNC *tmp= (*head);
    int check = 1;
    while (check == 1)
    {
        fprintf(fp,"%s,%s,%d,%d.%d.%d\n",tmp->etiketNo,tmp->ogrID,tmp->islemTipi,tmp->islemTarihi.gun,tmp->islemTarihi.ay,tmp->islemTarihi.yil);
        if(tmp->next == NULL){
            check = 0;
        }
        else
        {
            tmp = tmp->next;
        }
    }
    fclose(fp);
}
void saveKitapYazar(KITAPYAZAR **dizi){
    FILE *fp = fopen("KitapYazar.csv", "w");
    int i = 0;
    while (dizi[i] != NULL)
    {
        fprintf(fp,"%s,%d\n",dizi[i]->ISBN,dizi[i]->yazarID);
        i++;
    }
    fclose(fp);
}

void clearScreen(){
    if(os == 0){
        system("cls");
    }
    else{
        system("clear");
    }
}