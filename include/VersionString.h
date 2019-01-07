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
#ifndef VERSIONSTRING_H
#define VERSIONSTRING_H

#include <string>


// namespace: rage
//
// summary:	.
namespace rage
{
/// <summary>
/// A version string.
/// </summary>
class VersionString
{
public:

    /// <summary>
    /// Default constructor.
    /// </summary>
    VersionString(){};

    /// <summary>
    /// Constructor.
    /// </summary>
    ///
    /// <param name="version"> The version. </param>
    explicit VersionString(const char *version);

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~VersionString(){};
/// <summary>
/// .
/// </summary>
    bool operator <= (const VersionString &other);

    /// <summary>
    /// Assignment operator.
    /// </summary>
    ///
    /// <param name="other"> The other. </param>
    ///
    /// <returns>
    /// A shallow copy of this object.
    /// </returns>
    VersionString& operator = (const VersionString &other);
private:

    /// <summary>
    /// Gets the number of. 
    /// </summary>
    ///
    /// <value>
    /// The count.
    /// </value>
    int major, minor, revision, build, cnt;
};
}

#endif // VERSIONSTRING_H
