#pragma once

#include "SemantorAbout.h"
#include "SentimentService.h"
#using <System.Windows.Forms.dll>
using DialogResultEnum = System::Windows::Forms::DialogResult;

namespace OSmetod {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace System::Text;
	using namespace System::Windows::Forms;

	public ref class frmMain : public Form
	{
	public:
		frmMain(void)
		{
			InitializeComponent();
			sentimentService = gcnew SentimentService();
			sentimentService->OnProgress = gcnew OnProgressEvent(this, &frmMain::DoProgress);
			frmabout = gcnew frmAbout();
			cmbProfile->SelectedIndex = 0;
			UpdateStatus(L"Semantor готовий до роботи.");
		}

	protected:
		~frmMain()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		MenuStrip^ mnsMain;
		ToolStripMenuItem^ tsmiFile;
		ToolStripMenuItem^ tsmiNew;
		ToolStripMenuItem^ tsmiLoad;
		ToolStripMenuItem^ tsmiSave;
		ToolStripSeparator^ toolStripMenuItem1;
		ToolStripMenuItem^ tsmiClose;
		ToolStripMenuItem^ tsmiAnalyze;
		ToolStripMenuItem^ tsmiStart;
		ToolStripMenuItem^ tsmiStop;
		ToolStripMenuItem^ tsmiParams;
		ToolStripMenuItem^ tmsiHelp;
		ToolStripMenuItem^ tmsiAbout;
		ToolStrip^ tsMain;
		ToolStripButton^ tsbNew;
		ToolStripButton^ tsbOpen;
		ToolStripButton^ tsbSave;
		ToolStripSeparator^ toolStripSeparator1;
		ToolStripButton^ tsbExecute;
		ToolStripButton^ tsbCancel;
		ToolStripSeparator^ toolStripSeparator2;
		ToolStripButton^ tsbAbout;
		ToolStripButton^ tsbExit;
		StatusStrip^ stMain;
		ToolStripStatusLabel^ tslInfo;
		ToolStripProgressBar^ tspMain;
		SplitContainer^ scMain;
		Panel^ pnlview;
		Panel^ panel1;
		PictureBox^ pbMain;
		Panel^ pnlInfo;
		Label^ lblInfo;
		Label^ lblProfile;
		ComboBox^ cmbProfile;
		TextBox^ txbInfo;
		SplitContainer^ scView;
		GroupBox^ gbInput;
		GroupBox^ gbResult;
		TextBox^ txbInput;
		TextBox^ txbResult;
		System::ComponentModel::IContainer^ components;
		frmAbout^ frmabout;
		SentimentService^ sentimentService;

		void InitializeComponent(void)
		{
			this->mnsMain = (gcnew MenuStrip());
			this->tsmiFile = (gcnew ToolStripMenuItem());
			this->tsmiNew = (gcnew ToolStripMenuItem());
			this->tsmiLoad = (gcnew ToolStripMenuItem());
			this->tsmiSave = (gcnew ToolStripMenuItem());
			this->toolStripMenuItem1 = (gcnew ToolStripSeparator());
			this->tsmiClose = (gcnew ToolStripMenuItem());
			this->tsmiAnalyze = (gcnew ToolStripMenuItem());
			this->tsmiStart = (gcnew ToolStripMenuItem());
			this->tsmiStop = (gcnew ToolStripMenuItem());
			this->tsmiParams = (gcnew ToolStripMenuItem());
			this->tmsiHelp = (gcnew ToolStripMenuItem());
			this->tmsiAbout = (gcnew ToolStripMenuItem());
			this->tsMain = (gcnew ToolStrip());
			this->tsbNew = (gcnew ToolStripButton());
			this->tsbOpen = (gcnew ToolStripButton());
			this->tsbSave = (gcnew ToolStripButton());
			this->toolStripSeparator1 = (gcnew ToolStripSeparator());
			this->tsbExecute = (gcnew ToolStripButton());
			this->tsbCancel = (gcnew ToolStripButton());
			this->toolStripSeparator2 = (gcnew ToolStripSeparator());
			this->tsbAbout = (gcnew ToolStripButton());
			this->tsbExit = (gcnew ToolStripButton());
			this->stMain = (gcnew StatusStrip());
			this->tslInfo = (gcnew ToolStripStatusLabel());
			this->tspMain = (gcnew ToolStripProgressBar());
			this->scMain = (gcnew SplitContainer());
			this->pnlview = (gcnew Panel());
			this->panel1 = (gcnew Panel());
			this->pbMain = (gcnew PictureBox());
			this->pnlInfo = (gcnew Panel());
			this->txbInfo = (gcnew TextBox());
			this->cmbProfile = (gcnew ComboBox());
			this->lblProfile = (gcnew Label());
			this->lblInfo = (gcnew Label());
			this->scView = (gcnew SplitContainer());
			this->gbInput = (gcnew GroupBox());
			this->txbInput = (gcnew TextBox());
			this->gbResult = (gcnew GroupBox());
			this->txbResult = (gcnew TextBox());
			this->mnsMain->SuspendLayout();
			this->tsMain->SuspendLayout();
			this->stMain->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scMain))->BeginInit();
			this->scMain->Panel1->SuspendLayout();
			this->scMain->Panel2->SuspendLayout();
			this->scMain->SuspendLayout();
			this->pnlview->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbMain))->BeginInit();
			this->pnlInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scView))->BeginInit();
			this->scView->Panel1->SuspendLayout();
			this->scView->Panel2->SuspendLayout();
			this->scView->SuspendLayout();
			this->gbInput->SuspendLayout();
			this->gbResult->SuspendLayout();
			this->SuspendLayout();
			this->mnsMain->Items->AddRange(gcnew cli::array< ToolStripItem^ >(3) { this->tsmiFile, this->tsmiAnalyze, this->tmsiHelp });
			this->mnsMain->Location = Point(0, 0);
			this->mnsMain->Size = Drawing::Size(1100, 24);
			this->tsmiFile->DropDownItems->AddRange(gcnew cli::array< ToolStripItem^ >(5) { this->tsmiNew, this->tsmiLoad, this->tsmiSave, this->toolStripMenuItem1, this->tsmiClose });
			this->tsmiFile->Text = L"Файл";
			this->tsmiNew->Text = L"Новий сеанс";
			this->tsmiNew->Click += gcnew EventHandler(this, &frmMain::tsbNew_Click);
			this->tsmiLoad->Text = L"Завантажити текст";
			this->tsmiLoad->Click += gcnew EventHandler(this, &frmMain::tsbOpen_Click);
			this->tsmiSave->Text = L"Зберегти результат";
			this->tsmiSave->Click += gcnew EventHandler(this, &frmMain::tsbSave_Click);
			this->tsmiClose->Text = L"Вихід";
			this->tsmiClose->Click += gcnew EventHandler(this, &frmMain::tsbExit_Click);
			this->tsmiAnalyze->DropDownItems->AddRange(gcnew cli::array< ToolStripItem^ >(3) { this->tsmiStart, this->tsmiStop, this->tsmiParams });
			this->tsmiAnalyze->Text = L"Аналіз";
			this->tsmiStart->Text = L"Запустити аналіз";
			this->tsmiStart->Click += gcnew EventHandler(this, &frmMain::tsbExecute_Click);
			this->tsmiStop->Text = L"Очистити";
			this->tsmiStop->Click += gcnew EventHandler(this, &frmMain::tsbCancel_Click);
			this->tsmiParams->Text = L"Параметри";
			this->tmsiHelp->DropDownItems->AddRange(gcnew cli::array< ToolStripItem^ >(1) { this->tmsiAbout });
			this->tmsiHelp->Text = L"Довідка";
			this->tmsiAbout->Text = L"Про застосунок";
			this->tmsiAbout->Click += gcnew EventHandler(this, &frmMain::tmsiAbout_Click);
			this->tsMain->GripStyle = ToolStripGripStyle::Hidden;
			this->tsMain->Items->AddRange(gcnew cli::array< ToolStripItem^ >(9) { this->tsbNew, this->tsbOpen, this->tsbSave, this->toolStripSeparator1, this->tsbExecute, this->tsbCancel, this->toolStripSeparator2, this->tsbAbout, this->tsbExit });
			this->tsMain->Location = Point(0, 24);
			this->tsMain->Size = Drawing::Size(1100, 39);
			this->tsbNew->DisplayStyle = ToolStripItemDisplayStyle::Text;
			this->tsbNew->Text = L"New";
			this->tsbNew->Click += gcnew EventHandler(this, &frmMain::tsbNew_Click);
			this->tsbOpen->DisplayStyle = ToolStripItemDisplayStyle::Text;
			this->tsbOpen->Text = L"Open";
			this->tsbOpen->Click += gcnew EventHandler(this, &frmMain::tsbOpen_Click);
			this->tsbSave->DisplayStyle = ToolStripItemDisplayStyle::Text;
			this->tsbSave->Text = L"Save";
			this->tsbSave->Click += gcnew EventHandler(this, &frmMain::tsbSave_Click);
			this->tsbExecute->DisplayStyle = ToolStripItemDisplayStyle::Text;
			this->tsbExecute->Text = L"Analyze";
			this->tsbExecute->Click += gcnew EventHandler(this, &frmMain::tsbExecute_Click);
			this->tsbCancel->DisplayStyle = ToolStripItemDisplayStyle::Text;
			this->tsbCancel->Text = L"Clear";
			this->tsbCancel->Click += gcnew EventHandler(this, &frmMain::tsbCancel_Click);
			this->tsbAbout->DisplayStyle = ToolStripItemDisplayStyle::Text;
			this->tsbAbout->Text = L"About";
			this->tsbAbout->Click += gcnew EventHandler(this, &frmMain::tmsiAbout_Click);
			this->tsbExit->DisplayStyle = ToolStripItemDisplayStyle::Text;
			this->tsbExit->Text = L"Exit";
			this->tsbExit->Click += gcnew EventHandler(this, &frmMain::tsbExit_Click);
			this->stMain->Items->AddRange(gcnew cli::array< ToolStripItem^ >(2) { this->tslInfo, this->tspMain });
			this->stMain->Location = Point(0, 639);
			this->stMain->Size = Drawing::Size(1100, 22);
			this->tslInfo->AutoSize = false;
			this->tslInfo->Size = Drawing::Size(760, 17);
			this->tslInfo->Text = L"Semantor готовий до роботи.";
			this->tspMain->Maximum = 100;
			this->tspMain->Size = Drawing::Size(180, 16);
			this->scMain->Dock = DockStyle::Fill;
			this->scMain->Location = Point(0, 63);
			this->scMain->Size = Drawing::Size(1100, 576);
			this->scMain->SplitterDistance = 290;
			this->scMain->Panel1->Controls->Add(this->pnlview);
			this->scMain->Panel2->Controls->Add(this->scView);
			this->pnlview->Controls->Add(this->panel1);
			this->pnlview->Controls->Add(this->pnlInfo);
			this->pnlview->Dock = DockStyle::Fill;
			this->panel1->Controls->Add(this->pbMain);
			this->panel1->Dock = DockStyle::Fill;
			this->pbMain->Dock = DockStyle::Fill;
			this->pbMain->Image = SystemIcons::Application->ToBitmap();
			this->pbMain->SizeMode = PictureBoxSizeMode::CenterImage;
			this->pnlInfo->Controls->Add(this->txbInfo);
			this->pnlInfo->Controls->Add(this->cmbProfile);
			this->pnlInfo->Controls->Add(this->lblProfile);
			this->pnlInfo->Controls->Add(this->lblInfo);
			this->pnlInfo->Dock = DockStyle::Bottom;
			this->pnlInfo->Height = 190;
			this->lblInfo->AutoSize = true;
			this->lblInfo->Location = Point(14, 14);
			this->lblInfo->Text = L"Параметричний блок\r\nOS_metod-структура збережена:\r\n- зліва допоміжна панель;\r\n- справа робоча область;";
			this->lblProfile->AutoSize = true;
			this->lblProfile->Location = Point(14, 78);
			this->lblProfile->Text = L"Профіль аналізу:";
			this->cmbProfile->DropDownStyle = ComboBoxStyle::DropDownList;
			this->cmbProfile->Items->AddRange(gcnew cli::array< Object^ >(3) { L"Стандартний", L"Чутливий", L"Строгий" });
			this->cmbProfile->Location = Point(17, 102);
			this->cmbProfile->Size = Drawing::Size(240, 23);
			this->cmbProfile->SelectedIndexChanged += gcnew EventHandler(this, &frmMain::cmbProfile_SelectedIndexChanged);
			this->txbInfo->Location = Point(17, 134);
			this->txbInfo->Multiline = true;
			this->txbInfo->ReadOnly = true;
			this->txbInfo->ScrollBars = ScrollBars::Vertical;
			this->txbInfo->Size = Drawing::Size(240, 42);
			this->txbInfo->Text = L"Тут відображається стислий підсумок аналізу.";
			this->scView->Dock = DockStyle::Fill;
			this->scView->Orientation = Orientation::Horizontal;
			this->scView->SplitterDistance = 270;
			this->scView->Panel1->Controls->Add(this->gbInput);
			this->scView->Panel2->Controls->Add(this->gbResult);
			this->gbInput->Controls->Add(this->txbInput);
			this->gbInput->Dock = DockStyle::Fill;
			this->gbInput->Text = L"Вхідний текст";
			this->txbInput->Dock = DockStyle::Fill;
			this->txbInput->Multiline = true;
			this->txbInput->ScrollBars = ScrollBars::Vertical;
			this->gbResult->Controls->Add(this->txbResult);
			this->gbResult->Dock = DockStyle::Fill;
			this->gbResult->Text = L"Результат аналізу";
			this->txbResult->Dock = DockStyle::Fill;
			this->txbResult->Multiline = true;
			this->txbResult->ReadOnly = true;
			this->txbResult->ScrollBars = ScrollBars::Vertical;
			this->AutoScaleDimensions = Drawing::SizeF(7, 15);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = Drawing::Size(1100, 661);
			this->Controls->Add(this->scMain);
			this->Controls->Add(this->stMain);
			this->Controls->Add(this->tsMain);
			this->Controls->Add(this->mnsMain);
			this->MainMenuStrip = this->mnsMain;
			this->StartPosition = FormStartPosition::CenterScreen;
			this->Text = L"Semantor";
			this->Load += gcnew EventHandler(this, &frmMain::frmMain_Load);
			this->mnsMain->ResumeLayout(false);
			this->mnsMain->PerformLayout();
			this->tsMain->ResumeLayout(false);
			this->tsMain->PerformLayout();
			this->stMain->ResumeLayout(false);
			this->stMain->PerformLayout();
			this->scMain->Panel1->ResumeLayout(false);
			this->scMain->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scMain))->EndInit();
			this->scMain->ResumeLayout(false);
			this->pnlview->ResumeLayout(false);
			this->panel1->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbMain))->EndInit();
			this->pnlInfo->ResumeLayout(false);
			this->pnlInfo->PerformLayout();
			this->scView->Panel1->ResumeLayout(false);
			this->scView->Panel2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->scView))->EndInit();
			this->scView->ResumeLayout(false);
			this->gbInput->ResumeLayout(false);
			this->gbInput->PerformLayout();
			this->gbResult->ResumeLayout(false);
			this->gbResult->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		System::Void tmsiAbout_Click(System::Object^ sender, System::EventArgs^ e) {
			frmabout->ShowDialog(this);
		}

		void DoProgress(float value) {
			int progress = Math::Max(0, Math::Min(100, (int)value));
			if (tspMain->Value != progress) {
				tspMain->Value = progress;
			}
			Application::DoEvents();
		}

		void UpdateStatus(String^ message) {
			tslInfo->Text = message;
		}

		void UpdateSummary(ManagedAnalysisResult^ result) {
			txbInfo->Text =
				L"Профіль: " + result->ProfileName + Environment::NewLine +
				L"Тональність: " + result->Label + Environment::NewLine +
				L"Позитивний бал: " + result->PositiveScore.ToString() + Environment::NewLine +
				L"Негативний бал: " + result->NegativeScore.ToString() + Environment::NewLine +
				L"Індекс: " + result->SentimentIndex.ToString(L"F2");
		}

		void RunAnalysis() {
			if (String::IsNullOrWhiteSpace(txbInput->Text)) {
				MessageBox::Show(L"Введіть текст або завантажте файл для аналізу.", L"Semantor", MessageBoxButtons::OK, MessageBoxIcon::Information);
				UpdateStatus(L"Аналіз скасовано: відсутній вхідний текст.");
				tspMain->Value = 0;
				return;
			}

			UpdateStatus(L"Виконується аналіз тональності...");
			tspMain->Value = 5;
			ManagedAnalysisResult^ result = sentimentService->Analyze(txbInput->Text, safe_cast<String^>(cmbProfile->SelectedItem));
			txbResult->Text = result->DisplayText;
			UpdateSummary(result);
			tspMain->Value = 100;
			UpdateStatus(L"Аналіз завершено. Результат: " + result->Label);
		}

		void ClearAll() {
			txbInput->Clear();
			txbResult->Clear();
			txbInfo->Text = L"Тут відображається стислий підсумок аналізу.";
			tspMain->Value = 0;
			UpdateStatus(L"Поля введення та результату очищено.");
		}

		void NewSession() {
			ClearAll();
			cmbProfile->SelectedIndex = 0;
			UpdateStatus(L"Розпочато новий сеанс.");
		}

		void LoadTextFromFile() {
			OpenFileDialog^ dialog = gcnew OpenFileDialog();
			dialog->Filter = L"Text files (*.txt)|*.txt|All files (*.*)|*.*";
			dialog->Title = L"Завантажити текст";

			if (dialog->ShowDialog(this) == DialogResult::OK) {
				txbInput->Text = File::ReadAllText(dialog->FileName, Encoding::UTF8);
				tspMain->Value = 15;
				UpdateStatus(L"Текст успішно завантажено з файлу.");
			}
		}

		void SaveResultToFile() {
			if (String::IsNullOrWhiteSpace(txbResult->Text)) {
				MessageBox::Show(L"Спочатку виконайте аналіз тексту.", L"Semantor", MessageBoxButtons::OK, MessageBoxIcon::Warning);
				UpdateStatus(L"Збереження неможливе: результат відсутній.");
				return;
			}

			SaveFileDialog^ dialog = gcnew SaveFileDialog();
			dialog->Filter = L"Text files (*.txt)|*.txt|All files (*.*)|*.*";
			dialog->DefaultExt = L"txt";
			dialog->Title = L"Зберегти результат";

			if (dialog->ShowDialog(this) == DialogResult::OK) {
				File::WriteAllText(dialog->FileName, txbResult->Text, Encoding::UTF8);
				tspMain->Value = 100;
				UpdateStatus(L"Результат успішно збережено.");
			}
		}

		System::Void tsbNew_Click(System::Object^ sender, System::EventArgs^ e) { NewSession(); }
		System::Void tsbOpen_Click(System::Object^ sender, System::EventArgs^ e) { LoadTextFromFile(); }
		System::Void tsbSave_Click(System::Object^ sender, System::EventArgs^ e) { SaveResultToFile(); }
		System::Void tsbExecute_Click(System::Object^ sender, System::EventArgs^ e) { RunAnalysis(); }
		System::Void tsbCancel_Click(System::Object^ sender, System::EventArgs^ e) { ClearAll(); }
		System::Void tsbExit_Click(System::Object^ sender, System::EventArgs^ e) { this->Close(); }

		System::Void cmbProfile_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
			if (cmbProfile->SelectedItem != nullptr) {
				UpdateStatus(L"Обрано профіль аналізу: " + safe_cast<String^>(cmbProfile->SelectedItem));
			}
		}

		System::Void frmMain_Load(System::Object^ sender, System::EventArgs^ e) {
			tspMain->Value = 0;
			txbInput->Focus();
		}
	};
}
