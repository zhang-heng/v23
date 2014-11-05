/*
 * CNavEditor.h
 *
 *  Created on: 2014年11月5日
 *      Author: kay
 */

#ifndef CNAVEDITOR_H_
#define CNAVEDITOR_H_

#include <QmitkAbstractRenderEditor.h>

class CNavEditor: public QmitkAbstractRenderEditor
{
	Q_OBJECT
public:
	virtual ~CNavEditor();
	CNavEditor();

protected:
	virtual void CreateQtPartControl(QWidget *parent);
	virtual void SetFocus();
	void OnPreferencesChanged(const berry::IBerryPreferences*);
};

#endif /* CNAVEDITOR_H_ */
