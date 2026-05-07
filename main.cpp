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

int tambahEbook(vector<Ebook> &katalog) {
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
    baru.no = generateNo(katalog);
    baru.kode = generateKode(katalog, baru.judul, baru.penulis, baru.tahun);
    
    katalog.push_back(baru);

    cout << "\n     NO    : " << baru.no << endl;
    cout << "     Kode  : " << baru.kode << endl;
    tampilPesan(30, "E-book berhasil ditambahkan!");

    return 1;}

void editEbook() {}

void hapusEbook() {}

void urutEbook() {}

void cariEbook() {}

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

void lihatRiwayatPesanan() {}

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
                editEbook();
                system("pause");}

            /* c. HAPUS E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Hapus E-Book"); cout << endl;
                hapusEbook();
                system("pause");}

            /* d. URUT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                urutEbook();
                system("pause");}

            /* e. CARI E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 4) {
                cariEbook();
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
void kelolaAkunDiri() {
    string pilihMenuUser[] = {
        "   1 | Edit Data Diri",
        "   2 | Kembali",    };
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Kelola Akun Diri"); cout << endl;
        lihatDataDiri();
        for (int i = 0; i < 2; i++) {
            if (i == pilih) cout << "> " << *(pilihMenuUser + i) << endl;
            else cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 2);
        if (hasil == -1) {
    
            /* a. EDIT DATA DIRI
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                system("cls"); judul_subjudul("Edit Data Diri"); cout << endl;
                editDataDiri();
                system("pause");}

            /* b. KEMBALI
            ════════════════════════════════════════════════════*/
            else {
                break;}}}}

void belanjaUser() {
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
                tambahProdukkeKeranjang();
                system("pause");}

            /* b. PESAN SEKARANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Pesan Sekarang"); cout << endl;
                checkoutDariKatalog();
                system("pause");}

            /* c. URUT E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                urutEbook();
                system("pause");}

            /* d. CARI E-BOOK
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                cariEbook();
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
                hapusEbookDariKeranjang();
                system("pause");}

            /* b. PESAN KERANJANG
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Pesan Keranjang"); cout << endl;
                checkoutDariKeranjang();
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
                pesananBelumDibayar();
                system("pause");}

            /* b. DAFTAR PESANAN DIPROSES
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Daftar Pesanan Diproses"); cout << endl;
                pesananDiproses();
                system("pause");}

            /* c. DAFTAR PESANAN DIKIRIM
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Daftar Pesanan Dikirim"); cout << endl;
                pesananDikirim();
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

void saldoDanTransaksi(vector<Akun> &akun, int indeksLogin) {
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
                lihatRiwayatTransaksi();
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
                belanjaUser();
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
                saldoDanTransaksi(akun, indeksLogin);
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