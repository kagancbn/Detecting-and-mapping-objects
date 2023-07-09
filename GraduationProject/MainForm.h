#pragma once
#include "image.h"
#include "NeuralNetwork.h"
#include "Process.h"
#include <iostream>
#include <fstream>
#include <atlstr.h>
#include "ClassificationForm.h"
#include "CalibrationForm.h"
namespace GraduationProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
			delete[] mean;
			delete[] variance;
			delete[] testData;
			delete[] tag;
			delete[] Samples;
			delete[] targets;
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;


	protected:

	private:
		int  numClass = 0, numSample = 0;
		int inputDim;
		float* Samples, * targets;
		ANN* model = new ANN;
		float* mean;
		float* variance;
		bool initialized = false;
		// test
		float* testData;		// x-y Coord              
		float* tag;					// Class tag
		int numTestSample;

		//bounding boxes

		Boxes* boxes;

		//calibration
		float* Projection = new float[12]; // projection matrix
		point* p = new point; //input point

		bool isCalib = false;
		bool measureMod = false;
		int measurePCount = 0;
		float* imageCoord = new float[2]; // for measure point 


	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;








	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ measureButton;
	private: System::Windows::Forms::Button^ getCoordButton;
	private: System::Windows::Forms::ToolStripMenuItem^ classificationToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ openFormToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ readWeightsToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ extractFeaturesToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ predictToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ calibrationToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ openFormToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ readProjectionMatrixToolStripMenuItem;

		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   void ShowImages(image im, Windows::Forms::PictureBox^ pictureBox) {
			   pictureBox->Width = im.w;
			   pictureBox->Height = im.h;
			   pictureBox->Refresh();
			   Bitmap^ surface = gcnew Bitmap(im.w, im.h);
			   pictureBox->Image = surface;
			   Color c;
			   int psw, bufpos;
			   psw = im.w * im.c;
			   for (int row = 0; row < im.h; row++)
				   for (int col = 0; col < im.w; col++) {
					   bufpos = row * psw + col * im.c;
					   c = Color::FromArgb(im.data[bufpos], im.data[bufpos + 1], im.data[bufpos + 2]);
					   surface->SetPixel(col, row, c);
				   }
		   }//ShowImages
		   void drawB_box(Boxes* Bounding, int box_num) {
			   pictureBox1->Refresh();
			   Drawing::Graphics^ g;
			   g = pictureBox1->CreateGraphics();
			   Pen^ redPen = gcnew Pen(Color::Red);
			   for (int i = 0; i < box_num; i++)
			   {
				   Drawing::Rectangle rect(Bounding[i].left, Bounding[i].top, Bounding[i].right - Bounding[i].left, Bounding[i].bottom - Bounding[i].top);
				   g->DrawRectangle(redPen, rect);
			   }
		   }
		   void InitializeComponent(void)
		   {
			   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->classificationToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFormToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readWeightsToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->calibrationToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFormToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->readProjectionMatrixToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			   this->measureButton = (gcnew System::Windows::Forms::Button());
			   this->getCoordButton = (gcnew System::Windows::Forms::Button());
			   this->openToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->extractFeaturesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->predictToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			   this->menuStrip1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // pictureBox1
			   // 
			   this->pictureBox1->Location = System::Drawing::Point(11, 63);
			   this->pictureBox1->Margin = System::Windows::Forms::Padding(2);
			   this->pictureBox1->Name = L"pictureBox1";
			   this->pictureBox1->Size = System::Drawing::Size(797, 977);
			   this->pictureBox1->TabIndex = 0;
			   this->pictureBox1->TabStop = false;
			   this->pictureBox1->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &MainForm::pictureBox1_MouseClick);
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->openToolStripMenuItem,
					   this->classificationToolStripMenuItem1, this->calibrationToolStripMenuItem1
			   });
			   this->menuStrip1->Location = System::Drawing::Point(0, 0);
			   this->menuStrip1->Name = L"menuStrip1";
			   this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			   this->menuStrip1->Size = System::Drawing::Size(1130, 24);
			   this->menuStrip1->TabIndex = 1;
			   this->menuStrip1->Text = L"menuStrip1";
			   // 
			   // classificationToolStripMenuItem1
			   // 
			   this->classificationToolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->openFormToolStripMenuItem,
					   this->readWeightsToolStripMenuItem1
			   });
			   this->classificationToolStripMenuItem1->Name = L"classificationToolStripMenuItem1";
			   this->classificationToolStripMenuItem1->Size = System::Drawing::Size(89, 20);
			   this->classificationToolStripMenuItem1->Text = L"Classification";
			   // 
			   // openFormToolStripMenuItem
			   // 
			   this->openFormToolStripMenuItem->Name = L"openFormToolStripMenuItem";
			   this->openFormToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->openFormToolStripMenuItem->Text = L"Open Form";
			   this->openFormToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openFormToolStripMenuItem_Click);
			   // 
			   // readWeightsToolStripMenuItem1
			   // 
			   this->readWeightsToolStripMenuItem1->Name = L"readWeightsToolStripMenuItem1";
			   this->readWeightsToolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			   this->readWeightsToolStripMenuItem1->Text = L"Read Weights";
			   this->readWeightsToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::readWeightsToolStripMenuItem1_Click);
			   // 
			   // calibrationToolStripMenuItem1
			   // 
			   this->calibrationToolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				   this->openFormToolStripMenuItem1,
					   this->readProjectionMatrixToolStripMenuItem
			   });
			   this->calibrationToolStripMenuItem1->Name = L"calibrationToolStripMenuItem1";
			   this->calibrationToolStripMenuItem1->Size = System::Drawing::Size(77, 20);
			   this->calibrationToolStripMenuItem1->Text = L"Calibration";
			   // 
			   // openFormToolStripMenuItem1
			   // 
			   this->openFormToolStripMenuItem1->Name = L"openFormToolStripMenuItem1";
			   this->openFormToolStripMenuItem1->Size = System::Drawing::Size(194, 22);
			   this->openFormToolStripMenuItem1->Text = L"Open Form";
			   this->openFormToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::openFormToolStripMenuItem1_Click);
			   // 
			   // readProjectionMatrixToolStripMenuItem
			   // 
			   this->readProjectionMatrixToolStripMenuItem->Name = L"readProjectionMatrixToolStripMenuItem";
			   this->readProjectionMatrixToolStripMenuItem->Size = System::Drawing::Size(194, 22);
			   this->readProjectionMatrixToolStripMenuItem->Text = L"Read Projection Matrix";
			   this->readProjectionMatrixToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::readProjectionMatrixToolStripMenuItem_Click);
			   // 
			   // openFileDialog1
			   // 
			   this->openFileDialog1->FileName = L"openFileDialog1";
			   // 
			   // textBox1
			   // 
			   this->textBox1->Location = System::Drawing::Point(934, 193);
			   this->textBox1->Multiline = true;
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(158, 197);
			   this->textBox1->TabIndex = 5;
			   // 
			   // label1
			   // 
			   this->label1->Location = System::Drawing::Point(550, 36);
			   this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(34, 14);
			   this->label1->TabIndex = 0;
			   // 
			   // checkBox1
			   // 
			   this->checkBox1->AutoSize = true;
			   this->checkBox1->Location = System::Drawing::Point(934, 63);
			   this->checkBox1->Margin = System::Windows::Forms::Padding(2);
			   this->checkBox1->Name = L"checkBox1";
			   this->checkBox1->Size = System::Drawing::Size(91, 17);
			   this->checkBox1->TabIndex = 6;
			   this->checkBox1->Text = L"Measure Mod";
			   this->checkBox1->UseVisualStyleBackColor = true;
			   this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MainForm::checkBox1_CheckedChanged);
			   // 
			   // measureButton
			   // 
			   this->measureButton->Location = System::Drawing::Point(934, 86);
			   this->measureButton->Margin = System::Windows::Forms::Padding(2);
			   this->measureButton->Name = L"measureButton";
			   this->measureButton->Size = System::Drawing::Size(74, 33);
			   this->measureButton->TabIndex = 7;
			   this->measureButton->Text = L"Measure";
			   this->measureButton->UseVisualStyleBackColor = true;
			   this->measureButton->Click += gcnew System::EventHandler(this, &MainForm::measureButton_Click);
			   // 
			   // getCoordButton
			   // 
			   this->getCoordButton->Location = System::Drawing::Point(934, 137);
			   this->getCoordButton->Margin = System::Windows::Forms::Padding(2);
			   this->getCoordButton->Name = L"getCoordButton";
			   this->getCoordButton->Size = System::Drawing::Size(74, 32);
			   this->getCoordButton->TabIndex = 8;
			   this->getCoordButton->Text = L"Get Coords";
			   this->getCoordButton->UseVisualStyleBackColor = true;
			   this->getCoordButton->Click += gcnew System::EventHandler(this, &MainForm::getCoordButton_Click);
			   // 
			   // openToolStripMenuItem1
			   // 
			   this->openToolStripMenuItem1->Name = L"openToolStripMenuItem1";
			   this->openToolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			   this->openToolStripMenuItem1->Text = L"Object Detection";
			   this->openToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainForm::openToolStripMenuItem1_Click);
			   // 
			   // extractFeaturesToolStripMenuItem
			   // 
			   this->extractFeaturesToolStripMenuItem->Name = L"extractFeaturesToolStripMenuItem";
			   this->extractFeaturesToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->extractFeaturesToolStripMenuItem->Text = L"Extract Features";
			   this->extractFeaturesToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::extractFeaturesToolStripMenuItem_Click);
			   // 
			   // predictToolStripMenuItem
			   // 
			   this->predictToolStripMenuItem->Name = L"predictToolStripMenuItem";
			   this->predictToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			   this->predictToolStripMenuItem->Text = L"Predict";
			   this->predictToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::predictToolStripMenuItem_Click);
			   // 
			   // openToolStripMenuItem
			   // 
			   this->openToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				   this->openToolStripMenuItem1,
					   this->extractFeaturesToolStripMenuItem, this->predictToolStripMenuItem
			   });
			   this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			   this->openToolStripMenuItem->Size = System::Drawing::Size(70, 20);
			   this->openToolStripMenuItem->Text = L"Detection";
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1130, 857);
			   this->Controls->Add(this->getCoordButton);
			   this->Controls->Add(this->measureButton);
			   this->Controls->Add(this->checkBox1);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->pictureBox1);
			   this->Controls->Add(this->menuStrip1);
			   this->MainMenuStrip = this->menuStrip1;
			   this->Margin = System::Windows::Forms::Padding(2);
			   this->Name = L"MainForm";
			   this->Text = L"MyForm";
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private: System::Void openToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		CString str;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//Load image
			str = openFileDialog1->FileName;
			CStringA s2(str);
			const char* input = s2;
			image im = load_image(input);
			//Segmentation - Background removing - Binary image
			im = rgb_to_gray(im.w, im.h, im.data);
			im = Smoothing(im, 3);
			int** histogram = Histogram(im);
			int* T_values; int T_number = 2;
			T_values = K_means(histogram, T_number, 1);
			im = gray_to_binary_image(im, T_values);
			//im = Erosion(im);
			//im = Dilation(im);
			//Drawing bounding box - Labeling objects-
			int* tagged_data = Connectivity(im);
			Boxes* bounding = bounding_box(tagged_data, im);
			ShowImages(im, pictureBox1);
			drawB_box(bounding, bounding->obj_num);
		}//		
	}

	private: System::Void extractFeaturesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		CString str;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//Load image
			str = openFileDialog1->FileName;
			CStringA s2(str);
			const char* input = s2;
			image im = load_image(input);
			//Segmentation - Background removing - Binary image
			im = rgb_to_gray(im.w, im.h, im.data);
			im = Smoothing(im, 3);
			int** histogram = Histogram(im);
			int* T_values; int T_number = 2;
			T_values = K_means(histogram, T_number, 1); // T values are piksel values that background and foreground
			im = gray_to_binary_image(im, T_values);
			im = Erosion(im);
			im = Dilation(im);
			ShowImages(im, pictureBox1);
			//Drawing bounding box - Numareting objects-
			int* tagged_data = Connectivity(im);
			Boxes* bounding = bounding_box(tagged_data, im);
			// Feature extraction
			FeatureExtraction(bounding, tagged_data, bounding->obj_num, im);
			drawB_box(bounding, bounding->obj_num);
		}//	
	}
	private: System::Void predictToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		CString str;
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			//Load image
			str = openFileDialog1->FileName;
			CStringA s2(str);
			const char* input = s2;
			image im = load_image(input);
			//Segmentation - Background removing - Binary image
			im = rgb_to_gray(im.w, im.h, im.data);
			im = Smoothing(im, 5);
			int** histogram = Histogram(im);
			int* T_values; int T_number = 2;
			T_values = K_means(histogram, T_number, 1); // T values are piksel values that background and foreground
			im = gray_to_binary_image(im, T_values);
			im = Erosion(im);
			im = Dilation(im);
			//Drawing bounding box - Numareting objects-
			int* tagged_data = Connectivity(im);
			Boxes* bounding = bounding_box(tagged_data, im);
			boxes = bounding;
			//Prediction
			image im1 = make_empty_image(im.w, im.h, 3);
			im1 = Prediction(bounding, tagged_data, im1, model, mean, variance);
			ShowImages(im1, pictureBox1);
			drawB_box(bounding, bounding->obj_num);
		}//	

	}

	private: System::Void measureButton_Click(System::Object^ sender, System::EventArgs^ e) {
		if (measurePCount == 2)
		{
			float* realWorld = new float[6]; // for measrue point
			Reconstruct(2, imageCoord, Projection, realWorld);
			float distance = sqrt(pow(realWorld[0] - realWorld[3], 2) + pow(realWorld[1] - realWorld[4], 2));
			distance = distance / 10; // mm to cm
			textBox1->AppendText("\nDistance : " + distance + " cm" + "\n");
			measurePCount = 0;
		}

	}
	private: System::Void pictureBox1_MouseClick(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (measureMod) // For measure a two point
		{
			imageCoord[measurePCount * 2] = e->X - 3; //input
			imageCoord[measurePCount * 2 + 1] = e->Y - 3;
			measurePCount++;
			if (measurePCount == 2) {
				MessageBox::Show("Click on Measure button");
			}

			//textBox1->AppendText("X : " + realWorld[0] + "Y : " + realWorld[1] + "\n");
		}

		p->X = e->X;// For Reconstruct Points
		p->Y = e->Y;

	}
	private: System::Void getCoordButton_Click(System::Object^ sender, System::EventArgs^ e) {

		int obj_count = boxes->obj_num;
		float* center_coords = new float[obj_count * 2];
		for (int i = 0; i < obj_count; i++)
		{
			center_coords[i * 2] = boxes[i].left + (boxes[i].right - boxes[i].left) / 2; // X - col
			center_coords[i * 2 + 1] = boxes[i].top + (boxes[i].bottom - boxes[i].top) / 2; // Y - row
		}
		float* real_world_coords = new float[obj_count * 3];
		Reconstruct(obj_count, center_coords, Projection, real_world_coords);

		char** c = new char* [1];
		c[0] = "Data/Coordinates.txt";
		std::ofstream file(c[0]);
		if (!file.bad())
		{
			for (int i = 0; i < obj_count; i++)
				file << real_world_coords[i * 3] << " " << real_world_coords[i * 3 + 1] << " " << boxes[i].obj_id << std::endl;

			MessageBox::Show("Real world coords writed to the file.");

		}

	}
	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (checkBox1->Checked) {

			if (!isCalib)
				MessageBox::Show("You have to calibrate first");
			else {
				measureMod = true;
				MessageBox::Show("Clik on two point on image");
			}
		}
	}
	private: System::Void openFormToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		ClassificationForm^ frmClass = gcnew ClassificationForm;
		frmClass->Show();
	}
	private: System::Void openFormToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		CalibrationForm^ frmCalib = gcnew CalibrationForm;
		frmCalib->Show();
	}
	private: System::Void readWeightsToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
		char** c = new char* [1];
		// Veri Kümesini okunacak 
		c[0] = "Data/MeanVariance.txt";
		std::ifstream file;
		int num, samplenum, Dim, label;
		file.open(c[0]);
		if (file.is_open()) {
			file >> Dim >> num;
			mean = new float[Dim];
			variance = new float[Dim];
			inputDim = Dim;
			for (int d = 0; d < inputDim; d++)
				file >> mean[d];
			for (int d = 0; d < inputDim; d++)
				file >> variance[d];
			file.close();
			MessageBox::Show("Dosya basari ile okundu");
			model->InitFromFile();
			initialized = true;
		}//file.is_open
		else MessageBox::Show("Mean Variance icin Dosya acilamadi");
		delete[]c;

	}
	private: System::Void readProjectionMatrixToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		readProjection(Projection);
		isCalib = true;
		MessageBox::Show("Projection Matrix Read");
	}
	};
}

