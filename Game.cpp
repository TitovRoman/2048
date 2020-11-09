#include "Game.h"
#include "Settings.h"
#include <Windows.h>


using namespace Game;

#include <vector>

//std::vector<std::vector<int>> numbers;

[System::STAThread]
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew GameObj);
	return 0;
}

void Game::GameObj::setSize(int size)
{
	if (size >= 4 && size <= 10)
	{
		nextSize = size;
	}
}

void Game::GameObj::setStartElementsCount(int count)
{
	if (count >= 1 && count <= 5)
	{
		nextStartCnt = count;
	}
}

void Game::GameObj::setAddElementsCount(int count)
{
	if (count >= 1 && count <= 5)
	{
		nextElementCnt = count;
	}
}

void Game::GameObj::initializetionNumbers()
{
	int cubeSize = 100;
	int cubePadding = 5;
	int gridPadding = 7;
	int gridSize = size_ * (cubeSize + 2 * cubePadding) + 2 * gridPadding;
	GridPanel->Size = System::Drawing::Size(gridSize, gridSize);
	this->Size = System::Drawing::Size(gridSize + 40, gridSize + 160);

	System::Drawing::Font^ font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204));
	for (int i = 0; i < size_; ++i)
	{
		labels_numbers.Add(gcnew Generic::List<Label^>());
		numbers.Add(gcnew Generic::List<int>());
		for (int j = 0; j < size_; j++)
		{
			numbers[i]->Add(0);
			labels_numbers[i]->Add(gcnew Label());
			Label^ tmp = labels_numbers[i][j];
			tmp->BackColor = System::Drawing::Color::LightGray;
			tmp->Font = (font);
			tmp->Location = System::Drawing::Point(342, 232);
			tmp->Margin = System::Windows::Forms::Padding(cubePadding);
			//tmp->Name = L"c11";
			tmp->Size = System::Drawing::Size(cubeSize, cubeSize);
			tmp->TabIndex = 1;
			tmp->Text = L"";
			tmp->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

			GridPanel->Controls->Add(tmp);
		}
	}
}

void Game::GameObj::initializationColors()
{
	scoreToColor[0] = System::Drawing::Color::LightGray;
	scoreToColor[2] = System::Drawing::Color::Gainsboro;
	scoreToColor[4] = System::Drawing::Color::AntiqueWhite;
	scoreToColor[8] = System::Drawing::Color::PeachPuff;
	scoreToColor[16] = System::Drawing::Color::LightSalmon;
	scoreToColor[32] = System::Drawing::Color::Salmon;
	scoreToColor[64] = System::Drawing::Color::IndianRed;
	scoreToColor[128] = System::Drawing::Color::OrangeRed;
	scoreToColor[256] = System::Drawing::Color::Gold;
	scoreToColor[512] = System::Drawing::Color::Orange;
	scoreToColor[1024] = System::Drawing::Color::DarkOrange;
	scoreToColor[2048] = System::Drawing::Color::Sienna;
	scoreToColor[4096] = System::Drawing::Color::SaddleBrown;
}

void Game::GameObj::newGame()
{
	startElementsCount = nextStartCnt;
	addElementsCount = nextElementCnt;
	score_ = 0;

	if (size_ == nextSize)
	{
		for (int i = 0; i < size_; ++i)
		{
			for (int j = 0; j < size_; j++)
			{
				labels_numbers[i][j]->Text = L"";
				numbers[i][j] = 0;
			}
		}
	}
	else
	{
		GridPanel->Controls->Clear();
		labels_numbers.Clear();
		numbers.Clear();
		size_ = nextSize;
		initializetionNumbers();
	}

	updateScore();
	generateNewValues(startElementsCount);
	updateView();
}

bool Game::GameObj::upDirection()
{
	bool moveFlag = false;
	for (int j = 0; j < size_; ++j)
	{
		int min_i = 0;
		int start_i_iter = 0;
		while (start_i_iter < size_ && numbers[start_i_iter][j] == 0)
		{
			++start_i_iter;
		}
		if (start_i_iter > 0 && start_i_iter < size_)
		{
			numbers[min_i][j] = numbers[start_i_iter][j];
			numbers[start_i_iter][j] = 0;

			moveFlag = true;
		}

		for (int i = start_i_iter + 1; i < size_; ++i)
		{
			if (numbers[i][j] != 0)
			{
				if (numbers[i][j] == numbers[min_i][j])
				{
					numbers[min_i][j] *= 2;
					score_ += numbers[min_i][j];
					numbers[i][j] = 0;

					moveFlag = true;
				}
				else
				{
					if (i - min_i > 1)
					{
						numbers[min_i + 1][j] = numbers[i][j];
						numbers[i][j] = 0;

						moveFlag = true;
					}
					++min_i;
				}

			}
		}
	}

	return moveFlag;
}

bool Game::GameObj::downDirection()
{
	bool moveFlag = false;
	for (int j = 0; j < size_; ++j)
	{
		int max_i = size_ - 1;
		int start_i_iter = size_ - 1;
		while (start_i_iter >= 0 && numbers[start_i_iter][j] == 0)
		{
			--start_i_iter;
		}
		if (start_i_iter < size_ - 1 && start_i_iter >= 0)
		{
			numbers[max_i][j] = numbers[start_i_iter][j];
			numbers[start_i_iter][j] = 0;

			moveFlag = true;
		}

		for (int i = start_i_iter - 1; i >= 0; --i)
		{
			if (numbers[i][j] != 0)
			{
				if (numbers[i][j] == numbers[max_i][j])
				{
					numbers[max_i][j] *= 2;
					score_ += numbers[max_i][j];
					numbers[i][j] = 0;

					moveFlag = true;
				}
				else
				{
					if (max_i - i > 1)
					{
						numbers[max_i - 1][j] = numbers[i][j];
						numbers[i][j] = 0;

						moveFlag = true;
					}
					--max_i;
				}

			}
		}
	}
	return moveFlag;
}

bool Game::GameObj::leftDirection()
{
	bool moveFlag = false;
	for (int i = 0; i < size_; ++i)
	{
		int min_j = 0;
		int start_j_iter = 0;
		while (start_j_iter < size_ && numbers[i][start_j_iter] == 0)
		{
			++start_j_iter;
		}
		if (start_j_iter > 0 && start_j_iter < size_)
		{
			numbers[i][min_j] = numbers[i][start_j_iter];
			numbers[i][start_j_iter] = 0;

			moveFlag = true;
		}

		for (int j = start_j_iter + 1; j < size_; ++j)
		{
			if (numbers[i][j] != 0)
			{
				if (numbers[i][j] == numbers[i][min_j])
				{
					numbers[i][min_j] *= 2;
					score_ += numbers[i][min_j];
					numbers[i][j] = 0;

					moveFlag = true;
				}
				else
				{
					if (j - min_j > 1)
					{
						numbers[i][min_j + 1] = numbers[i][j];
						numbers[i][j] = 0;

						moveFlag = true;
					}
					++min_j;
				}

			}
		}
	}
	return moveFlag;
}

bool Game::GameObj::rightDirection()
{
	bool moveFlag = false;
	for (int i = 0; i < size_; ++i)
	{
		int max_j = size_ - 1;
		int start_j_iter = size_ - 1;
		while (start_j_iter >= 0 && numbers[i][start_j_iter] == 0)
		{
			--start_j_iter;
		}
		if (start_j_iter < size_ - 1 && start_j_iter >= 0)
		{
			numbers[i][max_j] = numbers[i][start_j_iter];
			numbers[i][start_j_iter] = 0;
			moveFlag = true;

		}

		for (int j = start_j_iter - 1; j >= 0; --j)
		{
			if (numbers[i][j] != 0)
			{
				if (numbers[i][j] == numbers[i][max_j])
				{
					numbers[i][max_j] *= 2;
					score_ += numbers[i][max_j];
					numbers[i][j] = 0;

					moveFlag = true;
				}
				else
				{
					if (max_j - j > 1)
					{
						numbers[i][max_j - 1] = numbers[i][j];
						numbers[i][j] = 0;

						moveFlag = true;
					}
					--max_j;
				}

			}
		}
	}
	return moveFlag;
}

bool Game::GameObj::checkMove()
{
	if (countEmptyBox() > 0)
	{
		return true;
	}

	for (int i = 1; i < size_ - 1; i += 2)
	{
		for (int j = 1; j < size_ - 1; j += 2)
		{
			int currentValue = numbers[i][j];
			if (currentValue == numbers[i - 1][j]
				|| currentValue == numbers[i + 1][j]
				|| currentValue == numbers[i][j - 1]
				|| currentValue == numbers[i][j + 1])
			{
				return true;
			}
		}
	}

	for (int i = 1; i < size_ - 1; ++i)
	{
		if (numbers[i][0] == numbers[i][1]
			|| numbers[i][0] == numbers[i - 1][0]
			|| numbers[i][0] == numbers[i + 1][0])
		{
			return true;
		}

		if (numbers[i][size_ - 1] == numbers[i][size_ - 2]
			|| numbers[i][size_ - 1] == numbers[i - 1][size_ - 1]
			|| numbers[i][size_ - 1] == numbers[i + 1][size_ - 1])
		{
			return true;
		}
	}
	for (int j = 1; j < size_ - 1; ++j)
	{
		if (numbers[0][j] == numbers[1][j]
			|| numbers[0][j] == numbers[0][j - 1]
			|| numbers[0][j] == numbers[0][j + 1])
		{
			return true;
		}

		if (numbers[size_ - 1][j] == numbers[size_ - 2][j]
			|| numbers[size_ - 1][j] == numbers[size_ - 1][j - 1]
			|| numbers[size_ - 1][j] == numbers[size_ - 1][j + 1])
		{
			return true;
		}
	}

	return false;
}

int Game::GameObj::countEmptyBox()
{
	int cnt = 0;
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; j++)
		{
			if (numbers[i][j] == 0)
			{
				++cnt;
			}
		}
	}

	return cnt;
}

void Game::GameObj::game(System::Windows::Forms::Keys direction)
{
	bool moveFlag = false;
	switch (direction)
	{
	case System::Windows::Forms::Keys::D:
		moveFlag = rightDirection();
		break;
	case System::Windows::Forms::Keys::A:
		moveFlag = leftDirection();
		break;
	case System::Windows::Forms::Keys::W:
		moveFlag = upDirection();
		break;
	case System::Windows::Forms::Keys::S:
		moveFlag = downDirection();
		break;
	case System::Windows::Forms::Keys::Right:
		moveFlag = rightDirection();
		break;
	case System::Windows::Forms::Keys::Left:
		moveFlag = leftDirection();
		break;
	case System::Windows::Forms::Keys::Up:
		moveFlag = upDirection();
		break;
	case System::Windows::Forms::Keys::Down:
		moveFlag = downDirection();
		break;
	default:
		break;
	}

	if (moveFlag)
	{
		updateScore();
		generateNewValues(addElementsCount);
		updateView();
		if (!checkMove())
		{
			gameOver();
			return;
		}
	}
}

void Game::GameObj::updateView()
{
	for (int i = 0; i < size_; ++i)
	{
		for (int j = 0; j < size_; j++)
		{
			if (scoreToColor.ContainsKey(numbers[i][j]))
			{
				labels_numbers[i][j]->BackColor = scoreToColor[numbers[i][j]];
			}
			else
			{
				labels_numbers[i][j]->BackColor = defaultColor;
			}

			if (numbers[i][j] != 0)
			{
				labels_numbers[i][j]->Text = Convert::ToString(numbers[i][j]);
			}
			else
			{
				labels_numbers[i][j]->Text = L"";
			}
		}
	}


}

void Game::GameObj::updateScore()
{
	ScoreLabel->Text = Convert::ToString(score_);
}

void Game::GameObj::generateNewValues(int n)
{

	if (countEmptyBox() < n)
	{
		gameOver();
		return;
	}
	Random^ rand = gcnew Random();
	int x, y;
	while (n-- > 0)
	{
		do
		{
			x = rand->Next(0, size_);
			y = rand->Next(0, size_);
		} while (numbers[x][y] != 0);
		numbers[x][y] = 2;
	}
}

void Game::GameObj::gameOver()
{
	MessageBox::Show(L"����: " + Convert::ToString(score_), L"���� ��������!", MessageBoxButtons::OK);
	newGame();
}


System::Void Game::GameObj::Set_Click(System::Object^ sender, System::EventArgs^ e)
{
	Settings^ settings = gcnew Settings(this);
	settings->Show();
}

System::Void Game::GameObj::Game1_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e)
{
	e->IsInputKey = true;

	return System::Void();
}

System::Void Game::GameObj::Game1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e)
{

	game(e->KeyCode);

	return System::Void();
}

