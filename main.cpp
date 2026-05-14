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
    time_t waktu_order;
    string status_order, status_bayar, batal_oleh, alasan;
};
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
            {"total_harga", o.total_harga},
            {"tanggal_pesan", o.tanggal_pesan},
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
            {"kode", k.kode},
            {"judul", k.judul},
            {"harga", k.harga}
        });}
    ofstream file("keranjang.json");
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
        clsScroll(0,0); judul_subjudul(judulMenu);
        cout << endl;
        cout << spasi(34) << BOLD << KUNING << "Pilih E-book:" << RESET; cout << endl;
        for (size_t i = 0; i < indexEbook.size(); i++) {
            if (i == pilih) 
                {cout << spasi(34) << "➠    " << BG_PUTIH << HITAM << BOLD  << setw(4) << ebook[indexEbook[i]].no << "│ " << setw(40) << ebook[indexEbook[i]].judul << "│ " << setw(18) << ebook[indexEbook[i]].kode << RESET << endl;}
            else {
                cout << DIM << spasi(34) << "     " << setw(4) << ebook[indexEbook[i]].no << "│ " << setw(40) << ebook[indexEbook[i]].judul << "│ " << setw(18) << ebook[indexEbook[i]].kode << RESET << endl;}}
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

int linearSearchOrder(vector<Order> &order, vector<Order> &hasil, string keyword = "") {
    hasil.clear();
    string key = ubahStringKecilSemua(keyword);
    for (size_t i = 0; i < order.size(); i++) {
        if (ubahStringKecilSemua(order[i].id_order).find(key) != string::npos) {
            hasil.push_back(order[i]);}}

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
    cout << spasi(47) << BOLD << "Username: " << RESET; cin >> username;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD "Password: " << RESET; cin >> password;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD "Email: " << RESET; cin >> email;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD "No. HP: " << RESET; cin >> no_hp;
    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
    cout << spasi(47) << BOLD "Alamat: " << RESET; cin >> alamat;
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
    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                     DAFTAR AKUN PELANGGAN                                                    │" << endl;
    cout << spasi(6) << "├────┬──────────┬────────────────────┬───────────────────────────────┬──────────────────┬─────┬────────────────┬───────────────┤" << endl;
    cout << spasi(6) << "│ NO │ ID USER  │ USERNAME           │ EMAIL                         │ NO HP            │ ALAMAT               │ STATUS AKUN   │" << endl;
    cout << spasi(6) << "├────┼──────────┼────────────────────┼───────────────────────────────┼──────────────────┼──────────────────────┼───────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (size_t i = 0; i < akun.size(); i++) {
        if (akun[i].role == "user") {
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

    int pilihan = scrollAkun(akun, "EDIT STATUS AKUN PELANGGAN");

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("EDIT STATUS AKUN PELANGGAN");
        cout << endl;
        lihatDataDiri(akun, pilihan);
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

int tambahEbook(vector<Ebook> &ebook) {
    string input;
    Ebook baru;
    string genre[] = {
        "Romance", "Fantasy", "Horror", "Mystery", "Thriller", "Sci-Fi", "Adventure", "Action", "Drama", "Comedy",
        "Historical", "Crime", "Psychological", "Slice of Life", "School", "Supernatural", "Family", "Friendship",
        "Religious", "Biography"};
    string tindakan[] = {
        "【 1 | Simpan      】",
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
            return 0;}}
    try {
        baru.tahun = stoi(input);}
    catch (...) {
        tampilPeringatan(20, "Angka terlalu besar!");
        return 0;}
    if (baru.tahun < 1000 || baru.tahun > 3000) {
        tampilPeringatan(46, "Tahun harus berada di rentang tahun 1000-3000!");
        return 0;}

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
            return 0;}}
    try {
        baru.harga = stoi(input);}
    catch (...) {
        tampilPeringatan(20, "Angka terlalu besar!");
        return 0;}
    if (baru.harga < 0 || baru.harga > 10000000) {
        tampilPeringatan(50, "Harga harus berada di rentang tahun 0-10.000.000!");
        return 0;}

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
                cout << endl; tampilPesan(28, "E-book berhasil ditambahkan!");}

            else {
                tampilPeringatan(22, "Penambahan dibatalkan!");
                break;}}}
    return 1;}

int editEbook(vector<Ebook> &ebook) {
    string inputJudul, inputPenulis, inputTahun, inputHarga;
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
                return 0;}}
        try {
            temp.tahun = stoi(inputTahun);}
        catch (...) {
            tampilPeringatan(20, "Angka terlalu besar!");
            return 0;}
        if (temp.tahun < 1000 || temp.tahun > 3000) {
            tampilPeringatan(46, "Tahun harus berada di rentang tahun 1000-3000!");
            return 0;}}

    int pilih = 0;
    bool refresh = true;
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("EDIT DETAIL E-BOOK");
        lihatDataEbook(ebook, pilihan); cout << endl;
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
    lihatDataEbook(ebook, pilihan); cout << endl;
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
                return 0;}}
        try {
            temp.harga = stoi(inputHarga);}
        catch (...) {
            tampilPeringatan(20, "Angka terlalu besar!");
            return 0;}
        if (temp.harga < 0 || temp.harga > 10000000) {
            tampilPeringatan(50, "Harga harus berada di rentang tahun 0-10.000.000!");
            return 0;}}

    int pilihTindakan = 0;
    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("EDIT DETAIL E-BOOK");
        cout << endl;
        lihatDataEbook(ebook, pilihan); cout << endl;
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
    return 1;}

int hapusEbook(vector<Ebook> &ebook) {
    string tindakan[] = {
        "【 1 | Hapus         】",
        "【 2 | Batalkan      】"};
    int pilihTindakan = 0;

    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi.");
        return 0;}

    int pilihan = scrollBuku(ebook, "HAPUS E-BOOK");
    system("cls"); judul_subjudul("HAPUS E-BOOK"); cout << endl;
    lihatDataEbook(ebook, pilihan); cout << endl;

    bool refreshTindakan = true;
    while (true) {
        if (refreshTindakan) {
            system("cls"); refreshTindakan = false;}
        clsScroll(0,0); judul_subjudul("HAPUS E-BOOK"); cout << endl;
        lihatDataEbook(ebook, pilihan);
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
    return 1;}


void urutEbook(vector<Ebook> &ebook) {
    string menuUrut[] = {
        "『  📝 Judul                        』",
        "『  🪶  Penulis                     』",
        "『  🏷️  Genre                       』",
        "『  🗓️  Tahun                       』",
        "『  💲 Harga                       』",
        "『  🔑 Kode                        』",
        "『 ↩   Kembali                     』"
    };
    
    int pilih = 0;
    while (true) {
        system("cls");
        judul_subjudul("URUTKAN KATALOG");
        cout << endl;

        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << menuUrut[i] << RESET << endl;
            else cout << DIM << spasi(34) << menuUrut[i] << RESET << endl;
        }
        cout << endl;
        // INI MENAMPILKAN DATA ASLI
        lihatDaftarEbook(ebook); 

        int hasil = scrollMenu(pilih, 7);

        if (hasil == -1) {
            // 1. JIKA PILIH KEMBALI, LANGSUNG PULANG
            if (pilih == 6) {
                return; 
            }
            
            // 2. JIKA PILIH KRITERIA, MASUK KE SUB-MENU
            int pilihJenis = 0;
            string jenisUrut[] = {"『 ⬆️ Ascending 』", "『 ⬇️ Descending 』"};

            while (true) {
                system("cls");
                judul_subjudul("JENIS PENGURUTAN");
                cout << spasi(34) << "Kategori: " << BOLD << menuUrut[pilih] << RESET << "\n\n";

                for (int i = 0; i < 2; i++) {
                    if (i == pilihJenis) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << jenisUrut[i] << RESET << endl;
                    else cout << DIM << spasi(34) << jenisUrut[i] << RESET << endl;
                }
                
                int hasilJenis = scrollMenu(pilihJenis, 2);

                if (hasilJenis == -1) {
                    // --- POIN PALING PENTING ---
                    // Kita buat duplikat/copy data 'ebook' ke variabel 'temp'
                    vector<Ebook> temp = ebook; 
                    
                    // Kita urutkan 'temp'-nya saja, 'ebook' asli JANGAN DISENTUH
                    bubbleSortEbook(temp, pilih, (pilihJenis == 0));

                    system("cls");
                    judul_subjudul("HASIL PENGURUTAN SEMENTARA");
                    lihatDaftarEbook(temp); // Tampilkan yang temporary
                    
                    cout << "\n" << spasi(34); 
                    system("pause");
                    break; // Balik ke menu kriteria, 'temp' akan otomatis dihapus dari memori
                }
                else if (hasilJenis == 27) break; 
            }
        }
    }
}

void cariEbook(vector<Ebook> &ebook) {
    string menuCari[] = {
        "『  📝 Judul                        』",
        "『  🪶  Penulis                     』",
        "『  🏷️  Genre                       』",
        "『  🗓️  Tahun                       』",
        "『  💲 Harga                       』",
        "『  🔑 Kode                        』",
        "『 ↩   Kembali                     』"};
    int pilih = 0;
    bool refresh = true, error = false;

    while (true) {
        if (refresh) { system("cls"); refresh = false; }
        clsScroll(0,0); judul_subjudul("CARI E-BOOK"); cout << endl;
        
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << HITAM << BOLD << menuCari[i] << RESET << endl;
            else cout << DIM << spasi(34) << menuCari[i] << RESET << endl;
        }
        cout << endl; lihatDaftarEbook(ebook);
        
        int hasilScroll = scrollMenu(pilih, 7);
        if (hasilScroll == -1) {
            refresh = true;
            if (pilih == 6) break;

            vector<Ebook> hasilCari;
            
            // CARI JUDUL, PENULIS, GENRE, KODE
            if (pilih == 0 || pilih == 1 || pilih == 2 || pilih == 5) {
                system("cls"); judul_subjudul("CARI E-BOOK"); cout << endl;
                string keyword;
                
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                
                cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                cout << spasi(47) << BOLD << "Keyword   : " << RESET; 
                getline(cin, keyword);
                cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;

                // VALIDASI: JIKA ENTER SAJA / KOSONG
                if (keyword.find_first_not_of(' ') == string::npos) {
                    tampilPeringatan(45, "Keyword tidak boleh kosong!");
                    system("pause");
                    continue; 
                }

                linearSearchEbook(ebook, hasilCari, pilih + 1, keyword);
            }
            // CARI TAHUN, HARGA
            else {
                system("cls"); judul_subjudul("CARI E-BOOK"); cout << endl;
                int minVal, maxVal;
                string inputMin, inputMax;
                
                try {
                    cout << spasi(45) << "┌────────────────────────────────────────────────┐" << endl;
                    cout << spasi(47) << BOLD << "Min   : " << RESET; cin >> inputMin;
                    
                    // Validasi angka manual
                    for(char c : inputMin) if(!isdigit(c)) throw "Input Minimum harus angka!";
                    minVal = stoi(inputMin);

                    cout << spasi(45) << "├────────────────────────────────────────────────┤" << endl;
                    cout << spasi(47) << BOLD << "Max   : " << RESET; cin >> inputMax;
                    cout << spasi(45) << "└────────────────────────────────────────────────┘" << endl;
                    
                    for(char c : inputMax) if(!isdigit(c)) throw "Input Maksimum harus angka!";
                    maxVal = stoi(inputMax);

                    if (minVal > maxVal) throw "Nilai Minimum tidak boleh lebih besar dari Maksimum!";
                }
                catch (const char* msg) {
                    tampilPeringatan(45, msg);
                    system("pause");
                    continue;
                }
                linearSearchEbook(ebook, hasilCari, pilih + 1, "", minVal, maxVal);
            }

            // TAMPILKAN HASIL
            if (!hasilCari.empty()) {
                system("cls");
                judul_subjudul("HASIL PENCARIAN");
                lihatDaftarEbook(hasilCari);
            } else {
                tampilPeringatan(45, "Data tidak ditemukan!");
            }
            system("pause");
        }
    }
}


void lihatDaftarPembelian(vector<Order> &order) {
    cout << CYAN << BOLD;
    cout << spasi(6) << "┌──────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐" << endl;
    cout << spasi(6) << "│                                                       DAFTAR PEMBELIAN                                                       │" << endl;
    cout << spasi(6) << "├──────┬──────────────────┬───────────┬─────────────────────────┬────────────┬────────────────────────┬────────────────────────┤" << endl;
    cout << spasi(6) << "│ NO   │ ID ORDER         │ ID USER   │ KODE E-BOOK             │ HARGA      │ TANGGAL PESAN          │ TANGGAL TERIMA         │" << endl;
    cout << spasi(6) << "├──────┼──────────────────┼───────────┼─────────────────────────┼────────────┼────────────────────────┼────────────────────────┤" << endl;
    cout << RESET;
    int no = 1;
    for (size_t i = 0; i < order.size(); i++) {
        cout << spasi(6);
        if (no % 2 == 0) cout << "\033[48;5;235m";
        cout << "│ " << left << setw(5) << no++
            << "│ " << setw(17) << order[i].id_order
            << "│ " << setw(10) << order[i].id_user
            << "│ " << setw(24) << order[i].kode
            << "│ " << setw(11) << order[i].harga
            << "│ " << setw(23) << order[i].tanggal_pesan
            << "│ " << setw(23) << order[i].tanggal_sampai;
        cout << "│" << RESET << endl;}
    cout << CYAN;
    cout << spasi(6) << "└──────┴──────────────────┴───────────┴─────────────────────────┴────────────┴────────────────────────┴────────────────────────┘" << endl;
    cout << RESET << endl;}

void cariRiwayatPembelian(vector<Order> &order) {
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


void lihatPesanan(string jenis, vector<Order> &order) {
    if(order.empty()) {
        tampilPeringatan(30, "Belum ada Pesanan yang dibuat!");
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
        if (order[i].status_bayar == jenis) {
            cout << spasi(6);
            if (no % 2 == 0) cout << "\033[48;5;235m";
            cout << "│ " << left << setw(5) << no++
                << "│ " << setw(18) << order[i].id_order
                << "│ " << setw(12) << order[i].id_user
                << "│ " << setw(26) << order[i].kode
                << "│ " << setw(11) << order[i].harga
                << "│ " << setw(23) << order[i].tanggal_pesan << "│ ";
            if (order[i].status_bayar == "Belum Lunas")
                cout << MERAH << BOLD << setw(18) << order[i].status_bayar << RESET;
            else
                cout << HIJAU << BOLD << setw(18) << order[i].status_bayar << RESET;
            cout << "│" << RESET << endl;}}
    cout << CYAN;
    cout << spasi(6) << "└──────┴───────────────────┴─────────────┴───────────────────────────┴────────────┴────────────────────────┴───────────────────┘" << endl;
    cout << RESET << endl;}

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
        tampilPeringatan(28, "Belum ada riwayat pesanan!");
    }

    system("pause");
}

void editStatusPesanan(vector<Order> &order, vector<Akun> &akun) {
    string tindakan[] = {
        "【 1 | Kirim         】",
        "【 2 | Cancel        】",
        "【 3 | Batalkan      】"};
    
    if (order.empty()) {
        tampilPeringatan(28, "Belum ada Pesanan yang dibuat!");
        return;
    }

    int pilihan = scrollAkun(akun, "EDIT STATUS AKUN PELANGGAN");
    string cari;
    bool ditemukan = false;
    system("cls");

    cout << "\nEDIT STATUS PESANAN\n";
    cout << "Masukkan ID Order : ";
    cin >> cari;

    for (auto &a : order) {

        if (a.id_order == cari) {
            ditemukan = true;

            cout << "\nData Ditemukan\n";
            cout << "ID Order           : " << a.id_order << endl;
            cout << "Judul              : " << a.judul << endl;
            cout << "Tanggal Pesan      : " << a.tanggal_pesan << endl;
            cout << "Status Pesanan     : " << a.status_order << endl;
            cout << "Status Bayar       : " << a.status_bayar << endl;

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
                if (a.status_bayar == "Belum Lunas") {
                    cout << "\nPesanan belum lunas, tidak bisa dikirim!\n";
                    system("pause");
                    return;
                }

                a.status_order = "Dikirim";

                cout << "\nPesanan berhasil dikirim!\n";
            }

            else if (pilihan == 2) {
                cin.ignore();
                a.status_order = "Dibatalkan";
                a.status_bayar = "Dikembalikan";
                a.batal_oleh = "Admin";

                cout << "Masukkan alasan pembatalan : ";
                getline(cin, a.alasan);

                cout << "\nPesanan berhasil dibatalkan!\n";
            }

            else {
                cout << "\nPilihan tidak valid!\n";
                system("pause");
                return;
            }

            saveOrder(order);
            break;
        }
    }

    if (!ditemukan) {
        tampilPeringatan(28, "ID Order tidak ditemukan!");
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
        "『  ✏️  Ubah Status Akun Pelanggan 』",
        "『 ↩   Kembali                    』"};
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
        "『  🔍 Cari Riwayat Pembelian     』",
        "『 ↩   Kembali                    』"};
    int pilih = 0;
    bool refresh = true;
    
    while (true) {
        if (refresh) {
            system("cls"); refresh = false;}
        clsScroll(0,0); judul_subjudul("MENU PEMBELIAN"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << spasi(34) << BG_PUTIH << BG_PUTIH << HITAM << BOLD << *(pilihMenuAdmin + i) << RESET << endl;
            else cout << DIM << spasi(34) << *(pilihMenuAdmin + i) << RESET << endl;}
        cout << endl; lihatDaftarPembelian(order);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            refresh = true;
    
            /* a. CARI RIWAYAT PEMBELIAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Cari Riwayat Pembelian"); cout << endl;
                cariRiwayatPembelian(order);
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pemesananAdmin(vector<Order> &order, vector<Akun> &akun){
    string pilihMenuAdmin[] = {
        "『  📋  Daftar Pesanan Belum Dibayar 』",
        "『  📋  Daftar Pesanan Sudah Dibayar 』",
        "『  ✏️  Ubah Status Pesanan           』",
        "『  📑 Riwayat Pesanan Lainnya       』",
        "『 ↩   Kembali                       』"};
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
                lihatPesanan("Belum Lunas", order);
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
                editStatusPesanan(order, akun);}

            /* d. RIWAYAT PESANAN LAINNYA
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("RIWAYAT PESANAN LAINNYA"); cout << endl;
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
                pembelianAdmin(order);}

            /* 4. MENU ADMIN PEMESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Menu Pemesanan"); cout << "" << endl;
                pemesananAdmin(order, akun);
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
    cout << "  [Ketik '0' jika tidak ingin mengubah data tertentu]\n\n";

    string tempNoHp, tempAlamat, tempPassword;
    
    cout << "    No HP baru      : "; cin >> tempNoHp;
    if (tempNoHp == "0") tempNoHp = "";

    cin.ignore();
    cout << "    Alamat baru     : "; getline(cin, tempAlamat);
    if (tempAlamat == "0") tempAlamat = "";

    cout << "    Password baru   : "; cin >> tempPassword;
    if (tempPassword == "0") tempPassword = "";

    try {
        if (tempNoHp.empty() && tempAlamat.empty() && tempPassword.empty()) {
            tampilPeringatan(35, "Tidak ada data yang diubah.");
            return;
        }

        if (!tempNoHp.empty()) {
            regex hpRegex("^08\\d{8,12}$");
            if (!regex_match(tempNoHp, hpRegex)) throw "Nomor HP tidak valid!";
            akun[index_login].no_hp = tempNoHp;
        }
        
        if (!tempAlamat.empty()) {
            akun[index_login].alamat = tempAlamat;
        }
        
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

void validasiWaktuPesanan(vector<Order> &order) {
    time_t waktu_sekarang = time(0);
    bool adaPerubahan = false;

    for (auto &o : order) {
        if (o.status_order == "Menunggu Pembayaran") {
            if (difftime(waktu_sekarang, o.waktu_order) > 300) {
                o.status_order = "Dibatalkan Otomatis";
                o.status_bayar = "Gagal";
                o.batal_oleh = "Sistem";
                o.alasan = "Batas waktu pembayaran 5 menit telah habis.";
                adaPerubahan = true;
            }
        }
    }
    if (adaPerubahan) saveOrder(order);
}

void lihatPesananUser(string status, vector<Order> &order, string id_user) {
    system("cls");
    judul_subjudul("PESANAN: " + status);
    
    bool ditemukan = false;
    int no = 1;

    cout << endl;
    cout << spasi(15) << "┌──────┬──────────────┬──────────────────────────┬─────────────┐" << endl;
    cout << spasi(15) << "│ No   │ ID Order     │ Judul E-Book             │ Status      │" << endl;
    cout << spasi(15) << "├──────┼──────────────┼──────────────────────────┼─────────────┤" << endl;

    for (int i = 0; i < order.size(); i++) {
        if (order[i].id_user == id_user && order[i].status_order == status) {
            cout << spasi(15) << "│ " << left << setw(5) << no++ 
                 << "│ " << setw(13) << order[i].id_order 
                 << "│ " << setw(25) << (order[i].judul.length() > 22 ? order[i].judul.substr(0, 22) + ".." : order[i].judul)
                 << "│ " << setw(12) << order[i].status_order << "│" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        system("cls");
        judul_subjudul("PESANAN: " + status);
        cout << "\n\n" << spasi(38) << "『 Tidak ada pesanan dengan status " << status << " 』" << endl;
    } else {
        cout << spasi(15) << "└──────┴──────────────┴──────────────────────────┴─────────────┘" << endl;
    }
}

void tambahProdukkeKeranjang(vector<Ebook> &ebook, vector<Keranjang> &keranjang, string id_user) {
    system("cls");
    judul_subjudul("TAMBAH KE KERANJANG");
    lihatDaftarEbook(ebook);
    
    string kodeCari;
    cout << "\n    " << "Masukkan Kode E-Book (Ketik '0' untuk batal): ";
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    cin >> kodeCari;

    if (kodeCari == "0") {
        tampilPeringatan(40, "Aksi dibatalkan.");
        return;
    }

    int indexBuku = -1;
    for (int i = 0; i < ebook.size(); i++) {
        // Bandingkan kode
        if (ebook[i].kode == kodeCari) {
            indexBuku = i;
            break;
        }
    }

    if (indexBuku == -1) {
        tampilPeringatan(40, "Kode '" + kodeCari + "' tidak ditemukan! Cek huruf kapital.");
        return;
    }

    for (int i = 0; i < keranjang.size(); i++) {
        if (keranjang[i].id_user == id_user && keranjang[i].kode == kodeCari) {
            tampilPeringatan(40, "E-Book sudah ada di keranjang!");
            return;
        }
    }

    Keranjang kBaru;
    kBaru.id_user = id_user;
    kBaru.kode = ebook[indexBuku].kode;
    kBaru.judul = ebook[indexBuku].judul;
    kBaru.harga = ebook[indexBuku].harga;

    keranjang.push_back(kBaru);
    saveKeranjang(keranjang);
    tampilPesan(40, "Berhasil masuk keranjang!");
}


void checkoutDariKatalog(vector<Ebook> &ebook, vector<Order> &order, vector<Akun> &akun, int index_login) {
    lihatDaftarEbook(ebook);
    string kodeCari;
    
    cout << "\n    Masukkan Kode E-Book yang ingin langsung dibeli (Ketik '0' untuk batal): ";
    cin.clear(); 
    fflush(stdin);

    // 2. AMBIL INPUT
    getline(cin >> ws, kodeCari);

    if (kodeCari == "0" || kodeCari.empty()) {
        tampilPeringatan(40, "Aksi dibatalkan.");
        return;
    }

    int indexBuku = -1;
    for (size_t i = 0; i < ebook.size(); i++) {
        
        if (ebook[i].kode == kodeCari) { 
            indexBuku = i; 
            break; 
        }
    }

    if (indexBuku == -1) {
    tampilPeringatan(40, "Kode '" + kodeCari + "' tidak ditemukan!");
    return;
}

    string pilihanBayar[] = {
        "【 1 | Bayar Sekarang     】",
        "【 2 | Bayar Nanti        】",
        "【 3 | Batal              】"
    };
    int pilihBayar = 0;

    while (true) {
        system("cls");
        judul_subjudul("PESAN SEKARANG");
        cout << endl;
        cout << spasi(40) << "┌───────────────────────────────────────────┐" << endl;
        cout << spasi(40) << "│  Judul  : " << left << setw(32) << ebook[indexBuku].judul << "│" << endl;
        cout << spasi(40) << "│  Harga  : Rp" << left << setw(30) << ebook[indexBuku].harga << "│" << endl;
        cout << spasi(40) << "│  Saldo  : Rp" << left << setw(30) << akun[index_login].saldo << "│" << endl;
        cout << spasi(40) << "└───────────────────────────────────────────┘" << endl;
        cout << endl;
        
        for (int i = 0; i < 3; i++) {
            if (i == pilihBayar) cout << spasi(50) << BG_PUTIH << HITAM << BOLD << pilihanBayar[i] << RESET << endl;
            else cout << DIM << spasi(50) << pilihanBayar[i] << RESET << endl;
        }

        int hasilBayar = scrollMenu(pilihBayar, 3);
        if (hasilBayar == -1) {
            
            // Pilihan BATAL
            if (pilihBayar == 2) {
                tampilPeringatan(40, "Pemesanan dibatalkan.");
                return;
            }

            time_t now = time(0); 
            tm *ltm = localtime(&now);
            int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;

            Order oBaru;
            oBaru.id_order       = "ORD" + to_string(now);
            oBaru.id_user        = akun[index_login].id_user;
            oBaru.kode           = ebook[indexBuku].kode;
            oBaru.judul          = ebook[indexBuku].judul;
            oBaru.harga          = ebook[indexBuku].harga;
            oBaru.total_harga    = ebook[indexBuku].harga;
            oBaru.tanggal_pesan  = tgl;
            oBaru.tanggal_kirim  = 0;
            oBaru.tanggal_sampai = 0;
            oBaru.batal_oleh     = "";
            oBaru.alasan         = "";

            // Pilihan BAYAR SEKARANG
            if (pilihBayar == 0) {
                if (akun[index_login].saldo < ebook[indexBuku].harga) {
                    tampilPeringatan(40, "Saldo tidak mencukupi! Gunakan fitur bayar nanti atau top up saldo.");
                    system("pause");
                    continue; // Kembali putar menu pilihan
                }
                akun[index_login].saldo -= ebook[indexBuku].harga;
                oBaru.status_order = "Diproses Admin";
                oBaru.status_bayar = "Lunas";
                
                saveAkun(akun);
                order.push_back(oBaru);
                saveOrder(order);
                tampilPesan(40, "Pembayaran berhasil! Pesanan sedang diproses admin.");
                break;
            }
            
            // Pilihan BAYAR NANTI
            else if (pilihBayar == 1) {
                oBaru.status_order = "Menunggu Pembayaran";
                oBaru.status_bayar = "Belum Lunas";
                
                order.push_back(oBaru);
                saveOrder(order);
                tampilPesan(40, "Pesanan disimpan! Bayar melalui menu Daftar Pesanan.");
                break;
            }
        }
    }
}


void lihatDaftarKeranjang(vector<Keranjang> &keranjang, string id_user) {
    cout << CYAN << BOLD;
    cout << "  ┌──────┬────────────────┬────────────────────────────────────┬────────────────┐" << endl;
    cout << "  │                               KERANJANG BELANJA                             │" << endl;
    cout << "  ├──────┼────────────────┼────────────────────────────────────┼────────────────┤" << endl;
    cout << "  │ NO   │ KODE           │ JUDUL                              │ HARGA          │" << endl;
    cout << "  ├──────┼────────────────┼────────────────────────────────────┼────────────────┤" << endl;
    cout << RESET;
    
    int no = 1, total = 0;
    bool ada = false;

    for (auto &k : keranjang) {
        if (k.id_user == id_user) {
            cout << "  ";
            if (no % 2 == 0) cout << "\033[48;5;235m";
            
            cout << "│ " << left << setw(5)  << no
                 << "│ " << setw(15) << k.kode
                 << "│ " << setw(35) << k.judul
                 << "│ Rp" << setw(13) << k.harga 
                 << "│" << RESET << endl;
                 
            total += k.harga;
            no++;
            ada = true;
        }
    }

    if (!ada) {
        cout << "  │ " << left << setw(75) << "                       Keranjang belanjamu kosong." << "│\n";
        cout << CYAN;
        cout << "  └──────┴────────────────┴────────────────────────────────────┴────────────────┘" << endl;
    } else {
        cout << CYAN;
        cout << "  ├──────┴────────────────┴────────────────────────────────────┼────────────────┤" << endl;
        string strTotal = "Rp" + to_string(total);
        cout << "  │" << right << setw(59) << "TOTAL HARGA │ " << left << setw(15) << strTotal << "│" << endl;
        cout << "  └────────────────────────────────────────────────────────────┴────────────────┘" << endl;
    }
    cout << RESET << endl;
}


void hapusEbookDariKeranjang(vector<Keranjang> &keranjang, string id_user) {
    string kodeHapus;
    cout << "  Masukkan Kode E-Book yang ingin dihapus (Ketik '0' untuk batal): ";
    cin >> kodeHapus;

    if (kodeHapus == "0") {
        tampilPeringatan(40, "Penghapusan dibatalkan.");
        return; 
    }

    try {
        int indexHapus = -1;
        for (size_t i = 0; i < keranjang.size(); i++) {
            if (keranjang[i].id_user == id_user && keranjang[i].kode == kodeHapus) {
                indexHapus = i;
                break;
            }
        }

        if (indexHapus == -1) throw "Kode E-Book tidak ditemukan di keranjang Anda!";

        keranjang.erase(keranjang.begin() + indexHapus);
                
        tampilPesan(40, "E-Book berhasil dihapus dari keranjang!");
    } catch (const char* e) {
        tampilPeringatan(40, e);
    }
}

void checkoutDariKeranjang(vector<Keranjang> &keranjang, vector<Order> &order, vector<Akun> &akun, int index_login) {
    int pilihMenu = 0;
    bool refreshMenu = true;

    while (true) {
        int jumlahKeranjang = 0;
        for (const auto& k : keranjang) {
            if (k.id_user == akun[index_login].id_user) jumlahKeranjang++;
        }

        if (jumlahKeranjang == 0) {
            if (refreshMenu) system("cls");
            tampilPeringatan(40, "Keranjang Anda kosong!");
            system("pause > nul");
            break;
        }

        if (refreshMenu) { system("cls"); refreshMenu = false; }
        
        clsScroll(0,0);
        lihatDaftarKeranjang(keranjang, akun[index_login].id_user);

        string opsiMenu[] = {
            "『   Checkout Barang       』",
            "『   Hapus dari Keranjang  』",
            "『   Kembali               』"
        };

        cout << "\n  Opsi Keranjang:\n\n";
        for (int i = 0; i < 3; i++) {
            if (i == pilihMenu) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << opsiMenu[i] << RESET << endl;
            else cout << DIM << spasi(20) << opsiMenu[i] << RESET << endl;
        }

        int hasilMenu = scrollMenu(pilihMenu, 3);
        
        if (hasilMenu == -1) {
            refreshMenu = true; 

            if (pilihMenu == 2) {
                break; 
            }
            
            else if (pilihMenu == 0) {
                string kodeCari;
                cout << "\n  Masukkan Kode (Ketik 'ALL' untuk beli semua, atau '0' untuk batal): ";
                cin >> kodeCari;

                if (kodeCari == "0") continue;

                vector<Keranjang> itemDipesan;
                
                if (kodeCari == "ALL" || kodeCari == "all") {
                    for (const auto& k : keranjang) {
                        if (k.id_user == akun[index_login].id_user) itemDipesan.push_back(k);
                    }
                } else {
                    for (const auto& k : keranjang) {
                        if (k.id_user == akun[index_login].id_user && k.kode == kodeCari) {
                            itemDipesan.push_back(k);
                            break;
                        }
                    }
                }

                if (itemDipesan.empty()) {
                    tampilPeringatan(40, "Item tidak ditemukan di keranjang!");
                    system("pause > nul");
                    continue;
                }

                time_t now = time(0); 
                tm *ltm = localtime(&now);
                int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;

                for (auto &item : itemDipesan) {
                    Order o;
                    o.id_order       = "ORD-" + to_string(time(0)) + item.kode;
                    o.id_user        = akun[index_login].id_user;
                    o.kode           = item.kode;
                    o.judul          = item.judul;
                    o.harga          = item.harga;
                    o.total_harga    = item.harga;
                    o.tanggal_pesan  = tgl;
                    o.tanggal_kirim  = 0;
                    o.tanggal_sampai = 0;
                    o.batal_oleh     = "";
                    o.alasan         = "";

                    if (akun[index_login].saldo >= item.harga) {
                        akun[index_login].saldo -= item.harga;
                        o.status_order = "Diproses Admin";
                        o.status_bayar = "Lunas";
                    } else {
                        o.status_order = "Menunggu Pembayaran";
                        o.status_bayar = "Belum Lunas";
                    }

                    order.push_back(o);
                    
                    for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                        if (it->kode == item.kode && it->id_user == o.id_user) {
                            it = keranjang.erase(it);
                        } else {
                            ++it;
                        }
                    }
                }

                saveOrder(order);
                saveAkun(akun);
                saveKeranjang(keranjang);
                tampilPesan(40, "Checkout berhasil diproses! Silakan cek menu Pesanan.");
                system("pause > nul");
            }

            else if (pilihMenu == 1) {
                string kodeHapus;
                cout << "\n  Masukkan Kode E-Book yang ingin dihapus (Ketik '0' untuk batal): ";
                cin >> kodeHapus;

                if (kodeHapus == "0") continue;

                bool terhapus = false;
                for (auto it = keranjang.begin(); it != keranjang.end(); ) {
                    if (it->kode == kodeHapus && it->id_user == akun[index_login].id_user) {
                        it = keranjang.erase(it);
                        terhapus = true;
                        break; 
                    } else {
                        ++it;
                    }
                }

                if (terhapus) {
                    saveKeranjang(keranjang);
                    tampilPesan(40, "Item berhasil dihapus dari keranjang!");
                } else {
                    tampilPeringatan(40, "Kode E-Book tidak ditemukan.");
                }
                system("pause > nul");
            }
        }
    }
}

void pesananBelumDibayar(vector<Order> &order, vector<Akun> &akun, int index_login) {
    system("cls");
    judul_subjudul("PESANAN BELUM DIBAYAR");
    
    string id_cari = akun[index_login].id_user;
    bool ditemukan = false;
    int no = 1;

    cout << endl;
    cout << spasi(15) << "┌──────┬──────────────┬──────────────────────────┬─────────────┐" << endl;
    cout << spasi(15) << "│ No   │ ID Order     │ Judul E-Book             │ Total Harga │" << endl;
    cout << spasi(15) << "├──────┼──────────────┼──────────────────────────┼─────────────┤" << endl;

    for (int i = 0; i < order.size(); i++) {
        if (order[i].id_user == id_cari && order[i].status_bayar == "Belum Lunas") {
            cout << spasi(15) << "│ " << left << setw(5) << no++ 
                 << "│ " << setw(13) << order[i].id_order 
                 << "│ " << setw(25) << (order[i].judul.length() > 22 ? order[i].judul.substr(0, 22) + ".." : order[i].judul)
                 << "│ Rp" << setw(9) << order[i].total_harga << "│" << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << spasi(15) << "│      Tidak ada pesanan yang perlu dibayar secara lunas       │" << endl;
        cout << spasi(15) << "└──────────────────────────────────────────────────────────────┘" << endl;
        cout << "\n" << spasi(45); 
        system("pause");
        return; 
    }
    
    cout << spasi(15) << "└──────┴──────────────┴──────────────────────────┴─────────────┘" << endl;

    string pilihanPesanan[] = {
        "【 1 | Bayar Sekarang     】",
        "【 2 | Batalkan Pesanan   】",
        "【 3 | Kembali            】"
    };
    int pilih = 0;

    while (true) {
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(35) << BG_PUTIH << HITAM << BOLD << pilihanPesanan[i] << RESET << endl;
            else cout << DIM << spasi(35) << pilihanPesanan[i] << RESET << endl;
        }

        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            if (pilih == 0) {
                string idOrder;
                cout << "\n" << spasi(35) << "Masukkan ID Order: "; 
                cin >> idOrder;
                
                bool orderKetemu = false;
                for (int i = 0; i < order.size(); i++) {
                    if (order[i].id_order == idOrder && order[i].id_user == id_cari && order[i].status_bayar == "Belum Lunas") {
                        orderKetemu = true;
                        if (akun[index_login].saldo >= order[i].total_harga) {
                            akun[index_login].saldo -= order[i].total_harga;
                            order[i].status_bayar = "Lunas";
                            order[i].status_order = "Diproses Admin";
                            saveAkun(akun);
                            saveOrder(order);
                            tampilPesan(35, "Pembayaran Berhasil!");
                        } else {
                            tampilPeringatan(35, "Saldo tidak cukup!");
                        }
                        break;
                    }
                }
                if (!orderKetemu) tampilPeringatan(35, "ID Order salah!");
                system("pause"); 
                break; 
            } 
            else if (pilih == 1) {
                string idOrder;
                cout << "\n" << spasi(35) << "Masukkan ID Order: "; 
                cin >> idOrder;
                
                bool orderKetemu = false;
                for (int i = 0; i < order.size(); i++) {
                    if (order[i].id_order == idOrder && order[i].id_user == id_cari && order[i].status_bayar == "Belum Lunas") {
                        orderKetemu = true;
                        order[i].status_order = "Dibatalkan";
                        order[i].status_bayar = "Dibatalkan";
                        order[i].batal_oleh = "User";
                        saveOrder(order);
                        tampilPesan(35, "Pesanan Dibatalkan!");
                        break;
                    }
                }
                if (!orderKetemu) tampilPeringatan(35, "ID Order salah!");
                system("pause"); 
                break;
            } 
            else break; 
        }
        cout << "\033[3A";
    }
} 

void pesananDiproses(vector<Order> &order, string id_user) {
    lihatPesananUser("Diproses Admin", order, id_user);
}


void pesananDikirim(vector<Order> &order, vector<Library> &lib, string id_user, string username) {
    int pilihMenu = 0;
    bool refreshMenu = true;

    while (true) {
        if (refreshMenu) { system("cls"); refreshMenu = false; }
        
        clsScroll(0,0);
        lihatPesananUser("Dikirim", order, id_user);

        int jumlahPesanan = 0;
        for (const auto& o : order) {
            if (o.id_user == id_user && o.status_order == "Dikirim") {
                jumlahPesanan++;
            }
        }

        if (jumlahPesanan == 0) {
            cout << "\n  Pilih Aksi:\n\n";
            cout << spasi(20) << BG_PUTIH << HITAM << BOLD << "『   Kembali               』" << RESET << endl;
            system("pause > nul"); 
            break;
        }

        string opsiMenu[] = {
            "『   Pesanan Diterima      』",
            "『   Kembali               』"
        };

        cout << "\n  Pilih Aksi:\n\n";
        for (int i = 0; i < 2; i++) {
            if (i == pilihMenu) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << opsiMenu[i] << RESET << endl;
            else cout << DIM << spasi(20) << opsiMenu[i] << RESET << endl;
        }

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
                    if (order[i].id_user == id_user && order[i].id_order == id_selesai && order[i].status_order == "Dikirim") {
                        order[i].status_order = "Selesai";
                        
                        Library lBaru;
                        lBaru.id_user    = id_user;
                        lBaru.username   = username;
                        lBaru.buku.kode  = order[i].kode;
                        lBaru.buku.judul = order[i].judul; 
                        lib.push_back(lBaru);

                        saveOrder(order);
                        saveLibrary(lib);
                        tampilPesan(45, "Pesanan Selesai! E-Book ditambahkan ke Library.");
                        ketemu = true;
                        break;
                    }
                }
                
                if (!ketemu) tampilPeringatan(35, "ID Order tidak valid.");
                system("pause"); 
            }
        }
    }
}


void editSaldo(vector<Akun> &akun, int index_login) {
    cout << "\n";
    cout << spasi(50) << "┌────────────────────────────────────┐" << endl;
    cout << spasi(50) << "│        TOP UP / EDIT SALDO         │" << endl;
    cout << spasi(50) << "├────────────────────────────────────┤" << endl;
    cout << spasi(50) << "│ Saldo Saat Ini : Rp" << left << setw(16) << akun[index_login].saldo << "│" << endl;
    cout << spasi(50) << "├────────────────────────────────────┤" << endl;
    cout << spasi(50) << "│ Nominal Top Up : Rp";

    string inputNominal;
    cin >> inputNominal;

    cout << spasi(50) << "└────────────────────────────────────┘" << endl;

    if (inputNominal == "0") {
        tampilPeringatan("Top Up dibatalkan.");
        return;
    }

    for (size_t i = 0; i < inputNominal.length(); i++) {
        if (!isdigit((unsigned char)inputNominal[i])) {
            tampilPeringatan("Nominal hanya boleh berisi angka tanpa tanda apapun!");
            return;
        }
    }

    long long nominal = 0;
    try {
        nominal = stoll(inputNominal);
    } catch (...) {
        tampilPeringatan("Nominal terlalu besar atau tidak valid!");
        return;
    }

    if (nominal <= 0) {
        tampilPeringatan("Nominal harus lebih dari 0!");
        return;
    }

    akun[index_login].saldo += (int)nominal;
    saveAkun(akun);

    cout << endl;
    cout << spasi(50) << "Saldo sekarang : Rp" << akun[index_login].saldo << endl;
    tampilPesan("Top Up Berhasil!");
}


void kelolaAkunDiri(vector<Akun> &akun, int index_login) {
    string pilihMenuUser[] = {
        "【 1 | Edit Data Diri     】",
        "【 2 | Kembali            】"
    };
    int pilih = 0;
    
    while (true) {
        system("cls"); 
        judul_subjudul("KELOLA AKUN DIRI"); 
        cout << endl;
        lihatDataDiri(akun, index_login);
        
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(20) << pilihMenuUser[i] << RESET << endl;
        }
        
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
            if (pilih == 0) {
                system("cls"); judul_subjudul("EDIT DATA DIRI");
                editDataDiri(akun, index_login);
                system("pause");
            } else break;
        }
    }
}

void belanjaUser(vector<Ebook> &ebook, vector<Keranjang> &keranjang, vector<Order> &order, vector<Akun> &akun, int index_login) {
    string pilihMenuUser[] = {
        "【 1 | Tambah Keranjang   】",
        "【 2 | Pesan Sekarang      】",
        "【 3 | Urutkan Katalog     】",
        "【 4 | Cari E-Book         】",
        "【 5 | Kembali             】"
    };
    int pilih = 0;
    
    while (true) {
        system("cls"); 
        judul_subjudul("MENU PEMESANAN"); 
        cout << endl;
        
        for (int i = 0; i < 5; i++) {
            if (i == pilih) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(20) << pilihMenuUser[i] << RESET << endl;
        }
        
        cout << "\n  DAFTAR KATALOG E-BOOK:\n";
        lihatDaftarEbook(ebook);

        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
            if (pilih == 0) {
                system("cls"); tambahProdukkeKeranjang(ebook, keranjang, akun[index_login].id_user);
                system("pause");
            } else if (pilih == 1) {
                system("cls"); checkoutDariKatalog(ebook, order, akun, index_login);
                system("pause");
            } else if (pilih == 2) {
                urutEbook(ebook); tampilPesan(20, "Katalog diurutkan!");
                system("pause");
            } else if (pilih == 3) {
                system("cls"); cariEbook(ebook);
                system("pause");
            } else break;
        }
    }
}

void keranjangUser(vector<Keranjang> &keranjang, vector<Akun> &akun, vector<Order> &order, int index_login) {
    string pilihMenuUser[] = {
        "【 1 | Hapus E-Book       】",
        "【 2 | Pesan Keranjang    】",
        "【 3 | Kembali            】"
    };
    int pilih = 0;
    
    while (true) {
        system("cls"); 
        judul_subjudul("KERANJANG BELANJA"); 
        cout << endl;
        
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(20) << pilihMenuUser[i] << RESET << endl;
        }
        
        lihatDaftarKeranjang(keranjang, akun[index_login].id_user);
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            if (pilih == 0) {
                system("cls"); hapusEbookDariKeranjang(keranjang, akun[index_login].id_user);
                system("pause");
            } else if (pilih == 1) {
                system("cls"); checkoutDariKeranjang(keranjang, order, akun, index_login);
            } else break;
        }
    }
}

void pesananUser(vector<Order> &order, vector<Akun> &akun, int index_login, vector<Library> &lib) {
    string pilihMenuUser[] = {
        "【 1 | Belum Dibayar      】",
        "【 2 | Diproses Admin     】",
        "【 3 | Dikirim            】",
        "【 4 | Selesai            】",
        "【 5 | Dibatalkan         】",
        "【 6 | Kembali            】"
    };
    int pilih = 0;
    
    while (true) {
        system("cls"); 
        judul_subjudul("DAFTAR PESANAN"); 
        cout << endl;
        
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(20) << pilihMenuUser[i] << RESET << endl;
        }
        
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
            system("cls");
            if (pilih == 0) pesananBelumDibayar(order, akun, index_login);
            else if (pilih == 1) { pesananDiproses(order, akun[index_login].id_user); system("pause"); }
            else if (pilih == 2) pesananDikirim(order, lib, akun[index_login].id_user, akun[index_login].username);
            else if (pilih == 3) { lihatPesananUser("Selesai", order, akun[index_login].id_user); system("pause"); }
            else if (pilih == 4) { lihatPesananUser("Dibatalkan", order, akun[index_login].id_user); system("pause"); }
            else break;
        }
    }
}


void lihatLibraryUser(vector<Library> &lib, string id_user) {
    cout << CYAN << BOLD;
    cout << "  ┌──────┬────────────────┬───────────────────────────────┬─────────────────────┬────────────────┬───────┐" << endl;
    cout << "  │                                  PERPUSTAKAAN E-BOOK MILIKMU                                       │" << endl;
    cout << "  ├──────┼────────────────┼───────────────────────────────┼─────────────────────┼────────────────┼───────┤" << endl;
    cout << "  │ NO   │ KODE           │ JUDUL                         │ PENULIS             │ GENRE          │ TAHUN │" << endl;
    cout << "  ├──────┼────────────────┼───────────────────────────────┼─────────────────────┼────────────────┼───────┤" << endl;
    cout << RESET;
    
    bool ada = false;
    int no = 1;

    for (size_t i = 0; i < lib.size(); i++) {
        if (lib[i].id_user == id_user) {
            cout << "  ";
            if (no % 2 == 0) cout << "\033[48;5;235m";
            
            cout << "│ " << left << setw(5)  << no
                 << "│ " << setw(15) << lib[i].buku.kode
                 << "│ " << setw(30) << lib[i].buku.judul
                 << "│ " << setw(20) << lib[i].buku.penulis
                 << "│ " << setw(15) << lib[i].buku.genre
                 << "│ " << setw(6)  << lib[i].buku.tahun
                 << "│" << RESET << endl;
            ada = true;
            no++;
        }
    }

    if (!ada) {
        cout << "  │ " << left << setw(99) << "                              Library kamu masih kosong!" << "│\n";
    }

    cout << CYAN;
    cout << "  └──────┴────────────────┴───────────────────────────────┴─────────────────────┴────────────────┴───────┘" << endl;
    cout << RESET << endl;
}


void saldoDanTransaksi(vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    string pilihMenuUser[] = {
        "【 1 | Top Up Saldo       】",
        "【 2 | Riwayat Transaksi  】",
        "【 3 | Kembali            】"
    };
    int pilih = 0;
    
    while (true) {
        system("cls"); 
        judul_subjudul("SALDO & TRANSAKSI"); 
        cout << endl;
        cout << spasi(48) << "┌────────────────────────────────┐" << endl;
        cout << spasi(48) << "│ Saldo: Rp" << left << setw(22) << akun[indeksLogin].saldo << "│" << endl;
        cout << spasi(48) << "└────────────────────────────────┘" << endl << endl;
        
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(20) << pilihMenuUser[i] << RESET << endl;
        }
        
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
            if (pilih == 0) { system("cls"); editSaldo(akun, indeksLogin); system("pause"); }
            else if (pilih == 1) { system("cls"); lihatRiwayatTransaksi(transaksi); system("pause"); }
            else break;
        }
    }
}

void menuUser(vector<Akun> &akun, int indeksLogin, vector<Ebook> &ebook, vector<Library> &library, vector<Order> &order, vector<Transaksi> &transaksi, vector<Keranjang> &keranjang) {
    string pilihMenuUser[] = {
        "【 1 | Kelola Akun Anda   】",
        "【 2 | Belanja Sekarang   】",
        "【 3 | Keranjang Belanja  】",
        "【 4 | Daftar Pesanan     】",
        "【 5 | Perpustakaan Anda  】",
        "【 6 | Saldo & Transaksi  】",
        "【 7 | Logout             】"
    };
    int pilih = 0;
    
    while (true) {
        system("cls"); 
        judul_subjudul("HALO, USER " + akun[indeksLogin].username);
        cout << endl;
        cout << spasi(48) << "┌────────────────────────────────┐" << endl;
        cout << spasi(48) << "│ Saldo: Rp" << left << setw(22) << akun[indeksLogin].saldo << "│" << endl;
        cout << spasi(48) << "└────────────────────────────────┘" << endl << endl;
        
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << spasi(20) << BG_PUTIH << HITAM << BOLD << pilihMenuUser[i] << RESET << endl;
            else cout << DIM << spasi(20) << pilihMenuUser[i] << RESET << endl;
        }
        
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {
            if (pilih == 0) kelolaAkunDiri(akun, indeksLogin);
            else if (pilih == 1) belanjaUser(ebook, keranjang, order, akun, indeksLogin);
            else if (pilih == 2) keranjangUser(keranjang, akun, order, indeksLogin);
            else if (pilih == 3) pesananUser(order, akun, indeksLogin, library);
            else if (pilih == 4) { system("cls"); lihatLibraryUser(library, akun[indeksLogin].id_user); system("pause"); }
            else if (pilih == 5) saldoDanTransaksi(akun, indeksLogin, transaksi);
            else { tampilPesan(20, "Logout berhasil!"); system("pause"); break; }
        }
    }
}

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