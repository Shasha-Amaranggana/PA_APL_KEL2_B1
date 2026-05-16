#include <iostream>
#include <regex>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <cctype>
#include <limits>
#include <vector>
#include "json.hpp"
using json = nlohmann::json;
using namespace std;


//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                        WARNA CIAMIK CUKK
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define UNDER   "\033[4m"
#define HITAM   "\033[30m"
#define MERAH   "\033[31m"
#define HIJAU   "\033[32m"
#define KUNING  "\033[33m"
#define BIRU    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define PUTIH   "\033[37m"
#define BG_BIRU    "\033[44m"
#define BG_HIJAU   "\033[42m"
#define BG_MERAH   "\033[41m"
#define BG_PUTIH   "\033[47m"



//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                     STRUCT ADMIN DAN CRUD
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
struct Akun {
    string id_user, username, password, role,
        status_akun, email, alamat, no_hp;
    int tanggal_daftar, saldo;};

struct Ebook {
    int no;
    string kode, judul, penulis, genre;
    int tahun, harga;};

struct Library {
    string id_user, username;
    Ebook buku;};

struct Order {
    string id_order, id_user, kode;
    string judul;
    int harga;
    int tanggal_pesan, tanggal_bayar, tanggal_kirim, tanggal_sampai;
    string status_order, status_bayar, batal_oleh, alasan;};

struct Transaksi {
    string id_transaksi, id_user, id_order;
    int nominal;
    int tanggal_transaksi;};

struct Keranjang {
    string id_user;
    Ebook buku;};



//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                  FUNGSI LOAD & SAVE JSON
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void loadAkun(vector<Akun> &akun) {
    ifstream file("akun.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Akun a;
        a.id_user = item.at("id_user");
        a.username = item.at("username");
        a.password = item.at("password");
        a.role = item.at("role");
        a.status_akun = item.at("status_akun");
        a.email = item.at("email");
        a.alamat = item.at("alamat");
        a.no_hp = item.at("no_hp");
        a.tanggal_daftar = item.at("tanggal_daftar");
        a.saldo = item.at("saldo");
        akun.push_back(a);}}

void loadEbook(vector<Ebook> &ebook) {
    ifstream file("ebook.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Ebook e;
        e.no = item["no"];
        e.kode = item["kode"];
        e.judul = item["judul"];
        e.penulis = item["penulis"];
        e.genre = item["genre"];
        e.tahun = item["tahun"];
        e.harga = item["harga"];
        ebook.push_back(e);}}

void loadLibrary(vector<Library> &lib) {
    ifstream file("library.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Library l;
        l.id_user = item["id_user"];
        l.username = item["username"];
        l.buku.no = item["buku"]["no"];
        l.buku.kode = item["buku"]["kode"];
        l.buku.judul = item["buku"]["judul"];
        l.buku.penulis = item["buku"]["penulis"];
        l.buku.genre = item["buku"]["genre"];
        l.buku.tahun = item["buku"]["tahun"];
        l.buku.harga = item["buku"]["harga"];
        lib.push_back(l);}}

void loadOrder(vector<Order> &order) {
    ifstream file("orders.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Order o;
        o.id_order = item["id_order"];
        o.id_user = item["id_user"];
        o.kode = item["kode"];
        o.judul = item["judul"];
        o.harga = item["harga"];
        o.tanggal_pesan = item["tanggal_pesan"];
        o.tanggal_bayar = item["tanggal_bayar"];
        o.tanggal_kirim = item["tanggal_kirim"];
        o.tanggal_sampai = item["tanggal_sampai"];
        o.status_order = item["status_order"];
        o.status_bayar = item["status_bayar"];
        o.batal_oleh = item["batal_oleh"];
        o.alasan = item["alasan"];
        order.push_back(o);}}

void loadTransaksi(vector<Transaksi> &trans) {
    ifstream file("transaksi.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Transaksi t;
        t.id_transaksi = item["id_transaksi"];
        t.id_user = item["id_user"];
        t.id_order = item["id_order"];
        t.nominal = item["nominal"];
        t.tanggal_transaksi = item["tanggal_transaksi"];
        trans.push_back(t);}}

void loadKeranjang(vector<Keranjang> &ker) {
    ifstream file("keranjang.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Keranjang k;
        k.id_user = item["id_user"];
        k.buku.no = item["buku"]["no"];
        k.buku.kode = item["buku"]["kode"];
        k.buku.judul = item["buku"]["judul"];
        k.buku.penulis = item["buku"]["penulis"];
        k.buku.genre = item["buku"]["genre"];
        k.buku.tahun = item["buku"]["tahun"];
        k.buku.harga = item["buku"]["harga"];
        ker.push_back(k);}}

void saveAkun(vector<Akun> &akun) {
    json j = json::array();
    for (auto &a : akun) {
        j.push_back({
            {"id_user", a.id_user},
            {"username", a.username},
            {"password", a.password},
            {"role", a.role},
            {"status_akun", a.status_akun},
            {"email", a.email},
            {"alamat", a.alamat},
            {"no_hp", a.no_hp},
            {"tanggal_daftar", a.tanggal_daftar},
            {"saldo", a.saldo}
        });}
    ofstream file("akun.json");
    file << setw(4) << j;}

void saveEbook(vector<Ebook> &ebook) {
    json j = json::array();
    for (auto &e : ebook) {
        j.push_back({
            {"no", e.no},
            {"kode", e.kode},
            {"judul", e.judul},
            {"penulis", e.penulis},
            {"genre", e.genre},
            {"tahun", e.tahun},
            {"harga", e.harga}
        });}
    ofstream file("ebook.json");
    file << setw(4) << j;}

void saveLibrary(vector<Library> &lib) {
    json j = json::array();
    for (auto &l : lib) {
        j.push_back({
            {"id_user", l.id_user},
            {"username", l.username},
            {"buku", {
                {"no", l.buku.no},
                {"kode", l.buku.kode},
                {"judul", l.buku.judul},
                {"penulis", l.buku.penulis},
                {"genre", l.buku.genre},
                {"tahun", l.buku.tahun},
                {"harga", l.buku.harga}
            }}});}
    ofstream file("library.json");
    file << setw(4) << j;}

void saveOrder(vector<Order> &order) {
    json j = json::array();
    for (auto &o : order) {
        j.push_back({
            {"id_order", o.id_order},
            {"id_user", o.id_user},
            {"kode", o.kode},
            {"judul", o.judul},
            {"harga", o.harga},
            {"tanggal_pesan", o.tanggal_pesan},
            {"tanggal_bayar", o.tanggal_bayar},
            {"tanggal_kirim", o.tanggal_kirim},
            {"tanggal_sampai", o.tanggal_sampai},
            {"status_order", o.status_order},
            {"status_bayar", o.status_bayar},
            {"batal_oleh", o.batal_oleh},
            {"alasan", o.alasan}
        });}
    ofstream file("orders.json");
    file << setw(4) << j;}

void saveTransaksi(vector<Transaksi> &trans) {
    json j = json::array();
    for (auto &t : trans) {
        j.push_back({
            {"id_transaksi", t.id_transaksi},
            {"id_user", t.id_user},
            {"id_order", t.id_order},
            {"nominal", t.nominal},
            {"tanggal_transaksi", t.tanggal_transaksi}
        });}
    ofstream file("transaksi.json");
    file << setw(4) << j;}

void saveKeranjang(vector<Keranjang> &ker) {
    json j = json::array();
    for (auto &k : ker) {
        j.push_back({
            {"id_user", k.id_user},
            {"buku", {
                {"no", k.buku.no},
                {"kode", k.buku.kode},
                {"judul", k.buku.judul},
                {"penulis", k.buku.penulis},
                {"genre", k.buku.genre},
                {"tahun", k.buku.tahun},
                {"harga", k.buku.harga}
        }}});}
    ofstream file("keranjang.json");
    file << setw(4) << j;}



//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                FUNGSI BANTUAN
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void judul_subjudul(string subjudul) {
    string spasiPesan = string(((140 - subjudul.length())) / 2, ' ');
    cout << "+=========+=========+=========+=========+=========+=========+========++========+=========+=========+=========+=========+=========+=========+" << endl;
    cout << BIRU << BOLD << "╔══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║" << KUNING << BOLD << "                                                       ☕📓   E-BOOKIE STORE   📓☕                                                       " << BIRU << BOLD << "║" << endl;
    cout << "╚══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝" << endl;
    cout << CYAN << BOLD << "                             ══════════════════════════════════════════════════════════════════════════════════" << endl;
    cout << spasiPesan << subjudul << endl;
    cout << "                             ══════════════════════════════════════════════════════════════════════════════════" << RESET << endl;}

void tampilPesan(int nilai, string pesan) {
    string spasiGaris = string((140 - 32) / 2, ' ');
    string spasiPesan = string((140 - nilai) / 2, ' ');
    cout << HIJAU << BOLD << endl;
    cout << spasiGaris << "================================" << endl;
    cout << spasiPesan << pesan << endl;
    cout << spasiGaris << "================================" << endl;
    cout << RESET << endl;}

/* [OVERLOAD]*/
void tampilPesan(string pesan) {
    tampilPesan((int)pesan.length(), pesan);}

void tampilPeringatan(int nilai, string pesan) {
    string spasiGaris = string((140 - 40) / 2, ' ');
    string spasiPesan = string((140 - nilai) / 2, ' ');
    cout << KUNING << BOLD << endl;
    cout << spasiGaris << "----------------------------------------" << endl;
    cout << spasiPesan << pesan << endl;
    cout << spasiGaris << "----------------------------------------" << endl;
    cout << RESET << endl;}

/* [OVERLOAD]*/
void tampilPeringatan(string pesan) {
    tampilPeringatan((int)pesan.length(), pesan);}

string spasi(int nilai) {
    return string(nilai, ' ');}

void tengah(string text) {
    int lebarTerminal = 140;
    int spasi = (lebarTerminal - text.length()) / 2;
    if (spasi < 0) spasi = 0;
    cout << string(spasi, ' ') << text;}

void clsScroll(int x, int y) {
    COORD c = {SHORT(x), SHORT(y)};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);}

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

int scrollBuku(vector<Ebook> &ebook, string judulMenu) {
    int pilih = 0;
    bool refresh = true;

    vector<int> indexEbook;
    for (size_t i = 0; i < ebook.size(); i++) {
        indexEbook.push_back(i);} 
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu); cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih E-book:" << RESET; cout << endl;
        for (size_t i = 0; i < indexEbook.size(); i++) {
            if (i == pilih) 
                {cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(4) << ebook[indexEbook[i]].no << "│ " << setw(38) << ebook[indexEbook[i]].judul << "│ " << setw(18) << ebook[indexEbook[i]].kode <<  "│ " << setw(20) << ebook[indexEbook[i]].penulis << RESET << endl;}
            else {
                cout << DIM << spasi(34) << "     " << setw(4) << ebook[indexEbook[i]].no << "│ " << setw(38) << ebook[indexEbook[i]].judul << "│ " << setw(18) << ebook[indexEbook[i]].kode <<  "│ " << setw(20) << ebook[indexEbook[i]].penulis << RESET << endl;}}
        int hasil = scrollMenu(pilih, indexEbook.size());
        if (hasil == -1) {
            refresh = true;
            return indexEbook[pilih];}}}

int scrollAkun(vector<Akun> &akun, string judulMenu) {
    int pilih = 0;
    bool refresh = true;

    vector<int> indexUser;
    for (size_t i = 0; i < akun.size(); i++) {
        if (akun[i].role == "User") indexUser.push_back(i);}
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu); cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih akun pelanggan:" << RESET; cout << endl;
        for (size_t i = 0; i < indexUser.size(); i++) {
            if (i == pilih)
                {cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(9) << akun[indexUser[i]].id_user <<  "│ " << setw(18) << akun[indexUser[i]].username << RESET << endl;}
            else {
                cout << DIM << spasi(34) << "     " << setw(9) << akun[indexUser[i]].id_user <<  "│ " << setw(18) << akun[indexUser[i]].username << RESET << endl;}}
        int hasil = scrollMenu(pilih, indexUser.size());
        if (hasil == -1) {
            refresh = true;
            return indexUser[pilih];}}}

int scrollOrder(vector<Order> &order, string judulMenu, string jenis, string id_user = "") {
    int pilih = 0;
    bool refresh = true;

    vector<int> indexOrder;
    for (size_t i = 0; i < order.size(); i++) {
        if (id_user != "" && order[i].id_user != id_user)
            continue;
        if (jenis == "Ditunggu") {
            if (order[i].status_order == "Ditunggu") indexOrder.push_back(i);}
        if (jenis == "Diproses") {
            if (order[i].status_order == "Diproses") indexOrder.push_back(i);}
        if (jenis == "Selesai") {
            if (order[i].status_order == "Selesai") indexOrder.push_back(i);}
        if (jenis == "Dikirim_Dibatalkan") {
            if (order[i].status_order == "Dikirim" || order[i].status_order == "Dibatalkan") indexOrder.push_back(i);}}
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu); cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih pesanan:" << RESET; cout << endl;
        for (size_t i = 0; i < indexOrder.size(); i++) {
            if (id_user == "") {
                if (i == pilih)
                    {cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(18) << order[indexOrder[i]].id_order <<  "│ " << setw(12) << order[indexOrder[i]].id_user <<  "│ " << setw(26) << order[indexOrder[i]].kode  << RESET << endl;}
                else {
                    cout << DIM << spasi(34) << "     " << setw(18) << order[indexOrder[i]].id_order <<  "│ " << setw(12) << order[indexOrder[i]].id_user <<  "│ " << setw(26) << order[indexOrder[i]].kode  << RESET << endl;}}
            else {
                if (i == pilih)
                    {cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(18) << order[indexOrder[i]].id_order  <<  "│ " << setw(26) << order[indexOrder[i]].kode  << RESET << endl;}
                else {
                    cout << DIM << spasi(34) << "     " << setw(18) << order[indexOrder[i]].id_order <<  "│ " << setw(26) << order[indexOrder[i]].kode  << RESET << endl;}}}
        int hasil = scrollMenu(pilih, indexOrder.size());
        if (hasil == -1) {
            refresh = true;
            return indexOrder[pilih];}}}

int scrollKeranjang(vector<Keranjang> &keranjang, string judulMenu, string id_user) {
    int pilih = 0;
    bool refresh = true;

    vector<int> indexKeranjang;
    for (size_t i = 0; i < keranjang.size(); i++) {
        if (keranjang[i].id_user == id_user) indexKeranjang.push_back(i);}
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu); cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih E-book di keranjang:" << RESET; cout << endl;
        for (size_t i = 0; i < indexKeranjang.size(); i++) {
            if (i == pilih)
                {cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(18) << keranjang[indexKeranjang[i]].buku.kode  <<  "│ " << setw(26) << keranjang[indexKeranjang[i]].buku.judul  << RESET << endl;}
            else {
                cout << DIM << spasi(34) << "     " << setw(18) << keranjang[indexKeranjang[i]].buku.kode  <<  "│ " << setw(26) << keranjang[indexKeranjang[i]].buku.judul  << RESET << endl;}}
        int hasil = scrollMenu(pilih, indexKeranjang.size());
        if (hasil == -1) {
            refresh = true;
            return indexKeranjang[pilih];}}}


string inisialKode(string teks) {
    string hasil = "";
    bool ambil = true;
    for (size_t i = 0; i < teks.length(); i++) {
        if (ambil && isalpha(teks[i])) {
            hasil += toupper(teks[i]);
            ambil = false;}
        if (teks[i] == ' ') {
            ambil = true;}}
    return hasil;}

string generateKode(vector<Ebook> &katalog, string judul, string penulis, int tahun) {
    int nomor = 1;
    string nomorStr, inisialJudul = inisialKode(judul), inisialPenulis = inisialKode(penulis);

    for (size_t i = 0; i < katalog.size(); i++) {
        if (katalog[i].judul == judul &&
            katalog[i].penulis == penulis &&
            katalog[i].tahun == tahun) {
            nomor++;}}
    if (nomor < 10) nomorStr = "00" + to_string(nomor);
    else if (nomor < 100) nomorStr = "0" + to_string(nomor);
    else nomorStr = to_string(nomor);
    return inisialJudul + inisialPenulis + to_string(tahun) + nomorStr;}

int generateNo(vector<Ebook> &katalog) {
    for (int i = 1; i <= static_cast<int>(katalog.size() + 1); i++) {
        bool ada = false;
        for (size_t j = 0; j < katalog.size(); j++) {
            if (katalog[j].no == i) {
                ada = true;
                break;}}
        if (!ada) {
            return i;}}

    return katalog.size() + 1;}

string ubahStringKecilSemua(string teks) {
    for (size_t i = 0; i < teks.length(); i++) {
        teks[i] = tolower(teks[i]);}
    return teks;}


void bubbleSortEbook(vector<Ebook> &ebook, int kategori, bool ascending) {
    for (size_t i = 0; i < ebook.size() - 1; i++) {
        for (size_t j = 0; j < ebook.size() - i - 1; j++) {
            bool tukar = false;

            // JUDUL
            if (kategori == 0) {
                if (ascending) tukar = ebook[j].judul > ebook[j + 1].judul;
                else tukar = ebook[j].judul < ebook[j + 1].judul;}

            // PENULIS
            else if (kategori == 1) {
                if (ascending) tukar = ebook[j].penulis > ebook[j + 1].penulis;
                else tukar = ebook[j].penulis < ebook[j + 1].penulis;}

            // GENRE
            else if (kategori == 2) {
                if (ascending)  tukar = ebook[j].genre > ebook[j + 1].genre;
                else tukar = ebook[j].genre < ebook[j + 1].genre;}

            // TAHUN
            else if (kategori == 3) {
                if (ascending) tukar = ebook[j].tahun > ebook[j + 1].tahun;
                else tukar = ebook[j].tahun < ebook[j + 1].tahun;}

            // HARGA
            else if (kategori == 4) {
                if (ascending) tukar = ebook[j].harga > ebook[j + 1].harga;
                else tukar = ebook[j].harga < ebook[j + 1].harga;}

            // KODE
            else if (kategori == 5) {
                if (ascending) tukar = ebook[j].kode > ebook[j + 1].kode;
                else tukar = ebook[j].kode < ebook[j + 1].kode;}

            // NO
            else if (kategori == 6) {
                if (ascending) tukar = ebook[j].no > ebook[j + 1].no;
                else tukar = ebook[j].no < ebook[j + 1].no;}

            if (tukar) {
                swap(ebook[j], ebook[j + 1]);}}}}

void bubbleSortOrder(vector<Order> &order) {
    for (size_t i = 0; i < order.size() - 1; i++) {
        for (size_t j = 0; j < order.size() - i - 1; j++) {
            bool tukar = false;
            tukar = order[j].id_order < order[j + 1].id_order;
            if (tukar) {
                swap(order[j], order[j + 1]);}}}}

int linearSearchEbook(vector<Ebook> &ebook, vector<Ebook> &hasil, int jenis, string keyword = "", int min = 0, int max = 0) {
    hasil.clear();
    string key = ubahStringKecilSemua(keyword);
    for (size_t i = 0; i < ebook.size(); i++) {

        // JUDUL
        if (jenis == 1) {
            if (ubahStringKecilSemua(ebook[i].judul).find(key) != string::npos) {
                hasil.push_back(ebook[i]);}}

        // PENULIS
        else if (jenis == 2) {
            if (ubahStringKecilSemua(ebook[i].penulis).find(key) != string::npos) {
                hasil.push_back(ebook[i]);}}

        // GENRE
        else if (jenis == 3) {
            if (ubahStringKecilSemua(ebook[i].genre).find(key) != string::npos) {
                hasil.push_back(ebook[i]);}}

        // TAHUN
        else if (jenis == 4) {
            if (ebook[i].tahun >= min && ebook[i].tahun <= max) {
                hasil.push_back(ebook[i]);}}

        // HARGA
        else if (jenis == 5) {
            if (ebook[i].harga >= min && ebook[i].harga <= max) {
                hasil.push_back(ebook[i]);}}

        // KODE
        else if (jenis == 6) {
            if (ubahStringKecilSemua(ebook[i].kode).find(key) != string::npos) {
                hasil.push_back(ebook[i]);}}}

    return hasil.size();}

int linearSearchOrder(vector<Order> &order, vector<Order> &hasil, string keyword = "", int index = 0) {
    if (index == 0) hasil.clear();
    if (index >= order.size()) return hasil.size();
    string key = ubahStringKecilSemua(keyword);
    if (order[index].status_order == "Selesai") {
        if (ubahStringKecilSemua(order[index].id_order).find(key) != string::npos) {
            hasil.push_back(order[index]);}}
    return linearSearchOrder(order, hasil, keyword, index + 1);}



//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                FUNGSI LOGIN DAN REGISTRASI
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
int login(vector<Akun> &akun, int percobaan = 0) {
    if (percobaan >= 3) {
        tampilPesan("Anda telah salah 3 kali. Silakan datang lain kali.");
        system("pause");
        return -3;}

    string jawabNama, jawabPassword;

    cout << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Username: " << RESET; cin >> jawabNama;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Password: " << RESET; cin >> jawabPassword;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;

    for (size_t i = 0; i < akun.size(); i++) {
        if (akun[i].username == jawabNama && akun[i].password == jawabPassword) {
            if (akun[i].status_akun == "Nonaktif") {
                tampilPeringatan("Akun anda nonaktif!");
                system("pause");
                return -2;}
            tampilPesan(35, "Login berhasil! Selamat datang, " + jawabNama);
            system("pause");
            return i;}}

    tampilPeringatan("Username atau Password salah atau akun belum terdaftar!");
    int sisa = 2 - percobaan;
    tampilPeringatan("Kesempatan anda tersisa " + to_string(sisa));
    system("pause");
    system("cls"); judul_subjudul("LOG IN AKUN ANDA");
    return login(akun, percobaan + 1);}

void registrasi(vector<Akun> &akun) {
    string username, password, email, no_hp, alamat;

    cout << KUNING << endl;
    cout << spasi(30) << "☞    Username min 5 karakter, mengandung huruf/angka, tidak mengandung simbol/" << endl;
    cout << spasi(30) << "     karakter spesial kecuali spasi/underscroe" << endl;
    cout << spasi(30) << "☞    Password min 8 karakter, mengandung huruf besar & kecil & angka, simbol" << endl;
    cout << spasi(30) << "     diperbolehkan"<< endl;
    cout << spasi(30) << "☞    Email harus valid dan berakhiran '@gmail.com'" << endl;
    cout << spasi(30) << "☞    No. HP harus valid, berawalan '08', min 10 angka" << RESET << endl << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Username : " << RESET; cin >> username;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Password : " << RESET; cin >> password;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Email    : " << RESET; cin >> email;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "No. HP   : " << RESET; cin >> no_hp;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Alamat   : " << RESET; cin >> alamat;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;

    regex userRegex("^[a-zA-Z0-9_ ]{5,}$");
    regex passRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$");
    regex hpRegex("^08\\d{8,12}$");
    if (!regex_match(username, userRegex)) {
        tampilPeringatan(22, "Username tidak valid!"); return;}
    if (!regex_match(password, passRegex)) {
        tampilPeringatan(54, "Password harus 8 karakter + huruf besar, kecil, angka!"); return;}
    if (!regex_match(no_hp, hpRegex)) {
        tampilPeringatan(18, "No HP tidak valid!"); return;}
    if (email.find("@gmail.com") == string::npos) {
        tampilPeringatan(24, "Email harus @gmail.com!");return;}

    for (auto &a : akun) {
        if (a.username == username) {
            tampilPeringatan(20, "Username sudah ada!"); return;}
        if (a.email == email) {
            tampilPeringatan(22, "Email sudah digunakan!"); return;}}
    string newID = "U" + to_string(0000 + akun.size());
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int tanggal =
        (1900 + ltm->tm_year) * 10000 +
        (1 + ltm->tm_mon) * 100 +
        ltm->tm_mday;
    Akun baru;
    baru.id_user = newID;
    baru.username = username;
    baru.password = password;
    baru.role = "User";
    baru.status_akun = "Aktif";
    baru.email = email;
    baru.no_hp = no_hp;
    baru.alamat = alamat;
    baru.tanggal_daftar = tanggal;
    baru.saldo = 0;

    akun.push_back(baru);
    tampilPesan(20, "Registrasi berhasil!");
}



//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                FUNGSI MENU ADMIN
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/

/*  MENU KELOLA AKUN PELANGGAN
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatDetailAkun(vector<Akun> &akun, int indeksLogin) {
    string passwordSensor = string(akun[indeksLogin].password.length(), '*');
    string field[10] = {
        "ID USER", "USERNAME", "PASSWORD", "ROLE", "STATUS AKUN", "EMAIL", "ALAMAT", "NO HP", "TANGGAL DAFTAR", "SALDO"};
    string data[10] = {
        akun[indeksLogin].id_user,
        akun[indeksLogin].username,
        passwordSensor,
        akun[indeksLogin].role,
        akun[indeksLogin].status_akun,
        akun[indeksLogin].email,
        akun[indeksLogin].alamat,
        akun[indeksLogin].no_hp,
        to_string(akun[indeksLogin].tanggal_daftar),
        "Rp" + to_string(akun[indeksLogin].saldo)};

    cout << CYAN << BOLD;
    cout << spasi(40) << "┌──────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(40) << "│                  DETAIL AKUN PELANGGAN                   │" << endl;
    cout << spasi(40) << "├────────────────────┬─────────────────────────────────────┤" << endl;
    cout << spasi(40) << "│ FIELD              │ DATA                                │" << endl;
    cout << spasi(40) << "├────────────────────┼─────────────────────────────────────┤" << endl;
    cout << RESET;

    for (int i = 0; i < 10; i++) {
        cout << spasi(40);
        if (i % 2 == 0) cout << "\033[48;5;235m";
        cout << "│ " << left << setw(19) << field[i]
            << "│ " << setw(36) << data[i]
            << "│" << RESET << endl;}
    cout << CYAN;
    cout << spasi(40) << "└────────────────────┴─────────────────────────────────────┘" << endl;
    cout << RESET << endl;}

void lihatDaftarPelanggan(vector<Akun> &akun) {
    bool ada = true;
    for (auto &a : akun) {
        if (a.role == "User") {ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(36, "Belum ada pelanggan yang terdaftar!");
        return;}

    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                     DAFTAR AKUN PELANGGAN                                                    │" << endl;
    cout << spasi(6) << "├────┬──────────┬────────────────────┬───────────────────────────────┬──────────────────┬─────┬────────────────┬───────────────┤" << endl;
    cout << spasi(6) << "│ NO │ ID USER  │ USERNAME           │ EMAIL                         │ NO HP            │ ALAMAT               │ STATUS AKUN   │" << endl;
    cout << spasi(6) << "├────┼──────────┼────────────────────┼───────────────────────────────┼──────────────────┼──────────────────────┼───────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (size_t i = 0; i < akun.size(); i++) {
        if (akun[i].role == "User") {
            cout << spasi(6);
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(3) << no++
                << "│ " << setw(9) << akun[i].id_user
                << "│ " << setw(19) << akun[i].username
                << "│ " << setw(30) << akun[i].email
                << "│ " << setw(17) << akun[i].no_hp
                << "│ " << setw(21) << akun[i].alamat << "│ ";
            if (akun[i].status_akun == "aktif" || akun[i].status_akun == "Aktif")
                cout << HIJAU << BOLD << setw(14) << akun[i].status_akun << RESET;
            else
                cout << MERAH << BOLD << setw(14) << akun[i].status_akun << RESET;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└────┴──────────┴────────────────────┴───────────────────────────────┴──────────────────┴──────────────────────┴───────────────┘" << endl;
    cout << RESET << endl;}

void editStatusPelanggan(vector<Akun> &akun) {
    string tindakan[] = {
        "【 1 | Aktifkan      】",
        "【 2 | Nonaktifkan   】",
        "【 3 | Batalkan      】"};

    bool ada = false;
    for (auto &a : akun) {
        if (a.role == "User") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(36, "Belum ada pelanggan yang terdaftar!");
        system("pause");
        return;}
    int pilihan = scrollAkun(akun, "EDIT STATUS AKUN PELANGGAN");

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("EDIT STATUS AKUN PELANGGAN"); cout << endl;
        lihatDetailAkun(akun, pilihan);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Ubah status akun pelanggan?" << RESET; cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;

            // AKTIFKAN
            if (pilih == 0) {
                if (akun[pilihan].status_akun == "Aktif") {
                    tampilPeringatan(18, "Akun sudah aktif!");}
                else {
                    akun[pilihan].status_akun = "Aktif";
                    saveAkun(akun);
                    tampilPesan(26, "Akun berhasil diaktifkan!");}
                system("pause");
                break;}

            // NONAKTIFKAN
            else if (pilih == 1){
                if (akun[pilihan].status_akun == "Nonaktif") {
                    tampilPeringatan(20, "Akun sudah nonaktif!");}
                else {
                    akun[pilihan].status_akun = "Nonaktif";
                    saveAkun(akun);
                    tampilPesan(28, "Akun berhasil dinonaktifkan!");}
                system("pause");
                break;}
            
            else {
                break;}}}}

/*  MENU PENJUALAN
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatDetailEbook(vector<Ebook> &ebook, int indeksEbook) {
    string field[7] = {
        "NO", "KODE", "JUDUL", "PENULIS", "TAHUN", "GENRE", "HARGA"};
    string data[10] = {
        to_string(ebook[indeksEbook].no),
        ebook[indeksEbook].kode,
        ebook[indeksEbook].judul,
        ebook[indeksEbook].penulis,
        to_string(ebook[indeksEbook].tahun),
        ebook[indeksEbook].genre,
        to_string(ebook[indeksEbook].harga)};

    cout << CYAN << BOLD;
    cout << spasi(40) << "┌──────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(40) << "│                      DETAIL E-BOOK                       │" << endl;
    cout << spasi(40) << "├─────────┬────────────────────────────────────────────────┤" << endl;
    cout << spasi(40) << "│ FIELD   │ DATA                                           │" << endl;
    cout << spasi(40) << "├─────────┼────────────────────────────────────────────────┤" << endl;
    cout << RESET;

    for (int i = 0; i < 7; i++) {
        cout << spasi(40);
        if (i % 2 == 0) cout << "\033[48;5;235m";
        cout << "│ " << left << setw(8) << field[i]
            << "│ " << setw(47) << data[i]
            << "│" << RESET << endl;}
    cout << CYAN;
    cout << spasi(40) << "└─────────┴────────────────────────────────────────────────┘" << endl;
    cout << RESET << endl;}

void lihatDaftarEbook(vector<Ebook> &ebook) {
    if (ebook.empty()) {
        tampilPesan(28, "Katalog E-book belum terisi.");
        return;}
    cout << CYAN << BOLD;
    cout << "  ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "  │                                                         DAFTAR E-BOOK KATALOG                                                        │" << endl;
    cout << "  ├──────┬───────────────────┬────────────────────────────────────────┬────────────────────────┬───────┬─────────────────┬───────────────┤" << endl;
    cout << "  │ NO   │ KODE              │ JUDUL                                  │ PENULIS                │ TAHUN │ GENRE           │ HARGA         │" << endl;
    cout << "  ├──────┼───────────────────┼────────────────────────────────────────┼────────────────────────┼───────┼─────────────────┼───────────────┤" << endl;
    cout << RESET;
    for (size_t i = 0; i < ebook.size(); i++) {
        cout << "  ";
        if (ebook[i].no % 2 == 0) cout << "\033[48;5;235m";
        cout << "│ " << left << setw(5) << ebook[i].no
            << "│ " << setw(18) << ebook[i].kode
            << "│ " << setw(39) << ebook[i].judul
            << "│ " << setw(23) << ebook[i].penulis
            << "│ " << setw(6) << ebook[i].tahun
            << "│ " << setw(16) << ebook[i].genre
            << "│ " << setw(14) << ebook[i].harga;
        cout << "│" << RESET << endl;}
    cout << CYAN;
    cout << "  └──────┴───────────────────┴────────────────────────────────────────┴────────────────────────┴───────┴─────────────────┴───────────────┘" << endl;
    cout << RESET << endl;}

void tambahEbook(vector<Ebook> &ebook) {
    string input;
    Ebook baru;
    string genre[] = {
        "Romance", "Fantasy", "Horror", "Mystery", "Thriller", "Sci-Fi", "Adventure", "Action", "Drama", "Comedy",
        "Historical", "Crime", "Psychological", "Slice of Life", "School", "Supernatural", "Family", "Friendship",
        "Religious", "Biography"};
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};

    system("cls"); judul_subjudul("TAMBAH E-BOOK"); cout << endl;
    cin.ignore(1000, '\n');
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Judul   : " << RESET; getline(cin, baru.judul);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Penulis : " << RESET; getline(cin, baru.penulis);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Tahun   : " << RESET; cin >> input;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    for (char c : input) {
        if (!isdigit(c)) {
            tampilPeringatan(26, "Tahun harus berupa angka!");
            return;}}
    try {
        baru.tahun = stoi(input);}
    catch (...) {
        tampilPeringatan(20, "Angka terlalu besar!");
        return;}
    if (baru.tahun < 1000 || baru.tahun > 3000) {
        tampilPeringatan(46, "Tahun harus berada di rentang tahun 1000-3000!");
        return;}

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("TAMBAH E-BOOK");
        cout << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Judul   : " << RESET << baru.judul << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Penulis : " << RESET << baru.penulis << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Tahun   : " << RESET << baru.tahun << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Genre   : " << RESET;
        cout << endl;
        for (int i = 0; i < 20; i++) {
            if (i == pilih)
                cout << spasi(52) << "➠    " << BG_PUTIH << HITAM << BOLD << genre[i] << RESET << endl;
            else cout << DIM << spasi(52) << "➠    " << genre[i] << RESET << endl;}
        int hasil = scrollMenu(pilih, 20);
        if (hasil == -1) {
            refresh = true;
            baru.genre = genre[pilih];
            break;}}

    system("cls"); judul_subjudul("TAMBAH E-BOOK");
    cout << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Judul   : " << RESET << baru.judul << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Penulis : " << RESET << baru.penulis << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Tahun   : " << RESET << baru.tahun << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Genre   : " << RESET << baru.genre << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Harga   : " << RESET; cin >> input;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    for (char c : input) {
        if (!isdigit(c)) {
            tampilPeringatan(26, "Harga harus berupa angka!");
            return;}}
    try {
        baru.harga = stoi(input);}
    catch (...) {
        tampilPeringatan(20, "Angka terlalu besar!");
        return;}
    if (baru.harga < 0 || baru.harga > 10000000) {
        tampilPeringatan(50, "Harga harus berada di rentang tahun 0-10.000.000!");
        return;}

    int pilihTindakan = 0;
    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("TAMBAH E-BOOK");
        cout << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Judul   : " << RESET << baru.judul << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Penulis : " << RESET << baru.penulis << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Tahun   : " << RESET << baru.tahun << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Genre   : " << RESET << baru.genre << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Harga   : " << RESET << baru.harga << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << endl;
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Simpan E-Book?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // SIMPAN
            if (pilihTindakan == 0) {
                baru.no = generateNo(ebook);
                baru.kode = generateKode(ebook, baru.judul, baru.penulis, baru.tahun);
                ebook.push_back(baru);
                bubbleSortEbook(ebook, 6, true);
                cout << endl; tampilPesan(28, "E-book berhasil ditambahkan!");
                break;}

            else {
                tampilPeringatan(22, "Penambahan dibatalkan!");
                break;}}}
    return;}

void editEbook(vector<Ebook> &ebook) {
    string inputJudul, inputPenulis, inputTahun, inputHarga;
    string genre[] = {
        "Romance", "Fantasy", "Horror", "Mystery", "Thriller", "Sci-Fi", "Adventure", "Action", "Drama", "Comedy",
        "Historical", "Crime", "Psychological", "Slice of Life", "School", "Supernatural", "Family", "Friendship",
        "Religious", "Biography"};
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};

    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi!");
        return;}

    int pilihan = scrollBuku(ebook, "EDIT DETAIL E-BOOK");
    system("cls"); judul_subjudul("EDIT DETAIL E-BOOK"); cout << endl;
    lihatDetailEbook(ebook, pilihan); cout << endl;
    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
    cout << KUNING << spasi(30) << "☞    Enter jika tidak ingin merubah salah satu field data (kecuali Genre)" << RESET << endl;

    Ebook temp = ebook[pilihan];
    cin.ignore(1000, '\n'); cout << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Judul Baru   : " << RESET; getline(cin, inputJudul);
    if (!inputJudul.empty()) {temp.judul = inputJudul;};
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Penulis Baru : " << RESET; getline(cin, inputPenulis);
    if (!inputPenulis.empty()) {temp.penulis = inputPenulis;};
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Tahun Baru   : " << RESET; getline(cin, inputTahun);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    if (!inputTahun.empty()) {
        for (char c : inputTahun) {
            if (!isdigit(c)) {
                tampilPeringatan(26, "Tahun harus berupa angka!");
                return;}}
        try {
            temp.tahun = stoi(inputTahun);}
        catch (...) {
            tampilPeringatan(20, "Angka terlalu besar!");
            return;}
        if (temp.tahun < 1000 || temp.tahun > 3000) {
            tampilPeringatan(46, "Tahun harus berada di rentang tahun 1000-3000!");
            return;}}

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("EDIT DETAIL E-BOOK");
        lihatDetailEbook(ebook, pilihan); cout << endl;
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << KUNING << spasi(30) << "☞    Enter jika tidak ingin merubah salah satu field data (kecuali Genre)" << RESET << endl;
        cout << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Judul Baru   : " << RESET << temp.judul << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Penulis Baru : " << RESET << temp.penulis << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Tahun Baru   : " << RESET << temp.tahun << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Genre Baru   : " << RESET;
        cout << endl;
        for (int i = 0; i < 20; i++) {
            if (i == pilih)
                cout << spasi(52) << "➠    " << BG_PUTIH << HITAM << BOLD << genre[i] << RESET << endl;
            else cout << DIM << spasi(52) << "➠    " << genre[i] << RESET << endl;}
        int hasil = scrollMenu(pilih, 20);
        if (hasil == -1) {
            refresh = true;
            temp.genre = genre[pilih];
            break;}}

    system("cls"); judul_subjudul("EDIT DETAIL E-BOOK");
    lihatDetailEbook(ebook, pilihan); cout << endl;
    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
    cout << KUNING << spasi(30) << "☞    Enter jika tidak ingin merubah salah satu field data (kecuali Genre)" << RESET << endl;
    cout << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Judul Baru   : " << RESET << temp.judul << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Penulis Baru : " << RESET << temp.penulis << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Tahun Baru   : " << RESET << temp.tahun << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Genre Baru   : " << RESET << temp.genre << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Harga Baru   : " << RESET; getline(cin, inputHarga);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    if (!inputHarga.empty()) {
        for (char c : inputHarga) {
            if (!isdigit(c)) {
                tampilPeringatan(26, "Harga harus berupa angka!");
                return;}}
        try {
            temp.harga = stoi(inputHarga);}
        catch (...) {
            tampilPeringatan(20, "Angka terlalu besar!");
            return;}
        if (temp.harga < 0 || temp.harga > 10000000) {
            tampilPeringatan(50, "Harga harus berada di rentang tahun 0-10.000.000!");
            return;}}

    int pilihTindakan = 0;
    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("EDIT DETAIL E-BOOK");
        cout << endl;
        lihatDetailEbook(ebook, pilihan); cout << endl;
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << spasi(34) << BOLD << KUNING << "Data perubahan:" << RESET; cout << endl;
        cout << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Judul Baru   : " << RESET << temp.judul << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Penulis Baru : " << RESET << temp.penulis << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Tahun Baru   : " << RESET << temp.tahun << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Genre Baru   : " << RESET << temp.genre << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Harga Baru   : " << RESET << temp.harga << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << endl;
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Simpan perubahan?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // SIMPAN
            if (pilihTindakan == 0) {
                ebook[pilihan] = temp;
                ebook[pilihan].kode = generateKode(ebook,temp.judul, temp.penulis,temp.tahun);
                saveEbook(ebook);
                tampilPesan(26, "Perubahan berhasil disimpan!");
                break;}

            else {
                tampilPeringatan(22, "Perubahan dibatalkan!");
                break;}}}
    return;}

void hapusEbook(vector<Ebook> &ebook) {
    string tindakan[] = {
        "【 1 | Hapus         】",
        "【 2 | Batalkan      】"};
    int pilihTindakan = 0;

    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi.");
        return;}

    int pilihan = scrollBuku(ebook, "HAPUS E-BOOK");

    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("HAPUS E-BOOK"); cout << endl;
        lihatDetailEbook(ebook, pilihan);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Hapus E-Book ini?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // HAPUS
            if (pilihTindakan == 0) {
                ebook.erase(ebook.begin() + pilihan);
                tampilPesan(24, "E-Book berhasil dihapus!");
                break;}

            else {
                tampilPeringatan(24, "Penghapusan dibatalkan!");
                break;}}}
    return;}

void urutEbook(vector<Ebook> &ebook) {
    string menuUrut[] = {
        "『  📝 Judul                      』",
        "『  🪶  Penulis                    』",
        "『  🏷️  Genre                      』",
        "『  🗓️  Tahun                      』",
        "『  💲 Harga                      』",
        "『  🔑 Kode                       』",
        "『 ↩   Kembali                    』"};
    string jenisUrut[] = {
        "『  ⬆️  Ascending                  』",
        "『  ⬇️  Descending                 』"}; 
    int pilih = 0;
    bool refresh = true;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("URUTKAN KATALOG"); cout << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << menuUrut[i] << RESET << endl;
            else cout << DIM << spasi(34) << menuUrut[i] << RESET << endl;}
        cout << endl; lihatDaftarEbook(ebook); 
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {
            refresh = true;

            // KEMBALI
            if (pilih == 6) {
                break; }
            
            // URUTKAN ASCENDING OR DESCENDING
            int pilihJenis = 0;
            bool refreshTindakan = true;
            while (true) {
                if (refreshTindakan) {
                    system("cls"); refreshTindakan = false;}
                clsScroll(0,0); judul_subjudul("JENIS PENGURUTAN"); cout << endl;
                cout << KUNING << BOLD << spasi(34) << "Kategori: " << RESET << BOLD << menuUrut[pilih] << RESET << "\n\n";
                for (int i = 0; i < 2; i++) {
                    if (i == pilihJenis) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << jenisUrut[i] << RESET << endl;
                    else cout << DIM << spasi(34) << jenisUrut[i] << RESET << endl;}
                cout << endl; lihatDaftarEbook(ebook);
                int hasilJenis = scrollMenu(pilihJenis, 2);
                if (hasilJenis == -1) {
                    refreshTindakan = true;

                    vector<Ebook> temp = ebook; 
                    bool ascending = (pilihJenis == 0);
                    bubbleSortEbook(temp, pilih, ascending);
                    system("cls"); judul_subjudul("HASIL PENGURUTAN SEMENTARA"); cout << endl;
                    lihatDaftarEbook(temp);
                    
                    system("pause");
                    break;}

                else if (hasilJenis == 27) break;}}}}

void cariEbook(vector<Ebook> &ebook) {
    string menuCari[] = {
        "『  📝 Judul                      』",
        "『  🪶  Penulis                    』",
        "『  🏷️  Genre                      』",
        "『  🗓️  Tahun                      』",
        "『  💲 Harga                      』",
        "『  🔑 Kode                       』",
        "『 ↩   Kembali                    』"};
    int pilih = 0;
    bool refresh = true;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false; }
        clsScroll(0,0); judul_subjudul("CARI E-BOOK"); cout << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << menuCari[i] << RESET << endl;
            else cout << DIM << spasi(34) << menuCari[i] << RESET << endl;}
        cout << endl; lihatDaftarEbook(ebook);
        int hasilScroll = scrollMenu(pilih, 7);
        if (hasilScroll == -1) {
            refresh = true;

            // KEMBALI
            if (pilih == 6) {
                break;}
            
            // CARI JUDUL, PENULIS, GENRE, KODE
            vector<Ebook> hasil;
            if (pilih == 0 || pilih == 1 || pilih == 2 || pilih == 5) {
                system("cls"); judul_subjudul("CARI E-BOOK"); cout << endl;
                string keyword; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            
                cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                cout << spasi(47) << BOLD << "Keyword   : " << RESET; getline(cin, keyword);
                cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;

                if (keyword.find_first_not_of(' ') == string::npos) {
                    tampilPeringatan(28, "Keyword tidak boleh kosong!");
                    system("pause");
                    continue; }
                linearSearchEbook(ebook, hasil, pilih + 1, keyword);}

            // CARI TAHUN, HARGA
            else {
                system("cls"); judul_subjudul("CARI E-BOOK"); cout << endl;
                int min, max;
                string inputMin, inputMax;
                bool error = false;
                try {
                    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                    cout << spasi(47) << BOLD << "Min   : " << RESET; cin >> inputMin;
                    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                    for(char c : inputMin) {
                        if(!isdigit(c)) {
                            throw "Input Minimum harus angka!";}}
                    try {
                        min = stoi(inputMin);}
                    catch (...) {
                        throw "Angka minimum terlalu besar!";}
                    if (min < 0) {
                        throw "Minimum tidak boleh negatif!";}
                    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                    cout << spasi(47) << BOLD << "Max   : " << RESET; cin >> inputMax;
                    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                    for (char c : inputMax) {
                        if (!isdigit(c)) {
                            throw "Maksimum harus berupa angka!";}}
                    try {
                        max = stoi(inputMax);}
                    catch (...) {
                        throw "Angka maksimum terlalu besar!";}
                    if (max < 0) {
                        throw "Maksimum tidak boleh negatif!";}
                    if (min > max) {
                        throw "Minimum tidak boleh lebih besar!";}
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');}
                catch (const char* e) {
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    tampilPeringatan(30, e);
                    system("pause");
                    error = true;}
                if (error) continue;
                linearSearchEbook(ebook, hasil, pilih + 1, "", min, max);}

            cout << endl;
            if (!hasil.empty()) {
                cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                cout << HIJAU << BOLD << "\nDaftar Hasil Pencarian:" << endl;
                lihatDaftarEbook(hasil);}
            else {tampilPeringatan(22, "Data tidak ditemukan!");}
            system("pause");}}}

/*  MENU PEMBELIAN
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatDetailOrder(vector<Order> &order, int indeksOrder, string jenis, string status, string id_user = "") {
    vector<string> field, data;
    if (jenis == "Admin") {
        if (status == "Ditunggu") {
            field = {
                "ID ORDER", "ID USER", "KODE", "JUDUL", "HARGA", "STATUS ORDER", "TANGGAL PESAN", "STATUS BAYAR"};
            data = {
                order[indeksOrder].id_order,
                order[indeksOrder].id_user,
                order[indeksOrder].kode,
                order[indeksOrder].judul,
                to_string(order[indeksOrder].harga),
                order[indeksOrder].status_order,
                to_string(order[indeksOrder].tanggal_pesan),
                order[indeksOrder].status_bayar};}
        else if (status == "Diproses" || status == "Dikirim" || status == "Selesai") {
            field = {
                "ID ORDER", "ID USER", "KODE", "JUDUL", "HARGA", "STATUS ORDER", "TANGGAL PESAN", "STATUS BAYAR", "TANGGAL BAYAR", "TANGGAL KIRIM", "TANGGAL SAMPAI", };
            data = {
                order[indeksOrder].id_order,
                order[indeksOrder].id_user,
                order[indeksOrder].kode,
                order[indeksOrder].judul,
                to_string(order[indeksOrder].harga),
                order[indeksOrder].status_order,
                to_string(order[indeksOrder].tanggal_pesan),
                order[indeksOrder].status_bayar,
                to_string(order[indeksOrder].tanggal_bayar),
                to_string(order[indeksOrder].tanggal_kirim),
                to_string(order[indeksOrder].tanggal_sampai)};}
        else {
            field = {
                "ID ORDER", "ID USER", "KODE", "JUDUL", "HARGA", "STATUS ORDER", "TANGGAL PESAN", "STATUS BAYAR", "TANGGAL BAYAR", "BATAL OLEH", "ALASAN BATAL"};
            data = {
                order[indeksOrder].id_order,
                order[indeksOrder].id_user,
                order[indeksOrder].kode,
                order[indeksOrder].judul,
                to_string(order[indeksOrder].harga),
                order[indeksOrder].status_order,
                to_string(order[indeksOrder].tanggal_pesan),
                order[indeksOrder].status_bayar,
                to_string(order[indeksOrder].tanggal_bayar),
                order[indeksOrder].batal_oleh,
                order[indeksOrder].alasan};}}
    else {
        if (status == "Ditunggu") {
            field = {
                "ID ORDER", "KODE", "JUDUL", "HARGA", "STATUS ORDER", "TANGGAL PESAN", "STATUS BAYAR"};
            data = {
                order[indeksOrder].id_order,
                order[indeksOrder].kode,
                order[indeksOrder].judul,
                to_string(order[indeksOrder].harga),
                order[indeksOrder].status_order,
                to_string(order[indeksOrder].tanggal_pesan),
                order[indeksOrder].status_bayar};}
        else if (status == "Diproses" || status == "Dikirim" || status == "Selesai") {
            field = {
                "ID ORDER", "KODE", "JUDUL", "HARGA", "STATUS ORDER", "TANGGAL PESAN", "STATUS BAYAR", "TANGGAL BAYAR", "TANGGAL KIRIM", "TANGGAL SAMPAI", };
            data = {
                order[indeksOrder].id_order,
                order[indeksOrder].kode,
                order[indeksOrder].judul,
                to_string(order[indeksOrder].harga),
                order[indeksOrder].status_order,
                to_string(order[indeksOrder].tanggal_pesan),
                order[indeksOrder].status_bayar,
                to_string(order[indeksOrder].tanggal_bayar),
                to_string(order[indeksOrder].tanggal_kirim),
                to_string(order[indeksOrder].tanggal_sampai)};}
        else {
            field = {
                "ID ORDER", "KODE", "JUDUL", "HARGA", "STATUS ORDER", "TANGGAL PESAN", "STATUS BAYAR", "TANGGAL BAYAR", "BATAL OLEH", "ALASAN BATAL"};
            data = {
                order[indeksOrder].id_order,
                order[indeksOrder].kode,
                order[indeksOrder].judul,
                to_string(order[indeksOrder].harga),
                order[indeksOrder].status_order,
                to_string(order[indeksOrder].tanggal_pesan),
                order[indeksOrder].status_bayar,
                to_string(order[indeksOrder].tanggal_bayar),
                order[indeksOrder].batal_oleh,
                order[indeksOrder].alasan};}}

    cout << CYAN << BOLD;
    cout << spasi(36) << "┌──────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(36) << "│                           DETAIL ORDER                           │" << endl;
    cout << spasi(36) << "├────────────────┬─────────────────────────────────────────────────┤" << endl;
    cout << spasi(36) << "│ FIELD          │ DATA                                            │" << endl;
    cout << spasi(36) << "├────────────────┼─────────────────────────────────────────────────┤" << endl;
    cout << RESET;
    for (size_t i = 0; i < field.size(); i++) {
        cout << spasi(36);
        if (i % 2 == 0) cout << "\033[48;5;235m";
        cout << "│ " << left << setw(15) << field[i]
            << "│ " << setw(48) << data[i]
            << "│" << RESET << endl;}
    cout << CYAN;
    cout << spasi(36) << "└────────────────┴─────────────────────────────────────────────────┘" << endl;
    cout << RESET << endl;}

void lihatDaftarPembelian(vector<Order> &order) {
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
        return;}
    bool ada = false;
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].status_order == "Selesai") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(26, "Belum ada daftar pembelian!");
        return;}

    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                       DAFTAR PEMBELIAN                                                       │" << endl;
    cout << spasi(6) << "├──────┬──────────────────┬───────────┬─────────────────────────┬────────────┬────────────────────────┬────────────────────────┤" << endl;
    cout << spasi(6) << "│ NO   │ ID ORDER         │ ID USER   │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN          │ TANGGAL TERIMA         │" << endl;
    cout << spasi(6) << "├──────┼──────────────────┼───────────┼─────────────────────────┼────────────┼────────────────────────┼────────────────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].status_order == "Selesai") {
            cout << spasi(6);
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(5) << no++
                << "│ " << setw(17) << order[i].id_order
                << "│ " << setw(10) << order[i].id_user
                << "│ " << setw(24) << order[i].kode
                << "│ " << setw(11) << order[i].harga
                << "│ " << setw(23) << order[i].tanggal_pesan
                << "│ " << setw(23) << order[i].tanggal_sampai;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└──────┴──────────────────┴───────────┴─────────────────────────┴────────────┴────────────────────────┴────────────────────────┘" << endl;
    cout << RESET << endl;}

void cariDaftarPembelian(vector<Order> &order) {
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
        return;}
    bool ada = false;
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].status_order == "Selesai") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(40, "Tidak ada pesanan dengan status tersebut!");
        return;}
    vector<Order> hasil;
    string keyword; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Masukkan ID Order : " << RESET; getline(cin, keyword);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    linearSearchOrder(order, hasil, keyword); cout << endl;

    if (!hasil.empty()) {
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << HIJAU << BOLD << "\nDaftar Hasil Pencarian:" << endl;
        lihatDaftarPembelian(hasil);}
    else {tampilPeringatan(22, "Data tidak ditemukan!");}
}

/*  MENU PEMESANAN
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatPesanan(string jenis, vector<Order> &order) {
    if(order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
        return;}
    bool ada = false;
    for (size_t i = 0; i < order.size(); i++) {
        if (jenis == "Belum Bayar") {
            if (order[i].status_bayar == jenis && order[i].status_order == "Ditunggu") {
                ada = true;
                break;}}
        else {
            if (order[i].status_order == "Diproses") {
                ada = true;
                break;}}}
    if (!ada) {
        tampilPeringatan(40, "Tidak ada pesanan dengan status tersebut!");
        return;}
    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                        DAFTAR PESANAN                                                        │" << endl;
    cout << spasi(6) << "├──────┬───────────────────┬─────────────┬───────────────────────────┬────────────┬────────────────────────┬───────────────────┤" << endl;
    cout << spasi(6) << "│ NO   │ ID ORDER          │ ID USER     │ KODE E-BOOK               │ HARGA      │ TANGGAL PESAN          │ STATUS            │" << endl;
    cout << spasi(6) << "├──────┼───────────────────┼─────────────┼───────────────────────────┼────────────┼────────────────────────┼───────────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (size_t i = 0; i < order.size(); i++) {
        bool tampil = false;
        if (jenis == "Belum Bayar") {
            tampil = (order[i].status_bayar == "Belum Bayar" && order[i].status_order == "Ditunggu");}
        else if (jenis == "Lunas") {
            tampil = (order[i].status_order == "Diproses");}
        if (tampil) {
            cout << spasi(6);
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(5) << no++
                << "│ " << setw(18) << order[i].id_order
                << "│ " << setw(12) << order[i].id_user
                << "│ " << setw(26) << order[i].kode
                << "│ " << setw(11) << order[i].harga
                << "│ " << setw(23) << order[i].tanggal_pesan << "│ ";
            if (order[i].status_bayar == "Belum Bayar")
                cout << MERAH << BOLD << setw(18) << order[i].status_bayar << RESET;
            else
                cout << HIJAU << BOLD << setw(18) << order[i].status_bayar << RESET;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└──────┴───────────────────┴─────────────┴───────────────────────────┴────────────┴────────────────────────┴───────────────────┘" << endl;
    cout << RESET << endl;}

void lihatRiwayatPesanan(vector<Order> &order) {
    if(order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
        return;}
    bool ada = false;
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].status_order == "Dikirim" || order[i].status_order == "Dibatalkan") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(40, "Tidak ada pesanan dengan status tersebut!");
        return;}
    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                        DAFTAR PESANAN                                                        │" << endl;
    cout << spasi(6) << "├──────┬───────────────────┬─────────────┬───────────────────────────┬────────────┬────────────────────┬───────────────────────┤" << endl;
    cout << spasi(6) << "│ NO   │ ID ORDER          │ ID USER     │ KODE E-BOOK               │ HARGA      │ TANGGAL PESAN      │ STATUS                │" << endl;
    cout << spasi(6) << "├──────┼───────────────────┼─────────────┼───────────────────────────┼────────────┼────────────────────┼───────────────────────┤" << endl;
    cout << RESET;

    int no = 1;
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].status_order == "Dikirim" || order[i].status_order == "Dibatalkan") {
            cout << spasi(6);
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(5) << no++
                << "│ " << setw(18) << order[i].id_order
                << "│ " << setw(12) << order[i].id_user
                << "│ " << setw(26) << order[i].kode
                << "│ " << setw(11) << order[i].harga
                << "│ " << setw(19) << order[i].tanggal_pesan << "│ ";
            if (order[i].status_order == "Dikirim")
                cout << BIRU << BOLD << setw(22) << order[i].status_order << RESET;
            else
                cout << MERAH << BOLD << setw(12) << order[i].status_order << " (" << setw(6) << order[i].batal_oleh << ") " << RESET;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└──────┴───────────────────┴─────────────┴───────────────────────────┴────────────┴────────────────────┴───────────────────────┘" << endl;
    cout << RESET << endl;}

void editStatusPesanan(vector<Order> &order) {
    string tindakan[] = {
        "【 1 | Kirim         】",
        "【 2 | Cancel        】",
        "【 3 | Batalkan      】"};
    int pilih = 0;
    bool refresh = false;

    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
        system("pause"); return;}
    bool ada = false;
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].status_order == "Diproses") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(40, "Tidak ada pesanan dengan status tersebut!");
        system("pause"); return;}

    int pilihan = scrollOrder(order, "UBAH STATUS PESANAN", "Diproses");

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("UBAH STATUS PESANAN"); cout << endl;
        lihatDetailOrder(order, pilihan, "Admin", "Diproses");
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Ubah status pesanan?" << RESET; cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;

            // KIRIM
            if (pilih == 0) {
                order[pilihan].status_order = "Dikirim";
                saveOrder(order);
                tampilPesan(26, "Pesanan berhasil dikirim!");
                system("pause");
                break;}

            // CANCEL
            else if (pilih == 1) {
                order[pilihan].status_order = "Dibatalkan";
                order[pilihan].status_bayar = "Dana Dikembalikan";
                order[pilihan].batal_oleh = "Admin";
                cout << endl;
                cin.ignore(1000, '\n');
                cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                cout << spasi(47) << BOLD << "Alasan : " << RESET; getline(cin, order[pilihan].alasan);
                cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                saveOrder(order);
                tampilPesan(22, "Dana 100\% dikembalikan");
                tampilPesan(28, "Pesanan berhasil dibatalkan!");
                system("pause");
                break;}

            else {
                tampilPeringatan(36, "Perubahan status pesanan dibatalkan!");
                break;}}}}

void RiwayatPesanan(vector<Order> &order) {
    string pilihMenuAdmin[] = {
        "『  📋 Lihat Detail Riwayat Pesanan 』",
        "『 ↩   Kembali                      』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("RIWAYAT PESANAN"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << spasi(34)  << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << spasi(34)  << *(pilihMenuAdmin + i) << RESET << endl;}
        cout << endl; lihatRiwayatPesanan(order);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;
    
            /* a. LIHAT DETAIL RIWAYAT PESANAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("LIHAT DETAIL RIWAYAT PESANAN"); cout << endl;
                if (order.empty()) {
                    tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
                    system("pause"); continue;}
                bool ada = false;
                for (size_t i = 0; i < order.size(); i++) {
                    if (order[i].status_order == "Dikirim" || order[i].status_order == "Dibatalkan" ) {
                        ada = true;
                        break;}}
                if (!ada) {
                    tampilPeringatan(40, "Tidak ada pesanan dengan status tersebut!");
                    system("pause"); continue;}

                int pilihan = scrollOrder(order, "LIHAT DETAIL RIWAYAT PESANAN", "Dikirim_Dibatalkan");
                system("cls"); judul_subjudul("LIHAT DETAIL RIWAYAT PESANAN");
                cout << endl;
                lihatDetailOrder(order, pilihan, "Admin", order[pilihan].status_order);
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

/*  MENU-MENU UTAMA ADMIN
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatRiwayatTransaksi(vector<Transaksi> &transaksi, string jenis, string id_user = "") {
    bool ada = false;
    for (size_t i = 0; i < transaksi.size(); i++) {
        if (jenis == "Admin" || transaksi[i].id_user == id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(32, "Belum ada transaksi yang dibuat!");
        return;}
    
    if (jenis == "Admin") {
        cout << CYAN << BOLD;
        cout << spasi(28) << "┌──────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << spasi(28) << "│                                RIWAYAT TRANSAKSI                                 │" << endl;
        cout << spasi(28) << "├──────┬──────────────────┬───────────┬──────────────────┬────────────┬────────────┤" << endl;
        cout << spasi(28) << "│ NO   │ ID TRANSAKSI     │ ID USER   │ ID ORDER         │ NOMINAL    │ TANGGAL    │" << endl;
        cout << spasi(28) << "├──────┼──────────────────┼───────────┼──────────────────┼────────────┼────────────┤" << endl;
        cout  << RESET;
        int no = 1;
        for (auto &t : transaksi) {
            cout << spasi(28); 
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(5)  << no++
                << "│ " << setw(17) << t.id_transaksi
                << "│ " << setw(10) << t.id_user
                << "│ " << setw(17) << t.id_order
                << "│ Rp" << setw(9) << t.nominal
                << "│ " << setw(11) << t.tanggal_transaksi
                << "│" << RESET << endl;}
        cout << CYAN;
        cout << spasi(28) << "└──────┴──────────────────┴───────────┴──────────────────┴────────────┴────────────┘" << endl;
        cout << RESET << endl;}

    else {
        cout << CYAN << BOLD;
        cout << spasi(34) << "┌──────────────────────────────────────────────────────────────────────┐" << endl;
        cout << spasi(34) << "│                          RIWAYAT TRANSAKSI                           │" << endl;
        cout << spasi(34) << "├──────┬──────────────────┬──────────────────┬────────────┬────────────┤" << endl;
        cout << spasi(34) << "│ NO   │ ID TRANSAKSI     │ ID ORDER         │ NOMINAL    │ TANGGAL    │" << endl;
        cout << spasi(34) << "├──────┼──────────────────┼──────────────────┼────────────┼────────────┤" << endl;
        cout  << RESET;
        int no = 1;
        for (auto &t : transaksi) {
            if (jenis != "Admin" && t.id_user != id_user)
                continue;
            cout << spasi(34);
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(5)  << no++
                << "│ " << setw(17) << t.id_transaksi
                << "│ " << setw(17) << t.id_order
                << "│ Rp" << setw(9) << t.nominal
                << "│ " << setw(11) << t.tanggal_transaksi
                << "│" << RESET << endl;}
        cout << CYAN;
        cout << spasi(34) << "└──────┴──────────────────┴──────────────────┴────────────┴────────────┘" << endl;
        cout << RESET << endl;}
    }

void kelolaAkunPelanggan(vector<Akun> &akun) {
    string pilihMenuAdmin[] = {
        "『  ✏️  Ubah Status Akun Pelanggan 』",
        "『 ↩   Kembali                    』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU KELOLA AKUN PELANGGAN"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuAdmin + i) << RESET << endl;}
        cout << endl; lihatDaftarPelanggan(akun);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;
    
            /* a. EDIT STATUS AKUN PELANGGAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                editStatusPelanggan(akun);}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void penjualanAdmin(vector<Ebook> &ebook) {
    string pilihMenuAdmin[] = {
        "『  ➕ E-Book Baru                』",
        "『  ✏️  Edit Detail E-Book         』",
        "『  🗑️  Hapus E-Book               』",
        "『  ↕️  Urutkan Katalog            』",
        "『  🔍 Cari E-Book                』",
        "『 ↩   Kembali                    』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU PENJUALAN"); cout << endl;
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuAdmin + i) << RESET << endl;}
        cout << endl; lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
            refresh = true;
    
            /* a. TAMBAH E-BOOK
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                tambahEbook(ebook); saveEbook(ebook);
                system("pause");}

            /* b. EDIT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                editEbook(ebook);
                system("pause");}

            /* c. HAPUS E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                hapusEbook(ebook);
                system("pause");}

            /* d. URUT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                urutEbook(ebook);}

            /* e. CARI E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                cariEbook(ebook);}

            /* f. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pembelianAdmin(vector<Order> &order) {
    string pilihMenuAdmin[] = {
        "『  🔍 Cari Riwayat Pembelian      』",
        "『  📋 Lihat Detail Data Pembelian 』",
        "『 ↩   Kembali                     』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU PEMBELIAN"); cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuAdmin + i) << RESET << endl;}
        cout << endl; lihatDaftarPembelian(order);
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;
    
            /* a. CARI RIWAYAT PEMBELIAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Cari Riwayat Pembelian"); cout << endl;
                cariDaftarPembelian(order);
                system("pause");}

            /* b. LIHAT DETAIL DATA PEMBELIAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("LIHAT DETAIL DATA PEMBELIAN"); cout << endl;
                if (order.empty()) {
                    tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
                    system("pause"); continue;}
                bool ada = false;
                for (size_t i = 0; i < order.size(); i++) {
                    if (order[i].status_order == "Selesai") {
                        ada = true;
                        break;}}
                if (!ada) {
                    tampilPeringatan(40, "Tidak ada pesanan dengan status tersebut!");
                    system("pause"); continue;}

                int pilihan = scrollOrder(order, "LIHAT DETAIL DATA PEMBELIAN", "Selesai");
                system("cls"); judul_subjudul("LIHAT DETAIL DATA PEMBELIAN");
                cout << endl;
                lihatDetailOrder(order, pilihan, "Admin", "Selesai");
                system("pause");}

            /* c. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pemesananAdmin(vector<Order> &order){
    string pilihMenuAdmin[] = {
        "『  📋 Daftar Pesanan Belum Dibayar 』",
        "『  📋 Daftar Pesanan Sudah Dibayar 』",
        "『  ✏️  Ubah Status Pesanan          』",
        "『  📑 Riwayat Pesanan Lainnya      』",
        "『 ↩   Kembali                      』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU PEMESANAN"); cout << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuAdmin + i) << RESET << endl;}
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
            refresh = true;
    
            /* a. DAFTAR PESANAN BELUM DIBAYAR
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("DAFTAR PESANAN BELUM DIBAYAR"); cout << endl;
                lihatPesanan("Belum Bayar", order);
                system("pause");}

            /* b. DAFTAR PESANAN SUDAH DIBAYAR
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("DAFTAR PESANAN SUDAH DIBAYAR"); cout << endl;
                lihatPesanan("Lunas", order);
                system("pause");}

            /* c. UBAH STATUS PESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("UBAH STATUS PESANAN"); cout << endl;
                editStatusPesanan(order);}

            /* d. RIWAYAT PESANAN LAINNYA
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("RIWAYAT PESANAN LAINNYA"); cout << endl;
                RiwayatPesanan(order);}

            /* e. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}


void menuAdmin(vector<Akun> &akun, int indeksLogin, vector<Ebook> &ebook, vector<Order> &order, vector<Transaksi> &transaksi) {
    string pilihMenuAdmin[] = {
        "『     Kelola Akun Pelanggan      』", 
        "『           Penjualan            』",
        "『           Pembelian            』",
        "『           Pemesanan            』",
        "『       Riwayat Transaksi        』",
        "『             Logout             』"}; 
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("HALO, ADMIN " + akun[indeksLogin].username);
        cout << HIJAU << BOLD << spasi(56) << "┌──────────────────────────┐" << RESET << endl;
        cout << spasi(58) << HIJAU << BOLD << BG_HIJAU << "  Saldo: " << akun[indeksLogin].saldo << " " << RESET << endl;
        cout << HIJAU << BOLD << spasi(56) << "└──────────────────────────┘" << RESET << endl;
        cout << endl;
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << spasi(52) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << spasi(52) << *(pilihMenuAdmin + i) << RESET << endl;}
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
            refresh = true;
    
            /* 1. MENU ADMIN KELOLA AKUN PELANGGAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                kelolaAkunPelanggan(akun);}

            /* 2. MENU ADMIN PENJUALAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                penjualanAdmin(ebook);}

            /* 3. MENU ADMIN PEMBELIAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                pembelianAdmin(order);}

            /* 4. MENU ADMIN PEMESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                pemesananAdmin(order);}

            /* 4. MENU ADMIN RIWAYAT TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("MENU RIWAYAT TRANSAKSI"); cout << "" << endl;
                lihatRiwayatTransaksi(transaksi, "Admin");
                system("pause");}

            /* 5. MENU ADMIN LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(16, "Logout berhasil!");
                system("pause");
                break;}}}}



/*═════════════════════════════════════════════════════════════════════════════════════════════════════════════
                FUNGSI MENU USER
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/

/*  MENU KELOLA AKUN DIRI
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void editDataDiri(vector<Akun> &akun, int indeksLogin) {
    string inputNoHp, inputAlamat, inputPassword;
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};

    system("cls"); judul_subjudul("UBAH DATA AKUN DIRI"); cout << endl;
    lihatDetailAkun(akun, indeksLogin); cout << endl;
    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
    cout << KUNING << spasi(30) << "☞    Ketik '0' jika tidak ingin merubah salah satu field data" << RESET << endl;

    Akun temp = akun[indeksLogin];
    cout << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "No. HP Baru   : " << RESET; cin >> inputNoHp;
    if (inputNoHp == "0") {inputNoHp = "";}
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cin.ignore(1000, '\n');
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Alamat Baru   : " << RESET; getline(cin, inputAlamat);
    if (inputAlamat == "0") {inputAlamat = "";}
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Password Baru : " << RESET; cin >> inputPassword;
    if (inputPassword == "0") inputPassword = "";
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    
    if (inputNoHp.empty() && inputAlamat.empty() && inputPassword.empty()) {
        tampilPeringatan(26, "Tidak ada data yang diubah.");
        system("pause"); return;}
    regex passRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$");
    regex hpRegex("^08\\d{8,12}$");
    if (!inputNoHp.empty()) {
        if (!regex_match(inputNoHp, hpRegex)) {
            tampilPeringatan(18, "No HP tidak valid!"); system("pause"); return;}
        temp.no_hp = inputNoHp;}
    if (!inputAlamat.empty()) {
        temp.alamat = inputAlamat;}
    if (!inputPassword.empty()) {
        if (!regex_match(inputPassword, passRegex)) {
            tampilPeringatan(54, "Password harus 8 karakter + huruf besar, kecil, angka!"); system("pause"); return;}
        temp.password = inputPassword;}

    int pilihTindakan = 0;
    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("UBAH DATA AKUN DIRI"); cout << endl;

        lihatDetailAkun(akun, indeksLogin); cout << endl;
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << spasi(34) << BOLD << KUNING << "Data perubahan:" << RESET; cout << endl;
        cout << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Username : " << RESET << temp.username << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Password : " << RESET << temp.password << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Email    : " << RESET << temp.email << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "No. HP   : " << RESET << temp.no_hp << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Alamat   : " << RESET << temp.alamat << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << endl;
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Simpan perubahan?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // SIMPAN
            if (pilihTindakan == 0) {
                akun[indeksLogin] = temp;
                saveAkun(akun);
                tampilPesan(30, "Data Diri berhasil diperbarui!");
                system("pause");
                break;}

            else {
                tampilPeringatan(22, "Perubahan dibatalkan!");
                system("pause");
                break;}}}
    return;}

/*  MENU BELANJA
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void tambahProdukkeKeranjang(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Order> &order, string id_user) {
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};
 
    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi!");
        system("pause");
        return;}
 
    int pilihan = scrollBuku(ebook, "TAMBAH KE KERANJANG");
 
    /* FIX 5: cek apakah sudah ada di keranjang */
    for (size_t i = 0; i < keranjang.size(); i++) {
        if (keranjang[i].id_user == id_user && keranjang[i].buku.kode == ebook[pilihan].kode) {
            tampilPeringatan(30, "E-Book sudah ada di keranjang!"); system("pause");
            return;}}
 
    /* FIX 5: cek apakah sudah dipesan dan statusnya bukan Dibatalkan */
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].id_user == id_user && order[i].kode == ebook[pilihan].kode &&
            order[i].status_order != "Dibatalkan") {
            tampilPeringatan(44, "Anda sudah memiliki pesanan aktif untuk E-Book ini!");
            system("pause"); return;}}
 
    int pilihTindakan = 0;
    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("TAMBAH E-BOOK"); cout << endl;
        lihatDetailEbook(ebook, pilihan); cout << endl;
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Tambah E-Book ke keranjang?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;
            if (pilihTindakan == 0) {
                Keranjang baru;
                baru.id_user = id_user;
                baru.buku = ebook[pilihan];
                keranjang.push_back(baru);
                saveKeranjang(keranjang);
                tampilPesan(24, "Berhasil masuk keranjang!");
                system("pause");
                break;}
            else {
                tampilPeringatan(22, "Penambahan dibatalkan!"); system("pause");
                break;}}}}
    
void checkoutDariKatalog(vector<Ebook> &ebook, vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi, vector<Keranjang> &keranjang) {
    string tindakan[] = {
        "【 1 | Bayar Sekarang     】",
        "【 2 | Bayar Nanti        】",
        "【 3 | Batal              】"};
    int pilihTindakan = 0;
    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi.");
        return;}
    
    int pilihan = scrollBuku(ebook, "CHECKOUT DARI KATALOG");

    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].id_user == akun[indeksLogin].id_user && order[i].kode == ebook[pilihan].kode &&
            order[i].status_order != "Dibatalkan") {
            tampilPeringatan(44, "Anda sudah memiliki pesanan aktif untuk E-Book ini!");
            system("pause"); return;}}

    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("CHECKOUT DARI KATALOG"); cout << endl;
        lihatDetailEbook(ebook, pilihan);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Checkout E-Book ini?" << RESET; cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 3);
        if (hasil == -1) {
            refreshTindakan = true;

            if (pilihTindakan == 2) {
                tampilPeringatan(40, "Pemesanan dibatalkan.");
                return;}

            else {
                time_t now = time(0); 
                tm *ltm = localtime(&now);
                int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;

                Order Baru;
                Baru.id_order       = "ORD" + to_string(order.size() + 1);
                Baru.id_user        = akun[indeksLogin].id_user;
                Baru.kode           = ebook[pilihan].kode;
                Baru.judul          = ebook[pilihan].judul;
                Baru.harga          = ebook[pilihan].harga;
                Baru.tanggal_pesan  = tgl;
                Baru.tanggal_kirim  = 0;
                Baru.tanggal_sampai = 0;
                Baru.batal_oleh     = "";
                Baru.alasan         = "";

                // BAYAR SEKARANG
                if (pilihTindakan == 0) {
                    if (akun[indeksLogin].saldo < ebook[pilihan].harga) {
                        tampilPeringatan(52, "Saldo tidak mencukupi! Bayar nanti atau top up saldo.");
                        system("pause");
                        continue;}

                    akun[indeksLogin].saldo -= ebook[pilihan].harga;
                    for (size_t i = 0; i < akun.size(); i++) {
                        if (akun[i].role == "Admin") {
                            akun[i].saldo += ebook[pilihan].harga;
                            break;}}

                    Baru.status_order = "Diproses";
                    Baru.status_bayar = "Lunas";
                    Baru.tanggal_bayar = tgl;
                    order.push_back(Baru);

                    for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                        if (it->id_user == akun[indeksLogin].id_user && it->buku.kode == ebook[pilihan].kode) {
                            it = keranjang.erase(it);
                        } else { ++it;}}

                    saveAkun(akun);
                    saveOrder(order);
                    saveKeranjang(keranjang);

                    Transaksi t;
                    t.id_transaksi = "TRX" + to_string(transaksi.size() + 1);
                    t.id_user = akun[indeksLogin].id_user;
                    t.id_order = Baru.id_order;
                    t.nominal = Baru.harga;
                    t.tanggal_transaksi = tgl;
                    transaksi.push_back(t);
                    saveTransaksi(transaksi);

                    tampilPesan(50, "Pembayaran berhasil! Pesanan sedang diproses admin.");
                    break;}
                
                // BAYAR NANTI
                else if (pilihTindakan == 1) {
                    Baru.status_order = "Ditunggu";
                    Baru.status_bayar = "Belum Bayar";
                    Baru.tanggal_bayar = 0;
                    order.push_back(Baru);

                    for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                        if (it->id_user == akun[indeksLogin].id_user && it->buku.kode == ebook[pilihan].kode) {
                            it = keranjang.erase(it);
                        } else { ++it;}}

                    saveOrder(order);
                    saveKeranjang(keranjang);
                    tampilPesan(52, "Pesanan disimpan! Bayar melalui menu Daftar Pesanan.");
                    break;}}}}}

/*  MENU KERANJANG
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatPesananUser(string jenis, vector<Order> &order, string id_user) {
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
        return;}
    bool ada = false;
    for (size_t i = 0; i < order.size(); i++) {
        if (jenis == "Belum Bayar") {
            if (order[i].id_user == id_user && order[i].status_bayar == jenis && order[i].status_order == "Ditunggu") {
                ada = true;
                break;}}
        else if (jenis == "Diproses") {
            if (order[i].id_user == id_user && order[i].status_order == "Diproses") {
                ada = true;
                break;}}
        else if (jenis == "Dikirim") {
            if (order[i].id_user == id_user && order[i].status_order == "Dikirim") {
                ada = true;
                break;}}
        else if (jenis == "Selesai") {
            if (order[i].id_user == id_user && order[i].status_order == "Selesai") {
                ada = true;
                break;}}
        else {     
            if (order[i].id_user == id_user && order[i].status_order == "Dibatalkan") {
                ada = true;
                break;}}}
    if (!ada) {
        tampilPeringatan(34, "Belum ada daftar pesanan tersebut!");
        return;}

    if (jenis == "Belum Bayar" || jenis == "Diproses" || jenis == "Dibatalkan") {
        cout << CYAN << BOLD;
        cout << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << "│                                                              DAFTAR PESANAN                                                              │" << endl;
        cout << "├──────┬─────────────────┬─────────────────────────────┬─────────────────────────┬────────────┬────────────────────┬───────────────────────┤" << endl;
        cout << "│ NO   │ ID ORDER        │ JUDUL                       │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN      │ STATUS                │" << endl;
        cout << "├──────┼─────────────────┼─────────────────────────────┼─────────────────────────┼────────────┼────────────────────┼───────────────────────┤" << endl;
        cout << RESET;
        int no = 1;
        for (size_t i = 0; i < order.size(); i++) {
            bool tampil = false;
            if (jenis == "Belum Bayar") {
                tampil = (order[i].id_user == id_user && order[i].status_bayar == "Belum Bayar" && order[i].status_order == "Ditunggu");}
            else if (jenis == "Diproses") {
                tampil = (order[i].id_user == id_user && order[i].status_order == "Diproses");}
            else if (jenis == "Dikirim") {
                tampil = (order[i].id_user == id_user && order[i].status_order == "Dikirim");}
            else {
                tampil = (order[i].id_user == id_user && order[i].status_order == "Dibatalkan");}
            if (tampil) {
                if (no % 2 == 0) cout << "\033[48;5;235m";
                cout << "│ " << left << setw(5) << no++
                    << "│ " << setw(16) << order[i].id_order
                    << "│ " << setw(28) << order[i].judul
                    << "│ " << setw(24) << order[i].kode
                    << "│ " << setw(11) << order[i].harga
                    << "│ " << setw(19) << order[i].tanggal_pesan << "│ ";
                if (order[i].status_bayar == "Belum Bayar" && order[i].status_order == "Ditunggu")
                    cout << MERAH << BOLD << setw(22) << order[i].status_bayar << RESET;
                else if (order[i].status_bayar == "Lunas" && order[i].status_order == "Diproses")
                    cout << HIJAU << BOLD << setw(22) << order[i].status_bayar << RESET;
                else if (order[i].id_user == id_user && order[i].status_order == "Dikirim")
                    cout << BIRU << BOLD << setw(22) << order[i].status_order << RESET;
                else
                    cout << MERAH << BOLD << setw(12) << order[i].status_order << " (" << setw(6) << order[i].batal_oleh << ") " << RESET;
                cout << "│" << RESET << endl;}}
        cout << CYAN;
        cout << "└──────┴─────────────────┴─────────────────────────────┴─────────────────────────┴────────────┴────────────────────┴───────────────────────┘" << endl;
        cout << RESET << endl;}

    else if (jenis == "Dikirim") {
        cout << CYAN << BOLD;
        cout << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << "│                                                              DAFTAR PESANAN                                                              │" << endl;
        cout << "├──────┬─────────────────┬─────────────────────────────┬─────────────────────────┬────────────┬────────────────────┬───────────────────────┤" << endl;
        cout << "│ NO   │ ID ORDER        │ JUDUL                       │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN      │ TANGGAL KIRIM         │" << endl;
        cout << "├──────┼─────────────────┼─────────────────────────────┼─────────────────────────┼────────────┼────────────────────┼───────────────────────┤" << endl;
        cout << RESET;
        int no = 1;
        for (size_t i = 0; i < order.size(); i++) {
            if (order[i].id_user == id_user && order[i].status_order == "Dikirim") {
                if (no % 2 == 0) cout << "\033[48;5;235m";
                cout << "│ " << left << setw(5) << no++
                    << "│ " << setw(16) << order[i].id_order
                    << "│ " << setw(28) << order[i].judul
                    << "│ " << setw(24) << order[i].kode
                    << "│ " << setw(11) << order[i].harga
                    << "│ " << setw(19) << order[i].tanggal_pesan
                    << "│ " << setw(22) << order[i].tanggal_kirim;
                cout << "│" << RESET << endl;}}
        cout << CYAN;
        cout << "└──────┴─────────────────┴─────────────────────────────┴─────────────────────────┴────────────┴────────────────────┴───────────────────────┘" << endl;
        cout << RESET << endl;}

    else {
        cout << CYAN << BOLD;
        cout << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << "│                                                              DAFTAR PESANAN                                                              │" << endl;
        cout << "├──────┬─────────────────┬─────────────────────────────┬─────────────────────────┬────────────┬────────────────────┬───────────────────────┤" << endl;
        cout << "│ NO   │ ID ORDER        │ JUDUL                       │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN      │ TANGGAL TERIMA        │" << endl;
        cout << "├──────┼─────────────────┼─────────────────────────────┼─────────────────────────┼────────────┼────────────────────┼───────────────────────┤" << endl;
        cout << RESET;
        int no = 1;
        for (size_t i = 0; i < order.size(); i++) {
            if (order[i].id_user == id_user && order[i].status_order == "Selesai") {
                if (no % 2 == 0) cout << "\033[48;5;235m";
                cout << "│ " << left << setw(5) << no++
                    << "│ " << setw(16) << order[i].id_order
                    << "│ " << setw(28) << order[i].judul
                    << "│ " << setw(24) << order[i].kode
                    << "│ " << setw(11) << order[i].harga
                    << "│ " << setw(19) << order[i].tanggal_pesan
                    << "│ " << setw(22) << order[i].tanggal_sampai;
                cout << "│" << RESET << endl;}}
        cout << CYAN;
        cout << "└──────┴─────────────────┴─────────────────────────────┴─────────────────────────┴────────────┴────────────────────┴───────────────────────┘" << endl;
        cout << RESET << endl;}}

void lihatDaftarKeranjang(vector<Keranjang> &keranjang, string id_user) {
    cout << CYAN << BOLD;
    cout << spasi(21) << "┌────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(21) << "│                                        KERANJANG BELANJA                                       │" << endl;
    cout << spasi(21) << "├──────┬───────────────────────────┬───────────────────────────────────────────┬─────────────────┤" << endl;
    cout << spasi(21) << "│ NO   │ KODE E-BOOK               │ JUDUL                                     │ HARGA           │" << endl;
    cout << spasi(21) << "├──────┼───────────────────────────┼───────────────────────────────────────────┼─────────────────┤" << endl;
    cout << RESET;
    int no = 1, total = 0;
    for (auto &k : keranjang) {
        if (k.id_user == id_user) {
            cout << spasi(21);
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(5)  << no++
                << "│ " << setw(26) << k.buku.kode
                << "│ " << setw(42) << k.buku.judul
                << "│ Rp" << setw(14) << k.buku.harga 
                << "│" << RESET << endl;
            total += k.buku.harga;}}
    cout << CYAN << BOLD;
    cout << spasi(21) << "├──────┴───────────────────────────┴───────────────────────────────────────────┼─────────────────┤" << endl;
    string strTotal = "Rp" + to_string(total);
    cout << spasi(21) << "│" << right << setw(82) << "TOTAL HARGA │ " << left << setw(16) << strTotal << "│" << endl;
    cout << spasi(21) << "└──────────────────────────────────────────────────────────────────────────────┴─────────────────┘" << endl;
    cout << RESET << endl;}

void hapusEbookDariKeranjang(vector<Ebook> &ebook, vector<Keranjang> &keranjang, string id_user) {
    string tindakan[] = {
        "【 1 | Hapus         】",
        "【 2 | Batalkan      】"};
    int pilihTindakan = 0;

    if (keranjang.empty()) {
        tampilPeringatan(28, "Keranjang belum terisi.");
        return;}
    bool ada = false;
    for (size_t i = 0; i < keranjang.size(); i++) {
        if (keranjang[i].id_user == id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(22, "Keranjang anda kosong!");
        return;}

    int pilihan = scrollKeranjang(keranjang, "HAPUS E-BOOK DARI KERANJANG", id_user);

    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("HAPUS E-BOOK DARI KERANJANG"); cout << endl;
        lihatDetailEbook(ebook, pilihan);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Hapus E-Book ini dari keranjang?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // HAPUS
            if (pilihTindakan == 0) {
                keranjang.erase(keranjang.begin() + pilihan);
                tampilPesan(38, "E-Book berhasil dihapus dari keranjang!");
                break;}

            else {
                tampilPeringatan(24, "Penghapusan dibatalkan!");
                break;}}}
    return;}

void checkoutDariKeranjang(vector<Keranjang> &keranjang, vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    bool ada = false;
    for (const auto& k : keranjang) {
        if (k.id_user == akun[indeksLogin].id_user) { ada = true; break;}}
    if (!ada) {
        tampilPeringatan(40, "Keranjang Anda kosong!");
        system("pause");
        return;}

    int pilihMenu = 0;
    bool refreshMenu = true;

    while (true) {
        if (refreshMenu) { system("cls"); refreshMenu = false;}
        clsScroll(0,0); judul_subjudul("KERANJANG BELANJA"); cout << endl;
        lihatDaftarKeranjang(keranjang, akun[indeksLogin].id_user);

        string opsiMenu[] = {
            "『   Checkout Barang       』",
            "『   Hapus dari Keranjang  』",
            "『   Kembali               』"};

        cout << "\n  Opsi Keranjang:\n\n";
        for (int i = 0; i < 3; i++) {
            if (i == pilihMenu) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << opsiMenu[i] << RESET << endl;
            else cout << DIM << spasi(20) << opsiMenu[i] << RESET << endl;}

        int hasilMenu = scrollMenu(pilihMenu, 3);
        if (hasilMenu == -1) {
            refreshMenu = true;

            if (pilihMenu == 2) {
                break;}

            else if (pilihMenu == 0) {
                string opsiJumlah[] = {
                    "『   Checkout Semua        』",
                    "『   Pilih Satu E-Book     』",
                    "『   Batal                 』"};
                int pilihJumlah = 0;
                bool refreshJumlah = true;
                while (true) {
                    if (refreshJumlah) { system("cls"); refreshJumlah = false;}
                    clsScroll(0,0); judul_subjudul("CHECKOUT KERANJANG"); cout << endl;
                    lihatDaftarKeranjang(keranjang, akun[indeksLogin].id_user);
                    cout << endl << spasi(34) << BOLD << KUNING << "Checkout semua atau pilih satu?" << RESET << endl;
                    for (int i = 0; i < 3; i++) {
                        if (i == pilihJumlah) cout << spasi(39) << BG_PUTIH << HITAM << BOLD << opsiJumlah[i] << RESET << endl;
                        else cout << DIM << spasi(39) << opsiJumlah[i] << RESET << endl;}
                    int hasilJumlah = scrollMenu(pilihJumlah, 3);
                    if (hasilJumlah != -1) continue;
                    if (pilihJumlah == 2) break;

                    vector<Keranjang> itemDipesan;
                    if (pilihJumlah == 0) {
                        for (const auto& k : keranjang) {
                            if (k.id_user == akun[indeksLogin].id_user) itemDipesan.push_back(k);}
                    } else {
                        int pilihanIdx = scrollKeranjang(keranjang, "PILIH E-BOOK", akun[indeksLogin].id_user);
                        itemDipesan.push_back(keranjang[pilihanIdx]);}

                    string opsiTindakan[] = {
                        "【 1 | Bayar Sekarang     】",
                        "【 2 | Bayar Nanti        】",
                        "【 3 | Batal              】"};
                    int pilihTindakan = 0;
                    bool refreshTindakan = true;
                    while (true) {
                        if (refreshTindakan) { system("cls"); refreshTindakan = false;}
                        clsScroll(0,0); judul_subjudul("CHECKOUT KERANJANG"); cout << endl;
                        lihatDaftarKeranjang(keranjang, akun[indeksLogin].id_user);
                        cout << endl << spasi(34) << BOLD << KUNING << "Pilih metode pembayaran:" << RESET << endl;
                        for (int i = 0; i < 3; i++) {
                            if (i == pilihTindakan) cout << spasi(39) << BG_PUTIH << HITAM << BOLD << opsiTindakan[i] << RESET << endl;
                            else cout << DIM << spasi(39) << opsiTindakan[i] << RESET << endl;}
                        int hasilTindakan = scrollMenu(pilihTindakan, 3);
                        if (hasilTindakan != -1) continue;
                        if (pilihTindakan == 2) { tampilPeringatan(40, "Checkout dibatalkan."); break;}

                        time_t now = time(0);
                        tm *ltm = localtime(&now);
                        int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;

                        for (auto &item : itemDipesan) {
                            bool sudahDipesan = false;
                            for (size_t i = 0; i < order.size(); i++) {
                                if (order[i].id_user == akun[indeksLogin].id_user &&
                                    order[i].kode == item.buku.kode &&
                                    order[i].status_order != "Dibatalkan") {
                                    sudahDipesan = true; break;}}
                            if (sudahDipesan) continue;

                            Order o;
                            o.id_order       = "ORD" + to_string(order.size() + 1);
                            o.id_user        = akun[indeksLogin].id_user;
                            o.kode           = item.buku.kode;
                            o.judul          = item.buku.judul;
                            o.harga          = item.buku.harga;
                            o.tanggal_pesan  = tgl;
                            o.tanggal_kirim  = 0;
                            o.tanggal_sampai = 0;
                            o.batal_oleh     = "";
                            o.alasan         = "";

                            if (pilihTindakan == 0) {
                                if (akun[indeksLogin].saldo < item.buku.harga) {
                                    tampilPeringatan(52, "Saldo tidak mencukupi untuk item ini, dilewati.");
                                    continue;}
                                o.status_order  = "Diproses";
                                o.status_bayar  = "Lunas";
                                o.tanggal_bayar = tgl;

                                akun[indeksLogin].saldo -= item.buku.harga;
                                for (size_t i = 0; i < akun.size(); i++) {
                                    if (akun[i].role == "Admin") {
                                        akun[i].saldo += item.buku.harga;
                                        break;}}

                                Transaksi t;
                                t.id_transaksi = "TRX" + to_string(transaksi.size() + 1);
                                t.id_user = akun[indeksLogin].id_user;
                                t.id_order = o.id_order;
                                t.nominal = item.buku.harga;
                                t.tanggal_transaksi = tgl;
                                transaksi.push_back(t);
                            } else {
                                o.status_order  = "Ditunggu";
                                o.status_bayar  = "Belum Bayar";
                                o.tanggal_bayar = 0;}

                            order.push_back(o);
                            for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                                if (it->buku.kode == item.buku.kode && it->id_user == o.id_user) {
                                    it = keranjang.erase(it);
                                } else { ++it;}}}

                        saveOrder(order);
                        saveAkun(akun);
                        saveKeranjang(keranjang);
                        saveTransaksi(transaksi);
                        tampilPesan(40, "Checkout berhasil diproses!");
                        system("pause");
                        break;}
                    break;}}

            else if (pilihMenu == 1) {
                string kodeHapus;
                cout << "\n  Masukkan Kode E-Book yang ingin dihapus (Ketik '0' untuk batal): ";
                cin >> kodeHapus;
                if (kodeHapus == "0") continue;

                bool terhapus = false;
                for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                    if (it->buku.kode == kodeHapus && it->id_user == akun[indeksLogin].id_user) {
                        it = keranjang.erase(it);
                        terhapus = true;
                        break;
                    } else { ++it;}}

                if (terhapus) {
                    saveKeranjang(keranjang);
                    tampilPesan(40, "Item berhasil dihapus dari keranjang!");
                } else {
                    tampilPeringatan(40, "Kode E-Book tidak ditemukan.");}
                system("pause > nul");}}}}

/*  MENU PESANAN
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void pesananBelumDibayar(vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    string tindakan[] = {
        "【 1 | Bayar Sekarang     】",
        "【 2 | Batalkan Pesanan   】",
        "【 3 | Kembali            】"};
    string tindakan2[] = {
        "【 1 | Yakin              】",
        "【 2 | Batalkan           】"};
    bool ada = false;
    for (const auto &o : order) {
        if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Ditunggu") {
            ada = true;
            break;}}
    if (!ada) {
        system("cls"); judul_subjudul("PESANAN BELUM DIBAYAR"); cout << endl;
        tampilPeringatan(38, "Tidak ada pesanan yang belum dibayar!"); system("pause");
        return;}

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("PESANAN BELUM DIBAYAR"); cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(35) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(35) << tindakan[i] << RESET << endl;}
        cout << endl; lihatPesananUser("Belum Bayar", order, akun[indeksLogin].id_user);
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;

            // BAYAR SEKARANG         
            if (pilih == 0) {
                int konfirmasi = 0;
                int pilihan = scrollOrder(order, "PESANAN BELUM DIBAYAR", "Ditunggu", akun[indeksLogin].id_user);
                while (true) {
                    if (refresh) {
                        system("cls"); refresh = false;}
                    clsScroll(0,0); judul_subjudul("BAYAR PESANAN"); cout << endl;
                    lihatDetailOrder(order, pilihan, "User", "Ditunggu", akun[indeksLogin].id_user);
                    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                    cout << endl << spasi(34) << BOLD << KUNING << "Yakin ingin melakukan pembayaran?" << RESET; cout << endl;
                    for (int i = 0; i < 2; i++) {
                        if (i == konfirmasi)
                            cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan2[i] << RESET << endl;
                        else cout << DIM << spasi(39) << tindakan2[i] << RESET << endl;}
                    int hasil2 = scrollMenu(konfirmasi, 2);
                    if (hasil2 == -1) {
                        refresh = true;
                        if (konfirmasi == 0) {     
                            if (akun[indeksLogin].saldo >= order[pilihan].harga) {
                                akun[indeksLogin].saldo -= order[pilihan].harga;
                                for (size_t i = 0; i < akun.size(); i++) {
                                    if (akun[i].role == "Admin") {
                                        akun[i].saldo += order[pilihan].harga;
                                        break;}}

                                order[pilihan].status_bayar = "Lunas";
                                order[pilihan].status_order = "Diproses";

                                time_t now = time(0);
                                tm *ltm = localtime(&now);
                                int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;
                                order[pilihan].tanggal_bayar = tgl;

                                saveAkun(akun);
                                saveOrder(order);

                                Transaksi t;
                                t.id_transaksi = "TRX" + to_string(transaksi.size() + 1);
                                t.id_user = akun[indeksLogin].id_user;
                                t.id_order = order[pilihan].id_order;
                                t.nominal = order[pilihan].harga;
                                t.tanggal_transaksi = tgl;
                                transaksi.push_back(t);
                                saveTransaksi(transaksi);

                                tampilPesan(20, "Pembayaran Berhasil!"); system("pause");
                                return;}
                            else {
                                tampilPeringatan(18, "Saldo tidak cukup!"); system("pause");
                                break;}}
                        else {
                            break;}}}}

            // BATALKAN PESANAN
            else if (pilih == 1) {
                int pilihan = scrollOrder(order, "PESANAN BELUM DIBAYAR", "Ditunggu", akun[indeksLogin].id_user);

                string alasan;
                system("cls"); judul_subjudul("BATALKAN PESANAN"); cout << endl;
                lihatDetailOrder(order, pilihan, "User", "Ditunggu", akun[indeksLogin].id_user);
                cin.ignore(1000, '\n');
                cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                cout << spasi(47) << BOLD << "Alasan membatalkan : " << RESET; getline(cin, alasan);
                cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                if (alasan.empty()) {
                    tampilPeringatan(26, "Alasan tidak boleh kosong!"); system("pause");
                    continue;}

                int konfirmasi = 0;
                while (true) {
                    if (refresh) {
                        system("cls"); refresh = false;}
                    clsScroll(0,0); judul_subjudul("BATALKAN PESANAN"); cout << endl;
                    lihatDetailOrder(order, pilihan, "User", "Ditunggu", akun[indeksLogin].id_user);
                    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                    cout << endl << spasi(34) << BOLD << KUNING << "Yakin ingin membatalkan?" << RESET; cout << endl;
                    for (int i = 0; i < 2; i++) {
                        if (i == konfirmasi)
                            cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan2[i] << RESET << endl;
                        else cout << DIM << spasi(39) << tindakan2[i] << RESET << endl;}
                    int hasil2 = scrollMenu(konfirmasi, 2);
                    if (hasil2 == -1) {
                        refresh = true;
                        if (konfirmasi == 0) {
                            /* pesanan Ditunggu belum bayar, tidak perlu refund */
                            order[pilihan].status_order = "Dibatalkan";
                            order[pilihan].status_bayar = "Dibatalkan";
                            order[pilihan].batal_oleh = "User";
                            order[pilihan].alasan = alasan;
                            saveOrder(order);
                            tampilPesan(18, "Pesanan Dibatalkan!"); system("pause");
                            return;}
                        else {
                            break;}}}}

            else {
                break;}}}}


void pesananDiproses(vector<Akun> &akun, vector<Order> &order, int indeksLogin) {
    string tindakan[] = {
        "【 1 | Batalkan Pesanan   】",
        "【 2 | Kembali            】"};
    string tindakan2[] = {
        "【 1 | Yakin              】",
        "【 2 | Tidak              】"};

    bool ada = false;
    for (const auto &o : order) {
        if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Diproses") {
            ada = true; break;}}

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("PESANAN DIPROSES"); cout << endl;

        if (!ada) {
            lihatPesananUser("Diproses", order, akun[indeksLogin].id_user);
            system("pause"); return;}

        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << spasi(35) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(35) << tindakan[i] << RESET << endl;}
        cout << endl; lihatPesananUser("Diproses", order, akun[indeksLogin].id_user);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;

            if (pilih == 0) {
                int pilihan = scrollOrder(order, "BATALKAN PESANAN DIPROSES", "Diproses", akun[indeksLogin].id_user);

                string alasan;
                system("cls"); judul_subjudul("BATALKAN PESANAN"); cout << endl;
                lihatDetailOrder(order, pilihan, "User", "Diproses", akun[indeksLogin].id_user);
                cin.ignore(1000, '\n');
                cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                cout << spasi(47) << BOLD << "Alasan membatalkan : " << RESET; getline(cin, alasan);
                cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                if (alasan.empty()) {
                    tampilPeringatan(26, "Alasan tidak boleh kosong!"); system("pause");
                    continue;}

                int konfirmasi = 0;
                while (true) {
                    system("cls"); judul_subjudul("BATALKAN PESANAN"); cout << endl;
                    lihatDetailOrder(order, pilihan, "User", "Diproses", akun[indeksLogin].id_user);
                    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                    cout << endl << spasi(34) << BOLD << KUNING << "Yakin? Dana akan dikembalikan." << RESET; cout << endl;
                    for (int i = 0; i < 2; i++) {
                        if (i == konfirmasi)
                            cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan2[i] << RESET << endl;
                        else cout << DIM << spasi(39) << tindakan2[i] << RESET << endl;}
                    int hasil2 = scrollMenu(konfirmasi, 2);
                    if (hasil2 == -1) {
                        if (konfirmasi == 0) {
                            akun[indeksLogin].saldo += order[pilihan].harga;
                            for (size_t i = 0; i < akun.size(); i++) {
                                if (akun[i].role == "Admin") {
                                    akun[i].saldo -= order[pilihan].harga;
                                    break;}}
                            order[pilihan].status_order = "Dibatalkan";
                            order[pilihan].status_bayar = "Dana Dikembalikan";
                            order[pilihan].batal_oleh = "User";
                            order[pilihan].alasan = alasan;
                            saveOrder(order);
                            saveAkun(akun);
                            tampilPesan(40, "Pesanan dibatalkan. Dana telah dikembalikan!");
                            system("pause");
                            return;}
                        else { break;}}}

            } else {
                break;}}}}

void pesananDikirim(vector<Order> &order, vector<Akun> &akun, vector<Library> &lib, int indeksLogin, string username) {
    int pilihMenu = 0;
    bool refreshMenu = true;
    while (true) {
        system("cls"); judul_subjudul("PESANAN DIKIRIM"); cout << endl;
        lihatPesananUser("Dikirim", order, akun[indeksLogin].id_user);

        int jumlahPesanan = 0;
        for (const auto& o : order) {
            if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Dikirim") {
                jumlahPesanan++;}}

        if (jumlahPesanan == 0) {
            cout << "\n  Pilih Aksi:\n\n";
            cout << spasi(20) << BG_PUTIH << HITAM << BOLD << "『   Kembali               』" << RESET << endl;
            system("pause > nul"); 
            break;}

        string opsiMenu[] = {
            "『   Pesanan Diterima      』",
            "『   Kembali               』"};

        cout << "\n  Pilih Aksi:\n\n";
        for (int i = 0; i < 2; i++) {
            if (i == pilihMenu) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << opsiMenu[i] << RESET << endl;
            else cout << DIM << spasi(20) << opsiMenu[i] << RESET << endl;}

        int hasilMenu = scrollMenu(pilihMenu, 2);
        if (hasilMenu == -1) {
            refreshMenu = true;
            if (pilihMenu == 1) break;
            else if (pilihMenu == 0) {
                int pilihan = scrollOrder(order, "KONFIRMASI TERIMA", "Dikirim", akun[indeksLogin].id_user);

                string tindakan2[] = {
                    "【 1 | Yakin              】",
                    "【 2 | Batalkan           】"};
                int konfirmasi = 0;
                system("cls"); judul_subjudul("KONFIRMASI TERIMA"); cout << endl;
                lihatDetailOrder(order, pilihan, "User", "Dikirim", akun[indeksLogin].id_user);
                cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                cout << endl << spasi(34) << BOLD << KUNING << "Konfirmasi pesanan sudah diterima?" << RESET; cout << endl;
                for (int i = 0; i < 2; i++) {
                    if (i == konfirmasi)
                        cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan2[i] << RESET << endl;
                    else cout << DIM << spasi(39) << tindakan2[i] << RESET << endl;}
                int hasil2 = scrollMenu(konfirmasi, 2);
                if (hasil2 == -1 && konfirmasi == 0) {
                    time_t now = time(0);
                    tm *ltm = localtime(&now);
                    int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;
                    order[pilihan].tanggal_sampai = tgl;
                    order[pilihan].status_order = "Selesai";

                    Library lBaru;
                    lBaru.id_user    = akun[indeksLogin].id_user;
                    lBaru.username   = username;
                    lBaru.buku.kode  = order[pilihan].kode;
                    lBaru.buku.judul = order[pilihan].judul;
                    lib.push_back(lBaru);
                    saveOrder(order);
                    saveLibrary(lib);
                    tampilPesan(45, "Pesanan Selesai! E-Book ditambahkan ke Library.");
                    system("pause");}}}}}

void pesananDiproses(vector<Akun> &akun, vector<Order> &order, int indeksLogin) {
    lihatPesananUser("Diproses", order, akun[indeksLogin].id_user);}

void pesananDikirim(vector<Order> &order, vector<Akun> &akun, vector<Library> &lib, int indeksLogin, string username) {
    int pilihMenu = 0;
    bool refreshMenu = true;
    while (true) {
        system("cls"); judul_subjudul("PESANAN DIKIRIM"); cout << endl;
        lihatPesananUser("Dikirim", order, akun[indeksLogin].id_user);

        int jumlahPesanan = 0;
        for (const auto& o : order) {
            if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Dikirim") {
                jumlahPesanan++;}}

        if (jumlahPesanan == 0) {
            cout << "\n  Pilih Aksi:\n\n";
            cout << spasi(20) << BG_PUTIH << HITAM << BOLD << "『   Kembali               』" << RESET << endl;
            system("pause > nul"); 
            break;}

        string opsiMenu[] = {
            "『   Pesanan Diterima      』",
            "『   Kembali               』"};

        cout << "\n  Pilih Aksi:\n\n";
        for (int i = 0; i < 2; i++) {
            if (i == pilihMenu) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << opsiMenu[i] << RESET << endl;
            else cout << DIM << spasi(20) << opsiMenu[i] << RESET << endl;}

        int hasilMenu = scrollMenu(pilihMenu, 2);
        if (hasilMenu == -1) {
            refreshMenu = true;
            if (pilihMenu == 1) break;
            else if (pilihMenu == 0) {
                string id_selesai;
                cout << "\n  Masukkan ID ORDER yang sudah diterima (Ketik '0' untuk batal): ";
                cin >> id_selesai;
                if (id_selesai == "0") continue;

                bool ketemu = false;
                for (size_t i = 0; i < order.size(); i++) {
                    if (order[i].id_user == akun[indeksLogin].id_user && order[i].id_order == id_selesai && order[i].status_order == "Dikirim") {
                        order[i].status_order = "Selesai";
                        Library lBaru;
                        lBaru.id_user    = akun[indeksLogin].id_user;
                        lBaru.username   = username;
                        lBaru.buku.kode  = order[i].kode;
                        lBaru.buku.judul = order[i].judul; 
                        lib.push_back(lBaru);
                        saveOrder(order);
                        saveLibrary(lib);
                        tampilPesan(45, "Pesanan Selesai! E-Book ditambahkan ke Library.");
                        ketemu = true;
                        break;}}
                if (!ketemu) tampilPeringatan(35, "ID Order tidak valid.");
                system("pause");}}}}

/*  MENU SALDO DAN TRANSAKSI
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void editSaldo(vector<Akun> &akun, int indeksLogin) {
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};

    system("cls"); judul_subjudul("TOP UP SALDO"); cout << endl;
    cout << spasi(50) << "┌────────────────────────────────────┐" << endl;
    cout << spasi(50) << "│            TOP UP SALDO            │" << endl;
    cout << spasi(50) << "├────────────────────────────────────┤" << endl;
    cout << spasi(50) << "│ Saldo Saat Ini : Rp" << left << setw(16) << akun[indeksLogin].saldo << "│" << endl;
    cout << spasi(50) << "├────────────────────────────────────┤" << endl;
    cout << spasi(50) << "│ Nominal Top Up : Rp";

    string inputNominal; cin >> inputNominal;
    cout << spasi(50) << "└────────────────────────────────────┘" << endl;

    for (char c : inputNominal) {
        if (!isdigit(c)) {
            tampilPeringatan(26, "Nominal harus berupa angka!");
            return;}}
    int nominal;
    try {
        nominal = stoi(inputNominal);}
    catch (...) {
        tampilPeringatan("Nominal terlalu besar atau tidak valid!");
        return;}
    if (nominal < 10000 || nominal > 1000000) {
        tampilPeringatan("Top Up minimal Rp10.000 dan maksimal Rp1.000.000");
        return;}

    int pilihTindakan = 0;
    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("TOP UP SALDO"); cout << endl;
        cout << spasi(50) << "┌────────────────────────────────────┐" << endl;
        cout << spasi(50) << "│            TOP UP SALDO            │" << endl;
        cout << spasi(50) << "├────────────────────────────────────┤" << endl;
        cout << spasi(50) << "│ Saldo Saat Ini : Rp" << left << setw(16) << akun[indeksLogin].saldo << "│" << endl;
        cout << spasi(50) << "├────────────────────────────────────┤" << endl;
        cout << spasi(50) << "│ Nominal Top Up : Rp" << inputNominal << endl;
        cout << spasi(50) << "└────────────────────────────────────┘" << endl;
        cout << endl;
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Top Up dilakukan?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // SIMPAN
            if (pilihTindakan == 0) {
                if (akun[indeksLogin].saldo + nominal > 5000000) {
                    tampilPeringatan(32, "Batas maksimum saldo Rp5.000.000!");
                    break;}
                akun[indeksLogin].saldo += (int)nominal;
                saveAkun(akun);
                cout << endl;
                cout << spasi(50) << "Saldo sekarang : Rp" << akun[indeksLogin].saldo << endl;
                tampilPesan("Top Up Berhasil!");
                break;}

            else {
                tampilPeringatan(20, "Top Up dibatalkan!");
                break;}}}
    return;}

/*  MENU-MENU UTAMA USER
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void kelolaAkunDiri(vector<Akun> &akun, int indeksLogin) {
    string pilihMenuUser[] = {
        "『  ✏️  Ubah Data Akun Diri        』",
        "『 ↩   Kembali                    』"};
    int pilih = 0;
    bool refresh = true;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU KELOLA AKUN DIRI"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(34) << pilihMenuUser[i] << RESET << endl;}
        cout << endl; lihatDetailAkun(akun, indeksLogin);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;

            /* a. UBAH DATA AKUN DIRI
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                editDataDiri(akun, indeksLogin);}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/                
            else {
                break;}}}}

void belanjaUser(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    string pilihMenuUser[] = {
        "『  ➕ Tambah Ke Keranjang        』",
        "『  ✏️  Pesan Sekarang             』",
        "『  ↕️  Urutkan Katalog            』",
        "『  🔍 Cari E-Book                』",
        "『 ↩   Kembali                    』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU BELANJA"); cout << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuUser + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuUser + i) << RESET << endl;}
        cout << endl; lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
            refresh = true;
            if (pilih == 0) {
                tambahProdukkeKeranjang(ebook, keranjang, order, akun[indeksLogin].id_user);}
            else if (pilih == 1) {
                system("cls");
                checkoutDariKatalog(ebook, order, akun, indeksLogin, transaksi, keranjang);
                system("pause");}
            else if (pilih == 2) {
                urutEbook(ebook);}
            else if (pilih == 3) {
                cariEbook(ebook);}
            else {
                break;}}}}

void keranjangUser(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Akun> &akun, vector<Order> &order, int indeksLogin, vector<Transaksi> &transaksi) {
    string pilihMenuUser[] = {
        "『  ➕ Pesan Keranjang            』",
        "『  🗑️  Hapus E-Book Di Keranjang  』",
        "『 ↩   Kembali                    』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("KERANJANG BELANJA"); cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(34) << pilihMenuUser[i] << RESET << endl;}
        cout << endl; lihatDaftarKeranjang(keranjang, akun[indeksLogin].id_user);
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;
            if (pilih == 0) {
                system("cls"); checkoutDariKeranjang(keranjang, order, akun, indeksLogin, transaksi);}
            else if (pilih == 1) {
                system("cls"); hapusEbookDariKeranjang(ebook, keranjang, akun[indeksLogin].id_user);
                system("pause");}
            else {
                break;}}}}

void pesananUser(vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Library> &lib, vector<Transaksi> &transaksi) {
    string pilihMenuUser[] = {
        "『  📋 Daftar Pesanan Belum Dibayar 』",
        "『  📋 Daftar Pesanan Diproses      』",
        "『  📋 Daftar Pesanan Dikirim       』",
        "『  📋 Daftar Pesanan Selesai       』",
        "『  📋 Daftar Pesanan Dibatalkan    』",
        "『 ↩   Kembali                      』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU PESANAN"); cout << endl;
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuUser + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuUser + i) << RESET << endl;}
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
            refresh = true;
            if (pilih == 0) {
                pesananBelumDibayar(order, akun, indeksLogin, transaksi);}
            else if (pilih == 1) {
                pesananDiproses(akun, order, indeksLogin); system("pause");}
            else if (pilih == 2) {
                pesananDikirim(order, akun, lib, indeksLogin, akun[indeksLogin].username);}
            else if (pilih == 3) {
                system("cls"); judul_subjudul("DAFTAR PESANAN SELESAI"); cout << endl;
                lihatPesananUser("Selesai", order, akun[indeksLogin].id_user);
                system("pause");}
            else if (pilih == 4) {
                system("cls"); judul_subjudul("DAFTAR PESANAN DIBATALKAN"); cout << endl;
                lihatPesananUser("Dibatalkan", order, akun[indeksLogin].id_user);
                system("pause");}
            else {
                break;}}}}

void lihatLibraryUser(vector<Library> &lib, string id_user) {
    if (lib.empty()) {
        tampilPeringatan(36, "Belum ada perpustakaan yang dibuat!");
        return;}
    bool ada = false;
    for (size_t i = 0; i < lib.size(); i++) {
        if (lib[i].id_user == id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(26, "Kamu belum memiliki E-Book!");
        return;}

    cout << CYAN << BOLD;
    cout << "  ┌──────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "  │                                     PERPUSTAKAAN E-BOOK MILIKMU                                      │" << endl;
    cout << "  ├──────┬────────────────┬───────────────────────────────┬─────────────────────┬────────────────┬───────┤" << endl;
    cout << "  │ NO   │ KODE           │ JUDUL                         │ PENULIS             │ GENRE          │ TAHUN │" << endl;
    cout << "  ├──────┼────────────────┼───────────────────────────────┼─────────────────────┼────────────────┼───────┤" << endl;
    cout << RESET;
    int no = 1;
    for (size_t i = 0; i < lib.size(); i++) {
        if (lib[i].id_user == id_user) {
            cout << "  ";
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(5)  << no++
                << "│ " << setw(15) << lib[i].buku.kode
                << "│ " << setw(30) << lib[i].buku.judul
                << "│ " << setw(20) << lib[i].buku.penulis
                << "│ " << setw(15) << lib[i].buku.genre
                << "│ " << setw(6)  << lib[i].buku.tahun
                << "│" << RESET << endl;}}
    cout << CYAN;
    cout << "  └──────┴────────────────┴───────────────────────────────┴─────────────────────┴────────────────┴───────┘" << endl;
    cout << RESET << endl;}

void saldoDanTransaksi(vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    string pilihMenuUser[] = {
        "【  ➕ Top Up Saldo               】",
        "【  📑 Riwayat Transaksi          】",
        "『 ↩   Kembali                    』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU SALDO DAN TRANSAKSI"); cout << endl;
        cout << HIJAU << BOLD << spasi(56) << "┌──────────────────────────┐" << RESET << endl;
        cout << spasi(58) << HIJAU << BOLD << BG_HIJAU << "  Saldo: " << akun[indeksLogin].saldo << " " << RESET << endl;
        cout << HIJAU << BOLD << spasi(56) << "└──────────────────────────┘" << RESET << endl;
        cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuUser + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuUser + i) << RESET << endl;}
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;

            /* a. TOP UP SALDO
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("TOP UP SALDO"); cout << "" << endl;
                editSaldo(akun, indeksLogin);
                system("pause");}

            /* b. RIWAYAT TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("RIWAYAT TRANSAKSI"); cout << "" << endl;
                lihatRiwayatTransaksi(transaksi, "User", akun[indeksLogin].id_user);
                system("pause");}

            /* c. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}


void menuUser(vector<Akun> &akun, int indeksLogin, vector<Ebook> &ebook, vector<Library> &library, vector<Order> &order, vector<Transaksi> &transaksi, vector<Keranjang> &keranjang) {
    string pilihMenuUser[] = {
        "『        Kelola Akun Anda        』", 
        "『        Belanja Sekarang        』",
        "『        Keranjang Belanja       』",
        "『         Daftar Pesanan         』",
        "『        Perpustakaan Anda       』",
        "『        Saldo & Transaksi       』",
        "『             Logout             』"}; 
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("HALO, USER " + akun[indeksLogin].username);
        cout << HIJAU << BOLD << spasi(56) << "┌──────────────────────────┐" << RESET << endl;
        cout << spasi(58) << HIJAU << BOLD << BG_HIJAU << "  Saldo: " << akun[indeksLogin].saldo << " " << RESET << endl;
        cout << HIJAU << BOLD << spasi(56) << "└──────────────────────────┘" << RESET << endl;
        cout << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << spasi(52) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuUser + i) << RESET << endl;
            else cout << DIM << spasi(52) << *(pilihMenuUser + i) << RESET << endl;}
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {
            refresh = true;
    
            /* 1. MENU USER KELOLA AKUN DIRI
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                kelolaAkunDiri(akun, indeksLogin);}

            /* 2. MENU USER BELANJA SEKARANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                belanjaUser(ebook, keranjang, order, akun, indeksLogin, transaksi);}

            /* 3. MENU USER KERANJANG BELANJA
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                keranjangUser(ebook, keranjang, akun, order, indeksLogin, transaksi);}

            /* 4. MENU USER DAFTAR PESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                pesananUser(order, akun, indeksLogin, library, transaksi);}

            /* 4. MENU USER PERPUSTAKAAN ANDA
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("PERPUSTAKAAN ANDA"); cout << "" << endl;
                lihatLibraryUser(library, akun[indeksLogin].id_user);
                system("pause");}

            /* 5. MENU USER SALDO & TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 5) {
                saldoDanTransaksi(akun, indeksLogin, transaksi);}

            /* 6. MENU USER LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(16, "Logout berhasil!");
                system("pause");
                break;}}}}



/*═════════════════════════════════════════════════════════════════════════════════════════════════════════════
                MAIN PROGRAM
═══════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
int main() {
    vector<Akun> akun;
    vector<Ebook> ebook;
    vector<Library> library;
    vector<Order> order;
    vector<Transaksi> transaksi;
    vector<Keranjang> keranjang;
    loadAkun(akun);
    loadEbook(ebook);
    loadLibrary(library);
    loadOrder(order);
    loadTransaksi(transaksi);
    loadKeranjang(keranjang);

    SetConsoleOutputCP(65001);
    string pilihMenu[] = {
        "『             Log In             』", 
        "『            Register            』",
        "『             Keluar             』"}; 
    int pilih = 0;
    bool refresh = true;

    /* PROGRAM UTAMA
    ════════════════════════════════════════════════════*/
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("SELAMAT DATANG DI TOKO E-BOOK KAMI");
        cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(52) << BG_PUTIH << HITAM << BOLD << *(pilihMenu + i) << RESET << endl;
            else cout << DIM << spasi(52) << *(pilihMenu + i) << RESET << endl;}
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;

            if (pilih == 0) {
                system("cls"); judul_subjudul("LOG IN AKUN ANDA");
                int indeksLogin = login(akun);   // rekursif di dalam
                if (indeksLogin == -3) {
                    break;}
                else if (indeksLogin >= 0) {
                    if (akun[indeksLogin].role == "Admin") {
                        menuAdmin(akun, indeksLogin, ebook, order, transaksi);}
                    else {
                        menuUser(akun, indeksLogin, ebook, library, order, transaksi, keranjang);}}}

            /* 2. REGISTRASI
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("REGISTRASI AKUN ANDA");
                registrasi(akun); saveAkun(akun);
                system("pause");}

            /* 3. KELUAR PROGRAM
            ════════════════════════════════════════════════════*/
            else {
                system("cls"); judul_subjudul("Terima Kasih Telah Mengunjungi Kami"); cout << endl;
                break;}
        }
    }
    
    return 0;
}