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
    int usahaall;
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
    kategoriUsaha kapasitasMaksimal;

}Wilayah;

int hitungKapasitas(int Populasi, int choice) {
    switch(choice) {
        case kulRingan:
            return Populasi / kulinerRingan;
        case kulBerat:
            return Populasi / kulinerBerat;
        case sembako:
            return Populasi / tokoSembako;
        case service:
            return Populasi / Jasa;
        case pakaian:
            return Populasi / tokoPakaian;
        case elektronik:
            return Populasi / tokoElektronik;
        default:
            return 0;
    }
}


int main() {

    Wilayah wilayah;
    int choice;

    printf("=== Sistem Zonasi dan Rekomendasi Diversifikasi UMKM Retail ===");

    printf("Masukkan nama wilayah : ");
    scanf("%s", wilayah.nama);

    printf("Anda mau buka usaha apa : ");
    scanf("%s", wilayah.namaUsaha);

    printf("Termasuk kategori apa usaha anda?");
    printf("\n1. Kuliner Ringan");
    printf("\n2. Kuliner Berat");
    printf("\n3. Toko Sembako");
    printf("\n4. Jasa");
    printf("\n5. Toko Pakaian");
    printf("\n6. Toko Elektronik\n\n");

    scanf("%d", &choice);
    switch(choice) {
        case kulRingan:
            printf("Populasi RT wilayah %s dan dua RT terdekat: ", wilayah.nama);
            scanf("%d", &wilayah.populasi.tiga_RT);
            wilayah.kapasitasMaksimal.kuliner_ringan = hitungKapasitas(wilayah.populasi.tiga_RT, choice);
            printf("\nBerapa banyak usaha %s yang ada di %s?", wilayah.namaUsaha, wilayah.nama);
            scanf("%d", &wilayah.banyakUsaha.kuliner_ringan);
            break;

        case kulBerat:
            printf("Populasi RW wilayah %s: ", wilayah.nama);
            scanf("%d", &wilayah.populasi.RW);
            wilayah.kapasitasMaksimal.kuliner_berat = hitungKapasitas(wilayah.populasi.RW, choice);
            printf("\nBerapa banyak usaha %s yang ada di %s?", wilayah.namaUsaha, wilayah.nama);
            scanf("%d", &wilayah.banyakUsaha.kuliner_berat);
            break;

        case sembako:
            printf("Populasi RW wilayah %s: ", wilayah.nama);
            scanf("%d", &wilayah.populasi.RW);
            wilayah.kapasitasMaksimal.toko_sembako = hitungKapasitas(wilayah.populasi.RW, choice);
            printf("\nBerapa banyak usaha %s yang ada di %s?", wilayah.namaUsaha, wilayah.nama);
            scanf("%d", &wilayah.banyakUsaha.toko_sembako);
            break;

        case service:
            printf("Populasi RW wilayah %s dan satu RW terdekat: ", wilayah.nama);
            scanf("%d", &wilayah.populasi.dua_RW);
            wilayah.kapasitasMaksimal.jasa = hitungKapasitas(wilayah.populasi.dua_RW, choice);
            printf("\nBerapa banyak usaha %s yang ada di %s?", wilayah.namaUsaha, wilayah.nama);
            scanf("%d", &wilayah.banyakUsaha.jasa);
            break;

        case pakaian:
            printf("Populasi Kelurahan wilayah %s: ", wilayah.nama);
            scanf("%d", &wilayah.populasi.Kelurahan);
            wilayah.kapasitasMaksimal.toko_pakaian = hitungKapasitas(wilayah.populasi.Kelurahan, choice);
            printf("\nBerapa banyak usaha %s yang ada di %s?", wilayah.namaUsaha, wilayah.nama);
            scanf("%d", &wilayah.banyakUsaha.toko_pakaian);
            break;
            
        case elektronik:
            printf("Populasi Kelurahan wilayah %s: ", wilayah.nama);
            scanf("%d", &wilayah.populasi.Kelurahan);
            wilayah.kapasitasMaksimal.toko_elektronik = hitungKapasitas(wilayah.populasi.Kelurahan, choice);
            printf("\nBerapa banyak usaha %s yang ada di %s?", wilayah.namaUsaha, wilayah.nama);
            scanf("%d", &wilayah.banyakUsaha.toko_elektronik);
            break;
            
        default:
            printf("Pilihan tidak valid\n");
            break;
    }

    if (wilayah.banyakUsaha.usahaall < wilayah.kapasitasMaksimal.usahaall) {
        printf("\nUsaha %s di wilayah %s masih memiliki potensi untuk berkembang.\n", wilayah.namaUsaha, wilayah.nama);
    } else {
        printf("\nUsaha %s di wilayah %s sudah mencapai kapasitas maksimal.\n", wilayah.namaUsaha, wilayah.nama);
    }
    
    return 0;
}



