

#include <iostream>
#include <cstring>
#include <vector>
#include <fstream>
using namespace std;

struct Hotel {
  
    int stars;
    string address;
    int availableRooms; 
    int staffCount;    
     string maKhachSan;   
    string tenKhachSan;   
    int soSao;
    string diaChi;        
    int soPhongTrong;     
    int soNhanVien;       
    string name;
    Hotel* next;
    Hotel* prev;    
};
struct HotelList {
    Hotel* head;
    Hotel* tail;
};
Hotel* timTheoMa(HotelList& danhSachKhachSan, const string& maKhachSan);
struct Booking {
    string customerName;
    int age;
    string cccd;
    int numOfRooms;
    int numOfNights;
    Hotel* hotel;
    bool isBookingSuccessful; 
};
Hotel* taoKhachSan(string maKhachSan, string ten, int soSao, string diaChi, int soPhongTrong, int soNhanVien) {
    Hotel* khachSanMoi = new Hotel;
    khachSanMoi->maKhachSan = maKhachSan;
    khachSanMoi->name = ten;
    khachSanMoi->stars = soSao;
    khachSanMoi->address = diaChi;
    khachSanMoi->availableRooms = soPhongTrong;
    khachSanMoi->staffCount = soNhanVien;
    khachSanMoi->next = NULL;
    khachSanMoi->prev = NULL;
    return khachSanMoi;
}
void themKhachSan(HotelList& danhSachKhachSan, Hotel* khachSanMoi) {
    if (!danhSachKhachSan.head) {
        danhSachKhachSan.head = khachSanMoi;
        danhSachKhachSan.tail = khachSanMoi;
    } else {
        khachSanMoi->prev = danhSachKhachSan.tail;
        danhSachKhachSan.tail->next = khachSanMoi;
        danhSachKhachSan.tail = khachSanMoi;
    }
}
void hienThiKhachSan(Hotel* khachSan) {
    cout << "Ma Khach San: " << khachSan->maKhachSan
         << "- Ten: " << khachSan->name << "- So sao: " << khachSan->stars
         << "- Dia Chi: " << khachSan->address
         << "- Phong Trong: " << khachSan->availableRooms
         << "- Nhan Vien Phuc Vu: " << khachSan->staffCount << endl;
}
void sapXepTheoSao(HotelList& danhSachKhachSan) {
    for (Hotel* i = danhSachKhachSan.head; i != NULL; i = i->next) {
        for (Hotel* j = danhSachKhachSan.head; j != NULL; j = j->next) {
            if (i->stars < j->stars) {
                swap(i->stars, j->stars);
                swap(i->name, j->name);
                swap(i->address, j->address);
                swap(i->availableRooms, j->availableRooms);
                swap(i->staffCount, j->staffCount);
            }
        }
    }
}
void hienThiDanhSachKhachSan(HotelList& danhSachKhachSan) {
    cout << "Danh sach khach san:" << endl;
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != NULL; hienTai = hienTai->next) {
        hienThiKhachSan(hienTai);
    }
}
void datPhong(HotelList& danhSachKhachSan, Booking& booking) {
    do {
      
        int luaChonKhachSan;
        string maKhachSan; 
        cout << " Ban chac chan voi lua chon cua minh ? Nhap lai ma khach san  : ";
        cin >> maKhachSan;
        Hotel* khachSanDuocChon = timTheoMa(danhSachKhachSan, maKhachSan);
        if (khachSanDuocChon) {
            booking.hotel = khachSanDuocChon;
            cout << "Nhap so phong muon dat: ";
            cin >> booking.numOfRooms;
            cout << "Nhap so dem muon dat phong: ";
            cin >> booking.numOfNights;
            if (booking.hotel->availableRooms >= booking.numOfRooms) {
                cout << "Dat phong thanh cong cho khach san :" << booking.hotel->name
                     << " -cho : " << booking.customerName
                     << "- So dem: " << booking.numOfNights
                     << "- So phong: " << booking.numOfRooms << endl;
                booking.hotel->availableRooms -= booking.numOfRooms;
                booking.isBookingSuccessful = true;
            } else {
                cout << "Khong du phong tai khach san " << booking.hotel->name << ". Vui long chon khach san khac." << endl;
                booking.isBookingSuccessful = false;
            }
        } else {
            cout << "Khong tim thay khach san theo lua chon." << endl;
            booking.isBookingSuccessful = false;
        }

    } while (!booking.isBookingSuccessful);
}
void hienThiDanhSachBooking(const vector<Booking>& danhSachBooking) {
    cout << "Danh sach booking:" << endl;
    for (const Booking& booking : danhSachBooking) {
        cout << "Khach hang: " << booking.customerName
             << "- Tuoi: " << booking.age
             << "- CCCD: " << booking.cccd
             << "- So dem: " << booking.numOfNights
             << "- So phong: " << booking.numOfRooms
             << "- Khach san: " << booking.hotel->name;
        
        if (!booking.isBookingSuccessful) {
            cout << " (Dat phong khong thanh cong)";
        }

        cout << endl;
    }
}
void themKhachSanVaoDau(HotelList& danhSachKhachSan, Hotel* khachSanMoi) {
    khachSanMoi->next = danhSachKhachSan.head;
    khachSanMoi->prev = nullptr;

    if (danhSachKhachSan.head) {
        danhSachKhachSan.head->prev = khachSanMoi;
    } else {
        danhSachKhachSan.tail = khachSanMoi;
    }

    danhSachKhachSan.head = khachSanMoi;
}
void themKhachSanSauViTri(HotelList& danhSachKhachSan, Hotel* khachSanMoi, int viTri) {
    if (viTri < 0) {
        cout << "Vi tri khong hop le." << endl;
        return;
    }
    Hotel* hienTai = danhSachKhachSan.head;
    for (int i = 0; i < viTri && hienTai; ++i) {
        hienTai = hienTai->next;
    }

    if (!hienTai) {
        cout << "Khong tim thay vi tri trong danh sach." << endl;
        return;
    }
    khachSanMoi->prev = hienTai;
    khachSanMoi->next = hienTai->next;

    if (hienTai->next) {
        hienTai->next->prev = khachSanMoi;
    } else {
        danhSachKhachSan.tail = khachSanMoi;
    }
    hienTai->next = khachSanMoi;
}
void xoaKhachSanTheoMa(HotelList& danhSachKhachSan, const string& maKhachSan) {
    Hotel* hienTai = danhSachKhachSan.head;
    while (hienTai) {
        if (hienTai->maKhachSan == maKhachSan) {
            if (hienTai->prev) {
                hienTai->prev->next = hienTai->next;
            } else {
                danhSachKhachSan.head = hienTai->next;
            }
            if (hienTai->next) {
                hienTai->next->prev = hienTai->prev;
            } else {
                danhSachKhachSan.tail = hienTai->prev;
            }
            delete hienTai;
            cout << "Da xoa khach san co ma " << maKhachSan << endl;
            return;
        }
        hienTai = hienTai->next;
    }
    cout << "Khong tim thay khach san voi ma " << maKhachSan << endl;
}
void xoaKhachSanTheoTen(HotelList& danhSachKhachSan, const string& tenKhachSan) {
    Hotel* hienTai = danhSachKhachSan.head;
    while (hienTai) {
        if (hienTai->tenKhachSan == tenKhachSan) {
            if (hienTai->prev) {
                hienTai->prev->next = hienTai->next;
            } else {
                danhSachKhachSan.head = hienTai->next;
            }
            if (hienTai->next) {
                hienTai->next->prev = hienTai->prev;
            } else {
                danhSachKhachSan.tail = hienTai->prev;
            }
            delete hienTai;
            cout << "Da xoa khach san co ten " << tenKhachSan << endl;
            return;
        }
        hienTai = hienTai->next;
    }
    cout << "Khong tim thay khach san voi ten " << tenKhachSan << endl;
}
void xoaPhanTuTaiViTri(HotelList& danhSachKhachSan, int viTri) {
    if (viTri < 0) {
        cout << "Vi tri khong hop le." << endl;
        return;
    }
    Hotel* hienTai = danhSachKhachSan.head;
    for (int i = 1; i < viTri && hienTai; ++i) {
        hienTai = hienTai->next;
    }
    if (!hienTai) {
        cout << "Khong tim thay vi tri trong danh sach." << endl;
        return;
    }
    if (hienTai->prev) {
        hienTai->prev->next = hienTai->next;
    } else {
        danhSachKhachSan.head = hienTai->next;
    }
    if (hienTai->next) {
        hienTai->next->prev = hienTai->prev;
    } else {
        danhSachKhachSan.tail = hienTai->prev;
    }
    delete hienTai;
    cout << "Da xoa phan tu tai vi tri " << viTri << endl;
}
int demTheoTieuChi(HotelList& danhSachKhachSan, int tieuChi) {
    int count = 0;

    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        if (hienTai->soSao == tieuChi) {
            count++;
        }
    }
    return count;
}
Hotel* timTheoMa(HotelList& danhSachKhachSan, const string& maKhachSan) {
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        if (hienTai->maKhachSan == maKhachSan) {
            return hienTai;
        }
    }
    return nullptr; 
}
void hienThiDanhSachTheoKhoang(HotelList& danhSachKhachSan, int gioiHanDuoi, int gioiHanTren) {
    cout << "Danh sach khach san trong khoang " << gioiHanDuoi << " den " << gioiHanTren << " sao:" << endl;

    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        if (hienTai->soSao >= gioiHanDuoi && hienTai->soSao <= gioiHanTren) {
            hienThiKhachSan(hienTai);
        }
    }
}
Hotel* timTheoTen(HotelList& danhSachKhachSan, const string& tenKhachSan) {
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        if (hienTai->tenKhachSan == tenKhachSan) {
            return hienTai;
        }
    }

    return nullptr; 
}
void ghiDanhSachVaoTep(HotelList& danhSachKhachSan, const vector<Booking>& danhSachBooking, const string& tenTep) {
    ofstream outFile(tenTep);
    outFile << "Ma khach san:";
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        outFile << hienTai->maKhachSan << endl;
    }

    outFile << "Ten khach san:";
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        outFile << hienTai->name << endl;
    }

    outFile << "So sao:";
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        outFile << hienTai->stars << endl;
    }

    outFile << "Dia chi:";
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        outFile << hienTai->address << endl;
    }

    outFile << "So phong trong:";
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        outFile << hienTai->availableRooms << endl;
    }

    outFile << "So nhan vien:";
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        outFile << hienTai->staffCount << endl;
    }
    outFile << endl;

    outFile << "Danh sach booking:";
    for (const Booking& booking : danhSachBooking) {
        outFile << "Ten khach hang: " << booking.customerName << endl;
        outFile << "Tuoi: " << booking.age << endl;
        outFile << "CCCD: " << booking.cccd << endl;
        outFile << "So phong: " << booking.numOfRooms << endl;
        outFile << "So dem dat: " << booking.numOfNights << endl;
        outFile << "Ten khach san: " << booking.hotel->name << endl;
        outFile << "Dat phong : " << (booking.isBookingSuccessful ? "Thanh cong" : "Khong thanh cong") << endl;
        outFile << endl;
    }

    outFile.close();
    cout << "Da ghi danh sach vao tep " << tenTep << endl;
}



void sapXepTheoTruong(HotelList& danhSachKhachSan, bool tangDan) {
    for (Hotel* i = danhSachKhachSan.head; i != nullptr; i = i->next) {
        for (Hotel* j = danhSachKhachSan.head; j != nullptr; j = j->next) {
            if ((tangDan && i->soSao < j->soSao) || (!tangDan && i->soSao > j->soSao)) {
                swap(i->soSao, j->soSao);
            }
        }
    }
}
int timVaXacDinhViTri(HotelList& danhSachKhachSan, const string& maKhachSan) {
    int viTri = 0;
    for (Hotel* hienTai = danhSachKhachSan.head; hienTai != nullptr; hienTai = hienTai->next) {
        if (hienTai->maKhachSan == maKhachSan) {
            return viTri;
        }

        viTri++;
    }
    return -1;
}
void capNhatThongTinKhachSan(Hotel* khachSan) {
    cout << "Nhap thong tin moi cho khach san " << khachSan->name << ":" << endl;
    cout << "Nhap ten khach san: ";
    cin >> khachSan->name;
    cout << "Nhap dia chi cho khach san: ";
    cin.ignore(); 
    getline(cin, khachSan->address);
    cout << "Nhap so sao cho khach san: ";
    cin >> khachSan->stars;
    cout << "Nhap so phong trong cho khach san: ";
    cin >> khachSan->availableRooms;
    cout << "Nhap so nhan vien phuc vu cho khach san: ";
    cin >> khachSan->staffCount;
}
int main() {
     HotelList danhSachKhachSan;
    danhSachKhachSan.head = NULL;
    danhSachKhachSan.tail = NULL;
    vector<Booking> danhSachBooking;
    int luaChon;
    do {        
                cout << "____ MENU CHUONG TRINH QUAN LY KHACH SAN ___"<<endl;
                cout << "_________1. Nhap so luong khach san_________" << endl;
                cout << "_______________2. Dat phong_________________" << endl;
                cout << "_______3. Hien thi danh sach khach san______" << endl;
                cout << "________4. Hien thi danh sach booking_______" << endl;
                cout << "_______5. Cap nhat thong tin khach san______" << endl;
                cout << "__________6. Ghi danh sach vao tep__________" << endl;
                cout << "___________7. Sap xep theo so sao___________" << endl;
                cout << "_____________8. Xoa khach san_______________" << endl;
                cout << "_________________0. Thoat___________________" << endl;
                cout << "      Xin vui long nhap lua chon:" ;cin >> luaChon; 

                
                switch (luaChon) {
            case 1: {
                int soLuongKhachSan;
                cout << "Nhap so luong khach san: ";
                cin >> soLuongKhachSan;
                for (int i = 0; i < soLuongKhachSan; ++i) {
                string ten, diaChi, maKhachSan;
                int soSao, soPhongTrong, soNhanVien;
                cout << "Nhap ten khach san " << i + 1 << ": ";
                cin >> ten;
                cout << "Nhap dia chi cho khach san " << i + 1 << ": ";
                cin.ignore(); 
                getline(cin, diaChi);
                cout << "Nhap so sao cho khach san " << i + 1 << ": ";
                cin >> soSao;
                cout << "Nhap so phong trong cho khach san " << i + 1 << ": ";
                cin >> soPhongTrong;
                cout << "Nhap so nhan vien phuc vu cho khach san " << i + 1 << ": ";
                cin >> soNhanVien;
                cout << "Nhap ma khach san " << i + 1 << ": ";
                cin >> maKhachSan;
                Hotel* khachSanMoi = taoKhachSan(maKhachSan, ten, soSao, diaChi, soPhongTrong, soNhanVien);
                themKhachSan(danhSachKhachSan, khachSanMoi);
                }
                sapXepTheoSao(danhSachKhachSan);
                hienThiDanhSachKhachSan(danhSachKhachSan);
                break;
}
           case 2: {
                Booking booking;
                cout << "Nhap ten khach hang: ";
                cin >> booking.customerName;
                cout << "Nhap tuoi: ";
                cin >> booking.age;
                cout << "Nhap so CCCD: ";
                cin >> booking.cccd;
                hienThiDanhSachKhachSan(danhSachKhachSan);
                int luaChonKhachSan;
                string maKhachSan;
                cout << " Nhap ma khach san : ";
                cin >> maKhachSan;
                Hotel* khachSanDuocChon = timTheoMa(danhSachKhachSan, maKhachSan);
                if (khachSanDuocChon) {
                    booking.hotel = khachSanDuocChon;
                    datPhong(danhSachKhachSan, booking);
                    danhSachBooking.push_back(booking);
                } else {
                    cout << "Khong tim thay khach san theo lua chon." << endl;
                }
                break;
            }
            case 3: {
                hienThiDanhSachKhachSan(danhSachKhachSan);
                break;
            }
            case 4: {
                hienThiDanhSachBooking(danhSachBooking);
                break;
            }

            case 5: {
                hienThiDanhSachKhachSan(danhSachKhachSan);
                cout << "Chon khach san de cap nhat thong tin (Nhap so thu tu trong danh sach): ";
                int luaChonKhachSanCapNhat;
                cin >> luaChonKhachSanCapNhat;

                Hotel* khachSanCanCapNhat = danhSachKhachSan.head;
                for (int i = 1; i < luaChonKhachSanCapNhat && khachSanCanCapNhat; ++i) {
                    khachSanCanCapNhat = khachSanCanCapNhat->next;
                }

                if (khachSanCanCapNhat) {
                    capNhatThongTinKhachSan(khachSanCanCapNhat);
                    cout << "Cap nhat thong tin thanh cong." << endl;
                } else {
                    cout << "Khong tim thay khach san theo lua chon." << endl;
                }
                break;
            }
            case 6: {
                string tenTep;
                cout << "Nhap ten tep can ghi: ";
                cin >> tenTep;
                ghiDanhSachVaoTep(danhSachKhachSan, danhSachBooking, tenTep);

                break;
            }
            case 7: {
                bool tangDan;
                cout << "Nhap 1 de sap xep tang dan, nhap 0 de sap xep giam dan: ";
                cin >> tangDan;
                sapXepTheoTruong(danhSachKhachSan, tangDan);
                break;
            }
            case 8: {
                int luaChonXoa;
                cout << "1. Xoa theo ma khach san" << endl;
                cout << "2. Xoa theo ten khach san" << endl;
                cout << "3. Xoa phan tu tai vi tri" << endl;
                cin >> luaChonXoa;
                switch (luaChonXoa) {
                    case 1: {
                        string maKhachSanXoa;
                        cout << "Nhap ma khach san can xoa: ";
                        cin >> maKhachSanXoa;
                        xoaKhachSanTheoMa(danhSachKhachSan, maKhachSanXoa);
                        break;
                    }
                    case 2: {
                        string tenKhachSanXoa;
                        cout << "Nhap ten khach san can xoa: ";
                        cin >> tenKhachSanXoa;
                        xoaKhachSanTheoTen(danhSachKhachSan, tenKhachSanXoa);
                        break;
                    }
                    case 3: {
                        int viTriXoa;
                        cout << "Nhap vi tri can xoa: ";
                        cin >> viTriXoa;
                        xoaPhanTuTaiViTri(danhSachKhachSan, viTriXoa);
                        break;
                    }
                    default:
                        cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                }
                break;
            }
                    case 0:
                        cout << "Thoat chuong trinh." << endl;
                        break;
                    default:
                        cout << "Lua chon khong hop le. Vui long nhap lai." << endl;
                }
    } while (luaChon != 0);
  

    return 0;
}