
//Queue _ Breadth First Search

#include <iostream>
#include <queue>
using namespace std;

const int X = 9;
queue<int*> q;

void push_Queue(int &number, int* State, int newOne[][10], int*currentState, int min, int to) {
	int i, j = 0, temp;
	int cnt=0;

	temp = State[min];

	i = to;
	while (i < to+3) {
		if (State[i] == X && i == to) {
			State[min] = X;
			State[i] = temp;
			for (j = 0; j < 10; j++) newOne[number][j] = State[j];
			q.push(newOne[number]);
			number++;
			number = number % 25000;

			
			for (j = 0; j < 10; j++) State[j] = currentState[j];
			break;
		}
		if (i == to) i++;
		if (State[i] == X && State[i - 1] != X && State[i - 1] > temp) {
			if (State[i - 1] != State[min]) State[min] = X;
			State[i] = temp;
			for (j = 0; j < 10; j++) newOne[number][j] = State[j];
			q.push(newOne[number]);
			number++;
			number = number % 25000;

			for (j = 0; j < 10; j++) State[j] = currentState[j];
			break;
		}
		i++;
	}
	return;
}
int main() {
	int *firstState = new int[9]{ 3,2,1,X,X,X,X,X,X };
	int *finalState = new int[9]{ X,X,X,X,X,X,3,2,1 };
	int *currentState = new int[10];
	bool Goal = false;
	int i, j = 0;
	int newOne[25000][10];
	int number = 0;

	q.push(firstState);
	while (!q.empty()) {
		currentState = q.front();
		q.pop();
		currentState[9] = X;

		//goal=true
		while (j < 10) {
			if (finalState[j] != currentState[j]) {
				Goal = false;
				break;
			}
			Goal = true;
			j++;
		}

		if (Goal) {
			cout << "End!" << endl;
		}
		else {
			// 1)
			int min[3] = { X,X,X };
			int j = 0;
			while (j < 3)
			{
				if (currentState[j] < currentState[min[0]]) min[0] = j;
				if (currentState[j + 3] < currentState[min[1]]) min[1] = j + 3;
				if (currentState[j + 6] < currentState[min[2]]) min[2] = j + 6;
				j++;
			}

			// 2) 
			if (min[0] >= 3) min[0] = X;
			if (min[1] >= 6) min[1] = X;
			if (min[2]) min[2] = X;

			cout << number << " : " << min[0] << " " << min[1] << " " << min[2] << endl;

			// 3)
			int *State = new int[10];
			for (i = 0; i < 10; i++) State[i] = currentState[i];
			

			//  A
			if (min[0] != X) {
				push_Queue( number, State, newOne, currentState, min[0],3 );
				push_Queue( number, State, newOne, currentState, min[0], 6);
			}
			//  B
			if (min[1] != X) {
				push_Queue( number, State, newOne, currentState, min[1],0);
				push_Queue(number, State, newOne, currentState,  min[0], 6);
			}
			//  C
			if (min[2] != X) {
				push_Queue( number, State, newOne, currentState, min[2],0);
				push_Queue( number, State, newOne, currentState, min[0], 3);
			}
		}
	}
	return 0;
}
