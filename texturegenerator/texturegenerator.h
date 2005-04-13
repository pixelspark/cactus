#include <wx/wx.h>
#include <wx/image.h>
#include "../include/cactus.h"

enum {
	ID_EXIT=1,
	ID_GENERATE,
	ID_DENSITY,
	ID_TYPE,
	ID_COL1,
	ID_COL2,
};

class TextureApplication: public wxApp {
	public:
		TextureApplication() {
		}
		virtual ~TextureApplication() {
		}


		virtual bool OnInit();
};

class TextureViewer: public wxWindow {
	public:
		TextureViewer(wxWindow* parent,wxPoint pos,wxSize size) : wxWindow(parent, -1, pos, size, wxSTATIC_BORDER, "TextureViewer") {
			Show(true);
		}

		virtual ~TextureViewer() {
		}

		void Generate(float f,wxString type,long col1, long col2) {
			// generate here
			CTextureFactory factory;
			int h;
			int w;
			this->GetSize(&w,&h);

			CTexture t;
			if(type=="Sky") {
				t = factory.Sky(w,h,f);
			}
			else if(type=="Wood") {
				t = factory.Wood(w,h,f);
			}
			else if(type=="Marble") {
				t = factory.Marble(w,h,f);
			}

			PaintTexture(t);
		}

		void PaintTexture(CTexture& t) {
				wxClientDC* dc = new wxClientDC(this);
				unsigned char* data =  t.GetDataAsRGBA();
				wxImage* img = new wxImage(t._width, t._height,data, TRUE);
				dc->BeginDrawing();
				dc->DrawBitmap(img->ConvertToBitmap(),0,0,false);
				dc->EndDrawing();
		}
	
		DECLARE_EVENT_TABLE()
};

class TextureFrame: public wxFrame {
	public:
		TextureFrame() : wxFrame(NULL,-1,"Texture Generator",wxDefaultPosition, wxSize(640,480),wxMINIMIZE_BOX | wxMAXIMIZE_BOX | wxRESIZE_BOX | wxSYSTEM_MENU | wxCAPTION|wxSTATIC_BORDER,"frame") {
			wxMenuBar* bar = new wxMenuBar(0);

			wxMenu* file = new wxMenu(0);
			file->Append(ID_EXIT,"&Exit","Quits this application",FALSE);

			bar->Append(file,"File");
			this->SetMenuBar(bar);
			this->SetAutoLayout(false);

			_viewer = new TextureViewer(this, wxPoint(10,10), wxSize(512,512));
			_viewer->SetBackgroundColour(wxColour(255,255,255));
			_viewer->SetSize(256,256);
			_viewer->Refresh();

			wxString choices[3];
			choices[0] = "Sky";
			choices[1] = "Wood";
			choices[2] = "Marble";

			wxButton* generate = new wxButton(this,ID_GENERATE, "Generate", wxPoint(270,10), wxSize(128,25), NULL, wxDefaultValidator, "button");
			wxTextCtrl* density = new wxTextCtrl(this, ID_DENSITY, "", wxPoint(270,40), wxSize(128,20), wxSTATIC_BORDER, wxDefaultValidator, "density");			
			wxComboBox* type = new wxComboBox(this,ID_TYPE, "Type", wxPoint(270,70),wxSize(128,20),3,choices,wxCB_READONLY,wxDefaultValidator,"comboBox");			
			wxTextCtrl* col1 = new wxTextCtrl(this, ID_COL1, "", wxPoint(270,100), wxSize(128,20), wxSTATIC_BORDER, wxDefaultValidator, "col1");			
			wxTextCtrl* col2 = new wxTextCtrl(this, ID_COL2, "", wxPoint(270,130), wxSize(128,20), wxSTATIC_BORDER, wxDefaultValidator, "col2");			
			

			this->SetBackgroundColour(wxColour(230,230,230));
			this->CreateStatusBar();
			//this->Refresh();
		}

		virtual ~TextureFrame() {
		}

		void OnExit(wxCommandEvent& event) {
			this->Show(false);
			this->Destroy();
		}

		void OnGenerate(wxCommandEvent& event) {
			wxTextCtrl* txt = (wxTextCtrl*)FindWindow(ID_DENSITY);
			wxString val = txt->GetValue();

			wxComboBox* type = (wxComboBox*)FindWindow(ID_TYPE);
			wxString typeval = type->GetValue();

			wxTextCtrl* col1 = (wxTextCtrl*)FindWindow(ID_COL1);
			wxTextCtrl* col2 = (wxTextCtrl*)FindWindow(ID_COL2);
			long coll1;
			long coll2;
			col1->GetValue().ToLong(&coll1);
			col1->GetValue().ToLong(&coll2);

			double s;
			val.ToDouble(&s);

			float f = (float)s;

			_viewer->Generate(f,typeval,coll1, coll2);
		}

		DECLARE_EVENT_TABLE()
	private:
		TextureViewer* _viewer;
};
