#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <ctime>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_USERS = 100;
const int MAX_KERANJANG = 100;
const int MAX_RIWAYAT = 100;
const int MAX_PROMO = 100;
const int MAX_LAYANAN = 100;

struct PesananItem {
    string namaLayanan;
    string namaItem;
    double beratAtauJumlah;
    double hargaPerUnit;
    double subTotalHarga;
    string estimasiSelesai;
    string kategoriLayanan;
    string unitSatuan;
};

struct User {
	string nama;
    string noTelepon;
    string alamat;
    string tanggalPesan;
    string username;
    string password;
    string role;
    int poin;
};

struct Riwayat {
    string tanggalLengkap;
    string tanggal;
    string bulan;
    string tahun;
    string kode;
    string nama;
    string telepon;
    string alamat;
    string metode;
    string status;
    string detailTransaksi;
};

struct Layanan {
    string namaLayanan;
    string kategori;
    double harga;
    string satuan;
};

struct Promo {
    string namaPromo;
    double diskon;
    string masaBerlaku;
};

struct daftarPromo {
    string namaPromo;
    double diskon;
    string masaBerlaku;
};

enum JenisLayanan {
    CUCI_UMUM = 1,
    SATUAN_PREMIUM,
    KHUSUS_BARANG,
    DRY_CLEANING,
    EXPRESS,
    ANTAR_JEMPUT,
    PAKET_LANGGANAN
};

void dataLayanan(Layanan layanan[], int &jumlahLayanan) {
	jumlahLayanan = 0;

    // Cuci Umum
    layanan[jumlahLayanan++] = (Layanan){"Cuci Kering", "Cuci Umum", 5000, "kg"};
    layanan[jumlahLayanan++] = (Layanan){"Cuci Basah", "Cuci Umum", 4000, "kg"};
    layanan[jumlahLayanan++] = (Layanan){"Cuci Setrika", "Cuci Umum", 7000, "kg"};
    layanan[jumlahLayanan++] = (Layanan){"Setrika Saja", "Cuci Umum", 4000, "kg"};

    // Satuan Premium
    layanan[jumlahLayanan++] = (Layanan){"Kemeja/Kaos", "Satuan Premium", 7000, "helai"};
    layanan[jumlahLayanan++] = (Layanan){"Celana/Rok", "Satuan Premium", 7000, "helai"};
    layanan[jumlahLayanan++] = (Layanan){"Jaket/Sweater", "Satuan Premium", 15000, "helai"};
    layanan[jumlahLayanan++] = (Layanan){"Jas/Blazer", "Satuan Premium", 35000, "helai"};
    layanan[jumlahLayanan++] = (Layanan){"Gaun/Kebaya", "Satuan Premium", 35000, "helai"};

    // Khusus Barang
    layanan[jumlahLayanan++] = (Layanan){"Cuci Sepatu Reguler", "Khusus Barang", 40000, "pasang"};
    layanan[jumlahLayanan++] = (Layanan){"Cuci Sepatu Premium", "Khusus Barang", 65000, "pasang"};
    layanan[jumlahLayanan++] = (Layanan){"Cuci Tas", "Khusus Barang", 40000, "buah"};
    layanan[jumlahLayanan++] = (Layanan){"Cuci Helm", "Khusus Barang", 35000, "buah"};
    layanan[jumlahLayanan++] = (Layanan){"Cuci Gorden", "Khusus Barang", 35000, "meter"};
    layanan[jumlahLayanan++] = (Layanan){"Cuci Karpet", "Khusus Barang", 30000, "lembar"};
    layanan[jumlahLayanan++] = (Layanan){"Sprei/Bedcover", "Khusus Barang", 25000, "set"};
    layanan[jumlahLayanan++] = (Layanan){"Selimut/Bantal", "Khusus Barang", 25000, "buah"};

    // Dry Cleaning
    layanan[jumlahLayanan++] = (Layanan){"Jas Formal", "Dry Cleaning", 60000, "helai"};
    layanan[jumlahLayanan++] = (Layanan){"Gaun Malam", "Dry Cleaning", 80000, "helai"};
    layanan[jumlahLayanan++] = (Layanan){"Kebaya", "Dry Cleaning", 60000, "helai"};
    layanan[jumlahLayanan++] = (Layanan){"Pakaian Sutera", "Dry Cleaning", 100000, "helai"};

    // Express
    layanan[jumlahLayanan++] = (Layanan){"Same Day Service", "Express", 20000, "kg"};
    layanan[jumlahLayanan++] = (Layanan){"Next Day Service", "Express", 10000, "kg"};

    // Antar Jemput
    layanan[jumlahLayanan++] = (Layanan){"Antar Jemput < 5 KM", "Antar Jemput", 15000, "layanan"};
    layanan[jumlahLayanan++] = (Layanan){"Antar Jemput 5-10 KM", "Antar Jemput", 25000, "layanan"};
    layanan[jumlahLayanan++] = (Layanan){"Antar Jemput > 10 KM", "Antar Jemput", 35000, "layanan"};

    // Paket Langganan
    layanan[jumlahLayanan++] = (Layanan){"Paket 20kg/bulan", "Paket Langganan", 150000, "paket"};
    layanan[jumlahLayanan++] = (Layanan){"Paket 40kg/bulan", "Paket Langganan", 280000, "paket"};
    layanan[jumlahLayanan++] = (Layanan){"Paket >40kg/bulan", "Paket Langganan", 400000, "paket"};
}

string getTanggalSekarang() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
    return string(buffer);
}

template<typename T>
T inputValidasi(const string& pesan) {
    T nilai;
    while (true) {
    	cout << pesan;
        if (cin >> nilai && nilai >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nilai;
        } else {
            cout << "Input tidak valid!.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

int validasiInput(const int &min, const int &max, const string &pesan) {
	int nilai;
    while (true) {
    	cout << pesan;
        if (cin >> nilai && nilai >= min && nilai <= max) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nilai;
        } else {
            cout << "Input tidak valid!.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string inputString(const string& pesan) {
    string input;
    cout << pesan;
    getline(cin, input);
    while (input.empty()) {
        cout << "Input tidak boleh kosong! " << pesan;
        getline(cin, input);
    }
    return input;
}

class Customer {
public:
    int indeksAktif;
    User user[MAX_USERS];
    Riwayat riwayat[MAX_RIWAYAT];
    int jumlahPengguna;
    Layanan layanan[MAX_LAYANAN];
    int jumlahLayanan;
	int jumlahData;
	
    Customer() {
        jumlahPengguna = 0;
        indeksAktif = -1;
        jumlahData = 0;
        dataLayanan(layanan, jumlahLayanan);
    }

	/*int binarySearchLayanan(const string& namaLayananDicari);
	void tampilkanHasilBinaryLayanan(const string& namaLayananDicari);
	void sortLayananByNama();*/
	
	void checkStatusCucian();
	
	void cariLayananByNama(const string &keyword);
	
    int loadUsers();
    void saveUsers();
    int login(string& role);
    int registrasiPengguna();
    void pengaturanAkun(User userArr[], int &indeks, int jumlahPengguna);
    void tampilkanAkunMenu();
    void ulasanRating();
    void lihatPoin();
    void tampilkanInformasiAkun();

    PesananItem keranjangLayanan[MAX_KERANJANG];
    int jumlahKeranjang;
    double potonganPoin;
    double totalBiaya;
    double totalSetelahPromo;
    double TOTAL;

    void kosongkanKeranjang();
    void tambahKeKeranjang(const PesananItem& item);
    void tampilkanKeranjang();
    void hapusItemKeranjang();
    void tampilkanRingkasanItem(const PesananItem& item);
	
	void loadRiwayatTransaksi();
	
    void prosesMenuLayanan();
    void tampilkanDaftarLayanan();
    void tampilkanLayananCuciUmum();
    PesananItem prosesLayananCuciUmum(int pilihan);
    void tampilkanLayananSatuanPremium();
    PesananItem prosesLayananSatuanPremium(int pilihan);
    void tampilkanLayananKhususBarang();
    PesananItem prosesLayananKhususBarang(int pilihan);
    void tampilkanLayananDryCleaning();
    PesananItem prosesLayananDryCleaning(int pilihan);
    void tampilkanLayananExpress();
    PesananItem prosesLayananExpress(int pilihan);
    void tampilkanLayananAntarJemput();
    PesananItem prosesLayananAntarJemput(int pilihan);
    void tampilkanLayananPaketLangganan();
    PesananItem prosesLayananPaketLangganan(int pilihan);

    Promo daftarPromo[MAX_PROMO];
    int jumlahPromo;
    void loadPromo();
    void checkPromo();

    void tampilkanStruk(const string& metodePembayaran, const string& kodeTransaksi);
    void simpanRiwayatTransaksi(const string& metodePembayaran, const string& kodeTransaksi);

    void tampilkanMenuCustomer();
    void prosesMenuCustomer();
};

class Admin : public Customer {
public:
    int jumlahLayanan;

    Admin() {
        jumlahPengguna = 0;
        indeksAktif = -1;
        jumlahData = 0;
        jumlahLayanan = 0;
    }

    int jumlahData;
    Riwayat riwayat[MAX_RIWAYAT];
    Promo daftarPromo[MAX_PROMO];
	
	void sortRiwayatByTanggalTerbaru();
	
	void loadRiwayatTransaksi();
	void PengaturanAkun();
	void cariUserLinear(const string& keyword);
	void sortKodeTransaksi();
	int binarySearchRiwayat(const string& keyword);
	void tampilkanHasilBinaryKode(const string& keyword);
    void tampilkanDashboard();
    void bacaRiwayatLayanan();
    void lihatUserAdmin();
    void lihatUserPengguna();
    void dataUser();
    void tampilkanHasilPencarian(bool ditemukan[], const string& jenisPencarian);
    void cariByTanggal();
    void cariByNama();
    void cariByKodeTransaksi();
    void cariByStatus();
    void menuCariRiwayat();
    void updateStatus();
    void simpanRiwayatKeFile();
    void hitungPendapatanBulanan();
    void ulasanRating();
    void buatPromo();
    void lihatPromo();
    void menuPromo();
    void hapusPromo();

    void menuAdmin();
    
};

class LaundrySystem {
public:
    User user[MAX_USERS];
    int jumlahPengguna;
    int indeksAktif;
    string role;
    Customer customer;
    Admin admin;

    LaundrySystem() {
        jumlahPengguna = 0;
        indeksAktif = -1;
        role = "";
    }

    void tampilkanHeader();
    void tampilkanMenuUtama();
    void prosesMenuUtama();
};

// Insertion Sort untuk mengurutkan riwayat berdasarkan kode transaksi 
void Admin::sortKodeTransaksi() {
    for (int i = 1; i < jumlahData; ++i) {
        Riwayat temp = riwayat[i];
        int j = i - 1;

        while (j >= 0 && riwayat[j].kode > temp.kode) {
            riwayat[j + 1] = riwayat[j];
            --j;
        }

        riwayat[j + 1] = temp;
    }
}

// Binary search untuk mencari riwayat transaksi berdasarkan kode transaksi
int Admin::binarySearchRiwayat(const string& keyword) {
	sortKodeTransaksi();
    int kiri = 0;
    int kanan = jumlahData - 1;
    while (kiri <= kanan) {
        int tengah = (kanan + kiri) / 2;
        string namaTengah = riwayat[tengah].kode;
        if (namaTengah == keyword) {
            return tengah;
        } else if (namaTengah < keyword) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    return -1;
}

// Tampilkan hasil search
void Admin::tampilkanHasilBinaryKode(const string& keyword) {
	int idx = binarySearchRiwayat(keyword);
    if (idx != -1) {
        cout << "\n--- RIWAYAT DITEMUKAN ---" << endl;
        cout << riwayat[idx].detailTransaksi << endl;
    } else {
        cout << "Tidak ada riwayat transaksi yang cocok dengan kata kunci " << keyword << endl << endl;
    }
	
}

int Customer::loadUsers() {
    ifstream file("users.txt");
    User tempUser;
    int count = 0;
    string line;
    while (getline(file, line)) {
        if (line.find("Nama") != string::npos) {
        	tempUser.nama = line.substr(line.find(":") + 2);
            getline(file, line); tempUser.username = line.substr(line.find(":") + 2);
            getline(file, line); tempUser.password = line.substr(line.find(":") + 2);
            getline(file, line); tempUser.role     = line.substr(line.find(":") + 2);
            getline(file, line); string strPoin = line.substr(line.find(":") + 2);
            stringstream ss(strPoin); ss >> tempUser.poin;
            getline(file, line); tempUser.alamat   = line.substr(line.find(":") + 2);
            getline(file, line); tempUser.noTelepon= line.substr(line.find(":") + 2);
            user[count++] = tempUser;
            if (count >= MAX_USERS) break;
            getline(file, line);
        }
    }
    file.close();
    jumlahPengguna = count;
    return count;
}

void Customer::saveUsers() {
    ofstream file("users.txt", ios::trunc);
    int i;
    for(i = 0; i < jumlahPengguna; ++i) {
        file << "=========================" << endl;
        file << "Nama       : " << user[i].nama << endl;
        file << "Username   : " << user[i].username << endl;
        file << "Password   : " << user[i].password << endl;
        file << "Role       : " << user[i].role << endl;
        file << "Poin       : " << user[i].poin << endl;
        file << "Alamat     : " << user[i].alamat << endl;
        file << "No.Telepon : " << user[i].noTelepon << endl;
        file << "=========================" << endl << endl;
    }
    file.close();
}

int Customer::login(string& role) {
    string username,password;
    cout << "" << string(40, '-') << endl;
    cout << left << setw(15) << "" << "LOGIN";
    cout << "\n" << string(40, '-') << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;
    int i;
    for(i = 0; i < jumlahPengguna; ++i) {
        if(user[i].username == username && user[i].password == password) {
            role = user[i].role;
            return i;
        }
    }
    cout << "Login gagal. Username atau password salah.\n";
    system("pause");
    system("cls");
    return -1;
}

int Customer::registrasiPengguna() {
	system("cls");
    if(jumlahPengguna >= MAX_USERS) {
        cout << "\nMaksimum pengguna telah tercapai.\n\n";
        system("pause");
    	system("cls");
        return jumlahPengguna;
    }
    User penggunaBaru;
    cout << "" << string(40, '-') << endl;
    cout << left << setw(13) << "" << "REGISTRASI";
    cout << "\n" << string(40, '-') << endl;
    penggunaBaru.role = "customer";
    
    cout << "Nama          : ";
    cin.ignore();
    getline(cin, penggunaBaru.nama);
    int i;
    for(i = 0; i < jumlahPengguna; ++i) {
        if(user[i].nama == penggunaBaru.nama) {
            cout << "\nNama sudah terdaftar!.\n\n";
            system("pause");
    		system("cls");
            return jumlahPengguna;
        }
    }
    
    cout << "Username      : ";
    cin >> penggunaBaru.username;
    for(i = 0; i < jumlahPengguna; ++i) {
        if(user[i].username == penggunaBaru.username) {
            cout << "\nUsername sudah terdaftar!.\n\n";
            system("pause");
    		system("cls");
            return jumlahPengguna;
        }
    }
    
    cout << "Password      : ";
    cin >> penggunaBaru.password;
    cout << "Alamat        : ";
    cin.ignore();
    getline(cin, penggunaBaru.alamat);
    cout << "Nomor Telepon : ";
    cin >> penggunaBaru.noTelepon;
    penggunaBaru.poin = 0;
    
    
    user[jumlahPengguna] = penggunaBaru;
    jumlahPengguna++;
    saveUsers();
    cout << "\nRegistrasi berhasil!\n\n";
    system("pause");
    system("cls");
    return jumlahPengguna;
}

void Customer::tampilkanAkunMenu() {
    cout << "" << string(40, '-') << endl;
    cout << left << setw(13) << "" << "AKUN CUSTOMER";
    cout << "\n" << string(40, '-') << endl;
    cout << "1. Pengaturan Akun\n";
    cout << "2. Berikan Ulasan dan Rating\n";
    cout << "0. Kembali\n\n";
    cout << "Pilih: ";
}

void Customer::pengaturanAkun(User userArr[], int &indeks, int jumlahPengguna) {
    int pilihan;
    string passwordVerifikasi;
    User &current = userArr[indeks];
    bool selesai = false;
    while(!selesai) {
        cout << "" << string(40, '-') << endl;
        cout << left << setw(10) << "" << "PENGATURAN AKUN";
        cout << "\n" << string(40, '-') << endl;

        cout << "1. Ubah Nama" << endl;
        cout << "2. Ubah Username" << endl;
        cout << "3. Ubah Password" << endl;
        cout << "4. Ubah Alamat" << endl;
        cout << "5. Ubah No. Telepon" << endl;
        cout << "6. Lihat Informasi Akun" << endl;
        cout << "0. Kembali" << endl;

        cout << endl;
        cout << "Pilih: ";
        cin >> pilihan;
        if (pilihan < 0 || pilihan > 6) {
            cout << "\nInput tidak valid!" << endl;
            system("pause");
            system("cls");
            continue;
        }
        if (pilihan != 0) {
            cout << "\nMasukkan password saat ini untuk verifikasi: ";
            cin >> passwordVerifikasi;
            if(passwordVerifikasi != current.password) {
                cout << "Password salah. Tidak dapat mengubah data akun.\n\n";
                system("pause");
                system("cls");
                continue;
            }
        }
        switch (pilihan) {
        case 1: {
            string namaBaru;
            cout << "Nama baru: ";
            cin.ignore();
            getline(cin, namaBaru);
            bool namaSudahAda = false;
            for(int i = 0; i < jumlahPengguna; ++i) {
                if(userArr[i].nama == namaBaru && i != indeks) {
                    namaSudahAda = true;
                    break;
                }
            }
            if(namaSudahAda) {
                cout << "Nama sudah digunakan oleh pengguna lain. Silakan gunakan nama lain.\n\n";
            } else {
                current.nama = namaBaru;
                cout << "Nama berhasil diperbarui.\n\n";
            }
            system("pause");
            system("cls");
            break;
        }
        case 2: {
            string usernameBaru;
            cout << "Username baru: ";
            cin >> usernameBaru;
            bool usernameSudahAda = false;
            for(int i = 0; i < jumlahPengguna; ++i) {
                if(userArr[i].username == usernameBaru && i != indeks) {
                    usernameSudahAda = true;
                    break;
                }
            }
            if(usernameSudahAda) {
                cout << "Username sudah digunakan oleh pengguna lain. Silakan pilih yang lain.\n\n";
            } else {
                current.username = usernameBaru;
                cout << "Username berhasil diperbarui.\n\n";
            }
            system("pause");
            system("cls");
            break;
        }
        case 3:
            cout << "Password baru: ";
            cin >> current.password;
            cout << "Password berhasil diperbarui.\n\n";
            system("pause");
            system("cls");
            break;
        case 4:
            cout << "Alamat baru: ";
            cin.ignore();
            getline(cin, current.alamat);
            cout << "Alamat berhasil diperbarui.\n\n";
            system("pause");
            system("cls");
            break;
        case 5:
            cout << "No. Telepon baru: ";
            cin >> current.noTelepon;
            cout << "No. Telepon berhasil diperbarui.\n\n";
            system("pause");
            system("cls");
            break;
        case 6:
            cout << endl;
            cout << "Nama        : " << current.nama << endl;
            cout << "Username    : " << current.username << endl;
            cout << "Password    : " << current.password << endl;
            cout << "Alamat      : " << current.alamat << endl;
            cout << "No. Telepon : " << current.noTelepon << endl;
            cout << endl;
            system("pause");
            system("cls");
            break;
        case 0:
            selesai = true;
            break;
        }
    }
}
		
void Customer::tampilkanInformasiAkun() {
    User &current = user[indeksAktif];
    cout << endl;
	cout << "Nama        : " << current.nama << endl;
    cout << "Username    : " << current.username << endl;
    cout << "Password    : " << current.password << endl;
    cout << "Alamat      : " << current.alamat << endl;
    cout << "No. Telepon : " << current.noTelepon << endl;
}

void Customer::ulasanRating() {
    string komentar;
    int rating;
    while (true) {
        cout << "Berikan Rating (1 - 5): ";
        cin >> rating;
        if (rating < 1 || rating > 5) {
            cout << "Rating harus antara 1 sampai 5." << endl << endl;
        } else {
            break;
        }
    }
    cout << "Berikan Ulasan: ";
    cin.ignore();
    getline(cin, komentar);
    cout << "Ulasan ditambahkan." << endl;
    system("pause");
    ofstream file("ulasanRating.txt", ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan komentar dan rating!" << endl;
        system("pause");
        return;
    }
    file << user[indeksAktif].username << " " << rating << " " << komentar << endl;
    file.close();
}

void Customer::lihatPoin() {
    cout << "Poin Anda saat ini: " << user[indeksAktif].poin << endl;
}

void Customer::kosongkanKeranjang() {
    jumlahKeranjang = 0;
}

void Customer::tambahKeKeranjang(const PesananItem& item) {
    if (item.namaLayanan != "" && jumlahKeranjang < MAX_KERANJANG) {
        keranjangLayanan[jumlahKeranjang++] = item;
        tampilkanRingkasanItem(item);
        cout << "\nItem berhasil ditambahkan ke keranjang!" << endl;
        cout << endl;
    }
}

void Customer::tampilkanKeranjang() {
    if (jumlahKeranjang == 0) {
        cout << "\nKeranjang kosong!" << endl;
        return;
    }
    cout << "\n" << string(50, '=') << endl;
    cout << "                KERANJANG BELANJA" << endl;
    cout << string(50, '=') << endl;
    totalBiaya = 0.0;
    int i;
    for (i = 0; i < jumlahKeranjang; ++i) {
        const PesananItem& item = keranjangLayanan[i];
        cout << "\nItem ke-" << (i + 1) << ":" << endl;
        cout << string(30, '-') << endl;
        cout << "Kategori   \t: " << item.kategoriLayanan << endl;
        cout << "Layanan    \t: " << item.namaLayanan << endl;
        cout << "Item       \t: " << item.namaItem << endl;
        cout << "Jumlah     \t: " << fixed << setprecision(1) << item.beratAtauJumlah << " " << item.unitSatuan << endl;
        cout << "Harga per " << item.unitSatuan << "\t: Rp " << fixed << setprecision(0) << item.hargaPerUnit << endl;
        cout << "Subtotal   \t: Rp " << item.subTotalHarga << endl;
        cout << "Estimasi   \t: " << item.estimasiSelesai << endl;
        totalBiaya += item.subTotalHarga;
    }
    cout << "\n" << string(50, '=') << endl;
    cout << "TOTAL KESELURUHAN: Rp " << fixed << setprecision(0) << totalBiaya << endl;
    cout << string(50, '=') << endl;
}

void Customer::hapusItemKeranjang() {
    if (jumlahKeranjang == 0) {
        cout << "\nKeranjang kosong!" << endl;
        return;
    }
    tampilkanKeranjang();
    int pilihan = inputValidasi<int>("Pilih nomor item yang ingin dihapus: ");
    if (pilihan >= 1 && pilihan <= jumlahKeranjang) {
        int i;
        for (i = pilihan - 1; i < jumlahKeranjang - 1; ++i) {
            keranjangLayanan[i] = keranjangLayanan[i + 1];
        }
        jumlahKeranjang--;
        cout << "\nItem berhasil dihapus!" << endl;
    } else {
        cout << "\nNomor item tidak valid!" << endl;
    }
}

void Customer::tampilkanRingkasanItem(const PesananItem& item) {
    cout << "\n" << string(35, '-') << endl;
    cout << "     RINGKASAN ITEM SAAT INI" << endl;
    cout << string(35, '-') << endl;
    cout << "Kategori   : " << item.kategoriLayanan << endl;
    cout << "Layanan    : " << item.namaLayanan << endl;
    cout << "Item       : " << item.namaItem << endl;
    cout << "Jumlah     : " << fixed << setprecision(1) << item.beratAtauJumlah << " " << item.unitSatuan << endl;
    cout << "Harga per " << item.unitSatuan << " : Rp " << fixed << setprecision(0) << item.hargaPerUnit << endl;
    cout << "Subtotal   : Rp " << item.subTotalHarga << endl;
    cout << "Estimasi   : " << item.estimasiSelesai << endl;
    cout << string(35, '-') << endl;
}

void Customer::tampilkanMenuCustomer() {
    cout << "" << string(40, '-') << endl;
    cout << left << setw(11) << "" << "MENU CUSTOMER";
    cout << "\n" << string(40, '-') << endl;
    cout << "1. Akun\n";
    cout << "2. Lihat Poin\n";
    cout << "3. Lihat Layanan Laundry\n";
    cout << "4. Check Status Cucian\n";
    cout << "0. Logout\n\n";
    cout << "Pilih: ";
}

void Customer::prosesMenuCustomer() {
    int subPilihan;
    while(true) {
        tampilkanMenuCustomer();
        cin >> subPilihan;
        if(subPilihan == 1) {
        	system("cls");
            int pill;
            while (true) {
                tampilkanAkunMenu();
                cin >> pill;
                system("cls");
                if(pill == 1) {
                    pengaturanAkun(user, indeksAktif, jumlahPengguna);
                    saveUsers();
                    system("cls");
                } else if(pill == 2) {
                    ulasanRating();
                    system("cls");
                } else if(pill == 0) {
                    break;
                } else {
                    cout << "\nPilihan tidak valid.\n\n";
                    system("pause");
                    system("cls");
                }
            }
        } else if(subPilihan == 2) {
            lihatPoin();
            cout << endl;
            system("pause");
            system("cls");
        } else if(subPilihan == 3) {
        	system("cls");
            prosesMenuLayanan();
        } else if(subPilihan == 4) {
        	system("cls");
            checkStatusCucian();
        } else if(subPilihan == 0) {
            cout << "\nLogout berhasil.\n\n";
            system("pause");
            system("cls");
            indeksAktif = -1;
            break;
        } else {
            cout << "\nPilihan tidak valid.\n\n";
            system("pause");
            system("cls");
        }
    }
}

void Customer::checkStatusCucian() {
    loadRiwayatTransaksi();  

    string nama = user[indeksAktif].nama;
    bool ditemukan = false;

    for (int i = 0; i < jumlahData; ++i) {
        if (riwayat[i].nama == nama && riwayat[i].status != "Selesai") {
            cout << "\n--- STATUS CUCIAN ---\n";
            cout << riwayat[i].detailTransaksi << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) {
        cout << "Saat ini Anda tidak memiliki cucian yang sedang dalam proses.\n";
    }

    cout << endl;
    system("pause");
    system("cls");
}


void Customer::tampilkanDaftarLayanan() {
    cout << "" << string(40, '-') << endl;
    cout << "       DAFTAR LAYANAN LAUNDRY RDR" << endl;
    cout << string(40, '-') << endl;
    cout << "1.  Layanan Cuci Umum" << endl;
    cout << "2.  Layanan Satuan (Premium)" << endl;
    cout << "3.  Layanan Khusus Barang" << endl;
    cout << "4.  Layanan Dry Cleaning" << endl;
    cout << "5.  Layanan Express" << endl;
    cout << "6.  Antar Jemput" << endl;
    cout << "7.  Paket Langganan" << endl;
    cout << "8.  Lihat Keranjang" << endl;
    cout << "9.  Hapus Item dari Keranjang" << endl;
    cout << "10. Checkout & Pembayaran" << endl;
    cout << "11. Cari Layanan Laundry\n";
    cout << "0.  Keluar" << endl;
    cout << string(40, '-') << endl;
}

// Linear Search untuk Mencari Nama Layanan
void Customer::cariLayananByNama(const string& keyword) {
    bool ditemukan = false;
    string keywordLower = keyword;
    transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower); 

    for (int i = 0; i < jumlahLayanan; ++i) {
        string namaLower = layanan[i].namaLayanan;
        transform(namaLower.begin(), namaLower.end(), namaLower.begin(), ::tolower);

        if (namaLower.find(keywordLower) != string::npos) {
            ditemukan = true;
            cout << "\n--- LAYANAN DITEMUKAN ---" << endl;
            cout << "Nama Layanan : " << layanan[i].namaLayanan << endl;
            cout << "Kategori     : " << layanan[i].kategori << endl;
            cout << "Harga        : Rp " << layanan[i].harga << endl;
            cout << "Satuan       : " << layanan[i].satuan << endl;
        }
    }
    if (!ditemukan) {
        cout << "Layanan dengan kata kunci " << keyword << " tidak ditemukan!" << endl;
    }
}


void Customer::prosesMenuLayanan() {
    int pilihan;
    do {
        tampilkanDaftarLayanan();
        pilihan = inputValidasi<int>("Pilih layanan (0-10): ");
        switch (pilihan) {
            case CUCI_UMUM: {
                int subPilihan;
                tampilkanLayananCuciUmum();
                subPilihan = inputValidasi<int>("Pilih sub-layanan (0 untuk kembali): ");
                if (subPilihan != 0) {
                    PesananItem item = prosesLayananCuciUmum(subPilihan);
                    tambahKeKeranjang(item);
                }
                break;
            }
            case SATUAN_PREMIUM: {
                int subPilihan;
                tampilkanLayananSatuanPremium();
                subPilihan = inputValidasi<int>("Pilih sub-layanan (0 untuk kembali): ");
                if (subPilihan != 0) {
                    PesananItem item = prosesLayananSatuanPremium(subPilihan);
                    tambahKeKeranjang(item);
                }
                break;
            }
            case KHUSUS_BARANG: {
                int subPilihan;
                tampilkanLayananKhususBarang();
                subPilihan = inputValidasi<int>("Pilih sub-layanan (0 untuk kembali): ");
                if (subPilihan != 0) {
                    PesananItem item = prosesLayananKhususBarang(subPilihan);
                    tambahKeKeranjang(item);
                }
                break;
            }
            case DRY_CLEANING: {
                int subPilihan;
                tampilkanLayananDryCleaning();
                subPilihan = validasiInput(0, 10, "Pilih sub-layanan (0 untuk kembali): ");
                if (subPilihan != 0) {
                    PesananItem item = prosesLayananDryCleaning(subPilihan);
                    tambahKeKeranjang(item);
                }
                break;
            }
            case EXPRESS: {
                int subPilihan;
                tampilkanLayananExpress();
                subPilihan = validasiInput(0, 10, "Pilih sub-layanan (0 untuk kembali): ");
                if (subPilihan != 0) {
                    PesananItem item = prosesLayananExpress(subPilihan);
                    tambahKeKeranjang(item);
                }
                break;
            }
            case ANTAR_JEMPUT: {
                int subPilihan;
                tampilkanLayananAntarJemput();
                subPilihan = validasiInput(0, 10, "Pilih sub-layanan (0 untuk kembali): ");
                if (subPilihan != 0) {
                    PesananItem item = prosesLayananAntarJemput(subPilihan);
                    tambahKeKeranjang(item);
                }
                break;
            }
            case PAKET_LANGGANAN: {
                int subPilihan;
                tampilkanLayananPaketLangganan();
                subPilihan = validasiInput(0, 10, "Pilih sub-layanan (0 untuk kembali): ");
                if (subPilihan != 0) {
                    PesananItem item = prosesLayananPaketLangganan(subPilihan);
                    tambahKeKeranjang(item);
                }
                break;
            }
            case 8:
                tampilkanKeranjang();
                break;
            case 9:
                hapusItemKeranjang();
                break;
            case 10: {
                int pilihanMetode;
                string metode;
                cout << "\nPilih metode pembayaran:\n";
                cout << "1. Cash\n";
                cout << "2. Transfer\n";
                cout << "3. Qris\n";
                cout << "4. E-Wallet\n";
                pilihanMetode = validasiInput(1, 4, "Pilihan Anda (1-4): ");
                switch (pilihanMetode) {
                    case 1: metode = "Cash"; break;
                    case 2: metode = "Transfer"; break;
                    case 3: metode = "Qris"; break;
                    case 4: {
                        int pilihanEwallet;
                        cout << "\nPilih jenis E-Wallet:\n";
                        cout << "1. GoPay\n";
                        cout << "2. ShopeePay\n";
                        cout << "3. OVO\n";
                        cout << "4. DANA\n";
                        pilihanEwallet = validasiInput(1, 4, "Pilihan Anda (1-4): ");
                        
                        string jenisEwallet;
                        switch (pilihanEwallet) {
                            case 1: jenisEwallet = "GoPay"; break;
                            case 2: jenisEwallet = "ShopeePay"; break;
                            case 3: jenisEwallet = "OVO"; break;
                            case 4: jenisEwallet = "DANA"; break;
                            default:
                                cout << "Pilihan E-Wallet tidak valid.\n";
                                system("pause");
        						system("cls");
                                return;
                        }
                        metode = "E-Wallet - " + jenisEwallet;
                        break;
                    }
                    default:
                        cout << "Pilihan metode pembayaran tidak valid.\n";
                        system("pause");
        				system("cls");
                        return;
                }
                stringstream ss;
                ss << "RDR" << time(0);
                string kodeTransaksi = ss.str();
                tampilkanStruk(metode, kodeTransaksi);
                simpanRiwayatTransaksi(metode, kodeTransaksi);
                kosongkanKeranjang();
                cout << "\nTerima kasih telah menggunakan layanan kami!\n";
                system("pause");
                system("cls");
                return;
            }
            case 0:
                break;
            case 11: {
            	string keyword;
			    cout << "Masukkan nama layanan yang ingin dicari: ";
			    cin.ignore();
			    getline(cin, keyword);
			
			    cariLayananByNama(keyword);
			    cout << endl;
	            break;
			}
            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n\n";
        }
    	system("pause");
        system("cls");
    } while (pilihan != 0);
}

// Fungsi untuk menampilkan sub layanan Cuci Umum
void Customer::tampilkanLayananCuciUmum() {
    cout << "\n--- Detail Layanan Cuci Umum ---" << endl;
    cout << "1. Cuci Kering (Rp 5.000/kg)" << endl;
    cout << "2. Cuci Basah (Rp 4.000/kg)" << endl;
    cout << "3. Cuci Setrika (Rp 7.000/kg)" << endl;
    cout << "4. Setrika Saja (Rp 4.000/kg)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(32, '-') << endl;
}

// Fungsi untuk memproses layanan Cuci Umum
PesananItem Customer::prosesLayananCuciUmum(int pilihan) {
    PesananItem item;
    item.kategoriLayanan = "Cuci Umum";
    item.unitSatuan = "kg";
    
    switch (pilihan) {
        case 1:
            item.namaLayanan = "Cuci Kering";
            item.hargaPerUnit = 5000.0;
            item.estimasiSelesai = "1-2 hari";
            break;
        case 2:
            item.namaLayanan = "Cuci Basah";
            item.hargaPerUnit = 4000.0;
            item.estimasiSelesai = "1 hari";
            break;
        case 3:
            item.namaLayanan = "Cuci Setrika";
            item.hargaPerUnit = 7000.0;
            item.estimasiSelesai = "2-3 hari";
            break;
        case 4:
            item.namaLayanan = "Setrika Saja";
            item.hargaPerUnit = 4000.0;
            item.estimasiSelesai = "1-2 hari";
            break;
        default:
            item.namaLayanan = "";
            return item;
    }
    
    cout << "\nLayanan Terpilih: " << item.namaLayanan << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    item.namaItem = inputString("Jenis item (Baju/Celana/Campuran): ");
    item.beratAtauJumlah = inputValidasi<double>("Masukkan berat (kg): ");
    item.subTotalHarga = item.beratAtauJumlah * item.hargaPerUnit;
    
    return item;
}

// Fungsi untuk menampilkan sub layanan Satuan Premium
void Customer::tampilkanLayananSatuanPremium() {
    cout << "\n--- Detail Layanan Satuan (Premium) ---" << endl;
    cout << "1. Kemeja/Kaos (Rp 7.000/helai)" << endl;
    cout << "2. Celana/Rok (Rp 7.000/helai)" << endl;
    cout << "3. Jaket/Sweater (Rp 15.000/helai)" << endl;
    cout << "4. Jas/Blazer (Rp 35.000/helai)" << endl;
    cout << "5. Gaun/Kebaya (Rp 35.000/helai)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(39, '-') << endl;
}

// Fungsi untuk memproses layanan Satuan Premium
PesananItem Customer::prosesLayananSatuanPremium(int pilihan) {
    PesananItem item;
    item.kategoriLayanan = "Satuan Premium";
    item.unitSatuan = "helai";
    
    switch (pilihan) {
        case 1:
            item.namaLayanan = "Kemeja/Kaos";
            item.hargaPerUnit = 7000.0;
            item.estimasiSelesai = "1-2 hari";
            break;
        case 2:
            item.namaLayanan = "Celana/Rok";
            item.hargaPerUnit = 7000.0;
            item.estimasiSelesai = "1-2 hari";
            break;
        case 3:
            item.namaLayanan = "Jaket/Sweater";
            item.hargaPerUnit = 15000.0;
            item.estimasiSelesai = "2 hari";
            break;
        case 4:
            item.namaLayanan = "Jas/Blazer";
            item.hargaPerUnit = 35000.0;
            item.estimasiSelesai = "3-4 hari";
            break;
        case 5:
            item.namaLayanan = "Gaun/Kebaya";
            item.hargaPerUnit = 35000.0;
            item.estimasiSelesai = "3-4 hari";
            break;
        default:
            item.namaLayanan = "";
            return item;
    }
    
    cout << "\nLayanan Terpilih: " << item.namaLayanan << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    item.namaItem = inputString("Jenis item spesifik: ");
    item.beratAtauJumlah = inputValidasi<double>("Masukkan jumlah (helai): ");
    item.subTotalHarga = item.beratAtauJumlah * item.hargaPerUnit;
    
    return item;
}

// Fungsi untuk menampilkan sub layanan Khusus Barang
void Customer::tampilkanLayananKhususBarang() {
    cout << "\n--- Detail Layanan Khusus Barang ---" << endl;
    cout << "1. Cuci Sepatu Reguler (Rp 40.000/pasang)" << endl;
    cout << "2. Cuci Sepatu Premium (Rp 65.000/pasang)" << endl;
    cout << "3. Cuci Tas (Rp 40.000/buah)" << endl;
    cout << "4. Cuci Helm (Rp 35.000/buah)" << endl;
    cout << "5. Cuci Gorden (Rp 35.000/meter)" << endl;
    cout << "6. Cuci Karpet (Rp 30.000/lembar)" << endl;
    cout << "7. Cuci Sprei/Bedcover (Rp 25.000/set)" << endl;
    cout << "8. Cuci Selimut/Bantal (Rp 25.000/buah)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(40, '-') << endl;
}

// Fungsi untuk memproses layanan Khusus Barang
PesananItem Customer::prosesLayananKhususBarang(int pilihan) {
    PesananItem item;
    item.kategoriLayanan = "Khusus Barang";
    
    switch (pilihan) {
        case 1:
            item.namaLayanan = "Cuci Sepatu Reguler";
            item.hargaPerUnit = 40000.0;
            item.estimasiSelesai = "2-3 hari";
            item.unitSatuan = "pasang";
            break;
        case 2:
            item.namaLayanan = "Cuci Sepatu Premium";
            item.hargaPerUnit = 65000.0;
            item.estimasiSelesai = "3-4 hari";
            item.unitSatuan = "pasang";
            break;
        case 3:
            item.namaLayanan = "Cuci Tas";
            item.hargaPerUnit = 40000.0;
            item.estimasiSelesai = "3-5 hari";
            item.unitSatuan = "buah";
            break;
        case 4:
            item.namaLayanan = "Cuci Helm";
            item.hargaPerUnit = 35000.0;
            item.estimasiSelesai = "1-2 hari";
            item.unitSatuan = "buah";
            break;
        case 5:
            item.namaLayanan = "Cuci Gorden";
            item.hargaPerUnit = 35000.0;
            item.estimasiSelesai = "3-5 hari";
            item.unitSatuan = "meter";
            break;
        case 6:
            item.namaLayanan = "Cuci Karpet";
            item.hargaPerUnit = 30000.0;
            item.estimasiSelesai = "4-6 hari";
            item.unitSatuan = "lembar";
            break;
        case 7:
            item.namaLayanan = "Sprei/Bedcover";
            item.hargaPerUnit = 25000.0;
            item.estimasiSelesai = "2-3 hari";
            item.unitSatuan = "set";
            break;
        case 8:
            item.namaLayanan = "Selimut/Bantal";
            item.hargaPerUnit = 25000.0;
            item.estimasiSelesai = "2-3 hari";
            item.unitSatuan = "buah";
            break;
        default:
            item.namaLayanan = "";
            return item;
    }
    
    cout << "\nLayanan Terpilih: " << item.namaLayanan << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    item.namaItem = inputString("Jenis item spesifik: ");
    item.beratAtauJumlah = inputValidasi<double>("Masukkan jumlah (" + item.unitSatuan + "): ");
    item.subTotalHarga = item.beratAtauJumlah * item.hargaPerUnit;
    
    return item;
}

// Fungsi untuk menampilkan sub layanan Dry Cleaning
void Customer::tampilkanLayananDryCleaning() {
    cout << "\n--- Detail Layanan Dry Cleaning ---" << endl;
    cout << "1. Jas Formal (Rp 60.000/helai)" << endl;
    cout << "2. Gaun Malam (Rp 80.000/helai)" << endl;
    cout << "3. Kebaya (Rp 60.000/helai)" << endl;
    cout << "4. Pakaian Sutera (Rp 100.000/helai)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(36, '-') << endl;
}

// Fungsi untuk memproses layanan Dry Cleaning
PesananItem Customer::prosesLayananDryCleaning(int pilihan) {
    PesananItem item;
    item.kategoriLayanan = "Dry Cleaning";
    item.unitSatuan = "helai";
    
    switch (pilihan) {
        case 1:
            item.namaLayanan = "Jas Formal";
            item.hargaPerUnit = 60000.0;
            item.estimasiSelesai = "2-4 hari";
            break;
        case 2:
            item.namaLayanan = "Gaun Malam";
            item.hargaPerUnit = 80000.0;
            item.estimasiSelesai = "3-5 hari";
            break;
        case 3:
            item.namaLayanan = "Kebaya";
            item.hargaPerUnit = 60000.0;
            item.estimasiSelesai = "3-5 hari";
            break;
        case 4:
            item.namaLayanan = "Pakaian Sutera";
            item.hargaPerUnit = 100000.0;
            item.estimasiSelesai = "3-5 hari";
            break;
        default:
            item.namaLayanan = "";
            return item;
    }
    
    cout << "\nLayanan Terpilih: " << item.namaLayanan << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    item.namaItem = inputString("Jenis item spesifik: ");
    item.beratAtauJumlah = inputValidasi<double>("Masukkan jumlah (helai): ");
    item.subTotalHarga = item.beratAtauJumlah * item.hargaPerUnit;
    
    return item;
}

// Fungsi untuk menampilkan sub layanan Express
void Customer::tampilkanLayananExpress() {
    cout << "\n--- Detail Layanan Express ---" << endl;
    cout << "1. Same Day Service (Rp 20.000/kg)" << endl;
    cout << "2. Next Day Service (Rp 10.000/kg)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(31, '-') << endl;
}

// Fungsi untuk memproses layanan Express
PesananItem Customer::prosesLayananExpress(int pilihan) {
    PesananItem item;
    item.kategoriLayanan = "Express";
    item.unitSatuan = "kg";
    
    switch (pilihan) {
        case 1:
            item.namaLayanan = "Same Day Service";
            item.hargaPerUnit = 20000.0;
            item.estimasiSelesai = "Selesai hari yang sama";
            break;
        case 2:
            item.namaLayanan = "Next Day Service";
            item.hargaPerUnit = 10000.0;
            item.estimasiSelesai = "Selesai besok hari";
            break;
        default:
            item.namaLayanan = "";
            return item;
    }
    
    cout << "\nLayanan Terpilih: " << item.namaLayanan << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    item.namaItem = inputString("Jenis item (Baju/Celana/Campuran): ");
    item.beratAtauJumlah = inputValidasi<double>("Masukkan berat (kg): ");
    item.subTotalHarga = item.beratAtauJumlah * item.hargaPerUnit;
    
    return item;
}

// Fungsi untuk menampilkan sub layanan Antar Jemput
void Customer::tampilkanLayananAntarJemput() {
    cout << "\n--- Detail Layanan Antar Jemput ---" << endl;
    cout << "1. Radius < 5 KM (Rp 15.000)" << endl;
    cout << "2. Radius 5-10 KM (Rp 25.000)" << endl;
    cout << "3. Di atas 10 KM (Rp 35.000)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(35, '-') << endl;
}

// Fungsi untuk memproses layanan Antar Jemput
PesananItem Customer::prosesLayananAntarJemput(int pilihan) {
    PesananItem item;
    item.kategoriLayanan = "Antar Jemput";
    item.unitSatuan = "layanan";
    item.beratAtauJumlah = 1;
    
    switch (pilihan) {
        case 1:
            item.namaLayanan = "Antar Jemput < 5 KM";
            item.hargaPerUnit = 15000.0;
            item.estimasiSelesai = "Sesuai jadwal";
            break;
        case 2:
            item.namaLayanan = "Antar Jemput 5-10 KM";
            item.hargaPerUnit = 25000.0;
            item.estimasiSelesai = "Sesuai jadwal";
            break;
        case 3:
            item.namaLayanan = "Antar Jemput > 10 KM";
            item.hargaPerUnit = 35000.0;
            item.estimasiSelesai = "Sesuai jadwal";
            break;
        default:
            item.namaLayanan = "";
            return item;
    }
    
    cout << "\nLayanan Terpilih: " << item.namaLayanan << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    item.namaItem = inputString("Alamat tujuan: ");
    item.subTotalHarga = item.hargaPerUnit;
    
    return item;
}

// Fungsi untuk menampilkan sub layanan Paket Langganan
void Customer::tampilkanLayananPaketLangganan() {
    cout << "\n--- Detail Paket Langganan ---" << endl;
    cout << "1. Paket 20kg/bulan (Rp 150.000)" << endl;
    cout << "2. Paket 40kg/bulan (Rp 280.000)" << endl;
    cout << "3. Paket > 40kg/bulan (Rp 400.000)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(31, '-') << endl;
}

// Fungsi untuk memproses layanan Paket Langganan
PesananItem Customer::prosesLayananPaketLangganan(int pilihan) {
    PesananItem item;
    item.kategoriLayanan = "Paket Langganan";
    item.unitSatuan = "paket";
    item.beratAtauJumlah = 1;
    
    switch (pilihan) {
        case 1:
            item.namaLayanan = "Paket 20kg/bulan";
            item.hargaPerUnit = 150000.0;
            item.estimasiSelesai = "Berlaku 1 bulan";
            break;
        case 2:
            item.namaLayanan = "Paket 40kg/bulan";
            item.hargaPerUnit = 280000.0;
            item.estimasiSelesai = "Berlaku 1 bulan";
            break;
        case 3:
            item.namaLayanan = "Paket >40kg/bulan";
            item.hargaPerUnit = 400000.0;
            item.estimasiSelesai = "Berlaku 1 bulan";
            break;
        default:
            item.namaLayanan = "";
            return item;
    }
    
    cout << "\nLayanan Terpilih: " << item.namaLayanan << endl;
    item.namaItem = "Paket Langganan";
    item.subTotalHarga = item.hargaPerUnit;
    
    return item;
}

void Customer::loadPromo() {
    ifstream file("promo.txt");
    jumlahPromo = 0;
    string line;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string nama, diskonStr, tanggal;

        getline(ss, nama, '|');
        getline(ss, diskonStr, '|');
        getline(ss, tanggal, '|');

        float diskon;
        stringstream convert(diskonStr);
        convert >> diskon;

        daftarPromo[jumlahPromo].namaPromo = nama;
        daftarPromo[jumlahPromo].diskon = diskon;
        daftarPromo[jumlahPromo].masaBerlaku = tanggal;

        jumlahPromo++;
    }
    
    file.close();
}


void Customer::checkPromo() {
    loadPromo();
    string tanggal = getTanggalSekarang();
    int nomorPromo = 1;
    bool adaPromo = false;
    totalSetelahPromo = totalBiaya;
    int i;
    for (i = 0; i < jumlahPromo; ++i) {
        if (tanggal <= daftarPromo[i].masaBerlaku && totalSetelahPromo <= totalBiaya) {
            adaPromo = true;
            if (nomorPromo == 1) cout << "PROMO!" << endl;
            cout << nomorPromo << ". " << daftarPromo[i].namaPromo << endl;
            double diskon = daftarPromo[i].diskon;
            double diskonRP = (diskon / 100) * totalBiaya;
            cout << "   Diskon: " << diskon << "%" << " : Rp " << diskonRP << endl;
            cout << "   Berlaku sampai: " << daftarPromo[i].masaBerlaku << endl;
            cout << string(30, '-') << endl;
            nomorPromo++;
            totalSetelahPromo -= diskonRP;
        }
    }
    if (!adaPromo) {
        totalSetelahPromo = 0;
        return;
    } else {
    	TOTAL = totalSetelahPromo;
	}
}

// Struk transaksi
void Customer::tampilkanStruk(const string& metodePembayaran, const string& kodeTransaksi) {
    cout << "\n" << string(50, '=') << endl;
    cout << "                 STRUK PEMBAYARAN" << endl;
    cout << "                 LAUNDRY RDR" << endl;
    cout << string(50, '=') << endl;
    cout << "Kode Transaksi : " << kodeTransaksi << endl;
    cout << "Tanggal        : " << getTanggalSekarang() << endl;
    cout << "Kasir          : Admin" << endl;
    cout << string(50, '-') << endl;
    cout << "Data Pelanggan:" << endl;
    cout << "Nama     : " << user[indeksAktif].nama << endl;
    cout << "Telepon  : " << user[indeksAktif].noTelepon << endl;
    cout << "Alamat   : " << user[indeksAktif].alamat << endl;
    cout << string(50, '-') << endl;
    cout << "Detail Pesanan:" << endl;
    totalBiaya = 0.0;
    int i;
    for (i = 0; i < jumlahKeranjang; ++i) {
        const PesananItem& item = keranjangLayanan[i];
        cout << (i + 1) << ". " << item.namaLayanan << endl;
        cout << "   " << item.namaItem << endl;
        cout << "   " << fixed << setprecision(1) << item.beratAtauJumlah
             << " " << item.unitSatuan << " x Rp " << fixed << setprecision(0)
             << item.hargaPerUnit << " = Rp " << item.subTotalHarga << endl;
        cout << "   Estimasi: " << item.estimasiSelesai << endl;
        totalBiaya += item.subTotalHarga;
    }
    cout << "\nTOTAL KESELURUHAN: Rp " << totalBiaya << endl;
    potonganPoin = 0;
    totalSetelahPromo = 0;
    cout << endl;
    checkPromo();
    TOTAL = totalBiaya;
    if (totalSetelahPromo != totalBiaya) {
    	TOTAL = totalSetelahPromo;
	}
    if (totalSetelahPromo > 0) {
        cout << "\nTOTAL KESELURUHAN SETELAH PROMO: Rp " << fixed << setprecision(0) << TOTAL << endl;
    }
    cout << "Metode Pembayaran: " << metodePembayaran << endl;
    cout << string(50, '=') << endl;
    user[indeksAktif].poin += (int)(totalBiaya / 100);
    cout << "Anda telah memperoleh " << (totalBiaya / 100) << " Poin!" << endl;
    char pil;
    cout << "Total Poin sekarang: " << user[indeksAktif].poin << endl << endl;
    cout << "Apakah ingin menggunakan poin untuk memotong total biaya? (y/n): ";
    cin >> pil;
    if (pil == 'Y' || pil == 'y') {
        while (true) {
            cout << "Masukkan jumlah poin (1 poin = Rp. 1): ";
            cin >> potonganPoin;
            if (potonganPoin > TOTAL) cout << "Poin yg digunakan lebih banyak dari total biaya!" << endl << endl;
            else if (potonganPoin < 0 || potonganPoin > user[indeksAktif].poin) cout <<"Poin anda tidak mencukupi atau tidak valid!" << endl << endl;
            else break;
        }
        cout << "Anda menggunakan " << potonganPoin << " poin." << endl;
        user[indeksAktif].poin -= (int)potonganPoin;
        cout << "\nTOTAL KESELURUHAN SEKARANG: Rp " << fixed << setprecision(0) << TOTAL - potonganPoin << endl;
        cout << "Total Poin sekarang: " << user[indeksAktif].poin << endl << endl;
    }
    saveUsers();
}

// Simpan struk transaksi ke file.txt
void Customer::simpanRiwayatTransaksi(const string& metodePembayaran, const string& kodeTransaksi) {
    ofstream file("riwayat_transaksi.txt", ios::app);
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk menyimpan riwayat transaksi!" << endl;
        return;
    }
    file << "=========================\n";
    file << "Kode Transaksi : " << kodeTransaksi << "\n";
    file << "Tanggal        : " << getTanggalSekarang() <<"\n";
    file << "Nama Pelanggan : " << user[indeksAktif].nama << "\n";
    file << "Telepon        : " << user[indeksAktif].noTelepon << "\n";
    file << "Alamat         : " << user[indeksAktif].alamat << "\n";
    file << "Metode Bayar   : " << metodePembayaran << "\n";
    file << "Status         : Diterima" << "\n";
    file << "-------------------------\n";
    double total = 0.0;
    int i;
    for (i = 0; i < jumlahKeranjang; ++i) {
        const PesananItem& item = keranjangLayanan[i];
        file << "- " << item.kategoriLayanan << " | " << item.namaLayanan << " | "
             << item.namaItem << " | " << fixed << setprecision(1) << item.beratAtauJumlah << " "
             << item.unitSatuan << " x Rp" << fixed << setprecision(0) << item.hargaPerUnit
             << " = Rp" << item.subTotalHarga << "\n";
        total += item.subTotalHarga;
    }
    if (potonganPoin > 0 || totalSetelahPromo > 0) {
        file << "SUBTOTAL.: Rp" << fixed << setprecision(0) << total << "\n";
        if (potonganPoin > 0) {
            file << "Potongan poin: Rp" << potonganPoin << "\n";
            total -= potonganPoin;
        }
        if (totalSetelahPromo > 0) {
            file << "Promo: Rp" << totalBiaya - totalSetelahPromo << "\n";
            total -= totalBiaya - totalSetelahPromo;
        }
    }
    file << "\nTOTAL: Rp" << fixed << setprecision(0) << total << "\n";
    file << "=========================\n\n";
    file.close();
    cout << "Riwayat transaksi berhasil disimpan.\n";
}

void Admin::tampilkanDashboard() {
    string today = getTanggalSekarang();
    double totalPendapatanHariIni = 0;
    int totalPesananHariIni = 0;
    string customerHariIni[100];
    int jumlahCustomerHariIni = 0;
    loadRiwayatTransaksi();

    for (int i = 0; i < jumlahData; i++) {
        if (riwayat[i].tanggalLengkap == today) {
            totalPesananHariIni++;

            bool customerSudahAda = false;
            for (int j = 0; j < jumlahCustomerHariIni; j++) {
                if (customerHariIni[j] == riwayat[i].nama) {
                    customerSudahAda = true;
                    break;
                }
            }
            if (!customerSudahAda && jumlahCustomerHariIni < 100) {
                customerHariIni[jumlahCustomerHariIni] = riwayat[i].nama;
                jumlahCustomerHariIni++;
            }

            if (riwayat[i].status == "Selesai") {
                string detailTransaksi = riwayat[i].detailTransaksi;
                size_t posTotalAkhir = detailTransaksi.rfind("TOTAL: Rp");
                if (posTotalAkhir != string::npos) {
                    size_t posAwalTotal = posTotalAkhir + 9;
                    size_t posAkhirTotal = detailTransaksi.find("\n", posAwalTotal);
                    if (posAkhirTotal == string::npos) {
                        posAkhirTotal = detailTransaksi.length();
                    }
                    if (posAkhirTotal > posAwalTotal) {
                        string totalStr = detailTransaksi.substr(posAwalTotal, posAkhirTotal - posAwalTotal);
                        size_t awal = totalStr.find_first_not_of(" \t\r\n");
                        size_t akhir = totalStr.find_last_not_of(" \t\r\n");
                        if (awal != string::npos && akhir != string::npos) {
                            totalStr = totalStr.substr(awal, akhir - awal + 1);
                        }
                        double totalTransaksi = atof(totalStr.c_str());
                        totalPendapatanHariIni += totalTransaksi;
                    }
                }
            }
        }
    }
    cout << "=== DASHBOARD ADMIN - " << today << " ===\n";
    cout << "Jumlah Pesanan Hari Ini         : " << totalPesananHariIni << endl;
    cout << "Jumlah Customer Pesan Hari Ini  : " << jumlahCustomerHariIni << endl;
    cout << "Pendapatan Selesai Hari Ini     : Rp" << fixed << setprecision(0) << totalPendapatanHariIni << endl;
    cout << "=====================================\n";
}



void Customer::loadRiwayatTransaksi() {
    ifstream file("riwayat_transaksi.txt");
    if (!file.is_open()) {
        jumlahData = 0;
        return;
    }
    string baris;
    int indeks = 0;
    bool sedangMembacaTransaksi = false;
    string detailLengkap = "";
    while (getline(file, baris) && indeks < MAX_RIWAYAT) {
        if (sedangMembacaTransaksi) {
            detailLengkap += baris + "\n";
        }
        if (baris.find("Kode Transaksi : ") == 0) {
            riwayat[indeks].kode = baris.substr(17);
            sedangMembacaTransaksi = true;
            detailLengkap = baris + "\n";
        } else if (baris.find("Tanggal        : ") == 0) {
            string stringTanggal = baris.substr(17);
            riwayat[indeks].tanggalLengkap = stringTanggal;
        } else if (baris.find("Nama Pelanggan : ") == 0) {
            riwayat[indeks].nama = baris.substr(17);
        } else if (baris.find("Telepon        : ") == 0) {
            riwayat[indeks].telepon = baris.substr(17);
        } else if (baris.find("Alamat         : ") == 0) {
            riwayat[indeks].alamat = baris.substr(17);
        } else if (baris.find("Metode Bayar   : ") == 0) {
            riwayat[indeks].metode = baris.substr(17);
        } else if (baris.find("Status         : ") == 0) {
            riwayat[indeks].status = baris.substr(17);
        } else if (baris == "=========================") {
            if (sedangMembacaTransaksi) {
                riwayat[indeks].detailTransaksi = detailLengkap;
                indeks++;
                sedangMembacaTransaksi = false;
                detailLengkap = "";
            }
        }
    }
    jumlahData = indeks;
    file.close();
}

void Admin::loadRiwayatTransaksi() {
    ifstream file("riwayat_transaksi.txt");
    if (!file.is_open()) {
        jumlahData = 0;
        return;
    }
    string baris;
    int indeks = 0;
    bool sedangMembacaTransaksi = false;
    string detailLengkap = "";
    while (getline(file, baris) && indeks < MAX_RIWAYAT) {
        if (sedangMembacaTransaksi) {
            detailLengkap += baris + "\n";
        }
        if (baris.find("Kode Transaksi : ") == 0) {
            riwayat[indeks].kode = baris.substr(17);
            sedangMembacaTransaksi = true;
            detailLengkap = baris + "\n";
        } else if (baris.find("Tanggal        : ") == 0) {
            string stringTanggal = baris.substr(17);
            riwayat[indeks].tanggalLengkap = stringTanggal;
        } else if (baris.find("Nama Pelanggan : ") == 0) {
            riwayat[indeks].nama = baris.substr(17);
        } else if (baris.find("Telepon        : ") == 0) {
            riwayat[indeks].telepon = baris.substr(17);
        } else if (baris.find("Alamat         : ") == 0) {
            riwayat[indeks].alamat = baris.substr(17);
        } else if (baris.find("Metode Bayar   : ") == 0) {
            riwayat[indeks].metode = baris.substr(17);
        } else if (baris.find("Status         : ") == 0) {
            riwayat[indeks].status = baris.substr(17);
        } else if (baris == "=========================") {
            if (sedangMembacaTransaksi) {
                riwayat[indeks].detailTransaksi = detailLengkap;
                indeks++;
                sedangMembacaTransaksi = false;
                detailLengkap = "";
            }
        }
    }
    jumlahData = indeks;
    file.close();
}

void Admin::lihatUserAdmin() {
    ifstream file("users.txt");
    if (!file.is_open()) {
        cerr << "Gagal membuka file users.txt\n";
        return;
    }
    cout << "\n" << string(40, '-') << endl;
    cout << left << setw(10) << "" << "DAFTAR AKUN ADMIN";
    cout << "\n" << string(40, '-') << endl;
    string baris, usernameSekarang = "";
    int jumlahAdmin = 0;
    bool adalahAdmin = false, sudahAdaUsername = false;
    while(getline(file, baris)) {
        if (baris.empty()) continue;
        if (baris == "=========================") {
            if (adalahAdmin && sudahAdaUsername && !usernameSekarang.empty()) {
                jumlahAdmin++;
                cout << jumlahAdmin << ". " << usernameSekarang << endl;
            }
            usernameSekarang = "";
            adalahAdmin = false;
            sudahAdaUsername = false;
            continue;
        }
        if (baris.find("Username   : ") != string::npos) {
            usernameSekarang = baris.substr(13);
            sudahAdaUsername = true;
        }
        if (baris.find("Role       : admin") != string::npos) {
            adalahAdmin = true;
        }
    }
    if (adalahAdmin && sudahAdaUsername && !usernameSekarang.empty()) {
        jumlahAdmin++;
        cout << jumlahAdmin << ". " << usernameSekarang << endl;
    }
    cout << "\nTotal akun admin: " << jumlahAdmin << endl;
    if (jumlahAdmin == 0) {
        cout << "Tidak ada data admin yang ditemukan." << endl;
    }
    file.close();
}

void Admin::lihatUserPengguna() {
    ifstream file("users.txt");
    if (!file.is_open()) {
        cerr << "Gagal membuka file users.txt\n";
        return;
    }
    cout << "\n" << string(40, '-') << endl;
    cout << left << setw(10) << "" << "DAFTAR  AKUN CUSTOMER";
    cout << "\n" << string(40, '-') << endl;
    string baris;
    int jumlahCustomer = 0;
    string dataUser[10];
    int idx = 0;
    bool adalahCustomer = false;
    while(getline(file, baris)) {
        if (baris.empty()) continue;
        if (baris == "=========================") {
            if (adalahCustomer && idx > 0) {
                cout << "=========================" << endl;
                for (int i = 0; i < idx; ++i) {
                    if (dataUser[i].find("Password   : ") == string::npos) {
                        cout << dataUser[i] << endl;
                    }
                }
                cout << "=========================" << endl;
                jumlahCustomer++;
            }
            idx = 0;
            adalahCustomer = false;
            continue;
        }
        dataUser[idx++] = baris;
        if (baris.find("Role       : customer") != string::npos) {
            adalahCustomer = true;
        }
    }
    if (adalahCustomer && idx > 0) {
        cout << "=========================" << endl;
        for (int i = 0; i < idx; ++i) {
            if (dataUser[i].find("Password   : ") == string::npos) {
                cout << dataUser[i] << endl;
            }
        }
        cout << "=========================" << endl;
        jumlahCustomer++;
    }
    cout << "\nTotal akun customer: " << jumlahCustomer << endl;
    if (jumlahCustomer == 0) {
        cout << "Tidak ada data customer yang ditemukan." << endl;
    }
    file.close();
}

void Admin::dataUser() {
    while (true) {
        cout << "\n" << string(40, '-') << endl;
        cout << left << setw(10) << "" << "MENU DATA USER";
        cout << "\n" << string(40, '-') << endl;
        cout << "1. Lihat Data Admin" << endl;
        cout << "2. Lihat Data Customer" << endl;
        cout << "0. Kembali ke Menu Utama" << endl << endl;
        int pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;
        cout << endl;
        switch(pilihan) {
            case 1: lihatUserAdmin(); break;
            case 2: lihatUserPengguna(); break;
            case 0: 
				return;
            default: 
				cout << "Pilihan tidak valid!" << endl; 
        }
    }
}

void Admin::tampilkanHasilPencarian(bool ditemukan[], const string& jenisPencarian) {
    bool adaHasil = false;
    cout << "\nHasil pencarian " << jenisPencarian << ":\n";
    for (int i = 0; i < jumlahData; i++) {
        if (ditemukan[i]) {
            adaHasil = true;
            cout << riwayat[i].detailTransaksi << endl;
        }
    }
    if (!adaHasil) {
        cout << "Data tidak ditemukan.\n";
    }
}

void Admin::cariByTanggal() {
    loadRiwayatTransaksi();
    bool ditemukan[MAX_RIWAYAT] = {0};
    int inputTanggal, inputBulan, inputTahun;
    cout << "=== PENCARIAN BERDASARKAN TANGGAL ===" << endl;
    do {
        cout << "Masukkan tanggal (1-31): ";
        cin >> inputTanggal;
        if (inputTanggal < 1 || inputTanggal > 31) {
            cout << "Input tidak valid! Masukkan angka 1-31." << endl;
        }
    } while (inputTanggal < 1 || inputTanggal > 31);
    do {
        cout << "Masukkan bulan (1-12): ";
        cin >> inputBulan;
        if (inputBulan < 1 || inputBulan > 12) {
            cout << "Input tidak valid! Masukkan angka 1-12." << endl;
        }
    } while (inputBulan < 1 || inputBulan > 12);
    cout << "Masukkan tahun (contoh: 2025): ";
    cin >> inputTahun;
    stringstream ss;
    ss << inputTahun << "-";
    if (inputBulan < 10) ss << "0";
    ss << inputBulan << "-";
    if (inputTanggal < 10) ss << "0";
    ss << inputTanggal;
    string tanggalDicari = ss.str();
    for (int i = 0; i < jumlahData; i++) {
        string detailTransaksi = riwayat[i].detailTransaksi;
        size_t posTanggal = detailTransaksi.find("Tanggal        : ");
        if (posTanggal != string::npos) {
            size_t posAwal = posTanggal + 17;
            size_t posAkhir = detailTransaksi.find("\n", posAwal);
            if (posAkhir != string::npos) {
                string tanggalRiwayat = detailTransaksi.substr(posAwal, posAkhir - posAwal);
                if (tanggalRiwayat == tanggalDicari) {
                    ditemukan[i] = true;
                }
            }
        }
    }
    string kriteria = "berdasarkan tanggal " + tanggalDicari;
    tampilkanHasilPencarian(ditemukan, kriteria);
}

void Admin::cariByNama() {
    loadRiwayatTransaksi();
    bool ditemukan[MAX_RIWAYAT] = {0};
    string nama;
    cout << "Masukkan nama pelanggan: ";
    cin.ignore();
    getline(cin, nama);
    transform(nama.begin(), nama.end(), nama.begin(), (int(*)(int))tolower);
    for (int i = 0; i < jumlahData; i++) {
        string namaRiwayat = riwayat[i].nama;
        transform(namaRiwayat.begin(), namaRiwayat.end(), namaRiwayat.begin(), (int(*)(int))tolower);
        if (namaRiwayat.find(nama) != string::npos) {
            ditemukan[i] = true;
        }
    }
    tampilkanHasilPencarian(ditemukan, "berdasarkan nama");
}

void Admin::cariByKodeTransaksi() {
    loadRiwayatTransaksi();
    bool ditemukan[MAX_RIWAYAT] = {0};
    string kode;
    cout << "Masukkan kode transaksi : ";
    cin >> kode;
    transform(kode.begin(), kode.end(), kode.begin(), (int(*)(int))toupper);
    for (int i = 0; i < jumlahData; i++) {
        string kodeRiwayat = riwayat[i].kode;
        transform(kodeRiwayat.begin(), kodeRiwayat.end(), kodeRiwayat.begin(), (int(*)(int))toupper);
        if (kodeRiwayat.find(kode) != string::npos) {
            ditemukan[i] = true;
        }
    }
    tampilkanHasilPencarian(ditemukan, "berdasarkan kode transaksi");
}

void Admin::cariByStatus() {
    loadRiwayatTransaksi();
    bool ditemukan[MAX_RIWAYAT] = {0};
    cout << "\n--- PENCARIAN BERDASARKAN STATUS ---" << endl;
    cout << "1. Status Selesai" << endl;
    cout << "2. Status Belum Selesai" << endl;
    cout << "0. Kembali" << endl << endl;
    int pilihan;
    cout << "Pilihan: ";
    cin >> pilihan;
    cout << endl;
    string kriteria;
    switch(pilihan) {
        case 1:
            for (int i = 0; i < jumlahData; i++) {
                if (riwayat[i].status == "Selesai") ditemukan[i] = true;
            }
            kriteria = "dengan status Selesai";
            break;
        case 2:
            for (int i = 0; i < jumlahData; i++) {
                if (riwayat[i].status != "Selesai") ditemukan[i] = true;
            }
            kriteria = "dengan status Belum Selesai";
            break;
        case 0: return;
        default: cout << "Pilihan tidak valid!" << endl; return;
    }
    tampilkanHasilPencarian(ditemukan, kriteria);
}

// Fungsi cari riwayat transaksi (linear search)
/*void Admin::cariRiwayatTransaksiLinear(const string& keyword) {
	loadRiwayatTransaksi();
    bool ditemukan = false;
    for (int i = 0; i < jumlahData; ++i) {
        if (riwayat[i].kode == keyword) {
            ditemukan = true;
            cout << "\n--- RIWAYAT DITEMUKAN ---" << endl;
            cout << riwayat[i].detailTransaksi << endl;
        }
    }
    if (!ditemukan) {
        cout << "Tidak ada riwayat transaksi yang cocok dengan kata kunci " << keyword << endl << endl;
    }
}*/

// Fungsi cari data user (linear search)
void Admin::cariUserLinear(const string& keyword) {
    bool ditemukan = false;
    for (int i = 0; i < jumlahPengguna; ++i) {
        if (user[i].username == keyword) {
            ditemukan = true;
            cout << "\n--- USER DITEMUKAN ---" << endl;
            cout << "Nama       : " << user[i].nama << endl;
            cout << "Username   : " << user[i].username << endl;
            cout << "Role       : " << user[i].role << endl;
            cout << "Alamat     : " << user[i].alamat << endl;
            cout << "No.Telepon : " << user[i].noTelepon << endl;
            cout << "Poin       : " << user[i].poin << endl;
            cout << "----------------------" << endl;
        }
    }
    if (!ditemukan) {
        cout << "Tidak ada user yang cocok dengan kata kunci "<< keyword << endl << endl;
    }
}

void Admin::menuCariRiwayat() {
    while (true) {
        cout << "\n" << string(40, '-') << endl;
        cout << left << setw(9) << "" << "MENU PENCARIAN RIWAYAT";
        cout << "\n" << string(40, '-') << endl;
        cout << "1. Cari berdasarkan Tanggal Lengkap (Tanggal-Bulan-Tahun)" << endl;
        cout << "2. Cari berdasarkan Nama Pelanggan" << endl;
        cout << "3. Cari berdasarkan Kode Transaksi" << endl;
        cout << "4. Cari berdasarkan Status" << endl;
        cout << "0. Kembali" << endl << endl;
        int pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;
        cout << endl;
        switch(pilihan) {
            case 1: cariByTanggal(); break;
            case 2: cariByNama(); break;
            case 3:   {
            	string keyword;
				cout << "Masukkan kode transaksi : ";
				cin.ignore();
				getline(cin, keyword);
	            tampilkanHasilBinaryKode(keyword);
				break;
			}
            case 4: cariByStatus(); break;
            case 0: return;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    }
}

// Sortir Riwayat Transaksi Berdasarkan Tanggal 
void Admin::sortRiwayatByTanggalTerbaru() {
    for (int i = 1; i < jumlahData; ++i) {
        Riwayat temp = riwayat[i];
        int j = i - 1;
        while (j >= 0 && riwayat[j].tanggalLengkap < temp.tanggalLengkap) {
            riwayat[j + 1] = riwayat[j];
            --j;
        }
        riwayat[j + 1] = temp;
    }
}

void Admin::bacaRiwayatLayanan() {
    sortRiwayatByTanggalTerbaru();
    if (jumlahData == 0) {
        cout << "Tidak ada riwayat transaksi yang tersedia." << endl;
        return;
    }
    for (int i = 0; i < jumlahData; ++i) {
        cout << riwayat[i].detailTransaksi << endl;
    }
}

void Admin::updateStatus() {
    loadRiwayatTransaksi();
    if (jumlahData == 0) {
        cout << "Tidak ada data transaksi yang tersedia." << endl;
        return;
    }
    string kodeTransaksi;
    cout << "\n=== UPDATE STATUS LAUNDRY ===" << endl;
    cout << "Masukkan kode transaksi: ";
    cin >> kodeTransaksi;
    transform(kodeTransaksi.begin(), kodeTransaksi.end(), kodeTransaksi.begin(), (int(*)(int))toupper);
    int indeksDitemukan = -1;
    for (int i = 0; i < jumlahData; i++) {
        string kodeRiwayat = riwayat[i].kode;
        transform(kodeRiwayat.begin(), kodeRiwayat.end(), kodeRiwayat.begin(), (int(*)(int))toupper);
        if (kodeRiwayat == kodeTransaksi) {
            indeksDitemukan = i;
            break;
        }
    }
    if (indeksDitemukan == -1) {
        cout << "Transaksi dengan kode " << kodeTransaksi << " tidak ditemukan!" << endl;
        return;
    }
    cout << "\nData transaksi ditemukan:" << endl;
    cout << "Kode Transaksi: " << riwayat[indeksDitemukan].kode << endl;
    cout << "Nama Pelanggan: " << riwayat[indeksDitemukan].nama << endl;
    cout << "Status Saat Ini: " << riwayat[indeksDitemukan].status << endl;
    cout << "\nPilih status baru:" << endl;
    cout << "1. Dicuci" << endl;
    cout << "2. Disetrika" << endl;
    cout << "3. Siap Ambil" << endl;
    cout << "4. Diantar" << endl;
    cout << "5. Selesai" << endl;
    cout << "0. Batal Update" << endl;
    int pilihanStatus;
    cout << "Pilihan: ";
    cin >> pilihanStatus;
    string statusBaru;
    switch(pilihanStatus) {
        case 1: statusBaru = "Dicuci"; break;
        case 2: statusBaru = "Disetrika"; break;
        case 3: statusBaru = "Siap Ambil"; break;
        case 4: statusBaru = "Diantar"; break;
        case 5: statusBaru = "Selesai"; break;
        case 0: cout << "Update status dibatalkan." << endl; return;
        default: cout << "Pilihan tidak valid!" << endl; return;
    }
    cout << "\nApakah Anda yakin ingin mengubah status dari '"
         << riwayat[indeksDitemukan].status << "' menjadi '" << statusBaru << "'? (y/n): ";
    char konfirmasi;
    cin >> konfirmasi;
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        riwayat[indeksDitemukan].status = statusBaru;
        string detailLama = riwayat[indeksDitemukan].detailTransaksi;
        size_t posStatus = detailLama.find("Status         : ");
        if (posStatus != string::npos) {
            size_t posAkhirBaris = detailLama.find("\n", posStatus);
            if (posAkhirBaris != string::npos) {
                string barisStatusBaru = "Status         : " + statusBaru;
                riwayat[indeksDitemukan].detailTransaksi =
                    detailLama.substr(0, posStatus) + barisStatusBaru +
                    detailLama.substr(posAkhirBaris);
            }
        }
        simpanRiwayatKeFile();
        cout << "Status berhasil diperbarui menjadi: " << statusBaru << endl;
    } else {
        cout << "Update status dibatalkan." << endl;
    }
}

void Admin::simpanRiwayatKeFile() {
    ofstream file("riwayat_transaksi.txt");
    if (!file.is_open()) {
        cerr << "Gagal membuka file untuk penulisan!" << endl;
        return;
    }
    for (int i = 0; i < jumlahData; i++) {
        file << riwayat[i].detailTransaksi;
        if (i < jumlahData - 1) {
            file << endl;
        }
    }
    file.close();
}

void Admin::buatPromo() {
    string namaPromo, masaBerlaku;
    float diskon;
    
    cout << "\n=== BUAT PROMO BARU ===" << endl;
    
    cout << "Masukkan nama promo: ";
    cin.ignore(); 
    getline(cin, namaPromo);
    
    do {
        cout << "Masukkan besaran diskon (0.1-100): ";
        cin >> diskon;
        
        if (diskon < 0.1 || diskon > 100) {
            cout << "Input tidak valid! Masukkan angka 0.1-100." << endl;
        }
    } while (diskon < 0.1 || diskon > 100);
    
    do {
        cout << "Masukkan masa berlaku (yyyy-mm-dd): ";
        cin >> masaBerlaku;
        
        if (masaBerlaku.length() != 10 || masaBerlaku[4] != '-' || masaBerlaku[7] != '-') {
            cout << "Format tidak valid! Gunakan format yyyy-mm-dd (contoh: 2025-01-31)" << endl;
        } else {
            bool formatValid = true;
            for (int i = 0; i < 10; i++) {
                if (i == 4 || i == 7) continue; 
                if (!isdigit(masaBerlaku[i])) {
                    formatValid = false;
                    break;
                }
            }
            
            if (!formatValid) {
                cout << "Format tidak valid! Gunakan format yyyy-mm-dd dengan angka yang benar" << endl;
            } else {
                string bulanStr = masaBerlaku.substr(5, 2);
                string tanggalStr = masaBerlaku.substr(8, 2);
                int bulan = atoi(bulanStr.c_str());
                int tanggal = atoi(tanggalStr.c_str());
                
                if (bulan < 1 || bulan > 12 || tanggal < 1 || tanggal > 31) {
                    cout << "Tanggal atau bulan tidak valid!" << endl;
                } else {
                    break; 
                }
            }
        }
    } while (true);
    
    cout << "\n=== KONFIRMASI PROMO ===" << endl;
    cout << "Nama Promo   : " << namaPromo << endl;
    cout << "Diskon       : " << diskon << "%" << endl;
    cout << "Masa Berlaku : " << masaBerlaku << endl;
    cout << "\nApakah data promo sudah benar? (y/n): ";
    
    char konfirmasi;
    cin >> konfirmasi;
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        ofstream file("promo.txt", ios::app);
        if (!file.is_open()) {
            cout << "Gagal membuka file promo.txt!" << endl;
            return;
        }
        
        file << namaPromo << "|" << diskon << "|" << masaBerlaku << endl;
        file.close();
        
        cout << "Promo berhasil dibuat dan disimpan!" << endl;
    } else {
        cout << "Pembuatan promo dibatalkan." << endl;
    }
}

void Admin::lihatPromo() {
    ifstream file("promo.txt");
    if (!file.is_open()) {
        cout << "Tidak ada file promo atau gagal membuka file!" << endl;
        return;
    }
    
    cout << "\n" << string(50, '=') << endl;
    cout << left << setw(15) << "" << "DAFTAR PROMO";
    cout << "\n" << string(50, '=') << endl;
    
    string baris;
    int nomorPromo = 1;
    bool adaPromo = false;
    
    while (getline(file, baris)) {
        if (!baris.empty()) {
            adaPromo = true;
            
            size_t pos1 = baris.find('|');
            size_t pos2 = baris.find('|', pos1 + 1);
            
            if (pos1 != string::npos && pos2 != string::npos) {
                string namaPromo = baris.substr(0, pos1);
                string diskonStr = baris.substr(pos1 + 1, pos2 - pos1 - 1);
                string masaBerlaku = baris.substr(pos2 + 1);
                
                cout << nomorPromo << ". " << namaPromo << endl;
                cout << "   Diskon: " << diskonStr << "%" << endl;
                cout << "   Berlaku sampai: " << masaBerlaku << endl;
                cout << string(30, '-') << endl;
                nomorPromo++;
            }
        }
    }
    
    if (!adaPromo) {
        cout << "Belum ada promo yang tersedia." << endl;
    }
    
    file.close();
}

void Admin::hapusPromo() {
    ifstream fileInput("promo.txt");
    if (!fileInput.is_open()) {
        cout << "Tidak ada file promo atau gagal membuka file!" << endl;
        return;
    }
    
    vector<string> daftarPromo;
    string baris;
    
    while (getline(fileInput, baris)) {
        if (!baris.empty()) {
            daftarPromo.push_back(baris);
        }
    }
    fileInput.close();
    
    if (daftarPromo.empty()) {
        cout << "Tidak ada promo yang tersedia untuk dihapus." << endl;
        return;
    }
    
    cout << "\n" << string(50, '=') << endl;
    cout << left << setw(15) << "" << "HAPUS PROMO";
    cout << "\n" << string(50, '=') << endl;
    
    for (size_t i = 0; i < daftarPromo.size(); i++) {
        size_t pos1 = daftarPromo[i].find('|');
        size_t pos2 = daftarPromo[i].find('|', pos1 + 1);
        
        if (pos1 != string::npos && pos2 != string::npos) {
            string namaPromo = daftarPromo[i].substr(0, pos1);
            string diskonStr = daftarPromo[i].substr(pos1 + 1, pos2 - pos1 - 1);
            string masaBerlaku = daftarPromo[i].substr(pos2 + 1);
            
            cout << (i + 1) << ". " << namaPromo << endl;
            cout << "   Diskon: " << diskonStr << "%" << endl;
            cout << "   Berlaku sampai: " << masaBerlaku << endl;
            cout << string(30, '-') << endl;
        }
    }
    
    cout << "0. Batal hapus promo" << endl << endl;
    
    int pilihan;
    cout << "Pilih nomor promo yang akan dihapus: ";
    cin >> pilihan;
    
    if (pilihan == 0) {
        cout << "Penghapusan promo dibatalkan." << endl;
        return;
    }
    
    if (pilihan < 1 || pilihan > (int)daftarPromo.size()) {
        cout << "Pilihan tidak valid!" << endl;
        return;
    }
    
    int indeksHapus = pilihan - 1;
    size_t pos1 = daftarPromo[indeksHapus].find('|');
    size_t pos2 = daftarPromo[indeksHapus].find('|', pos1 + 1);
    
    if (pos1 != string::npos && pos2 != string::npos) {
        string namaPromo = daftarPromo[indeksHapus].substr(0, pos1);
        string diskonStr = daftarPromo[indeksHapus].substr(pos1 + 1, pos2 - pos1 - 1);
        string masaBerlaku = daftarPromo[indeksHapus].substr(pos2 + 1);
        
        cout << "\n=== KONFIRMASI HAPUS PROMO ===" << endl;
        cout << "Promo yang akan dihapus:" << endl;
        cout << "Nama Promo   : " << namaPromo << endl;
        cout << "Diskon       : " << diskonStr << "%" << endl;
        cout << "Masa Berlaku : " << masaBerlaku << endl;
        cout << "\nApakah Anda yakin ingin menghapus promo ini? (y/n): ";
        
        char konfirmasi;
        cin >> konfirmasi;
        
        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            daftarPromo.erase(daftarPromo.begin() + indeksHapus);
            
            ofstream fileOutput("promo.txt");
            if (!fileOutput.is_open()) {
                cout << "Gagal menyimpan perubahan ke file!" << endl;
                return;
            }
            
            for (size_t i = 0; i < daftarPromo.size(); i++) {
                fileOutput << daftarPromo[i] << endl;
            }
            fileOutput.close();
            
            cout << "Promo '" << namaPromo << "' berhasil dihapus!" << endl;
        } else {
            cout << "Penghapusan promo dibatalkan." << endl;
        }
    }
}


void Admin::menuPromo() {
    while (true) {
        cout << "\n" << string(40, '-') << endl;
        cout << left << setw(13) << "" << "MENU PROMO";
        cout << "\n" << string(40, '-') << endl;
        cout << "1. Buat Promo Baru" << endl;
        cout << "2. Lihat Semua Promo" << endl;
        cout << "3. Hapus Promo" << endl;
        cout << "0. Kembali ke Menu Utama" << endl << endl;
        int pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;
        switch(pilihan) {
            case 1: buatPromo(); system("pause"); system("cls"); break;
            case 2: lihatPromo(); system("pause"); system("cls"); break;
            case 3: hapusPromo();  system("pause"); system("cls"); break;
            case 0: return;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    }
}

void Admin::ulasanRating() {
    string komentar, nama, line;
    int rating;
    ifstream file("ulasanRating.txt");
    if (!file.is_open()) {
        cout << "Gagal membuka file untuk melihat ulasan dan rating!" << endl;
        return;
    }
    while (file >> nama >> rating && file.ignore() && getline(file, komentar)) {
        cout << "----------------" << endl;
        cout << "Rating   : " << rating << endl;
        cout << "Username : " << nama << endl;
        cout << "Komentar : " << komentar << endl;
        cout << "----------------" << endl;
        cout << "Lanjut ke ulasan berikutnya?(y/n): " ;
        char pil;
        cin >> pil;
        cout << endl;
        if (pil != 'y' && pil != 'Y') break;
    }
    cout << "Sudah tidak ada ulasan lagi :>" << endl;
    file.close();
}

void Admin::hitungPendapatanBulanan() {
    loadRiwayatTransaksi();
    if (jumlahData == 0) {
        cout << "Tidak ada data transaksi yang tersedia." << endl;
        return;
    }
    int bulanInput, tahunInput;
    cout << "\n=== HITUNG PENDAPATAN BULANAN ===" << endl;
    do {
        cout << "Masukkan bulan (1-12): ";
        cin >> bulanInput;
        if (bulanInput < 1 || bulanInput > 12) {
            cout << "Input tidak valid! Masukkan angka 1-12." << endl;
        }
    } while (bulanInput < 1 || bulanInput > 12);
    cout << "Masukkan tahun (contoh: 2025): ";
    cin >> tahunInput;
    string namaBulan[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni",
                         "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    int totalPendapatan = 0;
    int jumlahTransaksiSelesai = 0;
    for (int i = 0; i < jumlahData; i++) {
        if (riwayat[i].status == "Selesai") {
            string detailTransaksi = riwayat[i].detailTransaksi;
            size_t posTanggal = detailTransaksi.find("Tanggal        : ");
            if (posTanggal != string::npos) {
                size_t posAwal = posTanggal + 17;
                size_t posAkhir = detailTransaksi.find("\n", posAwal);
                if (posAkhir != string::npos) {
                    string tanggalRiwayat = detailTransaksi.substr(posAwal, posAkhir - posAwal);
                    if (tanggalRiwayat.length() >= 10) {
                        string tahunStr = tanggalRiwayat.substr(0, 4);
                        string bulanStr = tanggalRiwayat.substr(5, 2);
                        int tahunRiwayat = atoi(tahunStr.c_str());
                        int bulanRiwayat = atoi(bulanStr.c_str());
                        if (bulanRiwayat == bulanInput && tahunRiwayat == tahunInput) {
                            size_t posTotalAkhir = detailTransaksi.rfind("TOTAL: Rp");
                            if (posTotalAkhir != string::npos) {
                                size_t posAwalTotal = posTotalAkhir + 9;
                                size_t posAkhirTotal = detailTransaksi.find("\n", posAwalTotal);
                                if (posAkhirTotal == string::npos)
                                    posAkhirTotal = detailTransaksi.length();
                                if (posAkhirTotal > posAwalTotal) {
                                    string totalStr = detailTransaksi.substr(posAwalTotal, posAkhirTotal - posAwalTotal);
                                    size_t awal = totalStr.find_first_not_of(" \t\r\n");
                                    size_t akhir = totalStr.find_last_not_of(" \t\r\n");
                                    if (awal != string::npos && akhir != string::npos) {
                                        totalStr = totalStr.substr(awal, akhir - awal + 1);
                                    }
                                    int totalTransaksi = atoi(totalStr.c_str());
                                    totalPendapatan += totalTransaksi;
                                    jumlahTransaksiSelesai++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << "\n" << string(40, '=') << endl;
    cout << "LAPORAN PENDAPATAN BULANAN" << endl;
    cout << string(40, '=') << endl;
    cout << "Bulan/Tahun             : " << namaBulan[bulanInput-1] << " " << tahunInput << endl;
    cout << "Jumlah Transaksi Selesai: " << jumlahTransaksiSelesai << endl;
    cout << "Pendapatan bulan ini    : Rp" << totalPendapatan << endl;
    cout << string(40, '=') << endl;
    if (jumlahTransaksiSelesai == 0) {
        cout << "Tidak ada transaksi yang selesai pada bulan tersebut." << endl;
    }
}

void Admin::PengaturanAkun() {
    pengaturanAkun(user, indeksAktif, jumlahPengguna);	
    saveUsers();
}

void Admin::menuAdmin() {
    while (true) {
        cout << "\n" << string(40, '-') << endl;
        cout << left << setw(13) << "" << "MENU ADMIN";
        cout << "\n" << string(40, '-') << endl;
        tampilkanDashboard();
        cout << "1. Pengaturan " << endl;
        cout << "2. Lihat Semua Riwayat Transaksi" << endl;
        cout << "3. Cari riwayat Transaksi" << endl;
        cout << "4. Lihat Data Users" << endl;
        cout << "5. Cari Data Users" << endl;
        cout << "6. Update Status" << endl;
        cout << "7. Pendapatan perbulan" << endl;
        cout << "8. Lihat Ulasan" << endl;
        cout << "9. Kelola Promo" << endl;
        cout << "0. Logout" << endl << endl;
        int pilihan;
        cout << "Pilihan: ";
        cin >> pilihan;
        if (pilihan == 1) {
        	system("cls");
            pengaturanAkun(user, indeksAktif, jumlahPengguna);
            saveUsers();
        } else if (pilihan == 2) {
        	system("cls");
            cout << "\n" << string(40, '-') << endl;
            cout << left << setw(10) << "" << "RIWAYAT TRANSAKSI";
            cout << "\n" << string(40, '-') << endl;
            bacaRiwayatLayanan();
        } else if (pilihan == 4) {
        	system("cls");
            dataUser();
        } else if (pilihan == 5) {
        	string keyword;
			cout << "Masukkan username : ";
			cin.ignore();
			getline(cin, keyword);
            cariUserLinear(keyword);
        } else if (pilihan == 3) {
        	system("cls");
        	menuCariRiwayat();
        } else if (pilihan == 6) {
        	system("cls");
            updateStatus();
        } else if (pilihan == 7) {
        	system("cls");
            hitungPendapatanBulanan();
        } else if (pilihan == 8) {
            system("cls");
            cout << "\n" << string(40, '-') << endl;
            cout << left << setw(10) << "" << "ULASAN CUSTOMER";
            cout << "\n" << string(40, '-') << endl;
            ulasanRating();
        } else if (pilihan == 9) {
            system("cls");
            menuPromo();
        } else if (pilihan == 0) {
            cout << "Logout berhasil. Terima kasih!" << endl;
            system("pause");
        	system("cls");
            break;
        } else {
            cout << "Input tidak valid!" << endl;
        }
        system("pause");
        system("cls");
    }
}

void LaundrySystem::tampilkanHeader() {
    cout << "" << string(50, '=') << endl;
    cout << "       SISTEM MANAJEMEN LAUNDRY RDR" << endl;
    cout << "          Solusi Terpercaya Untuk" << endl;
    cout << "          Kebutuhan Laundry Anda" << endl;
    cout << string(50, '=') << endl;
}

void LaundrySystem::tampilkanMenuUtama() {
    cout << "\n" << string(40, '-') << endl;
    cout << left << setw(13) << "" << "MENU UTAMA";
    cout << "\n" << string(40, '-') << endl;
    cout << "1. Login" << endl;
    cout << "2. Registrasi" << endl;
    cout << "0. Keluar" << endl << endl;
    cout << "Pilih: ";
}

void LaundrySystem::prosesMenuUtama() {
    int pilihan;
    customer.loadUsers();
    admin.jumlahPengguna = customer.jumlahPengguna;
    int i;
    for (i = 0; i < customer.jumlahPengguna; ++i) {
        admin.user[i] = customer.user[i];
    }
    while(true) {
    	tampilkanHeader();
        tampilkanMenuUtama();
        cin >> pilihan;
        if(pilihan == 1) {
        	system("cls");
            customer.indeksAktif = customer.login(role);
            if(customer.indeksAktif != -1) {
                cout << "Login berhasil sebagai " << role << ".\n\n";
                if(role == "customer") {
                	system("pause");
                	system("cls");
                    customer.prosesMenuCustomer();
                } else if(role == "admin") {
                    admin.indeksAktif = customer.indeksAktif;
                    system("pause");
                	system("cls");
                    admin.menuAdmin();
                }
            }
        } else if(pilihan == 2) {
            customer.registrasiPengguna();
            customer.saveUsers();
        } else if(pilihan == 0) {
            cout << "Terima kasih. Program selesai.\n";
            break;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

int main() {
    LaundrySystem sistem;
    
    sistem.prosesMenuUtama();
    return 0;
}
