#ifndef LOGDELEGATE_H
#define LOGDELEGATE_H

namespace rage
{
    class BaseDelegate
    {
        public:
            virtual bool equals( const BaseDelegate* obj) = 0;
            virtual void operator()(const void* message) = 0;
            virtual void call(const void* message) = 0;
    };

    template<class TReciever>
    class LogDelegate : public BaseDelegate
    {
        private:
            typedef void (TReciever::*Function)(const void* message);
            Function    function;
            TReciever*  receiver;
        public:
            LogDelegate(TReciever* obj, Function func)
            {
                function = func;
                receiver = obj;
            }

            bool equals(const BaseDelegate* obj)
            {
                const LogDelegate<TReciever>* delegate;

                delegate = static_cast<const LogDelegate<TReciever>*>(obj);

                return delegate->receiver == receiver && delegate->function == function;
            }

            virtual void operator()(const void* message)
            {
                (receiver->*function)(message);
            }

            virtual void call(const void* message)
            {
                (receiver->*function)(message);
            }
    };
}

#endif // LOGDELEGATE_H
