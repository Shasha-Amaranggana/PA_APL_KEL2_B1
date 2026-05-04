#include "data.h"
#include <fstream>

void loadAkun(Akun akun[], int &jumlahUser) {
    ifstream file("data/akun.json");

    if (!file.is_open()) {
        jumlahUser = 0;
        return;
    }

    json data;
    file >> data;

    jumlahUser = data.size();
    for (int i = 0; i < jumlahUser; i++) {
        akun[i].username = data[i]["username"];
        akun[i].password = data[i]["password"];
        akun[i].role = data[i]["role"];
        akun[i].saldo = data[i]["saldo"];
    }
}

void saveAkun(Akun akun[], int jumlahUser) {
    json data = json::array();

    for (int i = 0; i < jumlahUser; i++) {
        data.push_back({
            {"username", akun[i].username},
            {"password", akun[i].password},
            {"role", akun[i].role},
            {"saldo", akun[i].saldo}
        });
    }

    ofstream file("data/akun.json");
    file << data.dump(4);
}