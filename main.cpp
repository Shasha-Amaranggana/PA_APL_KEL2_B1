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
/*                     WARNA TAMPILAN                                                                             */
//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define UNDER   "\033[4m"
#define HITAM   "\033[30m"
#define MERAH   "\033[31m"
#define HIJAU   "\033[32m"
#define KUNING  "\033[33m"
#define BIRU    "\033[34m"
#define CYAN    "\033[36m"
#define PUTIH   "\033[37m"
#define BG_HIJAU   "\033[42m"
#define BG_PUTIH   "\033[47m"
#define BG_ABU     "\033[48;5;235m"

//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                     STRUCT CRUD                                                                             */
//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
struct Akun {
    string id_user, username, password, role,
        status_akun, email, alamat, no_hp, tanggal_daftar;
    int saldo;};

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
    string tanggal_pesan, tanggal_bayar, tanggal_kirim, tanggal_sampai;
    string status_order, status_bayar, batal_oleh, alasan;};

struct Transaksi {
    string id_transaksi, id_user, id_order;
    int nominal;
    string tanggal_transaksi;
    string jenis;};

struct Keranjang {
    string id_user;
    Ebook buku;};



//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                     FUNGSI LOAD & SAVE                                                                      */
//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
void loadAkun(vector<Akun> &akun) {
    ifstream file("../akun.json");
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
    ifstream file("../ebook.json");
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
    ifstream file("../library.json");
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
    ifstream file("../orders.json");
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
    ifstream file("../transaksi.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Transaksi t;
        t.id_transaksi = item["id_transaksi"];
        t.id_user = item["id_user"];
        t.id_order = item["id_order"];
        t.nominal = item["nominal"];
        t.tanggal_transaksi = item["tanggal_transaksi"];
        t.jenis = item["jenis"];
        trans.push_back(t);}}

void loadKeranjang(vector<Keranjang> &ker) {
    ifstream file("../keranjang.json");
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
    ofstream file("../akun.json");
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
    ofstream file("../ebook.json");
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
    ofstream file("../library.json");
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
    ofstream file("../orders.json");
    file << setw(4) << j;}

void saveTransaksi(vector<Transaksi> &trans) {
    json j = json::array();
    for (auto &t : trans) {
        j.push_back({
            {"id_transaksi", t.id_transaksi},
            {"id_user", t.id_user},
            {"id_order", t.id_order},
            {"nominal", t.nominal},
            {"tanggal_transaksi", t.tanggal_transaksi},
            {"jenis", t.jenis}
        });}
    ofstream file("../transaksi.json");
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
    ofstream file("../keranjang.json");
    file << setw(4) << j;}



//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                     FUNGSI BANTUAN                                                                          */
//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
void judul_subjudul(string subjudul) {
    string spasiPesan = string(((140 - subjudul.length())) / 2, ' ');
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

void tampilPeringatan(int nilai, string pesan) {
    string spasiGaris = string((140 - 40) / 2, ' ');
    string spasiPesan = string((140 - nilai) / 2, ' ');
    cout << KUNING << BOLD << endl;
    cout << spasiGaris << "----------------------------------------" << endl;
    cout << spasiPesan << pesan << endl;
    cout << spasiGaris << "----------------------------------------" << endl;
    cout << RESET << endl;}


// [FUNGSI OVERLOAD]
void tampilPeringatan(string pesan) {
    tampilPeringatan((int)pesan.length(), pesan);}

void tampilPesan(string pesan) {
    tampilPesan((int)pesan.length(), pesan);}


string spasi(int nilai) {
    return string(nilai, ' ');}

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
    if (ebook.empty()) return -1;

    int pilih = 0;
    bool refresh = true;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu); cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih E-book:" << RESET; cout << endl;
        for (size_t i = 0; i < ebook.size(); i++) {
            if (i == static_cast<size_t>(pilih)) {
                cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(4) << ebook[i].no << "│ " << setw(38) << ebook[i].judul << "│ " << setw(18) << ebook[i].kode <<  "│ " << setw(20) << ebook[i].penulis << RESET << endl;}
            else {
                cout << DIM << spasi(34) << "     " << setw(4) << ebook[i].no << "│ " << setw(38) << ebook[i].judul << "│ " << setw(18) << ebook[i].kode <<  "│ " << setw(20) << ebook[i].penulis << RESET << endl;}}
        int hasil = scrollMenu(pilih, ebook.size());
        if (hasil == -1) {
            refresh = true;
            return pilih;}}}

int scrollAkun(vector<Akun> &akun, string judulMenu) {
    int pilih = 0;
    bool refresh = true;

    vector<int> indexUser;
    for (size_t i = 0; i < akun.size(); i++) {
        if (akun[i].role == "User") {
            indexUser.push_back(i);}}

    if (indexUser.empty()) return -1;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu); cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih akun pelanggan:" << RESET; cout << endl;
        for (size_t i = 0; i < indexUser.size(); i++) {
            if (i == static_cast<size_t>(pilih)) {
                cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(9) << akun[indexUser[i]].id_user <<  "│ " << setw(18) << akun[indexUser[i]].username << RESET << endl;}
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
        if (jenis == "Dikirim_Dibatalkan") {
            if (order[i].status_order == "Dikirim" || order[i].status_order == "Dibatalkan") indexOrder.push_back(i);}
        else if (order[i].status_order == jenis) indexOrder.push_back(i);}
    
    if (indexOrder.empty()) return -1;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu); cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih pesanan:" << RESET; cout << endl;
        for (size_t i = 0; i < indexOrder.size(); i++) {
            if (id_user == "") {
                if (i == static_cast<size_t>(pilih)) {
                    cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(18) << order[indexOrder[i]].id_order <<  "│ " << setw(12) << order[indexOrder[i]].id_user <<  "│ " << setw(26) << order[indexOrder[i]].kode  << RESET << endl;}
                else {
                    cout << DIM << spasi(34) << "     " << setw(18) << order[indexOrder[i]].id_order <<  "│ " << setw(12) << order[indexOrder[i]].id_user <<  "│ " << setw(26) << order[indexOrder[i]].kode  << RESET << endl;}}
            else {
                if (i == static_cast<size_t>(pilih))
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
    
    if (indexKeranjang.empty()) return -1;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu); cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih E-book di keranjang:" << RESET; cout << endl;
        for (size_t i = 0; i < indexKeranjang.size(); i++) {
            if (i == static_cast<size_t>(pilih)) {
                cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(18) << keranjang[indexKeranjang[i]].buku.kode  <<  "│ " << setw(26) << keranjang[indexKeranjang[i]].buku.judul  << RESET << endl;}
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

string tanggalWaktuSekarang() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    return to_string(1900 + ltm->tm_year) + "-" + ((1 + ltm->tm_mon < 10) ? "0" : "")
        + to_string(1 + ltm->tm_mon) + "-" + ((ltm->tm_mday < 10) ? "0" : "")
        + to_string(ltm->tm_mday)

        + " "

        + ((ltm->tm_hour < 10) ? "0" : "") + to_string(ltm->tm_hour)
        + ":" + ((ltm->tm_min < 10) ? "0" : "") + to_string(ltm->tm_min)
        + ":" + ((ltm->tm_sec < 10) ? "0" : "") + to_string(ltm->tm_sec);}

string generateID(string prefix, int nomor, int padding = 4) {
    string nomorStr = to_string(nomor);
    int kurang = padding - nomorStr.length();
    if (kurang < 0) {
        kurang = 0;}
    return prefix + string(kurang, '0') + nomorStr;}

void bubbleSortEbook(vector<Ebook> *ebook, int kategori, bool ascending) {
    if (ebook->size() < 2) return;
    
    for (size_t i = 0; i < ebook->size() - 1; i++) {
        for (size_t j = 0; j < ebook->size() - i - 1; j++) {
            bool tukar = false;

            // JUDUL
            if (kategori == 0) {
                if (ascending) tukar = (*ebook)[j].judul > (*ebook)[j + 1].judul;
                else tukar = (*ebook)[j].judul < (*ebook)[j + 1].judul;}

            // PENULIS
            else if (kategori == 1) {
                if (ascending) tukar = (*ebook)[j].penulis > (*ebook)[j + 1].penulis;
                else tukar = (*ebook)[j].penulis < (*ebook)[j + 1].penulis;}

            // GENRE
            else if (kategori == 2) {
                if (ascending)  tukar = (*ebook)[j].genre > (*ebook)[j + 1].genre;
                else tukar = (*ebook)[j].genre < (*ebook)[j + 1].genre;}

            // TAHUN
            else if (kategori == 3) {
                if (ascending) tukar = (*ebook)[j].tahun > (*ebook)[j + 1].tahun;
                else tukar = (*ebook)[j].tahun < (*ebook)[j + 1].tahun;}

            // HARGA
            else if (kategori == 4) {
                if (ascending) tukar = (*ebook)[j].harga > (*ebook)[j + 1].harga;
                else tukar = (*ebook)[j].harga < (*ebook)[j + 1].harga;}

            // KODE
            else if (kategori == 5) {
                if (ascending) tukar = (*ebook)[j].kode > (*ebook)[j + 1].kode;
                else tukar = (*ebook)[j].kode < (*ebook)[j + 1].kode;}

            // NO
            else if (kategori == 6) {
                if (ascending) tukar = (*ebook)[j].no > (*ebook)[j + 1].no;
                else tukar = (*ebook)[j].no < (*ebook)[j + 1].no;}

            if (tukar) {
                swap((*ebook)[j], (*ebook)[j + 1]);}}}}

void bubbleSortOrder(vector<Order> &order) {
    if (order.size() < 2) return;
    
    for (size_t i = 0; i < order.size() - 1; i++) {
        for (size_t j = 0; j < order.size() - i - 1; j++) {
            if (order[j].id_order < order[j + 1].id_order) {
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
    if (index == 0) {
        hasil.clear();}
    if (index >= static_cast<int>(order.size())) {
        return hasil.size();}
    string key = ubahStringKecilSemua(keyword);
    if (order[index].status_order == "Selesai") {
        if (ubahStringKecilSemua(order[index].id_order).find(key) != string::npos) {
            hasil.push_back(order[index]);}}

    return linearSearchOrder(order, hasil, keyword, index + 1);}



//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                     FUNGSI LOGIN & REGISTER                                                                 */
//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
int login(vector<Akun> &akun) {
    string jawabNama, jawabPassword;

    cin.ignore(1000, '\n'); cout << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Username: " << RESET; getline(cin, jawabNama);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Password: " << RESET; getline(cin, jawabPassword);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    if (jawabNama.empty() || jawabPassword.empty()) {
        tampilPeringatan(40, "Username dan password tidak boleh kosong!"); system("pause");
        return -3;}
    for (size_t i = 0; i < akun.size(); i++) {
        if(akun[i].username == jawabNama && akun[i].password == jawabPassword) {
            if (akun[i].status_akun == "Nonaktif") {
                tampilPeringatan(20, "Akun anda nonaktif!");
                system("pause");
                return -2;}
            tampilPesan(35, "Login berhasil! Selamat datang, " + jawabNama);
            system("pause");
            return i;}}
    return -1;}
   
void registrasi(vector<Akun> &akun) {
    string username, password, email, no_hp, alamat;

    cout << KUNING << endl; cin.ignore(1000, '\n');
    cout << spasi(30) << "☞    Username min 5 karakter, mengandung huruf/angka, tidak mengandung simbol/" << endl;
    cout << spasi(30) << "     karakter spesial kecuali spasi/underscroe" << endl;
    cout << spasi(30) << "☞    Password min 8 karakter, mengandung huruf besar & kecil & angka, simbol" << endl;
    cout << spasi(30) << "     diperbolehkan kecuali spasi" << endl;
    cout << spasi(30) << "☞    Email harus valid dan berakhiran '@gmail.com'" << endl;
    cout << spasi(30) << "☞    No. HP harus valid, berawalan '08', min 10 angka" << RESET << endl << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Username : " << RESET; getline(cin, username);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Password : " << RESET; getline(cin, password);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Email    : " << RESET; getline(cin, email);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "No. HP   : " << RESET; getline(cin, no_hp);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Alamat   : " << RESET; getline (cin, alamat);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;

    // VALIDASI INPUT REGISTRASI
    if (password.find(' ') != string::npos || email.find(' ') != string::npos || no_hp.find(' ') != string::npos) {
        tampilPeringatan(56, "Password, Email, dan No. HP tidak boleh mengandung spasi!");
        return;}
    regex userRegex("^[a-zA-Z0-9_ ]{5,}$");
    regex passRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$");
    regex hpRegex("^08\\d{8,12}$");
    regex emailRegex("^[a-zA-Z0-9._%+\\-]+@gmail\\.com$");
    if (!regex_match(username, userRegex) || !regex_match(password, passRegex) || !regex_match(no_hp, hpRegex) || !regex_match(email, emailRegex)) {
        tampilPeringatan(36, "Data registrasi harus sesuai syarat!");
        return;}
    for (auto &a : akun) {
        if (a.username == username) {
            tampilPeringatan(20, "Username sudah ada!");
            return;}
        if (a.email == email) {
            tampilPeringatan(22, "Email sudah digunakan!");
            return;}}

    // TAMBAHKAN AKUN BARU
    Akun baru;
    baru.id_user = generateID("U", akun.size(), 4);
    baru.username = username;
    baru.password = password;
    baru.role = "User";
    baru.status_akun = "Aktif";
    baru.email = email;
    baru.no_hp = no_hp;
    baru.alamat = alamat;
    baru.tanggal_daftar = tanggalWaktuSekarang();
    baru.saldo = 0;
    akun.push_back(baru);
    saveAkun(akun);

    tampilPesan(20, "Registrasi berhasil!");}
   


//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                     FUNGSI MENU ADMIN                                                                       */
//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//

/*  MENU KELOLA AKUN PELANGGAN                                                                     */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
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
        akun[indeksLogin].tanggal_daftar,
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
        if (i % 2 == 0) cout << BG_ABU;
        cout << "│ " << left << setw(19) << field[i]
            << "│ " << setw(36) << data[i]
            << "│" << RESET << endl;}
    cout << CYAN;
    cout << spasi(40) << "└────────────────────┴─────────────────────────────────────┘" << endl;
    cout << RESET << endl;}

void lihatDaftarPelanggan(vector<Akun> &akun) {
    // CEK KETERSEDIAAN PELANGGAN
    bool ada = false;
    for (const auto &a : akun) {
        if (a.role == "User"){
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(36, "Belum ada pelanggan yang terdaftar!");
        return;}

    // DAFTAR PELANGGAN
    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                     DAFTAR AKUN PELANGGAN                                                    │" << endl;
    cout << spasi(6) << "├────┬──────────┬────────────────────┬───────────────────────────────┬──────────────────┬──────────────────────┬───────────────┤" << endl;
    cout << spasi(6) << "│ NO │ ID USER  │ USERNAME           │ EMAIL                         │ NO HP            │ ALAMAT               │ STATUS AKUN   │" << endl;
    cout << spasi(6) << "├────┼──────────┼────────────────────┼───────────────────────────────┼──────────────────┼──────────────────────┼───────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (const auto &a : akun) {
        if (a.role == "User") {
            cout << spasi(6);
            if (no % 2 == 0) cout << BG_ABU;
            cout << "│ " << left << setw(3) << no++
                << "│ " << setw(9) << a.id_user
                << "│ " << setw(19) << a.username
                << "│ " << setw(30) << a.email
                << "│ " << setw(17) << a.no_hp
                << "│ " << setw(21) << a.alamat << "│ ";
            if (a.status_akun == "Aktif")
                cout << HIJAU << BOLD << setw(14) << a.status_akun << RESET;
            else
                cout << MERAH << BOLD << setw(14) << a.status_akun << RESET;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└────┴──────────┴────────────────────┴───────────────────────────────┴──────────────────┴──────────────────────┴───────────────┘" << endl;
    cout << RESET << endl;}

void editStatusPelanggan(vector<Akun> &akun) {
    string tindakan[] = {
        "【 1 | Aktifkan      】",
        "【 2 | Nonaktifkan   】",
        "【 3 | Batalkan      】"};

    int pilihan = scrollAkun(akun, "EDIT STATUS AKUN PELANGGAN");

    // KONFIRMASI TINDAKAN
    int pilih = 0; bool refresh = true;
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
                break;}

            // NONAKTIFKAN
            else if (pilih == 1){
                if (akun[pilihan].status_akun == "Nonaktif") {
                    tampilPeringatan(20, "Akun sudah nonaktif!");}
                else {
                    akun[pilihan].status_akun = "Nonaktif";
                    saveAkun(akun);
                    tampilPesan(28, "Akun berhasil dinonaktifkan!");}
                break;}

            // BATALKAN
            else {
                break;}}}}


/*  MENU PENJUALAN                                                                                 */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
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
        if (i % 2 == 0) cout << BG_ABU;
        cout << "│ " << left << setw(8) << field[i]
            << "│ " << setw(47) << data[i]
            << "│" << RESET << endl;}
    cout << CYAN;
    cout << spasi(40) << "└─────────┴────────────────────────────────────────────────┘" << endl;
    cout << RESET << endl;}
 
void lihatDaftarEbook(vector<Ebook> &ebook) {
    // CEK KETERSEDIAAN E-BOOK
    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi.");
        return;}

    // DAFTAR E-BOOK
    cout << CYAN << BOLD;
    cout << "  ┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << "  │                                                         DAFTAR E-BOOK KATALOG                                                        │" << endl;
    cout << "  ├──────┬───────────────────┬────────────────────────────────────────┬────────────────────────┬───────┬─────────────────┬───────────────┤" << endl;
    cout << "  │ NO   │ KODE              │ JUDUL                                  │ PENULIS                │ TAHUN │ GENRE           │ HARGA         │" << endl;
    cout << "  ├──────┼───────────────────┼────────────────────────────────────────┼────────────────────────┼───────┼─────────────────┼───────────────┤" << endl;
    cout << RESET;
    for (const auto &e : ebook) {
        cout << "  ";
        if (e.no % 2 == 0) cout << BG_ABU;
        cout << "│ " << left << setw(5) << e.no
            << "│ " << setw(18) << e.kode
            << "│ " << setw(39) << e.judul
            << "│ " << setw(23) << e.penulis
            << "│ " << setw(6) << e.tahun
            << "│ " << setw(16) << e.genre
            << "│ " << setw(14) << e.harga
            << "│" << RESET << endl;}
    cout << CYAN;
    cout << "  └──────┴───────────────────┴────────────────────────────────────────┴────────────────────────┴───────┴─────────────────┴───────────────┘" << endl;
    cout << RESET << endl;}

void tambahEbook(vector<Ebook> &ebook) {
    string inputTahun, inputHarga;
    Ebook baru;
    string genre[] = {
        "Romance", "Fantasy", "Horror", "Mystery", "Thriller", "Sci-Fi", "Adventure", "Action", "Drama", "Comedy",
        "Historical", "Crime", "Psychological", "Slice of Life", "School", "Supernatural", "Family", "Friendship",
        "Religious", "Biography"};
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};

    // TAMBAHKAN JUDUL, PENULIS, TAHUN
    system("cls"); judul_subjudul("TAMBAH E-BOOK"); cout << endl;
    cin.ignore(1000, '\n');
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Judul   : " << RESET; getline(cin, baru.judul);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    if (baru.judul.empty()) {
        tampilPeringatan(24, "Judul tidak boleh kosong!");
        return;}
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Penulis : " << RESET; getline(cin, baru.penulis);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    if (baru.penulis.empty()) {
        tampilPeringatan(26, "Penulis tidak boleh kosong!");
        return;}
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Tahun   : " << RESET; getline(cin, inputTahun);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    if (inputTahun.empty()) {
        tampilPeringatan(24, "Tahun tidak boleh kosong!");
        return;}
    for (char c : inputTahun) {
        if (!isdigit(c)) {
            tampilPeringatan(24, "Tahun harus berupa angka!");
            return;}}
    try {
        baru.tahun = stoi(inputTahun);}
    catch (...) {
        tampilPeringatan(20, "Angka terlalu besar!");
        return;}
    if (baru.tahun < 1000 || baru.tahun > 3000) {
        tampilPeringatan(46, "Tahun harus berada di rentang tahun 1000-3000!");
        return;}

    // TAMBAH GENRE
    int pilihGenre = 0; bool refreshGenre = true;
    while (true) {
        if (refreshGenre) {
            system("cls"); refreshGenre = false;}
        clsScroll(0,0); judul_subjudul("TAMBAH E-BOOK"); cout << endl;
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
            if (i == pilihGenre)
                cout << spasi(52) << "➠    " << BG_PUTIH << HITAM << BOLD << genre[i] << RESET << endl;
            else cout << DIM << spasi(52) << "➠    " << genre[i] << RESET << endl;}
        int hasil = scrollMenu(pilihGenre, 20);
        if (hasil == -1) {
            refreshGenre = true;
            baru.genre = genre[pilihGenre];
            break;}}

    // TAMBAH HARGA
    system("cls"); judul_subjudul("TAMBAH E-BOOK"); cout << endl;
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
    cout << spasi(47) << BOLD << "Harga   : " << RESET; getline(cin, inputHarga);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    if (inputHarga.empty()) {
        tampilPeringatan(24, "Harga tidak boleh kosong!");
        return;}
    for (char c : inputHarga) {
        if (!isdigit(c)) {
            tampilPeringatan(24, "Harga harus berupa angka!");
            return;}}
    try {
        baru.harga = stoi(inputHarga);}
    catch (...) {
        tampilPeringatan(20, "Angka terlalu besar!");
        return;}
    if (baru.harga < 0 || baru.harga > 10000000) {
        tampilPeringatan(42, "Harga harus berada di rentang 0-10.000.000!");
        return;}

    // KONFIRMASI TINDAKAN
    int pilihTindakan = 0; bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("TAMBAH E-BOOK"); cout << endl;
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
        cout << endl << spasi(34) << BOLD << KUNING << "Simpan E-book?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // SIMPAN
            if (pilihTindakan == 0) {
                // CEK DUPLIKAT E-BOOK DI KATALOG
                for (auto &e : ebook) {
                    if (e.judul == baru.judul && e.penulis == baru.penulis && e.tahun == baru.tahun) {
                        tampilPeringatan(28, "E-book sudah ada di katalog!");
                        return;}}
                baru.no = generateNo(ebook);
                baru.kode = generateKode(ebook, baru.judul, baru.penulis, baru.tahun);
                ebook.push_back(baru);
                bubbleSortEbook(&ebook, 6, true);
                saveEbook(ebook);
                cout << endl; tampilPesan(28, "E-book berhasil ditambahkan!");
                break;}

            // BATALKAN
            else {
                tampilPeringatan(22, "Penambahan dibatalkan!");
                break;}}}}

void editEbook(vector<Ebook> &ebook) {
    // CEK KETERSEDIAAN E-BOOK
    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi!");
        return;}

    // EDIT E-BOOK
    string inputJudul, inputPenulis, inputTahun, inputHarga;
    string genre[] = {
        "Romance", "Fantasy", "Horror", "Mystery", "Thriller", "Sci-Fi", "Adventure", "Action", "Drama", "Comedy",
        "Historical", "Crime", "Psychological", "Slice of Life", "School", "Supernatural", "Family", "Friendship",
        "Religious", "Biography"};
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};

    int pilihan = scrollBuku(ebook, "EDIT DETAIL E-BOOK");
    Ebook temp = ebook[pilihan];

    system("cls"); judul_subjudul("EDIT DETAIL E-BOOK"); cout << endl;
    lihatDetailEbook(ebook, pilihan);
    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
    cout << KUNING << spasi(30) << "☞    Enter jika tidak ingin merubah salah satu field data (kecuali Genre)" << RESET << endl;
    
    // UBAH JUDUL, PENULIS, DAN TAHUN
    cout << endl; cin.ignore(1000, '\n');
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
                tampilPeringatan(34, "Tahun harus berupa angka dan jelas!");
                return;}}
        try {
            temp.tahun = stoi(inputTahun);}
        catch (...) {
            tampilPeringatan(20, "Angka terlalu besar!");
            return;}
        if (temp.tahun < 1000 || temp.tahun > 3000) {
            tampilPeringatan(46, "Tahun harus berada di rentang tahun 1000-3000!");
            return;}}

    // UBAH GENRE
    int pilihGenre = 0; bool refreshGenre = true;
    while (true) {
        if (refreshGenre) {
            system("cls"); refreshGenre = false;}
        clsScroll(0,0); judul_subjudul("EDIT DETAIL E-BOOK"); cout << endl;
        lihatDetailEbook(ebook, pilihan);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << KUNING << spasi(30) << "☞    Enter jika tidak ingin merubah salah satu field data (kecuali Genre)" << RESET << endl;
        cout << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Judul Baru   : " << RESET << inputJudul << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Penulis Baru : " << RESET << inputPenulis << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Tahun Baru   : " << RESET << inputTahun << endl;
        cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
        cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
        cout << spasi(47) << BOLD << "Genre Baru   : " << RESET;
        cout << endl;
        for (int i = 0; i < 20; i++) {
            if (i == pilihGenre)
                cout << spasi(52) << "➠    " << BG_PUTIH << HITAM << BOLD << genre[i] << RESET << endl;
            else cout << DIM << spasi(52) << "➠    " << genre[i] << RESET << endl;}
        int hasil = scrollMenu(pilihGenre, 20);
        if (hasil == -1) {
            refreshGenre = true;
            temp.genre = genre[pilihGenre];
            break;}}

    // UBAH HARGA
    system("cls"); judul_subjudul("EDIT DETAIL E-BOOK"); cout << endl;
    lihatDetailEbook(ebook, pilihan);
    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
    cout << KUNING << spasi(30) << "☞    Enter jika tidak ingin merubah salah satu field data (kecuali Genre)" << RESET << endl;
    cout << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Judul Baru   : " << RESET << inputJudul << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Penulis Baru : " << RESET << inputPenulis << endl;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Tahun Baru   : " << RESET << inputTahun << endl;
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
                tampilPeringatan(34, "Harga harus berupa angka dan jelas!");
                return;}}
        try {
            temp.harga = stoi(inputHarga);}
        catch (...) {
            tampilPeringatan(20, "Angka terlalu besar!");
            return;}
        if (temp.harga < 0 || temp.harga > 10000000) {
            tampilPeringatan(42, "Harga harus berada di rentang 0-10.000.000!");
            return;}}

    // KONFIRMASI TINDAKAN
    int pilihTindakan = 0; bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("EDIT DETAIL E-BOOK"); cout << endl;
        lihatDetailEbook(ebook, pilihan);
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
                tampilPesan(28, "Perubahan berhasil disimpan!");
                break;}

            // BATALKAN
            else {
                tampilPeringatan(20, "Perubahan dibatalkan!");
                break;}}}}

void hapusEbook(vector<Ebook> &ebook) {
    // CEK KETERSEDIAAN E-BOOK
    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi.");
        return;}

    // HAPUS E-BOOK
    string tindakan[] = {
        "【 1 | Hapus         】",
        "【 2 | Batalkan      】"};

    int pilihan = scrollBuku(ebook, "HAPUS E-BOOK");

    // KONFIRMASI TINDAKAN
    int pilihTindakan = 0; bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("HAPUS E-BOOK"); cout << endl;
        lihatDetailEbook(ebook, pilihan);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Hapus E-book ini?" << RESET; cout << endl;
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
                saveEbook(ebook);
                tampilPesan(24, "E-book berhasil dihapus!");
                break;}

            // BATALKAN
            else {
                tampilPeringatan(22, "Penghapusan dibatalkan!");
                break;}}}}

void urutEbook(vector<Ebook> &ebook) {
    // CEK KETERSEDIAAN E-BOOK
    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi!"); system("pause");
        return;}

    // URUT E-BOOK
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

    int pilih = 0; bool refresh = true;
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
            int pilihJenis = 0;  bool refreshTindakan = true;
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
                    if (pilihJenis == 0) {
                        bubbleSortEbook(&temp, pilih, true);}
                    else {
                        bubbleSortEbook(&temp, pilih, false);}

                    // TAMPILKAN HASIL
                    system("cls"); judul_subjudul("HASIL PENGURUTAN SEMENTARA"); cout << endl;
                    lihatDaftarEbook(temp);
                    system("pause");
                    break;}}}}}

void cariEbook(vector<Ebook> &ebook) {
    // CEK KETERSEDIAAN E-BOOK
    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi!"); system("pause");
        return;}

    // CARI E-BOOK
    string menuCari[] = {
        "『  📝 Judul                      』",
        "『  🪶  Penulis                    』",
        "『  🏷️  Genre                      』",
        "『  🗓️  Tahun                      』",
        "『  💲 Harga                      』",
        "『  🔑 Kode                       』",
        "『 ↩   Kembali                    』"};

    int pilih = 0; bool refresh = true;
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

            // TAMPILKAN HASIL
            cout << endl;
            if (!hasil.empty()) {
                cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                cout << HIJAU << BOLD << "\nDaftar Hasil Pencarian:" << endl;
                lihatDaftarEbook(hasil);}
            else {
                tampilPeringatan(22, "Data tidak ditemukan!");}
            system("pause");}}}


/*  MENU PEMBELIAN                                                                                 */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void lihatDetailOrder(vector<Order> &order, int indeksOrder, string jenis, string status) {
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
                order[indeksOrder].tanggal_pesan,
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
                order[indeksOrder].tanggal_pesan,
                order[indeksOrder].status_bayar,
                order[indeksOrder].tanggal_bayar,
                order[indeksOrder].tanggal_kirim,
                order[indeksOrder].tanggal_sampai};}
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
                order[indeksOrder].tanggal_pesan,
                order[indeksOrder].status_bayar,
                order[indeksOrder].tanggal_bayar,
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
                order[indeksOrder].tanggal_pesan,
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
                order[indeksOrder].tanggal_pesan,
                order[indeksOrder].status_bayar,
                order[indeksOrder].tanggal_bayar,
                order[indeksOrder].tanggal_kirim,
                order[indeksOrder].tanggal_sampai};}
        else {
            field = {
                "ID ORDER", "KODE", "JUDUL", "HARGA", "STATUS ORDER", "TANGGAL PESAN", "STATUS BAYAR", "TANGGAL BAYAR", "BATAL OLEH", "ALASAN BATAL"};
            data = {
                order[indeksOrder].id_order,
                order[indeksOrder].kode,
                order[indeksOrder].judul,
                to_string(order[indeksOrder].harga),
                order[indeksOrder].status_order,
                order[indeksOrder].tanggal_pesan,
                order[indeksOrder].status_bayar,
                order[indeksOrder].tanggal_bayar,
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
        if (i % 2 == 0) cout << BG_ABU;
        cout << "│ " << left << setw(15) << field[i]
            << "│ " << setw(48) << data[i]
            << "│" << RESET << endl;}
    cout << CYAN;
    cout << spasi(36) << "└────────────────┴─────────────────────────────────────────────────┘" << endl;
    cout << RESET << endl;}

void lihatDaftarPembelian(vector<Order> &order) {
    // CEK KETERSEDIAAN PEMBELIAN
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada pesanan yang dibuat!");
        return;}
    bool ada = false;
    for (const auto &o : order) {
        if (o.status_order == "Selesai") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(26, "Belum ada daftar pembelian!");
        return;}

    // DAFTAR PEMBELIAN
    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                       DAFTAR PEMBELIAN                                                       │" << endl;
    cout << spasi(6) << "├──────┬──────────────────┬───────────┬─────────────────────────┬────────────┬────────────────────────┬────────────────────────┤" << endl;
    cout << spasi(6) << "│ NO   │ ID ORDER         │ ID USER   │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN          │ TANGGAL TERIMA         │" << endl;
    cout << spasi(6) << "├──────┼──────────────────┼───────────┼─────────────────────────┼────────────┼────────────────────────┼────────────────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (const auto &o : order) {
        if (o.status_order == "Selesai") {
            cout << spasi(6);
            if (no % 2 == 0) cout << BG_ABU;
            cout << "│ " << left << setw(5) << no++
                << "│ " << setw(17) << o.id_order
                << "│ " << setw(10) << o.id_user
                << "│ " << setw(24) << o.kode
                << "│ " << setw(11) << o.harga
                << "│ " << setw(23) << o.tanggal_pesan
                << "│ " << setw(23) << o.tanggal_sampai
                << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└──────┴──────────────────┴───────────┴─────────────────────────┴────────────┴────────────────────────┴────────────────────────┘" << endl;
    cout << RESET << endl;}

void cariDaftarPembelian(vector<Order> &order) {
    vector<Order> hasil;
    string keyword; cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Masukkan ID Order : " << RESET; getline(cin, keyword);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    linearSearchOrder(order, hasil, keyword); cout << endl;
    
    // TAMPILKAN HASIL
    if (!hasil.empty()) {
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << HIJAU << BOLD << "\nDaftar Hasil Pencarian:" << endl;
        lihatDaftarPembelian(hasil);}
    else {
        tampilPeringatan(22, "Data tidak ditemukan!");}}


/*  MENU PEMESANAN                                                                                 */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void lihatPesanan(string jenis, vector<Order> &order) {
    // CEK KETERSEDIAAN PESANAN
    bool ada = false;
    for (const auto &o : order) {
        if (jenis == "Belum Bayar") {
            if (o.status_bayar == jenis && o.status_order == "Ditunggu") {
                ada = true;
                break;}}
        else {
            if (o.status_order == "Diproses") {
                ada = true;
                break;}}}
    if (!ada) {
        tampilPeringatan(40, "Belum ada pesanan dengan status tersebut!");
        return;}

    // DAFTAR PESANAN
    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                        DAFTAR PESANAN                                                        │" << endl;
    cout << spasi(6) << "├──────┬───────────────────┬─────────────┬───────────────────────────┬────────────┬────────────────────────┬───────────────────┤" << endl;
    cout << spasi(6) << "│ NO   │ ID ORDER          │ ID USER     │ KODE E-BOOK               │ HARGA      │ TANGGAL PESAN          │ STATUS            │" << endl;
    cout << spasi(6) << "├──────┼───────────────────┼─────────────┼───────────────────────────┼────────────┼────────────────────────┼───────────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (const auto &o : order) {
        bool tampil = false;
        if (jenis == "Belum Bayar") {
            tampil = (o.status_bayar == "Belum Bayar" && o.status_order == "Ditunggu");}
        else if (jenis == "Lunas") {
            tampil = (o.status_order == "Diproses");}
        if (tampil) {
            cout << spasi(6);
            if (no % 2 == 0) cout << BG_ABU;
            cout << "│ " << left << setw(5) << no++
                << "│ " << setw(18) << o.id_order
                << "│ " << setw(12) << o.id_user
                << "│ " << setw(26) << o.kode
                << "│ " << setw(11) << o.harga
                << "│ " << setw(23) << o.tanggal_pesan << "│ ";
            if (o.status_bayar == "Belum Bayar")
                cout << MERAH << BOLD << setw(18) << o.status_bayar << RESET;
            else
                cout << HIJAU << BOLD << setw(18) << o.status_bayar << RESET;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└──────┴───────────────────┴─────────────┴───────────────────────────┴────────────┴────────────────────────┴───────────────────┘" << endl;
    cout << RESET << endl;}

void lihatRiwayatPesanan(vector<Order> &order) {
    // CEK KETERSEDIAAN PESANAN
    if(order.empty()) {
        tampilPeringatan(30, "Belum ada pesanan yang dibuat!");
        return;}
    bool ada = false;
    for (const auto &o : order) {
        if (o.status_order == "Dikirim" || o.status_order == "Dibatalkan") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(40, "Belum ada pesanan dengan status tersebut!");
        return;}

    // DAFTAR PESANAN
    cout << CYAN << BOLD;
    cout << spasi(5) << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(5) << "│                                                         DAFTAR PESANAN                                                         │" << endl;
    cout << spasi(5) << "├──────┬───────────────────┬─────────────┬───────────────────────────┬────────────┬──────────────────────┬───────────────────────┤" << endl;
    cout << spasi(5) << "│ NO   │ ID ORDER          │ ID USER     │ KODE E-BOOK               │ HARGA      │ TANGGAL PESAN        │ STATUS                │" << endl;
    cout << spasi(5) << "├──────┼───────────────────┼─────────────┼───────────────────────────┼────────────┼──────────────────────┼───────────────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (const auto &o : order) {
        if (o.status_order == "Dikirim" || o.status_order == "Dibatalkan") {
            cout << spasi(5);
            if (no % 2 == 0) cout << BG_ABU;
            cout << "│ " << left << setw(5) << no++
                << "│ " << setw(18) << o.id_order
                << "│ " << setw(12) << o.id_user
                << "│ " << setw(26) << o.kode
                << "│ " << setw(11) << o.harga
                << "│ " << setw(21) << o.tanggal_pesan << "│ ";
            if (o.status_order == "Dikirim")
                cout << BIRU << BOLD << setw(22) << o.status_order << RESET;
            else
                cout << MERAH << BOLD << setw(12) << o.status_order << " (" << setw(6) << o.batal_oleh << ") " << RESET;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(5) << "└──────┴───────────────────┴─────────────┴───────────────────────────┴────────────┴──────────────────────┴───────────────────────┘" << endl;
    cout << RESET << endl;}

void editStatusPesanan(vector<Order> &order, vector<Akun> &akun, vector<Transaksi> &transaksi) {
    // CEK KETERSEDIAAN PESANAN
    bool ada = false;
    for (const auto &o : order) {
        if (o.status_order == "Diproses") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(40, "Tidak ada pesanan dengan status tersebut!");
        return;}

    // UBAH STATUS PESANAN
    string tindakan[] = {
        "【 1 | Kirim         】",
        "【 2 | Cancel        】",
        "【 3 | Batalkan      】"};

    int pilihan = scrollOrder(order, "UBAH STATUS PESANAN", "Diproses");

    // KONFIRMASI TINDAKAN
    int pilih = 0; bool refresh = false;
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
                // UBAH STATUS PESANAN
                order[pilihan].status_order = "Dikirim";
                order[pilihan].tanggal_kirim = tanggalWaktuSekarang();
                saveOrder(order);
                tampilPesan(26, "Pesanan berhasil dikirim!");
                break;}

            // CANCEL
            else if (pilih == 1) {
                cin.ignore(1000, '\n'); cout << endl;
                cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                cout << spasi(47) << BOLD << "Alasan : " << RESET; getline(cin, order[pilihan].alasan);
                cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                if (order[pilihan].alasan.empty()) {
                    tampilPeringatan(26, "Alasan tidak boleh kosong!"); system("pause");
                    continue;}

                // UBAH SALDO USER DAN ADMIN
                for (auto &a : akun) {
                    if (a.id_user == order[pilihan].id_user) {
                        a.saldo += order[pilihan].harga;
                        break;}}
                for (auto &a : akun) {
                    if (a.role == "Admin") {
                        a.saldo -= order[pilihan].harga;
                        break;}}

                // DETAIL PESANAN DIPERBARUI
                order[pilihan].status_order = "Dibatalkan";
                order[pilihan].status_bayar = "Dana Dikembalikan";
                order[pilihan].batal_oleh = "Admin";

                // CATAT TRANSAKSI
                Transaksi t;
                t.id_transaksi = generateID("TRX", transaksi.size() + 1, 6);
                t.id_user = order[pilihan].id_user;
                t.id_order = order[pilihan].id_order;
                t.nominal = order[pilihan].harga;
                t.tanggal_transaksi = tanggalWaktuSekarang();
                t.jenis = "Pengembalian";
                transaksi.push_back(t);
                
                saveTransaksi(transaksi);
                saveOrder(order);
                saveAkun(akun);
                tampilPesan(30, "Dana 100% dikembalikan ke user");
                tampilPesan(28, "Pesanan berhasil dibatalkan!");
                break;}

            // BATALKAN
            else {
                tampilPeringatan(36, "Perubahan status pesanan dibatalkan!");
                break;}}}}

void RiwayatPesanan(vector<Order> &order) {
    // CEK KETERSEDIAAN PESANAN
    bool ada = false;
    for (const auto &o : order) {
        if (o.status_order == "Dikirim" || o.status_order == "Dibatalkan" ) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(40, "Tidak ada pesanan dengan status tersebut!"); system("pause");
        return;}

    // RIWAYAT PESANAN
    string menuPemesanan[] = {
        "『  📋 Lihat Detail Riwayat Pesanan 』",
        "『 ↩   Kembali                      』"};

    int pilih = 0; bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("RIWAYAT PESANAN"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih)
                cout << spasi(34)  << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(menuPemesanan + i) << RESET << endl;
            else cout << DIM << spasi(34)  << *(menuPemesanan + i) << RESET << endl;}
        cout << endl; lihatRiwayatPesanan(order);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;
    
            /* a. LIHAT DETAIL RIWAYAT PESANAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("LIHAT DETAIL RIWAYAT PESANAN"); cout << endl;
                int pilihan = scrollOrder(order, "LIHAT DETAIL RIWAYAT PESANAN", "Dikirim_Dibatalkan");
                system("cls"); judul_subjudul("LIHAT DETAIL RIWAYAT PESANAN"); cout << endl;
                lihatDetailOrder(order, pilihan, "Admin", order[pilihan].status_order);
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}


/*  MENU-MENU UTAMA ADMIN                                                                          */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void lihatRiwayatTransaksi(vector<Transaksi> &transaksi, string jenis, string id_user = "") {
    // CEK KETERSEDIAAN TRANSAKSI
    if (transaksi.empty()) {
        tampilPeringatan(34, "Belum ada transaksi yang dilakukan!");
        return;}
    bool ada = false;
    for (const auto &t : transaksi) {
        if (jenis == "Admin" && t.jenis == "Isi Saldo")
            continue;
        if (jenis == "Admin" || t.id_user == id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(32, "Belum ada transaksi yang dibuat!");
        return;}

    // KELOLA RIWAYAT TRANSAKSI
    if (jenis == "Admin") {
        cout << CYAN << BOLD;
        cout << spasi(15) << "┌────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << spasi(15) << "│                                             RIWAYAT TRANSAKSI                                              │" << endl;
        cout << spasi(15) << "├──────┬──────────────────┬───────────┬──────────────────┬────────────┬──────────────────────┬───────────────┤" << endl;
        cout << spasi(15) << "│ NO   │ ID TRANSAKSI     │ ID USER   │ ID ORDER         │ NOMINAL    │ TANGGAL TRANSAKSI    │ JENIS         │" << endl;
        cout << spasi(15) << "├──────┼──────────────────┼───────────┼──────────────────┼────────────┼──────────────────────┼───────────────┤" << endl;
        cout  << RESET;
        int no = 1;
        for (const auto &t : transaksi) {
            if (t.jenis == "Isi Saldo")
                continue;
            cout << spasi(15); 
            if (no % 2 == 0) cout << BG_ABU;
            cout << "│ " << left << setw(5)  << no++
                << "│ " << setw(17) << t.id_transaksi
                << "│ " << setw(10) << t.id_user
                << "│ " << setw(17) << t.id_order << "│ ";
            if (t.jenis == "Pengembalian")
                cout << "-Rp" << setw(8) << t.nominal;
            else
                cout << "+Rp" << setw(8) << t.nominal;
            cout << "│ " << setw(21) << t.tanggal_transaksi << "│ ";
            if (t.jenis == "Pembayaran")
                cout << HIJAU << BOLD << setw(14) << t.jenis << RESET;
            else
                cout << MERAH << BOLD << setw(14) << t.jenis << RESET;
            cout << "│" << RESET << endl;}
        cout << CYAN;
        cout << spasi(15) << "└──────┴──────────────────┴───────────┴──────────────────┴────────────┴──────────────────────┴───────────────┘" << endl;
        cout << RESET << endl;}

    else {
        cout << CYAN << BOLD;
        cout << spasi(21) << "┌────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << spasi(21) << "│                                       RIWAYAT TRANSAKSI                                        │" << endl;
        cout << spasi(21) << "├──────┬──────────────────┬──────────────────┬────────────┬──────────────────────┬───────────────┤" << endl;
        cout << spasi(21) << "│ NO   │ ID TRANSAKSI     │ ID ORDER         │ NOMINAL    │ TANGGAL TRANSAKSI    │ JENIS         │" << endl;
        cout << spasi(21) << "├──────┼──────────────────┼──────────────────┼────────────┼──────────────────────┼───────────────┤" << endl;
        cout  << RESET;
        int no = 1;
        for (const auto &t : transaksi) {
            if (jenis != "Admin" && t.id_user != id_user)
                continue;
            cout << spasi(21);
            if (no % 2 == 0) cout << BG_ABU;
            cout << "│ " << left << setw(5)  << no++
                << "│ " << setw(17) << t.id_transaksi
                << "│ " << setw(17) << t.id_order << "│ ";
            if (t.jenis == "Pembayaran")
                cout << "-Rp" << setw(8) << t.nominal;
            else
                cout << "+Rp" << setw(8) << t.nominal;
            cout << "│ " << setw(21) << t.tanggal_transaksi << "│ ";
            if (t.jenis == "Pembayaran")
                cout << HIJAU << BOLD << setw(14) << t.jenis << RESET;
            else if (t.jenis == "Pengembalian")
                cout << MERAH << BOLD << setw(14) << t.jenis << RESET;
            else
                cout << BIRU << BOLD << setw(14) << t.jenis << RESET;
            cout << "│" << RESET << endl;}
        cout << CYAN;
        cout << spasi(21) << "└──────┴──────────────────┴──────────────────┴────────────┴──────────────────────┴───────────────┘" << endl;
        cout << RESET << endl;}}

void kelolaAkunPelanggan(vector<Akun> &akun) {
    // CEK KETERSEDIAAN PELANGGAN
    bool ada = false;
    for (const auto &a : akun) {
        if (a.role == "User") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(36, "Belum ada pelanggan yang terdaftar!"); system("pause");
        return;}

    // MENU KELOLA AKUN PELANGGAN
    string pilihMenuAdmin[] = {
        "『  ✏️  Ubah Status Akun Pelanggan 』",
        "『 ↩   Kembali                    』"};

    int pilih = 0; bool refresh = true;
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
                editStatusPelanggan(akun); system("pause");}

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

    int pilih = 0; bool refresh = true;
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
                tambahEbook(ebook);;
                system("pause");}

            /* b. EDIT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("EDIT DETAIL E-BOOK"); cout << endl;
                editEbook(ebook);
                system("pause");}

            /* c. HAPUS E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("HAPUS E-BOOK"); cout << endl;
                hapusEbook(ebook);
                system("pause");}

            /* d. URUT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("URUTKAN KATALOG"); cout << endl;
                urutEbook(ebook);}

            /* e. CARI E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("CARI E-BOOK"); cout << endl;
                cariEbook(ebook);}

            /* f. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pembelianAdmin(vector<Order> &order) {
    // CEK KETERSEDIAAN PEMBELIAN
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!"); system("pause");
        return;}
    bool ada = false;
    for (const auto &o : order) {
        if (o.status_order == "Selesai") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(26, "Belum ada daftar pembelian!"); system("pause");
        return;}

    // MENU PEMBELIAN
    string pilihMenuAdmin[] = {
        "『  🔍 Cari Riwayat Pembelian      』",
        "『  📋 Lihat Detail Data Pembelian 』",
        "『 ↩   Kembali                     』"};

    int pilih = 0; bool refresh = true;
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
                system("cls"); judul_subjudul("CARI RIWAYAT PEMBELIAN"); cout << endl;
                cariDaftarPembelian(order);
                system("pause");}

            /* b. LIHAT DETAIL DATA PEMBELIAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("LIHAT DETAIL DATA PEMBELIAN"); cout << endl;
                int pilihan = scrollOrder(order, "LIHAT DETAIL DATA PEMBELIAN", "Selesai");
                system("cls"); judul_subjudul("LIHAT DETAIL DATA PEMBELIAN"); cout << endl;
                lihatDetailOrder(order, pilihan, "Admin", "Selesai");
                system("pause");}

            /* c. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pemesananAdmin(vector<Order> &order, vector<Akun> &akun, vector<Transaksi> &transaksi){
    // CEK KETERSEDIAAN PESANAN
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!"); system("pause");
        return;}
    bool ada = false;
    for (const auto &o : order) {
        if (o.status_order != "Selesai") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(25, "Belum ada daftar pesanan!"); system("pause");
        return;}
    
    // MENU PEMESANAN
    string pilihMenuAdmin[] = {
        "『  📋 Daftar Pesanan Belum Dibayar 』",
        "『  📋 Daftar Pesanan Sudah Dibayar 』",
        "『  ✏️  Ubah Status Pesanan          』",
        "『  📑 Riwayat Pesanan Lainnya      』",
        "『 ↩   Kembali                      』"};

    int pilih = 0; bool refresh = true;
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
                editStatusPesanan(order, akun, transaksi);
                system("pause");}

            /* d. RIWAYAT PESANAN LAINNYA
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("RIWAYAT PESANAN LAINNYA"); cout << endl;
                RiwayatPesanan(order);}

            /* e. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}


/*  MENU ADMIN                                                                                     */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void menuAdmin(vector<Akun> &akun, int indeksLogin, vector<Ebook> &ebook, vector<Order> &order, vector<Transaksi> &transaksi) {
    string pilihMenuAdmin[] = {
        "『     Kelola Akun Pelanggan      』", 
        "『           Penjualan            』",
        "『           Pembelian            』",
        "『           Pemesanan            』",
        "『       Riwayat Transaksi        』",
        "『             Logout             』"}; 

    int pilih = 0; bool refresh = true;
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
                system("cls"); judul_subjudul("MENU KELOLA AKUN PELANGGAN"); cout << endl;
                kelolaAkunPelanggan(akun);}

            /* 2. MENU ADMIN PENJUALAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                penjualanAdmin(ebook);}

            /* 3. MENU ADMIN PEMBELIAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("MENU PEMBELIAN"); cout << endl;
                pembelianAdmin(order);}

            /* 4. MENU ADMIN PEMESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("MENU PEMESANAN"); cout << endl;
                pemesananAdmin(order, akun, transaksi);}

            /* 4. MENU ADMIN RIWAYAT TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("MENU RIWAYAT TRANSAKSI"); cout << endl;
                lihatRiwayatTransaksi(transaksi, "Admin");
                system("pause");}

            /* 5. MENU ADMIN LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(16, "Logout berhasil!"); system("pause");
                break;}}}}
   


//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                     FUNGSI MENU USER                                                                        */
//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//


/*  MENU KELOLA AKUN DIRI                                                                          */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void editDataDiri(vector<Akun> &akun, int indeksLogin) {
    string inputNoHp, inputAlamat, inputPassword;
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};

    Akun temp = akun[indeksLogin];

    // EDIT AKUN (NO HP, ALAMAT, PASSWORD)
    system("cls"); judul_subjudul("UBAH DATA AKUN DIRI"); cout << endl;
    lihatDetailAkun(akun, indeksLogin);
    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
    cout << KUNING << spasi(30) << "☞    Password min 8 karakter, mengandung huruf besar & kecil & angka, simbol" << endl;
    cout << spasi(30) << "     diperbolehkan" << endl;
    cout << spasi(30) << "☞    Email harus valid dan berakhiran '@gmail.com'" << endl;
    cout << spasi(30) << "☞    No. HP harus valid, berawalan '08', min 10 angka" << endl << endl;
    cout << spasi(30) << "☞    Tekan Enter jika tidak ingin mengubah field tertentu" << RESET << endl;

    cout << endl; cin.ignore(1000, '\n');
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "No. HP Baru   : " << RESET; getline(cin, inputNoHp);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    regex hpRegex("^08\\d{8,12}$");
    if (!inputNoHp.empty()) {
        if (!regex_match(inputNoHp, hpRegex)) {
            tampilPeringatan(34, "Data perubahan harus sesuai syarat!"); return;}
        temp.no_hp = inputNoHp;}
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Alamat Baru   : " << RESET; getline(cin, inputAlamat);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    if (!inputAlamat.empty()) {temp.alamat = inputAlamat;}
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD << "Password Baru : " << RESET; getline(cin, inputPassword);
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    regex passRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$");
    if (!inputPassword.empty()) {
        if (!regex_match(inputPassword, passRegex)) {
            tampilPeringatan(34, "Data perubahan harus sesuai syarat!");
             return;}
        temp.password = inputPassword;}

    if (inputNoHp.empty() && inputAlamat.empty() && inputPassword.empty()) {
        tampilPeringatan(26, "Tidak ada data yang diubah.");
        return;}

    // KONFIRMASI TINDAKAN
    int pilihTindakan = 0;  bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("UBAH DATA AKUN DIRI"); cout << endl;
        lihatDetailAkun(akun, indeksLogin);
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
                break;}

            // BATALKAN
            else {
                tampilPeringatan(20, "Perubahan dibatalkan!");
                break;}}}}

    
/*  MENU BELANJA                                                                                   */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void tambahProdukkeKeranjang(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Order> &order, vector<Library> &lib, string id_user) {
    Keranjang baru;
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};
 
    int pilihan = scrollBuku(ebook, "TAMBAH KE KERANJANG");
 
    // CEK KETERSEDIAAN PRODUK DI KERANJANG
    for (const auto &k : keranjang) {
        if (k.id_user == id_user && k.buku.kode == ebook[pilihan].kode) {
            tampilPeringatan(30, "E-Book sudah ada di keranjang!");
            return;}}
 
    // CEK KETERSEDIAAN PESANAN DENGAN STATUS YANG AKTIF (BELUM DIBAYAR, LUNAS/DIPROSES, DIKIRIM, SELESAI)
    for (const auto &o : order) {
        if (o.id_user == id_user && o.kode == ebook[pilihan].kode && o.status_order != "Dibatalkan") {
            tampilPeringatan(52, "Anda sudah memiliki pesanan aktif untuk E-book ini!");
            return;}}

    // CEK KETERSEDIAAN PESANAN DI LIBRARY
    for (const auto &l : lib) {
    if (l.id_user == id_user && l.buku.kode == ebook[pilihan].kode) {
        tampilPeringatan(42, "E-book ini sudah ada di perpustakaan Anda!");
        return;}}
 
    int pilihTindakan = 0; bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("TAMBAH E-BOOK KE KERANJANG"); cout << endl;
        lihatDetailEbook(ebook, pilihan);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Tambah E-book ke keranjang?" << RESET; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // SIMPAN
            if (pilihTindakan == 0) {
                baru.id_user = id_user;
                baru.buku = ebook[pilihan];
                keranjang.push_back(baru);
                saveKeranjang(keranjang);
                tampilPesan(24, "Berhasil masuk keranjang!");
                break;}

            // BATALKAN
            else {
                tampilPeringatan(22, "Penambahan dibatalkan!");
                break;}}}}

void checkoutDariKatalog(vector<Ebook> &ebook, vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi, vector<Keranjang> &keranjang, vector<Library> &lib) {
    string tindakan[] = {
        "【 1 | Bayar Sekarang     】",
        "【 2 | Bayar Nanti        】",
        "【 3 | Batalkan           】"};

    int pilihan = scrollBuku(ebook, "CHECKOUT E-BOOK DARI KATALOG");

    // CEK KETERSEDIAAN PESANAN DENGAN STATUS YANG AKTIF (BELUM DIBAYAR, LUNAS/DIPROSES, DIKIRIM, SELESAI)
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].id_user == akun[indeksLogin].id_user && order[i].kode == ebook[pilihan].kode && order[i].status_order != "Dibatalkan") {
            tampilPeringatan(52, "Anda sudah memiliki pesanan aktif untuk E-book ini!");
            return;}}

    // CEK KETERSEDIAAN PESANAN DI LIBRARY
    for (const auto &l : lib) {
    if (l.id_user == akun[indeksLogin].id_user && l.buku.kode == ebook[pilihan].kode) {
        tampilPeringatan(42, "E-book ini sudah ada di perpustakaan Anda!");
        return;}}

    // KONFIRMASI TINDAKAN
    int pilihTindakan = 0; bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("CHECKOUT E-BOOK DARI KATALOG"); cout << endl;
        lihatDetailEbook(ebook, pilihan);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Pilih opsi pembayaran:" << RESET; cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilihTindakan)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilihTindakan, 3);
        if (hasil == -1) {
            refreshTindakan = true;

            // BATALKAN
            if (pilihTindakan == 2) {
                tampilPeringatan(20, "Pemesanan dibatalkan!");
                break;}

            // BAYAR SEKARANG & BAYAR NANTI
            else {
                // CATAT PESANAN
                Order Baru;
                Baru.id_order       = generateID("ORD", order.size() + 1, 5);
                Baru.id_user        = akun[indeksLogin].id_user;
                Baru.kode           = ebook[pilihan].kode;
                Baru.judul          = ebook[pilihan].judul;
                Baru.harga          = ebook[pilihan].harga;
                Baru.tanggal_pesan  = tanggalWaktuSekarang();
                Baru.tanggal_kirim  = "";
                Baru.tanggal_sampai = "";
                Baru.batal_oleh     = "";
                Baru.alasan         = "";

                // BAYAR SEKARANG
                if (pilihTindakan == 0) {
                    // SALDO TERNYATA TIDAK CUKUP
                    if (akun[indeksLogin].saldo < ebook[pilihan].harga) {
                        tampilPeringatan(52, "Saldo tidak mencukupi! Bayar nanti atau top up saldo.");
                        continue;}

                    // SALDO ADMIN BERTAMBAH, SALDO USER BERKURANG
                    akun[indeksLogin].saldo -= ebook[pilihan].harga;
                    for (auto &a : akun) {
                        if (a.role == "Admin") {
                            a.saldo += ebook[pilihan].harga;
                            break;}}

                    // DETAIL PESANAN DIPERBARUI
                    Baru.status_order = "Diproses";
                    Baru.status_bayar = "Lunas";
                    Baru.tanggal_bayar = tanggalWaktuSekarang();
                    order.push_back(Baru);

                    // HAPUS E-BOOKNYA DARI KERANJANG (KALAU ADA)
                    for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                        if (it->id_user == akun[indeksLogin].id_user && it->buku.kode == ebook[pilihan].kode) {
                            it = keranjang.erase(it);}
                        else {
                            ++it;}}

                    // CATAT TRANSAKSI
                    Transaksi t;
                    t.id_transaksi = generateID("TRX", transaksi.size() + 1, 6);
                    t.id_user = akun[indeksLogin].id_user;
                    t.id_order = Baru.id_order;
                    t.nominal = Baru.harga;
                    t.tanggal_transaksi = tanggalWaktuSekarang();
                    t.jenis = "Pembayaran";
                    transaksi.push_back(t);

                    saveTransaksi(transaksi);
                    saveAkun(akun);
                    saveOrder(order);
                    saveKeranjang(keranjang);
                    tampilPesan(48, "Checkout berhasil! Pesanan sedang diproses admin.");
                    break;}
                
                // BAYAR NANTI
                else if (pilihTindakan == 1) {
                    // DETAIL PESANAN DIPERBARUI
                    Baru.status_order = "Ditunggu";
                    Baru.status_bayar = "Belum Bayar";
                    Baru.tanggal_bayar = "";
                    order.push_back(Baru);

                    // HAPUS E-BOOKNYA DARI KERANJANG (KALAU ADA)
                    for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                        if (it->id_user == akun[indeksLogin].id_user && it->buku.kode == ebook[pilihan].kode) {
                            it = keranjang.erase(it);}
                        else {
                            ++it;}}

                    saveOrder(order);
                    saveKeranjang(keranjang);
                    tampilPesan(52, "Pesanan disimpan! Bayar melalui menu Daftar Pesanan.");
                    break;}}}}}


/*  MENU KERANJANG                                                                                 */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void lihatPesananUser(string jenis, vector<Order> &order, string id_user) {
    // CEK KETERSEDIAAN PESANAN
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
        return;}
    bool ada = false;
    for (const auto &o : order) {
        if (jenis == "Belum Bayar") {
            if (o.id_user == id_user && o.status_bayar == jenis && o.status_order == "Ditunggu") {
                ada = true;
                break;}}
        else if (jenis == "Diproses") {
            if (o.id_user == id_user && o.status_order == "Diproses") {
                ada = true;
                break;}}
        else if (jenis == "Dikirim") {
            if (o.id_user == id_user && o.status_order == "Dikirim") {
                ada = true;
                break;}}
        else if (jenis == "Selesai") {
            if (o.id_user == id_user && o.status_order == "Selesai") {
                ada = true;
                break;}}
        else {     
            if (o.id_user == id_user && o.status_order == "Dibatalkan") {
                ada = true;
                break;}}}
    if (!ada) {
        tampilPeringatan(40, "Belum ada pesanan dengan status tersebut!");
        return;}

    // DAFTAR PESANAN (BELUM BAYAR, DIPROSES, DIBATALKAN)
    if (jenis == "Belum Bayar" || jenis == "Diproses" || jenis == "Dibatalkan") {
        cout << CYAN << BOLD;
        cout << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << "│                                                              DAFTAR PESANAN                                                              │" << endl;
        cout << "├──────┬─────────────┬─────────────────────────────┬─────────────────────────┬────────────┬────────────────────────┬───────────────────────┤" << endl;
        cout << "│ NO   │ ID ORDER    │ JUDUL                       │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN          │ STATUS                │" << endl;
        cout << "├──────┼─────────────┼─────────────────────────────┼─────────────────────────┼────────────┼────────────────────────┼───────────────────────┤" << endl;
        cout << RESET;
        int no = 1;
        for (const auto &o : order) {
            bool tampil = false;
            if (jenis == "Belum Bayar") {
                tampil = (o.id_user == id_user && o.status_bayar == "Belum Bayar" && o.status_order == "Ditunggu");}
            else if (jenis == "Diproses") {
                tampil = (o.id_user == id_user && o.status_order == "Diproses");}
            else {
                tampil = (o.id_user == id_user && o.status_order == "Dibatalkan");}
            if (tampil) {
                if (no % 2 == 0) cout << BG_ABU;
                cout << "│ " << left << setw(5) << no++
                    << "│ " << setw(12) << o.id_order
                    << "│ " << setw(28) << o.judul
                    << "│ " << setw(24) << o.kode
                    << "│ " << setw(11) << o.harga
                    << "│ " << setw(23) << o.tanggal_pesan << "│ ";
                if (o.status_bayar == "Belum Bayar" && o.status_order == "Ditunggu")
                    cout << MERAH << BOLD << setw(22) << o.status_bayar << RESET;
                else if (o.status_bayar == "Lunas" && o.status_order == "Diproses")
                    cout << HIJAU << BOLD << setw(22) << o.status_bayar << RESET;
                else
                    cout << MERAH << BOLD << setw(12) << o.status_order << " (" << setw(6) << o.batal_oleh << ") " << RESET;
                cout << "│" << RESET << endl;}}
        cout << CYAN;
        cout << "└──────┴─────────────┴─────────────────────────────┴─────────────────────────┴────────────┴────────────────────────┴───────────────────────┘" << endl;
        cout << RESET << endl;}

    // DAFTAR PESANAN (DIKIRIM)
    else if (jenis == "Dikirim") {
        cout << CYAN << BOLD;
        cout << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << "│                                                              DAFTAR PESANAN                                                              │" << endl;
        cout << "├──────┬──────────────┬─────────────────────────────┬─────────────────────────┬────────────┬───────────────────────┬───────────────────────┤" << endl;
        cout << "│ NO   │ ID ORDER     │ JUDUL                       │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN         │ TANGGAL KIRIM         │" << endl;
        cout << "├──────┼──────────────┼─────────────────────────────┼─────────────────────────┼────────────┼───────────────────────┼───────────────────────┤" << endl;
        cout << RESET;
        int no = 1;
        for (const auto &o : order) {
            if (o.id_user == id_user && o.status_order == "Dikirim") {
                if (no % 2 == 0) cout << BG_ABU;
                cout << "│ " << left << setw(5) << no++
                    << "│ " << setw(13) << o.id_order
                    << "│ " << setw(28) << o.judul
                    << "│ " << setw(24) << o.kode
                    << "│ " << setw(11) << o.harga
                    << "│ " << setw(22) << o.tanggal_pesan
                    << "│ " << setw(22) << o.tanggal_kirim;
                cout << "│" << RESET << endl;}}
        cout << CYAN;
        cout << "└──────┴──────────────┴─────────────────────────────┴─────────────────────────┴────────────┴───────────────────────┴───────────────────────┘" << endl;
        cout << RESET << endl;}

    // DAFTAR PESANAN (SELESAI)
    else {
        cout << CYAN << BOLD;
        cout << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
        cout << "│                                                              DAFTAR PESANAN                                                              │" << endl;
        cout << "├──────┬──────────────┬─────────────────────────────┬─────────────────────────┬────────────┬───────────────────────┬───────────────────────┤" << endl;
        cout << "│ NO   │ ID ORDER     │ JUDUL                       │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN         │ TANGGAL TERIMA        │" << endl;
        cout << "├──────┼──────────────┼─────────────────────────────┼─────────────────────────┼────────────┼───────────────────────┼───────────────────────┤" << endl;
        cout << RESET;
        int no = 1;
        for (const auto &o : order) {
            if (o.id_user == id_user && o.status_order == "Selesai") {
                if (no % 2 == 0) cout << BG_ABU;
                cout << "│ " << left << setw(5) << no++
                    << "│ " << setw(13) << o.id_order
                    << "│ " << setw(28) << o.judul
                    << "│ " << setw(24) << o.kode
                    << "│ " << setw(11) << o.harga
                    << "│ " << setw(22) << o.tanggal_pesan
                    << "│ " << setw(22) << o.tanggal_sampai;
                cout << "│" << RESET << endl;}}
        cout << CYAN;
        cout << "└──────┴──────────────┴─────────────────────────────┴─────────────────────────┴────────────┴───────────────────────┴───────────────────────┘" << endl;
        cout << RESET << endl;}}

void lihatDaftarKeranjang(vector<Keranjang> &keranjang, string id_user) {
    // CEK KETERSEDIAAN KERANJANG
    if (keranjang.empty()) {
        tampilPeringatan(22, "Keranjang belum terisi!");
        return;}
    bool ada = false;
    for (const auto &k : keranjang) {
        if (k.id_user == id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(22, "Keranjang anda kosong!");
        return;}

    // DAFTAR KERANJANG
    cout << CYAN << BOLD;
    cout << spasi(21) << "┌────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(21) << "│                                        KERANJANG BELANJA                                       │" << endl;
    cout << spasi(21) << "├──────┬───────────────────────────┬───────────────────────────────────────────┬─────────────────┤" << endl;
    cout << spasi(21) << "│ NO   │ KODE E-BOOK               │ JUDUL                                     │ HARGA           │" << endl;
    cout << spasi(21) << "├──────┼───────────────────────────┼───────────────────────────────────────────┼─────────────────┤" << endl;
    cout << RESET;
    int no = 1, total = 0;
    for (const auto &k : keranjang) {
        if (k.id_user == id_user) {
            cout << spasi(21);
            if (no % 2 == 0) cout << BG_ABU;
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
    // CEK KETERSEDIAAN KERANJANG
    if (keranjang.empty()) {
        tampilPeringatan(22, "Keranjang belum terisi!");
        return;}
    bool ada = false;
    for (const auto &k : keranjang) {
        if (k.id_user == id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(22, "Keranjang anda kosong!");
        return;}
    
    // HAPUS E-BOOK DARI KERANJANG
    string tindakan[] = {
        "【 1 | Hapus         】",
        "【 2 | Batalkan      】"};

    int pilihan = scrollKeranjang(keranjang, "HAPUS E-BOOK DARI KERANJANG", id_user);

    int pilihTindakan = 0; bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("HAPUS E-BOOK DARI KERANJANG"); cout << endl;
        int indeksEbook = -1;
        for (size_t i = 0; i < ebook.size(); i++) {
            if (ebook[i].kode == keranjang[pilihan].buku.kode) {
                indeksEbook = i;
                break;}}
        lihatDetailEbook(ebook, indeksEbook);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Hapus E-book ini dari keranjang?" << RESET; cout << endl;
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
                saveKeranjang(keranjang);
                tampilPesan(38, "E-book berhasil dihapus dari keranjang!");
                break;}

            // BATALKAN
            else {
                tampilPeringatan(22, "Penghapusan dibatalkan!");
                break;}}}}

void checkoutDariKeranjang(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    // CEK KETERSEDIAAN KERANJANG
    if (keranjang.empty()) {
        tampilPeringatan(22, "Keranjang belum terisi!");
        return;}
    bool ada = false;
    for (const auto &k : keranjang) {
        if (k.id_user == akun[indeksLogin].id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(22, "Keranjang anda kosong!");
        return;}
    
    // CHECKOUT DARI KERANJANG
    string jenis[] = {
        "『 1 | Checkout Semua     』",
        "『 2 | Pilih Satu E-Book  』",
        "【 3 | Kembali            】"};
    string tindakan[] = {
        "【 1 | Bayar Sekarang     】",
        "【 2 | Bayar Nanti        】",
        "【 3 | Batal              】"};

    int pilihJenis = 0; bool refreshJenis = true;
    while (true) {
        if (refreshJenis) {
            system("cls"); refreshJenis = false;}
        clsScroll(0,0); judul_subjudul("CHECKOUT E-BOOK DARI KERANJANG"); cout << endl;
        lihatDaftarKeranjang(keranjang, akun[indeksLogin].id_user);
        cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
        cout << endl << spasi(34) << BOLD << KUNING << "Checkout semua atau pilih salah satu?" << RESET; cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilihJenis)
                cout << spasi(39) << BG_PUTIH << HITAM << BOLD << jenis[i] << RESET << endl;
            else cout << DIM << spasi(39) << jenis[i] << RESET << endl;}
        int hasilJenis = scrollMenu(pilihJenis, 3);
        if (hasilJenis == -1) {
            refreshJenis = true;

            // KEMBALI
            if (pilihJenis == 2) {
                break;}

            // CHECKOUT SEMUA & PILIH SATU E-BOOK
            else {
                // SIMPAN ITEM YANG AKAN DI-CHECKOUT
                vector<Keranjang> itemDipesan;
                if (pilihJenis == 0) {
                    for (const auto& k : keranjang) {
                        if (k.id_user == akun[indeksLogin].id_user) {
                            itemDipesan.push_back(k);}}}
                else {
                    int pilihanIndeks = scrollKeranjang(keranjang, "PILIH E-BOOK", akun[indeksLogin].id_user);
                    if (pilihanIndeks == -1) {
                        continue;}
                    itemDipesan.push_back(keranjang[pilihanIndeks]);}

                // KONFIRMASI TINDAKAN
                int pilihTindakan = 0; bool refreshTindakan = true;
                while (true) {
                    if (refreshTindakan) {
                        system("cls"); refreshTindakan = false;}
                    clsScroll(0,0); judul_subjudul("CHECKOUT E-BOOK DARI KERANJANG"); cout << endl;
                
                    // TAMPILKAN DETAIL E-BOOK YANG AKAN DI-CHECKOUT
                    if (itemDipesan.size() == 1) {
                        int idxEbook = -1;
                        for (size_t i = 0; i < ebook.size(); i++) {
                            if (ebook[i].kode == itemDipesan[0].buku.kode) {
                                idxEbook = i;
                                break;}}
                        if (idxEbook != -1) {
                            lihatDetailEbook(ebook, idxEbook);}
                        else {
                            tampilPeringatan(34, "E-Book telah dihapus dari katalog!");}}
                    else {
                        for (size_t i = 0; i < itemDipesan.size(); i++) {
                            int idxEbook = -1;
                            for (size_t j = 0; j < ebook.size(); j++) {
                                if (ebook[j].kode == itemDipesan[i].buku.kode) {
                                    idxEbook = j;
                                    break;}}
                            if (idxEbook != -1) {
                                lihatDetailEbook(ebook, idxEbook);}
                            else {
                                tampilPeringatan(34, "E-Book [" + itemDipesan[i].buku.judul + "] telah dihapus dari katalog!");}}}

                    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                    cout << endl << spasi(34) << BOLD << KUNING << "Pilih opsi pembayaran:" << RESET; cout << endl;
                    for (int i = 0; i < 3; i++) {
                        if (i == pilihTindakan) cout << spasi(39) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
                        else cout << DIM << spasi(39) << tindakan[i] << RESET << endl;}
                    int hasilTindakan = scrollMenu(pilihTindakan, 3);
                    if (hasilTindakan == -1) {
                        refreshTindakan = true;

                        // BATALKAN
                        if (pilihTindakan == 2) {
                            tampilPeringatan(20, "Pemesanan dibatalkan.");
                            break;}

                        // BAYAR SEKARANG & BAYAR NANTI
                        else {
                            // CHECKOUT SEMUA & BAYAR SEKARANG
                            if (pilihJenis == 0 && pilihTindakan == 0) {
                                int totalHarga = 0;
                                for (auto &item : itemDipesan) {
                                    totalHarga += item.buku.harga;}
                                if (akun[indeksLogin].saldo < totalHarga) {
                                    tampilPeringatan(53, "Saldo tidak mencukupi! Bayar nanti atau top up saldo.");
                                    break;}}

                            for (auto &item : itemDipesan) {
                                // CATAT PESANAN
                                Order Baru;
                                Baru.id_order       = generateID("ORD", order.size() + 1, 5);
                                Baru.id_user        = akun[indeksLogin].id_user;
                                Baru.kode           = item.buku.kode;
                                Baru.judul          = item.buku.judul;
                                Baru.harga          = item.buku.harga;
                                Baru.tanggal_pesan  = tanggalWaktuSekarang();
                                Baru.tanggal_kirim  = "";
                                Baru.tanggal_sampai = "";
                                Baru.batal_oleh     = "";
                                Baru.alasan         = "";

                                // BAYAR SEKARANG
                                if (pilihTindakan == 0) {
                                    // DETAIL PESANAN DIPERBARUI
                                    Baru.status_order  = "Diproses";
                                    Baru.status_bayar  = "Lunas";
                                    Baru.tanggal_bayar = tanggalWaktuSekarang();

                                    // SALDO ADMIN BERTAMBAH, SALDO USER BERKURANG
                                    akun[indeksLogin].saldo -= item.buku.harga;
                                    for (auto &a : akun) {
                                        if (a.role == "Admin") {
                                            a.saldo += item.buku.harga;
                                            break;}}

                                    // CATAT TRANSAKSI
                                    Transaksi t;
                                    t.id_transaksi      = generateID("TRX", transaksi.size() + 1, 6);
                                    t.id_user           = akun[indeksLogin].id_user;
                                    t.id_order          = Baru.id_order;
                                    t.nominal           = item.buku.harga;
                                    t.tanggal_transaksi = tanggalWaktuSekarang();
                                    t.jenis             = "Pembayaran";
                                    transaksi.push_back(t);}

                                else {
                                    // DETAIL PESANAN DIPERBARUI
                                    Baru.status_order  = "Ditunggu";
                                    Baru.status_bayar  = "Belum Bayar";
                                    Baru.tanggal_bayar = "";}

                                order.push_back(Baru);

                                // HAPUS E-BOOKNYA DARI KERANJANG
                                for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                                    if (it->buku.kode == item.buku.kode && it->id_user == Baru.id_user) {
                                        it = keranjang.erase(it);}
                                    else {
                                        ++it;}}}

                            saveOrder(order);
                            saveAkun(akun);
                            saveKeranjang(keranjang);
                            saveTransaksi(transaksi);
                            if (pilihTindakan == 0) {
                                tampilPesan(48, "Checkout berhasil! Pesanan sedang diproses admin.");}
                            else {
                                tampilPesan(52, "Pesanan disimpan! Bayar melalui menu Daftar Pesanan.");}
                            break;}}}
                break;}}}}


/*  MENU PESANAN                                                                                   */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void pesananBelumDibayar(vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    string tindakan[] = {
        "【 1 | Bayar Sekarang     】",
        "【 2 | Batalkan Pesanan   】",
        "【 3 | Kembali            】"};
    string konfirmasi[] = {
        "【 1 | Yakin              】",
        "【 2 | Batalkan           】"};

    int pilih = 0; bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("DAFTAR PESANAN BELUM DIBAYAR"); cout << endl;

        // CEK KETERSEDIAAN PESANAN   
        bool ada = false;
        for (const auto &o : order) {
            if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Ditunggu") {
                ada = true;
                break;}}
        if (!ada) {
            tampilPeringatan(38, "Tidak ada pesanan yang belum dibayar!"); system("pause");
            return;}

        // UBAH STATUS PESANAN (TINDAKAN)
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(35) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(35) << tindakan[i] << RESET << endl;}
        cout << endl; lihatPesananUser("Belum Bayar", order, akun[indeksLogin].id_user);
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refreshTindakan = true;

            // BAYAR SEKARANG         
            if (pilih == 0) {

                int pilihan = scrollOrder(order, "DAFTAR PESANAN BELUM DIBAYAR", "Ditunggu", akun[indeksLogin].id_user);
                
                // KONFIRMASI PEMBAYARAN
                int pilihKonfirmasi = 0; bool refreshKonfirmasi = true;
                while (true) {
                    if (refreshKonfirmasi) {
                        system("cls"); refreshKonfirmasi = false;}
                    clsScroll(0,0); judul_subjudul("BAYAR PESANAN"); cout << endl;
                    lihatDetailOrder(order, pilihan, "User", "Ditunggu");
                    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                    cout << endl << spasi(34) << BOLD << KUNING << "Yakin ingin melakukan pembayaran?" << RESET; cout << endl;
                    for (int i = 0; i < 2; i++) {
                        if (i == pilihKonfirmasi)
                            cout << spasi(39) << BG_PUTIH << HITAM << BOLD << konfirmasi[i] << RESET << endl;
                        else cout << DIM << spasi(39) << konfirmasi[i] << RESET << endl;}
                    int hasil2 = scrollMenu(pilihKonfirmasi, 2);
                    if (hasil2 == -1) {
                        refreshKonfirmasi = true;

                        // KONFIRMASI "YAKIN"
                        if (pilihKonfirmasi == 0) {
                            // SALDO CUKUP, SALDO ADMIN BERTAMBAH, SALDO USER BERKURANG
                            if (akun[indeksLogin].saldo >= order[pilihan].harga) {
                                akun[indeksLogin].saldo -= order[pilihan].harga;
                                for (size_t i = 0; i < akun.size(); i++) {
                                    if (akun[i].role == "Admin") {
                                        akun[i].saldo += order[pilihan].harga;
                                        break;}}

                                // DETAIL PESANAN DIPERBARUI
                                order[pilihan].status_bayar = "Lunas";
                                order[pilihan].status_order = "Diproses";
                                order[pilihan].tanggal_bayar = tanggalWaktuSekarang();

                                // CATAT TRANSAKSI
                                Transaksi t;
                                t.id_transaksi = generateID("TRX", transaksi.size() + 1, 6);
                                t.id_user = akun[indeksLogin].id_user;
                                t.id_order = order[pilihan].id_order;
                                t.nominal = order[pilihan].harga;
                                t.tanggal_transaksi = tanggalWaktuSekarang();
                                t.jenis = "Pembayaran";
                                transaksi.push_back(t);

                                saveTransaksi(transaksi);
                                saveAkun(akun);
                                saveOrder(order);
                                tampilPesan(50, "Pembayaran Berhasil! Pesanan sedang diproses admin."); system("pause");
                                break;}
                            // SALDO TIDAK CUKUP
                            else {
                                tampilPeringatan(32, "Saldo anda masih tidak mencukupi!"); system("pause");
                                break;}}

                        // KONFIRMASI "BATALKAN"
                        else {
                            tampilPeringatan(22, "Pembayaran dibatalkan."); system("pause");
                            break;}}}}

            // BATALKAN PESANAN
            else if (pilih == 1) {

                int pilihan = scrollOrder(order, "BATALKAN PESANAN BELUM DIBAYAR", "Ditunggu", akun[indeksLogin].id_user);

                string alasan;
                system("cls"); judul_subjudul("BATALKAN PESANAN BELUM DIBAYAR"); cout << endl;
                lihatDetailOrder(order, pilihan, "User", "Ditunggu");
                cin.ignore(1000, '\n');
                cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                cout << spasi(47) << BOLD << "Alasan : " << RESET; getline(cin, alasan);
                cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                if (alasan.empty()) {
                    tampilPeringatan(26, "Alasan tidak boleh kosong!"); system("pause");
                    continue;}

                // KONFIRMASI PEMBATALAN
                int pilihKonfirmasi = 0; bool refreshKonfirmasi = true;
                while (true) {
                    if (refreshKonfirmasi) {
                        system("cls"); refreshKonfirmasi = false;}
                    clsScroll(0,0); judul_subjudul("BATALKAN PESANAN BELUM DIBAYAR"); cout << endl;
                    lihatDetailOrder(order, pilihan, "User", "Ditunggu");
                    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                    cout << spasi(47) << BOLD << "Alasan : " << RESET << alasan << endl;
                    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl << endl;
                    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                    cout << endl << spasi(34) << BOLD << KUNING << "Yakin ingin membatalkan?" << RESET; cout << endl;
                    for (int i = 0; i < 2; i++) {
                        if (i == pilihKonfirmasi)
                            cout << spasi(39) << BG_PUTIH << HITAM << BOLD << konfirmasi[i] << RESET << endl;
                        else cout << DIM << spasi(39) << konfirmasi[i] << RESET << endl;}
                    int hasil2 = scrollMenu(pilihKonfirmasi, 2);
                    if (hasil2 == -1) {
                        refreshKonfirmasi = true;

                        // KONFIRMASI "YAKIN"
                        if (pilihKonfirmasi == 0) {
                            // DETAIL PESANAN DIPERBARUI
                            order[pilihan].status_order = "Dibatalkan";
                            order[pilihan].status_bayar = "Belum Bayar";
                            order[pilihan].batal_oleh = "User";
                            order[pilihan].alasan = alasan;
                            saveOrder(order);
                            tampilPesan(18, "Pesanan Dibatalkan!"); system("pause");
                            break;}

                        // KONFIRMASI "BATALKAN"
                        else {
                            tampilPeringatan(22, "Pembatalan dibatalkan."); system("pause");
                            break;}}}}

            // KEMBALI
            else {
                break;}}}}

void pesananDiproses(vector<Akun> &akun, vector<Order> &order, int indeksLogin, vector<Transaksi> &transaksi) {
    string tindakan[] = {
        "【 1 | Batalkan Pesanan   】",
        "【 2 | Kembali            】"};
    string konfirmasi[] = {
        "【 1 | Yakin              】",
        "【 2 | Batalkan           】"};

    int pilih = 0;  bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("DAFTAR PESANAN DIPROSES"); cout << endl;

        // CEK KETERSEDIAAN PESANAN   
        bool ada = false;
        for (const auto &o : order) {
            if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Diproses") {
                ada = true;
                break;}}
        if (!ada) {
            tampilPeringatan(34, "Belum ada daftar pesanan diproses!"); system("pause");
            return;}

        // UBAH STATUS PESANAN (TINDAKAN)
        for (int i = 0; i < 2; i++) {
            if (i == pilih)
                cout << spasi(35) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(35) << tindakan[i] << RESET << endl;}
        cout << endl; lihatPesananUser("Diproses", order, akun[indeksLogin].id_user);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refreshTindakan = true;

            // BATALKAN PESANAN  
            if (pilih == 0) {

                int pilihan = scrollOrder(order, "BATALKAN PESANAN DIPROSES", "Diproses", akun[indeksLogin].id_user);

                string alasan;
                system("cls"); judul_subjudul("BATALKAN PESANAN DIPROSES"); cout << endl;
                lihatDetailOrder(order, pilihan, "User", "Diproses");
                cin.ignore(1000, '\n');
                cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                cout << spasi(47) << BOLD << "Alasan : " << RESET; getline(cin, alasan);
                cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                if (alasan.empty()) {
                    tampilPeringatan(26, "Alasan tidak boleh kosong!"); system("pause");
                    continue;}

                // KONFIRMASI PEMBATALAN
                int pilihKonfirmasi = 0; bool refreshKonfirmasi = true;
                while (true) {
                    if (refreshKonfirmasi) {
                        system("cls"); refreshKonfirmasi = false;}
                    clsScroll(0,0); judul_subjudul("BATALKAN PESANAN DIPROSES"); cout << endl;
                    lihatDetailOrder(order, pilihan, "User", "Diproses");
                    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                    cout << spasi(47) << BOLD << "Alasan : " << RESET << alasan << endl;
                    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl << endl;
                    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                    cout << endl << spasi(34) << BOLD << KUNING << "Yakin ingin membatalkan?" << RESET; cout << endl;
                    for (int i = 0; i < 2; i++) {
                        if (i == pilihKonfirmasi)
                            cout << spasi(39) << BG_PUTIH << HITAM << BOLD << konfirmasi[i] << RESET << endl;
                        else cout << DIM << spasi(39) << konfirmasi[i] << RESET << endl;}
                    int hasil2 = scrollMenu(pilihKonfirmasi, 2);
                    if (hasil2 == -1) {
                        refreshKonfirmasi = true;

                        // KONFIRMASI "YAKIN"
                        if (pilihKonfirmasi == 0) {
                            //SALDO ADMIN BERKURANG, SALDO USER BERTAMBAH
                            akun[indeksLogin].saldo += order[pilihan].harga;
                            for (size_t i = 0; i < akun.size(); i++) {
                                if (akun[i].role == "Admin") {
                                    akun[i].saldo -= order[pilihan].harga;
                                    break;}}

                            // DETAIL PESANAN DIPERBARUI
                            order[pilihan].status_order = "Dibatalkan";
                            order[pilihan].status_bayar = "Dana Dikembalikan";
                            order[pilihan].batal_oleh = "User";
                            order[pilihan].alasan = alasan;

                            // CATAT TRANSAKSI
                            Transaksi t;
                            t.id_transaksi = generateID("TRX", transaksi.size() + 1, 6);
                            t.id_user = akun[indeksLogin].id_user;
                            t.id_order = order[pilihan].id_order;
                            t.nominal = order[pilihan].harga;
                            t.tanggal_transaksi = tanggalWaktuSekarang();
                            t.jenis = "Pengembalian";
                            transaksi.push_back(t);

                            saveTransaksi(transaksi);
                            saveOrder(order);
                            saveAkun(akun);
                            tampilPesan(44, "Pesanan dibatalkan. Dana telah dikembalikan!"); system("pause");
                            break;}

                        // KONFIRMASI "BATALKAN"
                        else {
                            tampilPeringatan(22, "Pembatalan dibatalkan."); system("pause");
                            break;}}}}

            // KEMBALI
            else {
                break;}}}}

void pesananDikirim(vector<Order> &order, vector<Akun> &akun, vector<Library> &lib, vector<Ebook> &ebook, int indeksLogin, string username) {
    string tindakan[] = {
        "『 1 | Pesanan Diterima   』",
        "『 2 | Kembali            』"};
    string konfirmasi[] = {
        "【 1 | Yakin              】",
        "【 2 | Batalkan           】"};

    int pilih = 0;  bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("DAFTAR PESANAN DIKIRIM"); cout << endl;

        // CEK KETERSEDIAAN PESANAN  
        bool ada = false;;
        for (const auto &o : order) {
            if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Dikirim") {
                ada = true;
                break;}}
        if (!ada) {
            tampilPeringatan(32, "Belum ada daftar pesanan dikirim!");  system("pause");
            return;}

        // UBAH STATUS PESANAN (TINDAKAN)
        for (int i = 0; i < 2; i++) {
            if (i == pilih)
                cout << spasi(35) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(35) << tindakan[i] << RESET << endl;}
        cout << endl; lihatPesananUser("Dikirim", order, akun[indeksLogin].id_user);
        int hasilMenu = scrollMenu(pilih, 2);
        if (hasilMenu == -1) {
            refreshTindakan = true;

            // TERIMA PESANAN
            if (pilih == 0) { 
                
                int pilihan = scrollOrder(order, "TERIMA PESANAN", "Dikirim", akun[indeksLogin].id_user);

                // KONFIRMASI PEMBATALAN
                int pilihKonfirmasi = 0; bool refreshKonfirmasi = true;
                while (true) {
                    if (refreshKonfirmasi) {
                        system("cls"); refreshKonfirmasi = false;}
                    clsScroll(0,0); judul_subjudul("TERIMA PESANAN"); cout << endl;
                    lihatDetailOrder(order, pilihan, "User", "Dikirim");
                    cout << spasi(34) << "════════════════════════════════════════════════════════════════════════" << endl;
                    cout << endl << spasi(34) << BOLD << KUNING << "Yakin pesanan diterima?" << RESET; cout << endl;
                    for (int i = 0; i < 2; i++) {
                        if (i == pilihKonfirmasi)
                            cout << spasi(39) << BG_PUTIH << HITAM << BOLD << konfirmasi[i] << RESET << endl;
                        else cout << DIM << spasi(39) << konfirmasi[i] << RESET << endl;}
                    int hasil2 = scrollMenu(pilihKonfirmasi, 2);
                    if (hasil2 == -1) {
                        refreshKonfirmasi = true;

                        // KONFIRMASI "YAKIN"
                        if (pilihKonfirmasi == 0) {
                            // DETAIL PESANAN DIPERBARUI
                            order[pilihan].tanggal_sampai = tanggalWaktuSekarang();
                            order[pilihan].status_order = "Selesai";

                            // TAMBAHKAN E-BOOK KE LIBRARY
                            Library lBaru;
                            lBaru.id_user    = akun[indeksLogin].id_user;
                            lBaru.username   = username;
                            bool ebookDitemukan = false;
                            for (size_t i = 0; i < ebook.size(); i++) {
                                if (ebook[i].kode == order[pilihan].kode) {
                                    lBaru.buku = ebook[i];
                                    ebookDitemukan = true;
                                    break;}}
                            if (!ebookDitemukan) {
                                lBaru.buku.kode  = order[pilihan].kode;
                                lBaru.buku.judul = order[pilihan].judul;
                                lBaru.buku.harga = order[pilihan].harga;
                                lBaru.buku.no    = 0;
                                lBaru.buku.penulis = "-";
                                lBaru.buku.genre   = "-";
                                lBaru.buku.tahun   = 0;}
                            lib.push_back(lBaru);

                            saveLibrary(lib);
                            saveOrder(order);
                            tampilPesan(46, "Pesanan Selesai! E-Book ditambahkan ke Library."); system("pause");
                            break;}

                        // KONFIRMASI "BATALKAN"
                        else {
                            tampilPeringatan(22, "Penerimaan dibatalkan."); system("pause");
                            break;}}}}

            // KEMBALI
            else {
                break;}}}}

void pesananSelesai(vector<Akun> &akun, vector<Order> &order, int indeksLogin) {
    // CEK KETERSEDIAAN PEMBELIAN
    bool ada = false;
    for (const auto &o : order) {
        if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Selesai") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(32, "Belum ada daftar pesanan selesai!"); system("pause");
        return;}

    // PESANAN SELESAI
    string pilihMenuUser[] = {
        "『  📋 Lihat Detail Pesanan Selesai 』",
        "『 ↩   Kembali                      』"};

    int pilih = 0; bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("DAFTAR PESANAN SELESAI"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih)
                cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuUser + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuUser + i) << RESET << endl;}
        cout << endl; lihatPesananUser("Selesai", order, akun[indeksLogin].id_user);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;
    
            /* a. LIHAT DETAIL DATA PESANAN SELESAI
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("LIHAT DETAIL PESANAN SELESAI"); cout << endl;
                int pilihan = scrollOrder(order, "LIHAT DETAIL PESANAN SELESAI", "Selesai", akun[indeksLogin].id_user);
                system("cls"); judul_subjudul("LIHAT DETAIL PESANAN SELESAI"); cout << endl;
                lihatDetailOrder(order, pilihan, "User", "Selesai");
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pesananDibatalkan(vector<Akun> &akun, vector<Order> &order, int indeksLogin) {
    // CEK KETERSEDIAAN PEMBELIAN
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!"); system("pause");
        return;}
    bool ada = false;
    for (const auto &o : order) {
        if (o.id_user == akun[indeksLogin].id_user && o.status_order == "Dibatalkan") {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(36, "Belum ada daftar pesanan dibatalkan!"); system("pause");
        return;}

    // PESANAN DIBATALKAN
    string pilihMenuUser[] = {
        "『  📋 Lihat Detail Pesanan Dibatalkan 』",
        "『 ↩   Kembali                         』"};

    int pilih = 0; bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("DAFTAR PESANAN DIBATALKAN"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuUser + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuUser + i) << RESET << endl;}
        cout << endl; lihatPesananUser("Dibatalkan", order, akun[indeksLogin].id_user);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;
    
            /* a. LIHAT DETAIL DATA PESANAN DIBATALKAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("LIHAT DETAIL PESANAN DIBATALKAN"); cout << endl;
                int pilihan = scrollOrder(order, "LIHAT DETAIL PESANAN DIBATALKAN", "Dibatalkan", akun[indeksLogin].id_user);
                system("cls"); judul_subjudul("LIHAT DETAIL PESANAN DIBATALKAN"); cout << endl;
                lihatDetailOrder(order, pilihan, "User", "Dibatalkan");
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}


/*  MENU SALDO DAN TRANSAKSI                                                                       */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void editSaldo(vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    string inputNominal;
    string tindakan[] = {
        "【 1 | Simpan        】",
        "【 2 | Batalkan      】"};

    system("cls"); judul_subjudul("TOP UP SALDO"); cout << endl;
    cout << HIJAU << BOLD << spasi(56) << "┌──────────────────────────┐" << RESET << endl;
    cout << spasi(58) << HIJAU << BOLD << BG_HIJAU << "  Saldo: " << akun[indeksLogin].saldo << " " << RESET << endl;
    cout << HIJAU << BOLD << spasi(56) << "└──────────────────────────┘" << RESET << endl;
    cout << endl;
    cout << spasi(54) << "┌──────────────────────────────┐" << RESET << endl;
    cout << spasi(56) << BOLD << "Nominal Top Up: Rp" << RESET; cin >> inputNominal;
    cout << spasi(54) << "└──────────────────────────────┘" << RESET << endl;

    // VALIDASI INPUT NOMINAL TOP UP
    for (char c : inputNominal) {
        if (!isdigit(c)) {
            tampilPeringatan(36, "Nominal harus berupa angka dan jelas!");
            return;}}
    int nominal;
    try {
        nominal = stoi(inputNominal);}
    catch (...) {
        tampilPeringatan("Nominal terlalu besar!");
        return;}
    if (nominal < 10000 || nominal > 1000000) {
        tampilPeringatan("Top Up minimal Rp10.000 dan maksimal Rp1.000.000");
        return;}

    // KONFIRMASI TINDAKAN
    int pilihTindakan = 0; bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("TOP UP SALDO"); cout << endl;
        cout << HIJAU << BOLD << spasi(56) << "┌──────────────────────────┐" << RESET << endl;
        cout << spasi(58) << HIJAU << BOLD << BG_HIJAU << "  Saldo: " << akun[indeksLogin].saldo << " " << RESET << endl;
        cout << HIJAU << BOLD << spasi(56) << "└──────────────────────────┘" << RESET << endl;
        cout << endl;
        cout << spasi(54) << "┌──────────────────────────────┐" << RESET << endl;
        cout << spasi(56) << BOLD << "Nominal Top Up: Rp" << RESET << nominal << endl;
        cout << spasi(54) << "└──────────────────────────────┘" << RESET << endl;
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
                // TERNYATA SALDO USER SUDAH MAKSIMAL
                if (akun[indeksLogin].saldo + nominal > 5000000) {
                    tampilPeringatan(32, "Batas maksimum saldo Rp5.000.000!");
                    break;}
                // SALDO USER DITAMBAH
                akun[indeksLogin].saldo += (int)nominal;

                // CATAT TRANSAKSI
                Transaksi t;
                t.id_transaksi = generateID("TRX", transaksi.size() + 1, 6);
                t.id_user = akun[indeksLogin].id_user;
                t.id_order = "-";
                t.nominal = nominal;
                t.tanggal_transaksi = tanggalWaktuSekarang();
                t.jenis = "Isi Saldo";
                transaksi.push_back(t);
                saveTransaksi(transaksi);
                saveAkun(akun);

                cout << endl;
                cout << HIJAU << BOLD << spasi(56) << "┌──────────────────────────┐" << RESET << endl;
                cout << spasi(58) << HIJAU << BOLD << BG_HIJAU << "  Saldo baru : " << akun[indeksLogin].saldo << " " << RESET << endl;
                cout << HIJAU << BOLD << spasi(56) << "└──────────────────────────┘" << RESET << endl;
                tampilPesan("Top Up Berhasil!");
                break;}

            // BATALKAN
            else {
                tampilPeringatan(18, "Top Up dibatalkan!");
                break;}}}}


/*  MENU-MENU UTAMA USER                                                                           */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void kelolaAkunDiri(vector<Akun> &akun, int indeksLogin) {
    string pilihMenuUser[] = {
        "『  ✏️  Ubah Data Akun Diri        』",
        "『 ↩   Kembali                    』"};

    int pilih = 0; bool refresh = true;
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
                editDataDiri(akun, indeksLogin); system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/                
            else {
                break;}}}}

void belanjaUser(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi, vector<Library> &lib) {
    // CEK KETERSEDIAAN E-BOOK
    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi."); system("pause");
        return;}

    // MENU BELANJA    
    string pilihMenuUser[] = {
        "『  ➕ Tambah Ke Keranjang        』",
        "『  ✏️  Pesan Sekarang             』",
        "『  ↕️  Urutkan Katalog            』",
        "『  🔍 Cari E-Book                』",
        "『 ↩   Kembali                    』"};

    int pilih = 0; bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU BELANJA SEKARANG"); cout << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuUser + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuUser + i) << RESET << endl;}
        cout << endl; lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
            refresh = true;

            /* a. TAMBAH E-BOOK KE KERANJANG
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                tambahProdukkeKeranjang(ebook, keranjang, order, lib, akun[indeksLogin].id_user);
                system("pause");}

            /* b. PESAN LANGSUNG E-BOOK DARI KATALOG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                checkoutDariKatalog(ebook, order, akun, indeksLogin, transaksi, keranjang, lib);
                system("pause");}

            /* c. URUT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("URUTKAN KATALOG"); cout << endl;
                urutEbook(ebook);}

            /* d. CARI E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("CARI E-BOOK"); cout << endl;
                cariEbook(ebook);}

            /* e. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void keranjangUser(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Akun> &akun, vector<Order> &order, int indeksLogin, vector<Transaksi> &transaksi) {   
    string pilihMenuUser[] = {
        "『  ➕ Pesan Keranjang            』",
        "『  🗑️  Hapus E-Book Di Keranjang  』",
        "『 ↩   Kembali                    』"};

    int pilih = 0; bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU KERANJANG BELANJA"); cout << endl;

        // CEK KETERSEDIAAN KERANJANG
        if (keranjang.empty()) {
            tampilPeringatan(22, "Keranjang belum terisi!"); system("pause");
            return;}
        bool ada = false;
        for (const auto &k : keranjang) {
            if (k.id_user == akun[indeksLogin].id_user) {
                ada = true;
                break;}}
        if (!ada) {
            tampilPeringatan(22, "Keranjang anda kosong!"); system("pause");
            return;}

        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(34) << pilihMenuUser[i] << RESET << endl;}
        cout << endl; lihatDaftarKeranjang(keranjang, akun[indeksLogin].id_user);
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;

            /* a. CHECKOUT E-BOOK DARI KERANJANG
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("CHECKOUT E-BOOK DARI KERANJANG"); cout << endl;
                checkoutDariKeranjang(ebook, keranjang, order, akun, indeksLogin, transaksi);
                system("pause");}
            
            /* b. HAPUS E-BOOK DARI KERANJANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("HAPUS E-BOOK DARI KERANJANG"); cout << endl;
                hapusEbookDariKeranjang(ebook, keranjang, akun[indeksLogin].id_user);
                system("pause");}
            
            /* c. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pesananUser(vector<Ebook> &ebook, vector<Order> &order, vector<Akun> &akun, int indeksLogin, vector<Library> &lib, vector<Transaksi> &transaksi) {
    // CEK KETERSEDIAAN PESANAN
    if (order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!"); system("pause");
        return;}
    bool ada = false;
    for (const auto &o : order) {
        if (o.id_user == akun[indeksLogin].id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(18, "Belum ada pesanan!"); system("pause");
        return;}

    // MENU PESANAN
    string pilihMenuUser[] = {
        "『  📋 Daftar Pesanan Belum Dibayar 』",
        "『  📋 Daftar Pesanan Diproses      』",
        "『  📋 Daftar Pesanan Dikirim       』",
        "『  📋 Daftar Pesanan Selesai       』",
        "『  📋 Daftar Pesanan Dibatalkan    』",
        "『 ↩   Kembali                      』"};

    int pilih = 0; bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU DAFTAR PESANAN"); cout << endl;
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuUser + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuUser + i) << RESET << endl;}
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
            refresh = true;

            /* a. DAFTAR PESANAN BELUM DIBAYAR
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                pesananBelumDibayar(order, akun, indeksLogin, transaksi);}

            /* b. DAFTAR PESANAN DIPROSES
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                pesananDiproses(akun, order, indeksLogin, transaksi);}

            /* c. DAFTAR PESANAN DIKIRIM
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                pesananDikirim(order, akun, lib, ebook, indeksLogin, akun[indeksLogin].username);}

            /* d. DAFTAR PESANAN SELESAI
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("DAFTAR PESANAN SELESAI"); cout << endl;
                pesananSelesai(akun, order, indeksLogin);}

            /* e. DAFTAR PESANAN DIBATALKAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("DAFTAR PESANAN DIBATALKAN"); cout << endl;
                pesananDibatalkan(akun, order, indeksLogin);}

            /* f. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void lihatLibraryUser(vector<Library> &lib, string id_user) {
    // CEK KETERSEDIAAN PERPUSTAKAAN
    if (lib.empty()) {
        tampilPeringatan(36, "Belum ada perpustakaan yang dibuat!");
        return;}
    bool ada = false;
    for (const auto &l : lib) {
        if (l.id_user == id_user) {
            ada = true;
            break;}}
    if (!ada) {
        tampilPeringatan(26, "Kamu belum memiliki E-Book!");
        return;}

    // DAFTAR PERPUSTAKAAN
    cout << CYAN << BOLD;
    cout << spasi(10) << "┌─────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(10) << "│                                             PERPUSTAKAAN E-BOOK MILIKMU                                             │" << endl;
    cout << spasi(10) << "├──────┬──────────────────────┬──────────────────────────────────────────┬──────────────────────┬─────────────────────┤" << endl;
    cout << spasi(10) << "│ NO   │ KODE                 │ JUDUL                                    │ PENULIS              │ GENRE               │" << endl;
    cout << spasi(10) << "├──────┼──────────────────────┼──────────────────────────────────────────┼──────────────────────┼─────────────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (const auto &l : lib) {
        if (l.id_user == id_user) {
            cout << spasi(10);
            if (no % 2 == 0) cout << BG_ABU;
            cout << "│ " << left << setw(5)  << no++
                << "│ " << setw(21) << l.buku.kode
                << "│ " << setw(41) << l.buku.judul
                << "│ " << setw(21) << l.buku.penulis
                << "│ " << setw(20) << l.buku.genre
                << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(10) << "└──────┴──────────────────────┴──────────────────────────────────────────┴──────────────────────┴─────────────────────┘" << endl;
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
                editSaldo(akun, indeksLogin, transaksi);
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


/*  MENU USER                                                                                     */
//═════════════════════════════════════════════════════════════════════════════════════════════════//
void menuUser(vector<Akun> &akun, int indeksLogin, vector<Ebook> &ebook, vector<Library> &library, vector<Order> &order, vector<Transaksi> &transaksi, vector<Keranjang> &keranjang) {
    string pilihMenuUser[] = {
        "『        Kelola Akun Anda        』", 
        "『        Belanja Sekarang        』",
        "『        Keranjang Belanja       』",
        "『         Daftar Pesanan         』",
        "『        Perpustakaan Anda       』",
        "『        Saldo & Transaksi       』",
        "『             Logout             』"};

    int pilih = 0;  bool refresh = true;
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
                system("cls"); judul_subjudul("MENU KELOLA AKUN DIRI"); cout << endl;
                kelolaAkunDiri(akun, indeksLogin);}

            /* 2. MENU USER BELANJA SEKARANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("MENU BELANJA SEKARANG"); cout << endl;
                belanjaUser(ebook, keranjang, order, akun, indeksLogin, transaksi, library);}

            /* 3. MENU USER KERANJANG BELANJA
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                keranjangUser(ebook, keranjang, akun, order, indeksLogin, transaksi);}

            /* 4. MENU USER DAFTAR PESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("MENU DAFTAR PESANAN"); cout << endl;
                pesananUser(ebook, order, akun, indeksLogin, library, transaksi);}

            /* 4. MENU USER PERPUSTAKAAN ANDA
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("PERPUSTAKAAN ANDA"); cout << endl;
                lihatLibraryUser(library, akun[indeksLogin].id_user);
                system("pause");}

            /* 5. MENU USER SALDO & TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 5) {
                saldoDanTransaksi(akun, indeksLogin, transaksi);}

            /* 6. MENU USER LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(16, "Logout berhasil!"); system("pause");
                break;}}}}


//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
/*                     MAIN PROGRAM                                                                            */
//═════════════════════════════════════════════════════════════════════════════════════════════════════════════//
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
    int percobaan = 0;

    /* PROGRAM UTAMA
    ════════════════════════════════════════════════════*/
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("SELAMAT DATANG DI TOKO E-BOOK KAMI"); cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(52) << BG_PUTIH << HITAM << BOLD << *(pilihMenu + i) << RESET << endl;
            else cout << DIM << spasi(52) << *(pilihMenu + i) << RESET << endl;}
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            refresh = true;
    
            /* 1. LOGIN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("LOG IN AKUN ANDA");
                int indeksLogin = login(akun);

                // LOGIN BERHASIL
                if (indeksLogin >= 0) {
                    percobaan = 0;
                    if (akun[indeksLogin].role == "Admin") {
                        menuAdmin(akun, indeksLogin, ebook, order, transaksi);}
                    else {
                        menuUser(akun, indeksLogin, ebook, library, order, transaksi, keranjang);}}

                // LOGIN GAGAL
                else if (indeksLogin < 0) {
                    // USERNAME ATAU PASSWORD SALAH
                    if (indeksLogin == -1) {
                        percobaan++;
                        if (percobaan < 3) {
                            tampilPeringatan(54, "Username atau password salah atau akun tidak terdaftar.");
                            tampilPeringatan(20, "Sisa kesempatan: " + to_string(3 - percobaan));
                            system("pause");}
                        else {
                            system("cls"); judul_subjudul("TERIMA KASIH"); cout << endl;
                            tampilPesan("Terlalu banyak percobaan login. Program ditutup.");
                            break;}
                        refresh = true;}
                    // INPUT KOSONG ATAU AKUN NONAKTIF
                    else {
                        refresh = true;}}}

            /* 2. REGISTRASI
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("REGISTRASI AKUN ANDA");
                registrasi(akun);
                system("pause");}

            /* 3. KELUAR PROGRAM
            ════════════════════════════════════════════════════*/
            else {
                system("cls"); judul_subjudul("TERIMA KASIH TELAH BERKUNJUNG AWW MANTAP!"); cout << endl;
                break;}
        }
    }
    
    return 0;
}