#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <cctype>
#include <limits>
#include <regex>
#include <ctime>
using namespace std;


/* STRUCT ADMIN DAN CRUD
════════════════════════════════════════════════════*/
struct Akun {
    string id_user, username, password, role, status_user, tanggal_daftar;
    string email, no_hp, alamat;
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

Akun akun[100] = {
    {"U_A", "admin", "123", "admin", "aktif", "1-10-2025", "admin@example.com", "081234567890", "Jl. Admin No. 1", 1000000},
    {"U_U", "user", "456", "user", "aktif", "1-10-2025", "user@example.com", "081234567891", "Jl. User No. 1", 100000}};

Ebook katalog[300] = {
    {1, "MC2015001", "Magnus Chase 1", "Rick Riordan", 2015, "Fantasi", 70000},
    {2, "TWC2014001", "The Walled City", "Ryan Graudin", 2014, "Drama", 50000},
    {3, "CLS2012001", "City of Lost Souls", "Cassandra Clare", 2012, "Fantasi", 60000},
    {4, "TOA22017001", "The Trials of Apollo 2", "Rick Riordan", 2017, "Fantasi", 50000},
    {5, "TOA32018001", "The Trials of Apollo 3", "Rick Riordan", 2018, "Fantasi", 50000}};

EbookUser ebookUser[100];

int jumlahUser = 2;
int jumlahBuku = 5;
int jumlahEbookUser = 0;
int salah = 0;
int pilih = 0;


/* PROSEDUR DAN FUNGSI BANTU
════════════════════════════════════════════════════*/
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
    return hasil;}

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

    return inisialJudul + inisialPenulis + to_string(tahun) + nomorStr;}

int generateNo(Ebook *katalog, int &jumlahBuku) {
    for (int i = 1; i <= jumlahBuku + 1; i++) {
        bool ada = false;
        for (int j = 0; j < jumlahBuku; j++) {
            if ((katalog + j)->no == i) {
                ada = true;
                break;}}
        if (!ada) {
            return i;}}

    return jumlahBuku + 1;}

string ubahStringKecilSemua(string teks) {
    for (size_t i = 0; i < teks.length(); i++) {
        teks[i] = tolower(teks[i]);}
    return teks;}

string getTanggal() {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    string tgl = to_string(1900 + ltm->tm_year) + "-" +
                 to_string(1 + ltm->tm_mon) + "-" +
                 to_string(ltm->tm_mday);
    return tgl;}

// cek username & email duplikat
bool isDuplicate(string username, string email) {
    for (int i = 0; i < jumlahUser; i++) {
        if (akun[i].username == username || akun[i].email == email) {
            return true;
        }
    }
    return false;}


/* SORTING & SEARCHING
════════════════════════════════════════════════════*/
void merge(Ebook *katalog, int kiri, int tengah, int kanan, int jenis) {
    int n1 = tengah - kiri + 1, n2 = kanan - tengah;
    Ebook *L = new Ebook[n1];
    Ebook *R = new Ebook[n2];
    for (int i = 0; i < n1; i++){
        *(L + i) = *(katalog + kiri + i);}
    for (int j = 0; j < n2; j++){
        *(R + j) = *(katalog + tengah + 1 + j);}
    int i = 0, j = 0, k = kiri;

    while (i < n1 && j < n2) {
        bool kondisi = false;
        if (jenis == 1) {kondisi = (L + i)->judul <= (R + j)->judul;}
        else if (jenis == 2) {kondisi = (L + i)->penulis <= (R + j)->penulis;}
        else if (jenis == 3) {kondisi = (L + i)->genre <= (R + j)->genre;}
        else {kondisi = (L + i)->kode <= (R + j)->kode;}
        if (kondisi) {
            *(katalog + k) = *(L + i);
            i++;}
        else {
            *(katalog + k) = *(R + j);
            j++;}
        k++;}

    while (i < n1){
        *(katalog + k) = *(L + i);
        i++; k++;}
    while (j < n2){
        *(katalog + k) = *(R + j);
        j++; k++;}
    delete[] L; delete[] R;}
    
void urutJudulPenulisGenreKode_merge(Ebook *katalog, int kiri, int kanan, int jenis) {
    if (kiri < kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        urutJudulPenulisGenreKode_merge(katalog, kiri, tengah, jenis);
        urutJudulPenulisGenreKode_merge(katalog, tengah + 1, kanan, jenis);
        merge(katalog, kiri, tengah, kanan, jenis);}
}

void tukar(Ebook *a, Ebook *b) {
    Ebook temp = *a;
    *a = *b;
    *b = temp;}
int partition(Ebook *katalog, int low, int high, int jenis) {
    Ebook pivot = katalog[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool kondisi = false;
        if (jenis == 1) {kondisi = (katalog + j)->tahun > pivot.tahun;} 
        else {kondisi = (katalog + j)->harga > pivot.harga;}
        if (kondisi) {
            i++;
            tukar(&katalog[i], &katalog[j]);}}

    tukar(&katalog[i + 1], &katalog[high]);
    return i + 1;
}
void urutTahunHarga_quick(Ebook *katalog, int low, int high, int jenis) {
    if (low < high) {
        int pi = partition(katalog, low, high, jenis);
        urutTahunHarga_quick(katalog, low, pi - 1, jenis);
        urutTahunHarga_quick(katalog, pi + 1, high, jenis);}
}

void urutNO_bubble(Ebook *katalog, int &jumlahBuku) {
    for (int i = 0; i < jumlahBuku - 1; i++) {
        for (int j = 0; j < jumlahBuku - i - 1; j++) {
            if ((katalog + j)->no > (katalog + j + 1)->no) {
                tukar((katalog + j), (katalog + j + 1));}}}
}


int cariTahunHargaRange_linear(Ebook *katalog, int &jumlahBuku, Ebook *hasil, int min, int max, int jenis) {
    int jumlahHasil = 0;
    for (int i = 0; i < jumlahBuku; i++) {
        int kondisi;
        if (jenis == 1) {kondisi = (katalog + i)->tahun;} 
        else {kondisi = (katalog + i)->harga;} 
        if (kondisi >= min && kondisi <= max) {
            *(hasil + jumlahHasil) = *(katalog + i);
            jumlahHasil++;}}
    return jumlahHasil;
}

int cariKode_binary(Ebook *katalog, int &jumlahBuku, string target) {
    int kiri = 0, kanan = jumlahBuku - 1;

    while (kiri <= kanan) {
        string kondisi;
        int tengah = (kiri + kanan) / 2;
        if ((katalog + tengah)->kode == target) {
            return tengah;}
        else if ((katalog + tengah)->kode < target) {
            kiri = tengah + 1;}
        else {
            kanan = tengah - 1;}}
    return -1;
}

int cariJudulPenulisGenre_linear(Ebook *katalog, int &jumlahBuku, Ebook *hasil, string keyword) {
    int jumlahHasil = 0;
    string key = ubahStringKecilSemua(keyword);

    for (int i = 0; i < jumlahBuku; i++) {
        if ((ubahStringKecilSemua((katalog + i)->judul)).find(key) != string::npos || 
            (ubahStringKecilSemua((katalog + i)->penulis)).find(key) != string::npos || 
            (ubahStringKecilSemua((katalog + i)->genre)).find(key) != string::npos) {
            *(hasil + jumlahHasil) = *(katalog + i);
            jumlahHasil++;}}
    return jumlahHasil;
}


/* CRUD
════════════════════════════════════════════════════*/
void readKatalog(Ebook *katalog, int jumlahBuku, int indeks = 0) {
    if (jumlahBuku == 0) {
        tampilPesan(28, "Katalog E-book belum terisi.");
        return;}
    if (indeks == 0) {
        cout << "NO | KODE           | JUDUL                    | PENULIS             | TAHUN   | GENRE     | HARGA    " << endl;
        cout << "---+----------------+--------------------------+---------------------+---------+-----------+----------" << endl;}
    if (indeks >= jumlahBuku) {
        cout << right << endl;
        return;}
    cout << left
        << setw(3) << (katalog + indeks)->no << "| "<< setw(15) << (katalog + indeks)->kode << "| "
        << setw(25) << (katalog + indeks)->judul << "| "
        << setw(20) << (katalog + indeks)->penulis << "| " << setw(8) << (katalog + indeks)->tahun << "| "
        << setw(10) << (katalog + indeks)->genre << "| " << setw(10) << (katalog + indeks)->harga
        << endl;
    readKatalog(katalog, jumlahBuku, indeks + 1);}

int createEbook(Ebook *katalog, int &jumlahBuku) {
    int TahunBuku, HargaBuku;
    string JudulBuku, PenulisBuku, GenreBuku, input;

    if (jumlahBuku >= 100) {
        tampilPeringatan(20, "Katalog sudah penuh!");
        return jumlahBuku;}

    cout << "     Judul   : "; getline(cin, JudulBuku);
    cout << "     Penulis : "; getline(cin, PenulisBuku);
    try {
        cout << "     Tahun   : "; cin >> TahunBuku;
        if (cin.fail() || TahunBuku <= 0) {
            throw "Tahun harus berupa angka, tidak boleh minus atau 0!";}
        cin.ignore(numeric_limits<streamsize>::max(), '\n');}
    catch (const char* e) {
        cin.clear(); cin.ignore(1000, '\n');
        tampilPeringatan(50, e);
        return jumlahBuku;}
    cout << "     Genre   : "; getline(cin, GenreBuku);
    try {
        cout << "     Harga   : "; cin >> HargaBuku;
        if (cin.fail() || HargaBuku <= 0) {
            throw "Harga harus berupa angka, tidak boleh minus atau 0!";}}
    catch (const char* e) {
        cin.clear();
        cin.ignore(1000, '\n');
        tampilPeringatan(54, e);
        return jumlahBuku;}
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int NoBuku = generateNo(katalog, jumlahBuku);
    string KodeBuku = generateKode(katalog, jumlahBuku, JudulBuku, PenulisBuku, TahunBuku);

    (katalog + jumlahBuku)->no = NoBuku;
    (katalog + jumlahBuku)->kode = KodeBuku;
    (katalog + jumlahBuku)->judul = JudulBuku;
    (katalog + jumlahBuku)->penulis = PenulisBuku;
    (katalog + jumlahBuku)->tahun = TahunBuku;
    (katalog + jumlahBuku)->genre = GenreBuku;
    (katalog + jumlahBuku)->harga = HargaBuku;
    jumlahBuku++;
    urutNO_bubble(katalog, jumlahBuku);

    cout << "\n     NO    : " << NoBuku << endl;
    cout << "     Kode  : " << KodeBuku << endl;
    tampilPesan(30, "E-book berhasil ditambahkan!");

    return jumlahBuku;
}

void updateHarga(Ebook *katalog, int jumlahBuku) {
    int HargaBaru;
    string input;
    if (jumlahBuku == 0) {
        tampilPesan(28, "Katalog E-book belum terisi.");
        return;}
    cout << "    Pilih E-book yang ingin diubah harganya: " << endl << endl;
    int pilihan = scrollBuku(katalog, jumlahBuku, "Ubah Harga E-Book");
    cout << "\n\n     Judul E-Book : " << (katalog + pilihan)->judul << endl;
    cout << "     Harga lama : " << (katalog + pilihan)->harga << endl;
    try {
        cout << "\n\n     Masukkan harga baru: "; cin >> HargaBaru;
        if (cin.fail() || HargaBaru <= 0) {
            throw "Harga harus berupa angka, tidak boleh minus atau 0!";}}
    catch (const char* e) {
        cin.clear();
        cin.ignore(1000, '\n');
        tampilPeringatan(54, e);
        return;}
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    (katalog + pilihan)->harga = HargaBaru;
    tampilPesan(34, "Harga E-book berhasil diperbarui!");
}

int deleteEbook(Ebook *katalog, int &jumlahBuku) {
    if (jumlahBuku == 0) {
        tampilPesan(28, "Katalog E-book belum terisi.");
        return jumlahBuku;}
    cout << "    Pilih E-book yang ingin dihapus: " << endl << endl;
    int pilihan = scrollBuku(katalog, jumlahBuku, "Hapus E-Book");
    cout << "\n\n     NO           : " << (katalog + pilihan)->no << endl;
    cout << "     Judul E-Book : " << (katalog + pilihan)->judul << endl << endl;
    for (int j = pilihan; j < jumlahBuku - 1; j++) {
        *(katalog + j) = *(katalog + j + 1);}
    jumlahBuku--;
    tampilPesan(26, "E-book berhasil dihapus!");

    return jumlahBuku;
}


int createPesan(Ebook *katalog, int &jumlahBuku, EbookUser *ebookUser, int &jumlahEbookUser, Akun *akun, int indeksLogin, string jawabNama) {
    bool sudahBeli = false;

    if (jumlahBuku == 0) {
        tampilPesan(28, "Katalog E-book belum terisi.");
        return jumlahEbookUser;}
    if (jumlahEbookUser >= 100) {
        tampilPeringatan(20, "Katalog sudah penuh!");
        return jumlahEbookUser;}
    cout << "    Pilih E-book yang ingin dipesan: " << endl << endl;
    int pilihan = scrollBuku(katalog, jumlahBuku, "Pesan E-Book");

    for(int i = 0; i < jumlahEbookUser; i++){
        if((ebookUser + i)->username == jawabNama && (ebookUser + i)->buku.no == (katalog + pilihan)->no){
            sudahBeli = true;
            break;}}

    if (sudahBeli) {
        tampilPeringatan(32, "Anda sudah membeli E-book ini!");}
    else {
        if ((akun + indeksLogin)->saldo >= (katalog + pilihan)->harga) {
            (akun + indeksLogin)->saldo -= (katalog + pilihan)->harga;
            (akun + 0)->saldo += (katalog + pilihan)->harga;
            (ebookUser + jumlahEbookUser)->username = jawabNama;
            (ebookUser + jumlahEbookUser)->buku = katalog[pilihan];

            jumlahEbookUser++;
            cout << "\n\n     NO           : " << (katalog + pilihan)->no << endl;
            cout << "     Judul E-Book : " << (katalog + pilihan)->judul << endl;
            cout << "" << endl;
            cout << "" << endl;
            tampilPesan(24, "E-book berhasil dibeli!");
            cout << "" << endl;}
        else {
            tampilPeringatan(24, "Saldo anda tidak cukup!");}}
    return jumlahEbookUser;
}


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
    string username, password, email, no_hp, alamat;

    cout << "Username: "; getline(cin, username);
    cout << "Password: "; getline(cin, password);
    cout << "Email: "; getline(cin, email);
    cout << "No HP: "; getline(cin, no_hp);
    cout << "Alamat: "; getline(cin, alamat);

    if (username == "" || password == "" || email == "" ||
        no_hp == "" || alamat == "") {
        cout << "Semua kolom harus diisi!\n";
        return -1;}

    regex userRegex("^[a-zA-Z0-9_ ]{5,}$");
    if (!regex_match(username, userRegex)) {
        cout << "Username tidak valid!\n";
        return -1;}

    regex passRegex("^(?=.*[A-Z])(?=.*[a-z])(?=.*\\d).{8,}$");
    if (!regex_match(password, passRegex)) {
        cout << "Password tidak valid!\n";
        return -1;}

    regex hpRegex("08[0-9]{8,12}");
    if (!regex_match(no_hp, hpRegex)) {
        cout << "No HP tidak valid!\n";
        return -1;}

    if (email.find("@gmail.com") == string::npos) {
        cout << "Email harus @gmail.com!\n";
        return -1;}

    if (isDuplicate(username, email)) {
        cout << "Username atau email sudah terdaftar!\n";
        return -1;}

    int nextId = jumlahUser + 1;
    string id = "U_K" + to_string(nextId);

    akun[jumlahUser].id_user = id;
    akun[jumlahUser].username = username;
    akun[jumlahUser].password = password;
    akun[jumlahUser].role = "Konsumen";
    akun[jumlahUser].status_user = "Aktif";
    akun[jumlahUser].tanggal_daftar = getTanggal();
    akun[jumlahUser].email = email;
    akun[jumlahUser].no_hp = no_hp;
    akun[jumlahUser].alamat = alamat;
    akun[jumlahUser].saldo = 0;

    jumlahUser++;
    tampilPesan(34, "Registrasi berhasil! Silakan login untuk melanjutkan.");
    return jumlahUser;
}


/* SUB MENU
════════════════════════════════════════════════════*/
int menuAdmin(Akun *akun, int indeksLogin, Ebook *katalog, int &jumlahBuku) {
    string pilihMenuAdmin[] = {
        "   1 | Menu Katalog E-Book",
        "   2 | Tambahkan E-Book Baru",
        "   3 | Ubah Harga E-Book",
        "   4 | Hapus E-Book",
        "   5 | Logout"};
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Halo, Admin " + (akun + indeksLogin)->username);
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << setw((70 + 2) / 2) << "Saldo: " << (akun + indeksLogin)->saldo << endl;
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << "" << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih)
                cout << "> " << *(pilihMenuAdmin + i) << endl;
            else
                cout << "  " << *(pilihMenuAdmin + i) << endl;}
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
    
            /* a. MENU ADMIN READ (Katalog E-Book)
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                string pilihMenuAdmin[] = {
                    "   1 | Urutkan E-Book",
                    "   2 | Cari E-Book",
                    "   3 | Kembali"};
                int pilih = 0;
                
                while (true) {
                    system("cls"); judul_subjudul("Menu Katalog E-Book"); cout << endl;
                    if (jumlahBuku == 0) {
                        tampilPesan(28, "Katalog E-book belum terisi.");
                        system("pause");
                        break;}
                    for (int i = 0; i < 3; i++) {
                        if (i == pilih)
                            cout << "> " << *(pilihMenuAdmin + i) << endl;
                        else
                            cout << "  " << *(pilihMenuAdmin + i) << endl;}
                    cout << endl << endl; readKatalog(katalog, jumlahBuku);
                    int hasil = scrollMenu(pilih, 3);
                    if (hasil == -1) {
                        if (pilih == 0) {
                            cout << "\n\n     Pilih metode pengurutan: " << endl << endl;}
                        else if (pilih == 1) {
                            cout << "\n\n     Pilih metode pencarian: " << endl << endl;}
                        else {
                            break;}}}}

            /* b. MENU ADMIN CREATE (Tambah E-Book)
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Tambahkan E-Book Baru"); cout << endl;
                system("pause");}

            /* c. MENU ADMIN UPDATE (Edit Harga E-Book)
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("Ubah Harga E-Book"); cout << endl;
                system("pause");}

            /* d. MENU ADMIN DELETE (Hapus E-Book)
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Hapus E-Book"); cout << "" << endl;
                system("pause");}

            /* e. MENU ADMIN LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(18, "Logout berhasil!");
                system("pause");
                break;}}}
        return jumlahBuku;}

int menuUser(Akun *akun, int indeksLogin, Ebook *katalog, int &jumlahBuku, EbookUser *ebookUser, int &jumlahEbookUser) {
    string pilihMenuUser[] = {
        "   1 | Menu Katalog E-Book",
        "   2 | Pesan E-Book",
        "   3 | E-Book Anda",
        "   4 | Topup Saldo",
        "   5 | Logout"};
    int pilih = 0;
    
    while (true) {
        system("cls"); judul_subjudul("Halo, Pengguna " + (akun + indeksLogin)->username);
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << setw((70 + 2) / 2) << "Saldo: " << (akun + indeksLogin)->saldo << endl;
        cout << setw((70 + 22) / 2) << "=====================" << endl;
        cout << "" << endl;
        for (int i = 0; i < 5; i++) {
            if (i == pilih)
                cout << "> " << *(pilihMenuUser + i) << endl;
            else
                cout << "  " << *(pilihMenuUser + i) << endl;}
        int hasil = scrollMenu(pilih, 5);
        if (hasil == -1) {
    
            /* a. MENU USER READ (Katalog E-Book)
            ════════════════════════════════════════════════════*/
            if (pilih == 0) {
                string pilihMenuAdmin[] = {
                    "   1 | Urutkan E-Book",
                    "   2 | Cari E-Book",
                    "   3 | Kembali"};
                int pilih = 0;
                
                while (true) {
                    system("cls"); judul_subjudul("Menu Katalog E-Book"); cout << endl;
                    if (jumlahBuku == 0) {
                        tampilPesan(28, "Katalog E-book belum terisi.");
                        system("pause");
                        break;}
                    for (int i = 0; i < 3; i++) {
                        if (i == pilih)
                            cout << "> " << *(pilihMenuAdmin + i) << endl;
                        else
                            cout << "  " << *(pilihMenuAdmin + i) << endl;}
                    cout << endl << endl; readKatalog(katalog, jumlahBuku);
                    int hasil = scrollMenu(pilih, 3);
                    if (hasil == -1) {
                        if (pilih == 0) {
                            cout << "\n\n     Pilih metode pengurutan: " << endl << endl;}
                        else if (pilih == 1) {
                            cout << "\n\n     Pilih metode pencarian: " << endl << endl;}
                        else {
                            break;}}}}

            /* b. MENU USER CREATE (Pesan E-Book)
            ════════════════════════════════════════════════════*/
            else if (pilih == 1) {
                system("cls"); judul_subjudul("Pesan E-Book"); cout << endl;
                system("pause");}

            /* c. MENU USER READ (E-Book User)
            ════════════════════════════════════════════════════*/
            else if (pilih == 2) {
                system("cls"); judul_subjudul("E-Book Anda"); cout << endl;
                system("pause");}

            /* d. MENU USER UPDATE (Topup Saldo)
            ════════════════════════════════════════════════════*/
            else if (pilih == 3) {
                system("cls"); judul_subjudul("Topup Saldo Anda"); cout << endl;
                system("pause");}

            /* e. MENU USER LOGOUT
            ════════════════════════════════════════════════════*/
            else {
                tampilPesan(18, "Logout berhasil!");
                system("pause");
                break;}}}
        return jumlahEbookUser;}


/* MAIN
════════════════════════════════════════════════════*/
int main() {
    SetConsoleOutputCP(65001);

    string pilihMenu[] = {
        "   1 | Login", 
        "   2 | Register",
        "   3 | Keluar"}; 

    
    /* PROGRAM UTAMA
    ════════════════════════════════════════════════════*/
    cout << "╔═════════════════════════════════════════════════════════════════════════╗" << endl;
    cout << "║   _______           _______   _______   _______   _   __  _   _______   ║" << endl;
    cout << "║  │  _____│         │  __   │ │  ___  │ │  ___  │ │ │ ╱ ╱ │ │ │  _____│  ║" << endl;                                              
    cout << "║  │ │_____   _____  │ │__╱ ╱  │ │   │ │ │ │   │ │ │ │╱ ╱  │ │ │ │_____   ║" << endl;
    cout << "║  │  _____│ │_____│ │  __ <   │ │   │ │ │ │   │ │ │   <   │ │ │  _____│  ║" << endl;
    cout << "║  │ │_____          │ │__╲ ╲  │ │___│ │ │ │___│ │ │ │╲ ╲  │ │ │ │_____   ║" << endl;
    cout << "║  │_______│         │_______│ │_______│ │_______│ │_│ ╲_╲ │_│ │_______│  ║" << endl;
    cout << "║                                                                         ║" << endl;
    cout << "╚═════════════════════════════════════════════════════════════════════════╝" << endl;
    system("pause");

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
                        jumlahBuku = menuAdmin(akun, indeksLogin, katalog, jumlahBuku);}

                    /* 2. MENU USER (CRUD)
                    ════════════════════════════════════════════════════*/
                    else {
                        jumlahEbookUser = menuUser(akun, indeksLogin, katalog, jumlahBuku, ebookUser, jumlahEbookUser);}
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
    
    return 0;
}