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



/* WARNA CIAMIK CUKK
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



/* STRUCT ADMIN DAN CRUD
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
    int harga, total_harga;
    int tanggal_pesan, tanggal_kirim, tanggal_sampai;
    string status_order, status_bayar, batal_oleh, alasan;};

struct Transaksi {
    string id_transaksi, id_user, id_order;
    int nominal;
    int tanggal_transaksi;};

struct Keranjang {
    string id_user, kode, judul;
    int harga;};



/* FUNGSI LOAD & SAVE JSON
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
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
        o.total_harga = item["total_harga"];
        o.tanggal_pesan = item["tanggal_pesan"];
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
        trans.push_back(t);}}

void loadKeranjang(vector<Keranjang> &ker) {
    ifstream file("../keranjang.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Keranjang k;
        k.id_user = item["id_user"];
        k.kode = item["kode"];
        k.judul = item["judul"];
        k.harga = item["harga"];
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
            {"total_harga", o.total_harga},
            {"tanggal_pesan", o.tanggal_pesan},
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
            {"tanggal_transaksi", t.tanggal_transaksi}
        });}
    ofstream file("../transaksi.json");
    file << setw(4) << j;}

void saveKeranjang(vector<Keranjang> &ker) {
    json j = json::array();
    for (auto &k : ker) {
        j.push_back({
            {"id_user", k.id_user},
            {"kode", k.kode},
            {"judul", k.judul},
            {"harga", k.harga}
        });}
    ofstream file("../keranjang.json");
    file << setw(4) << j;}



/* PROSEDUR DAN FUNGSI BANTU
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
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
        clsScroll(0,0); judul_subjudul(judulMenu);
        cout << endl;
        for (size_t i = 0; i < indexEbook.size(); i++) {
            if (i == pilih) 
                {cout << "                                  ➠    " << BG_PUTIH << HITAM << BOLD  << setw(4) << ebook[indexEbook[i]].no << "│ " << setw(40) << ebook[indexEbook[i]].judul << "│ " << setw(18) << ebook[indexEbook[i]].kode << RESET << endl;}
            else {
                cout << DIM << "                                       " << setw(4) << ebook[indexEbook[i]].no << "│ " << setw(40) << ebook[indexEbook[i]].judul << "│ " << setw(18) << ebook[indexEbook[i]].kode << RESET << endl;}}
        int hasil = scrollMenu(pilih, indexEbook.size());
        if (hasil == -1) {
            refresh = true;
            return indexEbook[pilih];}}}

int scrollAkun(vector<Akun> &akun, string judulMenu) {
    int pilih = 0;
    bool refresh = true;

    vector<int> indexUser;
    for (size_t i = 0; i < akun.size(); i++) {
        if (akun[i].role == "user") indexUser.push_back(i);}
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul(judulMenu);
        cout << endl;
        for (size_t i = 0; i < indexUser.size(); i++) {
            if (i == pilih)
                {cout << "                                  ➠    " << BG_PUTIH << HITAM << BOLD  << setw(9) << akun[indexUser[i]].id_user <<  "│ " << setw(18) << akun[indexUser[i]].username << RESET << endl;}
            else {
                cout << DIM << "                                       " << setw(9) << akun[indexUser[i]].id_user <<  "│ " << setw(18) << akun[indexUser[i]].username << RESET << endl;}}
        int hasil = scrollMenu(pilih, indexUser.size());
        if (hasil == -1) {
            refresh = true;
            return indexUser[pilih];}}}

string spasi(int nilai) {
    return string(nilai, ' ');}

void tengah(string text) {
    int lebarTerminal = 140;
    int spasi = (lebarTerminal - text.length()) / 2;
    if (spasi < 0) spasi = 0;
    cout << string(spasi, ' ') << text;}


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



/* FUNGSI LOGIN & REGISTRASI
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/

/* [REKURSIF] */
int login(vector<Akun> &akun, int percobaan = 0) {
    if (percobaan >= 3) {
        tampilPesan("Anda telah salah 3 kali. Silakan datang lain kali.");
        system("pause");
        return -3;}

    string jawabNama, jawabPassword;

    cout << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << "Username: "; cin >> jawabNama;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << "Password: "; cin >> jawabPassword;
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
    cout << spasi(47) << "Username: "; cin >> username;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << "Password: "; cin >> password;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << "Email: "; cin >> email;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << "No. HP: "; cin >> no_hp;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << "Alamat: "; cin >> alamat;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;

    if (username.empty() || password.empty() || email.empty() || no_hp.empty() || alamat.empty()) {
        tampilPeringatan(24, "Semua kolom harus diisi!"); return;}
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
    baru.role = "user";
    baru.status_akun = "Aktif";
    baru.email = email;
    baru.no_hp = no_hp;
    baru.alamat = alamat;
    baru.tanggal_daftar = tanggal;
    baru.saldo = 0;

    akun.push_back(baru);
    tampilPesan(20, "Registrasi berhasil!");
}



/* FUNGSI MENU ADMIN
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatDataDiri(vector<Akun> &akun, int index_login) {
    string passwordSensor = string(akun[index_login].password.length(), '*');
    string field[10] = {
        "ID USER", "USERNAME", "PASSWORD", "ROLE", "STATUS AKUN", "EMAIL", "ALAMAT", "NO HP", "TANGGAL DAFTAR", "SALDO"};
    string data[10] = {
        akun[index_login].id_user,
        akun[index_login].username,
        passwordSensor,
        akun[index_login].role,
        akun[index_login].status_akun,
        akun[index_login].email,
        akun[index_login].alamat,
        akun[index_login].no_hp,
        to_string(akun[index_login].tanggal_daftar),
        "Rp" + to_string(akun[index_login].saldo)};

    cout << CYAN << BOLD;
    cout << spasi(40) << "┌────────────────────┬───────────────────────────────────────┐" << endl;
    cout << spasi(40) << "│ FIELD              │ DATA                                  │" << endl;
    cout << spasi(40) << "├────────────────────┼───────────────────────────────────────┤" << endl;
    cout << RESET;

    for (int i = 0; i < 10; i++) {
        cout << spasi(40);
        if (i % 2 == 0) cout << "\033[48;5;235m";
        cout << "│ " << left << setw(19) << field[i]
            << "│ " << setw(38) << data[i]
            << "│" << RESET << endl;}
    cout << CYAN;
    cout << spasi(40) << "└────────────────────┴───────────────────────────────────────┘" << endl;
    cout << RESET << endl;}

void lihatDaftarPelanggan(vector<Akun> &akun) {
    cout << CYAN << BOLD;
    cout << spasi(6) << "┌────┬──────────┬───────────────────┬───────────────────────────────┬──────────────────┬──────────────────────┬───────────────┐" << endl;
    cout << spasi(6) << "│ NO │ ID USER  │ USERNAME          │ EMAIL                         │ NO HP            │ ALAMAT               │ STATUS AKUN   │" << endl;
    cout << spasi(6) << "├────┼──────────┼───────────────────┼───────────────────────────────┼──────────────────┼──────────────────────┼───────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (size_t i = 0; i < akun.size(); i++) {
        if (akun[i].role == "user") {
            cout << spasi(6);
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(3) << no++
                << "│ " << setw(9) << akun[i].id_user
                << "│ " << setw(18) << akun[i].username
                << "│ " << setw(30) << akun[i].email
                << "│ " << setw(17) << akun[i].no_hp
                << "│ " << setw(21) << akun[i].alamat << "│ ";
            if (akun[i].status_akun == "aktif" || akun[i].status_akun == "Aktif")
                cout << HIJAU << BOLD << setw(14) << akun[i].status_akun << RESET;
            else
                cout << MERAH << BOLD << setw(14) << akun[i].status_akun << RESET;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└────┴──────────┴───────────────────┴───────────────────────────────┴──────────────────┴──────────────────────┴───────────────┘" << endl;
    cout << RESET << endl;}

void editStatusPelanggan(vector<Akun> &akun) {
    string tindakan[] = {
        "【 1 | Aktifkan      】",
        "【 2 | Nonaktifkan   】",
        "【 3 | Batalkan      】"};

    int pilihan = scrollAkun(akun, "EDIT STATUS AKUN PELANGGAN");

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("EDIT STATUS AKUN PELANGGAN");
        cout << endl;
        lihatDataDiri(akun, pilihan);
        for (int i = 0; i < 3; i++) {
            if (i == pilih)
                cout << spasi(34) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(34) << tindakan[i] << RESET << endl;}
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


void lihatDataEbook(vector<Ebook> &ebook, int index_ebook) {
    string field[7] = {
        "NO", "KODE", "JUDUL", "PENULIS", "TAHUN", "GENRE", "HARGA"};
    string data[10] = {
        to_string(ebook[index_ebook].no),
        ebook[index_ebook].kode,
        ebook[index_ebook].judul,
        ebook[index_ebook].penulis,
        to_string(ebook[index_ebook].tahun),
        ebook[index_ebook].genre,
        to_string(ebook[index_ebook].harga)};

    cout << CYAN << BOLD;
    cout << spasi(40) << "┌─────────┬────────────────────────────────────────────────┐" << endl;
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
    cout << " ┌──────┬───────────────────┬────────────────────────────────────────┬────────────────────────┬───────┬─────────────────┬───────────────┐" << endl;
    cout << " │ NO   │ KODE              │ JUDUL                                  │ PENULIS                │ TAHUN │ GENRE           │ HARGA         │" << endl;
    cout << " ├──────┼───────────────────┼────────────────────────────────────────┼────────────────────────┼───────┼─────────────────┼───────────────┤" << endl;
    cout << RESET;
    for (size_t i = 0; i < ebook.size(); i++) {
        cout << " ";
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
    cout << " └──────┴───────────────────┴────────────────────────────────────────┴────────────────────────┴───────┴─────────────────┴───────────────┘" << endl;
    cout << RESET << endl;}

int tambahEbook(vector<Ebook> &ebook) {
    Ebook baru;
    string genre[] = {
        "Romance", "Fantasy", "Horror", "Mystery", "Thriller", "Sci-Fi", "Adventure", "Action", "Drama", "Comedy",
        "Historical", "Crime", "Psychological", "Slice of Life", "School", "Supernatural", "Family", "Friendship",
        "Religious", "Biography"};

    cin.ignore(1000, '\n');
    cout << "\n                                             ┌────────────────────────────────────────────────┐"
        << "\n                                                Judul   : "; getline(cin, baru.judul);
    cout << "                                               └────────────────────────────────────────────────┘";
    cout << "\n                                             ┌────────────────────────────────────────────────┐"
        << "\n                                                Penulis : "; getline(cin, baru.penulis);
    cout << "                                               └────────────────────────────────────────────────┘";
    cout << "\n                                             ┌────────────────────────────────────────────────┐"
        << "\n                                                Tahun   : "; cin >> baru.tahun;
    cout << "                                               └────────────────────────────────────────────────┘";
    if (cin.fail() || baru.tahun <= 0) {
        tampilPeringatan(52, "Tahun harus berupa angka, tidak boleh minus atau 0!");
        return 0;}

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("EDIT STATUS AKUN PELANGGAN");
        cout << endl;
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Judul   : " << baru.judul;
        cout << "\n                                             └────────────────────────────────────────────────┘";
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Penulis : " << baru.penulis;
        cout << "\n                                             └────────────────────────────────────────────────┘";
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Tahun   : " << baru.tahun;
        cout << "\n                                             └────────────────────────────────────────────────┘";
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Genre   : ";
        cout << "                                               └────────────────────────────────────────────────┘";
        cout << endl;
        for (int i = 0; i < 20; i++) {
            if (i == pilih)
                cout << spasi(51) << "➠    " << BG_PUTIH << HITAM << BOLD << genre[i] << RESET << endl;
            else cout << DIM << spasi(51) << "➠    " << genre[i] << RESET << endl;}
        int hasil = scrollMenu(pilih, 20);
        if (hasil == -1) {
            refresh = true;
            baru.genre = genre[pilih];
            break;}}

    system("cls"); judul_subjudul("EDIT STATUS AKUN PELANGGAN");
    cout << endl;
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Judul   : " << baru.judul;
        cout << "\n                                             └────────────────────────────────────────────────┘";
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Penulis : " << baru.penulis;
        cout << "\n                                             └────────────────────────────────────────────────┘";
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Tahun   : " << baru.tahun;
        cout << "\n                                             └────────────────────────────────────────────────┘";
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Genre   : " << baru.genre;
        cout << "\n                                             └────────────────────────────────────────────────┘";
        cout << "\n                                             ┌────────────────────────────────────────────────┐"
            << "\n                                                Harga   : "; cin >> baru.harga;
        cout << "                                               └────────────────────────────────────────────────┘";
    if (cin.fail() || baru.harga <= 0) {
        tampilPeringatan(52, "Harga harus berupa angka, tidak boleh minus atau 0!");
        return 0;}

    baru.no = generateNo(ebook);
    baru.kode = generateKode(ebook, baru.judul, baru.penulis, baru.tahun);
    ebook.push_back(baru);
    bubbleSortEbook(ebook, 6, true);

    cout << endl; tampilPesan(28, "E-book berhasil ditambahkan!");
    return 1;}

int editEbook(vector<Ebook> &ebook) {
    string genre[] = {
        "Romance", "Fantasy", "Horror", "Mystery", "Thriller", "Sci-Fi", "Adventure", "Action", "Drama", "Comedy",
        "Historical", "Crime", "Psychological", "Slice of Life", "School", "Supernatural", "Family", "Friendship",
        "Religious", "Biography"};
    string tindakan[] = {
        "【 1 | Simpan      】",
        "【 2 | Batalkan      】"};

    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi!");
        return 0;}

    int pilihan = scrollBuku(ebook, "EDIT DETAIL E-BOOK");
    system("cls"); judul_subjudul("EDIT DETAIL E-BOOK"); cout << endl;
    lihatDataEbook(ebook, pilihan); cout << endl;

    Ebook temp = ebook[pilihan];
    cin.ignore(1000, '\n');
    cout << "\n                                         ┌────────────────────────────────────────────────────┐"
        << "\n                                              Judul Baru   : "; getline(cin, temp.judul);
    cout << "                                           └────────────────────────────────────────────────────┘";
    cout << "\n                                         ┌────────────────────────────────────────────────────┐"
        << "\n                                              Penulis Baru : "; getline(cin, temp.penulis);
    cout << "                                           └────────────────────────────────────────────────────┘";
    cout << "\n                                         ┌────────────────────────────────────────────────────┐"
        << "\n                                              Tahun Baru   : "; cin >> temp.tahun;
    cout << "                                           └────────────────────────────────────────────────────┘";
    if (cin.fail() || temp.tahun <= 0) {
        tampilPeringatan(52, "Tahun harus berupa angka, tidak boleh minus atau 0!");
        return 0;}

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("EDIT DETAIL E-BOOK");
        lihatDataEbook(ebook, pilihan); cout << endl;
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Judul Baru   : " << temp.judul;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Penulis Baru : " << temp.penulis;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Tahun Baru   : " << temp.tahun;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Genre Baru   : ";
        cout << "                                           └────────────────────────────────────────────────────────┘";
        cout << endl;
        for (int i = 0; i < 20; i++) {
            if (i == pilih)
                cout << spasi(51) << "➠    " << BG_PUTIH << HITAM << BOLD << genre[i] << RESET << endl;
            else cout << DIM << spasi(51) << "➠    " << genre[i] << RESET << endl;}
        int hasil = scrollMenu(pilih, 20);
        if (hasil == -1) {
            refresh = true;
            temp.genre = genre[pilih];
            break;}}

    system("cls"); judul_subjudul("EDIT DETAIL E-BOOK");
    lihatDataEbook(ebook, pilihan); cout << endl;
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Judul Baru   : " << temp.judul;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Penulis Baru : " << temp.penulis;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Tahun Baru   : " << temp.tahun;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Genre Baru   : " << temp.genre;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Harga Baru   : "; cin >> temp.harga;
        cout << "                                           └────────────────────────────────────────────────────────┘";
    if (cin.fail() || temp.harga <= 0) {
        tampilPeringatan(52, "Harga harus berupa angka, tidak boleh minus atau 0!");
        return 0;}

    int pilihTindakan = 0;
    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("EDIT DETAIL E-BOOK");
        lihatDataEbook(ebook, pilihan); cout << endl;
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Judul Baru   : " << temp.judul;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Penulis Baru : " << temp.penulis;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Tahun Baru   : " << temp.tahun;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Genre Baru   : " << temp.genre;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n                                         ┌────────────────────────────────────────────────────────┐"
            << "\n                                            Harga Baru   : " << temp.harga;
        cout << "\n                                         └────────────────────────────────────────────────────────┘";
        cout << "\n\n                                         Simpan perubahan?"; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilihTindakan)
                cout << spasi(45) << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << spasi(45) << tindakan[i] << RESET << endl;}
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
    return 1;}

int hapusEbook(vector<Ebook> &ebook) {
    string tindakan[] = {
        "【 1 | Hapus         】",
        "【 2 | Batalkan      】"};
    int pilih = 0;

    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi.");
        return 0;}

    int pilihan = scrollBuku(ebook, "HAPUS E-BOOK");
    system("cls"); judul_subjudul("HAPUS E-BOOK"); cout << endl;
    lihatDataEbook(ebook, pilihan); cout << endl;

    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("HAPUS E-BOOK"); cout << endl;
        lihatDataEbook(ebook, pilihan); cout << endl;
        cout << "                                         Hapus E-Book ini?"; cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih)
                cout << "                                             " << BG_PUTIH << HITAM << BOLD << tindakan[i] << RESET << endl;
            else cout << DIM << "                                             " << tindakan[i] << RESET << endl;}
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;

            // HAPUS
            if (pilih == 0) {
                ebook.erase(ebook.begin() + pilihan);
                tampilPesan(24, "E-Book berhasil dihapus!");
                break;}

            else {
                tampilPeringatan(24, "Penghapusan dibatalkan!");
                break;}}}
    return 1;}


void urutEbook(vector<Ebook> &ebook) {
    string menuUrut[] = {
        "『   Judul                        』",
        "『   Penulis                      』",
        "『   Genre                        』",
        "『   Tahun                        』",
        "『   Harga                        』",
        "『   Kode                         』",
        "『   Kembali                      』"}; 
    string jenisUrut[] = {
        "『   Ascending                    』",
        "『   Descending                   』"}; 
    int pilih = 0;
    bool refresh = true;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("URUTKAN KATALOG"); cout << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << "                                 " << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(menuUrut + i) << RESET << endl;
            else cout << DIM << "                                 " << *(menuUrut + i) << RESET << endl;}
        cout << endl; lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {
            refresh = true;

            // KEMBALI
            if (pilih == 6) {
                break;}

            vector<Ebook> hasil;
            // URUTKAN ASCENDING OR DESCENDING
            int pilihJenis = 0;
            bool refreshTindakan = true;
            while(true) {
                if (refreshTindakan) {
                    system("cls"); refreshTindakan = false;}
                clsScroll(0,0); judul_subjudul("JENIS PENGURUTAN"); cout << endl;
                for (int i = 0; i < 2; i++) {
                    if (i == pilihJenis) cout << "                                 " << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(jenisUrut + i) << RESET << endl;
                    else cout << DIM << "                                 " << *(jenisUrut + i) << RESET << endl;}
                cout << endl; lihatDaftarEbook(ebook);
                int hasilJenis = scrollMenu(pilihJenis, 2);

                if (hasilJenis == -1) {
                    refreshTindakan = true;
                    bool ascending = (pilihJenis == 0);
                    vector<Ebook> temp = ebook;
                    bubbleSortEbook(temp, pilih, ascending);

                    system("cls"); judul_subjudul("Hasil Pengurutan"); cout << endl;
                    lihatDaftarEbook(temp);
                    system("pause");
                    break;}}}}}

void cariEbook(vector<Ebook> &ebook) {
    string menuCari[] = {
        "『   Judul                        』",
        "『   Penulis                      』",
        "『   Genre                        』",
        "『   Tahun                        』",
        "『   Harga                        』",
        "『   Kode                         』",
        "『   Kembali                      』"}; 
    int pilih = 0;
    bool refresh = true;

    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("CARI E_BOOK"); cout << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << "                                 " << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(menuCari + i) << RESET << endl;
            else cout << DIM << "                                 " << *(menuCari + i) << RESET << endl;}
        cout << endl; lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {
            refresh = true;

            // KEMBALI
            if (pilih == 6) {
                break;}

            vector<Ebook> hasil;
            // CARI JUDUL, PENULIS, GENRE, KODE
            if (pilih == 0 || pilih == 1 || pilih == 2 || pilih == 5) {
                system("cls"); judul_subjudul("CARI E-BOOK"); cout << endl;
                string keyword; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "                                             ┌────────────────────────────────────────────────┐"
                    << "\n                                                Keyword   : "; getline(cin, keyword);
                cout << "                                             └────────────────────────────────────────────────┘";
                linearSearchEbook(ebook, hasil, pilih + 1, keyword);}

            // CARI TAHUN, HARGA
            else {
                system("cls"); judul_subjudul("CARI E-BOOK"); cout << endl;
                int min, max;
                try {
                    cout << "                                             ┌────────────────────────────────────────────────┐"
                        << "\n                                                Minimum   : "; cin >> min;
                    cout << "                                             └────────────────────────────────────────────────┘";
                    if (cin.fail() || min < 0) {
                        throw "Minimum harus angka!";}
                    cout << "\n                                             ┌────────────────────────────────────────────────┐"
                        << "\n                                                Maksimum  : "; cin >> max;
                    cout << "                                             └────────────────────────────────────────────────┘";
                    if (cin.fail() || max < 0) {
                        throw "Maksimum harus angka!";}
                    if (min > max) {
                        throw "Minimum tidak boleh lebih besar!";}
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');}
                catch (const char* e) {
                    cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    tampilPeringatan(40, e);
                    system("pause");
                    continue;}
                linearSearchEbook(ebook, hasil, pilih + 1, "", min, max);}

            cout << endl;
            if (!hasil.empty()) {
                cout << HIJAU << BOLD << "\nDaftar Hasil Pencarian:" << endl;
                lihatDaftarEbook(hasil);}
            else {tampilPeringatan(22, "Data tidak ditemukan!");}
            system("pause");}}}


void lihatDaftarPembelian(vector<Order> &order) {
    cout << CYAN << BOLD;
    cout << "      ┌──────┬─────────────┬─────────────┬─────────────────────────┬───────────────┬────────────────────────┬───────────────────────┐" << endl;
    cout << "      │ NO   │ ID ORDER    │ ID USER     │ KODE E-BOOK             │ HARGA         │ TANGGAL PESAN          │ TANGGAL TERIMA        │" << endl;
    cout << "      ├──────┼─────────────┼─────────────┼─────────────────────────┼───────────────┼────────────────────────┼───────────────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (size_t i = 0; i < order.size(); i++) {
        cout << "      ";
        if (no % 2 == 0) cout << "\033[48;5;235m";
        cout << "│ " << left << setw(5) << no++
            << "│ " << setw(12) << order[i].id_order
            << "│ " << setw(12) << order[i].id_user
            << "│ " << setw(24) << order[i].kode
            << "│ " << setw(14) << order[i].harga
            << "│ " << setw(23) << order[i].tanggal_pesan
            << "│ " << setw(22) << order[i].tanggal_sampai;
        cout << "│" << RESET << endl;}
    cout << CYAN;
    cout << "      └──────┴─────────────┴─────────────┴─────────────────────────┴───────────────┴────────────────────────┴───────────────────────┘" << endl;
    cout << RESET << endl;}

void cariRiwayatPembelian(vector<Order> &order) {
    string cari;
    bool ditemukan = false;

    system("cls");

    cout << "\n=== CARI RIWAYAT PEMBELIAN ===\n";
    cout << "Masukkan ID Order: ";
    cin >> cari;

    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].id_order == cari) {
            ditemukan = true;
            cout << "\nData Ditemukan\n";
            cout << "ID ORDER       | USERNAME         | JUDUL                    | HARGA    | TANGGAL PESAN  | STATUS ORDER " << endl;
            cout << "---+-----------------+------------------+--------------------------+----------+----------------+" << endl;
            cout << left
                << setw(3) << order[i].id_order << "| "
                << setw(17) << order[i].id_user << "| "
                << setw(25) << order[i].judul << "| "
                << setw(10) << order[i].harga << "| "
                << setw(14) << order[i].tanggal_pesan << "| "
                << setw(14) << order[i].status_order << endl;
        }
    }
}


void lihatPesanan(string jenis, vector<Order> &order) {
    if(order.empty()) {
        tampilPeringatan(28, "Belum ada Pesanan yang dibuat!");
        return;
    }
    cout << "NO | ID ORDER       | USERNAME         | JUDUL                    | HARGA    | TANGGAL PESAN  | STATUS " << endl;
    cout << "---+-----------------+------------------+--------------------------+----------+-----------------+-------------" << endl;
    for (size_t i = 0; i < order.size(); i++) {
        if (order[i].status_order == jenis) {
            cout << left
                << setw(3) << i + 1 << "| " << setw(16) << order[i].id_order << "| "
                << setw(17) << order[i].id_user << "| "
                << setw(25) << order[i].judul << "| "
                << setw(10) << order[i].harga << "| "
                << setw(14) << order[i].tanggal_pesan << "| "
                << setw(11) << order[i].status_order
                << endl;
        }
    }
}

void lihatRiwayatPesanan(vector<Order> &order) {

    bool ada = false;
    int no = 1;

    system("cls");

    cout << "===================== RIWAYAT PESANAN =====================\n\n";

    for (size_t i = 0; i < order.size(); i++) {

        if (order[i].status_order == "Dikirim" ||
            order[i].status_order == "Dibatalkan") {

            ada = true;

            cout << "============================================================\n";

            cout << "No               : " << no++ << endl;
            cout << "ID Order         : " << order[i].id_order << endl;
            cout << "Username         : " << order[i].id_user << endl;
            cout << "Judul            : " << order[i].judul << endl;
            cout << "Status           : " << order[i].status_order << endl;

            if (order[i].status_order == "Dibatalkan") {

                cout << "Dibatalkan Oleh  : " << order[i].batal_oleh << endl;
                cout << "Alasan           : " << order[i].alasan << endl;
            }

            cout << "============================================================\n\n";
        }
    }

    if (!ada) {
        cout << "Belum ada riwayat pesanan!\n";
    }

    system("pause");
}

void editStatusPesanan(vector<Order> &order) {
    if(order.empty()) {
        tampilPeringatan(28, "Belum ada Pesanan yang dibuat!");
        return;
    }
    string cari;
    int pilihan;
    bool ditemukan = false;
    system("cls");
    cout << "\nEDIT STATUS PESANAN\n"; 
    cout << "Masukkan ID Order :";
    cin >> cari;

    for (auto &a : order) {

        if (a.id_order == cari) {
            ditemukan = true;

            cout << "\nData Ditemukan\n";
            cout << "ID Order          : " << a.id_order << endl;
            cout << "Judul      : " << a.judul << endl;
            cout << "Tanggal Pesan         : " << a.tanggal_pesan << endl;
            cout << "Status Pesanan  : " << a.status_order << endl;

            cout << "\nPilihan Status\n";
            cout << "1. Kirim\n";
            cout << "2. Batalkan Pesanan\n";
            cout << "Pilih : ";
            cin >> pilihan;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                cout << "\nInput harus angka!\n";
                system("pause");
                return;
            }
            if (pilihan == 1) {
                a.status_order = "Dikirim";

                cout << "\nPesanan berhasil dikirim!!\n";
            }

            else if (pilihan == 2) {
                a.status_order = "Dibatalkan";

                cout << "\nPesanan dibatalkan!!\n";
            }

            else {
                cout << "\nPilihan tidak valid!\n";
                system("pause");
                return;
            }
        }
    } // belum selesai 
    if (!ditemukan) {
        cout << "\nAkun tidak ditemukan!\n";
    }
    system("pause");
}


void lihatRiwayatTransaksi(vector<Transaksi> &transaksi) {
    if(transaksi.empty()) {
        tampilPeringatan(28, "Belum ada Transaksi yang dibuat!");
        return;
    }
}

void kelolaAkunPelanggan(vector<Akun> &akun) {
    string pilihMenuAdmin[] = {
        "『   Ubah Status Akun Pelanggan   』",
        "『   Kembali                      』"}; 
    int pilih = 0;
    bool refresh = true, adaUser = false;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU KELOLA AKUN PELANGGAN"); cout << endl;

        for (auto &a : akun) {
            if (a.role == "user") {adaUser = true;
                break;}}
        if (!adaUser) {
            tampilPeringatan(36, "Belum ada pelanggan yang terdaftar!");
            return;}

        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << "                                 " << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << "                                 " << *(pilihMenuAdmin + i) << RESET << endl;}
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
        "『   E-Book Baru                  』",
        "『   Edit Detail E-Book           』",
        "『   Hapus E-Book                 』",
        "『   Urutkan Katalog              』",
        "『   Cari E-Book                  』",
        "『   Kembali                      』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU PENJUALAN"); cout << endl;
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << "                                 " << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << "                                 " << *(pilihMenuAdmin + i) << RESET << endl;}
        cout << endl; lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
            refresh = true;
    
            /* a. TAMBAH E-BOOK
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("E-BOOK BARU"); cout << endl;
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
                system("cls"); judul_subjudul("HAPUS E-BOOK"); cout << endl;
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
        "『   Cari Riwayat Pembelian       』",
        "『   Kembali                      』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU PEMBELIAN"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << "                                 " << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << "                                 " << *(pilihMenuAdmin + i) << RESET << endl;}
        cout << endl; lihatDaftarPembelian(order);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;
    
            /* a. CARI RIWAYAT PEMBELIAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Cari Riwayat Pembelian"); cout << endl;
                cariRiwayatPembelian(order);}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pemesananAdmin(vector<Order> &order) {
    string pilihMenuAdmin[] = {
        "   1 | Daftar Pesanan Belum Dibayar",
        "   2 | Daftar Pesanan Sudah Dibayar",
        "   3 | Ubah Status Pesanan",
        "   4 | Riwayat Pesanan Lainnya",
        "   5 | Kembali",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Menu Pemesanan"); cout << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuAdmin + i) << endl;
            else cout << "  " << *(pilihMenuAdmin + i) << endl;}
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
    
            /* a. DAFTAR PESANAN BELUM DIBAYAR
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Daftar Pesanan Belum Dibayar"); cout << endl;
                lihatPesanan("BelumBayar", order);
                system("pause");}

            /* b. DAFTAR PESANAN SUDAH DIBAYAR
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Daftar Pesanan Sudah Dibayar"); cout << endl;
                lihatPesanan("Dibayar", order);
                system("pause");}

            /* c. UBAH STATUS PESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Ubah Status Pesanan"); cout << endl;
                editStatusPesanan(order);
                system("pause");}

            /* d. RIWAYAT PESANAN LAINNYA
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Riwayat Pesanan Lainnya"); cout << endl;
                lihatRiwayatPesanan(order);
                system("pause");}

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
                system("cls"); judul_subjudul("Menu Pembelian"); cout << endl;
                pembelianAdmin(order);
                system("pause");}

            /* 4. MENU ADMIN PEMESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Menu Pemesanan"); cout << "" << endl;
                pemesananAdmin(order);
                system("pause");}

            /* 4. MENU ADMIN RIWAYAT TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("Riwayat Transaksi"); cout << "" << endl;
                lihatRiwayatTransaksi(transaksi);
                system("pause");}

            /* 5. MENU ADMIN LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(16, "Logout berhasil!");
                system("pause");
                break;}}}}



/* FUNGSI MENU USER
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/

void editDataDiri(vector<Akun> &akun, int index_login) {
    lihatDataDiri(akun, index_login);
    cout << "  [Tekan Enter jika tidak ingin mengubah data tertentu]\n\n";

    string tempNoHp, tempAlamat, tempPassword;
    cin.ignore();

    cout << "    No HP baru      : "; getline(cin, tempNoHp);
    cout << "    Alamat baru     : "; getline(cin, tempAlamat);
    cout << "    Password baru   : "; getline(cin, tempPassword);

    try {
        if (!tempNoHp.empty()) {
            regex hpRegex("^08\\d{8,12}$");
            if (!regex_match(tempNoHp, hpRegex)) throw "Nomor HP tidak valid!";
            akun[index_login].no_hp = tempNoHp;
        }
        if (!tempAlamat.empty()) akun[index_login].alamat = tempAlamat;
        if (!tempPassword.empty()) {
            regex passRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$");
            if (!regex_match(tempPassword, passRegex)) throw "Password minimal 8 karakter, ada huruf besar, kecil & angka!";
            akun[index_login].password = tempPassword;
        }

        saveAkun(akun);
        tampilPesan(35, "Data Diri berhasil diperbarui!");
    } catch (const char* e) {
        tampilPeringatan(50, e);
    }
}

void lihatPesananUser(string jenis, vector<Order> &order, string id_user) {
    cout << "ID ORDER         | KODE       | JUDUL                     | TOTAL HARGA | STATUS" << endl;
    cout << "-----------------+------------+---------------------------+-------------+-------------------" << endl;
    
    bool ada = false;
    for (auto &o : order) {
        if (o.id_user == id_user && o.status_order == jenis) {
            cout << left << setw(17) << o.id_order << "| "
                << setw(11) << o.kode << "| "
                << setw(26) << o.judul << "| "
                << setw(12) << o.total_harga << "| "
                << o.status_order << endl;
            ada = true;
        }
    }
    if (!ada) cout << "              Tidak ada pesanan di kategori ini.\n";
    cout << endl;
}

void tambahProdukkeKeranjang(vector<Ebook> &ebook, vector<Keranjang> &keranjang, string id_user) {
    lihatDaftarEbook(ebook);
    string kodeCari;
    cout << "    Masukkan Kode E-Book yang ingin ditambahkan: ";
    cin >> kodeCari;

    try {
        int indexBuku = -1;
        for (size_t i = 0; i < ebook.size(); i++) {
            if (ebook[i].kode == kodeCari) {
                indexBuku = i; break;
            }
        }
        if (indexBuku == -1) throw "Kode E-Book tidak ditemukan!";

        for (auto &k : keranjang) {
            if (k.id_user == id_user && k.kode == kodeCari) throw "E-Book sudah ada di keranjang Anda!";
        }

        Keranjang kBaru = {id_user, ebook[indexBuku].kode, ebook[indexBuku].judul, ebook[indexBuku].harga};
        keranjang.push_back(kBaru);
        saveKeranjang(keranjang);
        
        tampilPesan(40, "Berhasil ditambahkan ke Keranjang!");
    } catch (const char* e) {
        tampilPeringatan(40, e);
    }
}

void checkoutDariKatalog(vector<Ebook> &ebook, vector<Order> &order, vector<Akun> &akun, int index_login) {
    lihatDaftarEbook(ebook);
    string kodeCari;
    cout << "    Masukkan Kode E-Book yang ingin langsung dibeli: ";
    cin >> kodeCari;

    try {
        int indexBuku = -1;
        for (size_t i = 0; i < ebook.size(); i++) {
            if (ebook[i].kode == kodeCari) { indexBuku = i; break; }
        }
        if (indexBuku == -1) throw "Kode E-Book tidak ditemukan!";

        // Tampil detail buku yang dipilih
        cout << endl;
        cout << spasi(40) << "┌───────────────────────────────────────────┐" << endl;
        cout << spasi(40) << "│  Judul  : " << left << setw(33) << ebook[indexBuku].judul << "│" << endl;
        cout << spasi(40) << "│  Harga  : Rp" << left << setw(31) << ebook[indexBuku].harga << "│" << endl;
        cout << spasi(40) << "│  Saldo  : Rp" << left << setw(31) << akun[index_login].saldo << "│" << endl;
        cout << spasi(40) << "└───────────────────────────────────────────┘" << endl;
        cout << endl;

        // Pilihan bayar sekarang atau nanti
        string pilihanBayar[] = {
            "『   Bayar Sekarang   』",
            "『   Bayar Nanti      』",
            "『   Batal            』"};
        int pilihBayar = 0;
        bool refreshBayar = true;

        while (true) {
            if (refreshBayar) { system("cls"); refreshBayar = false; }
            clsScroll(0,0); judul_subjudul("PESAN SEKARANG");
            cout << endl;
            cout << spasi(40) << "┌───────────────────────────────────────────┐" << endl;
            cout << spasi(40) << "│  Judul  : " << left << setw(33) << ebook[indexBuku].judul << "│" << endl;
            cout << spasi(40) << "│  Harga  : Rp" << left << setw(31) << ebook[indexBuku].harga << "│" << endl;
            cout << spasi(40) << "│  Saldo  : Rp" << left << setw(31) << akun[index_login].saldo << "│" << endl;
            cout << spasi(40) << "└───────────────────────────────────────────┘" << endl;
            cout << endl;
            for (int i = 0; i < 3; i++) {
                if (i == pilihBayar)
                    cout << spasi(50) << BG_PUTIH << HITAM << BOLD << pilihanBayar[i] << RESET << endl;
                else
                    cout << DIM << spasi(50) << pilihanBayar[i] << RESET << endl;}

            int hasilBayar = scrollMenu(pilihBayar, 3);
            if (hasilBayar == -1) {
                refreshBayar = true;

                // BATAL
                if (pilihBayar == 2) {
                    tampilPeringatan("Pemesanan dibatalkan.");
                    return;}

                time_t now = time(0); tm *ltm = localtime(&now);
                int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;

                Order oBaru;
                oBaru.id_order    = "ORD" + to_string(now);
                oBaru.id_user     = akun[index_login].id_user;
                oBaru.kode        = ebook[indexBuku].kode;
                oBaru.judul       = ebook[indexBuku].judul;
                oBaru.harga       = ebook[indexBuku].harga;
                oBaru.total_harga = ebook[indexBuku].harga;
                oBaru.tanggal_pesan   = tgl;
                oBaru.tanggal_kirim   = 0;
                oBaru.tanggal_sampai  = 0;
                oBaru.batal_oleh  = "";
                oBaru.alasan      = "";

                // BAYAR SEKARANG
                if (pilihBayar == 0) {
                    if (akun[index_login].saldo < ebook[indexBuku].harga) {
                        tampilPeringatan("Saldo tidak mencukupi! Gunakan bayar nanti.");
                        system("pause");
                        continue;}
                    akun[index_login].saldo -= ebook[indexBuku].harga;
                    oBaru.status_order = "Diproses Admin";
                    oBaru.status_bayar = "Lunas";
                    saveAkun(akun);
                    order.push_back(oBaru);
                    saveOrder(order);
                    tampilPesan("Pembayaran berhasil! Pesanan sedang diproses admin.");
                    break;}

                // BAYAR NANTI
                else {
                    oBaru.status_order = "Menunggu Pembayaran";
                    oBaru.status_bayar = "Belum Lunas";
                    order.push_back(oBaru);
                    saveOrder(order);
                    tampilPesan("Pesanan disimpan! Bayar melalui menu Daftar Pesanan.");
                    break;}}}}

    catch (const char* e) {
        tampilPeringatan(40, e);
    }
}

void lihatDaftarKeranjang(vector<Keranjang> &keranjang, string id_user) {
    cout << "NO | KODE           | JUDUL                     | HARGA    " << endl;
    cout << "---+----------------+---------------------------+----------" << endl;
    int no = 1, total = 0;
    for (auto &k : keranjang) {
        if (k.id_user == id_user) {
            cout << left << setw(3) << no++ << "| " 
                << setw(15) << k.kode << "| "
                << setw(26) << k.judul << "| " 
                << k.harga << endl;
            total += k.harga;
        }
    }
    cout << "------------------------------------------------+----------\n";
    cout << "                                    TOTAL HARGA | Rp" << total << "\n\n";
}

void hapusEbookDariKeranjang(vector<Keranjang> &keranjang, string id_user) {
    lihatDaftarKeranjang(keranjang, id_user);
    string kodeHapus;
    cout << "    Masukkan KODE E-Book yang ingin dihapus: ";
    cin >> kodeHapus;

    bool terhapus = false;
    for (auto it = keranjang.begin(); it != keranjang.end(); ) {
        if (it->id_user == id_user && it->kode == kodeHapus) {
            it = keranjang.erase(it);
            terhapus = true;
            break; 
        } else {
            ++it;
        }
    }

    if (terhapus) {
        saveKeranjang(keranjang);
        tampilPesan(30, "Item berhasil dihapus.");
    } else {
        tampilPeringatan(40, "Kode tidak ditemukan di keranjang!");
    }
}

void checkoutDariKeranjang(vector<Keranjang> &keranjang, vector<Order> &order, string id_user) {
    time_t now = time(0); tm *ltm = localtime(&now);
    int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;
    bool adaItem = false;

    for (int i = keranjang.size() - 1; i >= 0; i--) {
        if (keranjang[i].id_user == id_user) {
            Order o;
            o.id_order = "ORD" + to_string(now) + to_string(i);
            o.id_user = id_user;
            o.kode = keranjang[i].kode;
            o.judul = keranjang[i].judul;
            o.harga = keranjang[i].harga;
            o.total_harga = keranjang[i].harga;
            o.tanggal_pesan = tgl;
            o.tanggal_kirim = 0;
            o.tanggal_sampai = 0;
            o.status_order = "Menunggu Pembayaran";
            o.status_bayar = "Belum Lunas";
            o.batal_oleh = "";
            o.alasan = "";
            
            order.push_back(o);
            keranjang.erase(keranjang.begin() + i);
            adaItem = true;
        }
    }

    if (adaItem) {
        saveKeranjang(keranjang);
        saveOrder(order);
        tampilPesan(40, "Semua item di Keranjang berhasil di Checkout!");
    } else {
        tampilPeringatan(35, "Keranjang Anda kosong!");
    }
}

void pesananBelumDibayar(vector<Order> &order, vector<Akun> &akun, int index_login) {
    string id_user = akun[index_login].id_user;
    lihatPesananUser("Menunggu Pembayaran", order, akun[index_login].id_user);
    
    char pil;
    cout << "Apakah Anda ingin melakukan pembayaran pesanan? (y/n): ";
    cin >> pil;

    if (tolower(pil) == 'y') {
        string id_bayar;
        cout << "Masukkan ID ORDER: "; cin >> id_bayar;

        for (size_t i = 0; i < order.size(); i++) {
            if (order[i].id_user == id_user && order[i].id_order == id_bayar && order[i].status_order == "Menunggu Pembayaran") {
                if (akun[index_login].saldo >= order[i].total_harga) {
                    akun[index_login].saldo -= order[i].total_harga;
                    order[i].status_order = "Diproses Admin";
                    order[i].status_bayar = "Lunas";

                    saveAkun(akun);
                    saveOrder(order);
                    tampilPesan(35, "Pembayaran Berhasil!");
                } else {
                    tampilPeringatan(30, "Saldo Anda tidak mencukupi!");
                }
                return;
            }
        }
        tampilPeringatan(30, "ID Order tidak ditemukan / sudah dibayar!");
    }
}

void pesananDiproses(vector<Order> &order, string id_user) {
    lihatPesananUser("Diproses Admin", order, id_user);
    system("pause");
}

void pesananDikirim(vector<Order> &order, vector<Library> &lib, string id_user, string username) {
    lihatPesananUser("Dikirim", order, id_user);
    
    char pil;
    cout << "Apakah ada pesanan yang sudah diterima/selesai? (y/n): ";
    cin >> pil;

    if (tolower(pil) == 'y') {
        string id_selesai;
        cout << "Masukkan ID ORDER: "; cin >> id_selesai;

        for (size_t i = 0; i < order.size(); i++) {
            if (order[i].id_user == id_user && order[i].id_order == id_selesai && order[i].status_order == "Dikirim") {
                order[i].status_order = "Selesai";
                
                Library lBaru;
                lBaru.id_user = id_user;
                lBaru.username = username;
                lBaru.buku.kode = order[i].kode;
                lBaru.buku.judul = order[i].judul; 
                lib.push_back(lBaru);

                saveOrder(order);
                saveLibrary(lib);
                tampilPesan(45, "Pesanan Selesai! E-Book ditambahkan ke Library.");
                return;
            }
        }
        tampilPeringatan(35, "ID Order tidak valid.");
    }
}

void editSaldo(vector<Akun> &akun, int index_login) {
    cout << "\n";
    cout << spasi(50) << "==============================" << endl;
    cout << spasi(50) << "    TOP UP / EDIT SALDO       " << endl;
    cout << spasi(50) << "==============================" << endl;
    cout << endl;
    cout << spasi(50) << "Saldo Saat Ini : Rp" << akun[index_login].saldo << endl;
    cout << endl;
    cout << spasi(50) << "┌────────────────────────────────────┐" << endl;
    cout << spasi(50) << "  Nominal Top Up : Rp";

    string inputNominal;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, inputNominal);

    cout << spasi(50) << "└────────────────────────────────────┘" << endl;

    // Validasi: tidak boleh kosong
    if (inputNominal.empty()) {
        tampilPeringatan("Nominal tidak boleh kosong!");
        return;}

    // Validasi: setiap karakter harus digit (isdigit), tidak boleh ada +, -, spasi, dll
    for (size_t i = 0; i < inputNominal.length(); i++) {
        if (!isdigit((unsigned char)inputNominal[i])) {
            tampilPeringatan("Nominal hanya boleh berisi angka tanpa tanda apapun!");
            return;}}

    long long nominal = 0;
    try {
        nominal = stoll(inputNominal);
    } catch (...) {
        tampilPeringatan("Nominal terlalu besar atau tidak valid!");
        return;}

    if (nominal <= 0) {
        tampilPeringatan("Nominal harus lebih dari 0!");
        return;}

    akun[index_login].saldo += (int)nominal;
    saveAkun(akun);

    cout << endl;
    cout << spasi(50) << "Saldo sekarang : Rp" << akun[index_login].saldo << endl;
    tampilPesan("Top Up Berhasil!");}

void kelolaAkunDiri(vector<Akun> &akun, int index_login) {
    string pilihMenuUser[] = {
        "   1 | Edit Data Diri",
        "   2 | Kembali",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Kelola Akun Diri"); cout << endl;
        lihatDataDiri(akun, index_login);
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
    
            /* a. EDIT DATA DIRI
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Edit Data Diri"); cout << endl;
                editDataDiri(akun, index_login);
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void belanjaUser(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Order> &order, vector<Akun> &akun, int index_login) {
    string pilihMenuUser[] = {
        "   1 | Tambah Ke Keranjang",
        "   2 | Pesan Sekarang",
        "   3 | Urutkan Katalog",
        "   4 | Cari E-Book",
        "   5 | Kembali",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Menu Pemesanan"); cout << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
    
            /* a. TAMBAH PRODUK KE KERANJANG
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Tambah Ke Keranjang"); cout << endl;
                tambahProdukkeKeranjang(ebook, keranjang, akun[index_login].id_user);
                system("pause");}

            /* b. PESAN SEKARANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Pesan Sekarang"); cout << endl;
                // Kirim akun & index_login agar bisa cek/potong saldo
                checkoutDariKatalog(ebook, order, akun, index_login);
                system("pause");}

            /* c. URUT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                urutEbook(ebook);
                system("pause");}

            /* d. CARI E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                cariEbook(ebook);
                system("pause");}

            /* e. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void keranjangUser(vector<Keranjang> &keranjang, vector<Akun> &akun, vector<Order> &order, int index_login) {
    string pilihMenuUser[] = {
        "   1 | Hapus E-Book dari Keranjang",
        "   2 | Pesan Keranjang",
        "   3 | Kembali"};
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Menu Kelola Akun Pelanggan"); cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        lihatDaftarKeranjang(keranjang, akun[index_login].id_user);
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
    
            /* a. HAPUS E-BOOK DARI KERANJANG
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Hapus E-Book dari Keranjang"); cout << endl;
                hapusEbookDariKeranjang(keranjang, akun[index_login].id_user);
                system("pause");}

            /* b. PESAN KERANJANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Pesan Keranjang"); cout << endl;
                checkoutDariKeranjang(keranjang, order, akun[index_login].id_user);
                system("pause");}

            /* c. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pesananUser(vector<Order> &order, vector<Akun> &akun, int index_login, vector<Library> &lib) {
    string pilihMenuUser[] = {
        "   1 | Daftar Pesanan Belum Dibayar",
        "   2 | Daftar Pesanan Diproses",
        "   3 | Daftar Pesanan Dikirim",
        "   4 | Daftar Pesanan Selesai",
        "   5 | Daftar Pesanan Dibatalkan",
        "   6 | Kembali"};
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Menu Pemesanan"); cout << endl;
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
    
            /* a. DAFTAR PESANAN BELUM DIBAYAR
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Daftar Pesanan Belum Dibayar"); cout << endl;
                pesananBelumDibayar(order, akun, index_login);
                system("pause");}

            /* b. DAFTAR PESANAN DIPROSES
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Daftar Pesanan Diproses"); cout << endl;
                pesananDiproses(order, akun[index_login].id_user);
                system("pause");}

            /* c. DAFTAR PESANAN DIKIRIM
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Daftar Pesanan Dikirim"); cout << endl;
                pesananDikirim(order, lib, akun[index_login].id_user, akun[index_login].username);
                system("pause");}

            /* d. DAFTAR PESANAN SELESAI
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Daftar Pesanan Selesai"); cout << endl;
                lihatPesananUser("Selesai", order, akun[index_login].id_user);
                system("pause");}

            /* e. DAFTAR PESANAN DIBATALKAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("Daftar Pesanan Dibatalkan"); cout << endl;
                lihatPesananUser("Batal", order, akun[index_login].id_user);
                system("pause");}

            /* f. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void lihatLibraryUser(vector<Library> &lib, string id_user) {
    bool ada = false;

    cout << "NO | KODE           | JUDUL                    | PENULIS             | GENRE      | TAHUN" << endl;
    cout << "---+----------------+--------------------------+---------------------+------------+-------" << endl;

    int no = 1;
    for (size_t i = 0; i < lib.size(); i++) {
        if (lib[i].id_user == id_user) {
            ada = true;

            cout << left
                << setw(3) << no++ << "| "
                << setw(15) << lib[i].buku.kode << "| "
                << setw(25) << lib[i].buku.judul << "| "
                << setw(20) << lib[i].buku.penulis << "| "
                << setw(11) << lib[i].buku.genre << "| "
                << setw(5) << lib[i].buku.tahun
                << endl;
        }
    }

    if (!ada) {
        tampilPeringatan(35, "Library kamu masih kosong!");
    }

    cout << endl;
}

void saldoDanTransaksi(vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    string pilihMenuUser[] = {
        "   1 | TopUP",
        "   2 | Riwayat Transaksi",
        "   3 | Kembali"};
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Saldo dan Transaksi"); cout << endl;
        cout << spasi(56) << "┌──────────────────────────┐" << endl;
        cout << spasi(58) << "Saldo: Rp" << akun[indeksLogin].saldo << endl;
        cout << spasi(56) << "└──────────────────────────┘" << endl;
        cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
    
            /* a. TOPUP
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("TopUp Saldo"); cout << endl;
                editSaldo(akun, indeksLogin);
                system("pause");}

            /* b. RIWAYAT TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Riwayat Transaksi"); cout << endl;
                lihatRiwayatTransaksi(transaksi);
                system("pause");}

            /* c. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}


void menuUser(vector<Akun> &akun, int indeksLogin, vector<Ebook> &ebook, vector<Library> &library, vector<Order> &order, vector<Transaksi> &transaksi, vector<Keranjang> &keranjang) {
    string pilihMenuUser[] = {
        "   1 | Kelola Akun Anda",
        "   2 | Belanja Sekarang",
        "   3 | Keranjang Belanja",
        "   4 | Daftar Pesanan",
        "   5 | Perpustakaan Milikmu",
        "   6 | Saldo dan Transaksi",
        "   7 | Logout"};
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Halo, User " + akun[indeksLogin].username);
        cout << spasi(56) << "┌──────────────────────────┐" << endl;
        cout << spasi(58) << "Saldo: Rp" << akun[indeksLogin].saldo << endl;
        cout << spasi(56) << "└──────────────────────────┘" << endl;
        cout << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {
    
            /* a. MENU USER KELOLA AKUN DIRI
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Kelola Akun Anda"); cout << endl;
                kelolaAkunDiri(akun, indeksLogin);
                system("pause");}

            /* b. MENU USER BELANJA SEKARANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Belanja Sekarang"); cout << endl;
                belanjaUser(ebook, keranjang, order, akun, indeksLogin);
                system("pause");}

            /* c. MENU USER KERANJANG BELANJA
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Keranjang Belanja"); cout << endl;
                keranjangUser(keranjang, akun, order, indeksLogin);
                system("pause");}

            /* d. MENU USER PESANAN USER
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Daftar Pesanan"); cout << "" << endl;
                pesananUser(order, akun, indeksLogin, library);
                system("pause");}

            /* e. MENU USER LIBRARY USER
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("Perpustakaan Milikmu"); cout << "" << endl;
                lihatLibraryUser(library, akun[indeksLogin].id_user);
                system("pause");}

            /* f. MENU USER SALDO & TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 5) {
                system("cls"); judul_subjudul("Saldo dan Transaksi"); cout << "" << endl;
                saldoDanTransaksi(akun, indeksLogin, transaksi);
                system("pause");}

            /* g. MENU USER LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(18, "Logout berhasil!");
                system("pause");
                break;}}}}



/* PROGRAM UTAMA
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
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
                    if (akun[indeksLogin].role == "admin") {
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