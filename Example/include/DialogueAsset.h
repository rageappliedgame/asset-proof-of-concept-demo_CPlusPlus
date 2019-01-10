/*
 * Copyright 2019 Open University of the Netherlands / St. Kliment Ohridski University of Sofia
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * This project has received funding from the European Union’s Horizon
 * 2020 research and innovation programme under grant agreement No 644187.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef DIALOGUEASSET_H
#define DIALOGUEASSET_H

#include <BaseAsset.h>
#include <Logger.h>

#include <list>

#pragma message ("VEG DialogueAsset.h is part of the demo app.")

namespace rage
{
	struct Dialogue
	{
		std::string actor;
		std::string id;
		int next;
		std::list<int> responses;
		std::string text;
	};
	struct State
	{
		std::string actor;
		std::string player;
		int state;
	};
	class DialogueAsset : public BaseAsset
	{
	public:
		DialogueAsset();
		virtual ~DialogueAsset() {};
		Dialogue interact(std::string actor, std::string player, int response);
		Dialogue interact(std::string actor, std::string player, std::string response = "");
		void loadScript(std::string actor, const char* fileName);
	private:
		int findStateIndex(std::string actor, std::string player);
		void updateState(std::string actor, std::string player, int state);
		bool isNumeric(std::string value);
		void doLog(std::string message);
		std::list<Dialogue> dialogues;
		std::list<State> states;
		Logger* logger;
	};
}

#endif // DIALOGUEASSET_H
