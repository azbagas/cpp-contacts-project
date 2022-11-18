#include <iostream>
#include <fstream>
#include <conio.h>
#include <iomanip>
#include <cstring>
#define MAX 100 // Maksimal kontak
using namespace std;

int banyak_kontak;

struct Data {
    string nama;
    string domisili;
    string nomor;
};

void handlePil() {
    cout << "Harap masukkan pilihan yang benar!" << endl;
    cout << "Press any key to continue...";
    getch();
}

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

void tampilanTabel(Data kontak[]) {
    if (banyak_kontak == 0) {
        cout << "Tidak ada kontak untuk ditampilkan!";
    }
    else {
        cout << "==========================" << endl;
        cout << "       Daftar Kontak      " << endl;
        cout << "==========================" << endl;
        cout<<"===========================================================================================================\n";
        cout<<"|  No  |           Nama           |     No Telepon    |                       Alamat                      |\n";
        cout<<"===========================================================================================================\n";
        for (int i = 0; i < banyak_kontak; i++){
            cout << "| " << setiosflags(ios::left) << setw(5) << i+1 << "|";
            cout << " " << setiosflags(ios::left) << setw(25) << kontak[i].nama << "|";
            cout << " " << setiosflags(ios::left) << setw(18) << kontak[i].nomor << "|";
            cout << " " << setiosflags(ios::left) << setw(50) << kontak[i].domisili << "|";
            cout <<"\n-----------------------------------------------------------------------------------------------------------\n";
        }
    }

    cout << "Press any key to continue...";
    getch();
}

void tampilanDetail(Data kontak[]) {
    int i = 0;
    int pil;
    if (banyak_kontak == 0) {
        cout << "Tidak ada kontak untuk ditampilkan!";
    }
    else {
        do {
            cout << "==========================" << endl; 
            cout << "       Detail Kontak      " << endl;
            cout << "==========================" << endl;
            cout << "Nomor (" << i+1 << "/"<< banyak_kontak << ")" << endl;
            cout << "Nama          : " << kontak[i].nama << endl;
            cout << "Nomor Telepon : " << kontak[i].nomor << endl;
            cout << "Domisili      : " << kontak[i].domisili << endl;
            cout << endl;
            cout << "Navigasi:" << endl;
            cout << "1. Selanjutnya" << endl;
            cout << "2. Sebelumnya" << endl;
            cout << "0. Kembali ke menu utama" << endl;
            cout << "Pilihan: ";
            cin >> pil;

            system("cls");

            switch (pil) {
            case 1:
                if (i == banyak_kontak - 1) 
                    i = 0;
                else
                    i++;
                break;
            case 2:
                if (i == 0)
                    i = banyak_kontak - 1;
                else
                    i--;
            case 0:
                break;
            default:
                handlePil();
                system("cls");
                break;
            }

        } while (pil != 0);   
    }
}

void menuTampilan(Data kontak[]) {
    int pil;
    cout << "==========================" << endl; 
    cout << "        Data Kontak       " << endl;
    cout << "==========================" << endl;
    cout << "1. Tampilkan tabel" << endl;
    cout << "2. Tampilkan detail" << endl;
    cout << "0. Kembali" << endl;
    cout << "Pilih: ";
    cin >> pil;

    system("cls");

    switch (pil) {
    case 1:
        tampilanTabel(kontak);
        break;
    case 2:
        tampilanDetail(kontak);
        break;
    case 0:
        break;
    default:
        handlePil();
        break;
    }
}

void printDetail(Data kontak[], int i) {
    cout << "Nama          : " << kontak[i].nama << endl;
    cout << "Nomor Telepon : " << kontak[i].nomor << endl;
    cout << "Domisili      : " << kontak[i].domisili << endl;
}

void sorting(Data kontak[]) {
    int i, j;
    for (i = 0; i < banyak_kontak - 1; i++) {
        for (j = 0; j < banyak_kontak - i - 1; j++) {
            if (tolower(kontak[j].nama[0]))
            {
                /* code */
            }
            
        }
        
    }
    
}

void search(Data kontak[]) {
    bool flag = false;
    int i;
    string key;
    cout << "==========================" << endl;
    cout << "        Cari Kontak      " << endl;
    cout << "==========================" << endl;
    cout << "Nama: "; cin >> ws; getline(cin, key);

    for (i = 0; i < banyak_kontak; i++) {
        if (strcasecmp(kontak[i].nama.c_str(), key.c_str()) == 0) {
            flag = true;
            break;
        }
    }
    cout << "--------------------------" << endl;
    if (flag == true) {
        printDetail(kontak, i);
    }
    else {
        cout << "Kontak dengan nama "<< key << " tidak ditemukan" << endl;
    }
    
    cout << endl;
    cout << "Press any key to continue...";
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
    cout << "Nomor Telepon  : "; getline(cin, kontak[i].nomor);
    cout << "Domisili       : "; getline(cin, kontak[i].domisili);

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

    // Update banyak kontaknya
    banyak_kontak++;

    cout << "Data telah berhasil diinput." << endl;
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
        cout << "3. Cari kontak" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: ";
        cin >> pil;
        
        system("cls");

        switch (pil) {
        case 1:
            menuTampilan(kontak);
            break;
        case 2:
            tambahKontak(kontak);
            break;
        case 3:
            search(kontak);
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