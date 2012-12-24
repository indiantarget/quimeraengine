// [TERMS&CONDITIONS]

#ifndef __TATFORMATTEDMESSAGE__
#define __TATFORMATTEDMESSAGE__

#include <list>

#include "TestExecution/TATMessageFormat.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

/// <summary>
/// Represents a multi-format text message. This message can be compound of many parts, which one with its own format.
/// This way, for example, a message can start with a white bold word and continue with a red underlined letter, ending
/// with a blue normal text.
/// </summary>
class TATFormattedMessage
{
    // TYPEDEFS
    // ---------------
public:

    typedef std::list< std::pair<wxString, TATMessageFormat> > TMessagePartCollection;
    typedef std::pair<wxString, TATMessageFormat> TMessagePart;


	// CONSTRUCTORS
	// ---------------
public:

	/// <summary>
	/// Default constructor.
	/// </summary>
	TATFormattedMessage();

    /// <summary>
    /// Constructor that receives a message part.
    /// </summary>
    /// <param name="strMessage">The text of the message part.</param>
    /// <param name="format">Optional. The format of the message part.</param>
    TATFormattedMessage(const wxString& strMessage, const TATMessageFormat& format=TATMessageFormat());


	// DESTRUCTOR
	// ---------------
public:

	/// <summary>
	/// Destructor.
	/// </summary>		
	virtual ~TATFormattedMessage();


	// METHODS
	// ---------------
public:

    /// <summary>
    /// Adds a new message part at the end.
    /// </summary>
    /// <param name="strMessage">The text of the message part.</param>
    /// <param name="format">Optional. The format of the message part.</param>
    /// <returns>
    /// A reference to the complete message.
    /// </returns>
    TATFormattedMessage& Append(const wxString& strMessage, const TATMessageFormat& format=TATMessageFormat());

    /// <summary>
    /// Removes all the parts of the message.
    /// </summary>
    void Clear();

    /// <summary>
    /// Concatenates the text of all the message parts and returns them as a unified string.
    /// </summary>
    /// <returns>
    /// The complete text of the message.
    /// </returns>
    wxString GetFullMessage() const;

    /// <summary>
    /// Gets the first message part and initializes the pointer to the current message part.
    /// </summary>
    /// <returns>
    /// The first message part. If there is no message parts, it will return null.
    /// </returns>
    const TMessagePart* GetFirstAndResetPointer();

    /// <summary>
    /// Gets the next message part, depending on the position of the internal pointer. 
    /// It moves forward the pointer too.
    /// </summary>
    /// <returns>
    /// The next message part. If there are no more message parts, it will return null.
    /// </returns>
    const TMessagePart* GetNext();
	

	// ATTRIBUTES
	// ---------------
protected:

    /// <summary>
    /// Internal list of message parts.
    /// </summary>
    TMessagePartCollection m_messageParts;

    /// <summary>
    /// The pointer to the current message part.
    /// </summary>
    TMessagePartCollection::const_iterator m_partPointer;
};

} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis

#endif // __TATFORMATTEDMESSAGE__
