#pragma once
#include <iostream>
namespace BoyApp {
    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::Media;

    public ref class Cartoon1 : public Form {
    public:
        Cartoon1() {
            InitializeComponent();
        }

    protected:
        ~Cartoon1() {
            if (components) delete components;
        }

    private:
        System::ComponentModel::Container^ components;
        Timer^ cartoonTimer;
        Timer^ endScreenTimer;
        Label^ endScreenLabel;

        PictureBox^ kolobok;
        PictureBox^ wolf;
        PictureBox^ wolf2;
        PictureBox^ fox;
        PictureBox^ fox2;
        PictureBox^ background;

        SoundPlayer^ sp = gcnew System::Media::SoundPlayer();

        int currentFrame = 0;
        int endScreenDuration = 4; 
        int kolobokX = 150, kolobokY = 450;
        int wolfX = 500, wolfY = 350;
        int foxX = 600, foxY = 250;
        int wolf2X = 500, wolf2Y = 350;
        int fox2X = 600, fox2Y = 250;
        int stage = 0;
        int VAR = 1;


        cli::array<String^>^ backgrounds;

    private:
        void InitializeComponent() {
            this->components = gcnew System::ComponentModel::Container();
            this->cartoonTimer = gcnew Timer(this->components);
            this->endScreenTimer = gcnew Timer(this->components);

            this->Text = "Лес: Мультфильм";
            this->Size = Drawing::Size(800, 600);
            this->StartPosition = FormStartPosition::CenterScreen;

            this->cartoonTimer->Interval = 50;
            this->cartoonTimer->Tick += gcnew EventHandler(this, &Cartoon1::OnCartoonTick);

            this->endScreenTimer->Interval = 1000; // 1 секунда
            this->endScreenTimer->Tick += gcnew EventHandler(this, &Cartoon1::OnEndScreenTick);

            this->backgrounds = gcnew cli::array<String^>{
                    "forest.gif",
                    "field.gif",
                    "second_field.gif"
            };

            this->background = gcnew PictureBox();
            this->background->Size = this->ClientSize;
            this->background->ImageLocation = backgrounds[0];
            this->background->BackColor = Color::White;
            this->background->SizeMode = PictureBoxSizeMode::StretchImage;

            this->kolobok = gcnew PictureBox();
            this->kolobok->Size = Drawing::Size(100, 100);
            this->kolobok->ImageLocation = "boy.png";
            this->kolobok->SizeMode = PictureBoxSizeMode::StretchImage;
            this->kolobok->BackColor = Color::Transparent;
            this->kolobok->Location = Drawing::Point(kolobokX, kolobokY);

            this->wolf = gcnew PictureBox();
            this->wolf->Size = Drawing::Size(200, 200);
            this->wolf->ImageLocation = "wolf.gif";
            this->wolf->SizeMode = PictureBoxSizeMode::StretchImage;
            this->wolf->BackColor = Color::Transparent;
            this->wolf->Location = Drawing::Point(wolfX, wolfY);
            this->wolf->Visible = false;

            this->wolf2 = gcnew PictureBox();
            this->wolf2->Size = Drawing::Size(200, 200);
            this->wolf2->ImageLocation = "wolf2.png";
            this->wolf2->SizeMode = PictureBoxSizeMode::StretchImage;
            this->wolf2->BackColor = Color::Transparent;
            this->wolf2->Location = Drawing::Point(wolf2X, wolf2Y);
            this->wolf2->Visible = false;

            this->fox = gcnew PictureBox();
            this->fox->Size = Drawing::Size(150, 150);
            this->fox->ImageLocation = "fox.gif";
            this->fox->SizeMode = PictureBoxSizeMode::StretchImage;
            this->fox->BackColor = Color::Transparent;
            this->fox->Location = Drawing::Point(foxX, foxY);
            this->fox->Visible = false;

            this->fox2 = gcnew PictureBox();
            this->fox2->Size = Drawing::Size(150, 150);
            this->fox2->ImageLocation = "fox2.png";
            this->fox2->SizeMode = PictureBoxSizeMode::StretchImage;
            this->fox2->BackColor = Color::Transparent;
            this->fox2->Location = Drawing::Point(fox2X, fox2Y);
            this->fox2->Visible = false;

            this->endScreenLabel = gcnew Label();
            this->endScreenLabel->Size = Drawing::Size(800, 600);
            this->endScreenLabel->Location = Drawing::Point(0, 0);
            this->endScreenLabel->Font = gcnew System::Drawing::Font("Arial", 48, FontStyle::Bold);
            this->endScreenLabel->Text = "Конец";
            this->endScreenLabel->TextAlign = ContentAlignment::MiddleCenter;
            this->endScreenLabel->BackColor = Color::White;
            this->endScreenLabel->Visible = false;

            this->Controls->Add(this->background);
            this->background->Controls->Add(this->kolobok);
            this->background->Controls->Add(this->wolf);
            this->background->Controls->Add(this->wolf2);
            this->background->Controls->Add(this->fox);
            this->background->Controls->Add(this->fox2);
            this->Controls->Add(this->endScreenLabel);

            sp->SoundLocation = "les.wav";
            sp->PlayLooping();

            this->cartoonTimer->Start();
        }

        void OnCartoonTick(Object^ sender, EventArgs^ e) {
            switch (stage) {
            case 0:
                kolobokY -= 5;
                kolobokX += 5;
                if (kolobokX >= 750) {
                    stage++;
                    background->ImageLocation = backgrounds[1];
                    kolobokX = 0;
                    kolobokY = 350;
                    kolobok->Size = Drawing::Size(50, 50);
                }
                break;

            case 1:
                wolf2->Visible = true;
                kolobokX += 2;
                kolobokY += 1;
                wolf2->Location = Drawing::Point(wolf2X, wolf2Y);
                if (kolobokX >= 250) {
                    wolf2->Visible = false;
                    wolf->Visible = true;
                    stage++;
                }
                break;

            case 2:
                kolobokX -= 5;
                kolobokY -= 2;
                wolf->Location = Drawing::Point(wolfX, wolfY);
                wolfX -= 5;
                if (kolobokX == 0) {
                    background->ImageLocation = backgrounds[0];
                    wolf->Visible = false;
                    kolobok->Size = Drawing::Size(100, 100);
                    kolobokX = 550;
                    kolobokY = 0;
                    stage++;

                }
                break;

            case 3:
                kolobokX -= 5;
                kolobokY += 7;
                if (kolobokX <= 0) {
                    background->ImageLocation = backgrounds[2];
                    fox2->Visible = true;
                    kolobok->Size = Drawing::Size(100, 100);
                    kolobokX = 450;
                    kolobokY = 450;
                    stage++;
                }
                break;
            
            case 4:
                kolobokX -= 3;
                kolobokY -= 2;
                if (kolobokX == 285) {
                    stage++;
                }
                break;

            case 5:
                kolobokX -= 3;
                kolobokY += 0.5;
                if (kolobokX == 99) {
                    stage++;
                }
                break;

            case 6:
                kolobokX += 3;
                kolobokY -= 2;
                if (kolobokX == 240) {
                    stage++;
                }
                break;

            case 7:
                kolobokX += 3;
                kolobokY += 1;
                if (kolobokX == 459) {
                    stage++;
                }
                break;
            case 8:
                kolobokX += 3;
                if (kolobokX == 513) {
                    fox2->Visible = false;
                    fox->Visible = true;
                    stage++;
                }
                break;
            case 9:
                fox->Location = Drawing::Point(foxX, foxY);
                VAR += 1;
                if (VAR == 24) {
                    cartoonTimer->Stop();
                    fox->Visible = false;
                    ShowEndScreen(); 
                }
                break;
            }

            kolobok->Location = Drawing::Point(kolobokX, kolobokY);
        }

        void ShowEndScreen() {
            endScreenLabel->BringToFront();
            endScreenLabel->Visible = true;
            this->Refresh(); 
            endScreenTimer->Start();
        }

        void OnEndScreenTick(Object^ sender, EventArgs^ e) {
            endScreenDuration--;
            if (endScreenDuration == 0) {
                endScreenTimer->Stop();
                endScreenLabel->Visible = false;

                stage = 0;
                kolobokX = 150;
                kolobokY = 450;
                kolobok->Size = Drawing::Size(100, 100);
                wolfX = 500;
                wolfY = 350;
                foxX = 600;
                foxY = 250;
                wolf2X = 500;
                wolf2Y = 350;
                fox2X = 600;
                fox2Y = 250;
                VAR = 1;
                background->ImageLocation = backgrounds[0];
                endScreenDuration = 4; 
                cartoonTimer->Start();

            }
        }
    };
}
