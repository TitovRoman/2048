#pragma once
#include <random>

namespace Game {
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Game
	/// </summary>
	public ref class GameObj : public System::Windows::Forms::Form
	{
	public:
		GameObj(void)
		{
			InitializeComponent();
			initializationColors();
			initializationDistribution();
			newGame();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameObj()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ ScoreLabel;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::FlowLayoutPanel^ GridPanel;
	private: System::Windows::Forms::Button^ button2;
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->ScoreLabel = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->GridPanel = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// label17
			// 
			this->label17->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label17->BackColor = System::Drawing::Color::LightGray;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->Location = System::Drawing::Point(298, 12);
			this->label17->Margin = System::Windows::Forms::Padding(5);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(168, 71);
			this->label17->TabIndex = 2;
			this->label17->Text = L"Score";
			this->label17->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// ScoreLabel
			// 
			this->ScoreLabel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->ScoreLabel->BackColor = System::Drawing::Color::LightGray;
			this->ScoreLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ScoreLabel->Location = System::Drawing::Point(298, 43);
			this->ScoreLabel->Name = L"ScoreLabel";
			this->ScoreLabel->Size = System::Drawing::Size(168, 40);
			this->ScoreLabel->TabIndex = 3;
			this->ScoreLabel->Text = L"0";
			this->ScoreLabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::LightGray;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(12, 12);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(168, 71);
			this->button1->TabIndex = 4;
			this->button1->Text = L"New Game";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &GameObj::buttonNewGame_Click);
			this->button1->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &GameObj::button1_PreviewKeyDown);
			// 
			// GridPanel
			// 
			this->GridPanel->BackColor = System::Drawing::Color::Silver;
			this->GridPanel->Location = System::Drawing::Point(12, 108);
			this->GridPanel->Name = L"GridPanel";
			this->GridPanel->Padding = System::Windows::Forms::Padding(7);
			this->GridPanel->Size = System::Drawing::Size(454, 454);
			this->GridPanel->TabIndex = 0;
			this->GridPanel->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &GameObj::GridPanel_PreviewKeyDown);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::LightGray;
			this->button2->CausesValidation = false;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(186, 12);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(104, 71);
			this->button2->TabIndex = 4;
			this->button2->Text = L"Set";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &GameObj::Set_Click);
			this->button2->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &GameObj::button2_PreviewKeyDown);
			// 
			// GameObj
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->ClientSize = System::Drawing::Size(478, 575);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->ScoreLabel);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->GridPanel);
			this->KeyPreview = true;
			this->MaximizeBox = false;
			this->Name = L"GameObj";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"2048";
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &GameObj::Game1_KeyDown);
			this->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &GameObj::Game1_PreviewKeyDown);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		int size_ = -1;
		int score_ = 0;

		int startElementsCount = 2;
		int addElementsCount = 1;

		int nextSize = 4;
		int nextStartCount = 2;
		int nextElementCount = 1;

		int cubeSize = 100;
		int cubePadding = 5;
		int gridPadding = 7;
		int formPadding = 20;
		int headSize = 140;

		Random^ rand = gcnew Random();
		Generic::Dictionary<int, Tuple<double, double>^> distribution;

	public:
		void setSize(int);
		void setStartElementsCount(int);
		void setAddElementsCount(int);
		void newGame();

	private:
		Generic::List<Generic::List<int>^> numbers;
		Generic::List<Generic::List<Label^>^> labels_numbers;
		Generic::Dictionary<int, System::Drawing::Color> scoreToColor;
		System::Drawing::Color defaultColor = System::Drawing::Color::RosyBrown;

		void initializetionNumbers();
		void initializationColors();
		void initializationDistribution();
		int getNewValue();

		void game(System::Windows::Forms::Keys);
		void updateView();
		void updateScore();
		void generateNewValues(int);
		void gameOver();

		bool upDirection();
		bool downDirection();
		bool leftDirection();
		bool rightDirection();

		bool checkMove();
		int countEmptyBox();
		

	private: 
		System::Void buttonNewGame_Click(System::Object^ sender, System::EventArgs^ e) 
		{
			newGame();
		}
		System::Void Set_Click(System::Object^ sender, System::EventArgs^ e);
		System::Void Game1_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e);

		System::Void Game1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e);

		System::Void GridPanel_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e) 
		{
			e->IsInputKey = true;
		}
		System::Void button1_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e) 
		{
			e->IsInputKey = true;
		}
		System::Void button2_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e) 
		{
			e->IsInputKey = true;
		}
};
}
