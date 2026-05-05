#include <iostream>
#include <windows.h>
using namespace std;

#include "json.hpp"
using json = nlohmann::json;

#include "data.h"
#include "help.h"
#include "menuAdmin.h"
#include "menuUser.h"

int login(Akun *akun, int &jumlahUser) {
    string jawabNama, jawabPassword;

    cout << "\n     Username: "; cin >> jawabNama;
    cout << "     Password: "; cin >> jawabPassword;
    for (int i = 0; i < jumlahUser; i++) {
        if ((akun + i)->username == jawabNama && (akun + i)->password == jawabPassword) {
            tampilPesan(38, "Login berhasil! Selamat datang, " + jawabNama);
            system("pause");
            return i;}}
    return -1;}

int registrasi(Akun *akun, int &jumlahUser) {
    string jawabNama, jawabPassword;
    bool userAda = false;
    
    if (jumlahUser >= 100) {
        tampilPeringatan(30, "Akun sudah penuh!");
        return jumlahUser;}
    cout << "\n     Username: "; cin >> jawabNama;
    cout << "     Password: "; cin >> jawabPassword;

    for (int i = 0; i < jumlahUser; i++) {
        if ((akun + i)->username == jawabNama) {
            userAda = true;
            tampilPeringatan(26, "Username sudah terdaftar!");
            break;}}
    if (!userAda) {
        (akun + jumlahUser)->username = jawabNama;
        (akun + jumlahUser)->password = jawabPassword;
        (akun + jumlahUser)->role = "user";
        jumlahUser++;
        tampilPesan(36, "Registrasi berhasil! Silakan login.");}
    return jumlahUser;}

void SetColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

    
int main() {
    SetConsoleOutputCP(65001);
    string pilihMenu[] = {
        "   1 | Login", 
        "   2 | Register",
        "   3 | Keluar"}; 

    int jumlahUser = 2;
    int jumlahBuku = 5;
    int jumlahEbookUser = 0;
    int salah = 0;
    int pilih = 0;

    Akun akun[100];
    Ebook katalog[100];
    EbookUser ebookUser[100];
    loadAkun(akun, jumlahUser);
    loadBuku(katalog, jumlahBuku);
    loadEbookUser(ebookUser, jumlahEbookUser);
    

    
    /* PROGRAM UTAMA
    ════════════════════════════════════════════════════*/
    SetColor(11);
    while (true) {
        system("cls");
        judul_subjudul("Selamat Datang");
        for (int i = 0; i < 3; i++) {
            if (i == pilih)
                cout << "> " << *(pilihMenu + i) << endl;
            else
                cout << "  " << *(pilihMenu + i) << endl;}

        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {

            /* A. LOGIN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls");
                judul_subjudul("Login Akun Anda");
                int indeksLogin = login(akun, jumlahUser);
                if (indeksLogin != -1) {
                    salah = 0;

                    /* 1. MENU ADMIN (CRUD)
                    ════════════════════════════════════════════════════*/
                    if ((akun + indeksLogin)->role == "admin") {
                        jumlahBuku = menuAdmin(akun, indeksLogin, jumlahBuku);}

                    /* 2. MENU USER (CRUD)
                    ════════════════════════════════════════════════════*/
                    else {
                        jumlahEbookUser = menuUser(akun, indeksLogin, jumlahBuku);}
                }

                else {
                    tampilPeringatan(56, "Username atau Password salah atau akun belum terdaftar!");
                    salah++;
                    tampilPeringatan(26, "Kesempatan anda tersisa " + to_string(3 - salah));

                    if (salah == 3) {
                        tampilPesan(52, "Anda telah salah 3 kali. Silakan datang lain kali.");
                        break;}
                    system("pause");} 
            }


            /* 2. REGISTRASI
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Registrasi Akun Anda");
                jumlahUser = registrasi(akun, jumlahUser);
                system("pause");}


            /* 3. KELUAR PROGRAM
            ════════════════════════════════════════════════════*/
            else {
                system("cls"); judul_subjudul("Terima Kasih Telah Mengunjungi Kami"); cout << endl;
                break;}
        }
    }
    
    saveAkun(akun, jumlahUser);
    saveBuku(katalog, jumlahBuku);
    saveEbookUser(ebookUser, jumlahEbookUser);

    return 0;
}