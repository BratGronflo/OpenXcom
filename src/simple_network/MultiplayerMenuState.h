#pragma once
/*
 * Copyright 2010-2016 OpenXcom Developers.
 *
 * This file is part of OpenXcom.
 *
 * OpenXcom is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * OpenXcom is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with OpenXcom.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "../Engine/State.h"

namespace OpenXcom
{

	class TextButton;
	class Window;
	class Text;

	class MultiplayerMenuState : public State
	{
	private:
		TextButton* _btnHostGame, * _btnJoinGame, * _btnRefreshGame, * _btnReturn;
		Window* _window;
		Text* _txtPlayerName;
	public:
		/// Creates the Multiplayer Menu state.
		MultiplayerMenuState();
		/// Cleans up the Main Menu state.
		~MultiplayerMenuState();
		/// Handler for clicking the Host Game button.
		void btnHostGameClick(Action *action);
		/// Handler for clicking the Join Game button.
		void btnJoinGameClick(Action *action);
		/// Handler for clicking the Refresh Game button.
		void btnRefreshGameClick(Action *action);
		/// Handler for clicking the ReturnToMainMenu button.
		void btnReturnClick(Action *action);
	};
}
