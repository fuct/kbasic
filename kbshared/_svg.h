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




#ifndef _SVG_H
#define _SVG_H


#include <QSvgWidget>

#include "typedef.h"



#include "_property.h"
#include "_control0.h"

#define TEST _svg    
#define TEST2 _svgs   
#define TEST3 "SvgBox"
#define SUPERCLASS QSvgWidget   

#define _SVG true

class _form;

class _svg : public QSvgWidget, public _property
{
  Q_OBJECT
public:


_svg(_form *f = 0, QWidget *parent = 0) : QSvgWidget (parent ? parent : (QWidget *) f)
{
  constructor(f, parent);


  bool bForm = my_form_isForm(my_form);

  // properties
  addProperty("StringValue", pt_qstring); addProperty("OldStringValue", pt_qstring);

  // events

  // default values
  SETPROPERTY_ControlType("SvgBox");
  SETPROPERTY_Visible(true);

#ifdef IDE
  SETPROPERTY_StringValue(kbasicPath("ide/runner.svg"));
#endif
}

#include "__property_x.h"
#include "__property_y.h"
#include "__property_stringvalue.h"

// *** bindings


void EVENT_OnSQLEvent();

// *** 
#include "_control1_binding.h"


// *** 
#include "_control1.h"


};

#include "_control2.h"

#undef _SVG

#undef TEST
#undef TEST2
#undef TEST3
#undef SUPERCLASS




  
#endif