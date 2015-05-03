#include <iostream>
#include <LogEvent.h>

using namespace std;
using namespace rage;

void LogEvent::operator += (const BaseDelegate* delegate)
{
    for(list<BaseDelegate*>::iterator itr = delegates.begin(); itr != delegates.end(); ++itr)
    {
        if((*itr)->equals(delegate))
        {
            return;
        }
    }

    delegates.push_back(const_cast<BaseDelegate*>(delegate));
}

void LogEvent::operator -= (const BaseDelegate* delegate)
{
    for(list<BaseDelegate*>::iterator itr = delegates.begin(); itr != delegates.end(); ++itr)
    {
        if((*itr)->equals(delegate))
        {
            delegates.erase(itr);
            break;
        }
    }
}

void LogEvent::operator ()(const void* message)
{
    for(list<BaseDelegate*>::iterator itr = delegates.begin(); itr != delegates.end(); ++itr)
    {
        (*itr)->call(message);
    }
}

LogEvent::~LogEvent()
{
    for(list<BaseDelegate*>::iterator itr = delegates.begin(); itr != delegates.end(); ++itr)
    {
        delete (*itr);
    }
}

list<BaseDelegate*> LogEvent::getInvocationList()
{
    return delegates;
}
