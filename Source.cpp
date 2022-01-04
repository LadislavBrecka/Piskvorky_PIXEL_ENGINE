#include<cmath>
#include<vector>
#include<string>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"


enum Ttype
{
	cross,
	circle,
};

struct object
{
	int x;
	int y;
	Ttype type;
	bool used;
};

struct CON
{
	int number;
	int x;
	int y;
};


class Piskvorky : public olc::PixelGameEngine
{
private:
	int cycle = 0;
	std::vector<object> obj;
	bool draw = false;
	int cross_score = 0, circle_score = 0;
	int spacing = 10;

public:

	bool checking(int _mx, int _my, const std::vector<object> vec)
	{
		int lenght = vec.capacity();

		for (int i = 0; i < lenght; i++)
			if (_mx == vec[i].x && _my == vec[i].y)
				return false;


		return true;
	}

	bool check4(CON * row, std::vector<object> &vec, int &pos, int arpos, int &m, int direction)
	{
		int nrow = 1;
		Ttype t;

		for (int i = 0; i < 7 - 1; i++)
		{
			if (row[i].number == 1 && row[i + 1].number == 1)
			{
				if (nrow == 1)
					pos = i;

				nrow++;

				if (direction == 0)
				{
					if (row[arpos].number == row[arpos + 1].number)
						m = 1;
				}
				else
				{
					if (row[arpos].number == row[arpos - 1].number)
						m = 1;
				}
			}

			else
			{
				nrow = 1;
				pos = 0;
			}

			if (nrow == 4)
			{
				for (int j = pos; j < pos + 4; j++)
					for (int k = 0; k < (signed)vec.size(); k++)
						if (vec[k].x == row[j].x && vec[k].y == row[j].y)
						{
							vec[k].used = true;
							t = vec[k].type;
						}
				
				if (t == circle)
					circle_score++;

				else if (t == cross)
					cross_score++;

				return true;
			}
		}

		return false;
	}


	void connecting(int _mx, int _my, std::vector<object> & vec, Ttype t)
	{
		int tx = 0, ty = 0;
		int ex, ey;
		CON _con[8];
		bool dir;
		int n = 0;
		int clicked_index;

		for (int i = 0; i < 7; i++)
		{
			_con[i].number = 0;
			_con[i].x = 0;
			_con[i].y = 0;
		}

		//Kontrola vodorovnej osy x
		ex = _mx - 3 * 10;

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < (signed)vec.size(); j++)
				if (vec[j].x == ex && vec[j].y == _my && vec[j].type == t && !vec[j].used)
				{
					if (ex == _mx)
						clicked_index = i;

					_con[i].number = 1;
					_con[i].x = vec[j].x;
					_con[i].y = vec[j].y;

					if (i < 4)
						dir = 0;

					else if (i > 4)
						dir = 1;
				}

			ex += 10;
		}

		if (check4(_con, vec, tx, clicked_index, n, dir))
		{
			if (!dir)
				tx = _mx - 3 * 10 + tx + 10 * n;

			else
				tx = _mx - 10 * n;

			DrawLine(tx, _my, tx + 3 * 10, _my);
		}

		//Nulovanie premennych pred dalsou kontrolou
		tx = 0; ty = 0; ex = 0;	ey = 0; n = 0;

		for (int i = 0; i < 8; i++)
		{
			_con[i].number = 0;
			_con[i].x = 0;
			_con[i].y = 0;
		}

		//Kontrola zvislej osy y
		ey = _my - 3 * 10;

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < (signed)vec.size(); j++)
				if (vec[j].x == _mx && vec[j].y == ey && vec[j].type == t && !vec[j].used)
				{
					if (ey == _mx)
						clicked_index = i;

					_con[i].number = 1;
					_con[i].x = vec[j].x;
					_con[i].y = vec[j].y;

					if (i < 4)
						dir = 0;

					else if (i > 4)
						dir = 1;
				}

			ey += 10;
		}

		if (check4(_con, vec, ty, clicked_index, n, dir))
		{
			if (!dir)
				ty = _my - 3 * 10 + ty + 10 * n;

			else
				ty = _my - 10 * n;

			DrawLine(_mx, ty, _mx, ty + 3 * 10);
		}

		//Nulovanie premennych pred dalsou kontrolou
		tx = 0; ty = 0;  ex = 0; ey = 0; n = 0;

		for (int i = 0; i < 8; i++)
		{
			_con[i].number = 0;
			_con[i].x = 0;
			_con[i].y = 0;
		}

		//Kontrola uhloprieèky 1
		ex = _mx - 3 * 10;
		ey = _my + 3 * 10;

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < (signed)vec.size(); j++)
				if (vec[j].x == ex && vec[j].y == ey && vec[j].type == t && !vec[j].used)
				{
					if (ey == _mx && ex == _mx)
						clicked_index = i;

					_con[i].number = 1;
					_con[i].x = vec[j].x;
					_con[i].y = vec[j].y;

					if (i < 4)
						dir = 0;

					else if (i > 4)
						dir = 1;
				}

			ex += 10;
			ey -= 10;
		}

		if (check4(_con, vec, tx, clicked_index, n, dir))
		{
			if (!dir)
			{
				tx = _mx - 3 * 10 + tx + 10 * n;
				ty = _my + 3 * 10 + ty - 10 * n;
			}

			else
			{
				tx = _mx - 10 * n;
				ty = _my + 10 * n;
			}

			DrawLine(tx, ty, tx + 3 * 10, ty - 3 * 10);
		}

		//Nulovanie premennych pred dalsou kontrolou
		tx = 0; ty = 0; ex = 0; ey = 0; n = 0;

		for (int i = 0; i < 8; i++)
		{
			_con[i].number = 0;
			_con[i].x = 0;
			_con[i].y = 0;
		}

		//Kontrola uhloprieèky 2
		ex = _mx - 3 * 10;
		ey = _my - 3 * 10;

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < (signed)vec.size(); j++)
				if (vec[j].x == ex && vec[j].y == ey && vec[j].type == t && !vec[j].used)
				{
					if (ey == _mx && ex == _mx)
						clicked_index = i;

					_con[i].number = 1;
					_con[i].x = vec[j].x;
					_con[i].y = vec[j].y;

					if (i < 4)
						dir = 0;

					else if (i > 4)
						dir = 1;
				}

			ex += 10;
			ey += 10;
		}

		if (check4(_con, vec, tx, clicked_index, n, dir))
		{
			if (!dir)
			{
				tx = _mx - 3 * 10 + tx + 10 * n;;
				ty = _my - 3 * 10 + ty + 10 * n;;
			}

			else
			{
				tx = _mx - 10 * n;;
				ty = _my - 10 * n;;
			}

			DrawLine(tx, ty, tx + 3 * 10, ty + 3 * 10);
		}
	}

	void DrawGrid(int spacing, olc::Pixel col)
	{
		for (int i = 1; i <= ScreenHeight(); i++)
			DrawLine(0, i * spacing, ScreenWidth(), i * spacing, col);

		for (int i = 0; i <= ScreenWidth(); i++)
			DrawLine(i * spacing, 10, i * spacing, ScreenHeight(), col);
	}

	void DrawCross(int xc, int yc, int r, olc::Pixel col)
	{
		int pL = xc - r, pR = xc + r;
		for (int i = yc - r; i < yc + r; i++)
		{
			for (int j = xc - r + 1; j < xc + r; j++)
			{
				if ((pL == j) || (pR == j))
					Draw(j, i, olc::RED);
			}
			pL++;
			pR--;
		}
	}

	Piskvorky()
	{
		sAppName = "PISKVORKY_GAME";
	}

	bool OnUserCreate() override
	{

		Clear(olc::BLACK);
		DrawGrid(10, olc::BLUE);

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		FillRect(0, 0, ScreenWidth(), 10, olc::BLACK);

		if (GetKey(olc::R).bHeld)
		{
			Clear(olc::BLACK);
			DrawGrid(10, olc::BLUE);
		}

		DrawString(1, 1, "CROSS score: " + std::to_string(cross_score), olc::RED);
		DrawString(225, 1, "CIRCLE score: " + std::to_string(circle_score), olc::YELLOW);

		if (GetMouse(0).bPressed)
		{
			int mx = GetMouseX();
			int my = GetMouseY();
			int dmx, dmy;

			dmx = mx % 10;
			dmy = my % 10;

			mx = mx - dmx + 5;
			my = my - dmy + 5;

			if ((cycle % 2) && checking(mx, my, obj))
			{
				DrawCircle(mx, my, 3, olc::YELLOW);
				draw = true;
				obj.insert(obj.begin(), { mx, my, circle });
				connecting(mx, my, obj, circle);
			}

			else if (checking(mx, my, obj))
			{
				DrawCross(mx, my, 4, olc::RED);
				draw = true;
				obj.insert(obj.begin(), { mx, my, cross });
				connecting(mx, my, obj, cross);
			}

			if (draw)
				cycle++;

			draw = false;
		}

		return true;
	}
};


int main()
{
	Piskvorky game;
	if (game.Construct(350, 180, 4, 4))
	{
		game.EnableFullScreen(true);
		game.Start();
	}
		
	return 0;
}