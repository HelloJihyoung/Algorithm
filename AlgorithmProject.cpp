#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>
using namespace std;

int bruteCount = 0;
int KMPCount = 0;
int bubbleCount = 0;
int quickCount = 0;

int maxvalue(int a, int b, int c) { // ���� �ݾ� ��
	int k[3] = { a, b, c };
	int max = 0;
	for (int i = 0; i < 3; i++) {
		if (max < k[i]) max = k[i];
	}
	if (max == a) cout << "���ξ��� ���� ū ī��� ���� �븮ī�� �Դϴ�." << endl;
	else if (max == b) cout << "���ξ��� ���� ū ī��� īī�� ��ũ ������ üũī�� �Դϴ�." << endl;
	else if (max == c) cout << "���ξ��� ���� ū ī��� ���� HeyYoungī�� �Դϴ�." << endl;

	return max;
}

inline void swap(vector<pair<string, int>> &a, int i, int j) { // ������ �̵� ���� swap �Լ�
	pair<string, int> t = a[i]; a[i] = a[j]; a[j] = t;
}

void bubblesort(vector<pair<string, int>> &a) { //bubble sort
	for (int i = 0; i < a.size(); i++) { 
		bubbleCount++;
		for (int j = 1; j < a.size() - i; j++) {
			bubbleCount++;
			if (a[j - 1].second > a[j].second) {
				swap(a[j - 1], a[j]);
				bubbleCount ++;
			}
		}
	}
}

int partition(vector<pair<string, int>> &a, int l, int r) { // bubble sort - partition
	int i, j; pair<string, int> v;
	if (r > l) {
		v = a[l]; i = l; j = r + 1;
		for (;;) {
			while (a[++i].second < v.second)
				quickCount++;
			while (a[--j].second > v.second)
				quickCount++;
			if (i >= j) break;
			swap(a, i, j);

		}
		swap(a, j, l);
	}
	return j;
}

void quicksort(vector<pair<string, int>> &a, int l, int r) { //quicksort
	int j;
	if (r > l) {
		j = partition(a, l, r);
		quicksort(a, l, j - 1);
		quicksort(a, j + 1, r);
	}
}

void makegraph(int k) { // �׷��� ����
	for (int i = 0; i < k; i++) {
		cout << "��";
	}
}

int findString(string parent, string pattern) { // bruteforce �� string ã��
	int cnt = 0; // ���� Ƚ���� ���� ���� ����
	int parentSize = parent.size() - pattern.size();
	int patternSize = pattern.size();

	for (int i = 0; i < parentSize - patternSize; i++) {
		bool finded = true;
		for (int j = 0; j < patternSize; j++) {
			bruteCount++;
			if (parent[i + j] != pattern[j]) {
				finded = false;
			}
		}
		if (finded) {
			cnt++;
		}
	}
	return cnt;
}

void checkBrute(string all, string arr[]) { //�׸� �з� ���� ���ڿ� �˻�
	int food = findString(all, arr[0]) + findString(all, arr[1]) + findString(all, arr[2]);
	int convien = findString(all, arr[3]);
	int coffee = findString(all, arr[4]);
	int internet = findString(all, arr[5]);
	int culture = findString(all, arr[6]) + findString(all, arr[13]);
	int deliver = findString(all, arr[7]);
	int bakery = findString(all, arr[8]);
	int phone = findString(all, arr[9]);
	int traffic = findString(all, arr[10]);
	int cosme = findString(all, arr[11]);
	int etc = findString(all, arr[12])+ findString(all, arr[14]);

	vector<pair<string, int>> sortB;
	sortB.push_back(make_pair("�ܽ�", food));
	sortB.push_back(make_pair("������", convien));
	sortB.push_back(make_pair("ī��", coffee));
	sortB.push_back(make_pair("���ڻ�ŷ�", internet));
	sortB.push_back(make_pair("��ȭ", culture));
	sortB.push_back(make_pair("���", deliver));
	sortB.push_back(make_pair("����Ŀ��", bakery));
	sortB.push_back(make_pair("���", phone));
	sortB.push_back(make_pair("����", traffic));
	sortB.push_back(make_pair("ȭ��ǰ", cosme));
	sortB.push_back(make_pair("��Ÿ", etc));

	//quicksort(sortB, 0, sortB.size()-1);
	bubblesort(sortB);
	for (int i = sortB.size() - 1; i >= 0; i--) {
		makegraph(sortB[i].second);
		cout << sortB[i].first << " : " << sortB[i].second + 1 ;
		cout << "\n";
	}

	cout << "����� " << sortB[sortB.size() - 1].first << "�� ���帹�� �Һ� �߽��ϴ�!" << endl;
	cout << "\n" << endl;
}

vector<int> makeTable(string pattern) {
	int patternSize = pattern.size();
	vector<int> table(patternSize, 0);
	int j = 0;
	for (int i = 1; i < patternSize; i++) {
		while (j > 0 && pattern[i] != pattern[j]) {
			j = table[j - 1];
		}
		if (pattern[i] == pattern[j]) {
			table[i] = ++j;
		}
	}
	return table;
}

int KMP(string parent, string pattern) {
	vector<int> table = makeTable(pattern);
	int parentSize = parent.size();
	int patternSize = pattern.size();
	int j = 0;
	int cnt = 0;
	for (int i = 0; i < parentSize; i++) {
		while (j > 0 && parent[i] != pattern[j]) {
			j = table[j - 1];
			KMPCount++;
		}
		if (parent[i] == pattern[j]) j++;
		if (j == patternSize - 1) {
			j = table[j];
			KMPCount++;
			cnt++;
		}
	}
	return cnt;
}

int checkKMP(string all, string arr[]) { //�׸� �з� ���� ���ڿ� �˻�
	
	int food = KMP(all, arr[0]) + KMP(all, arr[1]) + KMP(all, arr[2]);
	int convien = KMP(all, arr[3]);
	int coffee = KMP(all, arr[4]);
	int internet = KMP(all, arr[5]);
	int culture = KMP(all, arr[6]) + KMP(all, arr[13]);
	int deliver = KMP(all, arr[7]);
	int bakery = KMP(all, arr[8]);
	int phone = KMP(all, arr[9]);
	int traffic = KMP(all, arr[10]);
	int cosme = KMP(all, arr[11]);
	int etc = KMP(all, arr[12]) + KMP(all, arr[14]);

	vector<pair<string, int>> sortB;
	sortB.push_back(make_pair("�ܽ�", food));
	sortB.push_back(make_pair("������", convien));
	sortB.push_back(make_pair("ī��", coffee));
	sortB.push_back(make_pair("���ڻ�ŷ�", internet));
	sortB.push_back(make_pair("��ȭ", culture));
	sortB.push_back(make_pair("���", deliver));
	sortB.push_back(make_pair("����Ŀ��", bakery));
	sortB.push_back(make_pair("���", phone));
	sortB.push_back(make_pair("����", traffic));
	sortB.push_back(make_pair("ȭ��ǰ", cosme));
	sortB.push_back(make_pair("��Ÿ", etc));

	quicksort(sortB, 0, sortB.size() - 1);
	//bubblesort(sortB);
	for (int i = sortB.size() - 1; i >= 0; i--) {
		makegraph(sortB[i].second);
		cout << sortB[i].first << " : " << sortB[i].second + 1;
		cout << "\n";
	}
	cout << "����� " << sortB[sortB.size()-1].first << "�� ���帹�� �Һ� �߽��ϴ�!" << endl;
	cout << "\n" << endl;
	return 0;

}
//ī�庰 ���� �м�
int noricard(vector<pair<string, int>> &a) {
	int nori_discount = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i].first == "CGV") {
			if ((a[i].second) >= 10000) {
				if (((a[i].second)*0.35) > 7000) nori_discount += 7000;
				else nori_discount += ((a[i].second)*0.35);
			}
		}
		else if (a[i].first == "�޴������") {
			if ((a[i].second) < 50000) 	nori_discount += ((a[i].second)*0.05);
			else nori_discount += 2500;
		}
		else if (a[i].first == "����ö" || a[i].first == "Ƽ�Ӵ� �����ý�") {
			if (((a[i].second) * 0.1) > 2000) 	nori_discount += 2000;
			else nori_discount += ((a[i].second) * 0.1);
		}
		else if (a[i].first == "��Ÿ����") {
			if ((a[i].second) >= 10000) {
				if (((a[i].second)*0.2) > 4000) nori_discount += 4000;
				else nori_discount += ((a[i].second)*0.2);
			}
		}
		else if (a[i].first == "GS25") {
			if ((a[i].second) >= 10000) {
				if (((a[i].second)*0.05) > 1000) nori_discount += 1000;
				else nori_discount += ((a[i].second)*0.05);
			}
		}
	}

	
	return nori_discount;
}
int kakaocard(vector<pair<string, int>> &a) {
	int kakao_discount = 0;
	for (int i = 0; i < a.size(); i++) {
		if (a[i].first == "CGV") {
			if ((a[i].second) >= 15000) {
				kakao_discount += 4000;
			}
		}
		else if (a[i].first == "�޴������") {
			if ((a[i].second) >= 50000) 	kakao_discount += 3000;
		}
		else if (a[i].first == "��Ÿ����") {
			if ((a[i].second) >= 10000) kakao_discount += 1000;
		}
		else if (a[i].first == "����") {
			if ((a[i].second) >= 10000)	kakao_discount += 1000;
		}
		else if (a[i].first == "����") {
			if ((a[i].second) >= 20000)	kakao_discount += 2000;
		}
	}

	return kakao_discount;
}
int youngcard(vector<pair<string, int>> &a) {
	int young_discount = 0;

	for (int i = 0; i < a.size(); i++) {
		if (a[i].first == "CGV") {
			if ((a[i].second) >= 20000)	young_discount += 5000;
		}
		else if (a[i].first == "�޴������") {
			if ((a[i].second) >= 50000) young_discount += 2000;
		}
		else if (a[i].first == "����ö") {
			young_discount += ((a[i].second) * 0.05);
		}
		else if (a[i].first == "��Ÿ����") {
			if ((a[i].second) >= 10000) young_discount += 1000;
		}
		else if (a[i].first == "GS25") {
			if ((a[i].second) >= 10000) young_discount += 1000;
		}
	}
	
	return young_discount;
}

int main() {
	vector <string> name; // ��� ��Ҹ�, �ݾ�
	vector <int> money;
	vector <string> sort; // ������ ����
	ifstream file("re.csv"); // ���� �ҷ�����
	string all; //�ҷ��� ��ü ������ �����ϴ� all string
	string line; // txt������ ���پ� �޾ƿ�
	string arr[15] = { "�ѽ�", "�Ϲݴ�������", "�Ͻ�", "������", "Ŀ��������", "���ڻ�ŷ�","PC ���ӹ�","���", "������", "���", "����", "ȭ��ǰ", "��Ÿ", "��ȭ��", "�౹" };
	string s; // string �� �޾ƿ���
	while (!file.eof()) { // txt���� �����Ҷ����� �Ʒ� ���� �ݺ�
		getline(file, line);//getline�Լ��� �̿��Ͽ� ���پ� �о��
		stringstream f(line); // stringstream�� �̿��Ͽ� ���ڿ��� �Է¹޾� ����
		int flag = 0;
		while (getline(f, s, ',')) { //,�� ������ �Ͽ� �ܾ� ����
			all += s;
			if (flag == 0) { // name
				name.push_back(s);
			}
			else if (flag == 2) { //money
				int n = atoi(s.c_str());
				money.push_back(n);
			}
			flag++;
		}
	}
	vector <pair<string, int>> list;
	int sum = 0;
	for (int i = 0; i < name.size(); i++) {
		list.push_back(pair<string, int>(name[i], money[i]));
		sum += money[i];
	}
	int lastmoney = 0;
	cout << "������ ī�� ��� �ݾ��� �ۼ��� �ּ��� : ";
	cin >> lastmoney;
	while (lastmoney < 300000)
	{
		cout << "���������� �����Ͽ� ���� ������ ���� �� �����ϴ� :(" << "\n" << endl;
		cout << "������ ī�� ��� �ݾ��� �ۼ��� �ּ��� : ";
		cin >> lastmoney;
	}

	cout << "-----------BruteForce----------" << endl;
	clock_t start_Brute = clock();
	checkBrute(all, arr); // BruteForce + BubbleSort
	clock_t end_Brute = clock();


	cout << "-----------KMP----------" << endl;
	clock_t start_KMP = clock();
	checkKMP(all, arr); // KMP + QuickSort
	clock_t end_KMP = clock();

	cout << "-***********************************" << endl;

	cout << "�̹��� �� ��� �ݾ��� " << sum << "�� �Դϴ�." << "\n";

	cout << "---------------------" << endl;
	cout << "���� �븮ī�� ���� �ݾ� : " << noricard(list) << endl;
	cout << "īī�� ��ũ ������ üũī�� ���� �ݾ� : " << kakaocard(list) << endl;
	cout << "���� HeyYoungī�� ���� �ݾ� : " << youngcard(list) << endl;
	cout << endl;
	int a = noricard(list);
	int b = kakaocard(list);
	int c = youngcard(list);

	maxvalue(a, b, c);


	cout << "\n************�˰��� �� Ƚ��************" << endl;
	cout << "-----------���ڿ� Ž�� �˰���-----------" << endl;
	cout << "Brute-Force ��Ƚ�� : " << bruteCount << endl;
	cout << "KMP ��Ƚ��         : " << KMPCount << endl;
	cout << "--------------���� �˰���--------------" << endl;
	cout << "QuickSort ��Ƚ��   : " << quickCount << endl;
	cout << "BubbleSort ��Ƚ��  : " << bubbleCount << endl;

	cout << "\n***************��Ÿ�� �ð�***************" << endl;
	printf("Brute Force + Bubble Sort Run Time : %lf\n", (double)(end_Brute - start_Brute) / CLOCKS_PER_SEC);
	printf("KMP + Quick Sort Run Time          : %lf\n", (double)(end_KMP - start_KMP) / CLOCKS_PER_SEC);
	file.close(); // ���� �ݱ�
	

	return 0;

}