#include "texturegenerator.h"

bool TextureApplication::OnInit() {
	TextureFrame* fr = new TextureFrame();
	fr->Show();
	return true;
}

BEGIN_EVENT_TABLE(TextureFrame, wxFrame)
EVT_MENU(ID_EXIT, TextureFrame::OnExit)
EVT_BUTTON(ID_GENERATE, TextureFrame::OnGenerate)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(TextureViewer, wxWindow)
	
END_EVENT_TABLE()

IMPLEMENT_APP(TextureApplication);