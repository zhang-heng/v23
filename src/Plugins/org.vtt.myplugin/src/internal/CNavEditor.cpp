/*
 * CNavEditor.cpp
 *
 *  Created on: 2014年11月5日
 *      Author: kay
 */

#include "CNavEditor.h"


CNavEditor::~CNavEditor()
{
}

CNavEditor::CNavEditor()
{
}

void CNavEditor::SetFocus()
{
	MITK_INFO<<"CNavEditor::SetFocus";
}

void CNavEditor::CreateQtPartControl(QWidget *parent)
{
	MITK_INFO<<"CNavEditor::CreateQtPartControl";
}

void CNavEditor::OnPreferencesChanged(const berry::IBerryPreferences*)
{
	MITK_INFO<<"CNavEditor::OnPreferencesChanged";
}
