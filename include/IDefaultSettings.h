// file:	include\IDefaultSettings.h
//
// summary:	Declares the IDefaultSettings interface
#ifndef IDEFAULTSETTINGS_H
#define IDEFAULTSETTINGS_H

#include <string>


// namespace: rage
//
// summary:	.
namespace rage
{
/// <summary>
/// A default settings interface for the Bridge (used for loading default settings).
/// </summary>
class IDefaultSettings
{
public:

    /// <summary>
    /// Destructor.
    /// </summary>
    virtual ~IDefaultSettings() {};

    /// <summary>
    /// Query if 'clazz' has default settings.
    /// </summary>
    ///
    /// <param name="clazz"> The clazz. </param>
    /// <param name="id">    The identifier. </param>
    ///
    /// <returns>
    /// True if default settings, false if not.
    /// </returns>
    virtual bool hasDefaultSettings(const std::string& clazz, const std::string& id) = 0;

    /// <summary>
    /// Loads default settings.
    /// </summary>
    ///
    /// <param name="clazz"> The clazz. </param>
    /// <param name="id">    The identifier. </param>
    ///
    /// <returns>
    /// The default settings.
    /// </returns>
    virtual std::string loadDefaultSettings(const std::string& clazz, const std::string& id) = 0;

    /// <summary>
    /// Saves a default settings.
    /// </summary>
    ///
    /// <param name="clazz">    The clazz. </param>
    /// <param name="id">	    The identifier. </param>
    /// <param name="fileData"> Information describing the file. </param>
    virtual void saveDefaultSettings(const std::string& clazz, const std::string& id, const std::string& fileData) = 0;
};
}

#endif // IDEFAULTSETTINGS_H
