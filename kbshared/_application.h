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

#ifndef _APPLICATION_H
#define _APPLICATION_H




class _strings;
class _form;
class _control;

#include "typedef.h"

#ifdef RUN

#ifdef WINDOWS
#include "../kbrun/QtDotNetStyle.h" // HIDE
#endif


#include <QFontDatabase>
#include <QMotifStyle>
#include <QCDEStyle>
#include <QCleanlooksStyle>
#ifdef MAC
#include <QMacStyle> // HIDE
#endif
#if QT_VERSION >= 0x040500
#include <QGtkStyle>
#endif
#include <QPlastiqueStyle>
#include <QWindowsStyle>
#include <QWindowsXPStyle>
#include <QWindowsVistaStyle>

#include <QApplication>
#include <QMainWindow>
#include <QString>
#include <QMessageBox>
#include <QString>
#include <QTranslator>
#include <QMap>
#include <QClipboard>
#include <QDesktopWidget>
#include <QSound>
#include <QDesktopServices>
#include <QUrl>
#include <QIcon>
#include <QMdiArea>



extern QMainWindow *forms_mainwindow;

extern QMdiArea *forms_workspace;

extern const QPixmap &interpreter_loadPixmap(QString fn);

extern QMap<QString, QTranslator*> tr_map;

extern QString sQtException;

#endif



class _application
{
#ifdef RUN
public:

/*
static void EVENT_Application_OnOpen();


static void EVENT_Application_OnClose2(bool *Cancel); 
static void EVENT_Application_OnClose(bool *Cancel); 
*/
static void METHOD_SetWaitCursor();
static void METHOD_UnsetWaitCursor();

static QString METHOD_ArgumentsAsString();

static _strings *METHOD_Arguments();



static void EVENT_Forms_OnFormGotFocus(QString FormName); 
static void EVENT_Actions_OnAction(QString ActionId); 
static void EVENT_MenuBar_OnEvent(QString MenuBarItemName); 
static void EVENT_MenuBar_OnHovered(QString MenuBarItemName); 
static void EVENT_MenuBar_OnAboutToShow(QString MenuBarItemName); 
static void EVENT_MenuBar_OnAboutToHide(QString MenuBarItemName); 
static void EVENT_ToolBar_OnEvent(QString MenuBarItemName); 


 
static void METHOD_ClearQtException()
{
  sQtException = "";
}
 
static QString METHOD_QtException()
{
  return sQtException;
}

static void SETPROPERTY_X(int X)
{
  forms_mainwindow->move(X, forms_mainwindow->y());
}

static int GETPROPERTY_X()
{
  return forms_mainwindow->x();
}

static void SETPROPERTY_Y(int Y)
{
  forms_mainwindow->move(forms_mainwindow->x(), Y);
}

static int GETPROPERTY_Y()
{
  return forms_mainwindow->y();
}

static void SETPROPERTY_Width(int Width)
{
  forms_mainwindow->resize(Width, forms_mainwindow->height());
}

static int GETPROPERTY_Width()
{
  return forms_mainwindow->width();
}

static void SETPROPERTY_Height(int Height)
{
  forms_mainwindow->resize(forms_mainwindow->width(), Height);
}

static int GETPROPERTY_Height()
{
  return forms_mainwindow->height();
}

static void METHOD_ShowFullScreen()
{
  forms_mainwindow->showFullScreen();
}

static void METHOD_ShowMaximized()
{
  forms_mainwindow->showMaximized();
}

static void METHOD_ShowMinimized()
{
  forms_mainwindow->showMinimized();
}

static void METHOD_ShowNormal()
{
  forms_mainwindow->showNormal();
}

static QString METHOD_StandardIcon(QString Name);

static void METHOD_PrintHtml(QString Html);
static void METHOD_PrintHtmlAsPdf(QString Html, QString FileName);


static QString METHOD_TakeScreenShot();

static void METHOD_PlaySound(QString FileName);
static void METHOD_PlayMovie(QString FileName, t_boolean KeyAndMouseCanCancel);

static void METHOD_MsgBox(QString Title, QString Caption)
{
  QMessageBox::information(forms_mainwindow, Title, Caption);
}

static _strings *METHOD_AvailableFontNames()
{
  QFontDatabase database;
  static QStringList l; l = database.families();
  return (_strings *) &l;
}

static t_long METHOD_ProcessId()
{
  return qApp->applicationPid();
}

static void METHOD_SetViewMode(QString n)
{
  if (forms_workspace == 0) return;

  int i = 0;

  if (n.contains("SubWindowView")) i |= QMdiArea::SubWindowView;
  else if (n.contains("TabbedView")) i |= QMdiArea::TabbedView;

  forms_workspace->setViewMode((QMdiArea::ViewMode) i);
}

static QString METHOD_ViewMode()
{
  if (forms_workspace == 0) return "";

  QMdiArea::ViewMode i = forms_workspace->viewMode();
  if (i == QMdiArea::SubWindowView) return "SubWindowView";
  else if (i == QMdiArea::TabbedView) return "TabbedView";

  return "";
}

static void METHOD_SetCaption(QString Text)
{
  if (forms_mainwindow) forms_mainwindow->setWindowTitle(Text);
}

static void METHOD_SetIcon(QString Text);


static void METHOD_SetClipboardText(QString Text)
{
  static QString sBuffer;
  sBuffer = Text;
  QClipboard * p = qApp->clipboard();
  p->setText(sBuffer);
}

static QString METHOD_ClipboardText()
{
  QClipboard * p = qApp->clipboard();
  return p->text();

}

static QString METHOD_DirectoryName()
{
  return qApp->applicationDirPath();
}

static QString METHOD_FileName()
{
  return qApp->applicationFilePath();
}


static void METHOD_Run();

static void METHOD_Stop();

static void METHOD_AddLanguageTranslatorFile(QString k);

static void METHOD_DoEvents()
{
  qApp->processEvents();
}


static void METHOD_SetStyleSheet(QString k);

static void METHOD_SetLayoutDirection(t_boolean k)
{
  qApp->setLayoutDirection(k ? Qt::RightToLeft : Qt::LeftToRight);
}

static t_integer METHOD_ScreenWidth()
{
  QDesktopWidget *w = qApp->desktop();
  return w->width();
}

static t_integer METHOD_ScreenHeight()
{
  QDesktopWidget *w = qApp->desktop();
  return w->height();
}


static void METHOD_LoadExternalBrowserWithHTML(QString k)
{
  QDesktopServices::openUrl(QUrl(k));
}


static void METHOD_SetSQLDriver(QString k)
{
}

static void METHOD_SetSQLHost(QString k)
{
}

static void METHOD_SetSQLDatabase(QString k)
{
}

static void METHOD_SetSQLUser(QString k)
{
}

static void METHOD_SetSQLPassword(QString k)
{
}



static t_boolean METHOD_IsScrollBarsEnabled();



static void METHOD_SetScrollBarsEnabled(t_boolean k);
static void METHOD_SetFocusNextForm();
static void METHOD_SetFocusPreviousForm();
static void METHOD_Cascade();
static void METHOD_CloseActiveForm();
static void METHOD_CloseAll();
static void METHOD_Tile();



static QString METHOD_LoadProjectFileAsString(QString k);
static QString METHOD_LoadProjectFileAsBinary(QString k);

static QString METHOD_LoadFileAsString(QString k);
static QString METHOD_LoadURLAsBinary(QString k);

static t_boolean METHOD_IsMimeTypeAvailable(QString k);
static _strings *METHOD_AvailableMimeTypes();

static _strings *METHOD_AvailableLanguages();
static void METHOD_SetLanguage(QString k);
static void METHOD_SetCountry(QString k);


static void METHOD_Move(int X, int Y)
{
  forms_mainwindow->move(X, Y);
}

static void METHOD_Resize(int Width, int Height)
{
  forms_mainwindow->resize(Width, Height);
}

static void METHOD_Close()
{
  forms_mainwindow->close();
}

static QString METHOD_QtVersion()
{
  return QString(qVersion());
}

static QString METHOD_OperatingSystemName()
{
#ifdef WINDOWS
  if (QSysInfo::WindowsVersion == QSysInfo::WV_32s) return "Windows 3.1 wth Win 32s"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_95) return "Windows 95"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_98) return "Windows 98"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_Me) return "Windows Me"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_NT) return "Windows NT"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_2000) return "Windows 2000"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_XP) return "Windows XP"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_2003) return "Windows Server 2003"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_VISTA) return "Windows Vista"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_CE) return "Windows CE"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_CENET) return "Windows CE .NET"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_DOS_based) return "MS-DOS-based version of Windows"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_NT_based) return "NT-based version of Windows"; // HIDE
  if (QSysInfo::WindowsVersion == QSysInfo::WV_CE_based) return "CE-based version of Windows"; // HIDE
  return "Unknown"; // HIDE
#else 
#ifdef MAC
  if (QSysInfo::MacintoshVersion == QSysInfo::MV_9) return "Mac OS 9 (unsupported)"; // HIDE
  if (QSysInfo::MacintoshVersion == QSysInfo::MV_10_0) return "Mac OS X 10.0 (unsupported)"; // HIDE
  if (QSysInfo::MacintoshVersion == QSysInfo::MV_10_1) return "Mac OS X 10.1 (unsupported)"; // HIDE
  if (QSysInfo::MacintoshVersion == QSysInfo::MV_10_2) return "Mac OS X 10.2 (unsupported)"; // HIDE
  if (QSysInfo::MacintoshVersion == QSysInfo::MV_10_3) return "Mac OS X 10.3"; // HIDE
  if (QSysInfo::MacintoshVersion == QSysInfo::MV_10_4) return "Mac OS X 10.4"; // HIDE
  if (QSysInfo::MacintoshVersion == QSysInfo::MV_10_5) return "Mac OS X 10.5"; // HIDE
  return "Unknown"; // HIDE
#endif
#endif
  return "Linux";
}

static void METHOD_SetDefaultIcon(QString k);


static void METHOD_ExternalOpenFile(QString k);

static void METHOD_CloseAllWindows()
{
  qApp->closeAllWindows();
}

static t_boolean METHOD_IsLayoutDirection()
{
  return qApp->isRightToLeft();
}

static _form *METHOD_CurrentForm();


static _control *METHOD_FocusControl()
{
  return (_control *) qApp->focusWidget();
}

static void METHOD_SetStyle(QString k)
{
  if (k.contains("Motif", Qt::CaseInsensitive)) QApplication::setStyle(new QMotifStyle);
  else if (k.contains("CDE", Qt::CaseInsensitive)) QApplication::setStyle(new QCDEStyle);  
  else if (k.contains("Plastique", Qt::CaseInsensitive)) QApplication::setStyle(new QPlastiqueStyle);
  //else if (k.contains("GTK", Qt::CaseInsensitive)) QApplication::setStyle(new QGtkStyle);   
#ifdef MAC
  else if (k.contains("Mac", Qt::CaseInsensitive)) QApplication::setStyle(new QMacStyle); // HIDE
#endif
  else if (k.contains("Cleanlooks", Qt::CaseInsensitive)) QApplication::setStyle(new QCleanlooksStyle);
#ifdef WINDOWS
  else if (k.contains("WindowsXP", Qt::CaseInsensitive)) QApplication::setStyle(new QWindowsXPStyle); // HIDE
  else if (k.contains("WindowsVista", Qt::CaseInsensitive)) QApplication::setStyle(new QWindowsVistaStyle); // HIDE
  else if (k.contains("DotNetStandard", Qt::CaseInsensitive)) QApplication::setStyle(new QtDotNetStyle(QtDotNetStyle::Standard)); // HIDE
  else if (k.contains("DotNetOffice", Qt::CaseInsensitive)) QApplication::setStyle(new QtDotNetStyle(QtDotNetStyle::Office)); // HIDE
#endif
  // must be the last
  else if (k.contains("Windows", Qt::CaseInsensitive)) QApplication::setStyle(new QWindowsStyle);
}




private:


#endif
};


#endif