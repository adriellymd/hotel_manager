/***************************************************************
 * Name:      testeApp.cpp
 * Purpose:   Code for Application Class
 * Author:    eu ()
 * Created:   2025-10-07
 * Copyright: eu ()
 * License:
 **************************************************************/

#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "testeApp.h"
#include "testeMain.h"

IMPLEMENT_APP(testeApp);

bool testeApp::OnInit()
{
    
    testeDialog* dlg = new testeDialog(0L);
    
    dlg->Show();
    return true;
}
