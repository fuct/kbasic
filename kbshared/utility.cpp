/*
***************************************************************************
Copyright (C) 2000-2008 KBasic Software: www.kbasic.com. All rights reserved.
Source codes are copyrighted by Bernd Noetscher 2000-2008.

You may use this source codes under the terms of the GNU Public License (Version 3)
as published by the Free Software Foundation. 

If you are interested in using the source codes for other licenses or 
commercial development, you must buy commercial licenses from KBasic Software.

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
***************************************************************************
*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "utility.h"

char acText[1024 * 100];


textbuffer::textbuffer()
{
	acMem = 0;   
	nMem = 0;    // start length at some value

}

textbuffer::~textbuffer()
{
	if (acMem != 0){
		free(acMem);
		acMem = 0;
	}
}
