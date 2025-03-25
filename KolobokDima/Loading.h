#pragma once
#include "Cartoon1.h"

namespace BoyApp {
    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Drawing;
    using namespace System::Windows::Forms;

    public ref class Loading : public Form {
    public:
        Loading() {
            InitializeComponent();
        }

    protected:
        ~Loading() {
            if (components) {
                delete components;
            }
        }

    private:
        IContainer^ components;
        Button^ startButton;
        Timer^ countdownTimer;
        Label^ countdownLabel;
        int countdown;

    private:
        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->startButton = gcnew Button();
            this->countdownTimer = gcnew Timer(this->components);
            this->countdownLabel = gcnew Label();
            this->countdown = 3;

            this->ClientSize = System::Drawing::Size(500, 300);
            this->Text = L"Колобок. Мультфильм.";
            this->StartPosition = FormStartPosition::CenterScreen;

            this->startButton->Size = System::Drawing::Size(150, 50);
            this->startButton->Location = System::Drawing::Point(180, 130);
            this->startButton->Text = L"Начать";
            this->startButton->Font = gcnew System::Drawing::Font(L"Arial", 14);
            this->startButton->Click += gcnew EventHandler(this, &Loading::OnStartButtonClick);

            this->countdownLabel->Size = System::Drawing::Size(150, 50);
            this->countdownLabel->Location = System::Drawing::Point(180, 200);
            this->countdownLabel->Font = gcnew System::Drawing::Font(L"Arial", 24);
            this->countdownLabel->TextAlign = ContentAlignment::MiddleCenter;

            this->countdownTimer->Interval = 1000; // 1 секунда
            this->countdownTimer->Tick += gcnew EventHandler(this, &Loading::OnCountdownTick);

            this->Controls->Add(this->startButton);
            this->Controls->Add(this->countdownLabel);
        }

        void OnStartButtonClick(Object^ sender, EventArgs^ e) {
            this->startButton->Enabled = false;
            this->countdown = 3;
            this->countdownLabel->Text = countdown.ToString();
            this->countdownTimer->Start();
        }

        void OnCountdownTick(Object^ sender, EventArgs^ e) {
            if (--countdown > 0) {
                this->countdownLabel->Text = countdown.ToString();
            }
            else {
                this->countdownTimer->Stop();
                this->Hide();

                Cartoon1^ cartoonForm = gcnew Cartoon1();
                cartoonForm->ShowDialog();

                this->Show();
                this->startButton->Enabled = true;
                this->countdownLabel->Text = "";
            }
        }
    };
}
