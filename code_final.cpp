#include <iostream>
#include <iomanip>		// for std::setw(n), std::setfill(ch), std::left, std::right
#include <string>		// for stoi
#include <fstream>		// open, write to file
#include <sstream>		// stringstream
using namespace std;

class KH {
public:
    int ID;
    string name;
    string tel;
    string dob;
    long int pts;
    string rank;
    KH* next;
    KH* prev; // Add a pointer to the previous node
};

void nhapthongtin(KH* kh) {
	cout << "Nhap ID: ";
	cin >> kh->ID;
	fflush(stdin);
	cout << "Nhap ten: ";
	getline(cin,kh->name);
	cout << "Nhap SDT: ";
	getline(cin,kh->tel);
	cout << "Nhap ngay/thang/nam sinh: ";
	getline(cin,kh->dob);
	fflush(stdin);
	cout << "Nhap diem tich luy: ";
	cin >> kh->pts;
	fflush(stdin);
}
void hienthongtin(KH* kh) {
	cout << setfill(' ');
	cout << setw(15) << left << kh->ID;
	cout << setw(30) << left << kh->name;
	cout << setw(20) << left << kh->tel;
	cout << setw(20) << left << kh->dob;
	cout << setw(15) << left << kh->pts;
	cout << setw(5) << left << kh->rank << endl;
}
class List {
	private:
		KH* head;
		KH* tail;
		int length;
	public:
		// Constructor
		List() {
			head=nullptr;
			tail=nullptr;
			length=0;
		}
		// Destructor
		~List() {
			KH* temp=head;
			while(head != nullptr) {
				head=temp->next;
				delete temp;
				temp=head;
			}
		}
		// In danh sach
		void printList() {
			KH* temp=head;
			if (length == 0) {
				cout << "Khong co khach hang." << endl;
				return;
			}
			int i=1;
			cout << endl;
			cout << setfill(' ');
			cout << setw(5) << left << "STT";
			cout << setw(15) << left << "ID";
			cout << setw(30) << left << "Ten";
			cout << setw(20) << left << "SDT";
			cout << setw(20) << left << "Ngay sinh";
			cout << setw(15) << left << "Diem";
			cout << setw(5) << left << "Rank" << endl;
			cout << setfill('-');
			cout << setw(115) << "-" << endl;
			while(temp != nullptr) {
				cout << setfill(' ');
				cout << setw(5) << left << i;
				hienthongtin(temp);
				cout << setfill('-');

				temp=temp->next;
				i++;
			}
			cout << setw(115) << "-" << endl;
		}
		// Them vao duoi
		void append() {
        KH* newKH = new KH;
        nhapthongtin(newKH);
        updateRank(newKH);
        if (length == 0) {
            head = newKH;
            tail = newKH;
            newKH->next = nullptr;
            newKH->prev = nullptr; // Set the previous pointer to nullptr for the first node
        } else {
            newKH->prev = tail; // Set the previous pointer to the current tail
            tail->next = newKH;
            tail = newKH;
            newKH->next = nullptr;
        }
        length++;
    }
		// Them vao dau
		void prepend() {
        KH* newKH = new KH;
        nhapthongtin(newKH);
        updateRank(newKH);
        if (length == 0) {
            head = newKH;
            tail = newKH;
            newKH->next = nullptr;
            newKH->prev = nullptr;
        } else {
            newKH->next = head; // Set the next pointer to the current head
            head->prev = newKH;
            head = newKH;
        }
        length++;
    }
		// Xoa o dau
		void deleteFirst() {
			if(length==0) return;
			KH* temp=head;
			if(length==1) head=tail=nullptr;
			else {
				head=head->next;
				head->prev=nullptr;
			}
			delete temp;
			length--;
		}
		// Xoa o duoi
		void deleteLast() {
			if(length==0) return;
			KH* temp=tail;
			if(length==1) {
				head=nullptr;
				tail=nullptr;
			} else {
				tail=tail->prev;
				tail->next=nullptr;
			}
			delete temp;
			length--;
		}
		// Tim kiem theo STT
		KH* get(int index) {
			if (index < 1 || index > length) return nullptr;
			KH* temp = head;
			for (int i = 1; i < index; i++) {
				temp = temp->next;
			}
			return temp;
		}
		// Tim kiem theo ID
		KH* findID(int id) {
			KH* temp=head;
			while(temp) {
				if (temp->ID ==  id) {
					cout << "Found!" << endl;
					return temp;
				}
				temp=temp->next;
			}
			return temp;
		}
		// Tim kiem theo ten
		KH* findName(string Name) {
			KH* temp=head;
			while(temp) {
				if (temp->name ==  Name) {
					cout << "Found!" << endl;
					return temp;
				}
				temp=temp->next;
			}
			return temp;
		}
		// Tim kiem theo SDT
		KH* findTel(string Tel) {
			KH* temp=head;
			while(temp) {
				if (temp->tel ==  Tel) {
					cout << "Found!" << endl;
					return temp;
				}
				temp=temp->next;
			}
			return temp;
		}
		// Hien thi nhung khach hang co Rank xxx
		void findRank(string Rank) {
			KH* temp=head;
			int check=0;
			cout << setfill('-');
			cout << setw(115) << "-" << endl;
			while(temp) {
				if (temp->rank == Rank) {
					cout << setfill(' ');
					cout << setw(5) << left << " ";
					hienthongtin(temp);
					check = 1;
				}
				temp=temp->next;
			}
			if (check == 0) cout << "Khong ton tai Rank." << endl;
			cout << setfill('-');
			cout << setw(115) << "-" << endl;
		}
		// Sua thong tin theo ID
		void set(int id) {
			KH* temp=findID(id);
			if (temp == nullptr) {
				cout << "Khong tim thay khach hang co ID da nhap." << endl;
				return;
			}
			nhapthongtin(temp);
			updateRank(temp);
			cout << "Sua thanh cong!" << endl;
		}
		// Insert vi tri bat ki
		void insert(int index) {
			if (index < 1 || index > length+1) {
				cout << "Khong hop le." << endl;
				return;
			}
			if (index == 1) {
				prepend();
				cout << "DONE!" << endl;
				return;
			}
			if (index == length+1) {
				append();
				cout << "DONE!" << endl;
				return;
			}
			KH* newKH = new KH;
			nhapthongtin(newKH);
			updateRank(newKH);
			KH* temp = get(index - 1);
			newKH->next = temp->next;
			temp->next->prev = newKH;
			temp->next = newKH;
			newKH->prev=temp;
			length++;
			cout << "DONE!" << endl;
			return;
		}
		// Delete theo STT
		void deleteKH(int index) {
			if (index < 1 || index > length) {
				cout << "Khong hop le." << endl;
				return;
			}
			if (index == 1) {
				cout << "DONE!" << endl;
				return deleteFirst();
			}
			if (index == length) {
				cout << "DONE!" << endl;
				return deleteLast();
			}

			KH* before = get(index - 1);
			KH* temp = before->next;

			before->next = temp->next;
			temp->next->prev = before;
			delete temp;
			length--;
		}
		// Delete theo ten
		void deletename(string Name){
			KH* temp=findName(Name);
			if(temp == nullptr) {
				cout << "Khong tim thay khach hang." << endl;
				return;
			}
			if(temp->next==nullptr){
				deleteLast();
			}else if(temp->prev==nullptr){
				deleteFirst();
			}else{
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;
				delete temp;
			}
			cout << "Xoa thong tin khach hang thanh cong ";
			length--;
		}
		// delete theo ID
		void deleteID(int ID){
			KH* temp = findID(ID);
			if(temp == nullptr) {
				cout << "Khong tim thay khach hang." << endl;
				return;
			}
			if(temp->next==nullptr){
				deleteLast();
			}else if(temp->prev==nullptr){
				deleteFirst();
			}else{
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;
				delete temp;
			}
			cout << "Xoa thong tin khach hang thanh cong ";
			length--;
		}
		// delete theo SDT
		void deleteTel(string Tel){
			KH*temp=findTel(Tel);
			if(temp == nullptr) {
				cout << "Khong tim thay khach hang." << endl;
				return;
			}
			if(temp->next==nullptr){
				deleteLast();
			}else if(temp->prev==nullptr){
				deleteFirst();
			}else{
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;
				delete temp;
			}
			cout << "Xoa thong tin khach hang thanh cong ";
			length--;
		}
		// Cap nhat Rank
		void updateRank(KH* temp) {
			if (temp->pts >= 20000) temp->rank = "Diamond";
			else if (temp->pts >= 10000) temp->rank = "Platinum";
			else if (temp->pts >= 5000) temp->rank = "Gold";
			else if (temp->pts >= 1000) temp->rank = "Silver";
			else temp->rank = "Standard";
		}
		// Ham sap xep
		void merge(KH* arr[], int left, int mid, int right) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    KH* *leftArr = new KH*[leftSize];
    KH* *rightArr = new KH*[rightSize];

    for (int i = 0; i < leftSize; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < rightSize; j++)
        rightArr[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < leftSize && j < rightSize) {
        if (leftArr[i]->pts >= rightArr[j]->pts)
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    while (i < leftSize)
        arr[k++] = leftArr[i++];

    while (j < rightSize)
        arr[k++] = rightArr[j++];

    delete[] leftArr;
    delete[] rightArr;
}

// Merge Sort function
void mergeSort(KH* arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Updated Sort function
void Sort() {
    if (length == 0 || length == 1) {
        cout << "Khong du so luong de sap xep." << endl;
        return;
    }

    // Create an array of pointers to the list nodes
    KH* *arr = new KH*[length];
    KH* temp = head;
    int i = 0;
    while (temp) {
        arr[i++] = temp;
        temp = temp->next;
    }

    mergeSort(arr, 0, length - 1);

    cout << "DONE!" << endl;
    cout << setfill('-') << setw(115) << "-" << endl;

    for (int i = 0; i < length; i++) {
        cout << setfill(' ') << setw(5) << left << " ";
        hienthongtin(arr[i]);
    }

    cout << setfill('-') << setw(115) << "-" << endl;

    delete[] arr;
}
		// Ham add khach hang tu file
		void add(int ID, string name, string tel, string dob,long int pts,string rank) {
			KH* newKH= new KH;
			newKH->ID=ID;
			newKH->name=name;
			newKH->tel=tel;
			newKH->dob=dob;
			newKH->pts=pts;
			newKH->rank=rank;
			newKH->next=nullptr;
			newKH->prev=nullptr;
			if (length == 0) {
				head = newKH;
				tail = newKH;
			} else {
				tail->next = newKH;
				newKH->prev = tail;
				tail = newKH;
			}
			length++;
		}
		// Luu data vao file
		void savetofile() {
			ofstream save;
			save.open ("customer.txt", ios::out | ios::trunc);
			KH* temp=head;
			while(temp) {
				save << temp->ID << ",";
				save << temp->name << ",";
				save << temp->tel << ",";
				save << temp->dob << ",";
				save << temp->pts << ",";
				save << temp->rank << "," << endl;
				temp=temp->next;
			}
			save.close();
		}
		// Doc data tu file
		void readfile() {
			ifstream save("customer.txt");
			if(save.is_open()) {
				string line;
				while(getline(save, line)) {
					stringstream ss(line);
					string ID;
					string name;
					string tel;
					string dob;
					string pts;
					string rank;
					getline(ss, ID, ',');
					getline(ss, name, ',');
					getline(ss, tel, ',');
					getline(ss, dob, ',');
					getline(ss, pts, ',');
					getline(ss, rank, ',');
					add(stoi(ID),name,tel,dob,stoi(pts),rank);
				}
			}
		}
};

int main() {
	List* myList = new List();
	myList->readfile();
	cout << "----------Menu----------" << endl;
	cout << "[1] Them khach hang" << endl;
	cout << "[2] Them khach hang vao vi tri tu chon" << endl;
	cout << "[3] In danh sach khach hang" << endl;
	cout << "[4] Tim kiem khach hang" << endl;
	cout << "[5] Cap nhat diem" << endl;
	cout << "[6] Sap xep khach hang theo diem" << endl;
	cout << "[7] Sua thong tin khach hang" << endl;
	cout << "[8] Xoa khach hang" << endl;
	cout << "[0] Exit" << endl;
	int choice;
	while (1) {
		cout << "------------------------" << endl;
		cout << "[Nhap lua chon cua ban] ";
		cin >> choice;
		fflush(stdin);
		if (choice == 1) {
			myList->append();
			cout << "DONE!" << endl;
		}
		if (choice == 2) {
			cout << "Ban muon them vao dau? ";
			int index;
			cin >> index;
			myList->insert(index);
		}
		if (choice == 3) {
			myList->printList();
		}
		if (choice == 4) {
			cout << "\tTim kiem theo? " << endl << "[1] ID" << endl << "[2] Ten" << endl << "[3] SDT" << endl << "[4] Rank" << endl << "Chon: ";
			int choice2;
			cin >> choice2;
			fflush(stdin);
			if (choice2 == 1) {
				int id;
				cout << "Nhap ID can tim: ";
				cin >> id;
				KH* t = myList->findID(id);
				if (t == nullptr) {
					cout << "Khong tim thay ID." << endl;
				} else {
					cout << setfill('-');
					cout << setw(115) << "-" << endl;
					cout << "     ";
					hienthongtin(t);
					cout << setfill('-');
					cout << setw(115) << "-" << endl;
				}
			}
			if (choice2 == 2) {
				string name;
				cout << "Nhap ten can tim: ";
				getline(cin,name);
				KH* t = myList->findName(name);
				if (t == nullptr) {
					cout << "Khong tim thay ten." << endl;
				} else {
					cout << setfill('-');
					cout << setw(115) << "-" << endl;
					cout << "     ";
					hienthongtin(t);
					cout << setfill('-');
					cout << setw(115) << "-" << endl;
				}
			}
			if (choice2 == 3) {
				string tel;
				cout << "Nhap SDT can tim: ";
				getline(cin,tel);
				KH* t = myList->findTel(tel);
				if (t == nullptr) {
					cout << "Khong tim thay SDT." << endl;
				} else {
					cout << setfill('-');
					cout << setw(115) << "-" << endl;
					cout << "     ";
					hienthongtin(t);
					cout << setfill('-');
					cout << setw(115) << "-" << endl;
				}
			}
			if (choice2 == 4) {
				string rank;
				cout << "Nhap Rank can tim: ";
				cin >> rank;
				myList->findRank(rank);
			}
		}
		if (choice == 5) {
			int id;
			cout << "Nhap ID can tim: ";
			cin >> id;
			KH* t = myList->findID(id);
			if (t == nullptr) {
				cout << "Khong tim thay ID." << endl;
			} else {
				cout << "Diem cu: " << t->pts << ". Hay nhap diem moi: ";
				cin >> t->pts;
				myList->updateRank(t);
				cout << "Cap nhat thanh cong." << endl;
			}
		}
		if (choice == 6) {
			myList->Sort();
		}
		if (choice == 7) {
			int id;
			cout << "Nhap ID can sua: ";
			cin >> id;
			myList->set(id);
		}
		if (choice == 8) {
			cout << "\tXoa thong tin theo? " << endl << "[1] ID" << endl << "[2] Ten" << endl << "[3] SDT" << endl << "[4] Vi tri" << endl << "Chon: ";
			int chon;
			cin >> chon;
			fflush(stdin);
			if(chon==1){
				int ID;
				cout << "Nhap ID khach hang muon xoa: ";
				cin >> ID;
				myList->deleteID(ID);
			}
			if(chon==2){
				string Name;
				cout << "Nhap ten khach hang muon xoa: ";
				getline(cin,Name);
				myList->deletename(Name);
			}
			if(chon==3){
				string Tel;
				cout << "Nhap SDT khach hang muon xoa: ";
				getline(cin,Tel);
				myList->deleteTel(Tel);
			}
			if(chon==4){
				int index;
				cout << "Nhap STT khach hang muon xoa: ";
				cin >> index;
				myList->deleteKH(index);
			}
		}
		if (choice == 0) {
			myList->savetofile();
			cout << "Luu thanh cong." << endl;
			return 0;
		}
		if (choice < 0 || choice > 8) cout << "Khong hop le." << endl;
	}
}
