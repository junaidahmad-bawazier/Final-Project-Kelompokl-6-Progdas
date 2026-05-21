//Sistem Zonasi dan Rekomendasi Diversifikasi UMKM Retail 
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Junaid: Menentukan ambang batas (threshold) untuk tiap kategori usaha
#define kulinerRingan 500
#define kulinerBerat 1000
#define tokoSembako 1500
#define Jasa 2500
#define tokoPakaian 4000
#define tokoElektronik 7500
#define max 100

// Junaid: Membuat struktur data awal (union, enum, dan struct)
typedef union
{
    int usahaSejenis;
    int kuliner_ringan;
    int kuliner_berat;
    int toko_sembako;
    int jasa;
    int toko_pakaian;
    int toko_elektronik;
} kategoriUsaha;

typedef enum
{
    kulRingan = 1, kulBerat, sembako, service, pakaian, elektronik
} Pilihan;

typedef struct
{
    int tiga_RT; 
    int RW;
    int dua_RW; 
    int Kelurahan;
} Populasi;

typedef struct
{
    char nama[max];
    char namaUsaha[max];
    kategoriUsaha banyakUsaha;
    Populasi populasi;
    kategoriUsaha kapasitasMaksimal;
    int sisa_kuota;      
    char status[20];     
} Wilayah;

// Fahri: Membuat fungsi untuk menghitung kapasitas maksimal usaha
int hitungKapasitas(int Populasi, int choice)
{
    switch (choice)
    {
    case kulRingan: return Populasi / kulinerRingan;
    case kulBerat: return Populasi / kulinerBerat;
    case sembako: return Populasi / tokoSembako;
    case service: return Populasi / Jasa;
    case pakaian: return Populasi / tokoPakaian;
    case elektronik: return Populasi / tokoElektronik;
    default: return 0;
    }
}

// Altaf: Membuat fungsi tabel dan algoritma Bubble Sort untuk pengurutan
void tampilkanTabel(Wilayah daftarUsaha[], int jumlahUsaha)
{
    for (int i = 0; i < jumlahUsaha - 1; i++) {
        for (int j = 0; j < jumlahUsaha - i - 1; j++) {
            if (daftarUsaha[j].sisa_kuota < daftarUsaha[j + 1].sisa_kuota) {
                Wilayah temp = daftarUsaha[j];
                daftarUsaha[j] = daftarUsaha[j + 1];
                daftarUsaha[j + 1] = temp;
            }
        }
    }

    printf("\n--- Tabel Kesimpulan Hasil Usaha ---\n");
    printf("------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-6s | %-6s | %-6s | %-10s |\n", "Nama Usaha", "Wilayah", "Banyak", "Max", "Sisa", "Status");
    printf("------------------------------------------------------------------------------------\n");
    for (int i = 0; i < jumlahUsaha; i++) {
        printf("| %-15s | %-15s | %-6d | %-6d | %-6d | %-10s |\n", 
               daftarUsaha[i].namaUsaha, daftarUsaha[i].nama, 
               daftarUsaha[i].banyakUsaha.usahaSejenis, daftarUsaha[i].kapasitasMaksimal.usahaSejenis, 
               daftarUsaha[i].sisa_kuota, daftarUsaha[i].status);
    }

    printf("------------------------------------------------------------------------------------\n");

    // memberikan saran usaha paling berpotensi
    if (jumlahUsaha > 0 && daftarUsaha[0].sisa_kuota > 0) {
        printf("\nBerdasarkan data yang anda masukkan, usaha '%s' di wilayah '%s' adalah usaha yang PALING BERPOTENSI\n", 
                daftarUsaha[0].namaUsaha, daftarUsaha[0].nama);
        printf("karena masih memiliki sisa %d kuota.\n", daftarUsaha[0].sisa_kuota);
    } else if (jumlahUsaha > 0 && daftarUsaha[0].sisa_kuota <= 0) {
        printf("\nSemua usaha yang Anda cek sudah jenuh. Cobalah mencari wilayah atau usaha lain.\n");
    }

}

int main()
{
    // Altaf: Membuat alokasi memori dinamis awal untuk array
    int kapasitas_daftarUsaha = 2; 
    Wilayah *daftarUsaha = (Wilayah *)malloc(kapasitas_daftarUsaha * sizeof(Wilayah));
    
    // Junaid: Inisialisasi variabel kontrol dan kerangka utama program
    int jumlahUsaha = 0; 
    Wilayah wilayah; 
    int choice;
    int tindakanSelanjutnya;

    printf("=== Sistem Zonasi dan Rekomendasi Diversifikasi UMKM Retail ===\n");

    // Junaid: Membuat struktur looping utama (do-while) program (do-while yang di luar)
    // Hibban: Membuat struktur looping do-while yang di dalam
    do
    {
        printf("\nMasukkan nama wilayah : ");
        scanf(" %[^\n]", wilayah.nama);

        do
        {
            // Amsel: Membuat input nama usaha dan kategori
            printf("Anda mau buka usaha apa : ");
            scanf(" %[^\n]", wilayah.namaUsaha);
            printf("\n1. Kuliner Ringan\n2. Kuliner Berat\n3. Toko Sembako\n4. Jasa\n5. Toko Pakaian\n6. Toko Elektronik\n\n");
            printf("Termasuk kategori apa usaha Anda: ");
            scanf("%d", &choice);

            // Fahri: Membuat struktur switch case dan input populasi
            // Amsel: Melengkapi sisanya, mengisi setiap case dengan input banyak usaha
            switch (choice)
            {
            case kulRingan:
                printf("\nMasukkan total populasi RT lokasi dan 2 RT terdekat tempat Anda mau buka usaha: ");
                scanf("%d", &wilayah.populasi.tiga_RT);
                wilayah.kapasitasMaksimal.kuliner_ringan = hitungKapasitas(wilayah.populasi.tiga_RT, choice);
                printf("\nBerapa banyak usaha %s yang ada di RT dan 2 RT terdekat tempat Anda mau buka usaha? ", wilayah.namaUsaha);
                scanf("%d", &wilayah.banyakUsaha.kuliner_ringan);
                break;
            case kulBerat:
                printf("\nMasukkan total populasi di RW tempat Anda mau buka usaha: ");
                scanf("%d", &wilayah.populasi.RW);
                wilayah.kapasitasMaksimal.kuliner_berat = hitungKapasitas(wilayah.populasi.RW, choice);
                printf("\nBerapa banyak usaha %s yang ada di RW tempat Anda mau buka usaha? ", wilayah.namaUsaha);
                scanf("%d", &wilayah.banyakUsaha.kuliner_berat);
                break;
            case sembako:
                printf("\nMasukkan total populasi di RW tempat Anda mau buka usaha: ");
                scanf("%d", &wilayah.populasi.RW);
                wilayah.kapasitasMaksimal.toko_sembako = hitungKapasitas(wilayah.populasi.RW, choice);
                printf("\nBerapa banyak usaha %s yang ada di RW tempat Anda mau buka usaha? ", wilayah.namaUsaha);
                scanf("%d", &wilayah.banyakUsaha.toko_sembako);
                break;
            case service:
                printf("\nMasukkan total populasi RW tempat Anda buka usaha dan 1 RW terdekat: ");
                scanf("%d", &wilayah.populasi.dua_RW);
                wilayah.kapasitasMaksimal.jasa = hitungKapasitas(wilayah.populasi.dua_RW, choice);
                printf("\nBerapa banyak usaha %s yang ada di RW tempat Anda mau buka usaha dan 1 RW terdekat? ", wilayah.namaUsaha);
                scanf("%d", &wilayah.banyakUsaha.jasa);
                break;
            case pakaian:
                printf("\nMasukkan total populasi di kelurahan tempat Anda mau buka usaha: ");
                scanf("%d", &wilayah.populasi.Kelurahan);
                wilayah.kapasitasMaksimal.toko_pakaian = hitungKapasitas(wilayah.populasi.Kelurahan, choice);
                printf("\nBerapa banyak usaha %s yang ada di kelurahan tempat Anda mau buka usaha? ", wilayah.namaUsaha);
                scanf("%d", &wilayah.banyakUsaha.toko_pakaian);
                break;
            case elektronik:
                printf("\nMasukkan total populasi di kelurahan tempat Anda mau buka usaha: ");
                scanf("%d", &wilayah.populasi.Kelurahan);
                wilayah.kapasitasMaksimal.toko_elektronik = hitungKapasitas(wilayah.populasi.Kelurahan, choice);
                printf("\nBerapa banyak usaha %s yang ada di kelurahan tempat Anda mau buka usaha? ", wilayah.namaUsaha);
                scanf("%d", &wilayah.banyakUsaha.toko_elektronik);
                break;
            }

            // Hibban: Menghitung sisa kuota dan menetapkan status potensi usaha
            wilayah.sisa_kuota = wilayah.kapasitasMaksimal.usahaSejenis - wilayah.banyakUsaha.usahaSejenis;
            if (wilayah.sisa_kuota < 0) wilayah.sisa_kuota = 0;
            if (wilayah.banyakUsaha.usahaSejenis < wilayah.kapasitasMaksimal.usahaSejenis) {
                strcpy(wilayah.status, "potensi");
            } else {
                strcpy(wilayah.status, "maksimal");
            }

            // Altaf: Membuat penambahan memori dinamis (realloc) saat data bertambah
            if (jumlahUsaha >= kapasitas_daftarUsaha) {
                kapasitas_daftarUsaha *= 2; 
                daftarUsaha = (Wilayah *)realloc(daftarUsaha, kapasitas_daftarUsaha * sizeof(Wilayah));
            }
            daftarUsaha[jumlahUsaha++] = wilayah; 

            // Hibban: Menyusun logika percabangan untuk konfirmasi dan tindakan selanjutnya
            if (wilayah.banyakUsaha.usahaSejenis < wilayah.kapasitasMaksimal.usahaSejenis)
            {
                char konfirmasi;
                printf("\nUsaha %s di wilayah Anda masih berpotensi. \nApakah Anda yakin mau buka (y/n)? ", wilayah.namaUsaha);
                scanf(" %c", &konfirmasi);
                if (konfirmasi == 'y') {
                    printf("\n=== Silahkan buka usaha %s ===\n", wilayah.namaUsaha);
                    tindakanSelanjutnya = 0;
                } else {
                    do {
                        printf("\n1.Cek wilayah lain\n2.Pindah Usaha\n3.Lihat Tabel Usaha dan Saran\n4.Keluar\n\nPilih: ");
                        scanf("%d", &tindakanSelanjutnya);
                        if (tindakanSelanjutnya == 3) tampilkanTabel(daftarUsaha, jumlahUsaha);
                    } while (tindakanSelanjutnya == 3);
                }
            }
            else
            {
                printf("\nUsaha %s di wilayah yang mau Anda buka sudah jenuh.\n", wilayah.namaUsaha);
                do {
                    printf("\n1.Cek wilayah lain\n2.Pindah Usaha\n3.Lihat Tabel Usaha dan Saran\n4.Keluar\n\nPilih: ");
                    scanf("%d", &tindakanSelanjutnya);
                    if (tindakanSelanjutnya == 3) tampilkanTabel(daftarUsaha, jumlahUsaha);
                } while (tindakanSelanjutnya == 3);
            }
            
        } while (tindakanSelanjutnya == 2);
    } while (tindakanSelanjutnya == 1);

    // Altaf: Membersihkan alokasi memori sebelum program selesai
    free(daftarUsaha);
    return 0;
}