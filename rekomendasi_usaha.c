#include <stdio.h>

//daftar threshold
#define kulinerRingan 500
#define kulinerBerat 1000
#define tokoSembako 1500
#define Jasa 2500
#define tokoPakaian 4000
#define tokoElektronik 7500

//maksimal karakter nama wilayah
#define max 100

//kategori usaha nya
typedef union {
    int kuliner_ringan;
    int kuliner_berat;
    int toko_sembako;
    int jasa;
    int toko_pakaian;
    int toko_elektronik;

}kategoriUsaha;

typedef enum {
    kulRingan = 1, kulBerat, sembako, service, pakaian, elektronik
}Pilihan;


//pembagian populasi wilayahnya
typedef struct {
    int tiga_RT;    // 1 RT + 2 RT terdekat
    int RW;
    int dua_RW;     // 1 RW + 1 RW terdekat
    int Kelurahan;

}Populasi;

//setiap mau buka suatu "usaha" dalam suatu "wilayah" akan ada
typedef struct {
    char nama[max];
    char namaUsaha[max];
    kategoriUsaha banyakUsaha;
    Populasi populasi;

}Wilayah;

int main() {

    Wilayah wilayah;
    int choice;

    printf("=== Sistem Zonasi dan Rekomendasi Diversifikasi UMKM Retail ===");

    printf("Masukkan nama wilayah : ");
    scanf("%d", wilayah.nama);

    printf("Anda mau buka usaha apa : ");
    scanf("%s", wilayah.namaUsaha);

    printf("Termasuk kategori apa usaha anda?");
    printf("\n1. Kuliner Ringan");
    printf("\n2. Kuliner Berat");
    printf("\n3. Toko Sembako");
    printf("\n4. Jasa");
    printf("\n5. Toko Pakaian");
    printf("\n6. Toko Elektronik\n\n");

    scanf("%d", choice);

    return 0;
}