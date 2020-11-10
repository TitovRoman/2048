#include "Game.h"
#include "Settings.h"
#include <Windows.h>
#include <random>

using namespace Game;

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
		nextStartCount = count;
	}
}

void Game::GameObj::setAddElementsCount(int count)
{
	if (count >= 1 && count <= 5)
	{
		nextElementCount = count;
	}
}

void Game::GameObj::initializetionNumbers()
{
	int gridSize = size_ * (cubeSize + 2 * cubePadding) + 2 * gridPadding;
	GridPanel->Size = System::Drawing::Size(gridSize, gridSize);
	this->Size = System::Drawing::Size(gridSize + formPadding * 2, gridSize + headSize + formPadding);

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
			tmp->Margin = System::Windows::Forms::Padding(cubePadding);
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

void Game::GameObj::initializationDistribution()
{
	distribution[2] = gcnew Tuple<double, double>(0.0, 0.9);
	distribution[4] = gcnew Tuple<double, double>(0.9, 1.0);
}

void Game::GameObj::newGame()
{
	startElementsCount = nextStartCount;
	addElementsCount = nextElementCount;
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
		for (int i = 1; i < size_; ++i)
		{
			if (numbers[i][j] != 0)
			{
				if (numbers[min_i][j] == 0)
				{
					numbers[min_i][j] = numbers[i][j];
					numbers[i][j] = 0;
					moveFlag = true;
				}
				else if (numbers[i][j] == numbers[min_i][j])
				{
					numbers[min_i][j] *= 2;
					score_ += numbers[min_i][j];
					numbers[i][j] = 0;

					moveFlag = true;
					++min_i;
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
		for (int i = size_ - 2; i >= 0; --i)
		{
			if (numbers[i][j] != 0)
			{
				if (numbers[max_i][j] == 0)
				{
					numbers[max_i][j] = numbers[i][j];
					numbers[i][j] = 0;
					moveFlag = true;
				}
				else if (numbers[i][j] == numbers[max_i][j])
				{
					numbers[max_i][j] *= 2;
					score_ += numbers[max_i][j];
					numbers[i][j] = 0;

					moveFlag = true;
					--max_i;
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
		for (int j = 1; j < size_; ++j)
		{
			if (numbers[i][j] != 0)
			{
				if (numbers[i][min_j] == 0)
				{
					numbers[i][min_j] = numbers[i][j];
					numbers[i][j] = 0;
					moveFlag = true;
				}
				else if (numbers[i][j] == numbers[i][min_j])
				{
					numbers[i][min_j] *= 2;
					score_ += numbers[i][min_j];
					numbers[i][j] = 0;

					moveFlag = true;
					++min_j;
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
		for (int j = size_ - 2; j >= 0; --j)
		{
			if (numbers[i][j] != 0)
			{
				if (numbers[i][max_j] == 0)
				{
					numbers[i][max_j] = numbers[i][j];
					numbers[i][j] = 0;
					moveFlag = true;
				}
				else if (numbers[i][j] == numbers[i][max_j])
				{
					numbers[i][max_j] *= 2;
					score_ += numbers[i][max_j];
					numbers[i][j] = 0;

					moveFlag = true;
					--max_j;
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

	for (int i = 1; i < size_ - 1; i += 1)
	{
		for (int j = 2 - i % 2; j < size_ - 1; j += 2)
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
	if (direction == System::Windows::Forms::Keys::D
		|| direction == System::Windows::Forms::Keys::Right)
	{
		moveFlag = rightDirection();
	}
	else if (direction == System::Windows::Forms::Keys::A
		|| direction == System::Windows::Forms::Keys::Left)
	{
		moveFlag = leftDirection();
	}
	else if (direction == System::Windows::Forms::Keys::W
		|| direction == System::Windows::Forms::Keys::Up)
	{
		moveFlag = upDirection();
	}
	else if (direction == System::Windows::Forms::Keys::S
		|| direction == System::Windows::Forms::Keys::Down)
	{
		moveFlag = downDirection();
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

int Game::GameObj::getNewValue()
{
	double value = rand->NextDouble();
	
	for each(auto x in distribution)
	{
		if (x.Value->Item1 <= value && value <= x.Value->Item2)
		{
			return x.Key;
		}
	}
	throw gcnew System::NotImplementedException();
}

void Game::GameObj::generateNewValues(int n)
{
	if (countEmptyBox() < n)
	{
		updateView();
		gameOver();
		return;
	}

	int x, y;
	while (n-- > 0)
	{
		do
		{
			x = rand->Next(0, size_);
			y = rand->Next(0, size_);
		} while (numbers[x][y] != 0);

		numbers[x][y] = getNewValue();
	}
}

void Game::GameObj::gameOver()
{
	MessageBox::Show(L"Очки: " + Convert::ToString(score_), L"Игра окончена!", MessageBoxButtons::OK);
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


