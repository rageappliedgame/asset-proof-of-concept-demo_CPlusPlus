#include <DialogueAsset.h>

#include <AssetManager.h>
#include <PubSub.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
using namespace rage;

DialogueAsset::DialogueAsset() : BaseAsset("DialogueAsset")
{
    logger = dynamic_cast<Logger*>(AssetManager::getInstance().findAssetByClass("Logger"));
}

DialogueAsset::~DialogueAsset()
{
    //dtor
}

void DialogueAsset::loadScript(string actor, const char* fileName)
{
    ifstream file(fileName);
    if (!file)
    {
        cout << "File not found." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        Dialogue dialogue;

        dialogue.actor = actor;
        dialogue.next  = -1;

        if (!isdigit(line[0]))
        {
            dialogue.id = line.substr(0, line.find(":"));
            dialogue.text = line.substr(line.find(":") + 1);
        }
        else
        {
            int start = line.find(" ") + 1;

            dialogue.id = line.substr(0, start - 1);

            if (line.find("->") != std::string::npos)
            {
                dialogue.text = line.substr(start, line.find("->") - start - 1);
                dialogue.next = atoi(line.substr(line.find("->") + 3).c_str());
            }
            else
            {
                dialogue.text = line.substr(start, line.find("[") - start - 1);
                string responses = line.substr(line.find('[') + 1, line.find(']') - line.find('[') - 1);
                stringstream ss(responses);
                int response;
                while (ss >> response)
                {
                    dialogue.responses.push_back(response);
                    if (ss.peek() == ',' || ss.peek() == ' ')
                    {
                        ss.ignore();
                    }
                }
            }
        }

        dialogues.push_back(dialogue);
    }

    file.close();
}

Dialogue DialogueAsset::interact(string actor, string player, int response)
{
    ostringstream strResponse;
    strResponse << response;
    return interact(actor, player, strResponse.str());
}

Dialogue DialogueAsset::interact(string actor, string player, string response)
{
    int state = findStateIndex(actor, player);

    Dialogue dialogue;

    bool numeric = isNumeric(response);

    list<Dialogue>::iterator itr;
    itr = find_if(dialogues.begin(), dialogues.end(), [&](Dialogue& dialogue){
                  return dialogue.actor == actor && dialogue.id == response;
    });

    if (itr != dialogues.end())
    {
        if (numeric)
        {
            if (isNumeric(itr->id))
            {
                doLog(" << " + itr->id + " was chosen.");
                state = itr->next;
                updateState(actor, player, state);
            }

            list<Dialogue>::iterator itrNext;
            ostringstream strState;
            strState << state;
            itrNext = find_if(dialogues.begin(), dialogues.end(), [&](Dialogue& dialogue){
                          return dialogue.actor == actor && dialogue.id == strState.str();
            });

            dialogue = *itrNext;
        }
        else
        {
            doLog(actor + " ask " + player + " about " + response);
            dialogue = *itr;
        }
    }
    else
    {
        list<Dialogue>::iterator itrCur;
        ostringstream strState;
        strState << state;
        itrCur = find_if(dialogues.begin(), dialogues.end(), [&](Dialogue& dialogue){
                      return dialogue.actor == actor && dialogue.id == strState.str();
        });
        dialogue = *itrCur;
    }

    logger->log(dialogue.id + ". " + dialogue.text);

    if (dialogue.responses.size() > 0)
    {
        for (list<int>::iterator itr = dialogue.responses.begin(); itr != dialogue.responses.end(); ++itr)
        {
            list<Dialogue>::const_iterator answer;
            answer = find_if(dialogues.begin(), dialogues.end(), [&itr](Dialogue& dialogue){
                      ostringstream convert;
                      convert << *itr;
                      return dialogue.id == convert.str();});
            logger->log(" >> " + answer->id + ". " + answer->text);
        }
    }

    if (dialogue.next != -1)
    {
        updateState(actor, player, dialogue.next);
    }

    return dialogue;
}

int DialogueAsset::findStateIndex(string actor, string player)
{
    list<State>::const_iterator itr;
    itr = find_if(states.begin(), states.end(), [&](const State& state){
                  return state.actor == actor && state.player == player;
    });
    if (itr != states.end())
    {
        return itr->state;
    }
    else
    {
        State state;
        state.actor = actor;
        state.player = player;
        state.state = 0;
        states.push_back(state);
    }

    return 0;
}

void DialogueAsset::updateState(string actor, string player, int p_state)
{
    list<State>::iterator itr;
    itr = find_if(states.begin(), states.end(), [&](State& state){
                  return state.actor == actor && state.player == player;
    });
    if (itr != states.end())
    {
        itr->state = p_state;
    }
    else
    {
        State state;
        state.actor = actor;
        state.player = player;
        state.state = p_state;
        states.push_back(state);
    }
}

bool DialogueAsset::isNumeric(string value)
{
    bool isNumber = true;
    for(string::const_iterator k = value.begin(); k != value.end(); ++k)
    {
        isNumber = isNumber && isdigit(*k);
    }

    return isNumber;
}

void DialogueAsset::doLog(string message)
{
    if (logger)
    {
        logger->log(message);
    }
    else
    {
        cout << message << endl;
    }
}
