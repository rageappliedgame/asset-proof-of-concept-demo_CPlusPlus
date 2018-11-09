// file:	include\IDataStorage.h
//
// summary:	Declares the IDataStorage interface
#ifndef IDATASTORAGE_H
#define IDATASTORAGE_H

#include <string>
#include <vector>


// namespace: rage
//
// summary:	.
namespace rage
{
/// <summary>
/// A data storage interface for the Bridge (used for saving/loading data).
/// </summary>
class IDataStorage
{
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~IDataStorage() {}

    /// <summary>
    /// Deletes the given name.
    /// </summary>
    ///
    /// <param name="name"> The name to delete. </param>
    ///
    /// <returns>
    /// True if it succeeds, false if it fails.
    /// </returns>
    virtual bool Delete(const std::string& name) = 0;

    /// <summary>
    /// Determine if 'name' exists.
    /// </summary>
    ///
    /// <param name="name"> The name. </param>
    ///
    /// <returns>
    /// True if it succeeds, false if it fails.
    /// </returns>
    virtual bool Exists(const std::string& name) = 0;

    /// <summary>
    /// Gets the files.
    /// </summary>
    ///
    /// <returns>
    /// A std::vector&lt;std::string&gt;
    /// </returns>
    virtual std::vector<std::string> Files() = 0;

    /// <summary>
    /// Loads the given name.
    /// </summary>
    ///
    /// <param name="name"> The name to load. </param>
    ///
    /// <returns>
    /// A std::string.
    /// </returns>
    virtual std::string Load(const std::string& name) = 0;

    /// <summary>
    /// Saves.
    /// </summary>
    ///
    /// <param name="name"> The name. </param>
    /// <param name="data"> The data. </param>
    virtual void Save(const std::string& name, const std::string& data) = 0;
};
}

#endif // IDATASTORAGE_H
