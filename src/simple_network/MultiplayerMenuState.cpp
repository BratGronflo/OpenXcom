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
#include "MultiplayerMenuState.h"
#include <sstream>
#include "../version.h"
#include "../Engine/Game.h"
#include "../Mod/Mod.h"
#include "../Engine/LocalizedText.h"
#include "../Engine/Screen.h"
#include "../Interface/TextButton.h"
#include "../Interface/Window.h"
#include "../Interface/Text.h"
#include "../Menu/NewGameState.h"
#include "../Menu/NewBattleState.h"
#include "../Menu/ListLoadState.h"
#include "../Menu/OptionsVideoState.h"
#include "../Menu/ModListState.h"
#include "../Engine/Options.h"
#include "../Engine/FileMap.h"
#include "../Engine/SDL2Helpers.h"
#include <fstream>

namespace OpenXcom
{
	/**
	 * Initializes all the elements in the Multiplayer Menu window.
	 * @param updateCheck Perform update check?
	 */
	MultiplayerMenuState::MultiplayerMenuState()
	{
		// Create objects
		_window = new Window(this, 300, 180, 40, 25, POPUP_BOTH);
		_btnHostGame = new TextButton(92, 20, 64, 90);
		_btnJoinGame = new TextButton(92, 20, 164, 90);
		_btnRefreshGame = new TextButton(92, 20, 64, 118);
		_btnReturn = new TextButton(92, 20, 164, 118);
		_txtPlayerName = new Text(256, 30, 32, 45);

		// Set palette
		setInterface("MultiplayerMenu");

		add(_window, "window", "MultiplayerMenu");
		add(_btnHostGame, "button", "MultiplayerMenu");
		add(_btnJoinGame, "button", "MultiplayerMenu");
		add(_btnRefreshGame, "button", "MultiplayerMenu");
		add(_btnReturn, "button", "MultiplayerMenu");
		add(_txtPlayerName, "button", "MultiplayerMenu");

		centerAllSurfaces();

		// Set up objects
		setWindowBackground(_window, "MultiplayerMenu");

		_btnHostGame->setText(tr("STR_HOST_GAME"));
		_btnHostGame->onMouseClick((ActionHandler)&MultiplayerMenuState::btnHostGameClick);

		_btnJoinGame->setText(tr("STR_JOIN_GAME"));
		_btnJoinGame->onMouseClick((ActionHandler)&MultiplayerMenuState::btnJoinGameClick);

		_btnRefreshGame->setText(tr("STR_REFRESH_GAME"));
		_btnRefreshGame->onMouseClick((ActionHandler)&MultiplayerMenuState::btnRefreshGameClick);

		_btnReturn->setText(tr("STR_RETURN"));
		_btnReturn->onMouseClick((ActionHandler)&MultiplayerMenuState::btnReturnClick);

		_txtPlayerName->setText(tr("STR_PLAYERNAME"));
		_txtPlayerName->setVisible(true);
	};


	MultiplayerMenuState::~MultiplayerMenuState()
	{

	}

	void MultiplayerMenuState::btnHostGameClick(Action*)
	{
		_game->pushState(new NewBattleState);
	}
}
