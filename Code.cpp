//Queue _ Breadth First Search (G_List, stack)
#include <iostream>
#include <queue>
#include <stack>
using namespace std;

queue<int**> q;
int n = 0;	// index of son
int m = -1;	// index of parent
int ***G_List = new int**[100];
int *G_Parent = new int[100];

void Sons(int, int, int**);
void PrintArr(int**);
int** CopyArr(int **);
void Put_G_List(int **);
bool Equal_G_List(int **);

int main()
{
	int **firstArr = new int*[3];
	int **currentArr;
	int **arr;

	// init Arr, q
	for (int i = 0; i < 3; i++)
	{
		firstArr[i] = new int[3];
		firstArr[0][i] = 3 - i;
	}

	for (int i = 1; i <= 2; i++)
		for (int j = 0; j <= 2; j++)
			firstArr[i][j] = 0;
	Put_G_List(firstArr);
	q.push(firstArr);

	// i: start j: end
	while (!q.empty()) {
		currentArr = q.front();
		q.pop();
		m++;
		if (currentArr[2][0] == 3 && currentArr[2][1] == 2 && currentArr[2][2] == 1) {
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
	for (from = 2; from >= 0; from--)
		if (arr[i][from] != 0) break;

	// end: [j,to]
	for (to = 2; to >= 0; to--)
		if (arr[j][to] != 0) break;
	to++;

	// do not start X
	if (from < 0) {
		return;
	}

	// end : 1,2
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
	int **copy = new int*[3];
	for (int i = 0; i < 3; i++)
	{
		copy[i] = new int[3];
		for (int j = 0; j < 3; j++) {
			copy[i][j] = a[i][j];
		}
	}
	return copy;
}
void Put_G_List(int **a)
{
	G_List[n] = new int*[3];
	for (int i = 0; i < 3; i++) {
		G_List[n][i] = new int[3];
		for (int j = 0; j < 3; j++) {
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
			for (int j = 0; j < 3; j++) {
				if (G_List[x][i][j] == a[i][j]) {
					cnt++;
				}
			}
		}
		if (cnt == 9) return true;
		else {
			x++;
			cnt = 0;
		}
	}
	return false;
}
void PrintArr(int **a) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}