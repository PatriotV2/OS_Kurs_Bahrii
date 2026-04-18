#pragma once


namespace OSmetod {

	using namespace System;
	using namespace System::Drawing;
	using namespace System::Windows::Forms;

	public ref class frmAbout : public Form
	{
	public:
		frmAbout(void)
		{
			InitializeComponent();
			lblVersion->Text = L"Версія: 1.00.1";
		}

	protected:
		~frmAbout()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		Button^ btnClose;
		PictureBox^ pbIcon;
		Label^ lblName;
		Label^ lblVersion;
		Label^ lblAuthor;
		Label^ lblRights;
		GroupBox^ gbInfo;
		Label^ lblInfo;
		System::ComponentModel::Container^ components;

		void InitializeComponent(void)
		{
			this->btnClose = (gcnew Button());
			this->pbIcon = (gcnew PictureBox());
			this->lblName = (gcnew Label());
			this->lblVersion = (gcnew Label());
			this->lblAuthor = (gcnew Label());
			this->lblRights = (gcnew Label());
			this->gbInfo = (gcnew GroupBox());
			this->lblInfo = (gcnew Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbIcon))->BeginInit();
			this->gbInfo->SuspendLayout();
			this->SuspendLayout();
			this->btnClose->DialogResult = System::Windows::Forms::DialogResult::OK;
			this->btnClose->Location = Point(360, 286);
			this->btnClose->Size = Drawing::Size(96, 30);
			this->btnClose->Text = L"Close";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew EventHandler(this, &frmAbout::btnClose_Click);
			this->pbIcon->Image = SystemIcons::Information->ToBitmap();
			this->pbIcon->Location = Point(22, 22);
			this->pbIcon->Size = Drawing::Size(96, 96);
			this->pbIcon->SizeMode = PictureBoxSizeMode::Zoom;
			this->pbIcon->TabStop = false;
			this->lblName->AutoSize = true;
			this->lblName->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold));
			this->lblName->Location = Point(140, 22);
			this->lblName->Text = L"Semantor";
			this->lblVersion->AutoSize = true;
			this->lblVersion->Location = Point(142, 60);
			this->lblVersion->Text = L"Версія: 1.0";
			this->lblAuthor->AutoSize = true;
			this->lblAuthor->Location = Point(142, 86);
			this->lblAuthor->Text = L"Автор: Багрій Єгор Олексійович";
			this->lblRights->AutoSize = true;
			this->lblRights->Location = Point(142, 111);
			this->lblRights->Text = L"Copyright © 2026 Semantor";
			this->gbInfo->Controls->Add(this->lblInfo);
			this->gbInfo->Location = Point(22, 138);
			this->gbInfo->Size = Drawing::Size(434, 130);
			this->gbInfo->Text = L"Призначення";
			this->lblInfo->Dock = DockStyle::Fill;
			this->lblInfo->Padding = System::Windows::Forms::Padding(10, 8, 10, 8);
			this->lblInfo->Text = L"Semantor — локальний Windows-застосунок на C++, який дозволяє ввести або заванта"
				L"жити текст, виконати аналіз тональності, переглянути результат і зберегти його "
				L"у файл.";
			this->ClientSize = Drawing::Size(480, 336);
			this->Controls->Add(this->gbInfo);
			this->Controls->Add(this->lblRights);
			this->Controls->Add(this->lblAuthor);
			this->Controls->Add(this->lblVersion);
			this->Controls->Add(this->lblName);
			this->Controls->Add(this->pbIcon);
			this->Controls->Add(this->btnClose);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->StartPosition = FormStartPosition::CenterParent;
			this->Text = L"Про застосунок";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbIcon))->EndInit();
			this->gbInfo->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		System::Void btnClose_Click(System::Object^ sender, System::EventArgs^ e) {
			this->Close();
		}
	};
}
