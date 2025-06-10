#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <fstream>
using namespace std;

//  maksimal akun pengguna yang dapat ditampung
int const MAX_USERS = 100; 

// Struktur untuk menyimpan item layanan yang dipesan
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

// Struktur untuk menyimpan informasi pelanggan
struct User {
    string noTelepon;
    string alamat;
    string tanggalPesan;
    string username;
    string password;
    string role; // Admin atau Customer
    int poin;
};

// struktur untuk menyimpan riwayat transaksi customer
struct Riwayat {
    string tanggal;
    string bulan;
    string tahun;
    string kode;
    string nama;
    string telepon;
    string alamat;
    string metode;
    string status;
    string detailTransaksi; // Untuk menyimpan detail lengkap transaksi
};

// Enum untuk jenis layanan
enum JenisLayanan {
    CUCI_UMUM = 1,
    SATUAN_PREMIUM = 2,
    KHUSUS_BARANG = 3,
    DRY_CLEANING = 4,
    EXPRESS = 5,
    ANTAR_JEMPUT = 6,
    PAKET_LANGGANAN = 7
};

// Class untuk mengelola sistem laundry
class LaundrySystem {
	private:
		string role;
		vector<PesananItem> keranjangLayanan;
		double potonganPoin;
	    double totalBiaya;
	    double totalSetelahPromo;
	    double TOTAL;
	
	public:
		int indeksAktif;
		User user[MAX_USERS];
		int jumlahPengguna;
		LaundrySystem();
		
		void tampilkanMenuUtama();
		void tampilkanMenuCustomer();
		void tampilkanMenuAkunCustomer();
		void prosesMenuUtama();
		void prosesMenuCustomer();
		void prosesAkunCustomer();
		void ulasanRating();
		int pengguna(User daftarPengguna[]);
		void simpanPengguna(const User daftarPengguna[], int jumlahPengguna);
		int login(const User daftarPengguna[], int jumlahPengguna, string& role);
		int registrasiPengguna(User daftarPengguna[], int jumlahPengguna);
		void pengaturanAkun(User& user, const User daftarPengguna[], int jumlahPengguna);
		void prosesMenuLayanan();
		string getTanggalSekarang();
	    template<typename T>
		T inputValidasi(const string& pesan);
		string inputString(const string& pesan);
		void tampilkanHeader();
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
		void tampilkanRingkasanItem(const PesananItem& item);
		void tambahKeKeranjang(const PesananItem& item);
		void tampilkanKeranjang();
		void hapusItemKeranjang();
		void checkPromo();
		void tampilkanStruk(const string& metodePembayaran, const string& kodeTransaksi);
		void simpanRiwayatTransaksi(const string& metodePembayaran, const string& kodeTransaksi);
};

// Class untuk mengelola sistem Admin
class Admin {
	private:
	    static const int MAKSIMAL_RIWAYAT = 100;
	    
	    // Array untuk menyimpan data riwayat
	    Riwayat riwayat[MAKSIMAL_RIWAYAT];
	    int jumlahData;

	public:
		Admin();
	    int indeksAktif;
	    User user[MAX_USERS];
	    int jumlahPengguna;
		
	    void bacaRiwayatLayanan();
	    void loadRiwayatTransaksi();
	    void lihatUserAdmin();
	    void lihatUserPengguna();
	    void dataUser();
	    void tampilkanHasilPencarian(bool ditemukan[], const string& jenisPencarian);
	    void cariByTanggal();
	    void cariByNama();
	    void cariByKodeTransaksi();
	    void cariByStatus();
	    void menuCariRiwayat();
	    void updateStatus(); // Fungsi baru untuk update status
	    void simpanRiwayatKeFile(); // Fungsi helper untuk menyimpan ke file
	    void menuAdmin();
	    void hitungPendapatanBulanan();
	    void ulasanRating();
	    void buatPromo();
		void lihatPromo();
		void menuPromo();
		void hapusPromo();
};

// Konstruktor Class LaundrySystem
LaundrySystem::LaundrySystem() {
	totalBiaya = 0.0;
	jumlahPengguna = pengguna(user);
    indeksAktif = -1;
}

// Konstruktor untuk class Admin
Admin::Admin() {
	
}

// Fungsi untuk menampilkan menu utama
void LaundrySystem::tampilkanMenuUtama() {
	cout << "\n" << string(40, '-') << endl;
    cout << left << setw(13) << "" << "MENU UTAMA";
    cout << "\n" << string(40, '-') << endl;
    cout << "1. Login" << endl;
	cout << "2. Registrasi" << endl;
	cout << "0. Keluar" << endl << endl;
    cout << "Pilih: ";
}

// Fungsi untuk proses menu utama
void LaundrySystem::prosesMenuUtama() {
    int pilihan;
    
    while(true) {
        tampilkanMenuUtama();
        cin >> pilihan;

        if(pilihan == 1) {
            indeksAktif = login(user, jumlahPengguna, role);
            if(indeksAktif != -1) {
                cout << "Login berhasil sebagai "<<role<<".\n";
                
                if(role == "customer") {
                    prosesMenuCustomer();
                } else if(role == "admin") {
                	Admin admin;
                	admin.indeksAktif = indeksAktif;
					admin.jumlahPengguna = jumlahPengguna;
					for (int i = 0; i < jumlahPengguna; i++) {
						admin.user[i] = user[i];	
					}
                    admin.menuAdmin();
                }
            }
        } else if(pilihan == 2) {
            jumlahPengguna = registrasiPengguna(user, jumlahPengguna);
        } else if(pilihan == 0) {
            cout << "Terima kasih. Program selesai.\n";
            break;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

// Fungsi untuk menampilkan menu customer
void LaundrySystem::tampilkanMenuCustomer() {
	cout << "\n" << string(40, '-') << endl;
    cout << left << setw(11) << "" << "MENU CUSTOMER";
    cout << "\n" << string(40, '-') << endl;
    cout << "1. Akun\n";
    cout << "2. Lihat Poin\n";
    cout << "3. Lihat Layanan Laundry\n";
    cout << "0. Logout\n\n";
    cout << "Pilih: ";
}

// Fungsi untuk proses menu customer
void LaundrySystem::prosesMenuCustomer() {
    int subPilihan;
    
    while(true) {
        tampilkanMenuCustomer();
        cin >> subPilihan;
        
        if(subPilihan == 1) {
            prosesAkunCustomer();
        } else if(subPilihan == 2) {
            // Lihat poin customer
            cout << "Poin Anda saat ini: "<<user[indeksAktif].poin<<endl;
        } else if(subPilihan == 3) {	
            prosesMenuLayanan();
        } else if(subPilihan == 0) {
            cout << "Logout berhasil.\n";
            indeksAktif = -1;
            break;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}
 
// Fungsi untuk menampilkan menu akun customer
void LaundrySystem::tampilkanMenuAkunCustomer() {
	cout << "\n" << string(40, '-') << endl;
    cout << left << setw(13) << "" << "AKUN CUSTOMER";
    cout << "\n" << string(40, '-') << endl;
    cout << "1. Pengaturan Akun\n";
    cout << "2. Berikan Ulasan dan Rating\n";
    cout << "0. Kembali\n\n";
    cout << "Pilih: ";
}

// Fungsi untuk memberi ulasan dan rating
void LaundrySystem::ulasanRating() {
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
	
	ofstream file("ulasanRating.txt", ios::app); // mode append
	if (!file.is_open()) {
	    cout << "Gagal membuka file untuk menyimpan komentar dan rating!" << endl;
	    return;
	}
	file << user[indeksAktif].username << " " << rating << " " << komentar;
	file.close();
}

// Fungsi untuk proses menu akun customer
void LaundrySystem::prosesAkunCustomer() {
    int pill;
    
    while (true) {
    	tampilkanMenuAkunCustomer();
    	cin >> pill;
	    if(pill == 1) {
            pengaturanAkun(user[indeksAktif], user, jumlahPengguna);
            simpanPengguna(user, jumlahPengguna);
            break;
		} else if(pill == 2) {
        	ulasanRating();
        	break;
		} else if(pill == 0) {
            break;
		} else {
			cout << "Pilihan tidak valid.\n";
		}
	}
}

// Fungsi untuk memuat data pengguna dari users.txt
int LaundrySystem::pengguna(User daftarPengguna[]) {
    ifstream file("users.txt");
    User user;
    int count = 0;
    string line;
    while (getline(file, line)) {
	    if (line.find("Username") != string::npos) {
	
	        // Ambil username
	        user.username = line.substr(line.find(":") + 2);
	
	        getline(file, line); user.password = line.substr(line.find(":") + 2);
	        getline(file, line); user.role     = line.substr(line.find(":") + 2);
	        getline(file, line); string strPoin = line.substr(line.find(":") + 2);
            	stringstream ss(strPoin); ss >> user.poin;
	        getline(file, line); user.alamat   = line.substr(line.find(":") + 2);
	        getline(file, line); user.noTelepon= line.substr(line.find(":") + 2);
	
	        daftarPengguna[count++] = user;
	        if (count >= MAX_USERS) break;
	
	        // Lewati garis pemisah (jika ada)
	        getline(file, line);
    	}
    }
    file.close();
    return count;
}

// Fungsi untuk simpan data pengguna ke file.txt
void LaundrySystem::simpanPengguna(const User daftarPengguna[], int jumlahPengguna) {
    ofstream file("users.txt", ios::trunc);
    for(int i = 0; i < jumlahPengguna; ++i) {
    	file << "=========================" << endl;
        file << "Username   " << ": " << daftarPengguna[i].username << endl;
		file << "Password   " << ": " << daftarPengguna[i].password << endl;
		file << "Role       " << ": " << daftarPengguna[i].role << endl;
		file << "Poin       " << ": " << daftarPengguna[i].poin << endl;
		file << "Alamat     " << ": " << daftarPengguna[i].alamat << endl;
		file << "No.Telepon " << ": " << daftarPengguna[i].noTelepon << endl;
		file << "=========================" << endl << endl;
    }
    file.close();
}

// Fungsi untuk login
int LaundrySystem::login(const User daftarPengguna[], int jumlahPengguna, string& role) {
    string username,password;
    cout << "\n" << string(40, '-') << endl;
    cout << left << setw(15) << "" << "LOGIN";
    cout << "\n" << string(40, '-') << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    for(int i = 0; i < jumlahPengguna; ++i) {
        if(daftarPengguna[i].username == username && daftarPengguna[i].password == password) {
            role = daftarPengguna[i].role;
            return i;
        }
    }
    cout << "Login gagal. Username atau password salah.\n";
    return -1;
}

// Fungsi untuk registrasi
int LaundrySystem::registrasiPengguna(User daftarPengguna[], int jumlahPengguna) {
    if(jumlahPengguna >= MAX_USERS) {
        cout << "Maksimum pengguna telah tercapai.\n";
        return jumlahPengguna;
    }
    
    User penggunaBaru;
    cout << "\n" << string(40, '-') << endl;
    cout << left << setw(13) << "" << "REGISTRASI";
    cout << "\n" << string(40, '-') << endl;
    // Pilih role
    cout << "Role (admin/customer): ";
    cin >> penggunaBaru.role;
    if(penggunaBaru.role != "admin" && penggunaBaru.role != "customer") {
        cout << "Role tidak valid. Gunakan 'admin' atau 'customer'.\n";
        return jumlahPengguna;
    }
    
    if(penggunaBaru.role == "admin") {
	    cout << "Username: ";
	    cin >> penggunaBaru.username;
	    cout << "Password: ";
	    cin >> penggunaBaru.password;	
	    penggunaBaru.poin = 0;
	    penggunaBaru.alamat = "-";
	    penggunaBaru.noTelepon = "-";
	} else if(penggunaBaru.role == "customer") {
		cout << "Username: ";
	    cin >> penggunaBaru.username;
	    cout << "Password: ";
	    cin >> penggunaBaru.password;	
	    cout << "Alamat: ";
	    cin.ignore();
	    getline(cin, penggunaBaru.alamat);
	    cout << "Nomor Telepon: ";
	    cin >> penggunaBaru.noTelepon;
	    penggunaBaru.poin = 0;
	}
    
    // Cek duplikasi username
    for(int i = 0; i < jumlahPengguna; ++i) {
        if(daftarPengguna[i].username == penggunaBaru.username) {
            cout << "Username sudah terdaftar.\n";
            return jumlahPengguna;
        }
    }
    
    daftarPengguna[jumlahPengguna] = penggunaBaru;
    jumlahPengguna++;
    simpanPengguna(daftarPengguna, jumlahPengguna);
    cout << "Registrasi berhasil!\n";
    return jumlahPengguna;
}

// Fungsi untuk edit akun
void LaundrySystem::pengaturanAkun(User& user, const User daftarPengguna[], int jumlahPengguna) {
    int pilihan;
    string passwordVerifikasi;
	
    while(true) {
    	cout << "\n" << string(40, '-') << endl;
	    cout << left << setw(10) << "" << "PENGATURAN AKUN";
	    cout << "\n" << string(40, '-') << endl;
    	if (user.role == "admin") {;
	        cout << "1. Ubah Username" << endl;
			cout << "2. Ubah Password" << endl;
			cout << "3. Lihat Informasi Akun" << endl;
			cout << "0. Kembali" << endl;
		} else if (user.role == "customer") {
	        cout << "1. Ubah Username" << endl;
			cout << "2. Ubah Password" << endl;
			cout << "3. Ubah Alamat" << endl;
			cout << "4. Ubah No. Telepon" << endl;
			cout << "5. Lihat Informasi Akun" << endl;
			cout << "0. Kembali" << endl;
		}
		cout << endl;
		cout << "Pilih: ";
        cin >> pilihan;
		
        if(pilihan == 1) {
            cout << "\nMasukkan password saat ini untuk verifikasi: ";
            cin >> passwordVerifikasi;
            if(passwordVerifikasi == user.password) {
                string usernameBaru;
                cout << "Username baru: ";
                cin >> usernameBaru;

                // Cek apakah username baru sudah digunakan user lain
                bool usernameSudahAda = false;
                for(int i = 0; i < jumlahPengguna; ++i) {
                    if(daftarPengguna[i].username == usernameBaru && &daftarPengguna[i] != &user) {
                        usernameSudahAda = true;
                        break;
                    }
            	}
                if(usernameSudahAda) {
                    cout << "Username sudah digunakan oleh pengguna lain. Silakan pilih yang lain.\n";
                } else {
                    user.username = usernameBaru;
                    cout << "Username berhasil diperbarui.\n";
                }
            } else {
                cout << "Password salah. Tidak dapat mengubah username.\n";
            }
        } else if(pilihan == 2) {
            cout << "\nMasukkan password saat ini untuk verifikasi: ";
            cin >> passwordVerifikasi;
            if(passwordVerifikasi == user.password) {
                cout << "Password baru: ";
                cin >> user.password;
                cout << "Password berhasil diperbarui.\n";
            } else {
                cout << "Password salah. Tidak dapat mengubah password.\n";
            	}
        } else if(pilihan == 3 && user.role == "customer") {
            cout << "\nMasukkan password saat ini untuk verifikasi: ";
            cin >> passwordVerifikasi;
            if(passwordVerifikasi == user.password) {
                cout << "Alamat baru: ";
                cin.ignore();
	    		getline(cin, user.alamat);
                cout << "Alamat berhasil diperbarui.\n";
            } else {
                cout << "Password salah. Tidak dapat mengubah alamat.\n";
				} 
		} else if(pilihan == 4 && user.role == "customer") {
            cout << "\nMasukkan password saat ini untuk verifikasi: ";
            cin >> passwordVerifikasi;
            if(passwordVerifikasi == user.password) {
                cout << "No. Telepon baru: ";
                cin >> user.noTelepon;
                cout << "No. Telepon berhasil diperbarui.\n";
            } else {
           		cout << "Password salah. Tidak dapat mengubah No. Telepon.\n";
           	}
		} else if(pilihan == 3 && user.role == "admin" || pilihan == 5 && user.role == "customer") {
			cout << endl;
    		if(user.role == "customer") {
	            cout << "Username: " << user.username << endl;
				cout << "Password: " << user.password << endl;
				cout << "Alamat: " << user.alamat << endl;
				cout << "No. Telepon: " << user.noTelepon << endl;
			} else {
				cout << "Username: " << user.username << endl;
				cout << "Password: " << user.password << endl;
			}
        } else if(pilihan == 0) {
            break;
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    }
}

// Fungsi untuk proses menu layanan laundry
void LaundrySystem::prosesMenuLayanan() {
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
	            subPilihan = inputValidasi<int>("Pilih sub-layanan (0 untuk kembali): ");
	            if (subPilihan != 0) {
	                PesananItem item = prosesLayananDryCleaning(subPilihan);
	                tambahKeKeranjang(item);
	            }
	            break;
	        }
	        case EXPRESS: {
	            int subPilihan;
	            tampilkanLayananExpress();
	            subPilihan = inputValidasi<int>("Pilih sub-layanan (0 untuk kembali): ");
	            if (subPilihan != 0) {
	                PesananItem item = prosesLayananExpress(subPilihan);
	                tambahKeKeranjang(item);
	            }
	            break;
	        }
	        case ANTAR_JEMPUT: {
	            int subPilihan;
	            tampilkanLayananAntarJemput();
	            subPilihan = inputValidasi<int>("Pilih sub-layanan (0 untuk kembali): ");
	            if (subPilihan != 0) {
	                PesananItem item = prosesLayananAntarJemput(subPilihan);
	                tambahKeKeranjang(item);
	            }
	            break;
	        }
	        case PAKET_LANGGANAN: {
	            int subPilihan;
	            tampilkanLayananPaketLangganan();
	            subPilihan = inputValidasi<int>("Pilih sub-layanan (0 untuk kembali): ");
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
	            cout << "Pilihan Anda (1-4): ";
	            cin >> pilihanMetode;
	
	            switch (pilihanMetode) {
	                case 1:
	                    metode = "Cash";
	                    break;
	                case 2:
	                    metode = "Transfer";
	                    break;
	                case 3:
	                    metode = "Qris";
	                    break;
	                case 4: {
	                    int pilihanEwallet;
	                    cout << "\nPilih jenis E-Wallet:\n";
	                    cout << "1. GoPay\n";
	                    cout << "2. ShopeePay\n";
	                    cout << "3. OVO\n";
	                    cout << "4. DANA\n";
	                    cout << "Pilihan Anda (1-4): ";
	                    cin >> pilihanEwallet;
	
	                    string jenisEwallet;
	                    switch (pilihanEwallet) {
	                        case 1: jenisEwallet = "GoPay"; break;
	                        case 2: jenisEwallet = "ShopeePay"; break;
	                        case 3: jenisEwallet = "OVO"; break;
	                        case 4: jenisEwallet = "DANA"; break;
	                        default:
	                            cout << "Pilihan E-Wallet tidak valid.\n";
	                            return;
	                    }
	
	                    metode = "E-Wallet - " + jenisEwallet;
	                    break;
	                }
	                default:
	                    cout << "Pilihan metode pembayaran tidak valid.\n";
	                    return;
	            }
	
	            stringstream ss;
	            ss << "RDR" << time(0);  // kode unik dengan timestamp
	            string kodeTransaksi = ss.str();
	
	            tampilkanStruk(metode, kodeTransaksi);
	            simpanRiwayatTransaksi(metode, kodeTransaksi);
	            keranjangLayanan.clear();
	
	            cout << "\nTerima kasih telah menggunakan layanan kami!\n";
	            return;
	        }
	
	        case 0:
	            cout << "\nTerima kasih, sampai jumpa kembali!\n";
	            break;
	        default:
	            cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
	    }
	
	} while (pilihan != 0);
}

// Fungsi untuk mendapatkan tanggal sekarang
string LaundrySystem::getTanggalSekarang() {
	time_t now = time(0);
	tm *ltm = localtime(&now);
	
	char buffer[11];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d", ltm);
	return string(buffer);
}

// Fungsi untuk validasi input angka
template<typename T>
T LaundrySystem::inputValidasi(const string& pesan) {
    T nilai;
    while (true) {
        cout << pesan;
        if (cin >> nilai && nilai >= 0) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return nilai;
        } else {
            cout << "Input tidak valid! Masukkan angka positif.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// Fungsi untuk input string dengan validasi
string LaundrySystem::inputString(const string& pesan) {
    string input;
    cout << pesan;
    getline(cin, input);
    while (input.empty()) {
        cout << "Input tidak boleh kosong! " << pesan;
        getline(cin, input);
    }
    return input;
}

// Fungsi untuk menampilkan header aplikasi
void LaundrySystem::tampilkanHeader() {
    cout << "\n" << string(50, '=') << endl;
    cout << "       SISTEM MANAJEMEN LAUNDRY RDR" << endl;
    cout << "          Solusi Terpercaya Untuk" << endl;
    cout << "          Kebutuhan Laundry Anda" << endl;
    cout << string(50, '=') << endl;
}

// Fungsi untuk menampilkan daftar layanan
void LaundrySystem::tampilkanDaftarLayanan() {
    cout << "\n" << string(40, '-') << endl;
    cout << "       DAFTAR LAYANAN LAUNDRY RDR" << endl;
    cout << string(40, '-') << endl;
    cout << "1. Layanan Cuci Umum" << endl;
    cout << "2. Layanan Satuan (Premium)" << endl;
    cout << "3. Layanan Khusus Barang" << endl;
    cout << "4. Layanan Dry Cleaning" << endl;
    cout << "5. Layanan Express" << endl;
    cout << "6. Antar Jemput" << endl;
    cout << "7. Paket Langganan" << endl;
    cout << "8. Lihat Keranjang" << endl;
    cout << "9. Hapus Item dari Keranjang" << endl;
    cout << "10. Checkout & Pembayaran" << endl;
    cout << "0. Keluar" << endl;
    cout << string(40, '-') << endl;
}

// Fungsi untuk menampilkan sub layanan Cuci Umum
void LaundrySystem::tampilkanLayananCuciUmum() {
    cout << "\n--- Detail Layanan Cuci Umum ---" << endl;
    cout << "1. Cuci Kering (Rp 5.000/kg)" << endl;
    cout << "2. Cuci Basah (Rp 4.000/kg)" << endl;
    cout << "3. Cuci Setrika (Rp 7.000/kg)" << endl;
    cout << "4. Setrika Saja (Rp 4.000/kg)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(32, '-') << endl;
}

// Fungsi untuk memproses layanan Cuci Umum
PesananItem LaundrySystem::prosesLayananCuciUmum(int pilihan) {
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
void LaundrySystem::tampilkanLayananSatuanPremium() {
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
PesananItem LaundrySystem::prosesLayananSatuanPremium(int pilihan) {
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
void LaundrySystem::tampilkanLayananKhususBarang() {
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
PesananItem LaundrySystem::prosesLayananKhususBarang(int pilihan) {
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
void LaundrySystem::tampilkanLayananDryCleaning() {
    cout << "\n--- Detail Layanan Dry Cleaning ---" << endl;
    cout << "1. Jas Formal (Rp 60.000/helai)" << endl;
    cout << "2. Gaun Malam (Rp 80.000/helai)" << endl;
    cout << "3. Kebaya (Rp 60.000/helai)" << endl;
    cout << "4. Pakaian Sutera (Rp 100.000/helai)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(36, '-') << endl;
}

// Fungsi untuk memproses layanan Dry Cleaning
PesananItem LaundrySystem::prosesLayananDryCleaning(int pilihan) {
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
void LaundrySystem::tampilkanLayananExpress() {
    cout << "\n--- Detail Layanan Express ---" << endl;
    cout << "1. Same Day Service (Rp 20.000/kg)" << endl;
    cout << "2. Next Day Service (Rp 10.000/kg)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(31, '-') << endl;
}

// Fungsi untuk memproses layanan Express
PesananItem LaundrySystem::prosesLayananExpress(int pilihan) {
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
void LaundrySystem::tampilkanLayananAntarJemput() {
    cout << "\n--- Detail Layanan Antar Jemput ---" << endl;
    cout << "1. Radius < 5 KM (Rp 15.000)" << endl;
    cout << "2. Radius 5-10 KM (Rp 25.000)" << endl;
    cout << "3. Di atas 10 KM (Rp 35.000)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(35, '-') << endl;
}

// Fungsi untuk memproses layanan Antar Jemput
PesananItem LaundrySystem::prosesLayananAntarJemput(int pilihan) {
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
void LaundrySystem::tampilkanLayananPaketLangganan() {
    cout << "\n--- Detail Paket Langganan ---" << endl;
    cout << "1. Paket 20kg/bulan (Rp 150.000)" << endl;
    cout << "2. Paket 40kg/bulan (Rp 280.000)" << endl;
    cout << "3. Paket > 40kg/bulan (Rp 400.000)" << endl;
    cout << "0. Kembali" << endl;
    cout << string(31, '-') << endl;
}

// Fungsi untuk memproses layanan Paket Langganan
PesananItem LaundrySystem::prosesLayananPaketLangganan(int pilihan) {
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

 // Fungsi untuk menampilkan ringkasan item
void LaundrySystem::tampilkanRingkasanItem(const PesananItem& item) {
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

// Fungsi untuk menambah item ke keranjang
void LaundrySystem::tambahKeKeranjang(const PesananItem& item) {
    if (item.namaLayanan != "") {
        keranjangLayanan.push_back(item);
        tampilkanRingkasanItem(item);
        cout << "\nItem berhasil ditambahkan ke keranjang!" << endl;
    }
}

// Fungsi untuk menampilkan keranjang
void LaundrySystem::tampilkanKeranjang() {
    if (keranjangLayanan.empty()) {
        cout << "\nKeranjang kosong!" << endl;
        return;
    }
    
    cout << "\n" << string(50, '=') << endl;
    cout << "                KERANJANG BELANJA" << endl;
    cout << string(50, '=') << endl;
    
    totalBiaya = 0.0;
    for (size_t i = 0; i < keranjangLayanan.size(); ++i) {
        const PesananItem& item = keranjangLayanan[i];
        cout << "\nItem ke-" << (i + 1) << ":" << endl;
        cout << string(30, '-') << endl;
        cout << "Kategori   : " << item.kategoriLayanan << endl;
        cout << "Layanan    : " << item.namaLayanan << endl;
        cout << "Item       : " << item.namaItem << endl;
        cout << "Jumlah     : " << fixed << setprecision(1) << item.beratAtauJumlah 
             << " " << item.unitSatuan << endl;
        cout << "Harga per " << item.unitSatuan << " : Rp " << fixed << setprecision(0) 
             << item.hargaPerUnit << endl;
        cout << "Subtotal   : Rp " << item.subTotalHarga << endl;
        cout << "Estimasi   : " << item.estimasiSelesai << endl;
        
        totalBiaya += item.subTotalHarga;
    }
    
    cout << "\n" << string(50, '=') << endl;
    cout << "TOTAL KESELURUHAN: Rp " << fixed << setprecision(0) << totalBiaya << endl;
    cout << string(50, '=') << endl;
}

// Fungsi untuk menghapus item dari keranjang
void LaundrySystem::hapusItemKeranjang() {
    if (keranjangLayanan.empty()) {
        cout << "\nKeranjang kosong!" << endl;
        return;
    }
    
    tampilkanKeranjang();
    int pilihan = inputValidasi<int>("Pilih nomor item yang ingin dihapus: ");
    
    if (pilihan >= 1 && pilihan <= (int)keranjangLayanan.size()) {
        keranjangLayanan.erase(keranjangLayanan.begin() + pilihan - 1);
        cout << "\nItem berhasil dihapus!" << endl;
    } else {
        cout << "\nNomor item tidak valid!" << endl;
    }
}

void LaundrySystem::checkPromo() {
	ifstream file("promo.txt");
    if (!file.is_open()) {
    	totalSetelahPromo = 0;
        return;
    }
    
    string baris;
    int nomorPromo = 1;
    bool adaPromo = false;
    double diskon;
    string tanggal;
    totalSetelahPromo = totalBiaya;
    
    
    while (getline(file, baris)) {
        if (!baris.empty()) {
            adaPromo = true;
            
            if (nomorPromo == 1) cout << "PROMO!" << endl;
            
            // Parse data promo (format: Nama|Diskon|MasaBerlaku)
            size_t pos1 = baris.find('|');
            size_t pos2 = baris.find('|', pos1 + 1);
            
            tanggal = getTanggalSekarang();
            if (pos1 != string::npos && pos2 != string::npos) {
                string namaPromo = baris.substr(0, pos1);
                stringstream ss(baris.substr(pos1 + 1, pos2 - pos1 - 1));
    			ss >> diskon;
               // diskon = stod(baris.substr(pos1 + 1, pos2 - pos1 - 1));
                string masaBerlaku = baris.substr(pos2 + 1);
                double diskonRP = (diskon / 100) * totalBiaya;
                
                if (tanggal <= masaBerlaku && totalSetelahPromo <= totalBiaya) {
	                cout << nomorPromo << ". " << namaPromo << endl;
	                cout << "   Diskon: " << diskon << "%" << " : Rp " << diskonRP << endl;
	                cout << "   Berlaku sampai: " << masaBerlaku << endl;
	                cout << string(30, '-') << endl;
	                nomorPromo++;
	                totalSetelahPromo -= diskonRP;
				}
            }
        }
    }
    
    
    
    file.close();
    
    if (!adaPromo) {
    	totalSetelahPromo = 0;
        return;
    }
}

// Fungsi untuk menampilkan struk pembayaran
void LaundrySystem::tampilkanStruk(const string& metodePembayaran, const string& kodeTransaksi) {
    cout << "\n" << string(50, '=') << endl;
    cout << "                 STRUK PEMBAYARAN" << endl;
    cout << "                 LAUNDRY RDR" << endl;
    cout << string(50, '=') << endl;
    
    cout << "Kode Transaksi : " << kodeTransaksi << endl;
    cout << "Tanggal        : " << getTanggalSekarang() << endl;
    cout << "Kasir          : Admin" << endl;
    cout << string(50, '-') << endl;
    
    cout << "\nData Pelanggan:" << endl;
    cout << "Nama     : " << user[indeksAktif].username << endl;
    cout << "Telepon  : " << user[indeksAktif].noTelepon << endl;
    cout << "Alamat   : " << user[indeksAktif].alamat << endl;
    cout << string(50, '-') << endl;
    
    cout << "\nDetail Pesanan:" << endl;
    totalBiaya = 0.0;
    for (size_t i = 0; i < keranjangLayanan.size(); ++i) {
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
	cout << endl;
	checkPromo();
	TOTAL = totalBiaya;
	TOTAL -= totalSetelahPromo;
	
	if (totalSetelahPromo != 0) {
    	cout << "\nTOTAL KESELURUHAN SETELAH PROMO: Rp " << fixed << setprecision(0) << TOTAL << endl;
	}
	
    cout << "Metode Pembayaran: " << metodePembayaran << endl;
    cout << string(50, '=') << endl;
    user[indeksAktif].poin += totalBiaya / 100;
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
			else if (potonganPoin < 0 || potonganPoin >= user[indeksAktif].poin) cout <<"Poin anda tidak mencukupi atau tidak valid!" << endl << endl;
			else break;
		}
		cout << "Anda menggunakan " << potonganPoin << " poin." << endl;
		
		user[indeksAktif].poin -= potonganPoin;
		cout << "\nTOTAL KESELURUHAN SEKARANG: Rp " << fixed << setprecision(0) << TOTAL - potonganPoin << endl;
		cout << "Total Poin sekarang: " << user[indeksAktif].poin << endl << endl;
	}
	simpanPengguna(user, jumlahPengguna);
    
}

// Fungsi untuk menyimpan riwayat transaksi ke file.txt
void LaundrySystem::simpanRiwayatTransaksi(const string& metodePembayaran, const string& kodeTransaksi) {
	ofstream file("riwayat_transaksi.txt", ios::app); // mode append
	
	if (!file.is_open()) {
	    cout << "Gagal membuka file untuk menyimpan riwayat transaksi!" << endl;
	    return;
	}
	
	file << "=========================\n";
	file << "Kode Transaksi : " << kodeTransaksi << "\n";
	file << "Tanggal        : " << getTanggalSekarang() <<"\n";
	file << "Nama Pelanggan : " << user[indeksAktif].username << "\n";
	file << "Telepon        : " << user[indeksAktif].noTelepon << "\n";
	file << "Alamat         : " << user[indeksAktif].alamat << "\n";
	file << "Metode Bayar   : " << metodePembayaran << "\n";
	file << "Status         : Diterima" << "\n";
	file << "-------------------------\n";
	
	double total = 0.0;
	for (size_t i = 0; i < keranjangLayanan.size(); ++i) {
		const PesananItem& item = keranjangLayanan[i];
	    file << "- " << item.kategoriLayanan << " | " << item.namaLayanan << " | "
	         << item.namaItem << " | " << fixed << setprecision(1) << item.beratAtauJumlah << " " 
	         << item.unitSatuan << " x Rp" << fixed << setprecision(0) << item.hargaPerUnit 
	         << " = Rp" << item.subTotalHarga << "\n";
	    total += item.subTotalHarga;
	}
		
		if (potonganPoin > 0 || totalSetelahPromo > 0) {
		    file << "SUBTOTAL: Rp" << fixed << setprecision(0) << total << "\n";
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

// ==================================================================================================================================================================
// BLok class Admin:
// Fungsi Untuk menampilkan semua riwayat transaksi customer
void Admin::bacaRiwayatLayanan() {
    ifstream file("riwayat_transaksi.txt");
    if (!file.is_open()) {
        cerr << "Gagal membuka file\n";
        return;
    }
    string baris;
    while (getline(file, baris)) {
        cout << baris << endl;
    }
    file.close();
}

// Fungsi untuk memuat riwayat transaksi
void Admin::loadRiwayatTransaksi() {
    ifstream file("riwayat_transaksi.txt");
    if (!file.is_open()) {
        cerr << "Gagal membuka file\n";
        jumlahData = 0;
        return;
    }
    
    string baris;
    int indeks = 0;
    bool sedangMembacaTransaksi = false;
    string detailLengkap = "";
    
    while (getline(file, baris) && indeks < MAKSIMAL_RIWAYAT) {
        // Tambahkan ke detail lengkap
        if (sedangMembacaTransaksi) {
            detailLengkap += baris + "\n";
        }
        
        if (baris.find("Kode Transaksi : ") == 0) {
            riwayat[indeks].kode = baris.substr(17); // Ambil setelah "Kode Transaksi : "
            sedangMembacaTransaksi = true;
            detailLengkap = baris + "\n";
        } else if (baris.find("Tanggal        : ") == 0) {
            string stringTanggal = baris.substr(17); // Ambil setelah "Tanggal        : "
            stringstream ss(stringTanggal);
            string hari, bulan, tanggal, waktu, tahun;
            ss >> hari >> bulan >> tanggal >> waktu >> tahun;
            riwayat[indeks].tanggal = tanggal;
            riwayat[indeks].bulan = bulan;
            riwayat[indeks].tahun = tahun;
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

// Fungsi untuk menampilkan semua akun admin
void Admin::lihatUserAdmin() {
    ifstream file("users.txt");
    if (!file.is_open()) {
        cerr << "Gagal membuka file users.txt\n";
        return;
    }
    
     cout << "\n" << string(40, '-') << endl;
    cout << left << setw(10) << "" << "DAFTAR AKUN ADMIN";
    cout << "\n" << string(40, '-') << endl;
    
    string baris;
    int jumlahAdmin = 0;
    string usernameSekarang = "";
    bool adalahAdmin = false;
    bool sudahAdaUsername = false;
    
    while(getline(file, baris)) {
        // Lewati baris kosong
        if (baris.empty()) continue;
        
        // Lewati baris pemisah, tapi proses data yang sudah dikumpulkan terlebih dahulu
        if (baris == "=========================") {
            if (adalahAdmin && sudahAdaUsername && !usernameSekarang.empty()) {
                jumlahAdmin++;
                cout << jumlahAdmin << ". " << usernameSekarang << endl;
            }
            // Reset untuk user berikutnya
            usernameSekarang = "";
            adalahAdmin = false;
            sudahAdaUsername = false;
            continue;
        }
        
        // Ambil username terlebih dahulu
        if (baris.find("Username   : ") != string::npos) {
            usernameSekarang = baris.substr(13); // Ambil setelah "Username   : "
            sudahAdaUsername = true;
        }
        
        // Cek apakah user saat ini adalah admin
        if (baris.find("Role       : admin") != string::npos) {
            adalahAdmin = true;
        }
    }
    
    // Tangani user terakhir (jika file tidak diakhiri dengan pemisah)
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

// Fungsi untuk menampilkan semua akun customer
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
    vector<string> dataUser;
    bool adalahCustomer = false;
    
    while(getline(file, baris)) {
        // Lewati baris kosong
        if (baris.empty()) continue;
        
        // Cek pemisah - akhir dari data user
        if (baris == "=========================") {
            // Jika user saat ini adalah customer, tampilkan semua data 
            if (adalahCustomer) {
                cout << "=========================" << endl;
                for (vector<string>::const_iterator it = dataUser.begin(); it != dataUser.end(); ++it) {
                    // Lewati baris password
                    if (it->find("Password   : ") == string::npos) {
                        cout << *it << endl;
                    }
                }
                cout << "=========================" << endl;
                jumlahCustomer++;
            }
            
            // Reset untuk user berikutnya
            dataUser.clear();
            adalahCustomer = false;
            continue;
        }
        
        // Kumpulkan data user
        dataUser.push_back(baris);
        
        // Cek apakah user saat ini adalah customer
        if (baris.find("Role       : customer") != string::npos) {
            adalahCustomer = true;
        }
    }
    
    // Tangani user terakhir jika file tidak diakhiri dengan pemisah
    if (adalahCustomer && !dataUser.empty()) {
        cout << "=========================" << endl;
        for (vector<string>::const_iterator it = dataUser.begin(); it != dataUser.end(); ++it) {
            // Lewati baris password
            if (it->find("Password   : ") == string::npos) {
                cout << *it << endl;
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

// Fungsi untuk menampilkan menu data user
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
            case 1:
                lihatUserAdmin();
                break;
            case 2:
                lihatUserPengguna();
                break;
            case 0:
                return;
            default:
                cout << "Pilihan tidak valid!" << endl;
                continue;
        }
    }
}

// Fungsi untuk menampilkan hasil pencarian riwayat berdasarkan keywoard
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

// Funsgi untuk mencari riwayat berdasarkan tanggal
void Admin::cariByTanggal() {
    loadRiwayatTransaksi();
    bool ditemukan[MAKSIMAL_RIWAYAT];
    
    for (int i = 0; i < MAKSIMAL_RIWAYAT; i++) {
        ditemukan[i] = false;
    }
    
    int inputTanggal, inputBulan, inputTahun;
    
    cout << "=== PENCARIAN BERDASARKAN TANGGAL ===" << endl;
    
    // Validasi input tanggal
    do {
        cout << "Masukkan tanggal (1-31): ";
        cin >> inputTanggal;
        
        if (inputTanggal < 1 || inputTanggal > 31) {
            cout << "Input tidak valid! Masukkan angka 1-31." << endl;
        }
    } while (inputTanggal < 1 || inputTanggal > 31);
    
    // Validasi input bulan
    do {
        cout << "Masukkan bulan (1-12): ";
        cin >> inputBulan;
        
        if (inputBulan < 1 || inputBulan > 12) {
            cout << "Input tidak valid! Masukkan angka 1-12." << endl;
        }
    } while (inputBulan < 1 || inputBulan > 12);
    
    cout << "Masukkan tahun (contoh: 2025): ";
    cin >> inputTahun;
    
    // Format tanggal yang dicari menjadi YYYY-MM-DD
    stringstream ss;
    ss << inputTahun << "-";
    if (inputBulan < 10) ss << "0";
    ss << inputBulan << "-";
    if (inputTanggal < 10) ss << "0";
    ss << inputTanggal;
    string tanggalDicari = ss.str();
    
    // Cari dalam riwayat
    for (int i = 0; i < jumlahData; i++) {
        // Ambil tanggal dari detail transaksi
        string detailTransaksi = riwayat[i].detailTransaksi;
        size_t posTanggal = detailTransaksi.find("Tanggal        : ");
        if (posTanggal != string::npos) {
            size_t posAwal = posTanggal + 17; // Setelah "Tanggal        : "
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

// Fungsi untuk mencari riwayat berdasarkan nama customer
void Admin::cariByNama() {
    loadRiwayatTransaksi();
    bool ditemukan[MAKSIMAL_RIWAYAT];
    
    // Inisialisasi array ditemukan
    for (int i = 0; i < MAKSIMAL_RIWAYAT; i++) {
        ditemukan[i] = false;
    }
    
    string nama;
    cout << "Masukkan nama pelanggan: ";
    cin.ignore(); // Bersihkan buffer input
    getline(cin, nama);
    
    // Konversi input ke huruf kecil untuk pencarian case-insensitive
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

// Fungsi untuk mencari riwayat berdasarkan kode transaksi
void Admin::cariByKodeTransaksi() {
    loadRiwayatTransaksi();
    bool ditemukan[MAKSIMAL_RIWAYAT];
    
    // Inisialisasi array ditemukan
    for (int i = 0; i < MAKSIMAL_RIWAYAT; i++) {
        ditemukan[i] = false;
    }
    
    string kode;
    cout << "Masukkan kode transaksi (atau sebagian): ";
    cin >> kode;
    
    // Konversi input ke huruf besar untuk pencarian case-insensitive
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

// Fungsi untuk mencari riwayat berdasarkan status
void Admin::cariByStatus() {
    loadRiwayatTransaksi();
    bool ditemukan[MAKSIMAL_RIWAYAT];
    
    // Inisialisasi array ditemukan
    for (int i = 0; i < MAKSIMAL_RIWAYAT; i++) {
        ditemukan[i] = false;
    }
    
    cout << "\n=== PENCARIAN BERDASARKAN STATUS ===" << endl;
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
            // Cari transaksi dengan status "Selesai"
            for (int i = 0; i < jumlahData; i++) {
                if (riwayat[i].status == "Selesai") {
                    ditemukan[i] = true;
                }
            }
            kriteria = "dengan status Selesai";
            break;
        case 2:
            // Cari transaksi dengan status selain "Selesai"
            for (int i = 0; i < jumlahData; i++) {
                if (riwayat[i].status != "Selesai") {
                    ditemukan[i] = true;
                }
            }
            kriteria = "dengan status Belum Selesai";
            break;
        case 0:
            return;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
    }
    
    tampilkanHasilPencarian(ditemukan, kriteria);
}

// Fungsi untuk menampilkan menu cari riwayat
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
            case 1:
                cariByTanggal();
                break;
            case 2:
                cariByNama();
                break;
            case 3:
                cariByKodeTransaksi();
                break;
            case 4:
                cariByStatus();
                break;
            case 0:
                return;
            default:
                cout << "Pilihan tidak valid!" << endl;
                continue;
        }
    }
}

// Fungsi baru untuk memperbarui status laundry
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
    
    // Konversi ke huruf besar untuk pencarian case-insensitive
    transform(kodeTransaksi.begin(), kodeTransaksi.end(), kodeTransaksi.begin(), (int(*)(int))toupper);
    
    int indeksDitemukan = -1;
    
    // Cari transaksi berdasarkan kode
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
    
    // Tampilkan data transaksi yang ditemukan
    cout << "\nData transaksi ditemukan:" << endl;
    cout << "Kode Transaksi: " << riwayat[indeksDitemukan].kode << endl;
    cout << "Nama Pelanggan: " << riwayat[indeksDitemukan].nama << endl;
    cout << "Status Saat Ini: " << riwayat[indeksDitemukan].status << endl;
    
    // Pilihan status baru
    cout << "\nPilih status baru:" << endl;
    cout << "1. Pending" << endl;
    cout << "2. Dalam Proses" << endl;
    cout << "3. Selesai" << endl;
    cout << "4. Dibatalkan" << endl;
    cout << "0. Batal Update" << endl;
    
    int pilihanStatus;
    cout << "Pilihan: ";
    cin >> pilihanStatus;
    
    string statusBaru;
    switch(pilihanStatus) {
        case 1:
            statusBaru = "Pending";
            break;
        case 2:
            statusBaru = "Dalam Proses";
            break;
        case 3:
            statusBaru = "Selesai";
            break;
        case 4:
            statusBaru = "Dibatalkan";
            break;
        case 0:
            cout << "Update status dibatalkan." << endl;
            return;
        default:
            cout << "Pilihan tidak valid!" << endl;
            return;
    }
    
    // Konfirmasi perubahan
    cout << "\nApakah Anda yakin ingin mengubah status dari '" 
         << riwayat[indeksDitemukan].status << "' menjadi '" << statusBaru << "'? (y/n): ";
    char konfirmasi;
    cin >> konfirmasi;
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Update status di array
        riwayat[indeksDitemukan].status = statusBaru;
        
        // Update detail transaksi
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
        
        // Simpan perubahan ke file
        simpanRiwayatKeFile();
        
        cout << "Status berhasil diperbarui menjadi: " << statusBaru << endl;
    } else {
        cout << "Update status dibatalkan." << endl;
    }
}

// Fungsi untuk menyimpan riwayat kembali ke file
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

// Fungsi untuk membuat promo baru
void Admin::buatPromo() {
    string namaPromo, masaBerlaku;
    float diskon;
    
    cout << "\n=== BUAT PROMO BARU ===" << endl;
    
    cout << "Masukkan nama promo: ";
    cin.ignore(); 
    getline(cin, namaPromo);
    
    // Validasi input diskon
    do {
        cout << "Masukkan besaran diskon (0.1-100%): ";
        cin >> diskon;
        
        if (diskon < 0.1 || diskon > 100) {
            cout << "Input tidak valid! Masukkan angka 1-100." << endl;
        }
    } while (diskon < 0.1 || diskon > 100);
    
    // Input masa berlaku dengan validasi format
    do {
        cout << "Masukkan masa berlaku (yyyy-mm-dd): ";
        cin >> masaBerlaku;
        
        // Validasi format sederhana (panjang dan karakter '-')
        if (masaBerlaku.length() != 10 || masaBerlaku[4] != '-' || masaBerlaku[7] != '-') {
            cout << "Format tidak valid! Gunakan format yyyy-mm-dd (contoh: 2025-12-31)" << endl;
        } else {
            // Validasi angka pada posisi yang tepat
            bool formatValid = true;
            for (int i = 0; i < 10; i++) {
                if (i == 4 || i == 7) continue; // Skip karakter '-'
                if (!isdigit(masaBerlaku[i])) {
                    formatValid = false;
                    break;
                }
            }
            
            if (!formatValid) {
                cout << "Format tidak valid! Gunakan format yyyy-mm-dd dengan angka yang benar" << endl;
            } else {
                // Validasi bulan dan tanggal
                string bulanStr = masaBerlaku.substr(5, 2);
                string tanggalStr = masaBerlaku.substr(8, 2);
                int bulan = atoi(bulanStr.c_str());
                int tanggal = atoi(tanggalStr.c_str());
                
                if (bulan < 1 || bulan > 12 || tanggal < 1 || tanggal > 31) {
                    cout << "Tanggal atau bulan tidak valid!" << endl;
                } else {
                    break; // Format valid, keluar dari loop
                }
            }
        }
    } while (true);
    
    // Konfirmasi sebelum menyimpan
    cout << "\n=== KONFIRMASI PROMO ===" << endl;
    cout << "Nama Promo   : " << namaPromo << endl;
    cout << "Diskon       : " << diskon << "%" << endl;
    cout << "Masa Berlaku : " << masaBerlaku << endl;
    cout << "\nApakah data promo sudah benar? (y/n): ";
    
    char konfirmasi;
    cin >> konfirmasi;
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Simpan ke file promo.txt
        ofstream file("promo.txt", ios::app); // Mode append untuk menambah data
        if (!file.is_open()) {
            cout << "Gagal membuka file promo.txt!" << endl;
            return;
        }
        
        // Format penyimpanan: Nama|Diskon|MasaBerlaku
        file << namaPromo << "|" << diskon << "|" << masaBerlaku << endl;
        file.close();
        
        cout << "Promo berhasil dibuat dan disimpan!" << endl;
    } else {
        cout << "Pembuatan promo dibatalkan." << endl;
    }
}

// Fungsi untuk melihat semua promo yang ada
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
            
            // Parse data promo (format: Nama|Diskon|MasaBerlaku)
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

// Fungsi untuk menghapus promo tertentu
void Admin::hapusPromo() {
    ifstream fileInput("promo.txt");
    if (!fileInput.is_open()) {
        cout << "Tidak ada file promo atau gagal membuka file!" << endl;
        return;
    }
    
    // Baca semua promo ke dalam vector
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
    
    // Tampilkan daftar promo
    cout << "\n" << string(50, '=') << endl;
    cout << left << setw(15) << "" << "HAPUS PROMO";
    cout << "\n" << string(50, '=') << endl;
    
    for (size_t i = 0; i < daftarPromo.size(); i++) {
        // Parse data promo (format: Nama|Diskon|MasaBerlaku)
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
    
    // Tampilkan promo yang akan dihapus untuk konfirmasi
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
            // Hapus promo dari vector
            daftarPromo.erase(daftarPromo.begin() + indeksHapus);
            
            // Tulis ulang file dengan data yang tersisa
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

// Fungsi menu promo
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
            case 1:
                buatPromo();
                break;
            case 2:
                lihatPromo();
                break;
            case 3:
                hapusPromo();
                break;
            case 0:
                return;
            default:
                cout << "Pilihan tidak valid!" << endl;
                continue;
        }
    }
}

// Fungsi untuk menampilkan menu admin
void Admin::menuAdmin() {
    while (true) {
        cout << "\n" << string(40, '-') << endl;
	    cout << left << setw(13) << "" << "MENU ADMIN";
	    cout << "\n" << string(40, '-') << endl;
    
        cout << "1. Pengaturan Akun" << endl;
        cout << "2. Lihat Semua Riwayat Transaksi" << endl;
        cout << "3. Lihat Data Users" << endl;
        cout << "4. Cari riwayat" << endl;
        cout << "5. Update Status Transaksi" << endl;
        cout << "6. Pendapatan perbulan" << endl;
        cout << "7. Lihat Ulasan" << endl;
        cout << "8. Kelola Promo" << endl;
        cout << "0. Logout" << endl << endl;
        
        int pilihan;
        cout << "Pilihan: "; 
        cin >> pilihan;
        
        if (pilihan == 1) {
        	LaundrySystem temp;
            temp.pengaturanAkun(user[indeksAktif], user, jumlahPengguna);
        	temp.simpanPengguna(user, jumlahPengguna);
        } else if (pilihan == 2) {
            cout << "\n" << string(40, '-') << endl;
		    cout << left << setw(10) << "" << "RIWAYAT TRANSAKSI";
		    cout << "\n" << string(40, '-') << endl;
            bacaRiwayatLayanan();
        } else if (pilihan == 3) {
            dataUser();
        } else if (pilihan == 4) {
            menuCariRiwayat();
        } else if (pilihan == 5) {
            updateStatus();
        } else if (pilihan == 6) {
            hitungPendapatanBulanan();
        } else if (pilihan == 7) {
            cout << "\n" << string(40, '-') << endl;
		    cout << left << setw(10) << "" << "ULASAN CUSTOMER";
		    cout << "\n" << string(40, '-') << endl;
            ulasanRating();
        } else if (pilihan == 8) {
            menuPromo();
		} else if (pilihan == 0) {
            cout << "Logout berhasil. Terima kasih!" << endl;
            break;
        } else {
            cout << "Input tidak valid!" << endl;
            continue;
        }
    }
}

// Fungsi untuk melihat rating dan ulasan
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

// Fungsi untuk menghitung pendapatan per bulan
void Admin::hitungPendapatanBulanan() {
    loadRiwayatTransaksi();
    
    if (jumlahData == 0) {
        cout << "Tidak ada data transaksi yang tersedia." << endl;
        return;
    }
    
    int bulanInput, tahunInput;
    
    cout << "\n=== HITUNG PENDAPATAN BULANAN ===" << endl;
    
    // Validasi input bulan
    do {
        cout << "Masukkan bulan (1-12): ";
        cin >> bulanInput;
        
        if (bulanInput < 1 || bulanInput > 12) {
            cout << "Input tidak valid! Masukkan angka 1-12." << endl;
        }
    } while (bulanInput < 1 || bulanInput > 12);
    
    cout << "Masukkan tahun (contoh: 2025): ";
    cin >> tahunInput;
    
    // Array nama bulan untuk tampilan
    string namaBulan[] = {"Januari", "Februari", "Maret", "April", "Mei", "Juni",
                         "Juli", "Agustus", "September", "Oktober", "November", "Desember"};
    
    int totalPendapatan = 0;
    int jumlahTransaksiSelesai = 0;
    
    // Loop melalui semua data riwayat
    for (int i = 0; i < jumlahData; i++) {
        // Cek apakah status transaksi adalah "Selesai"
        if (riwayat[i].status == "Selesai") {
            // Ambil tanggal dari detail transaksi untuk mendapatkan bulan dan tahun
            string detailTransaksi = riwayat[i].detailTransaksi;
            size_t posTanggal = detailTransaksi.find("Tanggal        : ");
            
            if (posTanggal != string::npos) {
                size_t posAwal = posTanggal + 17; // Setelah "Tanggal        : "
                size_t posAkhir = detailTransaksi.find("\n", posAwal);
                
                if (posAkhir != string::npos) {
                    string tanggalRiwayat = detailTransaksi.substr(posAwal, posAkhir - posAwal);
                    
                    // Parse tanggal format YYYY-MM-DD
                    if (tanggalRiwayat.length() >= 10) {
                        string tahunStr = tanggalRiwayat.substr(0, 4);
                        string bulanStr = tanggalRiwayat.substr(5, 2);
                        
                        int tahunRiwayat = atoi(tahunStr.c_str());
                        int bulanRiwayat = atoi(bulanStr.c_str());
                        
                        // Cek apakah bulan dan tahun sesuai dengan input
                        if (bulanRiwayat == bulanInput && tahunRiwayat == tahunInput) {
                            // Ambil total dari detail transaksi dengan cara yang lebih sederhana
                            // Cari baris yang mengandung "TOTAL: Rp" terakhir dalam transaksi
                            size_t posTotalAkhir = detailTransaksi.rfind("TOTAL: Rp");
                            
                            if (posTotalAkhir != string::npos) {
                                size_t posAwalTotal = posTotalAkhir + 9; // Setelah "TOTAL: Rp"
                                size_t posAkhirTotal = detailTransaksi.find("\n", posAwalTotal);
                                if (posAkhirTotal == string::npos) {
                                    // Jika tidak ada newline, cari sampai akhir string atau karakter '='
                                    posAkhirTotal = detailTransaksi.find("=", posAwalTotal);
                                    if (posAkhirTotal == string::npos) {
                                        posAkhirTotal = detailTransaksi.length();
                                    }
                                }
                                
                                if (posAkhirTotal > posAwalTotal) {
                                    string totalStr = detailTransaksi.substr(posAwalTotal, posAkhirTotal - posAwalTotal);
                                    // Hapus spasi di awal dan akhir
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
    
    // Tampilkan hasil
    cout << "\n" << string(40, '=') << endl;
    cout << "LAPORAN PENDAPATAN BULANAN" << endl;
    cout << string(40, '=') << endl;
    cout << "Bulan/Tahun    : " << namaBulan[bulanInput-1] << " " << tahunInput << endl;
    cout << "Jumlah Transaksi Selesai: " << jumlahTransaksiSelesai << endl;
    cout << "Pendapatan bulan ini: Rp" << totalPendapatan << endl;
    cout << string(40, '=') << endl;
    
    if (jumlahTransaksiSelesai == 0) {
        cout << "Tidak ada transaksi yang selesai pada bulan tersebut." << endl;
    }
}


int main() {
	LaundrySystem sistem;
	
	sistem.tampilkanHeader();
	sistem.prosesMenuUtama();
    return 0;
}
