#ifndef DIALOGUEASSET_H
#define DIALOGUEASSET_H

#include <BaseAsset.h>
#include <Logger.h>

#include <list>

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
            virtual ~DialogueAsset();
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
