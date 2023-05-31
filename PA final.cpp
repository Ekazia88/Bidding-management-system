  
// header C++

#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "string.h"
#include <typeinfo>

using namespace std;
// untuk struct tanggal
struct datetime{
	int month;
	int day;
	int year;
	int h;
	int m;
};

// membuat struct kategori
struct kategori{
	string cat;
};

//membuat datanya dijadikan struct
struct data{
	int id_barang;
	string nama_barang;
	string kondisi_barang;
	int harga_awal;
	int harga_tertinggi;
	struct datetime tanggal_mulai;
	struct datetime tanggal_akhir;
	struct kategori kategori_barang;
	string user_terakhir;
	string status;
	int jml_user;
	
	void save_file(){
	fstream input;
    input.open ("Data_lelang.txt",ios::out | ios::app);
    input<<id_barang<<"," << nama_barang << ","<<kondisi_barang<<","<<harga_awal<<","<<harga_tertinggi<<","<<tanggal_mulai.day<<"/"<<tanggal_mulai.month<<"/"<<tanggal_mulai.year<<" "<<tanggal_mulai.h<< ":"<<tanggal_mulai.m<<",";
    input<<tanggal_akhir.day<<"/"<<tanggal_akhir.month<<"/"<<tanggal_akhir.year<<" "<<tanggal_akhir.h<<":"<<tanggal_akhir.m<<","<<kategori_barang.cat<<","<<status<<","<<user_terakhir<<","<<jml_user<<endl;
    input.close();
	}	
};

struct user_account{
	int id_user;
	string username;
	string nama;
	string password;
	string alamat;
	int history;
	struct data user_barang[100];
	
	void save_file_user(){
		fstream input;
		fstream user;
		input.open("user_data.txt",ios::out | ios::app);
		user.open("user_"+username+".txt",ios::in | ios::app);
		input<<id_user<<","<<username<<","<<nama<<","<<password<<","<<alamat<<","<<history<<endl;
		user<<id_user<<"\n"<<username<<"\n"<<nama<<"\n"<<password<<"\n"<<alamat<<"\n"<<history<<"\n"<<endl;
		input.close();
		user.close();
	}
	void save_file_history(int indek){
		fstream user;
		user.open("user_"+username+".txt",ios::in | ios::app);
		user<<id_user<<"\n"<<username<<"\n"<<nama<<"\n"<<password<<"\n"<<alamat<<"\n"<<history<<endl;
		user<<user_barang[indek].id_barang<<"," << user_barang[indek].nama_barang << ","<<user_barang[indek].kondisi_barang<<","<<user_barang[indek].harga_awal<<","<<user_barang[indek].harga_tertinggi<<","<<user_barang[indek].tanggal_mulai.day<<"/"<<user_barang[indek].tanggal_mulai.month<<"/"<<user_barang[indek].tanggal_mulai.year<<" "<<user_barang[indek].tanggal_mulai.h<< ":"<<user_barang[indek].tanggal_mulai.m<<",";
    	user<<user_barang[indek].tanggal_akhir.day<<"/"<<user_barang[indek].tanggal_akhir.month<<"/"<<user_barang[indek].tanggal_akhir.year<<" "<<user_barang[indek].tanggal_akhir.h<<":"<<user_barang[indek].tanggal_akhir.m<<","<<user_barang[indek].status<<","<<user_barang[indek].kategori_barang.cat<<","<<user_barang[indek].user_terakhir<<","<<user_barang[indek].jml_user<<endl;
		user.close();
	}
};


user_account ak[100];
user_account acc;
user_account *ptr_user[100];
//mebuat struct data menjadi array
data dt[100];
//membuat pointer sruct 
data *ptr[100];

//mendeklarasikan tipe data
int Menu,indeks;
int i=0;
int x=0;
int byk =0;
int byk_user = 0;
int all_user =0;
int j;
int f;
string pil,cari;
bool condition= true;
bool flag;
fstream Data;
fstream user_data;
fstream history_user;

void import_all_user(){
	i =0;
	string id_user,history;
	user_data.open("user_data.txt",ios::in | ios::app);
	while(!user_data.eof()){
	getline(user_data, id_user,',');
	getline(user_data, ak[i].username,',');
	getline(user_data, ak[i].nama,',');
	getline(user_data, ak[i].password,',');
	getline(user_data, ak[i].alamat,',');
	getline(user_data, history,'\n');
	
	stringstream str_id_user(id_user);
	stringstream str_history(history);                                                                
	
	str_id_user >> ak[i].id_user;
	str_history >> ak[i].history;
	i++;
	}
	all_user =i;
	user_data.close();
}
void import_user(string username){
	int i =0;
	string id_user,history,line;
	user_data.open("user_"+username+".txt",ios::in | ios::app);
	for(getline(user_data,line)&& i<6; i++;){
		stringstream line1(line);
		
		getline(line1, id_user,'\n');
		getline(line1, acc.username,'\n');
		getline(line1, acc.nama,'\n');
		getline(line1, acc.password,'\n');
		getline(line1, acc.alamat,'\n');
		getline(line1, history,'\n');
		
		stringstream str_id_user(id_user);
		stringstream str_history(history);                                                                
		
		str_id_user >> acc.id_user;
		str_history >> acc.history;
	}
	user_data.close();
}
int import_history(string username){
	i=0;
	int indeks =0;
	string line,line2,str_line, id_barang, harga_awal, harga_tertinggi,tanggal_mulai_day,tanggal_mulai_month, tanggal_mulai_year,tanggal_mulai_h,tanggal_mulai_m,tanggal_akhir_day,tanggal_akhir_month,tanggal_akhir_year,tanggal_akhir_h,tanggal_akhir_m,jml_user;
	string id_user,history;
	history_user.open("user_"+username+".txt",ios::in | ios::app);
	if(history_user.is_open()){
			while(getline(history_user,str_line)&& i != 6){
				i++;
			}
			if(i >=  6){
					stringstream line2(str_line);
					getline(line2, id_barang, ',');
					getline(line2, acc.user_barang[indeks].nama_barang, ',');
				    getline(line2, acc.user_barang[indeks].kondisi_barang, ',');
				    getline(line2, harga_awal, ',' );
				    getline(line2, harga_tertinggi, ',');
				    getline(line2, tanggal_mulai_day, '/');
				    getline(line2, tanggal_mulai_month, '/');
				    getline(line2, tanggal_mulai_year, ' ');
				    getline(line2, tanggal_mulai_h, ':');
				    getline(line2, tanggal_mulai_m, ',');
				    getline(line2, tanggal_akhir_day, '/');
				    getline(line2, tanggal_akhir_month,'/');
				    getline(line2, tanggal_akhir_year,' ');
				    getline(line2, tanggal_akhir_h,':');
				    getline(line2, tanggal_akhir_m,',');
				    getline(line2, acc.user_barang[indeks].kategori_barang.cat,',');
				    getline(line2, acc.user_barang[indeks].status,',');
				    getline(line2, acc.user_barang[indeks].user_terakhir,',');
				    getline(line2, jml_user);
				
				    stringstream str_id_barang(id_barang);
				    stringstream str_harga_awal(harga_awal);
				    stringstream str_harga_tertinggi(harga_tertinggi);
				    stringstream str_tglmulai_hari(tanggal_mulai_day);
				    stringstream str_tglmulai_bulan(tanggal_mulai_month);
				    stringstream str_tglmulai_tahun(tanggal_mulai_year);
				    stringstream str_tglmulai_jam(tanggal_mulai_h);
				    stringstream str_tglmulai_menit(tanggal_mulai_m);
				    stringstream str_tglakhir_hari(tanggal_akhir_day);
				    stringstream str_tglakhir_bulan(tanggal_akhir_month);
				    stringstream str_tglakhir_tahun(tanggal_akhir_year);
				    stringstream str_tglakhir_jam(tanggal_akhir_h);
				    stringstream str_tglakhir_menit(tanggal_akhir_m);
				    stringstream str_jml_user(jml_user);
				    
				    str_id_barang >> acc.user_barang[indeks].id_barang;
					str_harga_awal >> acc.user_barang[indeks].harga_awal;
					str_harga_tertinggi >> acc.user_barang[indeks].harga_tertinggi;
					str_tglmulai_hari >> acc.user_barang[indeks].tanggal_mulai.day;
					str_tglmulai_bulan >> acc.user_barang[indeks].tanggal_mulai.month; 
					str_tglmulai_tahun >> acc.user_barang[indeks].tanggal_mulai.year;
					str_tglmulai_jam >> acc.user_barang[indeks].tanggal_mulai.h;
					str_tglmulai_menit >> acc.user_barang[indeks].tanggal_mulai.m;
					str_tglakhir_hari >> acc.user_barang[indeks].tanggal_akhir.day;
					str_tglakhir_bulan >> acc.user_barang[indeks].tanggal_akhir.month;
					str_tglakhir_tahun >> acc.user_barang[indeks].tanggal_akhir.year;
					str_tglakhir_jam >> acc.user_barang[indeks].tanggal_akhir.h;
					str_tglakhir_menit >> acc.user_barang[indeks].tanggal_akhir.m;
					str_jml_user >> acc.user_barang[indeks].jml_user;
					indeks++;
				}
		history_user.clear();
		history_user.seekg(0, ios::beg);
		byk_user = indeks;
		history_user.close();
	}
	
	
}
int import_data(){
	i=0;
	string line, id_barang, harga_awal, harga_tertinggi,tanggal_mulai_day,tanggal_mulai_month, tanggal_mulai_year,tanggal_mulai_h,tanggal_mulai_m,tanggal_akhir_day,tanggal_akhir_month,tanggal_akhir_year,tanggal_akhir_h,tanggal_akhir_m,jml_user;
	Data.open("Data_lelang.txt", ios::in | ios::app );
	if(Data.is_open()){
		while(getline(Data, line)){
			stringstream str_line(line);

			getline(str_line, id_barang, ',');
			getline(str_line, dt[i].nama_barang, ',');
	        getline(str_line, dt[i].kondisi_barang, ',');
	        getline(str_line, harga_awal, ',' );
	        getline(str_line, harga_tertinggi, ',');
	        getline(str_line, tanggal_mulai_day, '/');
	        getline(str_line, tanggal_mulai_month, '/');
	        getline(str_line, tanggal_mulai_year, ' ');
	        getline(str_line, tanggal_mulai_h, ':');
	        getline(str_line, tanggal_mulai_m, ',');
	        getline(str_line, tanggal_akhir_day, '/');
	        getline(str_line, tanggal_akhir_month,'/');
	        getline(str_line, tanggal_akhir_year,' ');
	        getline(str_line, tanggal_akhir_h,':');
	        getline(str_line, tanggal_akhir_m,',');
	        getline(str_line, dt[i].kategori_barang.cat,',');
	        getline(str_line, dt[i].status,',');
	        getline(str_line, dt[i].user_terakhir,',');
	        getline(str_line, jml_user,'\n');
	
	        stringstream str_id_barang(id_barang);
	        stringstream str_harga_awal(harga_awal);
	        stringstream str_harga_tertinggi(harga_tertinggi);
	        stringstream str_tglmulai_hari(tanggal_mulai_day);
	        stringstream str_tglmulai_bulan(tanggal_mulai_month);
	        stringstream str_tglmulai_tahun(tanggal_mulai_year);
	        stringstream str_tglmulai_jam(tanggal_mulai_h);
	        stringstream str_tglmulai_menit(tanggal_mulai_m);
	        stringstream str_tglakhir_hari(tanggal_akhir_day);
	        stringstream str_tglakhir_bulan(tanggal_akhir_month);
	        stringstream str_tglakhir_tahun(tanggal_akhir_year);
	        stringstream str_tglakhir_jam(tanggal_akhir_h);
	        stringstream str_tglakhir_menit(tanggal_akhir_m);
	        stringstream str_jml_user(jml_user);
	        
	        str_id_barang >> dt[i].id_barang;
			str_harga_awal >> dt[i].harga_awal;
			str_harga_tertinggi >> dt[i].harga_tertinggi;
			str_tglmulai_hari >> dt[i].tanggal_mulai.day;
			str_tglmulai_bulan >> dt[i].tanggal_mulai.month; 
			str_tglmulai_tahun >> dt[i].tanggal_mulai.year;
			str_tglmulai_jam >> dt[i].tanggal_mulai.h;
			str_tglmulai_menit >> dt[i].tanggal_mulai.m;
			str_tglakhir_hari >> dt[i].tanggal_akhir.day;
			str_tglakhir_bulan >> dt[i].tanggal_akhir.month;
			str_tglakhir_tahun >> dt[i].tanggal_akhir.year;
			str_tglakhir_jam >> dt[i].tanggal_akhir.h;
			str_tglakhir_menit >> dt[i].tanggal_akhir.m;
			str_jml_user >> dt[i].jml_user;
			 i++;
		}
		byk = i;
	}
	history_user.clear();
	history_user.seekg(0, ios::beg);
	Data.close();
}

// prosedur menampilkan data
void show_admin(){
	import_data();
	bool empty = (Data.get(),Data.eof());
	cout<<"|=========================================|"<<endl;
	cout<<"|                APLIKASI LELANG          |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<empty;
	// jika array struct == 0 maka menampilkan data tidak ada
	if(empty==0){
		cout<<"|             Data tidak ada              |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<" tekan Enter untuk Kembali....."<<endl;
		// untuk kembali ke menu awal dengan menekan enter
		getch();
		// untuk menghapus tampilan sebelumnya
		system("cls");
	}
	//jika sturct ada isinya maka akan muncul sesuai yg diinputkan
	else{
			
		for(int i = 0; i<byk;i++){
			// membuat var pointer tadi menjadi address dari struct data dt
			ptr[i] = &dt[i];
			// memanggil sruct data menggunakan pointer
			cout<<"| id barang : "<<ptr[i]->id_barang<<endl;
			cout<<"| nama barang : "<<ptr[i]->nama_barang<<endl;
			cout<<"| kondisi barang : "<<ptr[i]->kondisi_barang<<endl;
			cout<<"| harga awal : "<<ptr[i]->harga_awal<<endl;
			cout<<"| harga tertinggi : "<<ptr[i]->harga_tertinggi<<endl;
			cout<<"| tanggal mulai lelang : "<<ptr[i]->tanggal_mulai.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
			cout<<"| tanggal akhir lelang : "<<ptr[i]->tanggal_akhir.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
			cout<<"| kategori barang : "<<ptr[i]->kategori_barang.cat<<endl;
			cout<<"| status : "<<ptr[i]->status<<endl;
			cout<<"|=========================================|"<<endl;
		}
	}
}

// prosedur menambahkan data 
void add_admin(){
	cout<<"|=========================================|"<<endl;
	cout<<"|            APLIKASI LELANG              |"<<endl;
	cout<<"|=========================================|"<<endl;
	// melakukan perulangan supaya bisa memasukkan data banyak
	do{
		ptr[i] = &dt[i];
		cout<<"| Id barang : ";
		// masukkan struct id barang
		cin>>dt[i].id_barang;
		// masukkan struct nama_barang
		cout<<"| nama barang : ";
		getline(cin>>ws,dt[i].nama_barang);
		cout<<"| Kondisi Barang :";
		getline(cin>>ws,dt[i].kondisi_barang);
		cout<<"| Harga awal : ";
		cin>>dt[i].harga_awal;
		dt[i].harga_tertinggi = 0;
		cout<<"| tanggal mulai "<<endl;
		cout<<"| tanggal : ";
		cin>>dt[i].tanggal_mulai.day;
		cout<<"| bulan : " ;
		cin>>dt[i].tanggal_mulai.month;
		cout<<"| tahun : " ;
		cin>>dt[i].tanggal_mulai.year; 
		cout<<"| waktu (H) : " ;
		cin>>dt[i].tanggal_mulai.h; 
		cout<<"| waktu (M) : " ;
		cin>>dt[i].tanggal_mulai.h; 
		cout<<"| tanggal akhir "<<endl;
		cout<<"| tanggal : ";
		cin>>dt[i].tanggal_akhir.day;
		cout<<"| bulan : " ;
		cin>>dt[i].tanggal_akhir.month;
		cout<<"| tahun : " ;
		cin>>dt[i].tanggal_akhir.year; 
		cout<<"| waktu (H) : ";
		cin>>dt[i].tanggal_akhir.h;
		cout<<"| waktu (M) : ";
		cin>>dt[i].tanggal_akhir.m;
		cout<<"| Kategori Barang : ";
		getline(cin>>ws,dt[i].kategori_barang.cat);
		dt[i].status = "Ditutup";
		dt[i].user_terakhir = " ";
		dt[i].jml_user = 0;
		dt[i].save_file();
		//jika ingin menambah data
		cout<<"Tambah Data ? [y/n] : ";
		cin>>pil;
		cout<<" "<<endl;
		if(pil == "y"){
			continue;
		}
		else if(pil == "n"){
			system("cls");
			break;
	 	}
		else{
			cout<<"Invalid Input / try again"<<endl;
			break;
			cout<<"tekan Enter untuk Kembali....."<<endl;
			getch();
		}
	}
	while(i<100);

}

// prosedur edit
void edit_admin(){
	bool flag;
	int indek;
	import_data();
	cout<<"|=========================================|"<<endl;
	cout<<"|             APLIKASI LELANG       	 	 |"<<endl;
	cout<<"|=========================================|"<<endl;
	// mencari data sesuai id 
	cout<<"  masukkan data id dicari : ";
	cin>>indeks;
	for(i=0;i<byk;i++){
		//jika id dicari benar maka akan muncul input edit
		if(dt[i].id_barang == indeks){
			flag = true;
			indek = i;
			break;
		}
	}
	if(flag== true){
		Data.open("Data_lelang.txt", ios::trunc);
		Data.close();
		cout<<"| Id barang : ";
		// masukkan struct id barang
		cin>>dt[indek].id_barang;
		// masukkan struct nama_barang
		cout<<"| nama barang : ";
		getline(cin>>ws,dt[indek].nama_barang);
		cout<<"| Kondisi Barang :";
		getline(cin>>ws,dt[indek].kondisi_barang);
		cout<<"| Harga awal : ";
		cin>>dt[indek].harga_awal;
		dt[indek].harga_tertinggi = dt[indek].harga_tertinggi;
		cout<<"| tanggal mulai "<<endl;
		cout<<"| tanggal : ";
		cin>>dt[indek].tanggal_mulai.day;
		cout<<"| bulan : " ;
		cin>>dt[indek].tanggal_mulai.month;
		cout<<"| tahun : " ;
		cin>>dt[indek].tanggal_mulai.year; 
		cout<<"| waktu (H) : " ;
		cin>>dt[indek].tanggal_mulai.h; 
		cout<<"| waktu (M) : " ;
		cin>>dt[indek].tanggal_mulai.h; 
		cout<<"| tanggal akhir "<<endl;
		cout<<"| tanggal : ";
		cin>>dt[indek].tanggal_akhir.day;
		cout<<"| bulan : " ;
		cin>>dt[indek].tanggal_akhir.month;
		cout<<"| tahun : " ;
		cin>>dt[indek].tanggal_akhir.year; 
		cout<<"| waktu (H) : ";
		cin>>dt[indek].tanggal_akhir.h;
		cout<<"| waktu (M) : ";
		cin>>dt[indek].tanggal_akhir.m;
		cout<<"| Kategori Barang : ";
		getline(cin>>ws,dt[indek].kategori_barang.cat);
		dt[indek].status = dt[indek].status;
		dt[indek].user_terakhir = dt[indek].user_terakhir;
		dt[indek].jml_user = dt[indek].jml_user;
	}		
		// kalo tidak ada maka data tidak ada / salah
	else{
		cout<<"|      	  Data tidak ada/salah           |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"tekan Enter untuk Kembali....."<<endl;
		getch();
		system("cls");
	}
	Data.open("Data_lelang.txt",ios::out);
	for(i=0;i<byk;i++){
		Data<<dt[i].id_barang<<","<<dt[i].nama_barang << ","<<dt[i].kondisi_barang<<","<<dt[i].harga_awal<<","<<dt[i].harga_tertinggi<<","<<dt[i].tanggal_mulai.day<<"/"<<dt[i].tanggal_mulai.month<<"/"<<dt[i].tanggal_mulai.year<<" "<<dt[i].tanggal_mulai.h<<":"<<dt[i].tanggal_mulai.m<<",";
	    Data<<dt[i].tanggal_akhir.day<<"/"<<dt[i].tanggal_akhir.month<<"/"<<dt[i].tanggal_akhir.year<<" "<<dt[i].tanggal_akhir.h<<":"<<dt[i].tanggal_akhir.m<<","<<dt[i].kategori_barang.cat<<","<<dt[i].status<<","<<dt[i].user_terakhir<<","<<dt[i].jml_user<<endl;
	}
	cout<<"|=========================================|"<<endl;
	system("cls");
	Data.close();
	cout<<"|=========================================|"<<endl;
	cout<<"|              APLIKASI LELANG            |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"|      	  Data Telah Berhasil Diubah     |"<<endl;
	cout<<"|=========================================|"<<endl;
	getch();
	system("cls");
}
void del_admin(){
	int indek;
	bool flag;
	import_data();
	cout<<"|=========================================|"<<endl;
	cout<<"|             APLIKASI LELANG             |"<<endl;
	cout<<"|=========================================|"<<endl;
	// mencari data sesuai id 
	cout<<" Masukkan data id dicari : ";
	cin>>indeks;
	cout<<"|=========================================|"<<endl;
	system("cls");
	// melakukan perulangan untuk mencheck semua data
	for(i=0;i<byk;i++){
		//jika id sesuai dengan data yg telah diinputkan
		if(dt[i].id_barang == indeks){
			flag = true;
			indek = i;
			break;
		}	
	}
	if(flag == true){
		Data.open("Data_lelang.txt", ios::trunc);
		Data.close();
		Data.open("Data_lelang.txt", ios::out);
		for(i=0;i<byk;i++){
			if(dt[i].id_barang != indeks){
				Data<<dt[i].id_barang<<","<< dt[i].nama_barang << ","<<dt[i].kondisi_barang<<","<<dt[i].harga_awal<<","<<dt[i].harga_tertinggi<<","<<dt[i].tanggal_mulai.day<<"/"<<dt[i].tanggal_mulai.month<<"/"<<dt[i].tanggal_mulai.year<<" "<<dt[i].tanggal_mulai.h<< ":"<<dt[i].tanggal_mulai.m<<",";
			    Data<<dt[i].tanggal_akhir.day<<"/"<<dt[i].tanggal_akhir.month<<"/"<<dt[i].tanggal_akhir.year<<" "<<dt[i].tanggal_akhir.h<<":"<<dt[i].tanggal_akhir.m<<","<<dt[i].status<<","<<dt[i].kategori_barang.cat<<","<<dt[i].user_terakhir<<","<<dt[i].jml_user<<endl;
			}
		}
		Data.close();
		cout<<"|=========================================|"<<endl;
		cout<<"|         APLIKASI LELANG  		         |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"|           Data telah dihapus!!          |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"tekan Enter untuk Kembali....."<<endl;
		getch();
		system("cls");
	}
			
	// kalo tidak ada maka data tidak ada / salah
	else{
		cout<<"|=========================================|"<<endl;
		cout<<"|         APLIKASI LELANG  		         |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"|              Data tidak ada             |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"    tekan Enter untuk Kembali....."<<endl;
		getch();
		system("cls");
	}
}
void change_status(int indek){
	import_data();
	Data.open("Data_lelang.txt", ios::trunc);
	history_user.open("user_"+dt[indek].user_terakhir+".txt",ios::trunc);
	
	Data.close();
	history_user.close();
	
	acc.id_user = acc.id_user;
	acc.username = acc.username;
	acc.nama = acc.nama;
	acc.alamat = acc.alamat;
	acc.password = acc.password;
	acc.history = acc.history;
	
		
	dt[indek].id_barang = dt[indek].id_barang;
	dt[indek].nama_barang = dt[indek].nama_barang;
	dt[indek].kondisi_barang = dt[indek].kondisi_barang;
	dt[indek].harga_awal = dt[indek].harga_awal;
	dt[indek].harga_tertinggi = dt[indek].harga_tertinggi;
	dt[indek].tanggal_mulai.day;dt[indek].tanggal_mulai.month;dt[indek].tanggal_mulai.year;dt[indek].tanggal_mulai.h;dt[indek].tanggal_mulai.m = dt[indek].tanggal_mulai.day;dt[indek].tanggal_mulai.month;dt[indek].tanggal_mulai.year;dt[indek].tanggal_mulai.h;dt[indek].tanggal_mulai.m;
	dt[indek].tanggal_akhir.day;dt[indek].tanggal_akhir.month;dt[indek].tanggal_akhir.year;dt[indek].tanggal_akhir.h;dt[indek].tanggal_akhir.m = dt[indek].tanggal_akhir.day;dt[indek].tanggal_akhir.month;dt[indek].tanggal_akhir.year;dt[indek].tanggal_akhir.h;dt[indek].tanggal_akhir.m;
	dt[indek].kategori_barang.cat = dt[indek].kategori_barang.cat;
	if(dt[indek].status == "Ditutup"){
		dt[indek].status = "Dibuka";
	}
	else if(dt[indek].status == "Dibuka"){
		dt[indek].status = "Ditutup";
	}
	dt[indek].user_terakhir = dt[indek].user_terakhir;
	
	acc.user_barang[indek].id_barang = dt[indek].id_barang;
	acc.user_barang[indek].nama_barang = dt[indek].nama_barang;
	acc.user_barang[indek].kondisi_barang = dt[indek].kondisi_barang;
	acc.user_barang[indek].harga_awal = dt[indek].harga_awal;
	acc.user_barang[indek].harga_tertinggi = dt[indek].harga_tertinggi;
	acc.user_barang[indek].tanggal_mulai.day = dt[indek].tanggal_mulai.day;acc.user_barang[indek].tanggal_mulai.month = dt[indek].tanggal_mulai.month;acc.user_barang[indek].tanggal_mulai.year = dt[indek].tanggal_mulai.year;acc.user_barang[indek].tanggal_mulai.h = dt[indek].tanggal_mulai.h;acc.user_barang[indek].tanggal_mulai.m = dt[indek].tanggal_mulai.m;
	acc.user_barang[indek].tanggal_akhir.day = dt[indek].tanggal_akhir.day;acc.user_barang[indek].tanggal_akhir.month = dt[indek].tanggal_mulai.month;acc.user_barang[indek].tanggal_akhir.year = dt[indek].tanggal_akhir.year;acc.user_barang[indek].tanggal_akhir.h = dt[indek].tanggal_akhir.h;acc.user_barang[indek].tanggal_akhir.m = dt[indek].tanggal_akhir.m;
	acc.user_barang[indek].kategori_barang.cat = dt[indek].kategori_barang.cat;
	acc.user_barang[indek].status = dt[indek].status;
	acc.user_barang[indek].user_terakhir = dt[indek].user_terakhir;
	Data.open("Data_lelang.txt",ios::out);
	history_user.open("user_"+dt[indek].user_terakhir+".txt",ios::out);
	
	byk_user = byk_user+1;
	
	history_user<<acc.id_user<<"\n"<<acc.username<<"\n"<<acc.nama<<"\n"<<acc.password<<"\n"<<acc.alamat<<"\n"<<acc.history<<endl;
	for(int k =0; k<byk_user;k++){
		history_user<<acc.user_barang[k].id_barang<<"," << acc.user_barang[k].nama_barang << ","<<acc.user_barang[k].kondisi_barang<<","<<acc.user_barang[k].harga_awal<<","<<acc.user_barang[k].harga_tertinggi<<","<<acc.user_barang[k].tanggal_mulai.day<<"/"<<acc.user_barang[k].tanggal_mulai.month<<"/"<<acc.user_barang[k].tanggal_mulai.year<<" "<<acc.user_barang[k].tanggal_mulai.h<< ":"<<acc.user_barang[k].tanggal_mulai.m<<",";
		history_user<<acc.user_barang[k].tanggal_akhir.day<<"/"<<acc.user_barang[k].tanggal_akhir.month<<"/"<<acc.user_barang[k].tanggal_akhir.year<<" "<<acc.user_barang[k].tanggal_akhir.h<<":"<<acc.user_barang[k].tanggal_akhir.m<<","<<acc.user_barang[k].kategori_barang.cat<<","<<acc.user_barang[k].status<<","<<acc.user_barang[k].user_terakhir<<","<<acc.user_barang[k].jml_user<<endl;
	}
	for(int k = 0; k<byk;k++){
		Data<<ptr[k]->id_barang<<"," << ptr[k]->nama_barang << ","<<ptr[k]->kondisi_barang<<","<<ptr[k]->harga_awal<<","<<ptr[k]->harga_tertinggi<<","<<ptr[k]->tanggal_mulai.day<<"/"<<ptr[k]->tanggal_mulai.month<<"/"<<ptr[k]->tanggal_mulai.year<<" "<<ptr[k]->tanggal_mulai.h<< ":"<<ptr[k]->tanggal_mulai.m<<",";
		Data<<ptr[k]->tanggal_akhir.day<<"/"<<ptr[k]->tanggal_akhir.month<<"/"<<ptr[k]->tanggal_akhir.year<<" "<<ptr[k]->tanggal_akhir.h<<":"<<ptr[k]->tanggal_akhir.m<<","<<ptr[k]->kategori_barang.cat<<","<<ptr[k]->status<<","<<ptr[k]->user_terakhir<<","<<ptr[k]->jml_user<<endl;
	}
	cout<<"|=========================================|"<<endl;
	cout<<"|          Data berhasil diubah           |"<<endl;
	cout<<"|=========================================|"<<endl;
	Data.close();
	history_user.close();
	
}
void Cari_data(){
	import_data();
	bool flag;
	int indek;
	cout<<"|=========================================|"<<endl;
	cout<<"|                APLIKASI LELANG          |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Nama Barang yg ingin dicari : ";
	getline(cin>>ws, cari);
	system("cls");
	for(int k = 0; k<byk;k++){
		if(dt[k].nama_barang == cari){
			flag = true;
			indek = k;
			break;
		}
	}
	if(flag == true){
		cout<<"|=========================================|"<<endl;
		cout<<"|                APLIKASI LELANG          |"<<endl;
		cout<<"|=========================================|"<<endl;
		ptr[indek] = &dt[indek];
		// memanggil sruct data menggunakan pointer
		cout<<"| id barang : "<<dt[indek].id_barang<<endl;
		cout<<"| nama barang : "<<ptr[indek]->nama_barang<<endl;
		cout<<"| kondisi barang : "<<ptr[indek]->kondisi_barang<<endl;
		cout<<"| harga awal : "<<ptr[indek]->harga_awal<<endl;
		cout<<"| harga tertinggi : "<<ptr[indek]->harga_tertinggi<<endl;
		cout<<"| tanggal mulai lelang : "<<ptr[indek]->tanggal_mulai.day<<"/"<<ptr[indek]->tanggal_mulai.month<<"/"<<ptr[indek]->tanggal_mulai.year<<" "<<ptr[indek]->tanggal_mulai.h<<":"<<ptr[indek]->tanggal_mulai.m<<endl;
		cout<<"| tanggal akhir lelang : "<<ptr[indek]->tanggal_akhir.day<<"/"<<ptr[indek]->tanggal_mulai.month<<"/"<<ptr[indek]->tanggal_mulai.month<<"/"<<ptr[indek]->tanggal_mulai.year<<" "<<ptr[indek]->tanggal_mulai.h<<":"<<ptr[indek]->tanggal_mulai.m<<endl;
		cout<<"| kategori barang : "<<ptr[indek]->kategori_barang.cat<<endl;
		cout<<"| status : "<<ptr[indek]->status<<endl;
		cout<<"|=========================================|"<<endl;
		while(true){
			cout<<"| Ganti Status Lelang [1.ya/2.tidak] : ";
			cin>>Menu;
			if(Menu == 1){
				system("cls");
				change_status(indek);
				getch();
				system("cls");
				break;
			}
			else if(Menu == 2){
				system("cls");
				break;
			}
			else{
				cout<<"Input invalid! Try again"<<endl;
				getch();
			}
		}
	}
	else{
		cout<<"|=========================================|"<<endl;
		cout<<"|              APLIKASI LELANG            |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"|      	  Data tidak ada/salah           |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"tekan Enter untuk Kembali....."<<endl;
		getch();
		system("cls");
	}
	getch();
}
void urut_Kategori(){
	import_data();
	cout<<"|=========================================|"<<endl;
	cout<<"|            APLIKASI LELANG              |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Sorting berdasarkan nama secara :       |"<<endl;
	cout<<"| 1. Ascending                            |"<<endl;
	cout<<"| 2. Descending                           |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Menu : ";
	cin>>Menu;
	system("cls");
	if(Menu == 1){
		struct data temp;
		for (i = 0; i < byk - 1; i++){
			for (int j = 0; j < (byk - 1-i); j++){
        		if (dt[j].kategori_barang.cat  > dt[j + 1].kategori_barang.cat ){
	                temp = dt[j];
	                dt[j] = dt[j + 1];
	                dt[j + 1] = temp;
        		} 
    		}
		}
	}
	else if(Menu == 2){
		struct data temp;
		for (i = 0; i < byk +1-1; i++){
			for (int j = 0; j < (byk - 1-i); j++){
        		if (dt[j].kategori_barang.cat  < dt[j + 1].kategori_barang.cat){
	                temp = dt[j];
	                dt[j] = dt[j + 1];
	                dt[j + 1] = temp;
        		} 
    		}
		}
	}
	else{
		cout<<"Invalid Input / Try Again"<<endl;
	}
	system("cls");
	cout<<"|=========================================|"<<endl;
	cout<<"|                APLIKASI LELANG          |"<<endl;
	cout<<"|=========================================|"<<endl;
	for(int i = 0; i<byk;i++){
		// membuat var pointer tadi menjadi address dari struct data dt
		ptr[i] = &dt[i];
		// memanggil sruct data menggunakan pointer
		cout<<"| id barang : "<<ptr[i]->id_barang<<endl;
		cout<<"| nama barang : "<<ptr[i]->nama_barang<<endl;
		cout<<"| kondisi barang : "<<ptr[i]->kondisi_barang<<endl;
		cout<<"| harga awal : "<<ptr[i]->harga_awal<<endl;
		cout<<"| harga tertinggi : "<<ptr[i]->harga_tertinggi<<endl;
		cout<<"| tanggal mulai lelang : "<<ptr[i]->tanggal_mulai.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
		cout<<"| tanggal akhir lelang : "<<ptr[i]->tanggal_akhir.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
		cout<<"| kategori barang : "<<ptr[i]->kategori_barang.cat<<endl;
		cout<<"| status : "<<ptr[i]->status<<endl;
		cout<<"|=========================================|"<<endl;
	}
	getch();
}
void urut_Tanggal(){
	import_data();
	cout<<"|=========================================|"<<endl;
	cout<<"|            APLIKASI LELANG              |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Sorting berdasarkan nama secara :       |"<<endl;
	cout<<"| 1. Ascending                            |"<<endl;
	cout<<"| 2. Descending                           |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Menu : ";
	cin>>Menu;
	system("cls");
	if(Menu == 1){
		struct data temp;
		for (i = 0; i < byk - 1; i++){
			for (int j = 0; j < (byk - 1-i); j++){
        		if (dt[j].tanggal_mulai.day  > dt[j + 1].tanggal_mulai.day && dt[j].tanggal_mulai.month > dt[j+1].tanggal_mulai.month && dt[j].tanggal_mulai.year > dt[j+1].tanggal_mulai.year && dt[j].tanggal_mulai.h > dt[j+1].tanggal_mulai.h && dt[j].tanggal_mulai.m > dt[j+1].tanggal_mulai.m){
	                temp = dt[j];
	                dt[j] = dt[j + 1];
	                dt[j + 1] = temp;
        		} 
    		}
		}
	}
	else if(Menu == 2){
		struct data temp;
		for (i = 0; i < byk +1-1; i++){
			for (int j = 0; j < (byk - 1-i); j++){
        		if (dt[j].tanggal_mulai.day  < dt[j + 1].tanggal_mulai.day && dt[j].tanggal_mulai.month < dt[j+1].tanggal_mulai.month && dt[j].tanggal_mulai.year < dt[j+1].tanggal_mulai.year && dt[j].tanggal_mulai.h < dt[j+1].tanggal_mulai.h && dt[j].tanggal_mulai.m < dt[j+1].tanggal_mulai.m){
	                temp = dt[j];
	                dt[j] = dt[j + 1];
	                dt[j + 1] = temp;
        		} 
    		}
		}
	}
	else{
		cout<<"Invalid Input / Try Again"<<endl;
	}
	system("cls");
	cout<<"|=========================================|"<<endl;
	cout<<"|                APLIKASI LELANG          |"<<endl;
	cout<<"|=========================================|"<<endl;
	for(int i = 0; i<byk;i++){
		// membuat var pointer tadi menjadi address dari struct data dt
		ptr[i] = &dt[i];
		// memanggil sruct data menggunakan pointer
		cout<<"| id barang : "<<ptr[i]->id_barang<<endl;
		cout<<"| nama barang : "<<ptr[i]->nama_barang<<endl;
		cout<<"| kondisi barang : "<<ptr[i]->kondisi_barang<<endl;
		cout<<"| harga awal : "<<ptr[i]->harga_awal<<endl;
		cout<<"| harga tertinggi : "<<ptr[i]->harga_tertinggi<<endl;
		cout<<"| tanggal mulai lelang : "<<ptr[i]->tanggal_mulai.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
		cout<<"| tanggal akhir lelang : "<<ptr[i]->tanggal_akhir.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
		cout<<"| kategori barang : "<<ptr[i]->kategori_barang.cat<<endl;
		cout<<"| status : "<<ptr[i]->status<<endl;
		cout<<"|=========================================|"<<endl;
	}
	getch();
}
void urut_Id(){
	import_data();
	cout<<"|=========================================|"<<endl;
	cout<<"|            APLIKASI LELANG              |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Sorting berdasarkan id secara :         |"<<endl;
	cout<<"| 1. Ascending                            |"<<endl;
	cout<<"| 2. Descending                           |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Menu : ";
	cin>>Menu;
	system("cls");
	if(Menu == 1){
		struct data temp;
		for (i = 0; i < byk - 1; i++){
			for (int j = 0; j < (byk - 1-i); j++){
        		if (dt[j].id_barang > dt[j + 1].id_barang){
	                temp = dt[j];
	                dt[j] = dt[j + 1];
	                dt[j + 1] = temp;
        		} 
    		}
		}
	}
	else if(Menu == 2){
		struct data temp;
		for (i = 0; i < byk +1-1; i++){
			for (int j = 0; j < (byk - 1-i); j++){
        		if (dt[j].id_barang < dt[j + 1].id_barang){
	                temp = dt[j];
	                dt[j] = dt[j + 1];
	                dt[j + 1] = temp;
        		} 
    		}
		}
	}
	else{
		cout<<"Invalid Input / Try Again"<<endl;
	}
	system("cls");
	cout<<"|=========================================|"<<endl;
	cout<<"|                APLIKASI LELANG          |"<<endl;
	cout<<"|=========================================|"<<endl;
	for(int i = 0; i<byk;i++){
		// membuat var pointer tadi menjadi address dari struct data dt
		ptr[i] = &dt[i];
		// memanggil sruct data menggunakan pointer
		cout<<"| id barang : "<<ptr[i]->id_barang<<endl;
		cout<<"| nama barang : "<<ptr[i]->nama_barang<<endl;
		cout<<"| kondisi barang : "<<ptr[i]->kondisi_barang<<endl;
		cout<<"| harga awal : "<<ptr[i]->harga_awal<<endl;
		cout<<"| harga tertinggi : "<<ptr[i]->harga_tertinggi<<endl;
		cout<<"| tanggal mulai lelang : "<<ptr[i]->tanggal_mulai.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
		cout<<"| tanggal akhir lelang : "<<ptr[i]->tanggal_akhir.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
		cout<<"| kategori barang : "<<ptr[i]->kategori_barang.cat<<endl;
		cout<<"| status : "<<ptr[i]->status<<endl;
		cout<<"|=========================================|"<<endl;
	}
}
	
void urut_Nama(){
	import_data();
	cout<<"|=========================================|"<<endl;
	cout<<"|            APLIKASI LELANG              |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Sorting berdasarkan nama secara :       |"<<endl;
	cout<<"| 1. Ascending                            |"<<endl;
	cout<<"| 2. Descending                           |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"| Menu : ";
	cin>>Menu;
	system("cls");
	if(Menu == 1){
		struct data temp;
		for (i = 0; i < byk +1-1; i++){
			for (int j = 0; j > (byk - 1-i); j++){
        		if (dt[j].nama_barang < dt[j + 1].nama_barang){
	                temp = dt[j];
	                dt[j] = dt[j + 1];
	                dt[j + 1] = temp;
        		} 
    		}
		}
	}	
	else if(Menu == 2){
		struct data temp;
		for (i = 0; i < byk - 1; i++){
			for (int j = 0; j < (byk - 1-i); j++){
        		if (dt[j].nama_barang > dt[j + 1].nama_barang){
	                temp = dt[j];
	                dt[j] = dt[j + 1];
	                dt[j + 1] = temp;
        		} 
    		}
		}
	}
	else{
		cout<<"Invalid Input / Try Again"<<endl;
	}
	system("cls");
	cout<<"|=========================================|"<<endl;
	cout<<"|                APLIKASI LELANG          |"<<endl;
	cout<<"|=========================================|"<<endl;
	for(int i = 0; i<byk;i++){
		// membuat var pointer tadi menjadi address dari struct data dt
		ptr[i] = &dt[i];
		// memanggil sruct data menggunakan pointer
		cout<<"| id barang : "<<ptr[i]->id_barang<<endl;
		cout<<"| nama barang : "<<ptr[i]->nama_barang<<endl;
		cout<<"| kondisi barang : "<<ptr[i]->kondisi_barang<<endl;
		cout<<"| harga awal : "<<ptr[i]->harga_awal<<endl;
		cout<<"| harga tertinggi : "<<ptr[i]->harga_tertinggi<<endl;
		cout<<"| tanggal mulai lelang : "<<ptr[i]->tanggal_mulai.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
		cout<<"| tanggal akhir lelang : "<<ptr[i]->tanggal_akhir.day<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.month<<"/"<<ptr[i]->tanggal_mulai.year<<" "<<ptr[i]->tanggal_mulai.h<<":"<<ptr[i]->tanggal_mulai.m<<endl;
		cout<<"| kategori barang : "<<ptr[i]->kategori_barang.cat<<endl;
		cout<<"| status : "<<ptr[i]->status<<endl;
		cout<<"|=========================================|"<<endl;
	}
}
void Menu_urut(){
		cout<<"|=========================================|"<<endl;
		cout<<"|              APLIKASI LELANG            |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"| Urutkan Data berdasarkan :              |"<<endl;
		cout<<"| 1. Nama                                 |"<<endl;
		cout<<"| 2. Id                                   |"<<endl;
		cout<<"| 3. Tanggal                              |"<<endl;
		cout<<"| 4. Kategori                       		 |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"| Menu : ";
		cin>>Menu;
		
		switch(Menu){
			case 1:
				urut_Nama();
				break;
			case 2:
				urut_Id();
				break;
			case 3:
				urut_Tanggal();
				break;
			case 4:
				urut_Kategori();
				break;
			default :
				cout<<"Invalid Input / try again"<<endl;
				break;
		}
}
// prosedur Menu
void admin_page(){
	while(condition){
		cout<<"|=========================================|"<<endl;
		cout<<"|              APLIKASI LELANG            |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"| 1. Lihat Data Lelang                    |"<<endl;
		cout<<"| 2. Masukkan Data                        |"<<endl;
		cout<<"| 3. Edit Data                            |"<<endl;
		cout<<"| 4. Hapus Data                           |"<<endl;
		cout<<"| 5. Urutkan Data                         |"<<endl;
		cout<<"| 6. Cari Data                            |"<<endl;
		cout<<"| 7. keluar                               |"<<endl;
		cout<<"|=========================================|"<<endl;
		cout<<"| Menu : ";
		cin>>Menu;
		while(std::cin.fail()) {
	        cout << "Error!!, Input harus berupa angka" <<endl;
	        cin.clear();
	        cin.ignore(256,'\n');
	        cin>>Menu;
	        break;
    	}
		system("cls");
		// Melakukan percabangan sesuai data yg diinputkan
		switch(Menu){
			// jika dipilih 1 maka menuju prosedur show
			case 1 :
				show_admin();
				cout<<" tekan Enter untuk Kembali....."<<endl;
				getch();
				system("cls");
				break;
			// jika dipilih 2 maka menuju prosedur add
			case 2 :
				add_admin();
				break;
			//jika dipilih 3 maka menuju prosedur edit
			case 3:
				edit_admin();
				break;
			// jika dipilih 4 maka menuju prosedur del
			case 4:
				del_admin();
				break;
			case 5:
				Menu_urut();
				break;
			case 6:
				Cari_data();
				break;
			case 7:
				cout<<"Terimakasih Telah Menggunakan Aplikasi Ini..... :)"<<endl;
				condition = false;
				break;	
			// jika yg inputan salah
			default :
				cout<<"Invalid Input / try again"<<endl;
				break;
		}
	}
}
void show_user(){
	import_data();
	
	//jika sturct ada isinya maka akan muncul sesuai yg diinputkan
		for(int k = 0; k<byk;k++){
			ptr[k] = &dt[k];
			if(ptr[k]->status == "Dibuka"){
			// membuat var pointer tadi menjadi address dari struct data dt
				// memanggil sruct data menggunakan pointer
				cout<<"| nama barang : "<<ptr[k]->nama_barang<<endl;
				cout<<"| kondisi barang : "<<ptr[k]->kondisi_barang<<endl;
				cout<<"| harga awal : "<<ptr[k]->harga_awal<<endl;
				cout<<"| harga tertinggi : "<<ptr[k]->harga_tertinggi<<endl;
				cout<<"| tanggal mulai lelang : "<<ptr[k]->tanggal_mulai.day<<"/"<<ptr[k]->tanggal_mulai.month<<"/"<<ptr[k]->tanggal_mulai.year<<" "<<ptr[k]->tanggal_mulai.h<<":"<<ptr[k]->tanggal_mulai.m<<endl;
				cout<<"| tanggal akhir lelang : "<<ptr[k]->tanggal_akhir.day<<"/"<<ptr[k]->tanggal_akhir.month<<"/"<<ptr[k]->tanggal_akhir.month<<"/"<<ptr[k]->tanggal_akhir.year<<" "<<ptr[k]->tanggal_akhir.h<<":"<<ptr[k]->tanggal_akhir.m<<endl;
				cout<<"| kategori barang : "<<ptr[k]->kategori_barang.cat<<endl;
				cout<<"| status : "<<ptr[k]->status<<endl;
				cout<<"| Jumlah user : "<<ptr[k]->jml_user<<endl;
				cout<<"|*************************************************************|"<<endl;
			}
		}
}
void history(int user){
	import_history(ak[user].username);
	cout<<"|=============================================================|"<<endl;
	cout<<"|                Selamat Datang Di Aplikasi Lelang            |"<<endl;
	cout<<"|=============================================================|"<<endl;
	cout<<"|                          History                            |"<<endl;
	for(int k = 0; k<byk_user;k++){
		// membuat var pointer tadi menjadi address dari struct data dt
		// memanggil sruct data menggunakan pointer
		cout<<"| nama barang : "<<acc.user_barang[k].nama_barang<<endl;
		cout<<"| kondisi barang : "<<acc.user_barang[k].kondisi_barang<<endl;
		cout<<"| harga awal : "<<acc.user_barang[k].harga_awal<<endl;
		cout<<"| harga tertinggi : "<<acc.user_barang[k].harga_tertinggi<<endl;
		cout<<"| tanggal mulai lelang : "<<acc.user_barang[k].tanggal_mulai.day<<"/"<<acc.user_barang[k].tanggal_mulai.month<<"/"<<acc.user_barang[k].tanggal_mulai.year<<" "<<acc.user_barang[k].tanggal_mulai.h<<":"<<acc.user_barang[k].tanggal_mulai.m<<endl;
		cout<<"| tanggal akhir lelang : "<<acc.user_barang[k].tanggal_akhir.day<<"/"<<acc.user_barang[k].tanggal_akhir.month<<"/"<<acc.user_barang[k].tanggal_akhir.month<<"/"<<acc.user_barang[k].tanggal_akhir.year<<" "<<acc.user_barang[k].tanggal_akhir.h<<":"<<acc.user_barang[k].tanggal_akhir.m<<endl;
		cout<<"| kategori barang : "<<acc.user_barang[k].kategori_barang.cat<<endl;
		cout<<"| status : "<<acc.user_barang[k].status<<endl;
		cout<<"|*************************************************************|"<<endl;
	}
	getch();
	system("cls");
}
int lelang_user(int user){
	import_history(ak[user].username);
	int line=0;
	bool flag;
	int indek;
	int harga;
	string str_line;
	cout<<"|=========================================|"<<endl;
	cout<<"|              APLIKASI LELANG            |"<<endl;
	cout<<"|=========================================|"<<endl;
	show_user();
	while(true){
		cout<<"|Silahkan Pilih barang yang ingin          "<<endl;
		cout<<"|Dilelang : ";
		getline(cin>>ws,cari);
		for(int k = 0; k<byk;k++){
			if(dt[k].nama_barang == cari ){
				flag = true;
				indek = k;
				break;
			}
			
		}
			if(flag == true &&  dt[indek].status == "Dibuka"){
				system("cls");
				cout<<"|=========================================|"<<endl;
				cout<<"|              APLIKASI LELANG            |"<<endl;
				cout<<"|=========================================|"<<endl;
				cout<<"| id barang : "<<ptr[indek]->id_barang<<endl;
				cout<<"| nama barang : "<<ptr[indek]->nama_barang<<endl;
				cout<<"| kondisi barang : "<<ptr[indek]->kondisi_barang<<endl;
				cout<<"| harga awal : "<<ptr[indek]->harga_awal<<endl;
				cout<<"| harga tertinggi : "<<ptr[indek]->harga_tertinggi<<endl;
				cout<<"| tanggal mulai lelang : "<<ptr[indek]->tanggal_mulai.day<<"/"<<ptr[indek]->tanggal_mulai.month<<"/"<<ptr[indek]->tanggal_mulai.year<<" "<<ptr[indek]->tanggal_mulai.h<<":"<<ptr[indek]->tanggal_mulai.m<<endl;
				cout<<"| tanggal akhir lelang : "<<ptr[indek]->tanggal_akhir.day<<"/"<<ptr[indek]->tanggal_mulai.month<<"/"<<ptr[indek]->tanggal_mulai.month<<"/"<<ptr[indek]->tanggal_mulai.year<<" "<<ptr[indek]->tanggal_mulai.h<<":"<<ptr[indek]->tanggal_mulai.m<<endl;
				cout<<"| kategori barang : "<<ptr[indek]->kategori_barang.cat<<endl;
				cout<<"| status : "<<ptr[indek]->status<<endl;
				cout<<"|=========================================|"<<endl;
				while(true){
					cout<<"| Masukkan Harga : ";
					cin>>harga;
					if(ptr[indek]->harga_tertinggi == 0){
						if(harga <= ptr[indek]->harga_awal){
							cout<<"Harga Harus diatas Rp."<<ptr[indek]->harga_awal<<endl;
						}
						else{
							Data.open("Data_lelang.txt", ios::trunc);
							history_user.open("user_"+ak[user].username+".txt",ios::trunc);
							user_data.open("user_data.txt",ios::trunc);
							Data.close();
							user_data.close();
							history_user.close();
							
							ak[user].id_user = ak[user].id_user;
							ak[user].username = ak[user].username;
							ak[user].nama = ak[user].nama;
							ak[user].alamat = ak[user].alamat;
							ak[user].password = ak[user].password;
							ak[user].history = ak[user].history+1;
							
							acc.id_user = ak[user].id_user;
							acc.username = ak[user].username;
							acc.nama = ak[user].nama;
							acc.alamat = ak[user].alamat;
							acc.password = ak[user].password;
							acc.history = ak[user].history+1;
							
							ptr[indek]->id_barang = ptr[indek]->id_barang;
							ptr[indek]->nama_barang = ptr[indek]->nama_barang;
							ptr[indek]->kondisi_barang = ptr[indek]->kondisi_barang;
							ptr[indek]->harga_awal = ptr[indek]->harga_awal;
							ptr[indek]->harga_tertinggi = harga;
							ptr[indek]->tanggal_mulai.day;ptr[indek]->tanggal_mulai.month;ptr[indek]->tanggal_mulai.year;ptr[indek]->tanggal_mulai.h;ptr[indek]->tanggal_mulai.m = ptr[indek]->tanggal_mulai.day;ptr[indek]->tanggal_mulai.month;ptr[indek]->tanggal_mulai.year;ptr[indek]->tanggal_mulai.h;ptr[indek]->tanggal_mulai.m;
							ptr[indek]->tanggal_akhir.day;ptr[indek]->tanggal_akhir.month;ptr[indek]->tanggal_akhir.year;ptr[indek]->tanggal_akhir.h;ptr[indek]->tanggal_akhir.m = ptr[indek]->tanggal_akhir.day;ptr[indek]->tanggal_akhir.month;ptr[indek]->tanggal_akhir.year;ptr[indek]->tanggal_akhir.h;ptr[indek]->tanggal_akhir.m;
							ptr[indek]->kategori_barang.cat = ptr[indek]->kategori_barang.cat;
							ptr[indek]->status = ptr[indek]->status;
							ptr[indek]->user_terakhir = ak[user].username;
							ptr[indek]->jml_user = ptr[indek]->jml_user+1;
							
							acc.user_barang[indek].id_barang = ptr[indek]->id_barang;
							acc.user_barang[indek].nama_barang = ptr[indek]->nama_barang;
							acc.user_barang[indek].kondisi_barang = ptr[indek]->kondisi_barang;
							acc.user_barang[indek].harga_awal = ptr[indek]->harga_awal;
							acc.user_barang[indek].harga_tertinggi = harga;
							acc.user_barang[indek].tanggal_mulai.day = ptr[indek]->tanggal_mulai.day;acc.user_barang[indek].tanggal_mulai.month = ptr[indek]->tanggal_mulai.month;acc.user_barang[indek].tanggal_mulai.year = ptr[indek]->tanggal_mulai.year;acc.user_barang[indek].tanggal_mulai.h = ptr[indek]->tanggal_mulai.h;acc.user_barang[indek].tanggal_mulai.m = ptr[indek]->tanggal_mulai.m;
							acc.user_barang[indek].tanggal_akhir.day = ptr[indek]->tanggal_akhir.day;acc.user_barang[indek].tanggal_akhir.month = ptr[indek]->tanggal_mulai.month;acc.user_barang[indek].tanggal_akhir.year = ptr[indek]->tanggal_akhir.year;acc.user_barang[indek].tanggal_akhir.h = ptr[indek]->tanggal_akhir.h;acc.user_barang[indek].tanggal_akhir.m = ptr[indek]->tanggal_akhir.m;
							acc.user_barang[indek].kategori_barang.cat = ptr[indek]->kategori_barang.cat;
							acc.user_barang[indek].status = ptr[indek]->status;
							acc.user_barang[indek].user_terakhir = ak[user].username;
							acc.user_barang[indek].jml_user = acc.user_barang[indek].jml_user+ 1;
							Data.open("Data_lelang.txt",ios::out);
							history_user.open("user_"+ak[user].username+".txt",ios::out);
							user_data.open("user_data.txt",ios::out);
							byk_user = byk_user+1;
							for(int k =0;k<all_user;k++){
								user_data<<ak[k].id_user<<","<<ak[k].username<<","<<ak[k].nama<<","<<ak[k].password<<","<<ak[k].alamat<<","<<ak[k].history<<endl;
							}
							history_user<<acc.id_user<<"\n"<<acc.username<<"\n"<<acc.nama<<"\n"<<acc.password<<"\n"<<acc.alamat<<"\n"<<acc.history<<endl;
							for(int k =0; k<byk_user;k++){
								history_user<<acc.user_barang[k].id_barang<<"," << acc.user_barang[k].nama_barang << ","<<acc.user_barang[k].kondisi_barang<<","<<acc.user_barang[k].harga_awal<<","<<acc.user_barang[k].harga_tertinggi<<","<<acc.user_barang[k].tanggal_mulai.day<<"/"<<acc.user_barang[k].tanggal_mulai.month<<"/"<<acc.user_barang[k].tanggal_mulai.year<<" "<<acc.user_barang[k].tanggal_mulai.h<< ":"<<acc.user_barang[k].tanggal_mulai.m<<",";
					    		history_user<<acc.user_barang[k].tanggal_akhir.day<<"/"<<acc.user_barang[k].tanggal_akhir.month<<"/"<<acc.user_barang[k].tanggal_akhir.year<<" "<<acc.user_barang[k].tanggal_akhir.h<<":"<<acc.user_barang[k].tanggal_akhir.m<<","<<acc.user_barang[k].kategori_barang.cat<<","<<acc.user_barang[k].status<<","<<acc.user_barang[k].user_terakhir<<","<<acc.user_barang[k].jml_user<<endl;
							}
							for(int k = 0; k<byk;k++){
								Data<<ptr[k]->id_barang<<"," << ptr[k]->nama_barang << ","<<ptr[k]->kondisi_barang<<","<<ptr[k]->harga_awal<<","<<ptr[k]->harga_tertinggi<<","<<ptr[k]->tanggal_mulai.day<<"/"<<ptr[k]->tanggal_mulai.month<<"/"<<ptr[k]->tanggal_mulai.year<<" "<<ptr[k]->tanggal_mulai.h<< ":"<<ptr[k]->tanggal_mulai.m<<",";
					    		Data<<ptr[k]->tanggal_akhir.day<<"/"<<ptr[k]->tanggal_akhir.month<<"/"<<ptr[k]->tanggal_akhir.year<<" "<<ptr[k]->tanggal_akhir.h<<":"<<ptr[k]->tanggal_akhir.m<<","<<ptr[k]->kategori_barang.cat<<","<<ptr[k]->status<<","<<ptr[k]->user_terakhir<<","<<ptr[k]->jml_user<<endl;
					    	}
							cout<<"| Harga Berhasil Dimasukkan "<<endl;
							Data.close();
							history_user.close();
							user_data.close();
							break;
							getch();
							system("cls");
						}
						
					}
					else{
						if(harga <= ptr[indek]->harga_tertinggi){
							cout<<"Harga Harus diatas Rp."<<ptr[indek]->harga_tertinggi<<endl;
						}
						else{
							Data.open("Data_lelang.txt", ios::trunc);
							history_user.open("user_"+ak[user].username+".txt",ios::trunc);
							user_data.open("user_data.txt",ios::trunc);
							Data.close();
							user_data.close();
							history_user.close();
							
							ak[user].id_user = ak[user].id_user;
							ak[user].username = ak[user].username;
							ak[user].nama = ak[user].nama;
							ak[user].alamat = ak[user].alamat;
							ak[user].password = ak[user].password;
							ak[user].history = ak[user].history+1;
							
							acc.id_user = ak[user].id_user;
							acc.username = ak[user].username;
							acc.nama = ak[user].nama;
							acc.alamat = ak[user].alamat;
							acc.password = ak[user].password;
							acc.history = ak[user].history+1;
							
							ptr[indek]->id_barang = ptr[indek]->id_barang;
							ptr[indek]->nama_barang = ptr[indek]->nama_barang;
							ptr[indek]->kondisi_barang = ptr[indek]->kondisi_barang;
							ptr[indek]->harga_awal = ptr[indek]->harga_awal;
							ptr[indek]->harga_tertinggi = harga;
							ptr[indek]->tanggal_mulai.day;ptr[indek]->tanggal_mulai.month;ptr[indek]->tanggal_mulai.year;ptr[indek]->tanggal_mulai.h;ptr[indek]->tanggal_mulai.m = ptr[indek]->tanggal_mulai.day;ptr[indek]->tanggal_mulai.month;ptr[indek]->tanggal_mulai.year;ptr[indek]->tanggal_mulai.h;ptr[indek]->tanggal_mulai.m;
							ptr[indek]->tanggal_akhir.day;ptr[indek]->tanggal_akhir.month;ptr[indek]->tanggal_akhir.year;ptr[indek]->tanggal_akhir.h;ptr[indek]->tanggal_akhir.m = ptr[indek]->tanggal_akhir.day;ptr[indek]->tanggal_akhir.month;ptr[indek]->tanggal_akhir.year;ptr[indek]->tanggal_akhir.h;ptr[indek]->tanggal_akhir.m;
							ptr[indek]->kategori_barang.cat = ptr[indek]->kategori_barang.cat;
							ptr[indek]->status = ptr[indek]->status;
							ptr[indek]->user_terakhir = ak[user].username;
							
							acc.user_barang[indek].id_barang = ptr[indek]->id_barang;
							acc.user_barang[indek].nama_barang = ptr[indek]->nama_barang;
							acc.user_barang[indek].kondisi_barang = ptr[indek]->kondisi_barang;
							acc.user_barang[indek].harga_awal = ptr[indek]->harga_awal;
							acc.user_barang[indek].harga_tertinggi = harga;
							acc.user_barang[indek].tanggal_mulai.day = ptr[indek]->tanggal_mulai.day;acc.user_barang[indek].tanggal_mulai.month = ptr[indek]->tanggal_mulai.month;acc.user_barang[indek].tanggal_mulai.year = ptr[indek]->tanggal_mulai.year;acc.user_barang[indek].tanggal_mulai.h = ptr[indek]->tanggal_mulai.h;acc.user_barang[indek].tanggal_mulai.m = ptr[indek]->tanggal_mulai.m;
							acc.user_barang[indek].tanggal_akhir.day = ptr[indek]->tanggal_akhir.day;acc.user_barang[indek].tanggal_akhir.month = ptr[indek]->tanggal_mulai.month;acc.user_barang[indek].tanggal_akhir.year = ptr[indek]->tanggal_akhir.year;acc.user_barang[indek].tanggal_akhir.h = ptr[indek]->tanggal_akhir.h;acc.user_barang[indek].tanggal_akhir.m = ptr[indek]->tanggal_akhir.m;
							acc.user_barang[indek].kategori_barang.cat = ptr[indek]->kategori_barang.cat;
							acc.user_barang[indek].status = ptr[indek]->status;
							acc.user_barang[indek].user_terakhir = ak[user].username;
							Data.open("Data_lelang.txt",ios::out);
							history_user.open("user_"+ak[user].username+".txt",ios::out);
							user_data.open("user_data.txt",ios::out);
							byk_user = byk_user;
							for(int k =0;k<all_user;k++){
								user_data<<ak[k].id_user<<","<<ak[k].username<<","<<ak[k].nama<<","<<ak[k].password<<","<<ak[k].alamat<<","<<ak[k].history<<endl;
							}
							history_user<<acc.id_user<<"\n"<<acc.username<<"\n"<<acc.nama<<"\n"<<acc.password<<"\n"<<acc.alamat<<"\n"<<acc.history<<endl;
							for(int k =0; k<byk_user;k++){
								history_user<<acc.user_barang[k].id_barang<<"," << acc.user_barang[k].nama_barang << ","<<acc.user_barang[k].kondisi_barang<<","<<acc.user_barang[k].harga_awal<<","<<acc.user_barang[k].harga_tertinggi<<","<<acc.user_barang[k].tanggal_mulai.day<<"/"<<acc.user_barang[k].tanggal_mulai.month<<"/"<<acc.user_barang[k].tanggal_mulai.year<<" "<<acc.user_barang[k].tanggal_mulai.h<< ":"<<acc.user_barang[k].tanggal_mulai.m<<",";
					    		history_user<<acc.user_barang[k].tanggal_akhir.day<<"/"<<acc.user_barang[k].tanggal_akhir.month<<"/"<<acc.user_barang[k].tanggal_akhir.year<<" "<<acc.user_barang[k].tanggal_akhir.h<<":"<<acc.user_barang[k].tanggal_akhir.m<<","<<acc.user_barang[k].status<<","<<acc.user_barang[k].kategori_barang.cat<<","<<acc.user_barang[k].user_terakhir<<","<<acc.user_barang[k].jml_user<<endl;
							}
							
							for(int k = 0; k<byk;k++){
								Data<<ptr[k]->id_barang<<"," << ptr[k]->nama_barang << ","<<ptr[k]->kondisi_barang<<","<<ptr[k]->harga_awal<<","<<ptr[k]->harga_tertinggi<<","<<ptr[k]->tanggal_mulai.day<<"/"<<ptr[k]->tanggal_mulai.month<<"/"<<ptr[k]->tanggal_mulai.year<<" "<<ptr[k]->tanggal_mulai.h<< ":"<<ptr[k]->tanggal_mulai.m<<",";
					    		Data<<ptr[k]->tanggal_akhir.day<<"/"<<ptr[k]->tanggal_akhir.month<<"/"<<ptr[k]->tanggal_akhir.year<<" "<<ptr[k]->tanggal_akhir.h<<":"<<ptr[k]->tanggal_akhir.m<<","<<ptr[k]->status<<","<<ptr[k]->kategori_barang.cat<<","<<ptr[k]->user_terakhir<<","<<ptr[k]->jml_user<<endl;	
							}
							cout<<"| Harga Berhasil Dimasukkan "<<endl;
							Data.close();
							user_data.close();
							history_user.close();
							break;
							getch();
							system("cls");
						}
					}
			}
		break;
		}
		else if (flag == false ){
			cout<<"| Nama tidak ada coba Lagi"<<endl;
			getch();
		}
		else if(flag == true && dt[indek].status == "Ditutup"){
			cout<<"| Barang di cari sudah dilelang, silahkan cari barang yg lain "<<endl;
			getch();
		}
	}
}



void lihat_account_user(int user){
	import_all_user();
	cout<<"|=============================================================|"<<endl;
	cout<<"|                Selamat Datang Di Aplikasi Lelang            |"<<endl;
	cout<<"|=============================================================|"<<endl;
	cout<<"| username : "<<ak[user].username<<endl;
	cout<<"| Nama : "<<ak[user].nama<<endl;
	cout<<"| alamat : "<<ak[user].alamat<<endl;
	cout<<"|=============================================================|"<<endl;
	getch();
	system("cls");
} 

void user_page(int user){
	while(condition){
		cout<<"|=============================================================|"<<endl;
		cout<<"|                Selamat Datang Di Aplikasi Lelang            |"<<endl;
		cout<<"|=============================================================|"<<endl;
		cout<<"| Selamat Datang "<<ak[user].username<<endl;
		cout<<"| Silahkan Pilih Menu Berikut : "<<endl;
		cout<<"| 1. Lelang "<<endl;
		cout<<"| 2. History "<<endl;
		cout<<"| 3. Lihat Account "<<endl;
		cout<<"| 4. Logout "<<endl;
		cout<<"|=============================================================|"<<endl;
		cout<<"| Menu : ";
		cin>>Menu;
		while(std::cin.fail()) {
        cout << "Error!! Input harus berupa angka" <<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"| Menu : ";
        cin >> Menu;
    	}
		system("cls");
		switch(Menu){
			case 1 :
				lelang_user(user);
				break;
			case 2 :
				history(user);
				break;
			case 3 :
				lihat_account_user(user);
				break;
			case 4 :
				cout<<"Terimakasih Telah Menggunakan Aplikasi Lelang..... :)"<<endl;
				cout<<"Sayonara"<<endl;
				condition = false;
				getch();
				system("cls");
				break;
			default :
				cout<<"Invalid Input / try again"<<endl;
				break;
		}
	}
}

void login(){
	import_all_user();
	int user;
	char ch;
	string logusername, logpass;
	cout<<"|=========================================|"<<endl;
	cout<<"|              APLIKASI LELANG            |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"|                  Login                  |"<<endl;
	cout<<"| Masukkan  Username : ";
	cin>>logusername;
	cout<<"| Masukkan Password : ";
	ch = _getch();
	while(ch!=13){
		logpass.push_back(ch);
		cout<<'*';
		ch =_getch();
	}
	if(logusername != "admin" && logpass != "admin123"){
		for(int k=0;k<all_user;k++){
			if(logusername == ak[k].username && logpass == ak[k].password){
				user = k;
				flag = true;
				break;
			}
			
		}
		if(flag== 1){
			getch();
			system("cls");
			condition = true;
			user_page(user);
		}
		else{
			cout<<"Username / Password salah, Silahkan coba lagi"<<endl;
			getch();
			system("cls");
		}
	}
	else{
		system("cls");
		condition = true;
		admin_page();
	}		
}

void reg(){
	import_all_user();
	all_user = i;
	cout<<"|=========================================|"<<endl;
	cout<<"|              APLIKASI LELANG            |"<<endl;
	cout<<"|=========================================|"<<endl;
	cout<<"|                  Register               |"<<endl;
	ak[i].id_user = all_user;
	cout<<"| username : ";
	getline(cin>>ws,ak[i].username);
	cout<<"| nama : ";
	getline(cin>>ws,ak[i].nama);
	cout<<"| password : ";
	cin>>ak[i].password;
	cout<<"| alamat : ";
	getline(cin>>ws,ak[i].alamat);
	ak[i].history = 0;
	ak[i].save_file_user();
	getch();
	system("cls");
}

void awal(){
	cout<<"|=============================================================|"<<endl;
	cout<<"|                Selamat Datang Di Aplikasi Lelang            |"<<endl;
	cout<<"|=============================================================|"<<endl;
	show_user();
	cout<<"| jika ingin melelang silahkan login jika belum silahkan      |"<<endl;
	cout<<"| Sign up.                                                    |"<<endl;
	cout<<"| 1. Login                                                    |"<<endl;
	cout<<"| 2. Sign up                                                  |"<<endl;
	cout<<"| 3. Keluar                                                   |"<<endl;
	cout<<"|=============================================================|"<<endl;
	cout<<"| Menu : ";
	cin>>Menu;
	while(std::cin.fail()) {
        cout << "Error!!, Input harus berupa angka" <<endl;
        cin.clear();
        cin.ignore(256,'\n');
        cout<<"| Menu : ";
        cin>>Menu;
        break;
    }
    system("cls");
	switch(Menu){
		case 1:
			login();
			break;
		case 2:
			reg();
			break;
		case 3:
			cout<<"Terima Kasih telah Menggunakan Aplikasi Lelang "<<endl;
			exit(0);
		default :
			cout<<"Invalid Input / try again"<<endl;		
			break;	
	}
	
}

int main(){
	while(true){
	awal();
	}
} 
