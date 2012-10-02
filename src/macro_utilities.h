/***************************************************************************
 *   Copyright (C) 2008-2012 by Andrzej Rybczak                            *
 *   electricityispower@gmail.com                                          *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.              *
 ***************************************************************************/

#ifndef NCMPCPP_MACRO_UTILITIES_H
#define NCMPCPP_MACRO_UTILITIES_H

#include <cassert>
#include "actions.h"
#include "screen_type.h"

struct PushCharacters : public Action
{
	PushCharacters(NC::Window **w, std::vector<int> &&queue)
	: Action(aMacroUtility, ""), m_window(w), m_queue(queue) { }
	
protected:
	virtual void Run();
	
private:
	NC::Window **m_window;
	std::vector<int> m_queue;
};

struct RequireRunnable : public Action
{
	RequireRunnable(Action *action)
	: Action(aMacroUtility, ""), m_action(action) { assert(action); }
	
protected:
	virtual bool canBeRun() const;
	virtual void Run() { }
	
private:
	Action *m_action;
};

struct RequireScreen : public Action
{
	RequireScreen(ScreenType screen_type)
	: Action(aMacroUtility, ""), m_screen_type(screen_type) { }
	
protected:
	virtual bool canBeRun() const;
	virtual void Run() { }
	
private:
	ScreenType m_screen_type;
};

#endif // NCMPCPP_MACRO_UTILITIES_H
