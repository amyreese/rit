/**
 * Unicalc.h
 * 
 * @author John Reese
 */

#ifndef UNICALC_H
#define UNICALC_H

#include <QtGui>

#include "UnicalcMath.h"
#include "UnicalcLua.h"

class UniLua;

class Unicalc : public QMainWindow
{
	Q_OBJECT

public:
	Unicalc();
	
	UnicalcMath *math;
	UnicalcLua *lua;

public slots:
	void changes();
	void click(QString button, int delay=0);
	void errors();
	void errors(QString desc);
	void results();
	
	void prefSpeech();
	void prefSound();
	void prefVisual();
	void resizeFonts();

private slots:

protected:
	void closeEvent (QCloseEvent *event);
	void errorEvent ();

private:
	bool bPrefSpeech;
	bool bPrefSound;
	bool bPrefVisual;

	// Methods
	QAction *actionTemplate (char* title, char* tooltip, char* shortcut, char* icon);
	QPushButton* buttonTemplate (char* title, char* shortcut, int width, bool resize);
		
	void createActions();
	void createMenus();
	void createToolbar();

	void createLayout();
	void createButtons();
	void createConnections();

	// Members
	QAction		*actionQuit;

	QAction		*actionPrefSpeech;
	QAction		*actionPrefSound;
	QAction		*actionPrefVisual;
	
	QAction		*actionAbout;
	QAction		*actionHelp;

	QAction		*actionLuaRun;
	QAction		*actionLuaLoad;
	QAction		*actionLuaReset;

	QMenu		*menuFile;
	QMenu		*menuSettings;
	QMenu		*menuLua;
	QMenu		*menuHelp;
	QToolBar	*toolbarFile;
	QToolBar	*toolbarSettings;
	QToolBar	*toolbarLua;
	QToolBar	*toolbarHelp;

	QGridLayout	*layoutMain;

	QTextEdit	*screenCurrent;
	QTextEdit	*screenLast;

	QPushButton	*buttonNum0;
	QPushButton	*buttonNum1;
	QPushButton	*buttonNum2;
	QPushButton	*buttonNum3;
	QPushButton	*buttonNum4;
	QPushButton	*buttonNum5;
	QPushButton	*buttonNum6;
	QPushButton	*buttonNum7;
	QPushButton	*buttonNum8;
	QPushButton	*buttonNum9;

	QPushButton	*buttonDecimal;
	QPushButton	*buttonChangeSign;
	QPushButton	*buttonPlus;
	QPushButton	*buttonMinus;
	QPushButton	*buttonMultiply;
	QPushButton	*buttonDivide;
	QPushButton	*buttonEquals;

	QPushButton	*buttonBackspace;
	QPushButton	*buttonClear;
	QPushButton	*buttonClearAll;

};

#endif // UNICALC_H

// EOF

