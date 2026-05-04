#include <iostream>
#include <windows.h>
using namespace std;

#include "json.hpp"
using json = nlohmann::json;

#include "data.h"
#include "help.h"

int menuUser(Akun *akun, int indeksLogin, int &jumlahEbookUser) {
    string pilihMenuUser[] = {
        "   1 | Menu Katalog E-Book",
        "   2 | Pesan E-Book",
        "   3 | E-Book Anda",
        "   4 | Topup Saldo",
        "   5 | Logout"};
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Halo, Pengguna " + (akun + indeksLogin)->username);
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << setw((70 + 2) / 2) << "Saldo: " << (akun + indeksLogin)->saldo << endl;
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << "" << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih)
                cout << "> " << *(pilihMenuUser + i) << endl;
            else
                cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
    
            /* a. MENU USER READ (Katalog E-Book)
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                cout << endl;
                system("pause");}

            /* b. MENU USER CREATE (Pesan E-Book)
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Pesan E-Book"); cout << endl;
                system("pause");}

            /* c. MENU USER READ (E-Book User)
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("E-Book Anda"); cout << endl;
                system("pause");}

            /* d. MENU USER UPDATE (Topup Saldo)
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Topup Saldo Anda"); cout << endl;
                system("pause");}

            /* e. MENU USER LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(18, "Logout berhasil!");
                system("pause");
                break;}}}
        return jumlahEbookUser;}