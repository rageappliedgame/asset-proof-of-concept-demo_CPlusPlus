// file:	include\IBridge.h
//
// summary:	Declares the IBridge interface
#ifndef IBRIDGE_H
#define IBRIDGE_H


// namespace: rage
//
// summary:	.
namespace rage
{
	/// <summary>
	/// A bridge interface (used for type-safety).
	/// </summary>
	class IBridge
	{
	public:

		/// <summary>
		/// Destructor.
		/// </summary>
		virtual ~IBridge() {}
	};
}

#endif // IBRIDGE_H
