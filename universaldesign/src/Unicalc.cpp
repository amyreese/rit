/**
 * Unicalc.cpp
 *
 * @author John Reese
 */

#include <QtGui>

#include "Unicalc.h"
#include "UnicalcLua.h"
#include "UnicalcMath.h"
#include "UnicalcAccess.h"

Unicalc::Unicalc()
{
	setWindowTitle(tr("Unicalc 0.1"));

	createActions();
	createMenus();
	createToolbar();
	statusBar() -> showMessage(tr(""));
	createLayout();

	bPrefSpeech = bPrefSound = bPrefVisual = true;

	math = new UnicalcMath();
	lua = new UnicalcLua(this);

	createConnections();

	QWidget *widget = new QWidget();
	widget -> setLayout(layoutMain);
	setCentralWidget(widget);

	QAccessible::setRootObject( widget );
	this -> changes();
}

void Unicalc::changes () {
	char symbol = math -> symbol();
	
	QString screen = math -> last();
	
	if ( '=' == symbol ) {
		screen = screen.prepend(" ").prepend(symbol);
	}

	screen = screen.append("<br />");

	if ( '=' != symbol ) {
		screen = screen.append(symbol).append(" ");
	}

	screen = screen.append(math -> current());

	screenCurrent -> setHtml(screen);
	screenLast -> setHtml(math -> history());

}

void Unicalc::click(QString name, int delay)
{
	QPushButton *button = NULL;

	if (name == "0") { 
		button = buttonNum0; 
	}
	else if (name == "1") { 
		button = buttonNum1; 
	}
	else if (name == "2") { 
		button = buttonNum2; 
	}
	else if (name == "3") { 
		button = buttonNum3; 
	}
	else if (name == "4") { 
		button = buttonNum4; 
	}
	else if (name == "5") { 
		button = buttonNum5; 
	}
	else if (name == "6") { 
		button = buttonNum6; 
	}
	else if (name == "7") { 
		button = buttonNum7; 
	}
	else if (name == "8") { 
		button = buttonNum8; 
	}
	else if (name == "9") { 
		button = buttonNum9; 
	}

	else if (name == ".") { 
		button = buttonDecimal; 
	}
	else if (name == "+/-") { 
		button = buttonChangeSign; 
	}
	else if (name == "+") { 
		button = buttonPlus; 
	}
	else if (name == "-") { 
		button = buttonMinus; 
	}
	else if (name == "*") { 
		button = buttonMultiply; 
	}
	else if (name == "/") { 
		button = buttonDivide; 
	}
	else if (name == "=") { 
		button = buttonEquals; 
	}

	else if (name == "Back") { 
		button = buttonBackspace; 
	}
	else if (name == "C") { 
		button = buttonClear; 
	}
	else if (name == "CE") { 
		button = buttonClearAll; 
	}

	if (button != NULL) {
		QTimer::singleShot(delay, button, SLOT(animateClick()));
	}
}

void Unicalc::errors () { 
	statusBar() -> showMessage(tr("Error"));
	//errorBeep();
}
void Unicalc::errors (QString desc) { 
	statusBar() -> showMessage(desc);
	//errorBeep();
}
void Unicalc::results () { }

void Unicalc::prefSpeech () { this -> bPrefSpeech = actionPrefSpeech -> isChecked(); }
void Unicalc::prefSound () { this -> bPrefSound = actionPrefSound -> isChecked(); }
void Unicalc::prefVisual () { this -> bPrefVisual = actionPrefVisual -> isChecked(); }

void Unicalc::resizeFonts () 
{
	QFont f = buttonNum0 -> font();
	f.setPixelSize( buttonNum0 -> height() * 3 / 7 );
	f.setBold( true );

	screenLast -> setFont( f );
	screenCurrent -> setFont( f );

	buttonNum0 -> setFont( f );
	buttonNum1 -> setFont( f );
	buttonNum2 -> setFont( f );
	buttonNum3 -> setFont( f );
	buttonNum4 -> setFont( f );
	buttonNum5 -> setFont( f );
	buttonNum6 -> setFont( f );
	buttonNum7 -> setFont( f );
	buttonNum8 -> setFont( f );
	buttonNum9 -> setFont( f );
	buttonDecimal -> setFont( f );
	buttonChangeSign -> setFont( f );
	buttonPlus -> setFont( f );
	buttonMinus -> setFont( f );
	buttonMultiply -> setFont( f );
	buttonDivide -> setFont( f );
	buttonEquals -> setFont( f );
	buttonBackspace -> setFont( f );
	buttonClear -> setFont( f );
	buttonClearAll -> setFont( f );
}

void Unicalc::errorEvent () 
{
	//QPalette p = this -> palette();
	//QPalette q = this -> palette();
	//p.setBrush( QPalette::Background, Qt::black );
	//this -> setPalette( p );
	if ( bPrefVisual ) {
		this -> setWindowOpacity( 0.2 );
		this -> update();
		this -> repaint();

		QTime t;
		t.start();
		while (t.elapsed() < 250) { }

		this -> setWindowOpacity( 1.0 );
	}

	if ( bPrefSound ) {
		QSound* s = new QSound( "ding.wav" );//Error Beep!
		QTimer::singleShot( 10, s, SLOT(play()) );
	}
}

void Unicalc::closeEvent (QCloseEvent *event)
{
	event->accept();
}

QAction* Unicalc::actionTemplate (char* title, char* tooltip, char* shortcut, char* icon)
{
	QAction *action  = new QAction(QIcon(icon), tr(title), this);
	action -> setShortcut(tr(shortcut));
	action -> setStatusTip(tr(tooltip));
	//action -> setAccessibleName(tr(title));
	return action;
}

void Unicalc::createActions ()
{
	actionQuit = actionTemplate("&Quit", "Quit Unicalc", "Ctrl+Q", "");
	
	actionPrefSpeech = actionTemplate("&Text-to-Speech", "Enable/disable text-to-speech", "", "");
	actionPrefSpeech -> setCheckable(true);
	actionPrefSpeech -> setChecked(true);

	actionPrefSound = actionTemplate("&Sound Cues", "Enable/disable audible cues", "", "");
	actionPrefSound -> setCheckable(true);
	actionPrefSound -> setChecked(true);

	actionPrefVisual = actionTemplate("&Visual Cues", "Enable/disable visual cues", "", "");
	actionPrefVisual -> setCheckable(true);
	actionPrefVisual -> setChecked(true);

	
	actionAbout = actionTemplate("&About", "Information about Unicalc", "", ":/images/icon.png");
	actionHelp = actionTemplate("&Help", "How to use Unicalc", "F1", "");
	
	actionLuaRun = actionTemplate("&Run", "Execute Lua script", "Ctrl+R", "");
	actionLuaLoad = actionTemplate("&Load", "Load Lua script from file", "Ctrl+L", "");
	actionLuaReset = actionTemplate("Re&set", "Clear and reload Lua interpreter", "Ctrl+S", "");
}

void Unicalc::createMenus ()
{
	menuFile = menuBar() -> addMenu(tr("&File"));
	menuFile -> setAccessibleName(tr("File"));
	menuFile -> addAction(actionQuit);

	menuSettings = menuBar() -> addMenu(tr("&Settings"));
	menuSettings -> setAccessibleName(tr("Settings"));
	menuSettings -> addAction(actionPrefSpeech);
	menuSettings -> addAction(actionPrefSound);
	menuSettings -> addAction(actionPrefVisual);

	menuHelp = menuBar() -> addMenu(tr("&Help"));
	menuHelp -> setAccessibleName(tr("Help"));
	menuHelp -> addAction(actionHelp);
	menuHelp -> addAction(actionAbout);
	menuHelp -> addSeparator();
	menuLua = menuHelp -> addMenu(tr("&Lua"));
	menuLua -> setAccessibleName(tr("Lua"));
	menuLua -> addAction(actionLuaLoad);
	menuLua -> addAction(actionLuaRun);
	menuLua -> addSeparator();
	menuLua -> addAction(actionLuaReset);

}

void Unicalc::createToolbar ()
{
	return;

	toolbarFile = addToolBar(tr("File"));
	toolbarFile -> addAction(actionQuit);
}

void Unicalc::createLayout ()
{
	createButtons();

	screenCurrent = new QTextEdit();
	screenCurrent -> setMinimumHeight(32);
	screenCurrent -> setMaximumHeight(64);
	screenCurrent -> document() -> setDefaultStyleSheet("* { text-align: right; }");
	screenCurrent -> setDisabled( true );
	screenCurrent -> setReadOnly( true );

	screenLast = new QTextEdit();
	screenLast -> setMinimumHeight(32);
	screenLast -> setMaximumHeight(64);
	screenLast -> setDisabled( true );
	screenLast -> setReadOnly( true );

	layoutMain = new QGridLayout();
	layoutMain -> addWidget(screenLast, 0, 0, 1, 4);
	layoutMain -> addWidget(screenCurrent, 1, 0, 1, 4);

	layoutMain -> addWidget(buttonNum7, 3, 0);
	layoutMain -> addWidget(buttonNum8, 3, 1);
	layoutMain -> addWidget(buttonNum9, 3, 2);
	layoutMain -> addWidget(buttonNum4, 4, 0);
	layoutMain -> addWidget(buttonNum5, 4, 1);
	layoutMain -> addWidget(buttonNum6, 4, 2);
	layoutMain -> addWidget(buttonNum1, 5, 0);
	layoutMain -> addWidget(buttonNum2, 5, 1);
	layoutMain -> addWidget(buttonNum3, 5, 2);
	layoutMain -> addWidget(buttonNum0, 6, 0);
	
	layoutMain -> addWidget(buttonDecimal, 6, 1);
	layoutMain -> addWidget(buttonChangeSign, 6, 2);
	layoutMain -> addWidget(buttonPlus, 5, 3);
	layoutMain -> addWidget(buttonMinus, 4, 3);
	layoutMain -> addWidget(buttonMultiply, 3, 3);
	layoutMain -> addWidget(buttonDivide, 2, 3);
	layoutMain -> addWidget(buttonEquals, 6, 3);

	layoutMain -> addWidget(buttonBackspace, 2, 0);
	layoutMain -> addWidget(buttonClear, 2, 1);
	layoutMain -> addWidget(buttonClearAll, 2, 2);

}

void Unicalc::createButtons ()
{
	buttonNum0 = buttonTemplate("0","0",80,true);
	buttonNum1 = buttonTemplate("1","1",80,true);
	buttonNum2 = buttonTemplate("2","2",80,true);
	buttonNum3 = buttonTemplate("3","3",80,true);
	buttonNum4 = buttonTemplate("4","4",80,true);
	buttonNum5 = buttonTemplate("5","5",80,true);
	buttonNum6 = buttonTemplate("6","6",80,true);
	buttonNum7 = buttonTemplate("7","7",80,true);
	buttonNum8 = buttonTemplate("8","8",80,true);
	buttonNum9 = buttonTemplate("9","9",80,true);
	
	buttonDecimal = buttonTemplate(".",".",80,true);
	buttonChangeSign = buttonTemplate("+/-","Shift+-",80,true);
	buttonPlus = buttonTemplate("+","+",80,true);
	buttonMinus = buttonTemplate("-","-",80,true);
	buttonMultiply = buttonTemplate("*","*",80,true);
	buttonDivide = buttonTemplate("/","/",80,true);
	buttonEquals = buttonTemplate("=","Return",80,true);
	
	buttonBackspace = buttonTemplate("Backspace","Backspace",80,true);
	buttonClear = buttonTemplate("C","Delete",80,true);
	buttonClearAll = buttonTemplate("CE","Shift+Delete",80,true);
}

QPushButton* Unicalc::buttonTemplate (char* title, char* shortcut, int width, bool resize)
{
	QPushButton *button = new QPushButton(tr(title));
	button -> setShortcut(tr(shortcut));
	button -> setMinimumWidth(width);
	button -> setAccessibleName(tr(title));
	if (resize) {
		button -> setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);
	}
	return button;
}

void Unicalc::createConnections ()
{
	connect(actionQuit, SIGNAL(triggered()), this, SLOT(close()));

	connect(actionPrefSpeech, SIGNAL(triggered()), this, SLOT(prefSpeech()));
	connect(actionPrefSound, SIGNAL(triggered()), this, SLOT(prefSound()));
	connect(actionPrefVisual, SIGNAL(triggered()), this, SLOT(prefVisual()));
	
	connect(actionLuaLoad, SIGNAL(triggered()), lua, SLOT(load()));
	connect(actionLuaRun, SIGNAL(triggered()), lua, SLOT(exec()));
	connect(actionLuaReset, SIGNAL(triggered()), lua, SLOT(reset()));

	connect(buttonNum0, SIGNAL(clicked()), math, SLOT(press0()));
	connect(buttonNum1, SIGNAL(clicked()), math, SLOT(press1()));
	connect(buttonNum2, SIGNAL(clicked()), math, SLOT(press2()));
	connect(buttonNum3, SIGNAL(clicked()), math, SLOT(press3()));
	connect(buttonNum4, SIGNAL(clicked()), math, SLOT(press4()));
	connect(buttonNum5, SIGNAL(clicked()), math, SLOT(press5()));
	connect(buttonNum6, SIGNAL(clicked()), math, SLOT(press6()));
	connect(buttonNum7, SIGNAL(clicked()), math, SLOT(press7()));
	connect(buttonNum8, SIGNAL(clicked()), math, SLOT(press8()));
	connect(buttonNum9, SIGNAL(clicked()), math, SLOT(press9()));

	connect(buttonDecimal, SIGNAL(clicked()), math, SLOT(pressDecimal()));
	connect(buttonChangeSign, SIGNAL(clicked()), math, SLOT(pressChangeSign()));
	connect(buttonPlus, SIGNAL(clicked()), math, SLOT(pressPlus()));
	connect(buttonMinus, SIGNAL(clicked()), math, SLOT(pressMinus()));
	connect(buttonMultiply, SIGNAL(clicked()), math, SLOT(pressMultiply()));
	connect(buttonDivide, SIGNAL(clicked()), math, SLOT(pressDivide()));
	connect(buttonEquals, SIGNAL(clicked()), math, SLOT(pressEquals()));

	connect(buttonBackspace, SIGNAL(clicked()), math, SLOT(pressBackspace()));
	connect(buttonClear, SIGNAL(clicked()), math, SLOT(pressClear()));
	connect(buttonClearAll, SIGNAL(clicked()), math, SLOT(pressClearAll()));

	connect(math, SIGNAL(changed()), this, SLOT(changes()));
	connect(math, SIGNAL(error(QString)), this, SLOT(errors(QString)));
	connect(math, SIGNAL(error()), this, SLOT(errors()));
}


//EOF

