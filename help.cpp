#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include "data.h"
using namespace std;


/* PROSEDUR DAN FUNGSI BANTU
════════════════════════════════════════════════════*/
void judul_subjudul(string subjudul) {
    int spasiKiri = (70 - subjudul.length()) / 2;
    cout << "══════════════════════════════════════════════════════════════════════" << endl;
    cout << "│                    ☕📓   E-BOOKIE STORE   📓☕                    │" << endl;
    cout << "══════════════════════════════════════════════════════════════════════" << endl;
    cout << "      ══════════════════════════════════════════════════════════      " << endl;
    cout << string(spasiKiri, ' ') << subjudul << endl;
    cout << "      ══════════════════════════════════════════════════════════      " << endl;}

void tampilPesan(int nilai, string pesan) {
    cout << "" << endl;
    cout << setw((70 + 26) / 2) << "=========================" << endl;
    cout << setw((70 + nilai) / 2) << pesan << endl;
    cout << setw((70 + 26) / 2) << "=========================" << endl;
    cout << "" << endl;}

void tampilPeringatan(int nilai, string pesan) {
    cout << "" << endl;
    cout << setw((70 + 34) / 2) << "---------------------------------" << endl;
    cout << setw((70 + nilai) / 2) << pesan << endl;
    cout << setw((70 + 34) / 2) << "---------------------------------" << endl;
    cout << "" << endl;}

int scrollMenu(int &pilih, int jumlahMenu) {
    int tombol = getch();

    if (tombol == 224 || tombol == 0) {
        tombol = getch();
        if (tombol == 72) {
            pilih = (pilih - 1 + jumlahMenu) % jumlahMenu;}
        else if (tombol == 80) {
            pilih = (pilih + 1) % jumlahMenu;}}
    else if (tombol == 13) {
        return -1;}

    return pilih;} 

int scrollBuku(Ebook *katalog, int &jumlahBuku, string judulMenu) {
    int pilih = 0;

    while(true){
        system("cls");
        judul_subjudul(judulMenu);
        cout << "" << endl;
        for(int i = 0; i < jumlahBuku; i++){
            if(i == pilih)
                cout << "> " << (katalog + i)->judul << endl;
            else
                cout << "  " << (katalog + i)->judul << endl;}
        int hasil = scrollMenu(pilih, jumlahBuku);
        if(hasil == -1)
            return pilih;}}   

string inisialKode(string teks) {
    string hasil = "";
    bool ambil = true;
    for (size_t i = 0; i < teks.length(); i++) {
        if (ambil && isalpha(teks[i])) {
            hasil += toupper(teks[i]);
            ambil = false;}
        if (teks[i] == ' ') {
            ambil = true;}}
    return hasil;
}

string generateKode(Ebook *katalog, int jumlahBuku, string judul, string penulis, int tahun) {
    int nomor = 1;
    string nomorStr;
    string inisialJudul = inisialKode(judul);
    string inisialPenulis = inisialKode(penulis);

    for (int i = 0; i < jumlahBuku; i++) {
        if ((katalog + i)->judul == judul &&
            (katalog + i)->penulis == penulis &&
            (katalog + i)->tahun == tahun) {
            nomor++;}}
    if (nomor < 10) nomorStr = "00" + to_string(nomor);
    else if (nomor < 100) nomorStr = "0" + to_string(nomor);
    else nomorStr = to_string(nomor);

    return inisialJudul + inisialPenulis + to_string(tahun) + nomorStr;
}

int generateNo(Ebook *katalog, int &jumlahBuku) {
    for (int i = 1; i <= jumlahBuku + 1; i++) {
        bool ada = false;
        for (int j = 0; j < jumlahBuku; j++) {
            if ((katalog + j)->no == i) {
                ada = true;
                break;}}
        if (!ada) {
            return i;}}

    return jumlahBuku + 1;
}

string ubahStringKecilSemua(string teks) {
    for (size_t i = 0; i < teks.length(); i++) {
        teks[i] = tolower(teks[i]);}
    return teks;}