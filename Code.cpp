//Tower of Hanoi_Breadth First Search (G_List, queue, stack)
#include <iostream>
#include <queue>
#include <stack>
#include <cmath>
using namespace std;

queue<int**> q;
int n = 0;		// index of son
int m = -1;	// index of parent
int number_hanoi;	// height of hanoi tower
int ***G_List;
int *G_Parent;

void Sons(int, int, int**);
void PrintArr(int**);
int** CopyArr(int **);
void Put_G_List(int **);
bool Equal_G_List(int **);

int main()
{
	cin >> number_hanoi;
	int size_glist = (int) pow(3, number_hanoi);
	G_List = new int**[3];
	G_Parent = new int[3];

	int **firstArr = new int*[number_hanoi];
	int **goalArr = new int*[number_hanoi];
	int **currentArr;
	int **arr;

	// init rows
	for (int i = 0; i < 3; i++)
	{
		firstArr[i] = new int[number_hanoi];
		goalArr[i] = new int[number_hanoi];

	}
	// init columns
	for (int i = 0; i < number_hanoi; i++)
	{
		firstArr[0][i] = number_hanoi - i;
		goalArr[2][i] = number_hanoi - i;
	}

	for (int i = 1; i < 3; i++)
		for (int j = 0; j < number_hanoi; j++)
			firstArr[i][j] = 0;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < number_hanoi; j++)
			goalArr[i][j] = 0;
	Put_G_List(firstArr);
	q.push(firstArr);

	// i: start, j: arrive
	while (!q.empty()) {
		currentArr = q.front();
		q.pop();
		m++;
		int cnt = 0;
		//check goalstate
		for (int i = 0; i < number_hanoi; i++)
		{
			if (currentArr[2][i] == goalArr[2][i]) cnt++;
		}
		if (cnt == number_hanoi) {
			// parent->son printArr
			stack<int> s;
			s.push(m);
			while (m != 0) {
				s.push(G_Parent[m]);
				m = G_Parent[m];
			}
			int a;
			while (!s.empty()) {
				a = s.top();
				s.pop();
				PrintArr(G_List[a]);
			}
			cout << "end!" << endl;
			return 0;
		}
		else {
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					arr = CopyArr(currentArr);
					if (i != j) Sons(i, j, arr);
				}
			}
		}
	}
	return 0;
}
void Sons(int i, int j, int **arr) {
	int from;
	int to;

	// start: [i,from]
	for (from = number_hanoi-1; from >= 0; from--)
		if (arr[i][from] != 0) break;

	// arrive: [j,to]
	for (to = number_hanoi-1; to >= 0; to--)
		if (arr[j][to] != 0) break;
	to++;

	// do not start
	if (from < 0) {
		return;
	}

	// index of arrive is not 0, check idx-1
	if (to != 0) {
		if (arr[j][to - 1] <= arr[i][from]) {
			return;
		}
	}
	int temp = arr[i][from];
	arr[j][to] = temp;
	arr[i][from] = 0;
	if (!Equal_G_List(arr)) {
		Put_G_List(arr);
		q.push(arr);
	}
}
int** CopyArr(int **a)
{
	int **copy = new int*[number_hanoi];
	for (int i = 0; i < 3; i++)
	{
		copy[i] = new int[number_hanoi];
		for (int j = 0; j < number_hanoi; j++) {
			copy[i][j] = a[i][j];
		}
	}
	return copy;
}
void Put_G_List(int **a)
{
	G_List[n] = new int*[3];
	for (int i = 0; i < 3; i++) {
		G_List[n][i] = new int[number_hanoi];
		for (int j = 0; j < number_hanoi; j++) {
			G_List[n][i][j] = a[i][j];
		}
	}
	G_Parent[n] = m;
	n++;
}
bool Equal_G_List(int **a) {
	int cnt = 0;
	for (int x = 0; x < n;) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < number_hanoi; j++) {
				if (G_List[x][i][j] == a[i][j]) {
					cnt++;
				}
			}
		}
		if (cnt == number_hanoi*3) return true;
		else {
			x++;
			cnt = 0;
		}
	}
	return false;
}
void PrintArr(int **a) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < number_hanoi; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}