/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3) as published 
by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.
***************************************************************************
*/

#include <QtGui>


#include "_preferences.h"
#include "_mainwindow.h"
#include "_typedef.h"

extern QString cachePath(QString s);
extern QString kbasicPath(QString sPath);

_preferences::_preferences(QWidget* _parent, bool _bSaveOnly) : QDialog(_parent)
{
  setAttribute(Qt::WA_DeleteOnClose);
  setWindowFlags(windowFlags() | Qt::Dialog);

  parent = _parent;
  bSaveOnly = _bSaveOnly;

  QMap<QString, QWidget*>::Iterator it2;
  for ( it2 = pref.begin(); it2 != pref.end(); ++it2 ) {
    QWidget *m = it2.value();
    delete m;
  }

  
  QVBoxLayout *j = new QVBoxLayout();
  
    setLayout(j);
    j->setMargin(5);
    j->setSpacing(0);

  

  QWidget *tt = new QWidget();
  tt->setFixedSize(1, 5);
  j->addWidget(tt);

  tab = new QTabWidget(); j->addWidget(tab);
  tab->setUsesScrollButtons(true);

  pref.clear();
  pref2.clear();

  my_mainwindow = EXTERN_my_mainwindow;

  int w = 530;
  int h = 480;

#ifdef MAC
  w = 850;
  h = 490;
  resize(w, h); // HIDE
#else
  resize(w, h);
#endif
  setWindowTitle(tr("Preferences"));
  setModal(true);
  
  QWidget *f = new QWidget();
  QHBoxLayout *fj = new QHBoxLayout();
  f->setLayout(fj);
  j->addWidget(f);
 
  QPushButton *p;
#ifdef MAC

  p = new QPushButton(tr("&Close"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performClose()) );

  p = new QPushButton(tr("&Set Default"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performDefault()) );

  p = new QPushButton(tr("&Save"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performSave()) );

#else
  p = new QPushButton(tr("&Save"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performSave()) );

  p = new QPushButton(tr("&Set Default"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performDefault()) );

  p = new QPushButton(tr("&Close"), f); fj->addWidget(p);
  connect(p, SIGNAL( clicked() ), this, SLOT(performClose()) );

#endif


  pref2["Standard"] = my_mainwindow->getPreference("Standard");
  pref2["Keyword"] = my_mainwindow->getPreference("Keyword");
  pref2["Builtin Function"] = my_mainwindow->getPreference("Builtin Function");
  pref2["Type"] = my_mainwindow->getPreference("Type");
  pref2["Operator"] = my_mainwindow->getPreference("Operator");
  pref2["Symbol"] = my_mainwindow->getPreference("Symbol");
  pref2["String"] = my_mainwindow->getPreference("String");
  pref2["Comment"] = my_mainwindow->getPreference("Comment");
  pref2["Bookmark"] = my_mainwindow->getPreference("Bookmark");
  pref2["Breakpoint"] = my_mainwindow->getPreference("Breakpoint");
  pref2["Debug Line"] = my_mainwindow->getPreference("Debug Line");
  pref2["Current Line"] = my_mainwindow->getPreference("Current Line");
  pref2["Marked Line"] = my_mainwindow->getPreference("Marked Line");
  pref2["Marked Comment"] = my_mainwindow->getPreference("Marked Comment");

  setupGeneral();  
  setupSourceCodeEditor();
  
  setupCompatibility();
  setupScanner();
  setupParser();
  setupCompiler();
  setupInterpreter();

  
  if (_bSaveOnly){
    performSave();
    return;
  }

 
  move(QApplication::desktop()->width() / 2 - width() / 2, QApplication::desktop()->height() / 2 - height() / 2);
  show();
  qApp->setActiveWindow(this);
  this-exec();
  
}
void _preferences::setupGeneral()
{

  QLabel *l;

    QWidget *g = new QWidget();

    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    
    a->setWidgetResizable(true);

    bool t = false;
/*
    pref["SplashScreen"] = new QCheckBox(tr("&Splash-Screen on startup"), g); j->addWidget(pref["SplashScreen"]);
    ((QCheckBox *) (pref["SplashScreen"]))->setChecked( my_mainwindow->isPreferenceSet("SplashScreen") );
    pref["SplashScreen"]->setDisabled(true);*/
/*
    pref["BackgroundImages"] = new QCheckBox(tr("&Background Images"), g); j->addWidget(pref["BackgroundImages"]);
    ((QCheckBox *) (pref["BackgroundImages"]))->setChecked( my_mainwindow->isPreferenceSet("BackgroundImages") );
    //pref["BackgroundImages"]->setDisabled(true);
*/
#ifndef MAC
    pref["WelcomeScreen"] = new QCheckBox(tr("Show &Welcome-Screen"), g); j->addWidget(pref["WelcomeScreen"]);
    ((QCheckBox *) (pref["WelcomeScreen"]))->setChecked( my_mainwindow->isPreferenceSet("WelcomeScreen") );
    ((QCheckBox *) (pref["WelcomeScreen"]))->setDisabled(t);
	#endif

    pref["ThanksScreen"] = new QCheckBox(tr("&Thanks-Screen after exiting"), g); j->addWidget(pref["ThanksScreen"]);
    ((QCheckBox *) (pref["ThanksScreen"]))->setChecked( my_mainwindow->isPreferenceSet("ThanksScreen") );
    ((QCheckBox *) (pref["ThanksScreen"]))->setDisabled(t);
/*
    pref["CompileScreen"] = new QCheckBox(tr("&Compile-Screen when Starting"), g); j->addWidget(pref["CompileScreen"]);
    ((QCheckBox *) (pref["CompileScreen"]))->setChecked( my_mainwindow->isPreferenceSet("CompileScreen") );
    ((QCheckBox *) (pref["CompileScreen"]))->setDisabled(t);*/
/*
    pref["ShowColorizedIcon"] = new QCheckBox( tr("Show Icons colorfully"), g); j->addWidget(pref["ShowColorizedIcon"]);
    ((QCheckBox *) (pref["ShowColorizedIcon"]))->setChecked( my_mainwindow->isPreferenceSet("ShowColorizedIcon") );
    ((QCheckBox *) (pref["ShowColorizedIcon"]))->setDisabled(t);
    */
/*
    pref["HelpPropertyWindow"] = new QCheckBox( tr("Show Help &Property Window"), g); j->addWidget(pref["HelpPropertyWindow"]);
    ((QCheckBox *) (pref["HelpPropertyWindow"]))->setChecked( my_mainwindow->isPreferenceSet("HelpPropertyWindow") );
    ((QCheckBox *) (pref["HelpPropertyWindow"]))->setDisabled(t);

    pref["GridInFormDesign"] = new QCheckBox( tr("Show &Grid in Form Design"), g); j->addWidget(pref["GridInFormDesign"]);
    ((QCheckBox *) (pref["GridInFormDesign"]))->setChecked( my_mainwindow->isPreferenceSet("GridInFormDesign") );
    ((QCheckBox *) (pref["GridInFormDesign"]))->setDisabled(true);*/
/*
    pref["BackImageInFormDesign"] = new QCheckBox( tr("Show Back-&Image in Form Design"), g); j->addWidget(pref["BackImageInFormDesign"]);
    ((QCheckBox *) (pref["BackImageInFormDesign"]))->setChecked( my_mainwindow->isPreferenceSet("BackImageInFormDesign") );
    ((QCheckBox *) (pref["BackImageInFormDesign"]))->setDisabled(true);  

    pref["KBasicScreenshot"] = new QCheckBox( tr("Show KBasic Scr&eenshots"), g); j->addWidget(pref["KBasicScreenshot"]);
    ((QCheckBox *) (pref["KBasicScreenshot"]))->setChecked( my_mainwindow->isPreferenceSet("KBasicScreenshot") );
    ((QCheckBox *) (pref["KBasicScreenshot"]))->setDisabled(t);  

    pref["ExamplesInMenu"] = new QCheckBox( tr("Show Examples in Main-Menu"), g); j->addWidget(pref["ExamplesInMenu"]);
    ((QCheckBox *) (pref["ExamplesInMenu"]))->setChecked( my_mainwindow->isPreferenceSet("ExamplesInMenu") );
    ((QCheckBox *) (pref["ExamplesInMenu"]))->setDisabled(t);  

    pref["EnableUnfinished"] = new QCheckBox( tr("Enable Under-Construction Features"), g); j->addWidget(pref["EnableUnfinished"]);
    ((QCheckBox *) (pref["EnableUnfinished"]))->setChecked( my_mainwindow->isPreferenceSet("EnableUnfinished") );
    ((QCheckBox *) (pref["EnableUnfinished"]))->setDisabled(t);      

    pref["StatusBar"] = new QCheckBox( tr("Show St&atusbar"), g); j->addWidget(pref["StatusBar"]);
    ((QCheckBox *) (pref["StatusBar"]))->setChecked( my_mainwindow->isPreferenceSet("StatusBar") );
    ((QCheckBox *) (pref["StatusBar"]))->setDisabled(t);  
*/
    pref["IntroductionHelp"] = new QCheckBox( tr("Introduction &Help"), g); j->addWidget(pref["IntroductionHelp"]);
    ((QCheckBox *) (pref["IntroductionHelp"]))->setChecked( my_mainwindow->isPreferenceSet("IntroductionHelp") );
    ((QCheckBox *) (pref["IntroductionHelp"]))->setDisabled(t);
/*
    pref["MenuIcon"] = new QCheckBox( tr("Show &Icons In Menu"), g); j->addWidget(pref["MenuIcon"]);
    ((QCheckBox *) (pref["MenuIcon"]))->setChecked( my_mainwindow->isPreferenceSet("MenuIcon") );
    ((QCheckBox *) (pref["MenuIcon"]))->setDisabled(t);  
   
    pref["CachedCompilation"] = new QCheckBox( tr("Activate Cached Compilation"), g); j->addWidget(pref["CachedCompilation"]);
    ((QCheckBox *) (pref["CachedCompilation"]))->setChecked( my_mainwindow->isPreferenceSet("CachedCompilation") );
    ((QCheckBox *) (pref["CachedCompilation"]))->setDisabled(t);*/
/*
    pref["ConsoleInfo"] = new QCheckBox( tr("Activate Virtual Machine Info"), g); j->addWidget(pref["ConsoleInfo"]);
    ((QCheckBox *) (pref["ConsoleInfo"]))->setChecked( my_mainwindow->isPreferenceSet("ConsoleInfo") );
    ((QCheckBox *) (pref["ConsoleInfo"]))->setDisabled(t);

    pref["ConsoleDebugInfo"] = new QCheckBox( tr("Show Virtual Machine Info In Console"), g); j->addWidget(pref["ConsoleDebugInfo"]);
    ((QCheckBox *) (pref["ConsoleDebugInfo"]))->setChecked( my_mainwindow->isPreferenceSet("ConsoleDebugInfo") );
    ((QCheckBox *) (pref["ConsoleDebugInfo"]))->setDisabled(t);*/
/*
    pref["LogFile"] = new QCheckBox( tr("Logfile for Virtual Machine Info"), g); j->addWidget(pref["LogFile"]);
    ((QCheckBox *) (pref["LogFile"]))->setChecked( my_mainwindow->isPreferenceSet("LogFile") );
    ((QCheckBox *) (pref["LogFile"]))->setDisabled(t);

    pref["PlaySound"] = new QCheckBox( tr("&Music On"), g); j->addWidget(pref["PlaySound"]);
    ((QCheckBox *) (pref["PlaySound"]))->setChecked( my_mainwindow->isPreferenceSet("PlaySound") );
    ((QCheckBox *) (pref["PlaySound"]))->setDisabled(t);*/


    QString kk;
    
    QWidget *d1 = new QWidget(); j->addWidget(d1);
    QHBoxLayout *dl1 = new QHBoxLayout();
    d1->setLayout(dl1);

    
    l = new QLabel(tr("IDE Language . . . . . . . . . . . . . . . . . . . . : "), d1); dl1->addWidget(l);

    pref["Language"] = new QComboBox(d1); dl1->addWidget(pref["Language"]);
    ((QComboBox *) (pref["Language"]))->addItem("English");
    ((QComboBox *) (pref["Language"]))->addItem("German");

    kk = my_mainwindow->getPreference("Language");

    if (kk.length()){
      if (kk == "English") ((QComboBox *) (pref["Language"]))->setCurrentIndex(0);
      if (kk == "German") ((QComboBox *) (pref["Language"]))->setCurrentIndex(1);
    } else {
      ((QComboBox *) (pref["Language"]))->setCurrentIndex(0);
    }        

    QWidget *d2 = new QWidget(); j->addWidget(d2);
    QHBoxLayout *dl2 = new QHBoxLayout();
    d2->setLayout(dl2);


    


    l = new QLabel(tr("Default Project: "), d2); dl2->addWidget(l);
    
    pref["DefaultProject"] = new QLineEdit(d2); dl2->addWidget(pref["DefaultProject"]);
    ((QLineEdit *) (pref["DefaultProject"]))->setDisabled(t);
    ((QLineEdit *) (pref["DefaultProject"]))->setText( my_mainwindow->getPreference("DefaultProject") );

    QPushButton *p;
    p = new QPushButton("...", d2); dl2->addWidget(p);
    p->setMaximumWidth(30);
    p->setDisabled(t);

    connect(p,  SIGNAL( clicked ( ) ), this, SLOT( clicked(  ) ) );


    QWidget *d3 = new QWidget(); j->addWidget(d3);
    QHBoxLayout *dl3 = new QHBoxLayout();
    d3->setLayout(dl3);

    l = new QLabel(tr("Default File......: "), d3); dl3->addWidget(l);
    
    pref["DefaultFile"] = new QLineEdit(d3); dl3->addWidget(pref["DefaultFile"]);
    ((QLineEdit *) (pref["DefaultFile"]))->setDisabled(t);
    ((QLineEdit *) (pref["DefaultFile"]))->setText( my_mainwindow->getPreference("DefaultFile") );
    
    p = new QPushButton("...", d3); dl3->addWidget(p);
    p->setMaximumWidth(30);
    p->setDisabled(t);

    connect(p,  SIGNAL( clicked ( ) ),  this, SLOT( clicked2(  ) ) );



/*
    QWidget *d0 = new QWidget(); j->addWidget(d0);
    QHBoxLayout *dl0 = new QHBoxLayout();
    d0->setLayout(dl0);

    l = new QLabel(tr("Stylesheet . . . . . . . . . . . . . . . . . . . . : "), d0); dl0->addWidget(l);

    pref["Stylesheet"] = new QComboBox(d0); dl0->addWidget(pref["Stylesheet"]);
    ((QComboBox *) (pref["Stylesheet"]))->addItem(tr("Default"));
    ((QComboBox *) (pref["Stylesheet"]))->addItem(tr("BlackWhite"));
    ((QComboBox *) (pref["Stylesheet"]))->addItem(tr("Khaki"));

    kk = my_mainwindow->getPreference("Stylesheet");

    if (kk.length()){
      if (kk == "BlackWhite") ((QComboBox *) (pref["Stylesheet"]))->setCurrentIndex(1);
      else if (kk == "Khaki") ((QComboBox *) (pref["Stylesheet"]))->setCurrentIndex(2);
      else ((QComboBox *) (pref["Stylesheet"]))->setCurrentIndex(0);
    } else {
      ((QComboBox *) (pref["Stylesheet"]))->setCurrentIndex(0);
    }
*/

    QWidget *d4 = new QWidget(); j->addWidget(d4);
    QHBoxLayout *dl4 = new QHBoxLayout();
    d4->setLayout(dl4);

    l = new QLabel(tr("License Key . . . . . . : "), d4); dl4->addWidget(l);
    QFont f = l->font();
    f.setBold(true);
    l->setFont(f);
    
    pref["License"] = new QLineEdit(d4); dl4->addWidget(pref["License"]);
    ((QLineEdit *) (pref["License"]))->setDisabled(t);
    ((QLineEdit *) (pref["License"]))->setText( my_mainwindow->getPreference("License") );
    

    QWidget *d5 = new QWidget(); j->addWidget(d5);
    QHBoxLayout *dl5 = new QHBoxLayout();
    d5->setLayout(dl5);

    l = new QLabel(tr("Cache . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . : "), d5); dl5->addWidget(l);
    
    QPushButton *pp = new QPushButton(tr("Clear"), d5); dl5->addWidget(pp);
    //((QLineEdit *) (pref["License"]))->setDisabled(t);
    //((QLineEdit *) (pref["License"]))->setText( my_mainwindow->getPreference("License") );
    pp->setMaximumWidth(70);    
    connect(pp,  SIGNAL( clicked ( ) ),  this, SLOT( clicked3(  ) ) );


    tab->addTab(a, tr("General"));
}

void _preferences::clicked()
{
     
  QString fn = QFileDialog::getExistingDirectory(this);

  if (!fn.isEmpty()){
    ((QLineEdit *) (pref["DefaultProject"]))->setText(fn + "/");
  }  
}

void _preferences::clicked2()
{
     
  QString fn = QFileDialog::getOpenFileName(this);

  if (!fn.isEmpty()){
    ((QLineEdit *) (pref["DefaultFile"]))->setText(fn + "/");
  }  
}

void _preferences::clicked3()
{     

  QDir thisDir( cachePath("") );	
  QFileInfoList files = thisDir.entryInfoList();

  if ( files.size() ) {

    QFileInfo fi;
    for (int i = 0; i < files.size(); ++i) {
     fi = files.at(i);

		    if (fi.fileName() == "." || fi.fileName() == "..")
		        ; // nothing
		    else if ( fi.isSymLink()) {
          ; // nothing
		    }
        else if ( fi.isDir() ){
          ; // nothing

        } else {

          QString s = fi.absoluteFilePath();

          if (!QFile::remove(s)){
            return;
          }

        }		    
	    }
  
  }    
  QMessageBox::information(this, MYAPP,
    tr("Cached directory for compilation has been cleared."));
    
}

void _preferences::performSave()
{
    save(EXTERN_my_mainwindow);
    close();  
}

void _preferences::performDefault()
{
  my_mainwindow->setDefaultPreferences();
  _preferences c(my_mainwindow, true);
  close();  
}

void _preferences::performClose()
{
  close();  
}  

void _preferences::setupGeneral2()
{

    QWidget *g = new QWidget();
    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    //g->setMinimumSize(300, 300);
    a->setWidgetResizable(true);


    bool t = false;
/*
    pref["SearchBrowserAndHelpTips"] = new QCheckBox( tr("Source Code Br&owser and Help-Tips left side"), g); j->addWidget(pref["SearchBrowserAndHelpTips"]);
    ((QCheckBox *) (pref["SearchBrowserAndHelpTips"]))->setChecked( my_mainwindow->isPreferenceSet("SearchBrowserAndHelpTips") );
    ((QCheckBox *) (pref["SearchBrowserAndHelpTips"]))->setDisabled(t);

    pref["QuickCommands"] = new QCheckBox( tr("&Quick Commands right side"), g); j->addWidget(pref["QuickCommands"]);
    ((QCheckBox *) (pref["QuickCommands"]))->setChecked( my_mainwindow->isPreferenceSet("QuickCommands") );
    ((QCheckBox *) (pref["QuickCommands"]))->setDisabled(t);

    pref["ImportantHelpIndex"] = new QCheckBox( tr("&Important/Help-Index below editor"), g); j->addWidget(pref["ImportantHelpIndex"]);
    ((QCheckBox *) (pref["ImportantHelpIndex"]))->setChecked( my_mainwindow->isPreferenceSet("ImportantHelpIndex") );
    ((QCheckBox *) (pref["ImportantHelpIndex"]))->setDisabled(t);

    pref["ExampleOnQuickCommands"] = new QCheckBox( tr("&Example on Quick Command"), g); j->addWidget(pref["ExampleOnQuickCommands"]);
    ((QCheckBox *) (pref["ExampleOnQuickCommands"]))->setChecked( my_mainwindow->isPreferenceSet("ExampleOnQuickCommands") );
    ((QCheckBox *) (pref["ExampleOnQuickCommands"]))->setDisabled(t);

    pref["MascotTux"] = new QCheckBox( tr("Show Mascot Tu&x"), g); j->addWidget(pref["MascotTux"]);
    ((QCheckBox *) (pref["MascotTux"]))->setChecked( my_mainwindow->isPreferenceSet("MascotTux") );
    ((QCheckBox *) (pref["MascotTux"]))->setDisabled(t);

    pref["MascotKonqui"] = new QCheckBox( tr("Show Mascot &Konqui"), g); j->addWidget(pref["MascotKonqui"]);
    ((QCheckBox *) (pref["MascotKonqui"]))->setChecked( my_mainwindow->isPreferenceSet("MascotKonqui") );
    ((QCheckBox *) (pref["MascotKonqui"]))->setDisabled(t);

    pref["MascotDevil"] = new QCheckBox( tr("Show Mascot &Devil"), g); j->addWidget(pref["MascotDevil"]);
    ((QCheckBox *) (pref["MascotDevil"]))->setChecked( my_mainwindow->isPreferenceSet("MascotDevil") );
    ((QCheckBox *) (pref["MascotDevil"]))->setDisabled(t);

    pref["SourcecodeBrowserImage"] = new QCheckBox( tr("Show Source Code-Browser Picture"), g); j->addWidget(pref["SourcecodeBrowserImage"]);
    ((QCheckBox *) (pref["SourcecodeBrowserImage"]))->setChecked( my_mainwindow->isPreferenceSet("SourcecodeBrowserImage") );
    ((QCheckBox *) (pref["SourcecodeBrowserImage"]))->setDisabled(t);    

    pref["SourcecodeBrowserImage2"] = new QCheckBox( tr("Show Source Code-Browser Picture #2"), g); j->addWidget(pref["SourcecodeBrowserImage2"]);
    ((QCheckBox *) (pref["SourcecodeBrowserImage2"]))->setChecked( my_mainwindow->isPreferenceSet("SourcecodeBrowserImage2") );
    ((QCheckBox *) (pref["SourcecodeBrowserImage2"]))->setDisabled(t);    

    pref["MascotRunner"] = new QCheckBox( tr("Show Mascot R&unner"), g); j->addWidget(pref["MascotRunner"]);
    ((QCheckBox *) (pref["MascotRunner"]))->setChecked( my_mainwindow->isPreferenceSet("MascotRunner") );
    ((QCheckBox *) (pref["MascotRunner"]))->setDisabled(t); 

    pref["ShowIconType"] = new QCheckBox( tr("&Show File Icon Top Right"), g); j->addWidget(pref["ShowIconType"]);
    ((QCheckBox *) (pref["ShowIconType"]))->setChecked( my_mainwindow->isPreferenceSet("ShowIconType") );
    ((QCheckBox *) (pref["ShowIconType"]))->setDisabled(t);

    pref["UnderLineSubsFunctions"] = new QCheckBox( tr("&Underline Subs/Functions"), g); j->addWidget(pref["UnderLineSubsFunctions"]);
    ((QCheckBox *) (pref["UnderLineSubsFunctions"]))->setChecked( my_mainwindow->isPreferenceSet("UnderLineSubsFunctions") );
    ((QCheckBox *) (pref["UnderLineSubsFunctions"]))->setDisabled(t);

    pref["SubFunctionLines"] = new QCheckBox( tr("&Show Sub/Function-Lines"), g); j->addWidget(pref["SubFunctionLines"]);
    ((QCheckBox *) (pref["SubFunctionLines"]))->setChecked( my_mainwindow->isPreferenceSet("SubFunctionLines") );
    ((QCheckBox *) (pref["SubFunctionLines"]))->setDisabled(t);

    pref["HighlightCurrentCursorLine"] = new QCheckBox( tr("&Highlight Current Cursor-Line"), g); j->addWidget(pref["HighlightCurrentCursorLine"]);
    ((QCheckBox *) (pref["HighlightCurrentCursorLine"]))->setChecked( my_mainwindow->isPreferenceSet("HighlightCurrentCursorLine") );
    ((QCheckBox *) (pref["HighlightCurrentCursorLine"]))->setDisabled(t);

    pref["VariableRedOnDblClick"] = new QCheckBox( tr("&Print variable in red on double click"), g); j->addWidget(pref["VariableRedOnDblClick"]);
    ((QCheckBox *) (pref["VariableRedOnDblClick"]))->setChecked( my_mainwindow->isPreferenceSet("VariableRedOnDblClick") );
    ((QCheckBox *) (pref["VariableRedOnDblClick"]))->setDisabled(t);
*/
    pref["SyntaxHighlighting"] = new QCheckBox( tr("Synt&ax Highlighting activated"), g); j->addWidget(pref["SyntaxHighlighting"]);
    ((QCheckBox *) (pref["SyntaxHighlighting"]))->setChecked( my_mainwindow->isPreferenceSet("SyntaxHighlighting") );
    ((QCheckBox *) (pref["SyntaxHighlighting"]))->setDisabled(true);
/*
    pref["RedLineAter$END"] = new QCheckBox( tr("&Draw red line after $End"), g); j->addWidget(pref["RedLineAter$END"]);
    ((QCheckBox *) (pref["RedLineAter$END"]))->setChecked( my_mainwindow->isPreferenceSet("RedLineAter$END") );
    ((QCheckBox *) (pref["RedLineAter$END"]))->setDisabled(t);

    pref["BookmarkPicture"] = new QCheckBox( tr("Show Picture &Right Of Bookmark"), g); j->addWidget(pref["BookmarkPicture"]);
    ((QCheckBox *) (pref["BookmarkPicture"]))->setChecked( my_mainwindow->isPreferenceSet("BookmarkPicture") );
    ((QCheckBox *) (pref["BookmarkPicture"]))->setDisabled(t);

    pref["BreakpointPicture"] = new QCheckBox( tr("Show &Picture Right Of Breakpoint"), g); j->addWidget(pref["BreakpointPicture"]);
    ((QCheckBox *) (pref["BreakpointPicture"]))->setChecked( my_mainwindow->isPreferenceSet("BreakpointPicture") );
    ((QCheckBox *) (pref["BreakpointPicture"]))->setDisabled(t);

    pref["FlashDebuggingMessage"] = new QCheckBox( tr("&Flash Debugging Message"), g); j->addWidget(pref["FlashDebuggingMessage"]);
    ((QCheckBox *) (pref["FlashDebuggingMessage"]))->setChecked( my_mainwindow->isPreferenceSet("FlashDebuggingMessage") );
    ((QCheckBox *) (pref["FlashDebuggingMessage"]))->setDisabled(t);

    pref["BackImageOnNewFile"] = new QCheckBox( tr("Show &Background Picture On New File"), g); j->addWidget(pref["BackImageOnNewFile"]);
    ((QCheckBox *) (pref["BackImageOnNewFile"]))->setChecked( my_mainwindow->isPreferenceSet("BackImageOnNewFile") );
    ((QCheckBox *) (pref["BackImageOnNewFile"]))->setDisabled(t);*/

    pref["AutoInsert"] = new QCheckBox( tr("&Auto-Insert activated"), g); j->addWidget(pref["AutoInsert"]);
    ((QCheckBox *) (pref["AutoInsert"]))->setChecked(true);//my_mainwindow->isPreferenceSet("AutoInsert") );
    ((QCheckBox *) (pref["AutoInsert"]))->setDisabled(true);

    pref["AutoCompletion"] = new QCheckBox( tr("Auto-&Completion activated"), g); j->addWidget(pref["AutoCompletion"]);
    ((QCheckBox *) (pref["AutoCompletion"]))->setChecked(true);// my_mainwindow->isPreferenceSet("AutoCompletion") );
    ((QCheckBox *) (pref["AutoCompletion"]))->setDisabled(true);

    pref["AutoCorrection"] = new QCheckBox( tr("Auto-Co&rrection activate&d"), g); j->addWidget(pref["AutoCorrection"]);
    ((QCheckBox *) (pref["AutoCorrection"]))->setChecked(true);// my_mainwindow->isPreferenceSet("AutoCorrection") );
    ((QCheckBox *) (pref["AutoCorrection"]))->setDisabled(true);

    // hidden
    pref["EDIT_TOOLBARS_FILE"] = new QCheckBox( "EDIT_TOOLBARS_FILE", g); j->addWidget(pref["EDIT_TOOLBARS_FILE"]);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_FILE"]))->setChecked( my_mainwindow->isPreferenceSet("EDIT_TOOLBARS_FILE") );
    ((QCheckBox *) (pref["EDIT_TOOLBARS_FILE"]))->setDisabled(t);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_FILE"]))->setHidden(true);

    pref["EDIT_TOOLBARS_RUN"] = new QCheckBox( "EDIT_TOOLBARS_RUN", g); j->addWidget(pref["EDIT_TOOLBARS_RUN"]);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_RUN"]))->setChecked( my_mainwindow->isPreferenceSet("EDIT_TOOLBARS_RUN") );
    ((QCheckBox *) (pref["EDIT_TOOLBARS_RUN"]))->setDisabled(t);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_RUN"]))->setHidden(true);

    pref["EDIT_TOOLBARS_EDIT"] = new QCheckBox( "EDIT_TOOLBARS_EDIT", g); j->addWidget(pref["EDIT_TOOLBARS_EDIT"]);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_EDIT"]))->setChecked( my_mainwindow->isPreferenceSet("EDIT_TOOLBARS_EDIT") );
    ((QCheckBox *) (pref["EDIT_TOOLBARS_EDIT"]))->setDisabled(t);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_EDIT"]))->setHidden(true);

    pref["EDIT_TOOLBARS_FORMAT"] = new QCheckBox( "EDIT_TOOLBARS_FORMAT", g); j->addWidget(pref["EDIT_TOOLBARS_FORMAT"]);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_FORMAT"]))->setChecked( my_mainwindow->isPreferenceSet("EDIT_TOOLBARS_FORMAT") );
    ((QCheckBox *) (pref["EDIT_TOOLBARS_FORMAT"]))->setDisabled(t);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_FORMAT"]))->setHidden(true);

    pref["EDIT_TOOLBARS_INSERT"] = new QCheckBox( "EDIT_TOOLBARS_INSERT", g); j->addWidget(pref["EDIT_TOOLBARS_INSERT"]);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_INSERT"]))->setChecked( my_mainwindow->isPreferenceSet("EDIT_TOOLBARS_INSERT") );
    ((QCheckBox *) (pref["EDIT_TOOLBARS_INSERT"]))->setDisabled(t);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_INSERT"]))->setHidden(true);

    pref["EDIT_TOOLBARS_HELP"] = new QCheckBox( "EDIT_TOOLBARS_HELP", g); j->addWidget(pref["EDIT_TOOLBARS_HELP"]);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_HELP"]))->setChecked( my_mainwindow->isPreferenceSet("EDIT_TOOLBARS_HELP") );
    ((QCheckBox *) (pref["EDIT_TOOLBARS_HELP"]))->setDisabled(t);
    ((QCheckBox *) (pref["EDIT_TOOLBARS_HELP"]))->setHidden(true);

    tab->addTab(a, tr("Editing"));
  
}

void _preferences::setupSave()
{
    QWidget *g = new QWidget();
    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    //g->setMinimumSize(300, 300);
    a->setWidgetResizable(true);

    bool t = false;

    QCheckBox *c;
    /*
    c = new QCheckBox(tr("&Save every 10 minutes automatically"), g); j->addWidget(c);
    c->setChecked(false);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Create always backup file when saving"), g); j->addWidget(c);
    c->setChecked(false);
    c->setDisabled(true);*/

    c = new QCheckBox(tr("&Save as ASCII file"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Carriage Return is UNIX-like"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    tab->addTab(a, tr("Saving"));
}

void _preferences::setupSourceCodeEditor()
{
    QWidget *g = new QWidget();
    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    //g->setMinimumSize(300, 300);
    a->setWidgetResizable(true);


    bool t = false;
    

    QLabel *l;
    l = new QLabel(tr("Font:"), g); j->addWidget(l);

    QComboBox *font;
    pref["FontName"] = font = new QComboBox(g); j->addWidget(font);

    font->addItem("Arial");
    
    QFontDatabase fdb;
    QStringList families = fdb.families();
    for (QStringList::Iterator f = families.begin(); f != families.end(); ++f){
      QString family = *f;
      font->addItem(family);
    }

    connect(font, SIGNAL(highlighted(int)), this, SLOT(selected(int)));
    connect(font, SIGNAL(activated(int)), this, SLOT(selected(int)));



    { // set item

      QString x = my_mainwindow->getPreference("FontName");
      int i = 0;

      do {
       QString z = font->itemText(i);
       if (z == 0) break;
       if (z == x){ 
         font->setCurrentIndex(i);
         break;
       }

       i++;
      } while (true);
    }


    l = new QLabel(tr("Size:"), g); j->addWidget(l);
    
    QComboBox *size;
    pref["FontSize"] = size = new QComboBox(g); j->addWidget(size);
    size->setEditable(true);
    size->setMaximumWidth(100);

    size->addItem("6");
    size->addItem("7");
    size->addItem("8");
    size->addItem("9");
    size->addItem("10");
    size->addItem("11");
    size->addItem("12");
    size->addItem("13");
    size->addItem("14");
    size->addItem("15");
    size->addItem("16");
    size->addItem("17");
    size->addItem("18");
    size->addItem("19");
    size->addItem("20");
    size->addItem("21");
    size->addItem("22");
    size->addItem("23");
    size->addItem("24");


    connect(size, SIGNAL( highlighted (int)), this, SLOT(selected(int)));
    connect(size, SIGNAL(activated(int)), this, SLOT(selected(int)));

    { // set item

      QString x = my_mainwindow->getPreference("FontSize");
      if (x.length() == 0) x = "8";
      int i = 0;

      do {
       QString z = size->itemText(i);       
       if (z == x){ 
         size->setCurrentIndex(i);
         break;
       }
       if (z == "24") break;

       i++;
      } while (true);
    }
    

    list = new QListWidget ( g ); j->addWidget(list);
    list->setEnabled(false);

    list->addItem("Automatic");
    list->addItem("Standard");
    list->addItem("Keyword");
    list->addItem("Type");
    list->addItem("Comment");

    connect(list, SIGNAL(currentRowChanged (int)), this, SLOT(selected(int)));
   


    l = new QLabel(tr("Color:"), g); j->addWidget(l);

    
    fore = new QComboBox(g); j->addWidget(fore);
    fore->setEnabled(false);
    
    fore->addItem ("Automatic");
    fore->addItem ("Black");
    fore->addItem ("White");
    fore->addItem ("Dark Red");
    fore->addItem ("Dark Green");
    fore->addItem ("Olive");
    fore->addItem ("Dark Blue");
    fore->addItem ("Violet");
    fore->addItem ("Aqua Marine");
    fore->addItem ("Grey");
    fore->addItem ("Dark Grey");
    fore->addItem ("Red");
    fore->addItem ("Green");
    fore->addItem ("Yellow");
    fore->addItem ("Blue");
    fore->addItem ("Magenta");
    fore->addItem ("Cyan");

    connect(fore, SIGNAL( highlighted (int)), this, SLOT(selected(int)));

    
    
    l = new QLabel(tr("Background color:"), g); j->addWidget(l);

    
    back = new QComboBox(g); j->addWidget(back);
    back->setEnabled(false);
    back->addItem ("Automatic");
   

    connect(back, SIGNAL( highlighted (int)), this, SLOT(selected(int)));


    

    
    bold = new QCheckBox(tr("Bold"), g); j->addWidget(bold );
    bold->setDisabled(true);

    connect(bold, SIGNAL(clicked()), this, SLOT(updateExample()));

    
    l = new QLabel(tr("Example:"), g); j->addWidget(l);

    
    example = new QLabel("AaBbCcXxYyZz", g); j->addWidget(example);


    list->setCurrentRow(0);

    updateExample();

    tab->addTab(a, tr("Syntax Highlighting"));
    
}

void _preferences::updateExample ( )
{

  QString k = list->item(list->currentRow())->text();

  k = k.trimmed();

  QFont f;
  f.setBold(bold->isChecked());

  QComboBox *bb = ((QComboBox *) (pref["FontName"]));
  f.setFamily(bb->itemText(bb->currentIndex()));

  bb = ((QComboBox *) (pref["FontSize"]));
  f.setPointSize(bb->itemText(bb->currentIndex()).toInt());
  example->setFont(f);
  /*
  QPalette qPalette;
  qPalette.setColor( QPalette::Foreground,QColor(getColor(fore->currentText())) );
  example->setPalette( qPalette );

  QString m = fore->currentText();
  m.append("|");
  m.append(back->currentText());
  m.append("|");
  m.append(bold->isChecked() ? "bold" : "normal");

  pref2[k] = m;*/

}

int _preferences::getColor(QString s)
{
  s = s.trimmed();

  if (s == "Automatic"){    
    return 0;
  } else if (s == "Black"){
    return 0;
  } else if (s == "White"){
    return 0xffffff;
  } else if (s == "Dark Red"){
    return 0xcd0000;
  } else if (s == "Dark Green"){
    return 0x008000;
  } else if (s == "Olive"){
    return 0x808000;
  } else if (s == "Dark Blue"){
    return 0x000080;
  } else if (s == "Violet"){
    return 0x800080;
  } else if (s == "Aqua Marine"){
    return 0x008181;
  } else if (s == "Grey"){
    return 0xC0C0C0;
  } else if (s == "Dark Grey"){
    return 0x808080;
  } else if (s == "Red"){
    return 0xff0000;
  } else if (s == "Green"){
    return 0x00ff00;
  } else if (s == "Yellow"){
    return 0xffff00;
  } else if (s == "Blue"){
    return 0x0000ff;
  } else if (s == "Magenta"){
    return 0xff00ff;
  } else if (s == "Cyan"){
    return 0x00ffff;
  }

  return 0;
}

void _preferences::selected ( int index )
{
  
  updateExample();
  
}

void _preferences::setupCompatibility()
{

    QWidget *g = new QWidget();
    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    
    a->setWidgetResizable(true);

    bool t = false;



    QCheckBox *c;
    c = new QCheckBox(tr("&Allow Array access with ( ) and not only [ ]"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Option OldBasic' and 'Option VeryOldBasic'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'On Error GoTo' and not only 'Try Catch'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Nothing' and not only 'Null'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Class_Initialisize' and not only 'Constructor'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Call' for calling subs and functions"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Optional'and 'IsMissing' and not only default value"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Data' and 'Def*', like DefInt"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'GoSub'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'GoTo'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow Ending As Implicit Typing: $,%,!..."), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    tab->addTab(a, tr("BASIC Compatibility"));
}

void _preferences::setupScanner()
{

    QWidget *g = new QWidget();
    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    
    a->setWidgetResizable(true);

    QCheckBox *c;
    c = new QCheckBox(tr("&Overflow Check For Literals"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Stop Scanning On Error"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);
/*
    c = new QCheckBox(tr("&Code Page: ASCII"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);
*/
    tab->addTab(a, tr("Scanner"));
    
}


void _preferences::setupParser()
{
  
    QWidget *g = new QWidget();
    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    //g->setMinimumSize(300, 300);
    a->setWidgetResizable(true);


    QCheckBox *c;
/*
    c = new QCheckBox(tr("&Identifiers are Case-Sensitive"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);
*/
    c = new QCheckBox(tr("&Stop Parsing On Error"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Option OldBasic'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Option VeryOldBasic'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow Operator Overloading"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'On Error Goto'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow '(' and ')' For Accessing Array"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Call' For Function-Calling"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'Optional' And 'IsMissing'"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);
/*
    c = new QCheckBox(tr("&Allow Keyword As Identifier"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);*/
/*
    c = new QCheckBox(tr("&Ignore All Builtin"), g); j->addWidget(c);
    c->setChecked(false);
    c->setDisabled(true);
*/
    c = new QCheckBox(tr("&Show Semantic-Error As Syntax-Error"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow Ending As Implicit Typing: $,%,&,#,!, @"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow 'DEFINT', 'DEFLNG', 'DEFSTR'..."), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);
   

    QListWidget *list = new QListWidget ( g ); j->addWidget(list);

list->addItem("Variable");
list->addItem("Declaration | Dim | Public | Private | Protected | Static | As | Assignment | User Defined Type | Type ");
list->addItem("Comment ");
list->addItem("REM | ' | /* | */ | /** ");
list->addItem("Literal ");
list->addItem("Byte, Short, Integer, Long, Int16, Int32, Int64, UInt16, UInt32, UInt64 | Hex | Binary | Octal | Single (Decimal) | Double (Decimal) | Currency | Date, Time | String | Boolean ");
list->addItem("Constant ");
list->addItem("Const | As ");
list->addItem("Array ");
list->addItem("Dim | Access Array | Lower And Upper Bound Of Array | UBound | LBound | Dim With Explicit Lower Bound | Multi-Dimension | Dynamic Array | Redim | Delete Array | Reset Array | Erase ");
list->addItem("Flow Control - Decision ");
list->addItem("Single Decision | If | Then | Else | End If | IIf  Short If | Multi Decision | Select Case | Case | End Select | Switch  Short Select Case | Choose  Short Select Case | Uncoditional Jump | GoTo | With ");
list->addItem("Flow Control - Loop ");
list->addItem("For Next | To | Step | Do While ... Loop | Do ... Loop Until | Do ... Loop While | Do Until ... Loop | While ... Wend | While ... End While | Explicit Leave Of Loop | Explicit Test of Loop Condition ");
list->addItem("Subs / Procedures ");
list->addItem("Sub-Procedure | Sub | End Sub | Function-Procedure | Function | End Function | Argument | Named Argument | Optional Argument | Paramarray | Call Of Sub or Function | Explicit Leave Of Procedures ");
list->addItem("Function ");
list->addItem("Function | End Function | Return Function Value | Return ");
list->addItem("Property ");
list->addItem("Access Property | Property | Property Set | Property Get | Set | End Set | Get | End Get | End Property ");
list->addItem("User defined Type ");
list->addItem("Access Type | Type | End Type ");
list->addItem("Enumeration ");
list->addItem("Access Enum | Enum | End Enum ");
list->addItem("Class ");
list->addItem("Class | Abstract | Inherits | Constructor | Destructor | Sub | Function | Signal | Slot | End Class ");
list->addItem("Module ");
list->addItem("Create Module | Access Module Variable | Access Module Sub Or Function | Module Sub Or Function | Call Module Sub Or Function | Access Module Type | Access Module Enum | Module | End Module ");
list->addItem("Error Handling ");
list->addItem("New Exception | Throw | Exception | Try | Catch | End Catch | Exception In Procedure (Sub Or Function) ");

tab->addTab(a, tr("Parser"));

}



void _preferences::setupInterpreter()
{
    QWidget *g = new QWidget();
    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    //g->setMinimumSize(300, 300);
    a->setWidgetResizable(true);


    QCheckBox *c;

    c = new QCheckBox(tr("&Show PCode-Error As Runtime-Error"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Stop Interpreting On Critical Error"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Activate Full Runtime-Checking"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);



    QListWidget *list = new QListWidget ( g ); j->addWidget(list);

list->addItem("Null-Pointer Exception");
list->addItem("Divide By Zero Exception");
list->addItem("Cast Exception");
list->addItem("Method-Not-Found Exception");
list->addItem("Unknown Exception");
    
    tab->addTab(a, tr("Interpreter"));
}

void _preferences::setupCompiler()
{
    QWidget *g = new QWidget();
    QVBoxLayout *j = new QVBoxLayout();
    g->setLayout(j);
    QScrollArea *a = new QScrollArea(this);
    a->setFrameShape(QFrame::NoFrame);
    a->setWidget(g);
    a->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    a->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded); 
    
    a->setWidgetResizable(true);

    QCheckBox *c;

    c = new QCheckBox(tr("&Generate PCode For Virtual Machine"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);
   
    c = new QCheckBox(tr("&Stop Compiling On Error"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);
   /*
    c = new QCheckBox(tr("&Enable Debug-Information"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);*/

    c = new QCheckBox(tr("&Activate String-Pooling"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Allow Exception"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);

    c = new QCheckBox(tr("&Speed Optimize PCode (fastest)"), g); j->addWidget(c);
    c->setChecked(true);
    c->setDisabled(true);
  
    tab->addTab(a, tr("Compiler"));
}

void _preferences::load(_mainwindow *parent)
{
  _mainwindow *my_mainwindow = (_mainwindow *) parent;

  QString m =  kbasicPath("ide/kbasic.config");
  QString s = "";

  QFile f(m);
  if (!f.open(QIODevice::ReadOnly)){
    QMessageBox::information(0, MYAPP, QString("Could not read from %1").arg(m));
    return;
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    s = t.readAll();
    s = s.replace("\r", "");
    f.close();
  }

  QStringList l = s.split("\n");

  for (QStringList::Iterator it = l.begin(); it != l.end(); ++it ) {
    QString k = *it;

    k = k.trimmed();

    QString sKey = "";
    QString sValue = "";

    sKey = k.left(k.indexOf("="));
    sKey = sKey.trimmed();
    sValue = k.mid(k.indexOf("=") + 1);
    sValue = sValue.trimmed();

    my_mainwindow->preferences[sKey.toUpper()] = sValue;

  }
    
}

void _preferences::save(_mainwindow *parent)
{
  _mainwindow * my_mainwindow = (_mainwindow *) parent;

  QString m =  kbasicPath("ide/kbasic.config");
  QString s = "";

/*
  if (QFile::exists(m)){
    QMessageBox::information(0, "exists=true", m);
  } else {
    QMessageBox::information(0, "exists=false", m);
  }

  QFile::Permissions p = QFile::permissions(m);

  QString x = "";
  if (p & QFile::ReadOwner) x += "QFile::ReadOwner\n";
  if (p & QFile::WriteOwner) x += "QFile::WriteOwner\n";
  if (p & QFile::ExeOwner) x += "QFile::ExeOwner\n";
  if (p & QFile::ReadUser) x += "QFile::ReadUser\n";
  if (p & QFile::WriteUser) x += "QFile::WriteUser\n";
  if (p & QFile::ExeUser) x += "QFile::ExeUser\n";
  if (p & QFile::ReadGroup) x += "QFile::ReadGroup\n";
  if (p & QFile::WriteGroup) x += "QFile::WriteGroup\n";
  if (p & QFile::ExeGroup) x += "QFile::ExeGrou\np";
  if (p & QFile::ReadOther) x += "QFile::ReadOther\n";
  if (p & QFile::WriteOther) x += "QFile::WriteOther\n";
  if (p & QFile::ExeOther) x += "QFile::ExeOther";

  QMessageBox::information(0, "Permissions", x);*/

  QMap<QString, QWidget*>::Iterator it;
  for ( it = pref.begin(); it != pref.end(); ++it ) {
    QString sKey = it.key();
    QString sValue = ""; /// it.data();

    QWidget *w = *it;


    if (qobject_cast<QCheckBox *>(w)){
      sValue = ((QCheckBox *) w)->isChecked() ? "Yes" : "No";
    } else if (qobject_cast<QLineEdit *>(w)){
      sValue = ((QLineEdit *) w)->text();
    } else if (qobject_cast<QComboBox *>(w)){
      
      if (w == pref["Language"]){
        sValue = ((QComboBox *) w)->currentText();

        //if (sValue == "Englisch") sValue == "English";
        //else if (sValue == "Deutsch") sValue == "German";

      } else {
        sValue = ((QComboBox *) w)->currentText();
      }
    }

    my_mainwindow->preferences[sKey.toUpper()] = sValue;
    s = s + sKey + " = " + sValue + "\n";
  }

  QMap<QString, QString>::Iterator it2;
  for ( it2 = pref2.begin(); it2 != pref2.end(); ++it2 ) {
    QString sKey = it2.key();
    QString sValue = *it2;

    my_mainwindow->preferences[sKey.toUpper()] = sValue;
    s = s + sKey + " = " + sValue + "\n";
  }

  QFile f(m);
  if (!f.open(QIODevice::WriteOnly)){
    QMessageBox::information(this, MYAPP, QString("Could not write to %1").arg(m));
  } else {
    QTextStream t(&f);
    
    t.setCodec("UTF-8");
    t.setAutoDetectUnicode(true);
    t.setGenerateByteOrderMark(true);

    t << s;
    f.close();
  }

  if (!bSaveOnly){
    QMessageBox::information(this, tr("Preferences"),
          tr(""
    "Some changes will affect after restarting KBasic only.<br>"
    ));
  }

}

