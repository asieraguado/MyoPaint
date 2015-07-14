#pragma once
#include "histogram.h"
#include <iostream>

namespace emgdatasampleVisualStudio2013 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Resumen de histGUI
	/// </summary>
	public ref class histGUI : public System::Windows::Forms::Form
	{
	public:
		histGUI(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//
		}
		void updateHist(histogram h);

	protected:
		/// <summary>
		/// Limpiar los recursos que se estén utilizando.
		/// </summary>
		~histGUI()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Variable del diseñador requerida.
		/// </summary>
		System::ComponentModel::Container ^components;
		Graphics ^ graphDrawingArea;
	private: System::Windows::Forms::Label^  lblLeft;
			 Bitmap   ^ bmpDrawingArea;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido del método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->lblLeft = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// lblLeft
			// 
			this->lblLeft->AutoSize = true;
			this->lblLeft->Location = System::Drawing::Point(12, 9);
			this->lblLeft->Name = L"lblLeft";
			this->lblLeft->Size = System::Drawing::Size(0, 13);
			this->lblLeft->TabIndex = 0;
			// 
			// histGUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(324, 181);
			this->ControlBox = false;
			this->Controls->Add(this->lblLeft);
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"histGUI";
			this->ShowIcon = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Gesture recognition";
			this->Load += gcnew System::EventHandler(this, &histGUI::histGUI_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &histGUI::histGUI_Paint);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void histGUI_Load(System::Object^  sender, System::EventArgs^  e) {
		bmpDrawingArea = gcnew Bitmap(Width, Height);
		graphDrawingArea = Graphics::FromImage(bmpDrawingArea);
	}
	private: System::Void histGUI_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		e->Graphics->DrawImage(bmpDrawingArea, 0, 0);
	}
	};
}
