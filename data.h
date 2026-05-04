#pragma once
#include <iostream>
#include "json.hpp"
using namespace std;
using json = nlohmann::json;

struct Akun {
    string username;
    string password;
    string role;
    int saldo;};

struct Ebook {
    int no;
    string kode;
    string judul;
    string penulis;
    int tahun;
    string genre;
    int harga;};

struct EbookUser {
    string username;
    Ebook buku;};

// load
void loadAkun(Akun akun[], int &jumlahUser);
void loadBuku(Ebook katalog[], int &jumlahBuku);
void loadEbookUser(EbookUser ebookUser[], int &jumlahEbookUser);

// save
void saveAkun(Akun akun[], int jumlahUser);
void saveBuku(Ebook katalog[], int jumlahBuku);
void saveEbookUser(EbookUser ebookUser[], int jumlahEbookUser);