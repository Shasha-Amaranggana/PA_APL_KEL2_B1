#include <iostream>
#include <windows.h>
using namespace std;

#include "json.hpp"
using json = nlohmann::json;

#include "data.h"
#include "help.h"

int menuAdmin(Akun *akun, int indeksLogin, int &jumlahBuku) {
    string pilihMenuAdmin[] = {
        "   1 | Menu Katalog E-Book",
        "   2 | Tambahkan E-Book Baru",
        "   3 | Ubah Harga E-Book",
        "   4 | Hapus E-Book",
        "   5 | Logout"};
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Halo, Admin " + (akun + indeksLogin)->username);
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << setw((70 + 2) / 2) << "Saldo: " << (akun + indeksLogin)->saldo << endl;
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << "" << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih)
                cout << "> " << *(pilihMenuAdmin + i) << endl;
            else
                cout << "  " << *(pilihMenuAdmin + i) << endl;}
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
    
            /* a. MENU ADMIN READ (Katalog E-Book)
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                cout << endl;
                system("pause");}

            /* b. MENU ADMIN CREATE (Tambah E-Book)
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Tambahkan E-Book Baru"); cout << endl;
                system("pause");}

            /* c. MENU ADMIN UPDATE (Edit Harga E-Book)
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Ubah Harga E-Book"); cout << endl;
                system("pause");}

            /* d. MENU ADMIN DELETE (Hapus E-Book)
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Hapus E-Book"); cout << "" << endl;
                system("pause");}

            /* e. MENU ADMIN LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(18, "Logout berhasil!");
                system("pause");
                break;}}}
        return jumlahBuku;}