using namespace rage;

/// <summary>
/// Sets the settings.
/// </summary>
///
/// <param name="settings"> [in,out] If non-null, options for controlling the operation. </param>
void BaseSettings::setSettings(BaseSettings* settings) {
	ISettings::setSettings(this);
}
