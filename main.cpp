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
    ifstream file("data/akun.json");
    if (!file.is_open()) return;
    json j; file >> j;
    for (auto &item : j) {
        Akun a;
        a.id_user = item["id_user"];
        a.username = item["username"];
        a.password = item["password"];
        a.role = item["role"];
        a.status_akun = item["status_akun"];
        a.email = item["email"];
        a.alamat = item["alamat"];
        a.no_hp = item["no_hp"];
        a.tanggal_daftar = item["tanggal_daftar"];
        a.saldo = item["saldo"];
        akun.push_back(a);}}

void loadEbook(vector<Ebook> &ebook) {
    ifstream file("data/ebook.json");
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
    ifstream file("data/library.json");
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
    ifstream file("data/order.json");
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
    ifstream file("data/transaksi.json");
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
    ifstream file("data/keranjang.json");
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
    ofstream file("data/akun.json");
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
    ofstream file("data/ebook.json");
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
    ofstream file("data/library.json");
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
    ofstream file("data/order.json");
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
    ofstream file("data/transaksi.json");
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
    ofstream file("data/keranjang.json");
    file << setw(4) << j;}



/* PROSEDUR DAN FUNGSI BANTU
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void judul_subjudul(string subjudul) {
    int spasiKiri = (80 - subjudul.length()) / 2;
    cout << "╔════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    ☕📓   E-BOOKIE STORE   📓☕                   ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════════════╝" << endl;
    cout << "      ══════════════════════════════════════════════════════════      " << endl;
    cout << string(spasiKiri, ' ') << subjudul << endl;
    cout << "      ══════════════════════════════════════════════════════════      " << endl;}

void tampilPesan(int nilai, string pesan) {
    cout << "\033[1;32m" << endl;
    cout << setw((80 + 26) / 2) << "=========================" << endl;
    cout << setw((80 + nilai) / 2) << pesan << endl;
    cout << setw((80 + 26) / 2) << "=========================" << endl;
    cout << "\033[0m" << endl;}

void tampilPeringatan(int nilai, string pesan) {
    cout << "\033[1;31m" << endl;
    cout << setw((80 + 34) / 2) << "---------------------------------" << endl;
    cout << setw((80 + nilai) / 2) << pesan << endl;
    cout << setw((80 + 34) / 2) << "---------------------------------" << endl;
    cout << "\033[0m" << endl;}

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

int scrollBuku(vector<Ebook> &katalog, string judulMenu) {
    int pilih = 0;

    while(true){
        system("cls"); judul_subjudul(judulMenu);
        cout << "" << endl;
        for(int i = 0; i < katalog.size(); i++){
            if(i == pilih)
                cout << "> " << katalog[i].judul << endl;
            else
                cout << "  " << katalog[i].judul << endl;}
        int hasil = scrollMenu(pilih, katalog.size());
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
    return hasil;}

string generateKode(vector<Ebook> &katalog, string judul, string penulis, int tahun) {
    int nomor = 1;
    string nomorStr, inisialJudul = inisialKode(judul), inisialPenulis = inisialKode(penulis);

    for (int i = 0; i < katalog.size(); i++) {
        if (katalog[i].judul == judul &&
            katalog[i].penulis == penulis &&
            katalog[i].tahun == tahun) {
            nomor++;}}
    if (nomor < 10) nomorStr = "00" + to_string(nomor);
    else if (nomor < 100) nomorStr = "0" + to_string(nomor);
    else nomorStr = to_string(nomor);
    return inisialJudul + inisialPenulis + to_string(tahun) + nomorStr;}

int generateNo(vector<Ebook> &katalog) {
    for (int i = 1; i <= katalog.size() + 1; i++) {
        bool ada = false;
        for (int j = 0; j < katalog.size(); j++) {
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
    for (int i = 0; i < ebook.size() - 1; i++) {
        for (int j = 0; j < ebook.size() - i - 1; j++) {
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

            if (tukar) {
                swap(ebook[j], ebook[j + 1]);}}}}

int linearSearchEbook(vector<Ebook> &ebook, vector<Ebook> &hasil, int jenis, string keyword = "", int min = 0, int max = 0) {
    hasil.clear();
    string key = ubahStringKecilSemua(keyword);
    for (int i = 0; i < ebook.size(); i++) {

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
int login(vector<Akun> &akun) {
    string jawabNama, jawabPassword;

    cout << "\n     Username: "; cin >> jawabNama;
    cout << "     Password: "; cin >> jawabPassword;
    for (int i = 0; i < akun.size(); i++) {
        if (akun[i].username == jawabNama && akun[i].password == jawabPassword) {
            tampilPesan(38, "Login berhasil! Selamat datang, " + jawabNama);
            system("pause"); return i;}}
    return -1;}

void registrasi(vector<Akun> &akun) {
    string username, password, email, no_hp, alamat;
    
    cout << "\n     Username: "; cin >> username;
    cout << "     Password: "; cin >> password;
    cout << "     Email: "; cin >> email;
    cout << "     No HP: "; cin >> no_hp;
    cout << "     Alamat: "; cin >> alamat;

    if (username.empty() || password.empty() || email.empty() || no_hp.empty() || alamat.empty()) {
        tampilPeringatan(30, "Semua kolom harus diisi!"); return;}
    regex userRegex("^[a-zA-Z0-9_ ]{5,}$");
    regex passRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).{8,}$");
    regex hpRegex("^08\\d{8,12}$");
    if (!regex_match(username, userRegex)) {
        tampilPeringatan(40, "Username tidak valid!"); return;}
    if (!regex_match(password, passRegex)) {
        tampilPeringatan(45, "Password harus 8 karakter + huruf besar, kecil, angka!"); return;}
    if (!regex_match(no_hp, hpRegex)) {
        tampilPeringatan(35, "No HP tidak valid!"); return;}
    if (email.find("@gmail.com") == string::npos) {
        tampilPeringatan(40, "Email harus @gmail.com!");return;}

    for (auto &a : akun) {
        if (a.username == username) {
            tampilPeringatan(30, "Username sudah ada!"); return;}
        if (a.email == email) {
            tampilPeringatan(30, "Email sudah digunakan!"); return;}}
    string newID = "U" + to_string(1000 + akun.size());
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
    baru.status_akun = "aktif";
    baru.email = email;
    baru.no_hp = no_hp;
    baru.alamat = alamat;
    baru.tanggal_daftar = tanggal;
    baru.saldo = 0;

    akun.push_back(baru);
    tampilPesan(36, "Registrasi berhasil!");
}



/* FUNGSI MENU ADMIN
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatDaftarPelanggan(vector<Akun> &akun) {
    cout << "NO | USERNAME         | EMAIL                | NO HP          | ALAMAT              | STATUS AKUN" << endl;
    cout << "---+------------------+----------------------+-----------------+---------------------+-------------" << endl;
    for (int i = 0; i < akun.size(); i++) {
        if (akun[i].role == "user") {
            cout << left
                << setw(3) << i + 1 << "| " << setw(17) << akun[i].username << "| "
                << setw(20) << akun[i].email << "| "
                << setw(16) << akun[i].no_hp << "| "
                << setw(21) << akun[i].alamat << "| "
                << setw(12) << akun[i].status_akun
                << endl;}}
    cout << endl;}

void editStatusPelanggan() {}


void lihatDaftarEbook(vector<Ebook> &ebook) {
    if (ebook.empty()) {
        tampilPesan(28, "Katalog E-book belum terisi.");
        return;}
    cout << "NO | KODE           | JUDUL                    | PENULIS             | TAHUN   | GENRE     | HARGA    " << endl;
    cout << "---+----------------+--------------------------+---------------------+---------+-----------+----------" << endl;
    for (int i = 0; i < ebook.size(); i++) {
        cout << left
            << setw(3) << ebook[i].no << "| "<< setw(15) << ebook[i].kode << "| "
            << setw(25) << ebook[i].judul << "| "
            << setw(20) << ebook[i].penulis << "| " << setw(8) << ebook[i].tahun << "| "
            << setw(10) << ebook[i].genre << "| " << setw(10) << ebook[i].harga
            << endl;}
    cout << endl;}

int tambahEbook(vector<Ebook> &ebook) {
    Ebook baru;

    cout << "     Judul   : "; getline(cin, baru.judul);
    cout << "     Penulis : "; getline(cin, baru.penulis);
    try {
        cout << "     Tahun   : "; cin >> baru.tahun;
        if (cin.fail() || baru.tahun <= 0) {
            throw "Tahun harus berupa angka, tidak boleh minus atau 0!";}
        cin.ignore(numeric_limits<streamsize>::max(), '\n');}
    catch (const char* e) {
        cin.clear(); cin.ignore(1000, '\n');
        tampilPeringatan(50, e);
        return 0;}
    cout << "     Genre   : "; getline(cin, baru.genre);
    try {
        cout << "     Harga   : "; cin >> baru.harga;
        if (cin.fail() || baru.harga <= 0) {
            throw "Harga harus berupa angka, tidak boleh minus atau 0!";}}
    catch (const char* e) {
        cin.clear();
        cin.ignore(1000, '\n');
        tampilPeringatan(54, e);
        return 0;}
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    baru.no = generateNo(ebook);
    baru.kode = generateKode(ebook, baru.judul, baru.penulis, baru.tahun);
    
    ebook.push_back(baru);

    cout << "\n     NO    : " << baru.no << endl;
    cout << "     Kode  : " << baru.kode << endl;
    tampilPesan(30, "E-book berhasil ditambahkan!");

    return 1;}

int editEbook(vector<Ebook> &ebook) {
    string tindakan[] = {
        "   1 | Simpan Perubahan",
        "   2 | Batal Edit"};
    int pilih = 0;

    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi.");
        return 0;}
    int index = scrollBuku(ebook, "Edit E-Book");
    Ebook temp = ebook[index];

    cout << "     Judul lama   : " << ebook[index].judul << endl;
    cout << "     Penulis lama : " << ebook[index].penulis << endl;
    cout << "     Tahun lama   : " << ebook[index].tahun << endl;
    cout << "     Genre lama   : " << ebook[index].genre << endl;
    cout << "     Harga lama   : " << ebook[index].harga << endl;

    cout << "\n     Judul baru   : "; getline(cin, temp.judul);
    cout << "     Penulis baru : "; getline(cin, temp.penulis);
    try {
        cout << "     Tahun baru   : "; cin >> temp.tahun;
        if (cin.fail() || temp.tahun <= 0) {
            throw "Tahun harus angka dan > 0!";}
        cin.ignore(numeric_limits<streamsize>::max(), '\n');}
    catch (const char* e) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        tampilPeringatan(45, e);
        return 0;}
    cout << "     Genre baru   : "; getline(cin, temp.genre);
    try {
        cout << "     Harga baru   : "; cin >> temp.harga;
        if (cin.fail() || temp.harga <= 0) {
            throw "Harga harus angka dan > 0!";}
        cin.ignore(numeric_limits<streamsize>::max(), '\n');}
    catch (const char* e) {
        cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
        tampilPeringatan(45, e);
        return 0;}
    temp.kode = generateKode(ebook, temp.judul, temp.penulis, temp.tahun);
    
    cout << "\n     Simpan perubahan? " << temp.no << endl;
    while(true){
        for(int i = 0; i < 2; i++){
            if(i == pilih) cout << "> " << tindakan[i] << endl;
            else cout << "  " << tindakan[i] << endl;}
        int hasil = scrollMenu(pilih, 2);
        if(hasil == -1) {
            if (pilih == 0) {
                ebook[index] = temp;
                tampilPesan(35, "E-book berhasil diupdate!");
                return 1;}
            else {
                tampilPeringatan(32, "Perubahan dibatalkan!");
                return 0;}}}}

int hapusEbook(vector<Ebook> &ebook) {
    string tindakan[] = {
        "   1 | Simpan Perubahan",
        "   2 | Batal Edit"};
    int pilih = 0;

    if (ebook.empty()) {
        tampilPeringatan(28, "Katalog E-book belum terisi.");
        return 0;}
    int index = scrollBuku(ebook, "Hapus E-Book");

    cout << "     Judul lama   : " << ebook[index].judul << endl;
    cout << "     Penulis lama : " << ebook[index].penulis << endl;
    cout << "     Tahun lama   : " << ebook[index].tahun << endl;
    cout << "     Genre lama   : " << ebook[index].genre << endl;
    cout << "     Harga lama   : " << ebook[index].harga << endl;

    cout << "\n     Hapus E-Book? " << ebook[index].no << endl;
    while(true){
        for(int i = 0; i < 2; i++){
            if(i == pilih) cout << "> " << tindakan[i] << endl;
            else cout << "  " << tindakan[i] << endl;}
        int hasil = scrollMenu(pilih, 2);
        if(hasil == -1) {
            if (pilih == 0) {
                ebook.erase(ebook.begin() + index);
                tampilPesan(35, "E-book berhasil dihapus!");
                return 1;}
            else {
                tampilPeringatan(32, "Perubahan dibatalkan!");
                return 0;}}}}


void urutEbook(vector<Ebook> &ebook) {
    string menuUrut[] = {
        "   1 | Judul",
        "   2 | Penulis",
        "   3 | Genre",
        "   4 | Tahun",
        "   5 | Harga",
        "   6 | Kode",
        "   7 | Kembali"};
    string jenisUrut[] = {
        "   1 | Ascending",
        "   2 | Descending"};
    int pilih = 0;
    int pilihJenis = 0;

    while (true) {
        system("cls"); judul_subjudul("Urutkan Katalog E-Book"); cout << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << "> " << menuUrut[i] << endl;
            else cout << "  " << menuUrut[i] << endl;}
        lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 7);

        if (hasil == -1) {

            // KEMBALI
            if (pilih == 6) {
                break;}

            vector<Ebook> hasil;
            // URUTKAN ASCENDING OR DESCEMDING
            while(true) {
                system("cls"); judul_subjudul("Pilihan Jenis Pengurutan"); cout << endl;
                for (int i = 0; i < 2; i++) {
                    if (i == pilihJenis) cout << "> " << jenisUrut[i] << endl;
                    else cout << "  " << jenisUrut[i] << endl;}
                int hasilJenis = scrollMenu(pilihJenis, 2);

                if (hasilJenis == -1) {
                    bool ascending = (pilihJenis == 0);
                    vector<Ebook> temp = ebook;
                    bubbleSortEbook(temp, pilih, ascending);

                    system("cls"); judul_subjudul("Hasil Pengurutan"); cout << endl;
                    lihatDaftarEbook(temp);
                    system("pause");
                    break;}}}}}

void cariEbook(vector<Ebook> &ebook) {
    string menuCari[] = {
        "   1 | Judul",
        "   2 | Penulis",
        "   3 | Genre",
        "   4 | Tahun",
        "   5 | Harga",
        "   6 | Kode",
        "   7 | Kembali"};
    int pilih = 0;

    while (true) {
        system("cls"); judul_subjudul("Cari E-Book Di Katalog"); cout << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << "> " << menuCari[i] << endl;
            else cout << "  " << menuCari[i] << endl;}
        lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {

            // KEMBALI
            if (pilih == 6) {
                break;}

            vector<Ebook> hasil;
            // CARI JUDUL, PENULIS, GENRE, KODE
            if (pilih == 0 || pilih == 1 || pilih == 2 || pilih == 5) {
                system("cls"); judul_subjudul("Cari E-Book"); cout << endl;
                string keyword;
                cout << "     Masukkan keyword : "; getline(cin, keyword);
                linearSearchEbook(ebook, hasil, pilih + 1, keyword);}

            // CARI TAHUN, HARGA
            else {
                system("cls"); judul_subjudul("Cari E-Book"); cout << endl;
                int min, max;
                try {
                    cout << "     Minimum : "; cin >> min;
                    if (cin.fail() || min < 0) {
                        throw "Minimum harus angka!";}
                    cout << "     Maksimum : "; cin >> max;
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

            system("cls"); judul_subjudul("Hasil Pencarian"); cout << endl;
            if (!hasil.empty()) {lihatDaftarEbook(hasil);}
            else {tampilPeringatan(25, "Data tidak ditemukan!");}
            system("pause");}}}


void lihatDaftarPembelian(vector<Order> &order) {
        cout << "NO | ID ORDER       | USERNAME         | JUDUL                    | HARGA    | TANGGAL PESAN" << endl;
        cout << "---+-----------------+------------------+--------------------------+----------+--------------" << endl;
        for (int i = 0; i < order.size(); i++) {
            cout << left
                << setw(3) << i + 1 << "| " << setw(16) << order[i].id_order << "| "
                << setw(17) << order[i].id_user << "| "
                << setw(25) << order[i].judul << "| "
                << setw(10) << order[i].harga << "| "
                << setw(14) << order[i].tanggal_pesan
                << endl;}
        cout << endl;
}

void cariRiwayatPembelian() {}


void lihatPesanan(string jenis) {}

void lihatRiwayatPesanan() {
    cout << "NO | ID ORDER       | USERNAME         | JUDUL                    | HARGA    | TANGGAL PESAN  | STATUS ORDER" << endl;
    cout << "---+-----------------+------------------+--------------------------+----------+-----------------+-------------" << endl;
    for (int i = 0; i < 10; i++) {
        cout << left
            << setw(3) << i + 1 << "| " << setw(16) << "tes tes dlu" << "| "
            << setw(17) << "user123" << "| "
            << setw(25) << "Contoh E-Book" << "| "
            << setw(10) << 50000 << "| "
            << setw(16) << "2024-01-01" << "| "
            << setw(12) << "Dikirim"
            << endl;}
}

void editStatusPesanan() {}


void lihatRiwayatTransaksi(vector<Transaksi> &transaksi) {}

void kelolaAkunPelanggan(vector<Akun> &akun) {
    string pilihMenuAdmin[] = {
        "   1 | Ubah Status Akun Pelanggan",
        "   2 | Kembali",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Menu Kelola Akun Pelanggan"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuAdmin + i) << endl;
            else cout << "  " << *(pilihMenuAdmin + i) << endl;}
        lihatDaftarPelanggan(akun);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
    
            /* a. EDIT STATUS AKUN PELANGGAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Edit Status Pelanggan"); cout << endl;
                editStatusPelanggan();
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void penjualanAdmin(vector<Ebook> &ebook) {
    string pilihMenuAdmin[] = {
        "   1 | E-Book Baru",
        "   2 | Edit Detail E-Book",
        "   3 | Hapus E-Book",
        "   4 | Urutkan Katalog",
        "   5 | Cari E-Book",
        "   6 | Kembali",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Menu Penjualan"); cout << endl;
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuAdmin + i) << endl;
            else cout << "  " << *(pilihMenuAdmin + i) << endl;}
        lihatDaftarEbook(ebook);
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
    
            /* a. TAMBAH E-BOOK
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Tambah E-Book"); cout << endl;
                tambahEbook(ebook);
                system("pause");}

            /* b. EDIT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Edit E-Book"); cout << endl;
                editEbook(ebook);
                system("pause");}

            /* c. HAPUS E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Hapus E-Book"); cout << endl;
                hapusEbook(ebook);
                system("pause");}

            /* d. URUT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                urutEbook(ebook);
                system("pause");}

            /* e. CARI E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                cariEbook(ebook);
                system("pause");}

            /* f. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pembelianAdmin(vector<Order> &order) {
    string pilihMenuAdmin[] = {
        "   1 | Cari Riwayat Pembelian",
        "   2 | Kembali",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Menu Kelola Akun Pelanggan"); cout << endl;
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuAdmin + i) << endl;
            else cout << "  " << *(pilihMenuAdmin + i) << endl;}
        lihatDaftarPembelian(order);
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
    
            /* a. CARI RIWAYAT PEMBELIAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Cari Riwayat Pembelian"); cout << endl;
                cariRiwayatPembelian();
                system("pause");}

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
                lihatPesanan("BelumBayar");
                system("pause");}

            /* b. DAFTAR PESANAN SUDAH DIBAYAR
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Daftar Pesanan Sudah Dibayar"); cout << endl;
                lihatPesanan("Dibayar");
                system("pause");}

            /* c. UBAH STATUS PESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Ubah Status Pesanan"); cout << endl;
                editStatusPesanan();
                system("pause");}

            /* d. RIWAYAT PESANAN LAINNYA
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Riwayat Pesanan Lainnya"); cout << endl;
                lihatRiwayatPesanan();
                system("pause");}

            /* e. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}


void menuAdmin(vector<Akun> &akun, int indeksLogin, vector<Ebook> &ebook, vector<Order> &order, vector<Transaksi> &transaksi) {
    string pilihMenuAdmin[] = {
        "   1 | Kelola Akun Pelanggan",
        "   2 | Penjualan",
        "   3 | Pembelian",
        "   4 | Pemesanan",
        "   5 | Riwayat Transaksi",
        "   6 | Logout",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Halo, Admin " + akun[indeksLogin].username);
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << setw((70 + 2) / 2) << "Saldo: " << akun[indeksLogin].saldo << endl;
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << "" << endl;
        for (int i = 0; i < 6; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuAdmin + i) << endl;
            else cout << "  " << *(pilihMenuAdmin + i) << endl;}
        int hasil = scrollMenu(pilih, 6);
        if (hasil == -1) {
    
            /* a. MENU ADMIN KELOLA AKUN PELANGGAN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                kelolaAkunPelanggan(akun);
                system("pause");}

            /* b. MENU ADMIN PENJUALAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                penjualanAdmin(ebook);
                system("pause");}

            /* c. MENU ADMIN PEMBELIAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Menu Pembelian"); cout << endl;
                pembelianAdmin(order);
                system("pause");}

            /* d. MENU ADMIN PEMESANAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Menu Pemesanan"); cout << "" << endl;
                pemesananAdmin(order);
                system("pause");}

            /* e. MENU ADMIN RIWAYAT TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("Riwayat Transaksi"); cout << "" << endl;
                lihatRiwayatTransaksi(transaksi);
                system("pause");}

            /* f. MENU ADMIN LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(18, "Logout berhasil!");
                system("pause");
                break;}}}}



/* FUNGSI MENU USER
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
void lihatDataDiri(vector<Akun> &akun, int index_login) {
    system("cls");
    judul_subjudul("Informasi Data Diri");
    cout << "\n    ID User        : " << akun[index_login].id_user
        << "\n    Username       : " << akun[index_login].username
        << "\n    Email          : " << akun[index_login].email
        << "\n    No. HP         : " << akun[index_login].no_hp
        << "\n    Alamat         : " << akun[index_login].alamat
        << "\n    Saldo          : Rp" << akun[index_login].saldo
        << "\n    Status Akun    : " << akun[index_login].status_akun << "\n\n";
}

void editDataDiri(vector<Akun> &akun, int index_login) {
    lihatDataDiri(akun, index_login);
    cout << "  [Tekan Enter jika tidak ingin mengubah data tertentu]\n\n";

    string tempEmail, tempNoHp, tempAlamat, tempPassword;
    cin.ignore();
    
    cout << "    Email baru      : "; getline(cin, tempEmail);
    cout << "    No HP baru      : "; getline(cin, tempNoHp);
    cout << "    Alamat baru     : "; getline(cin, tempAlamat);
    cout << "    Password baru   : "; getline(cin, tempPassword);

    try {
        if (!tempEmail.empty()) {
            if (tempEmail.find("@gmail.com") == string::npos) throw "Format Email harus @gmail.com!";
            akun[index_login].email = tempEmail;
        }
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

void tambahProdukkeKeranjang(vector<Ebook> &ebook, vector<Keranjang> &keranjang, string id_user) {
    lihatDaftarEbook(ebook);
    string kodeCari;
    cout << "    Masukkan Kode E-Book yang ingin ditambahkan: ";
    cin >> kodeCari;

    try {
        int indexBuku = -1;
        for (int i = 0; i < ebook.size(); i++) {
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

void checkoutDariKatalog(vector<Ebook> &ebook, vector<Order> &order, string id_user) {
    lihatDaftarEbook(ebook);
    string kodeCari;
    cout << "    Masukkan Kode E-Book yang ingin langsung dibeli: ";
    cin >> kodeCari;

    try {
        int indexBuku = -1;
        for (int i = 0; i < ebook.size(); i++) {
            if (ebook[i].kode == kodeCari) { indexBuku = i; break; }
        }
        if (indexBuku == -1) throw "Kode E-Book tidak ditemukan!";

        time_t now = time(0); tm *ltm = localtime(&now);
        int tgl = (1900 + ltm->tm_year) * 10000 + (1 + ltm->tm_mon) * 100 + ltm->tm_mday;
        
        Order oBaru;
        oBaru.id_order = "ORD" + to_string(now);
        oBaru.id_user = id_user;
        oBaru.kode = ebook[indexBuku].kode;
        oBaru.judul = ebook[indexBuku].judul;
        oBaru.harga = ebook[indexBuku].harga;
        oBaru.total_harga = ebook[indexBuku].harga;
        oBaru.tanggal_pesan = tgl;
        oBaru.status_order = "Menunggu Pembayaran";
        oBaru.status_bayar = "Belum Lunas";
        
        order.push_back(oBaru);
        saveOrder(order);
        
        tampilPesan(40, "Checkout berhasil! Masuk ke Pesanan.");
    } catch (const char* e) {
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
            it = keranjang.erase(it); // Menghapus elemen dari vector
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
            o.status_order = "Menunggu Pembayaran";
            o.status_bayar = "Belum Lunas";
            
            order.push_back(o);
            keranjang.erase(keranjang.begin() + i); // Hapus dari keranjang
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

void pesananBelumDibayar(vector<Order> &order, vector<Akun> &akun, vector<Library> &lib, int index_login) {
    string id_user = akun[index_login].id_user;
    lihatPesananUser("Menunggu Pembayaran", order, id_user);
    
    char pil;
    cout << "Apakah Anda ingin melakukan pembayaran pesanan? (y/n): ";
    cin >> pil;

    if (tolower(pil) == 'y') {
        string id_bayar;
        cout << "Masukkan ID ORDER: "; cin >> id_bayar;

        for (int i = 0; i < order.size(); i++) {
            if (order[i].id_user == id_user && order[i].id_order == id_bayar && order[i].status_order == "Menunggu Pembayaran") {
                if (akun[index_login].saldo >= order[i].total_harga) {
                    // Potong saldo & ubah status (Modul 4: pointer/reference array struct termodifikasi)
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
    // Hanya sekadar menampilkan pesanan yang statusnya "Diproses Admin"
    lihatPesananUser("Diproses Admin", order, id_user);
    system("pause");
}

void pesananDikirim(vector<Order> &order, vector<Library> &lib, string id_user, string username) {
    // Menampilkan pesanan yang statusnya "Dikirim"
    lihatPesananUser("Dikirim", order, id_user);
    
    char pil;
    cout << "Apakah ada pesanan yang sudah diterima/selesai? (y/n): ";
    cin >> pil;

    if (tolower(pil) == 'y') {
        string id_selesai;
        cout << "Masukkan ID ORDER: "; cin >> id_selesai;

        for (int i = 0; i < order.size(); i++) {
            if (order[i].id_user == id_user && order[i].id_order == id_selesai && order[i].status_order == "Dikirim") {
                order[i].status_order = "Selesai";
                
                // Masukkan e-book ke Library user
                Library lBaru;
                lBaru.id_user = id_user;
                lBaru.username = username;
                // Hanya mengcopy data dasar yang dibutuhkan library
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

/* FUNGSI KELOLA PESANAN USER
══════════════════════════════════════════════════════════════════════════════════════════════════════════════════════*/
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

void editSaldo() {}


void kelolaAkunDiri() {
    string pilihMenuUser[] = {
        "   1 | Edit Data Diri",
        "   2 | Kembali",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Kelola Akun Diri"); cout << endl;
        kelolaAkunDiri();
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
    
            /* a. EDIT DATA DIRI
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Edit Data Diri"); cout << endl;
                kelolaAkunDiri();
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void belanjaUser(vector<Ebook> &ebook) {
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
                tambahProdukkeKeranjang(ebook, keranjang, akunindex_login].id_user);
                system("pause");}

            /* b. PESAN SEKARANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Pesan Sekarang"); cout << endl;
                checkoutDariKatalog(ebook, order, akun[index_login].id_user);
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

void keranjangUser() {
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
        lihatDaftarKeranjang();
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
                checkoutDariKeranjang(ebook, order, akun[index_login].id_user);
                system("pause");}

            /* c. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void pesananUser() {
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
                pesananBelumDibayar(order, akun, lib, index_login);
                system("pause");}

            /* b. DAFTAR PESANAN DIPROSES
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Daftar Pesanan Diproses"); cout << endl;
                pesananDiproses(order, akun, lib, index_login);
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
                lihatPesananUser("Selesai");
                system("pause");}

            /* e. DAFTAR PESANAN DIBATALKAN
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("Daftar Pesanan Dibatalkan"); cout << endl;
                lihatPesananUser("Batal");
                system("pause");}

            /* f. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void lihatLibraryUser() {}

void saldoDanTransaksi(vector<Akun> &akun, int indeksLogin, vector<Transaksi> &transaksi) {
    string pilihMenuUser[] = {
        "   1 | TopUP",
        "   2 | Riwayat Transaksi",
        "   3 | Kembali"};
    int pilih = 0;
    
    while (true) {
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << setw((70 + 2) / 2) << "Saldo: " << akun[indeksLogin].saldo << endl;
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << "" << endl;
        system("cls"); judul_subjudul("Saldo dan Transaksi"); cout << endl;
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {
    
            /* a. TOPUP
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("TopUp Saldo"); cout << endl;
                editSaldo();
                system("pause");}

            /* b. RIWAYAT TRANSAKSI
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
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
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << setw((70 + 2) / 2) << "Saldo: " << akun[indeksLogin].saldo << endl;
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << "" << endl;
        for (int i = 0; i < 7; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 7);
        if (hasil == -1) {
    
            /* a. MENU USER KELOLA AKUN DIRI
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Kelola Akun Anda"); cout << endl;
                kelolaAkunDiri();
                system("pause");}

            /* b. MENU ADMUSERIN BELANJA SEKARANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Belanja Sekarang"); cout << endl;
                belanjaUser(ebook);
                system("pause");}

            /* c. MENU USER KERANJANG BELANJA
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Keranjang Belanja"); cout << endl;
                keranjangUser();
                system("pause");}

            /* d. MENU USER PESANAN USER
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Daftar Pesanan"); cout << "" << endl;
                pesananUser();
                system("pause");}

            /* e. MENU USER LIBRARY USER
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                system("cls"); judul_subjudul("Perpustakaan Milikmu"); cout << "" << endl;
                lihatLibraryUser();
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
        "   1 | Login", 
        "   2 | Register",
        "   3 | Keluar"}; 
    int pilih = 0, salah = 0;

    /* PROGRAM UTAMA
    ════════════════════════════════════════════════════*/
    while (true) {
        system("cls"); judul_subjudul("Selamat Datang");
        for (int i = 0; i < 3; i++) {
            if (i == pilih) cout << "> " << *(pilihMenu + i) << endl;
            else cout << "  " << *(pilihMenu + i) << endl;}
        int hasil = scrollMenu(pilih, 3);
        if (hasil == -1) {

            /* A. LOGIN
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Login Akun Anda");
                int indeksLogin = login(akun);
                if (indeksLogin != -1) {
                    salah = 0;

                    /* 1. MENU ADMIN (CRUD)
                    ════════════════════════════════════════════════════*/
                    if (akun[indeksLogin].role == "admin") {
                        menuAdmin(akun, indeksLogin, ebook, order, transaksi);}

                    /* 2. MENU USER (CRUD)
                    ════════════════════════════════════════════════════*/
                    else {
                        menuUser(akun, indeksLogin, ebook, library, order, transaksi, keranjang);}}

                else {
                    tampilPeringatan(56, "Username atau Password salah atau akun belum terdaftar!");
                    salah++;
                    tampilPeringatan(26, "Kesempatan anda tersisa " + to_string(3 - salah));

                    if (salah == 3) {
                        tampilPesan(52, "Anda telah salah 3 kali. Silakan datang lain kali.");
                        break;}
                    system("pause");} }

            /* 2. REGISTRASI
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Registrasi Akun Anda");
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