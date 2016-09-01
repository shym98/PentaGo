#pragma comment(linker,"/STACK:100000000000")

#include <chrono>
#include <thread>
#include <ctime>
#include "Main_menu.h"

const double cp = 2 * asin(1.0);

map<pair<int, int>, pair<int, int> > left_rotate, right_rotate;

class Board
{
public:
	int matrix[3][3];
	Sprite rect;
	CircleShape circle[9];
	map<int, pair<int, int> > pos_m; // getting index in matrix by number
	map<pair<int, int>, int> pos_b;
	double center_x, center_y;
	Board(double pix1, double pix2)
	{
		rect.setPosition(0+pix1, 0+pix2);
		for (int i = 0; i < 3;i++)
		for (int j = 0; j < 3; j++)
			matrix[i][j] = 0;
		for (int i = 0; i < 9; i++)
		{
			circle[i].setFillColor(Color::Green);
			circle[i].setRadius(30.f);
			if (i == 0)	pos_m[i] = make_pair(0, 0), circle[i].setPosition(Vector2f(30 + pix1, 30 + pix2)), pos_b[make_pair(0, 0)] = 0;
			if (i == 1)	pos_m[i] = make_pair(1, 0), circle[i].setPosition(Vector2f(30 + pix1, 120 + pix2)), pos_b[make_pair(1, 0)] = 1;
			if (i == 2)	pos_m[i] = make_pair(2, 0), circle[i].setPosition(Vector2f(30 + pix1, 210 + pix2)), pos_b[make_pair(2, 0)] = 2;
			if (i == 3)	pos_m[i] = make_pair(0, 1), circle[i].setPosition(Vector2f(120 + pix1, 30 + pix2)), pos_b[make_pair(0, 1)] = 3;
			if (i == 4)	pos_m[i] = make_pair(1, 1), circle[i].setPosition(Vector2f(120 + pix1, 120 + pix2)), center_x = 120 + pix1, center_y = 120 + pix2, pos_b[make_pair(1, 1)] = 4;
			if (i == 5)	pos_m[i] = make_pair(2, 1), circle[i].setPosition(Vector2f(120 + pix1, 210 + pix2)), pos_b[make_pair(2, 1)] = 5;
			if (i == 6)	pos_m[i] = make_pair(0, 2), circle[i].setPosition(Vector2f(210 + pix1, 30 + pix2)), pos_b[make_pair(0, 2)] = 6;
			if (i == 7)	pos_m[i] = make_pair(1, 2), circle[i].setPosition(Vector2f(210 + pix1, 120 + pix2)), pos_b[make_pair(1, 2)] = 7;
			if (i == 8)	pos_m[i] = make_pair(2, 2), circle[i].setPosition(Vector2f(210 + pix1, 210 + pix2)), pos_b[make_pair(2, 2)] = 8;
		}
	}
};

int checkEnd(Board &A, Board &B, Board &C, Board &D)
{

	set<int> NumOfWinner;

	int GenMatr[6][6]; // general matrix

	/*Making general matrix*/

	for (int Q = 0; Q < 9; Q++)
		GenMatr[A.pos_m[Q].first][A.pos_m[Q].second] = ((A.circle[Q].getFillColor() == Color::White) ? 1 : (((A.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[B.pos_m[Q].first][B.pos_m[Q].second + 3] = ((B.circle[Q].getFillColor() == Color::White) ? 1 : (((B.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[C.pos_m[Q].first + 3][C.pos_m[Q].second] = ((C.circle[Q].getFillColor() == Color::White) ? 1 : (((C.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[D.pos_m[Q].first + 3][D.pos_m[Q].second + 3] = ((D.circle[Q].getFillColor() == Color::White) ? 1 : (((D.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	set<int> colors;

	/*Horizontal checking*/

	for (int Q = 0; Q < 3; Q++)
	{
		for (int i = 0; i < 5; i++) colors.insert(GenMatr[Q][i]);
		if (colors.size() == 1 && (*colors.begin())!=0)
		{
			A.circle[A.pos_b[make_pair(Q, 0)]].setFillColor(Color::Red);
			A.circle[A.pos_b[make_pair(Q, 1)]].setFillColor(Color::Red);
			A.circle[A.pos_b[make_pair(Q, 2)]].setFillColor(Color::Red);
			B.circle[B.pos_b[make_pair(Q, 0)]].setFillColor(Color::Red);
			B.circle[B.pos_b[make_pair(Q, 1)]].setFillColor(Color::Red);
			NumOfWinner.insert (*colors.begin());
		}

		colors.clear();

		for (int i = 1; i < 6; i++) colors.insert(GenMatr[Q][i]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			A.circle[A.pos_b[make_pair(Q, 1)]].setFillColor(Color::Red);
			A.circle[A.pos_b[make_pair(Q, 2)]].setFillColor(Color::Red);
			B.circle[B.pos_b[make_pair(Q, 0)]].setFillColor(Color::Red);
			B.circle[B.pos_b[make_pair(Q, 1)]].setFillColor(Color::Red);
			B.circle[B.pos_b[make_pair(Q, 2)]].setFillColor(Color::Red);
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();
	}

	for (int Q = 3; Q < 6; Q++)
	{
		for (int i = 0; i < 5; i++) colors.insert(GenMatr[Q][i]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			C.circle[C.pos_b[make_pair(Q%3, 0)]].setFillColor(Color::Red);
			C.circle[C.pos_b[make_pair(Q%3, 1)]].setFillColor(Color::Red);
			C.circle[C.pos_b[make_pair(Q%3, 2)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(Q%3, 0)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(Q%3, 1)]].setFillColor(Color::Red);
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();

		for (int i = 1; i < 6; i++) colors.insert(GenMatr[Q][i]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			C.circle[C.pos_b[make_pair(Q%3, 1)]].setFillColor(Color::Red);
			C.circle[C.pos_b[make_pair(Q%3, 2)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(Q%3, 0)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(Q%3, 1)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(Q%3, 2)]].setFillColor(Color::Red);
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();
	}

	/*Vertical checking*/

	for (int Q = 0; Q < 3; Q++)
	{
		for (int i = 0; i < 5; i++) colors.insert(GenMatr[i][Q]);
		if (colors.size() == 1 && (*colors.begin()) != 0)
		{
			A.circle[A.pos_b[make_pair(0, Q)]].setFillColor(Color::Red);
			A.circle[A.pos_b[make_pair(1, Q)]].setFillColor(Color::Red);
			A.circle[A.pos_b[make_pair(2, Q)]].setFillColor(Color::Red);
			C.circle[C.pos_b[make_pair(0, Q)]].setFillColor(Color::Red);
			C.circle[C.pos_b[make_pair(1, Q)]].setFillColor(Color::Red);
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();

		for (int i = 1; i < 6; i++) colors.insert(GenMatr[i][Q]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			A.circle[A.pos_b[make_pair(1, Q)]].setFillColor(Color::Red);
			A.circle[A.pos_b[make_pair(2, Q)]].setFillColor(Color::Red);
			C.circle[C.pos_b[make_pair(0, Q)]].setFillColor(Color::Red);
			C.circle[C.pos_b[make_pair(1, Q)]].setFillColor(Color::Red);
			C.circle[C.pos_b[make_pair(2, Q)]].setFillColor(Color::Red);
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();
	}

	for (int Q = 3; Q < 6; Q++)
	{
		for (int i = 0; i < 5; i++) colors.insert(GenMatr[i][Q]);
		if (colors.size() == 1 && (*colors.begin()) != 0)
		{
			B.circle[B.pos_b[make_pair(0, Q%3)]].setFillColor(Color::Red);
			B.circle[B.pos_b[make_pair(1, Q%3)]].setFillColor(Color::Red);
			B.circle[B.pos_b[make_pair(2, Q%3)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(0, Q%3)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(1, Q%3)]].setFillColor(Color::Red);
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();

		for (int i = 1; i < 6; i++) colors.insert(GenMatr[i][Q]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			B.circle[B.pos_b[make_pair(1, Q%3)]].setFillColor(Color::Red);
			B.circle[B.pos_b[make_pair(2, Q%3)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(0, Q%3)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(1, Q%3)]].setFillColor(Color::Red);
			D.circle[D.pos_b[make_pair(2, Q%3)]].setFillColor(Color::Red);
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();
	}

	/*Diagonal checking*/

	colors.insert(GenMatr[0][1]); colors.insert(GenMatr[1][2]); colors.insert(GenMatr[2][3]); colors.insert(GenMatr[3][4]); colors.insert(GenMatr[4][5]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		A.circle[A.pos_b[make_pair(0, 1)]].setFillColor(Color::Red);
		A.circle[A.pos_b[make_pair(1, 2)]].setFillColor(Color::Red);
		B.circle[B.pos_b[make_pair(2, 0)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(0, 1)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(1, 2)]].setFillColor(Color::Red);
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[1][0]); colors.insert(GenMatr[2][1]); colors.insert(GenMatr[3][2]); colors.insert(GenMatr[4][3]); colors.insert(GenMatr[5][4]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		A.circle[A.pos_b[make_pair(1, 0)]].setFillColor(Color::Red);
		A.circle[A.pos_b[make_pair(2, 1)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(0, 2)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(1, 0)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(2, 1)]].setFillColor(Color::Red);
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[0][0]); colors.insert(GenMatr[1][1]); colors.insert(GenMatr[2][2]); colors.insert(GenMatr[3][3]); colors.insert(GenMatr[4][4]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		A.circle[A.pos_b[make_pair(0, 0)]].setFillColor(Color::Red);
		A.circle[A.pos_b[make_pair(1, 1)]].setFillColor(Color::Red);
		A.circle[A.pos_b[make_pair(2, 2)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(0, 0)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(1, 1)]].setFillColor(Color::Red);
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[1][1]); colors.insert(GenMatr[2][2]); colors.insert(GenMatr[3][3]); colors.insert(GenMatr[4][4]); colors.insert(GenMatr[5][5]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		A.circle[A.pos_b[make_pair(1, 1)]].setFillColor(Color::Red);
		A.circle[A.pos_b[make_pair(2, 2)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(2, 2)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(0, 0)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(1, 1)]].setFillColor(Color::Red);
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[0][5]); colors.insert(GenMatr[1][4]); colors.insert(GenMatr[2][3]); colors.insert(GenMatr[3][2]); colors.insert(GenMatr[4][1]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		B.circle[B.pos_b[make_pair(0, 2)]].setFillColor(Color::Red);
		B.circle[B.pos_b[make_pair(1, 1)]].setFillColor(Color::Red);
		B.circle[B.pos_b[make_pair(2, 0)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(0, 2)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(1, 1)]].setFillColor(Color::Red);
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[5][0]); colors.insert(GenMatr[1][4]); colors.insert(GenMatr[2][3]); colors.insert(GenMatr[3][2]); colors.insert(GenMatr[4][1]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		B.circle[B.pos_b[make_pair(2, 0)]].setFillColor(Color::Red);
		B.circle[B.pos_b[make_pair(1, 1)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(2, 0)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(0, 2)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(1, 1)]].setFillColor(Color::Red);
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[0][4]); colors.insert(GenMatr[1][3]); colors.insert(GenMatr[2][2]); colors.insert(GenMatr[3][1]); colors.insert(GenMatr[4][0]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		B.circle[B.pos_b[make_pair(0, 1)]].setFillColor(Color::Red);
		B.circle[B.pos_b[make_pair(1, 0)]].setFillColor(Color::Red);
		A.circle[A.pos_b[make_pair(2, 2)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(0, 1)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(1, 0)]].setFillColor(Color::Red);
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[1][5]); colors.insert(GenMatr[2][4]); colors.insert(GenMatr[3][3]); colors.insert(GenMatr[4][2]); colors.insert(GenMatr[5][1]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		B.circle[B.pos_b[make_pair(1, 2)]].setFillColor(Color::Red);
		B.circle[B.pos_b[make_pair(2, 1)]].setFillColor(Color::Red);
		D.circle[D.pos_b[make_pair(0, 0)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(1, 2)]].setFillColor(Color::Red);
		C.circle[C.pos_b[make_pair(2, 1)]].setFillColor(Color::Red);
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	if (NumOfWinner.size())
	{
		if (NumOfWinner.size() == 1) return *(NumOfWinner.begin()); else 
			return -1;
	}
	return 0;

}

int cEnd(Board A, Board B, Board C, Board D, int x, int y, int Pl)
{

	set<int> NumOfWinner;

	int GenMatr[6][6]; // general matrix

	/*Making general matrix*/

	for (int Q = 0; Q < 9; Q++)
		GenMatr[A.pos_m[Q].first][A.pos_m[Q].second] = ((A.circle[Q].getFillColor() == Color::White) ? 1 : (((A.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[B.pos_m[Q].first][B.pos_m[Q].second + 3] = ((B.circle[Q].getFillColor() == Color::White) ? 1 : (((B.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[C.pos_m[Q].first + 3][C.pos_m[Q].second] = ((C.circle[Q].getFillColor() == Color::White) ? 1 : (((C.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[D.pos_m[Q].first + 3][D.pos_m[Q].second + 3] = ((D.circle[Q].getFillColor() == Color::White) ? 1 : (((D.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	GenMatr[x][y] = Pl;

	set<int> colors;

	/*Horizontal checking*/

	for (int Q = 0; Q < 3; Q++)
	{
		for (int i = 0; i < 5; i++) colors.insert(GenMatr[Q][i]);
		if (colors.size() == 1 && (*colors.begin()) != 0)
		{
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();

		for (int i = 1; i < 6; i++) colors.insert(GenMatr[Q][i]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();
	}

	for (int Q = 3; Q < 6; Q++)
	{
		for (int i = 0; i < 5; i++) colors.insert(GenMatr[Q][i]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();

		for (int i = 1; i < 6; i++) colors.insert(GenMatr[Q][i]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();
	}

	/*Vertical checking*/

	for (int Q = 0; Q < 3; Q++)
	{
		for (int i = 0; i < 5; i++) colors.insert(GenMatr[i][Q]);
		if (colors.size() == 1 && (*colors.begin()) != 0)
		{
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();

		for (int i = 1; i < 6; i++) colors.insert(GenMatr[i][Q]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();
	}

	for (int Q = 3; Q < 6; Q++)
	{
		for (int i = 0; i < 5; i++) colors.insert(GenMatr[i][Q]);
		if (colors.size() == 1 && (*colors.begin()) != 0)
		{
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();

		for (int i = 1; i < 6; i++) colors.insert(GenMatr[i][Q]);
		if (colors.size() == 1 && (*colors.begin()))
		{
			NumOfWinner.insert(*colors.begin());
		}

		colors.clear();
	}

	/*Diagonal checking*/

	colors.insert(GenMatr[0][1]); colors.insert(GenMatr[1][2]); colors.insert(GenMatr[2][3]); colors.insert(GenMatr[3][4]); colors.insert(GenMatr[4][5]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[1][0]); colors.insert(GenMatr[2][1]); colors.insert(GenMatr[3][2]); colors.insert(GenMatr[4][3]); colors.insert(GenMatr[5][4]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[0][0]); colors.insert(GenMatr[1][1]); colors.insert(GenMatr[2][2]); colors.insert(GenMatr[3][3]); colors.insert(GenMatr[4][4]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[1][1]); colors.insert(GenMatr[2][2]); colors.insert(GenMatr[3][3]); colors.insert(GenMatr[4][4]); colors.insert(GenMatr[5][5]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[0][5]); colors.insert(GenMatr[1][4]); colors.insert(GenMatr[2][3]); colors.insert(GenMatr[3][2]); colors.insert(GenMatr[4][1]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[5][0]); colors.insert(GenMatr[1][4]); colors.insert(GenMatr[2][3]); colors.insert(GenMatr[3][2]); colors.insert(GenMatr[4][1]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[0][4]); colors.insert(GenMatr[1][3]); colors.insert(GenMatr[2][2]); colors.insert(GenMatr[3][1]); colors.insert(GenMatr[4][0]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	colors.insert(GenMatr[1][5]); colors.insert(GenMatr[2][4]); colors.insert(GenMatr[3][3]); colors.insert(GenMatr[4][2]); colors.insert(GenMatr[5][1]);
	if (colors.size() == 1 && (*colors.begin()))
	{
		NumOfWinner.insert(*colors.begin());
	}
	else
		colors.clear();

	if (NumOfWinner.size())
	{
		if (NumOfWinner.size() == 1) return *(NumOfWinner.begin()); else
			return -1;
	}
	return 0;

}

void rotate(Board &x, int dir)
{
	map <pair<int, int>, int> w = x.pos_b;
	for (int Q = 0; Q < 9; Q++)
	{
		if (dir == -1)
			x.pos_m[Q] = left_rotate[x.pos_m[Q]], x.pos_b[x.pos_m[Q]] = w[right_rotate[x.pos_m[Q]]];
		else
			x.pos_m[Q] = right_rotate[x.pos_m[Q]], x.pos_b[x.pos_m[Q]] = w[left_rotate[x.pos_m[Q]]];
	}

}

pair<int, int> make_move(Board &A, Board &B, Board &C, Board &D)
{
	int GenMatr[6][6]; // general matrix

	/*Making general matrix*/

	for (int Q = 0; Q < 9; Q++)
		GenMatr[A.pos_m[Q].first][A.pos_m[Q].second] = ((A.circle[Q].getFillColor() == Color::White) ? 1 : (((A.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[B.pos_m[Q].first][B.pos_m[Q].second + 3] = ((B.circle[Q].getFillColor() == Color::White) ? 1 : (((B.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[C.pos_m[Q].first + 3][C.pos_m[Q].second] = ((C.circle[Q].getFillColor() == Color::White) ? 1 : (((C.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));

	for (int Q = 0; Q < 9; Q++)
		GenMatr[D.pos_m[Q].first + 3][D.pos_m[Q].second + 3] = ((D.circle[Q].getFillColor() == Color::White) ? 1 : (((D.circle[Q].getFillColor() == Color::Black) ? 2 : 0)));
	
	for (int i = 0; i < 6;i++)
	for (int j = 0; j < 6; j++)
	{
		if (!GenMatr[i][j] && (cEnd(A, B, C, D, i, j, 1) || cEnd(A, B, C, D, i, j, 2))) return make_pair(i, j);
	}

	vector<pair<int, int> > hor;

	for (int i = 0; i < 6; i++)
	for (int j = 0; j <= 4; j++)
	{
		bool ok = true;
		for (int k = j; k < j + 2; k++)
		if (GenMatr[i][k] != 1) ok = false;
		if (ok) hor.push_back(make_pair(i, j));
	}

	for (int i = 0; i < hor.size(); i++)
	{
		if (hor[i].second>0 && !GenMatr[hor[i].first][hor[i].second - 1]) return make_pair(hor[i].first, hor[i].second - 1);
		if (hor[i].second + 2 < 6 && !GenMatr[hor[i].first][hor[i].second + 2]) return make_pair(hor[i].first, hor[i].second + 2);
	}

	hor.clear();

	for (int j = 0; j < 6; j++)
	for (int i = 0; i <= 4; i++)
	{
		bool ok = true;
		for (int k = i; k < i + 2; k++)
		if (GenMatr[k][j] != 1) ok = false;
		if (ok) hor.push_back(make_pair(i, j));
	}

	for (int i = 0; i < hor.size(); i++)
	{
		if (hor[i].first>0 && !GenMatr[hor[i].first - 1][hor[i].second]) return make_pair(hor[i].first - 1, hor[i].second);
		if (hor[i].first + 2 < 6 && !GenMatr[hor[i].first + 2][hor[i].second]) return make_pair(hor[i].first + 2, hor[i].second);
	}

	hor.clear();

	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 6; j++)
	{
		bool ok = true;
		for (int k = 0; k < 2; k++)
		{
			if (i + k > 5 || j + k > 5) ok = false;
			if (GenMatr[i + k][j + k] != 1) ok = false;
		}
		if (ok) hor.push_back(make_pair(i, j));
	}

	for (int i = 0; i < hor.size(); i++)
	{
		if (hor[i].first - 1 >= 0 && hor[i].second - 1 >= 0 && !GenMatr[hor[i].first - 1][hor[i].second - 1]) return make_pair(hor[i].first - 1, hor[i].second - 1);
		if (hor[i].first + 2 < 6 && hor[i].second + 2 < 6 && !GenMatr[hor[i].first + 2][hor[i].second + 2]) return make_pair(hor[i].first + 2, hor[i].second + 2);
	}

	hor.clear();

	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 6; j++)
	{
		bool ok = true;
		for (int k = 0; k < 2; k++)
		{
			if (i - k < 0 || j - k < 0) ok = false;
			if (GenMatr[i - k][j - k] != 1) ok = false;
		}
		if (ok) hor.push_back(make_pair(i, j));
	}

	for (int i = 0; i < hor.size(); i++)
	{
		if (hor[i].first - 1 >= 0 && hor[i].second + 1 < 6 && !GenMatr[hor[i].first - 1][hor[i].second + 1]) return make_pair(hor[i].first - 1, hor[i].second + 1);
		if (hor[i].first + 2 < 6 && hor[i].second - 2 >= 0 && !GenMatr[hor[i].first + 2][hor[i].second - 2]) return make_pair(hor[i].first + 2, hor[i].second - 2);
	}

	hor.clear();

	for (int i = 0; i < 6;i++)
	for (int j = 0; j <= 3; j++)
	{
		bool ok = true;
		for (int k = j; k < j + 3; k++)
		if (GenMatr[i][k] != 1) ok = false;
		if (ok) hor.push_back(make_pair(i, j));
	}

	for (int i = 0; i < hor.size(); i++)
	{
		if (hor[i].second>0 && !GenMatr[hor[i].first][hor[i].second - 1]) return make_pair(hor[i].first, hor[i].second - 1);
		if (hor[i].second + 3 < 6 && !GenMatr[hor[i].first][hor[i].second + 3]) return make_pair(hor[i].first, hor[i].second + 3);
	}

	hor.clear();

	for (int j = 0; j < 6; j++)
	for (int i = 0; i <= 3; i++)
	{
		bool ok = true;
		for (int k = i; k < i + 3; k++)
		if (GenMatr[k][j] != 1) ok = false;
		if (ok) hor.push_back(make_pair(i, j));
	}

	for (int i = 0; i < hor.size(); i++)
	{
		if (hor[i].first>0 && !GenMatr[hor[i].first - 1][hor[i].second]) return make_pair(hor[i].first - 1, hor[i].second);
		if (hor[i].first + 3 < 6 && !GenMatr[hor[i].first + 3][hor[i].second]) return make_pair(hor[i].first + 3, hor[i].second);
	}

	hor.clear();

	for (int i = 0; i < 6;i++)
	for (int j = 0; j < 6; j++)
	{
		bool ok = true;
		for (int k = 0; k < 3; k++)
		{
			if (i + k > 5 || j + k > 5) ok = false;
			if (GenMatr[i + k][j + k] != 1) ok = false;
		}
		if (ok) hor.push_back(make_pair(i, j));
	}

	for (int i = 0; i < hor.size(); i++)
	{
		if (hor[i].first - 1 >= 0 && hor[i].second - 1 >= 0 && !GenMatr[hor[i].first - 1][hor[i].second - 1]) return make_pair(hor[i].first - 1, hor[i].second - 1);
		if (hor[i].first + 3 < 6 && hor[i].second + 3 < 6 && !GenMatr[hor[i].first + 3][hor[i].second + 3]) return make_pair(hor[i].first + 3, hor[i].second + 3);
	}

	hor.clear();

	for (int i = 0; i < 6; i++)
	for (int j = 0; j < 6; j++)
	{
		bool ok = true;
		for (int k = 0; k < 3; k++)
		{
			if (i - k < 0 || j - k < 0) ok = false;
			if (GenMatr[i - k][j - k] != 1) ok = false;
		}
		if (ok) hor.push_back(make_pair(i, j));
	}

	for (int i = 0; i < hor.size(); i++)
	{
		if (hor[i].first - 1 >= 0 && hor[i].second + 1 < 6 && !GenMatr[hor[i].first - 1][hor[i].second + 1]) return make_pair(hor[i].first - 1, hor[i].second + 1);
		if (hor[i].first + 3 < 6 && hor[i].second - 3 >= 0 && !GenMatr[hor[i].first + 3][hor[i].second - 3]) return make_pair(hor[i].first + 3, hor[i].second - 3);
	}

	if (GenMatr[1][1] == 0) return make_pair(1, 1);
	if (GenMatr[1][4] == 0) return make_pair(1, 4);
	if (GenMatr[4][1] == 0) return make_pair(4, 1);
	if (GenMatr[4][4] == 0) return make_pair(4, 4);

	srand(time(0));

	int x, y;

	while (GenMatr[x = rand() % 6][y = rand() % 6]) continue;

	return make_pair(x, y);

}

bool cr(Board A, Board B, Board C, Board D, int num, int p)
{
	if (p == 1) p = 1; else p = -1;
	if (num == 1) rotate(A, p);
	if (num == 2) rotate(B, p);
	if (num == 3) rotate(C, p);
	if (num == 4) rotate(D, p);
	if (checkEnd(A, B, C, D)) return false;
	return true;
}

int main()
{
	end:

	/*Creating right_rotate map*/
	
	right_rotate[make_pair(0, 0)] = make_pair(0, 2);
	right_rotate[make_pair(1, 0)] = make_pair(0, 1);
	right_rotate[make_pair(2, 0)] = make_pair(0, 0);
	right_rotate[make_pair(0, 1)] = make_pair(1, 2);
	right_rotate[make_pair(1, 1)] = make_pair(1, 1);
	right_rotate[make_pair(2, 1)] = make_pair(1, 0);
	right_rotate[make_pair(0, 2)] = make_pair(2, 2);
	right_rotate[make_pair(1, 2)] = make_pair(2, 1);
	right_rotate[make_pair(2, 2)] = make_pair(2, 0);

	/*Creating left_rotate map*/

	left_rotate[make_pair(0, 0)] = make_pair(2, 0);
	left_rotate[make_pair(1, 0)] = make_pair(2, 1);
	left_rotate[make_pair(2, 0)] = make_pair(2, 2);
	left_rotate[make_pair(0, 1)] = make_pair(1, 0);
	left_rotate[make_pair(1, 1)] = make_pair(1, 1);
	left_rotate[make_pair(2, 1)] = make_pair(1, 2);
	left_rotate[make_pair(0, 2)] = make_pair(0, 0);
	left_rotate[make_pair(1, 2)] = make_pair(0, 1);
	left_rotate[make_pair(2, 2)] = make_pair(0, 2);

	sf::ContextSettings Hitler;
	Hitler.antialiasingLevel = 4;
	RenderWindow window(VideoMode(830,800), "Pentago", sf::Style::Titlebar|sf::Style::Close, Hitler);

	/*Text*/

	Font font;
	font.loadFromFile("COPRGTL.ttf");
	Text text("", font, 60);
	text.setColor(Color::Yellow);
	text.setStyle(sf::Text::Bold);
	Text ToMainMenu("Press 'N' to go to main menu \n           or 'Q' to exit", font, 25);
	ToMainMenu.setColor(Color::Yellow);
	ToMainMenu.setStyle(sf::Text::Bold | sf::Text::Italic);
	ToMainMenu.setPosition(200, 690);

	/*Background*/

	Texture Reich;
	Reich.loadFromFile("zighail.png");
	Sprite Fuhrer;
	Fuhrer.setTexture(Reich);
	Fuhrer.setTextureRect(IntRect(0, 0, 830, 800));
	Fuhrer.setPosition(0, 0);

	/*Board texture*/

	Texture t;
	t.loadFromFile("wood1.png");
	
	/*Arrow texture*/

	Image arrow1;
	arrow1.loadFromFile("arrow.png");
	arrow1.createMaskFromColor(Color(0, 0, 255));
	Texture Arr1;
	Arr1.loadFromImage(arrow1);
	
	Sprite arrowA_R, arrowA_L, arrowB_L, arrowB_R, arrowC_L, arrowC_R, arrowD_L, arrowD_R; // arrows

	/*A arrows*/

	arrowA_L.setTexture(Arr1);
	arrowA_R.setTexture(Arr1);
	arrowA_L.setRotation(90);
	arrowA_R.setPosition(100, 20);
	arrowA_L.setPosition(80, 100);

	/*B arrows*/

	arrowB_L.setTexture(Arr1);
	arrowB_R.setTexture(Arr1);
	arrowB_L.setRotation(-180);
	arrowB_R.setRotation(90);
	arrowB_R.setPosition(800, 100);
	arrowB_L.setPosition(700, 90);

	/*C arrows*/

	arrowC_L.setTexture(Arr1);
	arrowC_R.setTexture(Arr1);
	arrowC_L.setRotation(-90);
	arrowC_R.setPosition(100, 700);
	arrowC_L.setPosition(10, 700);

	/*D arrows*/

	arrowD_L.setTexture(Arr1); 
	arrowD_R.setTexture(Arr1);
	arrowD_R.setPosition(690, 775);
	arrowD_L.setPosition(730, 700);
	arrowD_L.setRotation(-90);
	arrowD_R.setRotation(180);

	/*Boards settings*/

	Board A(100,100),B(400,100),C(100,400),D(400,400);
	
	A.rect.setTexture(t);
	A.rect.setTextureRect(IntRect(0, 0, 300, 300));
	A.rect.setOrigin(150, 150);
	A.rect.setPosition(250, 250);

	B.rect.setTexture(t);
	B.rect.setTextureRect(IntRect(0, 0, 300, 300));
	B.rect.setOrigin(150, 150);
	B.rect.setPosition(550, 250);

	C.rect.setTexture(t);
	C.rect.setTextureRect(IntRect(0, 0, 300, 300));
	C.rect.setOrigin(150, 150);
	C.rect.setPosition(250, 550);

	D.rect.setTexture(t);
	D.rect.setTextureRect(IntRect(0, 0, 300, 300));
	D.rect.setOrigin(150, 150);
	D.rect.setPosition(550, 550);


	bool EndOfGame = false;
	int WinnerCode = -1;
	int balls = 0;

	double angle = 0;
	bool ok = false;

	bool arrow_display = false; // need to rotate
	bool check = false; // some point was checked in the previous step

	int num_of_board = 0, num_of_rotate_board = 0;
	int Player = 0;

	bool mv = false;

	menu(window);

	while (window.isOpen())
	{

		int k = 0,x,y;

		if (balls == 36) EndOfGame = true;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos = window.mapPixelToCoords(pixelPos);

		if ((Keyboard::isKeyPressed(Keyboard::N)) && EndOfGame)
		{
			goto end;
		}

		else

		if ((Keyboard::isKeyPressed(Keyboard::Q)) && EndOfGame)
		{
			window.close();
		}

		else
		
		if (Player % 2 && !mv && !EndOfGame)
		{
			srand(time(0));
			pair<int, int> pmove = make_move(A, B, C, D);
			while (!cr(A, B, C, D, num_of_rotate_board = rand() % 4 + 1, k = k = rand() % 2 + 1)) continue;
			if (pmove.first >= 0 && pmove.first < 3 && pmove.second >= 0 && pmove.second < 3) num_of_board = 1;
			if (pmove.first >= 0 && pmove.first < 3 && pmove.second >= 3 && pmove.second < 6) num_of_board = 2;
			if (pmove.first >= 3 && pmove.first < 6 && pmove.second >= 0 && pmove.second < 3) num_of_board = 3;
			if (pmove.first >= 3 && pmove.first < 6 && pmove.second >= 3 && pmove.second < 6) num_of_board = 4;
			x = pmove.first % 3;
			y = pmove.second % 3;
			mv = true;
		}

		if ((event.type == Event::MouseButtonPressed && event.key.code == Mouse::Left && !EndOfGame) || (mv && !EndOfGame))
		{
				
			if (!mv){

				if (arrowA_L.getGlobalBounds().contains(pos.x, pos.y)) k = 1, num_of_rotate_board = 1;
				if (arrowA_R.getGlobalBounds().contains(pos.x, pos.y)) k = 2, num_of_rotate_board = 1;

				if (arrowB_L.getGlobalBounds().contains(pos.x, pos.y)) k = 1, num_of_rotate_board = 2;
				if (arrowB_R.getGlobalBounds().contains(pos.x, pos.y)) k = 2, num_of_rotate_board = 2;

				if (arrowC_L.getGlobalBounds().contains(pos.x, pos.y)) k = 2, num_of_rotate_board = 3;
				if (arrowC_R.getGlobalBounds().contains(pos.x, pos.y)) k = 1, num_of_rotate_board = 3;

				if (arrowD_L.getGlobalBounds().contains(pos.x, pos.y)) k = 1, num_of_rotate_board = 4;
				if (arrowD_R.getGlobalBounds().contains(pos.x, pos.y)) k = 2, num_of_rotate_board = 4;
			}

			/*Check points on board A*/
			if (Player%2==0 && !mv)
			{
				for (int Q = 0; Q < 9; Q++)
				if (A.circle[Q].getGlobalBounds().contains(pos.x, pos.y) && (A.circle[Q].getFillColor() == Color::Green) && !arrow_display)
				{
					balls++;
					A.circle[Q].setFillColor((Player % 2) ? (Color::Black) : (Color::White));
					A.matrix[A.pos_m[Q].first][A.pos_m[Q].second] = ((Player % 2) ? 2 : 1);
					if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
					arrow_display = true;
					check = true;
					break;
				}
			}

			else
			if (Player%2 && num_of_board==1)
			{
				balls++;
				int Q = A.pos_b[make_pair(x, y)];
				A.circle[Q].setFillColor((Player % 2) ? (Color::Black) : (Color::White));
				A.matrix[A.pos_m[Q].first][A.pos_m[Q].second] = ((Player % 2) ? 2 : 1);
				if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
				arrow_display = true;
				check = true;
			}
			
			/*Check points on board B*/
			if (Player % 2 == 0 && !mv)
				{
				for (int Q = 0; Q < 9; Q++)
				if (B.circle[Q].getGlobalBounds().contains(pos.x, pos.y) && (B.circle[Q].getFillColor() == Color::Green) && !arrow_display)
				{
					balls++;
					B.circle[Q].setFillColor((Player % 2) ? (Color::Black) : (Color::White));
					B.matrix[B.pos_m[Q].first][B.pos_m[Q].second] = ((Player % 2) ? 2 : 1);
					if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
					arrow_display = true;
					check = true;
					break;
				}
				}
			else
			if (Player % 2 && num_of_board == 2)
				{
					balls++;
					int Q = B.pos_b[make_pair(x, y)];
					B.circle[Q].setFillColor((Player % 2) ? (Color::Black) : (Color::White));
					B.matrix[B.pos_m[Q].first][B.pos_m[Q].second] = ((Player % 2) ? 2 : 1);
					if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
					arrow_display = true;
					check = true;
				}

			/*Check points on board C*/

			if (Player % 2 == 0 && !mv)
			{
				for (int Q = 0; Q < 9; Q++)
				if (C.circle[Q].getGlobalBounds().contains(pos.x, pos.y) && (C.circle[Q].getFillColor() == Color::Green) && !arrow_display)
				{
					balls++;
					C.circle[Q].setFillColor((Player % 2) ? (Color::Black) : (Color::White));
					C.matrix[C.pos_m[Q].first][C.pos_m[Q].second] = ((Player % 2) ? 2 : 1);
					if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
					arrow_display = true;
					check = true;
					break;
				}
			}
				else
				if (Player % 2 && num_of_board == 3)
				{
					balls++;
					int Q = C.pos_b[make_pair(x, y)];
					C.circle[Q].setFillColor((Player % 2) ? (Color::Black) : (Color::White));
					C.matrix[C.pos_m[Q].first][C.pos_m[Q].second] = ((Player % 2) ? 2 : 1);
					if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
					arrow_display = true;
					check = true;
				}
			/*Check points on board D*/
			if (Player % 2 == 0 && !mv)
			{
				for (int Q = 0; Q < 9; Q++)
				if (D.circle[Q].getGlobalBounds().contains(pos.x, pos.y) && (D.circle[Q].getFillColor() == Color::Green) && !arrow_display)
				{
					balls++;
					D.circle[Q].setFillColor((Player % 2) ? (Color::Black) : (Color::White));
					D.matrix[D.pos_m[Q].first][D.pos_m[Q].second] = ((Player % 2) ? 2 : 1);
					if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
					arrow_display = true;
					check = true;
					break;
				}
				}
				else
				if (Player % 2 && num_of_board == 4)
				{
					balls++;
					int Q = D.pos_b[make_pair(x, y)];
					D.circle[Q].setFillColor((Player % 2) ? (Color::Black) : (Color::White));
					D.matrix[D.pos_m[Q].first][D.pos_m[Q].second] = ((Player % 2) ? 2 : 1);
					if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
					arrow_display = true;
					check = true;
				}
			/*Need rotation*/

			if ((k && check || mv) && !EndOfGame)
			{
				double delta = 0.;

				if (k == 1) delta = -0.5; else delta = 0.5;

				bool ok1 = false;

				double counter = 0;

				if (delta == 0.5 || delta == -0.5)

				while (counter >= -90 || counter <= 90)
				{
					if (num_of_rotate_board == 1)	A.rect.setRotation(A.rect.getRotation() + delta);
					if (num_of_rotate_board == 2)	B.rect.setRotation(B.rect.getRotation() + delta);
					if (num_of_rotate_board == 3)	C.rect.setRotation(C.rect.getRotation() + delta);
					if (num_of_rotate_board == 4)	D.rect.setRotation(D.rect.getRotation() + delta);

					for (int i = 0; i < 9; i++)
					{
						Vector2f pt;
						if (num_of_rotate_board == 1) pt = A.circle[i].getPosition();
						if (num_of_rotate_board == 2) pt = B.circle[i].getPosition();
						if (num_of_rotate_board == 3) pt = C.circle[i].getPosition();
						if (num_of_rotate_board == 4) pt = D.circle[i].getPosition();

						double center_x = 0.0, center_y = 0.;

						if (num_of_rotate_board == 1) center_x = A.center_x, center_y = A.center_y;
						if (num_of_rotate_board == 2) center_x = B.center_x, center_y = B.center_y;
						if (num_of_rotate_board == 3) center_x = C.center_x, center_y = C.center_y;
						if (num_of_rotate_board == 4) center_x = D.center_x, center_y = D.center_y;

						double rad = -delta * cp / 180.0;
						double cs = cos(rad), sn = sin(rad);
						double new_x = (pt.x - center_x) * cs - ((800 - pt.y) - (800 - center_y)) * sn + center_x;
						double new_y = ((800 - pt.y) - (800 - center_y)) * cs + (pt.x - center_x) * sn + (800 - center_y);
						new_y = 800 - new_y;
						if (num_of_rotate_board == 1) A.circle[i].setPosition(new_x, new_y);
						if (num_of_rotate_board == 2) B.circle[i].setPosition(new_x, new_y);
						if (num_of_rotate_board == 3) C.circle[i].setPosition(new_x, new_y);
						if (num_of_rotate_board == 4) D.circle[i].setPosition(new_x, new_y);
					}
					counter += delta;
					if (counter < -90. + 0.5) break;
					if (counter > 90. - 0.5) break;
					window.clear();
					window.draw(Fuhrer);
					window.draw(arrowA_L);
					window.draw(arrowA_R);
					window.draw(arrowB_L);
					window.draw(arrowB_R);
					window.draw(arrowC_L);
					window.draw(arrowC_R);
					window.draw(arrowD_L);
					window.draw(arrowD_R);
					if (num_of_rotate_board != 1)
					{
						window.draw(A.rect);
						for (int i = 0; i < 9; i++) window.draw(A.circle[i]);
					}
					if (num_of_rotate_board != 2)
					{
						window.draw(B.rect);
						for (int i = 0; i < 9; i++) window.draw(B.circle[i]);
					}
					if (num_of_rotate_board != 3)
					{
						window.draw(C.rect);
						for (int i = 0; i < 9; i++) window.draw(C.circle[i]);
					}
					if (num_of_rotate_board != 4)
					{
						window.draw(D.rect);
						for (int i = 0; i < 9; i++) window.draw(D.circle[i]);
					}
					if (num_of_rotate_board == 1)
					{
						window.draw(A.rect);
						for (int i = 0; i < 9; i++) window.draw(A.circle[i]);
					}
					if (num_of_rotate_board == 2)
					{
						window.draw(B.rect);
						for (int i = 0; i < 9; i++) window.draw(B.circle[i]);
					}
					if (num_of_rotate_board == 3)
					{
						window.draw(C.rect);
						for (int i = 0; i < 9; i++) window.draw(C.circle[i]);
					}
					if (num_of_rotate_board == 4)
					{
						window.draw(D.rect);
						for (int i = 0; i < 9; i++) window.draw(D.circle[i]);
					}
					window.display();
				}
				if (num_of_rotate_board == 1) rotate(A, ((k == 1) ? -1 : 1));
				if (num_of_rotate_board == 2) rotate(B, ((k == 1) ? -1 : 1));
				if (num_of_rotate_board == 3) rotate(C, ((k == 1) ? -1 : 1));
				if (num_of_rotate_board == 4) rotate(D, ((k == 1) ? -1 : 1));
				if ((WinnerCode = checkEnd(A, B, C, D)) != 0) EndOfGame = true;
				check = false;
				arrow_display = false;
				{
					Player++;
					mv = false;
					num_of_board = -1;
					num_of_rotate_board = -1;
				}
			}
		}

		window.clear();
		window.draw(Fuhrer);
		window.draw(arrowA_L);
		window.draw(arrowA_R);
		window.draw(arrowB_L);
		window.draw(arrowB_R);
		window.draw(arrowC_L);
		window.draw(arrowC_R);
		window.draw(arrowD_L);
		window.draw(arrowD_R);
		window.draw(A.rect);
		window.draw(B.rect);
		window.draw(C.rect);
		window.draw(D.rect);
		for (int i = 0; i < 9; i++) window.draw(A.circle[i]);
		for (int i = 0; i < 9; i++) window.draw(B.circle[i]);
		for (int i = 0; i < 9; i++) window.draw(C.circle[i]);
		for (int i = 0; i < 9; i++) window.draw(D.circle[i]); 
		if (EndOfGame)
		{
			if (WinnerCode == 1)
			{
				text.setString("First player won");
				text.setPosition(120, 355);
			}

			else 
			if (WinnerCode == 2)
			{
				text.setString("Second player won");
				text.setPosition(100, 355);
			}
			else
			if (WinnerCode == 0 || WinnerCode == -1)
			{
				text.setString("Draw");
				text.setPosition(400, 350);
			}
			window.draw(text);
			window.draw(ToMainMenu);

		}
		window.display();
		this_thread::sleep_for(chrono::milliseconds(50));
	}

	return 0;
}