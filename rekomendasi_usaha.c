#include <stdio.h>
#include <string.h>
#include <stdlib.h> // untuk malloc, realloc, dan free

// daftar threshold
#define kulinerRingan 500
#define kulinerBerat 1000
#define tokoSembako 1500
#define Jasa 2500
#define tokoPakaian 4000
#define tokoElektronik 7500

// maksimal karakter nama wilayah
#define max 100

// kategori usaha nya
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
    kulRingan = 1,
    kulBerat,
    sembako,
    service,
    pakaian,
    elektronik
} Pilihan;

// pembagian populasi wilayahnya
typedef struct
{
    int tiga_RT; // 1 RT + 2 RT terdekat
    int RW;
    int dua_RW; // 1 RW + 1 RW terdekat
    int Kelurahan;

} Populasi;

// setiap mau buka suatu "usaha" dalam suatu "wilayah" akan ada
typedef struct
{
    char nama[max];
    char namaUsaha[max];
    kategoriUsaha banyakUsaha;
    Populasi populasi;
    kategoriUsaha kapasitasMaksimal;
    int sisa_kuota;      // untuk tabel bagian sisa kuotas
    char status[20];     // untuk tabel bagian status
} Wilayah;

int hitungKapasitas(int Populasi, int choice)
{
    switch (choice)
    {
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

// Fungsi tabel menggunakan akses array biasa (tanpa pointer yang rumit)
void tampilkanTabel(Wilayah daftarUsaha[], int jumlahUsaha)   // jumlahUsaha buat nentuin banyak usahanya
{
    // Bubble Sort 
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
               daftarUsaha[i].namaUsaha,
               daftarUsaha[i].nama,
               daftarUsaha[i].banyakUsaha.usahaSejenis,
               daftarUsaha[i].kapasitasMaksimal.usahaSejenis,
               daftarUsaha[i].sisa_kuota,
               daftarUsaha[i].status);
    }
    printf("------------------------------------------------------------------------------------\n");
}

int main()
{
    // Alokasi memori dinamis HANYA untuk rwayat tabel
    int kapasitas_daftarUsaha = 2; 
    Wilayah *daftarUsaha = (Wilayah *)malloc(kapasitas_daftarUsaha * sizeof(Wilayah));
    if (daftarUsaha == NULL) {
        printf("Gagal mengalokasikan memori!\n");
        return 1; 
    }
    
    int jumlahUsaha = 0; //counter buat ngitung jumlah usahanya
    Wilayah wilayah; 
    int choice;
    int tindakanSelanjutnya;

    printf("=== Sistem Zonasi dan Rekomendasi Diversifikasi UMKM Retail ===\n\n");

    do
    {
        printf("\nMasukkan nama wilayah : ");
        scanf(" %[^\n]", wilayah.nama);

        do
        {
            printf("Anda mau buka usaha apa : ");
            scanf(" %[^\n]", wilayah.namaUsaha);

            printf("\n1. Kuliner Ringan");
            printf("\n2. Kuliner Berat");
            printf("\n3. Toko Sembako");
            printf("\n4. Jasa");
            printf("\n5. Toko Pakaian");
            printf("\n6. Toko Elektronik\n\n");
            printf("Termasuk kategori apa usaha anda: ");
            scanf("%d", &choice);

            switch (choice)
            {
            case kulRingan:
                printf("\nMasukkan total populasi RT lokasi usaha Anda serta 2 RT terdekat dari lokasi usaha Anda: ");
                scanf("%d", &wilayah.populasi.tiga_RT);
                wilayah.kapasitasMaksimal.kuliner_ringan = hitungKapasitas(wilayah.populasi.tiga_RT, choice);
                printf("\nBerapa banyak usaha %s yang ada di %s? ", wilayah.namaUsaha, wilayah.nama);
                scanf("%d", &wilayah.banyakUsaha.kuliner_ringan);
                break;

            case kulBerat:
                printf("\nMasukkan total populasi di RW tempat usaha Anda: ");
                scanf("%d", &wilayah.populasi.RW);
                wilayah.kapasitasMaksimal.kuliner_berat = hitungKapasitas(wilayah.populasi.RW, choice);
                printf("\nBerapa banyak usaha %s yang ada di %s? ", wilayah.namaUsaha, wilayah.nama);
                scanf("%d", &wilayah.banyakUsaha.kuliner_berat);
                break;

            case sembako:
                printf("\nMasukkan total populasi di RW tempat usaha Anda: ");
                scanf("%d", &wilayah.populasi.RW);
                wilayah.kapasitasMaksimal.toko_sembako = hitungKapasitas(wilayah.populasi.RW, choice);
                printf("\nBerapa banyak usaha %s yang ada di %s? ", wilayah.namaUsaha, wilayah.nama);
                scanf("%d", &wilayah.banyakUsaha.toko_sembako);
                break;

            case service:
                printf("\nMasukkan total populasi gabungan di RW tempat usaha Anda dan RW terdekat dari usaha Anda: ");
                scanf("%d", &wilayah.populasi.dua_RW);
                wilayah.kapasitasMaksimal.jasa = hitungKapasitas(wilayah.populasi.dua_RW, choice);
                printf("\nBerapa banyak usaha %s yang ada di %s? ", wilayah.namaUsaha, wilayah.nama);
                scanf("%d", &wilayah.banyakUsaha.jasa);
                break;

            case pakaian:
                printf("\nMasukkan total populasi di kelurahan tempat anda buka usaha: ");
                scanf("%d", &wilayah.populasi.Kelurahan);
                wilayah.kapasitasMaksimal.toko_pakaian = hitungKapasitas(wilayah.populasi.Kelurahan, choice);
                printf("\nBerapa banyak usaha %s yang ada di %s? ", wilayah.namaUsaha, wilayah.nama);
                scanf("%d", &wilayah.banyakUsaha.toko_pakaian);
                break;

            case elektronik:
                printf("\nMasukkan total populasi di kelurahan tempat anda buka usaha: ");
                scanf("%d", &wilayah.populasi.Kelurahan);
                wilayah.kapasitasMaksimal.toko_elektronik = hitungKapasitas(wilayah.populasi.Kelurahan, choice);
                printf("\nBerapa banyak usaha %s yang ada di %s? ", wilayah.namaUsaha, wilayah.nama);
                scanf("%d", &wilayah.banyakUsaha.toko_elektronik);
                break;

            default:
                printf("Pilihan tidak valid\n");
                break;
            }

            // Menghitung sisa kuota dan status untuk dimasukkan ke array daftarUsaha
            wilayah.sisa_kuota = wilayah.kapasitasMaksimal.usahaSejenis - wilayah.banyakUsaha.usahaSejenis;
            if (wilayah.sisa_kuota < 0) wilayah.sisa_kuota = 0;
            
            if (wilayah.banyakUsaha.usahaSejenis < wilayah.kapasitasMaksimal.usahaSejenis) {
                strcpy(wilayah.status, "potensi");
            } else {
                strcpy(wilayah.status, "maksimal");
            }

            // Memasukkan data wilayah saat ini ke alokasi memori array dinamis
            if (jumlahUsaha >= kapasitas_daftarUsaha) {
                kapasitas_daftarUsaha *= 2; 
                Wilayah *temp = (Wilayah *)realloc(daftarUsaha, kapasitas_daftarUsaha * sizeof(Wilayah));
                if (temp == NULL) {
                    printf("Gagal menambah alokasi memori!\n");
                    free(daftarUsaha); 
                    return 1;
                }
                daftarUsaha = temp; 
            }
            daftarUsaha[jumlahUsaha] = wilayah; // Simpan ke array
            jumlahUsaha++; 

            
            if (wilayah.banyakUsaha.usahaSejenis < wilayah.kapasitasMaksimal.usahaSejenis)
            {
                char konfirmasi;
                printf("\nUsaha %s di wilayah %s masih memiliki potensi untuk berkembang.\n", wilayah.namaUsaha, wilayah.nama);
                printf("\nApakah anda yakin mau buka usaha tersebut (y/n)? ");
                scanf(" %c", &konfirmasi);
                
                if (konfirmasi == 'y')
                {
                    printf("\n\n=== Silahkan Anda buka usaha %s ===\n", wilayah.namaUsaha);
                    tindakanSelanjutnya = 0;
                }
                else
                {
                    do {
                        printf("\n1. Cek wilayah lain\n");
                        printf("2. Pindah Usaha\n");
                        printf("3. Lihat Tabel Potensi Usaha dan Saran\n");
                        printf("4. Keluar Program\n");
                        printf("\nPilih tindakan Anda selanjutnya : ");
                        scanf("%d", &tindakanSelanjutnya);
                        
                        if (tindakanSelanjutnya == 3) {
                            tampilkanTabel(daftarUsaha, jumlahUsaha);
                            if (jumlahUsaha > 0 && daftarUsaha[0].sisa_kuota > 0) {
                                printf("Usaha dengan potensi paling tinggi saat ini adalah %s di %s dengan sisa kuota %d.\n", 
                                       daftarUsaha[0].namaUsaha, daftarUsaha[0].nama, daftarUsaha[0].sisa_kuota);
                            }
                        }
                    } while (tindakanSelanjutnya == 3);
                }
            }
            else
            {
                printf("\nUsaha %s di wilayah %s sudah mencapai kapasitas maksimal.\n", wilayah.namaUsaha, wilayah.nama);
                do {
                    printf("\nPilih tindakan Anda selanjutnya :\n");
                    printf("1. Cek wilayah lain\n");
                    printf("2. Pindah Usaha\n");
                    printf("3. Lihat tabel potensi usaha dan saran\n");
                    printf("4. Keluar Program\n");
                    printf("\nPilihan: ");
                    scanf("%d", &tindakanSelanjutnya);
                    
                    if (tindakanSelanjutnya == 3) {
                        tampilkanTabel(daftarUsaha, jumlahUsaha);
                        if (jumlahUsaha > 0 && daftarUsaha[0].sisa_kuota > 0) {
                            printf("\nUsaha dengan potensi paling tinggi saat ini adalah %s di %s dengan sisa kuota %d.\n", 
                                   daftarUsaha[0].namaUsaha, daftarUsaha[0].nama, daftarUsaha[0].sisa_kuota);
                        } else {
                            printf("\nSeluruh usaha yang dianalisis sudah mencapai batas maksimal. Cari wilayah atau usaha lain!\n");
                        }
                    }
                } while (tindakanSelanjutnya == 3);
            }
            
        } while (tindakanSelanjutnya == 2);
    } while (tindakanSelanjutnya == 1);

    // free daftarUsaha karena realloc
    free(daftarUsaha);

    return 0;
}
