/***************************************************************
 * Name:      testeMain.h
 * Purpose:   Defines Application Frame
 * Author:    eu ()
 * Created:   2025-10-07
 * Copyright: eu ()
 * License:
 **************************************************************/

#ifndef TESTEMAIN_H
#define TESTEMAIN_H



#include "testeApp.h"



#include "GUIDialog.h"

class testeDialog: public GUIDialog
{
    public:
        testeDialog(wxDialog *dlg);
        ~testeDialog();
    private:
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
};
#endif // TESTEMAIN_H
