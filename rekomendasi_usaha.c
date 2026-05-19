#include <stdio.h>
#include <string.h>

// daftar threshold
#define kulinerRingan 500
#define kulinerBerat 1000
#define tokoSembako 1500
#define Jasa 2500
#define tokoPakaian 4000
#define tokoElektronik 7500

// maksimal karakter nama wilayah
#define max 100
// maksimal riwayat untuk tabel
#define maxRiwayat 50

// kategori usaha nya
typedef union {
    int kuliner_ringan;
    int kuliner_berat;
    int toko_sembako;
    int jasa;
    int toko_pakaian;
    int toko_elektronik;
    int usahaall;
} kategoriUsaha;

typedef enum {
    kulRingan = 1,
    kulBerat,
    sembako,
    service,
    pakaian,
    elektronik
} Pilihan;

// pembagian populasi wilayahnya
typedef struct {
    int tiga_RT; 
    int RW;
    int dua_RW; 
    int Kelurahan;
} Populasi;

// setiap mau buka suatu "usaha" dalam suatu "wilayah" akan ada
typedef struct {
    char nama[max];
    char namaUsaha[max];
    kategoriUsaha banyakUsaha;
    Populasi populasi;
    kategoriUsaha kapasitasMaksimal;
    int sisa_kuota;      // Tambahan baru
    char status[20];     // Tambahan baru
} Wilayah;

int hitungKapasitas(int Populasi, int choice) {
    switch (choice) {
        case kulRingan: return Populasi / kulinerRingan;
        case kulBerat: return Populasi / kulinerBerat;
        case sembako: return Populasi / tokoSembako;
        case service: return Populasi / Jasa;
        case pakaian: return Populasi / tokoPakaian;
        case elektronik: return Populasi / tokoElektronik;
        default: return 0;
    }
}

// Fungsi tabel menggunakan pointer format (*ptr).member
void tampilkanTabel(Wilayah *daftar, int total) {
    printf("\n--- Tabel Kesimpulan Hasil Usaha ---\n");
    printf("--------------------------------------------------------------------------\n");
    printf("| %-15s | %-15s | %-5s | %-5s | %-10s |\n", "Nama Usaha", "Wilayah", "Banyak", "Max", "Status");
    printf("--------------------------------------------------------------------------\n");
    for (int i = 0; i < total; i++) {
        printf("| %-15s | %-15s | %-5d | %-5d | %-10s |\n", 
               (*(daftar + i)).namaUsaha,
               (*(daftar + i)).nama,
               (*(daftar + i)).banyakUsaha.usahaall,
               (*(daftar + i)).kapasitasMaksimal.usahaall,
               (*(daftar + i)).status);
    }
    printf("--------------------------------------------------------------------------\n");
}

int main() {
    Wilayah riwayat[maxRiwayat];
    int jumlahData = 0;
    int choice;
    int tindakanSelanjutnya;
    char tempNamaWilayah[max];

    printf("=== Sistem Zonasi dan Rekomendasi Diversifikasi UMKM Retail ===\n\n");

    do {
        printf("Masukkan nama wilayah : ");
        scanf(" %[^\n]", tempNamaWilayah);

        do {
            // Menggunakan pointer ke elemen array riwayat saat ini
            Wilayah *w = &riwayat[jumlahData];
            strcpy((*w).nama, tempNamaWilayah);

            printf("Anda mau buka usaha apa : ");
            scanf(" %[^\n]", (*w).namaUsaha);

            printf("\n1. Kuliner Ringan\n2. Kuliner Berat\n3. Toko Sembako\n4. Jasa\n5. Toko Pakaian\n6. Toko Elektronik\n\n");
            printf("Termasuk kategori apa usaha anda: ");
            scanf("%d", &choice);

            int pop_pilihan = 0;
            switch (choice) {
                case kulRingan:
                    printf("Populasi RT wilayah %s dan dua RT terdekat: ", (*w).nama);
                    scanf("%d", &(*w).populasi.tiga_RT);
                    pop_pilihan = (*w).populasi.tiga_RT;
                    break;
                case kulBerat:
                case sembako:
                    printf("Populasi RW wilayah %s: ", (*w).nama);
                    scanf("%d", &(*w).populasi.RW);
                    pop_pilihan = (*w).populasi.RW;
                    break;
                case service:
                    printf("Populasi RW wilayah %s dan satu RW terdekat: ", (*w).nama);
                    scanf("%d", &(*w).populasi.dua_RW);
                    pop_pilihan = (*w).populasi.dua_RW;
                    break;
                case pakaian:
                case elektronik:
                    printf("Populasi Kelurahan wilayah %s: ", (*w).nama);
                    scanf("%d", &(*w).populasi.Kelurahan);
                    pop_pilihan = (*w).populasi.Kelurahan;
                    break;
            }

            (*w).kapasitasMaksimal.usahaall = hitungKapasitas(pop_pilihan, choice);
            printf("\nBerapa banyak usaha %s yang ada di %s? ", (*w).namaUsaha, (*w).nama);
            scanf("%d", &(*w).banyakUsaha.usahaall);

            // Logika Sisa Kuota
            (*w).sisa_kuota = (*w).kapasitasMaksimal.usahaall - (*w).banyakUsaha.usahaall;
            if ((*w).sisa_kuota < 0) (*w).sisa_kuota = 0;

            if ((*w).banyakUsaha.usahaall < (*w).kapasitasMaksimal.usahaall) {
                strcpy((*w).status, "potensi");
                printf("\nUsaha %s di wilayah %s masih memiliki potensi untuk berkembang.\n", (*w).namaUsaha, (*w).nama);
            } else {
                strcpy((*w).status, "maksimal");
                printf("\nUsaha %s di wilayah %s sudah mencapai kapasitas maksimal.\n", (*w).namaUsaha, (*w).nama);
            }

            jumlahData++; // Simpan data ke riwayat

            do {
                printf("\nPilih tindakan Anda selanjutnya :\n");
                printf("1. Cek wilayah lain\n");
                printf("2. Pindah Usaha (wilayah sama)\n");
                printf("3. Lihat tabel potensi usaha\n");
                printf("4. Keluar Program\n");
                printf("Pilihan: ");
                scanf("%d", &tindakanSelanjutnya);

                if (tindakanSelanjutnya == 3) {
                    tampilkanTabel(riwayat, jumlahData);
                }
            } while (tindakanSelanjutnya == 3);

        } while (tindakanSelanjutnya == 2);
    } while (tindakanSelanjutnya == 1);

    return 0;
}