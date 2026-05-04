#pragma once
#include <string>
#include "data.h"
using namespace std;

void judul_subjudul(string subjudul);
void tampilPesan(int nilai, string pesan);
void tampilPeringatan(int nilai, string pesan);

int scrollMenu(int &pilih, int jumlahMenu);
int scrollBuku(Ebook *katalog, int &jumlahBuku, string judulMenu);

string inisialKode(string teks);
string generateKode(Ebook *katalog, int jumlahBuku, string judul, string penulis, int tahun);
int generateNo(Ebook *katalog, int &jumlahBuku);
string ubahStringKecilSemua(string teks);