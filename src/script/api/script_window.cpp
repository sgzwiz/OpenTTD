/* $Id: script_window.cpp 23737 2012-01-03 20:37:56Z truebrain $ */

/*
 * This file is part of OpenTTD.
 * OpenTTD is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, version 2.
 * OpenTTD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with OpenTTD. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file script_window.cpp Implementation of ScriptWindow. */

#include "../../stdafx.h"
#include "script_window.hpp"
#include "script_game.hpp"
#include "../../window_func.h"
#include "../../window_gui.h"

/* static */ void ScriptWindow::Close(WindowClass window, uint32 number)
{
	if (ScriptGame::IsMultiplayer()) return;

	if (number == NUMBER_ALL) {
		DeleteWindowByClass((::WindowClass)window);
		return;
	}

	DeleteWindowById((::WindowClass)window, number);
}

/* static */ bool ScriptWindow::IsOpen(WindowClass window, uint32 number)
{
	if (ScriptGame::IsMultiplayer()) return false;

	if (number == NUMBER_ALL) {
		return (FindWindowByClass((::WindowClass)window) != NULL);
	}

	return FindWindowById((::WindowClass)window, number) != NULL;
}

/* static */ void ScriptWindow::Highlight(WindowClass window, uint32 number, uint8 widget, TextColour colour)
{
	if (ScriptGame::IsMultiplayer()) return;
	if (number == NUMBER_ALL) return;
	if (!IsOpen(window, number)) return;
	if (colour != TC_INVALID && (::TextColour)colour >= ::TC_END) return;

	Window *w = FindWindowById((::WindowClass)window, number);

	if (widget == WIDGET_ALL) {
		if (colour != TC_INVALID) return;
		w->DisableAllWidgetHighlight();
		return;
	}

	const NWidgetBase *wid = w->GetWidget<NWidgetBase>(widget);
	if (wid == NULL) return;
	w->SetWidgetHighlight(widget, (::TextColour)colour);
}
