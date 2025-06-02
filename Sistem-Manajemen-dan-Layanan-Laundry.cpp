#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <limits>
using namespace std;

struct User {
    string username;
    string password;
    string role; // Admin atau Customer
    int poin; // poin hanya untuk customer, default 0 (diset di fungsi)
};

// Fungsi untuk memuat data pengguna dari file.txt
vector<User> pengguna() {
    vector<User> daftarPengguna;
    ifstream file("users.txt");
    User user;
    while(file>>user.username>>user.password>>user.role) {
        if(user.role == "customer") {
            file>>user.poin;
        } else {
            user.poin = 0;
        }
        daftarPengguna.push_back(user);
    }
    file.close();
    return daftarPengguna;
}

// Simpan data pengguna ke file
void simpanPengguna(const vector<User>& daftarPengguna) {
    ofstream file("users.txt");
    for(size_t i=0;i<daftarPengguna.size();++i) {
        file<<daftarPengguna[i].username<<" "<<daftarPengguna[i].password<<" "<<daftarPengguna[i].role<<" "<<daftarPengguna[i].poin<<endl;
    }
    file.close();
}

// Cek login
int login(const vector<User>& daftarPengguna, string& role) {
    string username,password;
    cout<<"=== Login ==="<<endl;
    cout<<"Username: ";
    cin>>username;
    cout<<"Password: ";
    cin>>password;

    for(size_t i=0;i<daftarPengguna.size();++i) {
        if(daftarPengguna[i].username == username && daftarPengguna[i].password == password) {
            role = daftarPengguna[i].role;
            return i;
        }
    }
    cout<<"Login gagal. Username atau password salah.\n";
    return -1;
}

// Registrasi
void registrasiPengguna(vector<User>& daftarPengguna) {
    User penggunaBaru;
    cout<<"=== Registrasi ==="<<endl;
    cout<<"Username: ";
    cin>>penggunaBaru.username;
    cout<<"Password: ";
    cin>>penggunaBaru.password;

    // Pilih role
    cout<<"Role (admin/customer): ";
    cin>>penggunaBaru.role;
    if(penggunaBaru.role != "admin" && penggunaBaru.role != "customer") {
        cout<<"Role tidak valid. Gunakan 'admin' atau 'customer'.\n";
        return;
    }

    // Cek duplikasi username
    for(size_t i=0;i<daftarPengguna.size();++i) {
        if(daftarPengguna[i].username == penggunaBaru.username) {
            cout<<"Username sudah terdaftar.\n";
            return;
        }
    }

    // Inisialisasi poin
    penggunaBaru.poin = 0;

    daftarPengguna.push_back(penggunaBaru);
    simpanPengguna(daftarPengguna);
    cout<<"Registrasi berhasil!\n";
}

// Edit akun
void pengaturanAkun(User& user, const vector<User>& daftarPengguna) {
    int pilihan;
    string passwordVerifikasi;

    while(true) {
        cout<<"\n=== Pengaturan Akun ==="<<endl;
        cout<<"1. Ubah Username\n2. Ubah Password\n3. Lihat Username & Password\n0. Kembali\n";
		cout<<"Pilih: ";
        cin>>pilihan;

        if(pilihan == 1) {
            cout<<"Masukkan password saat ini untuk verifikasi: ";
            cin>>passwordVerifikasi;
            if(passwordVerifikasi == user.password) {
                string usernameBaru;
                cout<<"Username baru: ";
                cin>>usernameBaru;

                // Cek apakah username baru sudah digunakan user lain
                bool usernameSudahAda = false;
                for(size_t i=0;i<daftarPengguna.size();++i) {
                    if(daftarPengguna[i].username == usernameBaru && &daftarPengguna[i] != &user) {
                        usernameSudahAda = true;
                        break;
                    }
                }

                if(usernameSudahAda) {
                    cout<<"Username sudah digunakan oleh pengguna lain. Silakan pilih yang lain.\n";
                } else {
                    user.username = usernameBaru;
                    cout<<"Username berhasil diperbarui.\n";
                }
            } else {
                cout<<"Password salah. Tidak dapat mengubah username.\n";
            }
        } else if(pilihan == 2) {
            cout<<"Masukkan password saat ini untuk verifikasi: ";
            cin>>passwordVerifikasi;
            if(passwordVerifikasi == user.password) {
                cout<<"Password baru: ";
                cin>>user.password;
                cout<<"Password berhasil diperbarui.\n";
            } else {
                cout<<"Password salah. Tidak dapat mengubah password.\n";
            }
        } else if(pilihan == 3) {
            cout<<"Username: "<<user.username<<"\nPassword: "<<user.password<<endl;
        } else if(pilihan == 0) {
            break;
        } else {
            cout<<"Pilihan tidak valid.\n";
        }
    }
}

//========================================================================================================================================================

//Struktur untuk menyimpan item layanan yang dipesan
struct pesananItem {
	string namaLayanan;
	string namaItem;
	double beratAtauJumlah;
	double hargaPerUnit;
	double subTotalHarga;
	string estimasiSelesai;
};

//Daftar Layanan Laundry
void DaftarLayanan_Laundry(){
	cout<<"\n--- Daftar Layanan Laundry RDR ---" <<endl;
	cout<<"1. Cuci Kiloan" <<endl;
	cout<<"2. Satuan (Pakaian Khusus)" <<endl;
	cout<<"3. Setrika Saja" <<endl;
	cout<<"4. Dry Clean" <<endl;
	cout<<"5. Express Service" <<endl;
	cout<<"----------------------------------" <<endl;
}

//fungsi untuk memproses input detail item pesanan
pesananItem prosesInputLayanan(int pilihanLayanan) {
	pesananItem itemPesanan;
	itemPesanan.subTotalHarga = 0.0;
	
	cout<<"\n--- Informasi Detail Layanan ---" <<endl;

	//Deklarasi harga dasar per unti (akan disesuaikan di switch)
	double hargaDasar = 0.0;
	string estimasi;
	bool cuciKg = false;
	bool satuan = false;
	bool setrika = false;
	bool express = false;
	
	switch (pilihanLayanan) {
		case 1:
			itemPesanan.namaLayanan = "Cuci Kiloan";
			hargaDasar = 7000.0; //perKg
			estimasi = "2 hari";
			cuciKg = true;
			break;
		case 2:
			itemPesanan.namaLayanan = "Satuan (Pakaian Khusus)";
			hargaDasar = 15000.0; //perKg
			estimasi = "3-4 hari";
			satuan = true;
			break;
		case 3:
			itemPesanan.namaLayanan = "Setrika Saja";
			hargaDasar = 5000.0; //perKg
			estimasi = "1 hari";
			setrika = true;
			break;
		case 4:
			itemPesanan.namaLayanan = "Dry Clean";
			hargaDasar = 25000.0; //perKg
			estimasi = "4-5 hari";
			satuan = true;
			break;
		case 5:
			itemPesanan.namaLayanan = "Ekspress Service";
			hargaDasar = 10000.0; //perKg
			estimasi = "1 hari";
			express = true;
			break;
		default:
			cout<<"Pilihan layanan tidak valid" <<endl;
			return itemPesanan;
	}
	cout<<"--------------------------------" <<endl <<endl;
	
	itemPesanan.hargaPerUnit = hargaDasar;
	itemPesanan.estimasiSelesai = estimasi;
	
	cout<<"Layanan Terpilih " <<itemPesanan.namaLayanan <<endl;
	if (cuciKg || setrika){
		cout<<"Masukkan jenis item (Baju/Celana/Campur): ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin, itemPesanan.namaItem);
		
		cout<<"Masukkan total berat (Kg): ";
		while(!(cin>>itemPesanan.beratAtauJumlah) || itemPesanan.beratAtauJumlah <=0){
			cout<<"Input tidak valid, Masukkan jumlah berat dalam angka positif (Kg): ";
			cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		itemPesanan.subTotalHarga = itemPesanan.beratAtauJumlah * itemPesanan.hargaPerUnit;
	}
	else if (satuan){
		cout<<"Masukkan jenis item (contoh: Jas/Selimut/Gaun): ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, itemPesanan.namaItem);
        
        cout<<"Masukkan jumlah item (potong): ";
        while (!(cin >> itemPesanan.beratAtauJumlah) || itemPesanan.beratAtauJumlah <= 0) {
        	cout << "Input tidak valid. Harap masukkan jumlah dalam angka positif (potong): ";
        	cin.clear();
        	cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	}
    	itemPesanan.subTotalHarga = itemPesanan.beratAtauJumlah * itemPesanan.hargaPerUnit;
	}
	else if (express){
		cout<<"Masukkan jenis item (contoh: Baju/Celana/Campur): ";
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, itemPesanan.namaItem);
        
        cout<<"Masukkan total berat (Kg): ";
		while(!(cin>>itemPesanan.beratAtauJumlah) || itemPesanan.beratAtauJumlah <=0){
			cout<<"Input tidak valid, Masukkan jumlah berat dalam angka positif (Kg): ";
			cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		itemPesanan.subTotalHarga = itemPesanan.beratAtauJumlah * itemPesanan.hargaPerUnit;
	}
	
	//Menampilkan harga dalam tanpa desimal
	cout<<fixed <<setprecision(0);
	cout<<"--------------------------------" <<endl;
	cout<<"Ringkasan item saat ini" <<endl;
	cout<<"Layanan : " <<itemPesanan.namaLayanan <<endl;
	cout<<"Item    : " <<itemPesanan.namaItem <<endl;
	
	if (cuciKg || setrika){
		cout<<"Berat  : " <<itemPesanan.beratAtauJumlah <<" Kg" <<endl;
	}
	else if (satuan){
		cout<<"Jumlah  : " <<itemPesanan.beratAtauJumlah <<" potong" <<endl;
	}
	else if (express){
		cout<<"Berat/jumlah: " <<itemPesanan.beratAtauJumlah <<" Kg/potong" <<endl;
	}
	cout<<"\nHarga per unit : Rp " << itemPesanan.hargaPerUnit <<endl;
    cout<<"Subtotal       : Rp " << itemPesanan.subTotalHarga <<endl;
    
	cout<<"\nEstimasi selesai: " <<itemPesanan.estimasiSelesai <<endl;
	cout<<"--------------------------------" <<endl;
	
	return itemPesanan;
}

//Menampilkan seluruh daftar layanan yang telah dipilih
void tampilkanLayananTerpilih(const vector<pesananItem>& layananTerpilih){
	if (layananTerpilih.empty()){
		cout<<"\nAnda tidak memilih layanan apapun" <<endl;
		return;
	}
	cout<<"Layanan yang anda pilih" <<endl;
	double totalKeseluruhan = 0.0;
	cout<<fixed <<setprecision(0);
	
	for (size_t i = 0; i < layananTerpilih.size(); ++i){
		const pesananItem& item = layananTerpilih[i];
		cout<<"--------------------------------" <<endl;
		cout<<"Pesanan ke-" <<(i+1) <<" : " <<endl;
		cout<<"Layanan : " <<item.namaLayanan <<endl;
		cout<<"Item    : " <<item.namaItem <<endl;
		
		if (item.namaLayanan == "Cuci Kiloan" || item.namaLayanan == "Setrika Saja"){
			cout<<"Berat: " <<item.beratAtauJumlah <<" Kg" <<endl;
		}
		else if (item.namaLayanan == "Satuan(Pakaian Khusus)" || item.namaLayanan == "Dry Clean"){
			cout<<"Jumlah: " <<item.beratAtauJumlah <<" potong" <<endl;
		}
		else if(item.namaLayanan == "express"){
			cout<<"Berat/jumlah: " <<item.beratAtauJumlah <<" Kg/potong" <<endl;
		}
		cout<<"\nHarga per unit : Rp " << item.hargaPerUnit <<endl;
        cout<<"Subtotal       : Rp " << item.subTotalHarga <<endl;
    	totalKeseluruhan += item.subTotalHarga;
    	
    	cout<<"\nEstimasi Selesai: " <<item.estimasiSelesai <<endl;
	}
	cout<<"--------------------------------" <<endl;
	cout<<"\nTotal Keseluruhan: " <<totalKeseluruhan <<endl;
	cout<<"--------------------------------" <<endl<<endl;
}

//============================================================================================================================================

struct Ulasan {
    string komentar;
    int rating;
};

// struk transaksi disimpan di struk.txt
void simpanLayananTerpilih(const vector<pesananItem>& layananTerpilih, string namaCustomer){
	ofstream struk;
	struk.open("struk.txt", ios::app);
	if (layananTerpilih.empty()){
		cout<<"\nAnda tidak memilih layanan apapun" <<endl;
		return;
	}
	struk<<"Nama Customer: "<<namaCustomer<<endl;
	double totalKeseluruhan = 0.0;
	struk<<fixed<<setprecision(0);
	
	for (size_t i = 0; i < layananTerpilih.size(); ++i){
		const pesananItem& item = layananTerpilih[i];
		struk<<"--------------------------------" <<endl;
		struk<<"Pesanan ke-" <<(i+1) <<" : " <<endl;
		struk<<"Layanan : " <<item.namaLayanan <<endl;
		struk<<"Item    : " <<item.namaItem <<endl;
		
		if (item.namaLayanan == "Cuci Kiloan" || item.namaLayanan == "Setrika Saja"){
			cout<<"Berat: " <<item.beratAtauJumlah <<" Kg" <<endl;
		}
		else if (item.namaLayanan == "Satuan(Pakaian Khusus)" || item.namaLayanan == "Dry Clean"){
			struk<<"Jumlah: " <<item.beratAtauJumlah <<" potong" <<endl;
		}
		else if(item.namaLayanan == "express"){
			struk<<"Berat/jumlah: " <<item.beratAtauJumlah <<" Kg/potong" <<endl;
		}
		struk<<"\nHarga per unit : Rp " << item.hargaPerUnit <<endl;
        struk<<"Subtotal       : Rp " << item.subTotalHarga <<endl;
    	totalKeseluruhan += item.subTotalHarga;
    	
    	struk<<"\nEstimasi Selesai: " <<item.estimasiSelesai <<endl;
	}
	struk<<"--------------------------------" <<endl;
	struk<<"\nTotal Keseluruhan: " <<totalKeseluruhan <<endl;
	struk<<"--------------------------------" <<endl;
	struk.close();
}

int main() {
    vector<User> daftarPengguna = pengguna();
    int pilihan;
    string role;
    int indeksPenggunaAktif = -1;

    while(true) {
        cout<<"\n--- Menu Utama ---\n";
        cout<<"1. Login\n2. Registrasi\n0. Keluar\n";
		cout<<"Pilih: ";
        cin>>pilihan;

        if(pilihan == 1) {
            indeksPenggunaAktif = login(daftarPengguna, role);
            if(indeksPenggunaAktif != -1) {
                cout<<"Login berhasil sebagai "<<role<<".\n";
                // Menu setelah login
                int subPilihan;
                while(true) {
                    cout<<"\n--- Menu "<<role<<" ---\n";
                    if(role == "customer") {
                        cout<<"1. Akun\n";
                        cout<<"2. Lihat Poin\n";
                    	cout<<"3. Lihat Layanan Laundry\n";
                        cout<<"0. Logout\n";
                    } else if(role == "admin") {
                        cout<<"1. Pengaturan Akun\n";
                        cout<<"0. Logout\n";
                    }	
                    cout<<"Pilih: ";
                    cin>>subPilihan;
					
                    if(subPilihan == 1 && role =="customer") {
                    	cout<<"\n--- Akun "<<role<<" ---\n";
                    	cout<<"1. Pengaturan Akun\n";
                        cout<<"2. Pesanan diterima\n";
                        cout<<"0. Kembali\n";
                        int pill;
                        cout<<"Pilih: ";
                        cin>>pill;
                        
                        switch (pill) {
		                    case 1:
		                    	pengaturanAkun(daftarPengguna[indeksPenggunaAktif], daftarPengguna);
                        		simpanPengguna(daftarPengguna);
		                    	break;
		                    case 2:
		                    	cout<<"\nAnda menyatakan pesanan telah diterima.\n";
		                    	cin.ignore();
				                do {
				                    Ulasan u;
				                    cout<<"Komentar Anda: ";
				                    getline(cin, u.komentar);
				                    cout<<"Rating (1 - 5): ";
				                    cin>>u.rating;
				                    cin.ignore();
				
				                    if (u.rating < 1 || u.rating > 5) {
				                        cout<<"Rating harus antara 1 sampai 5.\n";
				                    } else {
				                        cout<<"Ulasan ditambahkan.\n";
				                        break;
				                    }
				                } while (true);
		                    	break;
		                    case 0:
		                    	break;
						}
                    } else if(subPilihan == 1 && role =="admin" ){
                        pengaturanAkun(daftarPengguna[indeksPenggunaAktif], daftarPengguna);
                        simpanPengguna(daftarPengguna);
                    } else if(subPilihan == 2 && role == "customer") {
                        // Lihat poin customer
                        cout<<"Poin Anda saat ini: "<<daftarPengguna[indeksPenggunaAktif].poin<<endl;
                    } else if(subPilihan == 3 && role == "customer") {
					    // Layanan Laundry
					    vector<pesananItem> keranjangLayanan;
					    int pilihanLayanan;
					    int pilihanAksi;
					    bool prosesSelesai = false;
						
						//Menampilkan Daftar Layanan Laundry
					    do {
					        DaftarLayanan_Laundry();
					        
					        //Meminta user untuk memasukkan pilihan
					        cout<<"Masukkan pilihan layanan (0 untuk membatalkan pesanan dan keluar): ";
					        while(!(cin>>pilihanLayanan)){
					            cout<<"Input tidak valid, Masukkan angka: ";
					            cin.clear();
					            cin.ignore(numeric_limits<streamsize>::max(), '\n');
					        }
					
					        if (pilihanLayanan == 0){
					            cout<<"\nAnda membatalkan pemesanan.\n";
					            prosesSelesai = true;
					            break;
					        }
					
							// Memproses input detail layanan dan mendapatkan PesananItem
					        pesananItem currentItem = prosesInputLayanan(pilihanLayanan);
					        if (currentItem.namaLayanan != "") {
					            keranjangLayanan.push_back(currentItem);
					        } else {
					            continue;
					        }
							
							//Menampilkan hasil dari yang dipilih user
					        do {
					            cout<<"\nApa yang ingin anda lakukan?:\n";
					            cout<<"1. Lanjut ke pembayaran\n";
					            cout<<"2. Tambah layanan lain\n";
					            cout<<"3. Batalkan semua layanan dan keluar\n";
					            cout<<"Pilihan anda: ";
					
					            while(!(cin>>pilihanAksi)){
					                cout<<"Input tidak valid,masukkan pilihan (1-3): "<<endl;
					                cin.clear();
					                cin.ignore(numeric_limits<streamsize>::max(), '\n');
					            }
					
					            switch (pilihanAksi){
									case 1:
										tampilkanLayananTerpilih(keranjangLayanan);
										simpanLayananTerpilih(keranjangLayanan, daftarPengguna[indeksPenggunaAktif].username);
										cout<<"\nProses pembayaran untuk total " <<keranjangLayanan.size() <<" layanan anda." <<endl;
										cout<<"Silahkan pilih moda pembayaran" <<endl;
										cout<<"1. Cash (Tunai)" <<endl;
										cout<<"2. Transfer Bank" <<endl;
										cout<<"3. QRIS" <<endl;
										cout<<"4. E-Wallet (DANA/OVO/GoPay/ShoopePay)" <<endl;
										
										cout<<"Masukkan pilihan moda pembayaran: ";
										int modaPembayaran;
										cin>>modaPembayaran;
										cin.ignore(numeric_limits<streamsize>::max(), '\n');
										
										switch (modaPembayaran){
											case 1:
												cout<<"Anda memilih pembayaran dengan Cash (Tunai)" <<endl;
												break;
											case 2:
												cout<<"Anda memilih pembayaran dengan Transfer Bank" <<endl;
												break;
											case 3:
												cout<<"Anda memilih pembayaran dengan QRIS" <<endl;
												break;
											case 4:
												cout<<"Anda memilih pembayaran dengan E-Wallet" <<endl;
												cout<<"Pilih jenis E-Wallet:" <<endl;
												cout<<"1. DANA" <<endl;
												cout<<"2. OVO" <<endl;
												cout<<"3. GoPay" <<endl;
												cout<<"4. ShoopePay" <<endl;
												
												cout<<"Masukkan pilihan E-Wallet: ";
												int ewallet;
												cin>>ewallet;
												cin.ignore(numeric_limits<streamsize>::max(), '\n');
												
												switch (ewallet){
													case 1:
														cout<<"Anda memilih pembayaran dengan DANA" <<endl;
														break;
													case 2:
														cout<<"Anda memilih pembayaran dengan OVO" <<endl;
														break;
													case 3:
														cout<<"Anda memilih pembayaran dengan GoPay" <<endl;
														break;
													case 4:
														cout<<"Anda memilih pembayaran dengan ShoopePay" <<endl;
														break;
													default:
														cout<<"Pilihan E-Wallet tidak valid" <<endl;
														break;
												}
												break;
											default:
												cout<<"Pilihan moda pembayaran tidak valid" <<endl;
												break;
										}
										prosesSelesai = true;
										break;
										
									case 2:
										cout<<"Silahkan tambah pilih layanan yang lain" <<endl;
										break;
									case 3:
										cout<<"\nSemua layanan telah dibatalkan. Terimakasih telah berkunjung" <<endl;
										keranjangLayanan.clear();
										prosesSelesai = true;
										break;
									default:
										cout<<"\nPilihan tidak valid, coba lagi" <<endl;
										break;
								}
							} while (pilihanAksi != 1 && pilihanAksi != 2 && pilihanAksi != 3);
	} while (!prosesSelesai);
		// Tambah POIN
        int bonusPoin = static_cast<int>(keranjangLayanan.size()) * 10;
        daftarPengguna[indeksPenggunaAktif].poin += bonusPoin;
        cout<<"Anda mendapat "<<bonusPoin<<" poin! Total poin sekarang: "<<daftarPengguna[indeksPenggunaAktif].poin<<endl;
					} else if(subPilihan == 0) {
                        cout<<"Logout berhasil.\n";
                        indeksPenggunaAktif = -1;
                        break;
                    } else {
                        cout<<"Pilihan tidak valid.\n";
                    }
                }
            }
        } else if(pilihan == 2) {
            registrasiPengguna(daftarPengguna);
        } else if(pilihan == 0) {
            cout<<"Terima kasih. Program selesai.\n";
            break;
        } else {
            cout<<"Pilihan tidak valid.\n";
        }
    }

    return 0;
}
