#ifndef LOGEVENT_H
#define LOGEVENT_H

#include <LogDelegate.h>

#include <list>

namespace rage
{
    class LogEvent
    {
        public:
            void operator += (const BaseDelegate* delegate);
            void operator -= (const BaseDelegate* delegate);
            void operator () (const void* message);
            ~LogEvent();
            std::list<BaseDelegate*> getInvocationList();
        private:
            std::list<BaseDelegate*> delegates;
    };
}

#endif // LOGEVENT_H
