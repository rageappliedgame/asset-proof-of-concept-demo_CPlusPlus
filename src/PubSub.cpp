// file:	src\PubSub.cpp
//
// summary:	Implements the pub sub class
#include <PubSub.h>

using namespace std;
using namespace rage;

/// <summary>
/// Gets the instance.
/// </summary>
///
/// <returns>
/// The instance.
/// </returns>
PubSub& PubSub::getInstance()
{
    static PubSub instance;
    return instance;
}

/// <summary>
/// Defines.
/// </summary>
///
/// <param name="topic"> The topic. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
bool PubSub::define(string topic)
{
    TopicMap::iterator itr = topics.find(topic);
    if (itr == topics.end())
    {
        Subscribers subscribers;
        topics[topic] = subscribers;
    }

    return false;
}

/// <summary>
/// Unsubscribes.
/// </summary>
///
/// <param name="token"> The token. </param>
///
/// <returns>
/// True if it succeeds, false if it fails.
/// </returns>
bool PubSub::unsubscribe(int token)
{
    Subscribers::iterator itrSub;
    for(TopicMap::iterator itr = topics.begin(); itr != topics.end(); ++itr)
    {
        itrSub = itr->second.find(token);
        if (itrSub != itr->second.end())
        {
            itr->second.erase(itrSub);
            return true;
        }
    }

    return false;
}
