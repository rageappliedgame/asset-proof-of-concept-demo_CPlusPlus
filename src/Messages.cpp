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
#include <Messages.h>

using namespace std;
using namespace rage;

/// <summary>
/// Gets the instance.
/// </summary>
///
/// <returns>
/// The instance.
/// </returns>
Messages& Messages::getInstance()
{
    static Messages instance;
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
bool Messages::define(string topic)
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
bool Messages::unsubscribe(int token)
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
