// file:	include\VersionString.h
//
// summary:	Declares the version string class
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
