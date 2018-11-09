// file:	include\IDataArchive.h
//
// summary:	Declares the IDataArchive interface
#ifndef IDATAARCHIVE_H
#define IDATAARCHIVE_H


// namespace: rage
//
// summary:	.
namespace rage
{
/// <summary>
/// A data archive interface for the Bridge (used for archiving data).
/// </summary>
class IDataArchive
{
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~IDataArchive() {}

    /// <summary>
    /// Archives the given name.
    /// </summary>
    ///
    /// <param name="name"> The name. </param>
    ///
    /// <returns>
    /// True if it succeeds, false if it fails.
    /// </returns>
    virtual bool Archive(const std::string& name) = 0;
};
}

#endif // IDATAARCHIVE_H
