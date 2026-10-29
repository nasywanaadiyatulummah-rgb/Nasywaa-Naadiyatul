#include <stdio.h>
#include <string.h>

#define MAX_TRANSAKSI 10
#define JUMLAH_ALAT 5

// Data peralatan camping
char *namaAlat[JUMLAH_ALAT] = {
    "Tenda Kapasitas 4 Orang",
    "Sleeping Bag",
    "Kompor Portable",
    "Matras Camping",
    "Lampu Camping"
};

int hargaAlat[JUMLAH_ALAT] = {
    50000, 15000, 20000, 10000, 12000
};

// Array untuk menyimpan riwayat transaksi
char namaPenyewa[MAX_TRANSAKSI][100];
int pilihanAlat[MAX_TRANSAKSI];
int jumlahUnit[MAX_TRANSAKSI];
int lamaSewa[MAX_TRANSAKSI];
int totalBayar[MAX_TRANSAKSI];

int jumlahTransaksi = 0;

// Fungsi 1: Menampilkan daftar peralatan
void tampilkanAlat() {
    int i;

    printf("\n========== DAFTAR PERALATAN ==========\n");

    for (i = 0; i < JUMLAH_ALAT; i++) {
        printf("%d. %-28s Rp%d\n",
               i + 1, namaAlat[i], hargaAlat[i]);
    }

    printf("======================================\n");
}

// Fungsi 2: Melakukan penyewaan
void sewaAlat() {
    int alat, unit, hari;
    int subtotal, diskon, total;
    int persenDiskon;
    char kembali;

    if (jumlahTransaksi >= MAX_TRANSAKSI) {
        printf("\nKapasitas transaksi sudah penuh!\n");
        return;
    }

    tampilkanAlat();

    printf("\nNama penyewa: ");
    scanf(" %99[^\n]", namaPenyewa[jumlahTransaksi]);

    do {
        printf("Pilih nomor peralatan (1-5): ");
        scanf("%d", &alat);

        if (alat < 1 || alat > JUMLAH_ALAT) {
            printf("Pilihan tidak tersedia. Ulangi!\n");
        }
    } while (alat < 1 || alat > JUMLAH_ALAT);

    do {
        printf("Jumlah unit: ");
        scanf("%d", &unit);

        if (unit < 1) {
            printf("Jumlah minimal 1 unit!\n");
        }
    } while (unit < 1);

    do {
        printf("Lama sewa (hari): ");
        scanf("%d", &hari);

        if (hari < 1) {
            printf("Lama sewa minimal 1 hari!\n");
        }
    } while (hari < 1);

    // Menghitung subtotal
    subtotal = hargaAlat[alat - 1] * unit * hari;

    // Menentukan diskon
    if (hari >= 5) {
        persenDiskon = 15;
    } else if (hari >= 3) {
        persenDiskon = 10;
    } else {
        persenDiskon = 0;
    }

    diskon = subtotal * persenDiskon / 100;
    total = subtotal - diskon;

    // Menyimpan data transaksi ke array
    pilihanAlat[jumlahTransaksi] = alat - 1;
    jumlahUnit[jumlahTransaksi] = unit;
    lamaSewa[jumlahTransaksi] = hari;
    totalBayar[jumlahTransaksi] = total;

    jumlahTransaksi++;

    // Menampilkan struk
    printf("\n========== STRUK PENYEWAAN ==========\n");
    printf("Nama Penyewa   : %s\n",
           namaPenyewa[jumlahTransaksi - 1]);
    printf("Peralatan      : %s\n", namaAlat[alat - 1]);
    printf("Harga per Hari : Rp%d\n", hargaAlat[alat - 1]);
    printf("Jumlah Unit    : %d\n", unit);
    printf("Lama Sewa      : %d hari\n", hari);
    printf("-------------------------------------\n");
    printf("Subtotal       : Rp%d\n", subtotal);
    printf("Diskon (%d%%)   : Rp%d\n", persenDiskon, diskon);
    printf("-------------------------------------\n");
    printf("TOTAL BAYAR    : Rp%d\n", total);
    printf("=====================================\n");

    printf("Kembali ke menu utama? (Y/T): ");
    scanf(" %c", &kembali);

    if (kembali == 'T' || kembali == 't') {
        printf("\nTerima kasih telah menggunakan "
               "layanan Adventure Camp!\n");
    }
}

// Fungsi 3: Menampilkan riwayat transaksi
void tampilkanRiwayat() {
    int i;
    int pendapatan = 0;

    printf("\n========== RIWAYAT TRANSAKSI ==========\n");

    if (jumlahTransaksi == 0) {
        printf("Belum ada transaksi penyewaan.\n");
        return;
    }

    for (i = 0; i < jumlahTransaksi; i++) {
        printf("\nTransaksi ke-%d\n", i + 1);
        printf("Nama       : %s\n", namaPenyewa[i]);
        printf("Peralatan  : %s\n",
               namaAlat[pilihanAlat[i]]);
        printf("Jumlah     : %d unit\n", jumlahUnit[i]);
        printf("Lama Sewa  : %d hari\n", lamaSewa[i]);
        printf("Total      : Rp%d\n", totalBayar[i]);

        pendapatan += totalBayar[i];
    }

    printf("---------------------------------------\n");
    printf("Jumlah Transaksi : %d\n", jumlahTransaksi);
    printf("Total Pendapatan : Rp%d\n", pendapatan);
    printf("=======================================\n");
}

int main() {
    int menu;
    int berjalan = 1;

    do {
        printf("\n========================================\n");
        printf("             ADVENTURE CAMP\n");
        printf("       SISTEM PENYEWAAN PERALATAN\n");
        printf("========================================\n");
        printf("1. Lihat Daftar Peralatan\n");
        printf("2. Sewa Peralatan\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Keluar\n");
        printf("========================================\n");
        printf("Pilih menu [1-4]: ");

        if (scanf("%d", &menu) != 1) {
            printf("Input harus berupa angka!\n");

            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
                // Membersihkan input yang tidak valid
            }
            continue;
        }

        switch (menu) {
            case 1:
                tampilkanAlat();
                break;

            case 2:
                sewaAlat();

                if (jumlahTransaksi >= MAX_TRANSAKSI) {
                    printf("\nKapasitas transaksi telah penuh.\n");
                }
                break;

            case 3:
                tampilkanRiwayat();
                break;

            case 4:
                printf("\nTerima kasih telah menggunakan "
                       "Adventure Camp!\n");
                berjalan = 0;
                break;

            default:
                printf("Menu tidak tersedia. Pilih 1-4!\n");
        }

    } while (berjalan == 1);

    return 0;
}
