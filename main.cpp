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

// Functions
void header(string text);
void pressAnyKey();
void handlePil();
void tabel(Data kontak[]);
void tampilanTabel(Data kontak[]);
void tampilanDetail(Data kontak[]);
void menuTampilan(Data kontak[]);
void printDetail(Data kontak[], int i);
void sorting(Data kontak[]);
void search(Data kontak[]);
void read(string str, char del, Data kontak[], int i);
void inisialisasiKontak(Data kontak[]);
void titleCase(string &str);
void tambahKontak(Data kontak[]);
void aboutUs();
void hapusKontak(Data kontak[]);
void editKontak(Data kontak[]);
int banyakLine();

// Main
int main() {
    int pil;
    
    Data kontak[MAX];
    inisialisasiKontak(kontak);

    do {
        system("cls");
        header("My Contacts");
        cout << "1. Tampilkan data kontak" << endl;
        cout << "2. Tambahkan kontak" << endl;
        cout << "3. Cari kontak" << endl;
        cout << "4. Hapus kontak" << endl;
        cout << "5. Edit kontak" << endl;
        cout << "6. About Us" << endl;
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
        case 4:
            hapusKontak(kontak);
            break;
        case 5:
            editKontak(kontak);
            break;
        case 6:
            aboutUs();
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

void header(string text) {
    cout << "==========================" << endl;
    cout << "       " << text << endl;
    cout << "==========================" << endl;
}

void pressAnyKey() {
    cout << "Press any key to continue...";
    getch();
}

void handlePil() {
    cout << "Harap masukkan pilihan yang benar!" << endl;
    pressAnyKey();
}

int banyakLine() {
    // Pram
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

void tabel(Data kontak[]) {
    cout<<"===========================================================================================================\n";
    cout<<"|  No  |           Nama           |     No Telepon    |                       Alamat                      |\n";
    cout<<"===========================================================================================================\n";
    for (int i = 0; i < banyak_kontak; i++){
        cout << "| " << setiosflags(ios::left) << setw(5) << i+1 << "|";
        cout << " " << setiosflags(ios::left) << setw(25) << kontak[i].nama << "|";
        cout << " " << setiosflags(ios::left) << setw(18) << kontak[i].nomor << "|";
        cout << " " << setiosflags(ios::left) << setw(50) << kontak[i].domisili << "|";
        cout <<"\n";
    }
    cout << "-----------------------------------------------------------------------------------------------------------\n\n";
}

void tampilanTabel(Data kontak[]) {
    // Syifa
    if (banyak_kontak == 0) {
        cout << "Tidak ada kontak untuk ditampilkan!" << endl;
    }
    else {
        header("Daftar Kontak");
        tabel(kontak);
    }

    pressAnyKey();
}

void tampilanDetail(Data kontak[]) {
    int i = 0;
    int pil;
    if (banyak_kontak == 0) {
        cout << "Tidak ada kontak untuk ditampilkan!" << endl;
        pressAnyKey();
    }
    else {
        do {
            header("Detail Kontak");
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
    header("Data Kontak");
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
            if (kontak[j].nama > kontak[j + 1].nama) {
                Data temp = kontak[j];
                kontak[j] = kontak[j + 1];
                kontak[j + 1] = temp;
            }
        }
    }
}

void search(Data kontak[]) {
    // Marsha
    bool flag = false;
    int i;
    string key;
    header("Cari Kontak");
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
    pressAnyKey();
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
    // Faza
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

void titleCase(string &str) {
    for(int i = 0; i < str.size(); i++){
        if(i == 0 || (i != 0 && str[i - 1] == ' ')){
            str[i] = toupper(str[i]);
        }
        else {
            str[i] = tolower(str[i]);
        }
    }
}

void tambahKontak(Data kontak[]) {
    header("Tambah Kontak");
    cout << "Nama           : "; cin >> ws; getline(cin, kontak[banyak_kontak].nama);
    cout << "Nomor Telepon  : "; getline(cin, kontak[banyak_kontak].nomor);
    cout << "Domisili       : "; getline(cin, kontak[banyak_kontak].domisili);

    // Benerin kapitalisasi
    titleCase(kontak[banyak_kontak].nama);
    titleCase(kontak[banyak_kontak].domisili);

    // Update banyak kontaknya
    banyak_kontak++;
    // Lalu sorting alfabetikal
    sorting(kontak);

    // Pasha
    // Masukkin datanya ke file
    ofstream file("data.txt", ios::out);
    if(file.is_open()) {
        for (int i = 0; i < banyak_kontak; i++) {
            if (i > 0) {
                file << endl;
            }
            file << kontak[i].nama << "#" << kontak[i].domisili << "#" << kontak[i].nomor;
        }
        
        file.close();
    }
    else {
        cout << "Tidak bisa membuka file";
    }

    cout << endl;
    cout << "Data telah berhasil diinput." << endl;
    pressAnyKey();
}

void aboutUs() {
    header("About Us");
    cout << "Project By:" << endl;
    cout << "- Azhar Bagaskara (22/502652/PA/21573)" << endl;
    cout << "- Faza Aster Apriliani (22/500393/PA/21550)" << endl;
    cout << "- Marsha Rasyida Al-Farabi (22/499914/PA/21544)" << endl;
    cout << "- Pasha Rai Azi Zaydan (22/505428/PA/21765)" << endl;
    cout << "- Pramudya Putra Hidayat (22/496600/PA/21349)" << endl;
    cout << "- Syifa Ramadhanty (22/504446/PA/21699)" << endl << endl;
    pressAnyKey();
}

void hapusKontak(Data kontak[]) {
    int nomor;
    char pil;
    header("Hapus Kontak");
    tabel(kontak);
    cout << "Masukkan nomor berapa yang ingin dihapus: ";
    cin >> nomor;
    cout << "Anda yakin ingin menghapus " << kontak[nomor-1].nama << "? [y/n]: ";
    cin >> pil;

    if (pil == 'y' || pil == 'Y') {
        for (int i = nomor-1; i < banyak_kontak; i++) {
            kontak[i] = kontak[i+1];
        }
        banyak_kontak--;

        sorting(kontak);
        // Masukkin datanya ke file
        ofstream file("data.txt", ios::out);
        if(file.is_open()) {
            for (int i = 0; i < banyak_kontak; i++) {
                if (i > 0) {
                    file << endl;
                }
                file << kontak[i].nama << "#" << kontak[i].domisili << "#" << kontak[i].nomor;
            }
            
            file.close();
        }
        else {
            cout << "Tidak bisa membuka file";
        }

        cout << "Kontak berhasil dihapus" << endl;
        pressAnyKey();
    }
    else {
        return;
    }
}

void editKontak(Data kontak[]) {
    int nomor;
    char pil;
    header("Edit Kontak");
    tabel(kontak);
    cout << "Masukkan angka 0 jika ingin kembali ke menu utama\n\n";
    cout << "Masukkan nomor berapa yang ingin diedit: ";
    cin >> nomor;
    nomor--;

    if (nomor == -1)
        return;
    
    if (nomor < -1 || nomor >= banyak_kontak) {
        cout << "Nomor tidak valid" << endl;
        pressAnyKey();
        return;
    }

    string temp;
    cout << endl;
    cout << "Masukkan strip (-) jika tidak ingin diubah" << endl;
    cout << kontak[nomor].nama << " -> ";
    cin >> ws;
    getline(cin, temp);
    if (temp != "-") {
        kontak[nomor].nama = temp;
    }
    cout << kontak[nomor].domisili << " -> ";
    getline(cin, temp);
    if (temp != "-") {
        kontak[nomor].domisili = temp;
    }
    cout << kontak[nomor].nomor << " -> ";
    getline(cin, temp);
    if (temp != "-") {
        kontak[nomor].nomor = temp;
    }

    // Masukkin datanya ke file
    ofstream file("data.txt", ios::out);
    if(file.is_open()) {
        for (int i = 0; i < banyak_kontak; i++) {
            if (i > 0) {
                file << endl;
            }
            file << kontak[i].nama << "#" << kontak[i].domisili << "#" << kontak[i].nomor;
        }
        
        file.close();
    }
    else {
        cout << "Tidak bisa membuka file";
    }

    cout << endl;
    cout << "Kontak berhasil diedit" << endl;
    pressAnyKey();
}