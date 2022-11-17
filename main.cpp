#include <iostream>
#include <fstream>
#include <conio.h>
#define MAX 100 // Maksimum kontak
using namespace std;

int banyak_kontak;

struct Data {
    string nama;
    string domisili;
    string nomor;
};

int banyakLine() {
    string line;
    int count = 0;

    ifstream file("data.txt");
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, line);
            count++;
        }
        file.close();
    } 
    else {
        cout << "Tidak bisa membuka file";
    }

    return count;
}

void tampilkanKontak(Data kontak[]) {
    if (banyak_kontak == 0) {
        cout << "Tidak ada kontak untuk ditampilkan!";
    }
    else {
        for (int i = 0; i < banyak_kontak; i++) {
            cout << kontak[i].nama << " " << kontak[i].domisili << " " << kontak[i].nomor << endl;
        }
    }
    
    getch();
}

void read(string str, char del, Data kontak[], int i){
    // banyak_var itu banyak member dari struct: nama, domisili, dll
    int banyak_var = 3;
    // temp untuk penyimpanan sementara string data kontak yang udah dipisah
    string temp[banyak_var] = {"", "", ""};

    // j untuk perulangan temp
    int j = 0;

    for(int i = 0; i < str.size(); i++){
        // Kalo stringnya tidak sama dengan delimiternya, maka
        // masih terus ditambah huruf demi hurufnya.
        // Kalo udah sampe delimiter maka pindah ke temp index selanjutnya 
        if(str[i] != del){
            temp[j] += str[i];
        }
        else{
            j++;
        }
    }

    // Masukkin data yang udah dipisah dari delimiter ke struct
    kontak[i].nama = temp[0];
    kontak[i].domisili = temp[1];
    kontak[i].nomor = temp[2];
}

void inisialisasiKontak(Data kontak[]) {
    banyak_kontak = banyakLine();
    string line;
    ifstream file("data.txt");

    int i = 0;
    if (file.is_open()) {
        while (!file.eof()) {
            getline(file, line);
            read(line, '#', kontak, i);
            i++;
        }
        file.close();
    } 
    else {
        cout << "Tidak bisa membuka file";
    }
}

void tambahKontak(Data kontak[]) {
    int i = banyak_kontak;
    cout << "==========================" << endl; 
    cout << "       Tambah Kontak      " << endl;
    cout << "==========================" << endl;
    cout << "Nama           : "; cin >> ws; getline(cin, kontak[i].nama);
    cout << "Domisili       : "; getline(cin, kontak[i].domisili);
    cout << "Nomor Telepon  : "; getline(cin, kontak[i].nomor);

    ofstream file("data.txt", ios::app);

    if(file.is_open()) {
        if (banyak_kontak == 0) {
            file << kontak[i].nama << "#" << kontak[i].domisili << "#" << kontak[i].nomor;
        }
        else {
            file << "\n" << kontak[i].nama << "#" << kontak[i].domisili << "#" << kontak[i].nomor;
        }
        file.close();
    }
    else {
        cout << "Tidak bisa membuka file";
    }

    banyak_kontak++;

    cout << "Data telah berhasil diinput." << endl;
    cout << "Press any key to continue...";
    getch();
 
}

void handlePil() {
    cout << "Harap masukkan pilihan yang benar!" << endl;
    cout << "Press any key to continue...";
    getch();
}

int main() {
    int pil;
    
    Data kontak[MAX];
    inisialisasiKontak(kontak);

    do {
        system("cls");
        cout << "==========================" << endl; 
        cout << "        My Contacts       " << endl;
        cout << "==========================" << endl;
        cout << "1. Tampilkan data kontak" << endl;
        cout << "2. Tambahkan kontak" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pil;

        switch (pil) {
        case 1:
            tampilkanKontak(kontak);
            break;
        case 2:
            tambahKontak(kontak);
            break;
        case 0:
            cout << "Thank you..." << endl;
            break;
        default:
            handlePil();
            break;
        }

    } while (pil != 0);
    
    
    return 0;
}