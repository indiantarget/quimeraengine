//-------------------------------------------------------------------------------//
//                         QUIMERA ENGINE : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Quimera Engine.                                          //
// Quimera Engine is free software: you can redistribute it and/or modify        //
// it under the terms of the Lesser GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Quimera Engine is distributed in the hope that it will be useful,             //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// Lesser GNU General Public License for more details.                           //
//                                                                               //
// You should have received a copy of the Lesser GNU General Public License      //
// along with Quimera Engine. If not, see <http://www.gnu.org/licenses/>.        //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Quimera Engine in your project but we would appreciate     //
// if you do so or, at least, if you let us know about that.                     //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "QPath.h"

#include "EQComparisonType.h"
#include "EQTextEncoding.h"
#include "SQInteger.h"
#include "QDynamicArray.h"
#include "QUri.h"

#if defined(QE_OS_WINDOWS)
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

using Kinesis::QuimeraEngine::Common::DataTypes::char_q;


namespace Kinesis
{
namespace QuimeraEngine
{
namespace System
{
namespace IO
{
namespace FileSystem
{

//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |  ATTRIBUTES INITIALIZATION |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

const string_q QPath::PATH_SEPARATOR("/");
const char_q QPath::DOT('.');


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |       CONSTRUCTORS         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

QPath::QPath(const string_q &strPath)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

    string_q strReplacedPath = strPath;

#if defined(QE_OS_WINDOWS)
    
    // On Windows, paths can be created using backslashes as segment separator. They have to be replaced with slashes.
    static const string_q BACK_SLASH("\\");
    strReplacedPath.Replace(BACK_SLASH, QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive);

#endif

    // The path can be preceded by the hostname
    string_q strHostname;
    QPath::_ExtractHostnameFromPath(strReplacedPath, strHostname);

    if(!strHostname.IsEmpty())
    {
        //[TODO] Thund: Move this code to SetHostname when it exists
        QPath::_RemoveNotAllowedCharactersInHostname(strHostname);
        QPath::_ValidateHostname(strHostname);

        m_strHostname = strHostname;
    }

#if defined(QE_OS_WINDOWS)

    // Adds a slash at the end if the path consists only in a drive letter
    static const char_q CHAR_COLON(':');

    if(!strReplacedPath.IsEmpty() && strReplacedPath[strReplacedPath.GetLength() - 1U] == CHAR_COLON)
        strReplacedPath.Append(QPath::PATH_SEPARATOR);

    // Removes all the characters that are not allowed in Windows' file systems
    QPath::_RemoveNotAllowedCharactersInPath(strReplacedPath);
    // Note: Linux and Mac use Posix path names (case sensitive, separed with slashes, allowing any UTF-16 character but NUL and /)

#endif
    
    // Gets the filename if any
    string_q strFilename;
    QPath::_ExtractFilenameFromPath(strReplacedPath, strFilename);

    // [TODO] Thund: Move this code to SetFilename when it exists
    // Note: About the length restriction of 255 characters http://www.linfo.org/file_name.html
    m_strFilename = strFilename;
    QE_ASSERT_WARNING(m_strFilename.GetLength() <= 255, 
                      string_q("The length of the file name (") + SQInteger::ToString(m_strFilename.GetLength()) + ") exceeds the maximum allowed (255).");

    // [TODO] Thund: Move this code to SetPath when it exists
    static const string_q DOT_SEPARATOR(string_q(QPath::DOT) + QPath::PATH_SEPARATOR);

    if(strReplacedPath.IsEmpty())
        m_strPath = m_strHostname.IsEmpty() ? DOT_SEPARATOR : QPath::PATH_SEPARATOR;
    else
        m_strPath = strReplacedPath;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |           METHODS          |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

void QPath::_ResolveDotSegments(string_q &strPathToResolve)
{
    static const string_q FILE_SCHEME("file:");
    static const char_q CHAR_TILDE('~');

    string_q strFirstPart; // Stores the part of the path that is not affected by this operation (for example, the drive)
    string_q strRest;

#if defined(QE_OS_WINDOWS)
    /* [TODO] Thund: Uncomment this when HasDrive and GetDrive exist
    if(this->HasDrive())
    {
        // Extracts the drive part
        strFirstPart = this->GetDrive();
        strRest = strPathToResolve.Substring(strFirstPart.GetLength() + 1U); // +1 due to the colon (:)
    }
    */
    if(false)
    {
    }
#else
    if(strPathToResolve[0] == CHAR_TILDE)
    {
        // Extracts the tilde (~)
        strFirstPart = CHAR_TILDE;
        strRest = strPathToResolve.Substring(strFirstPart.GetLength() + 1U); // +1 due to the colon (:)
    }
#endif
    else
    {
        strRest = strPathToResolve;
    }

    QUri uri(FILE_SCHEME + strRest);
    strRest = uri.GetPath();
    QUri::Decode(strRest, strRest);

    if(strFirstPart.IsEmpty())
    {
        strPathToResolve = strRest;
    }
    else
    {
        strPathToResolve = strFirstPart;
        strPathToResolve.Append(strRest);
    }
}

#if defined(QE_OS_WINDOWS)

void QPath::_RemoveNotAllowedCharactersInPath(string_q &strPathToBeReplaced)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    // Windows's file system allows any UTF-16 character in path names but: NUL \ / : * ? " < > |
    static const string_q COLON(":");
    static const string_q ASTERISK("*");
    static const string_q QUESTION_MARK("?");
    static const string_q QUOTES("\"");
    static const string_q LOWER_THAN("<");
    static const string_q GREATER_THAN(">");
    static const string_q PIPE("|");

    QE_ASSERT_WARNING(!strPathToBeReplaced.Contains(ASTERISK,      EQComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(QUESTION_MARK, EQComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(QUOTES,        EQComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(LOWER_THAN,    EQComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(GREATER_THAN,  EQComparisonType::E_BinaryCaseSensitive) &&
                      !strPathToBeReplaced.Contains(PIPE,          EQComparisonType::E_BinaryCaseSensitive),
                      "Characters :  \\ / * ? \" < > | are not allowed.");

    if(strPathToBeReplaced.Contains(ASTERISK, EQComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(ASTERISK, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(QUESTION_MARK, EQComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(QUESTION_MARK, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(QUOTES, EQComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(QUOTES, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(LOWER_THAN, EQComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(LOWER_THAN, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(GREATER_THAN, EQComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(GREATER_THAN, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);

    if(strPathToBeReplaced.Contains(PIPE, EQComparisonType::E_BinaryCaseSensitive))
        strPathToBeReplaced.Replace(PIPE, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);

    // Colons are not allowed in path names, but Windows uses the concept of drives, which are specified using a colon
    // Therefore, this colon must be treated differently
    int nFirstSlashPosition = strPathToBeReplaced.IndexOf(QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive, 0);
    int nFirstColonPosition = strPathToBeReplaced.IndexOf(COLON, EQComparisonType::E_BinaryCaseSensitive, 0);

    if(nFirstSlashPosition != string_q::PATTERN_NOT_FOUND && nFirstColonPosition != string_q::PATTERN_NOT_FOUND)
    {
        if(nFirstColonPosition > nFirstSlashPosition)
        {
            QE_ASSERT_WARNING(false, "Colons (\":\") are not allowed but for specifying drives.");

            // Replaces all colons
            strPathToBeReplaced.Replace(COLON, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);
        }
        else
        {
            // Replaces all colons but first one (reserved for the drive)
            string_q strAfterDriveColon = strPathToBeReplaced.Substring(nFirstColonPosition + 1U, strPathToBeReplaced.GetLength() - 1U);

            if(strAfterDriveColon.Contains(COLON, EQComparisonType::E_BinaryCaseSensitive))
            {
                QE_ASSERT_WARNING(false, "Colons (\":\") are not allowed but for specifying drives.");
                strAfterDriveColon.Replace(COLON, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);
                strPathToBeReplaced = strPathToBeReplaced.Substring(0, nFirstColonPosition) + strAfterDriveColon;
            }
        }
    }
}

#endif

void QPath::_RemoveNotAllowedCharactersInHostname(string_q &strHostnameToBeReplaced)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    static const char_q CHAR_HYPHEN                          = '-';
    static const char_q CHAR_DOT                             = '.';
    static const codepoint_q CODEPOINT_FIRST_NUMBER          = '0';
    static const codepoint_q CODEPOINT_LAST_NUMBER           = '9';
    static const char_q CHAR_AT_SIGN                         = '@';
    static const codepoint_q CODEPOINT_FIRST_ALPHA_UPPERCASE = 'A';
    static const codepoint_q CODEPOINT_LAST_ALPHA_UPPERCASE  = 'Z';
    static const char_q CHAR_OPENING_SQUARE_BRACKET          = '[';
    static const char_q CHAR_CLOSING_SQUARE_BRACKET          = ']';
    static const codepoint_q CODEPOINT_FIRST_ALPHA_LOWERCASE = 'a';
    static const codepoint_q CODEPOINT_LAST_ALPHA_LOWERCASE  = 'z';

    codepoint_q currentCodepoint = 0;
    char_q currentChar(0);
    unsigned int i = 0;

    if(QPath::_IsIP(strHostnameToBeReplaced))
    {
        // Expected string example: [255.255.255.255]

        while(i < strHostnameToBeReplaced.GetLength())
        {
            currentChar = strHostnameToBeReplaced[i];
            currentCodepoint = currentChar.GetCodePoint();

            if((currentCodepoint < CODEPOINT_FIRST_NUMBER || currentCodepoint > CODEPOINT_LAST_NUMBER) && 
               currentChar != CHAR_OPENING_SQUARE_BRACKET &&
               currentChar != CHAR_CLOSING_SQUARE_BRACKET &&
               currentChar != CHAR_DOT)
            {
                QE_ASSERT_WARNING(false, string_q("The character '") + currentChar + "' is not allowed in this hostname.");
                strHostnameToBeReplaced.Replace(currentChar, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);
            }
            else
            {
                ++i;
            }
        }
    }
    else
    {
        // Expected string example: AZaz-09

        while(i < strHostnameToBeReplaced.GetLength())
        {
            currentChar = strHostnameToBeReplaced[i];
            currentCodepoint = currentChar.GetCodePoint();

            if((currentCodepoint < CODEPOINT_FIRST_NUMBER ||
                (currentCodepoint > CODEPOINT_LAST_NUMBER && currentCodepoint < CODEPOINT_FIRST_ALPHA_UPPERCASE) ||
                (currentCodepoint > CODEPOINT_LAST_ALPHA_UPPERCASE && currentCodepoint < CODEPOINT_FIRST_ALPHA_LOWERCASE) ||
                currentCodepoint > CODEPOINT_LAST_ALPHA_LOWERCASE)          // It's not an alpha or numerical chracter
#if defined(QE_OS_LINUX) || defined(QE_OS_MAC)
                &&
                currentChar != CHAR_AT_SIGN // On Unix-based systems, the hostname may appear accompanied with the username using an at sign
#endif
                &&
                currentChar != CHAR_HYPHEN)
            {
                QE_ASSERT_WARNING(false, string_q("The character '") + currentChar + "' is not allowed in this hostname.");
                strHostnameToBeReplaced.Replace(currentChar, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);
            }
            else
            {
                ++i;
            }
        }
    }
}

void QPath::_ExtractHostnameFromPath(string_q &strPath, string_q &strHostname)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    static const string_q AUTHORITY_SEPARATOR = "//";

    QE_ASSERT_WARNING(strPath != AUTHORITY_SEPARATOR, string_q("The path \"") + strPath + "\" is malformed.");
    
    int nHostnameStartPosition = strPath.IndexOf(AUTHORITY_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive);

    if(nHostnameStartPosition != string_q::PATTERN_NOT_FOUND)
    {
        nHostnameStartPosition += AUTHORITY_SEPARATOR.GetLength();
        int nHostnameEndPosition = strPath.IndexOf(QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive, nHostnameStartPosition);

        if(nHostnameEndPosition != string_q::PATTERN_NOT_FOUND)
        {
            // The authority is defined and the path is not empty
            strHostname = strPath.Substring(nHostnameStartPosition, nHostnameEndPosition - QPath::PATH_SEPARATOR.GetLength());
            
            // All the components prior to the path are removed so only the path is processed in next steps
            strPath = strPath.Substring(nHostnameEndPosition);
        }
        else
        {
            // The authority is defined and the path is empty
            strHostname = strPath.Substring(nHostnameStartPosition);
            
            // All the components prior to the path are removed so only the path is processed in next steps
            strPath = string_q::GetEmpty();
        }
    }
}

bool QPath::_ValidateHostname(const string_q &strHostname)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::SQInteger;

    static const char_q CHAR_HYPHEN = '-';

    const bool IS_NOT_EMPTY = !strHostname.IsEmpty();
    const bool DOES_NOT_START_WITH_HYPHEN = strHostname.IsEmpty() || strHostname[0] != CHAR_HYPHEN;
    const bool IS_VALID_IP = !QPath::_IsIP(strHostname) || QPath::_ValidateIP(strHostname);

    // RFC1123 section 2.1 says that hostnames are allowed to start with either a digit or a letter, so the restriction described in RFC 952 is relaxed

    QE_ASSERT_WARNING(IS_NOT_EMPTY, "The hostname is empty.");
    QE_ASSERT_WARNING(DOES_NOT_START_WITH_HYPHEN, "Hostnames cannot start with an hyphen.");
    QE_ASSERT_WARNING(IS_VALID_IP, "The IP is malformed.");
    
    return IS_NOT_EMPTY               &&
           DOES_NOT_START_WITH_HYPHEN && 
           IS_VALID_IP;
}

bool QPath::_IsIP(const string_q &strHostname)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;

    static const codepoint_q CODEPOINT_FIRST_NUMBER           = '0';
    static const codepoint_q CODEPOINT_LAST_NUMBER            = '9';
    static const codepoint_q CODEPOINT_OPENING_SQUARE_BRACKET = '[';

    // If it begins with an opening square bracket ("[") or a number ("0-9"), it must be an IP
    const codepoint_q FIRST_CODEPOINT = strHostname.IsEmpty() ? 0 : strHostname[0].GetCodePoint();
    return (FIRST_CODEPOINT >= CODEPOINT_FIRST_NUMBER && FIRST_CODEPOINT <= CODEPOINT_LAST_NUMBER) || FIRST_CODEPOINT == CODEPOINT_OPENING_SQUARE_BRACKET;
}

bool QPath::_ValidateIP(const string_q &strHostname)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::codepoint_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::i64_q;

    static const codepoint_q CODEPOINT_FIRST_NUMBER           = '0';
    static const codepoint_q CODEPOINT_LAST_NUMBER            = '9';
    static const codepoint_q CODEPOINT_OPENING_SQUARE_BRACKET = '[';
    static const codepoint_q CODEPOINT_CLOSING_SQUARE_BRACKET = ']';
    static const string_q DOT = ".";

    bool bIsValid = false;

    if(QPath::_IsIP(strHostname))
    {
        static const unsigned int PARTS_OF_IPV4 = 4U;

        // If the IP starts with a square bracket "[" it must end with another "]"
        const bool STARTS_WITH_SQUARE_BRACKET = strHostname[0].GetCodePoint() == CODEPOINT_OPENING_SQUARE_BRACKET;
        const bool ENDS_WITH_SQUARE_BRACKET = strHostname[strHostname.GetLength() - 1U].GetCodePoint() == CODEPOINT_CLOSING_SQUARE_BRACKET;
        const bool MISSING_SQUARE_BRACKET = STARTS_WITH_SQUARE_BRACKET != ENDS_WITH_SQUARE_BRACKET;
        string_q strIP;

        // Removes the square brackets
        if(STARTS_WITH_SQUARE_BRACKET && ENDS_WITH_SQUARE_BRACKET)
            strIP = strHostname.Substring(1U, strHostname.GetLength() - 2U);
        else
            strIP = strHostname;

        QE_ASSERT_WARNING(!MISSING_SQUARE_BRACKET, "If the IP starts with an opening square bracket (\"[\") it must end with a closing square bracket (\"]\").");

        if(!MISSING_SQUARE_BRACKET)
        {
            unsigned int uNumberOfParts = 0;
            string_q* arParts = strIP.Split(DOT, uNumberOfParts);

            QE_ASSERT_WARNING(uNumberOfParts == PARTS_OF_IPV4, "The IP (v4) must be compound of four parts.");

            if(uNumberOfParts == PARTS_OF_IPV4)
            {
                bool bAllPartsAreValid = true;

                unsigned int iPart = 0;

                // For every part of the IP NNN.NNN.NNN.NNN
                while(iPart < PARTS_OF_IPV4 && bAllPartsAreValid)
                {
                    // IP values cannot be empty
                    bAllPartsAreValid = bAllPartsAreValid && !arParts[iPart].IsEmpty();

                    QE_ASSERT_WARNING(!arParts[iPart].IsEmpty(), "Every part of the IP must contain a number in the range [0-255].");

                    unsigned int iChar = 0;
                    const unsigned int PART_LENGTH = arParts[iPart].GetLength();

                    // Checks for valid characters: [0-9]
                    while(iChar < PART_LENGTH && bAllPartsAreValid)
                    {
                        codepoint_q currentCodepoint = arParts[iPart][iChar].GetCodePoint();

                        bAllPartsAreValid = bAllPartsAreValid &&
                                            currentCodepoint >= CODEPOINT_FIRST_NUMBER && currentCodepoint <= CODEPOINT_LAST_NUMBER;

                        QE_ASSERT_WARNING(bAllPartsAreValid, "The IP contains non-allowed characters. Allowed characters are: \"[0-9]\", \".\", \"[\", \"]\".");

                        ++iChar;
                    }

                    // Checks that every number in the IP is not greater than 255 and is compound of up to 3 numbers
                    if(bAllPartsAreValid)
                    {
                        static const i64_q MAXIMUM_VALUE_ALLOWED = 255;
                        static const i64_q MAXIMUM_VALUE_LENGTH = 3;

                        const i64_q CURRENT_VALUE = arParts[iPart].ToInteger();

                        QE_ASSERT_WARNING(CURRENT_VALUE <= MAXIMUM_VALUE_ALLOWED, string_q("The number ") + arParts[iPart] + " is greater than maximum allowed (255).");
                        QE_ASSERT_WARNING(arParts[iPart].GetLength() <= MAXIMUM_VALUE_LENGTH, "Every part of the IP must, at most, 3-characters length.");

                        bAllPartsAreValid = bAllPartsAreValid && CURRENT_VALUE <= MAXIMUM_VALUE_ALLOWED;
                        bAllPartsAreValid = bAllPartsAreValid && arParts[iPart].GetLength() <= MAXIMUM_VALUE_LENGTH;
                    }

                    ++iPart;
                }

                bIsValid = bAllPartsAreValid;
            }

            delete[] arParts;
        }
    }

    return bIsValid;
}

void QPath::_ExtractFilenameFromPath(string_q &strPath, string_q &strFilename)
{
    static const char_q CHAR_SEPARATOR(QPath::PATH_SEPARATOR[0]);

    const int STRING_LAST_POSITION = strPath.GetLength() - 1;

    if(!strPath.IsEmpty() && strPath[STRING_LAST_POSITION] != CHAR_SEPARATOR)
    {
        int nLastSlashPosition = QPath::_GetLastIndexOfString(CHAR_SEPARATOR, strPath, STRING_LAST_POSITION);

        if(nLastSlashPosition != string_q::PATTERN_NOT_FOUND)
        {
            strFilename = strPath.Substring(nLastSlashPosition + 1);
            strPath = strPath.Substring(0, nLastSlashPosition);
        }
        else
        {
            // It only contains a filename
            strFilename = strPath;
            strPath = string_q::GetEmpty();
        }
    }
    else
    {
        strFilename = string_q::GetEmpty();
    }
}

QPath& QPath::operator=(const QPath &path)
{
    if(this != &path)
    {
        m_strHostname = path.m_strHostname;
        m_strPath     = path.m_strPath;
        m_strFilename = path.m_strFilename;
    }

    return *this;
}

bool QPath::operator==(const QPath &path) const
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    string_q strResolvedResidentPath = m_strPath;
    QPath::_ResolveDotSegments(strResolvedResidentPath);

    string_q strResolvedInputPath = path.m_strPath;
    QPath::_ResolveDotSegments(strResolvedInputPath);

#if defined(QE_OS_WINDOWS)
    // On Windows (NTFS, FAT16, FAT32, etc.) paths are case insensitive
    return m_strHostname.CompareTo(path.m_strHostname, EQComparisonType::E_BinaryCaseInsensitive) == 0 &&
           strResolvedResidentPath.CompareTo(strResolvedInputPath, EQComparisonType::E_BinaryCaseInsensitive) == 0 &&
           m_strFilename.CompareTo(path.m_strFilename, EQComparisonType::E_BinaryCaseInsensitive) == 0;
#else
    // On Unix and Mac (Posix) paths are case sensitive
    return m_strHostname == path.m_strHostname && strResolvedResidentPath == strResolvedInputPath && m_strFilename == path.m_strFilename;
#endif

}

bool QPath::operator!=(const QPath &path) const
{
    return !this->operator==(path);
}

void QPath::RemoveLastDirectory()
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    static const char_q CHAR_SEPARATOR(QPath::PATH_SEPARATOR[0]);
    static const string_q LEADING_DOT(string_q(QPath::DOT) + QPath::PATH_SEPARATOR);

    if(!m_strPath.IsEmpty() && 
        m_strPath != LEADING_DOT &&
        m_strPath != QPath::PATH_SEPARATOR)
    {
        int nPreviousDirectorySlash = QPath::_GetLastIndexOfString(CHAR_SEPARATOR, m_strPath, m_strPath.GetLength() - 2);

        // If it is not a relative path with only one directory
        if(nPreviousDirectorySlash != string_q::PATTERN_NOT_FOUND)
            m_strPath = m_strPath.Substring(0, nPreviousDirectorySlash);
    }
}

void QPath::AppendDirectory(const string_q &strDirectory)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    QE_ASSERT_WARNING(!strDirectory.IsEmpty(), "The input directory cannot be empty.");

    if(!strDirectory.IsEmpty())
    {
        string_q strFixedDirectory = strDirectory;

        QE_ASSERT_WARNING(!strFixedDirectory.Contains(QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive),
                          "Character '/' is not allowed.");

        if(strFixedDirectory.Contains(QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive))
            strFixedDirectory.Replace(QPath::PATH_SEPARATOR, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);

#if defined(QE_OS_WINDOWS)

        QPath::_RemoveNotAllowedCharactersInPath(strFixedDirectory);
        
        static const string_q BACKSLASH = "\\";

        QE_ASSERT_WARNING(!strFixedDirectory.Contains(BACKSLASH, EQComparisonType::E_BinaryCaseSensitive),
                          "Character '\\' is not allowed.");

        if(strFixedDirectory.Contains(BACKSLASH, EQComparisonType::E_BinaryCaseSensitive))
            strFixedDirectory.Replace(BACKSLASH, string_q::GetEmpty(), EQComparisonType::E_BinaryCaseSensitive);

        m_strPath.Append(strFixedDirectory);
#else
        // Note: Linux and Mac use Posix path names (case sensitive, separed with slashes, allowing any UTF-16 character but NUL and /)
        m_strPath.Append(strFixedDirectory);
#endif
        m_strPath.Append(QPath::PATH_SEPARATOR);
    }
}

QPath QPath::_GetCurrentWorkingDirectory()
{
    // Note: Interesting article about the variable PATH_MAX http://insanecoding.blogspot.com.es/2007/11/pathmax-simply-isnt.html
    // Note: Interesting article about working directories on Windows http://blogs.msdn.com/b/oldnewthing/archive/2010/10/11/10073890.aspx

    using Kinesis::QuimeraEngine::Common::DataTypes::EQTextEncoding;

    string_q strPath;

#if defined(QE_OS_WINDOWS)
    DWORD uPathLength = ::GetCurrentDirectoryW(0, null_q);
    wchar_t* arCharacters = new wchar_t[uPathLength + 1U];
    ::GetCurrentDirectoryW(uPathLength, arCharacters);

    strPath = string_q(rcast_q(arCharacters, char*), uPathLength * sizeof(wchar_t), EQTextEncoding::E_UTF16LE);
    delete[] arCharacters;
#elif defined(_GNU_SOURCE)
    char* arCharacters = ::get_current_dir_name();
    pointer_uint_q uPathLength = strlen(arCharacters);
    strPath = string_q(arCharacters, uPathLength, EQTextEncoding::E_UTF8);
    free(arCharacters);
#else
    char* arCharacters = ::getcwd(null_q, 0);
    pointer_uint_q uPathLength = strlen(arCharacters);
    strPath = string_q(arCharacters, uPathLength, EQTextEncoding::E_UTF8);
    free(arCharacters);
#endif

    // Adds a trailing slash if it does not end with one
    static const char_q CHAR_SEPARATOR(QPath::PATH_SEPARATOR[0]);

    if(!strPath.IsEmpty() && strPath[strPath.GetLength() - 1U] != CHAR_SEPARATOR)
        strPath.Append(QPath::PATH_SEPARATOR);

    return QPath(strPath);
}

void QPath::Resolve(const QPath &relativePath)
{
    QE_ASSERT_WARNING(!relativePath.IsAbsolute(), "Input path should be relative.");

#if defined(QE_OS_WINDOWS)    
    const bool RESIDENT_IS_ABSOLUTE = this->IsAbsolute();
#else
    static const char_q TILDE('~');
    const bool RESIDENT_IS_ABSOLUTE = this->IsAbsolute() || m_strPath[0] == TILDE;
#endif
    
    QE_ASSERT_WARNING(RESIDENT_IS_ABSOLUTE, "Resident path should be absolute.");

    if(relativePath.IsAbsolute())
    {
#if defined(QE_OS_WINDOWS)
        // [TODO] Thund: Uncomment when HasDrive, HasHostname, GetDrive and SetDrive exist
        // if(this->HasDrive() && !relativePath.HasHostname() && !relativePath.HasDrive())
        // {
        //     string_q strDrive = this->GetDrive();
        //     *this = relativePath;
        //     this->SetDrive(strDrive);
        // }
        // else
        {
            *this = relativePath;
        }
#else
        *this = relativePath;
#endif
    }
    else if(RESIDENT_IS_ABSOLUTE)
    {
        static const string_q FILE_SCHEME("file:");

        QUri relativeUri(relativePath.m_strPath);
        QUri absoluteURI(FILE_SCHEME + m_strPath);
        absoluteURI.Resolve(relativeUri);

#if defined(QE_OS_WINDOWS)
        // [TODO] Thund: Uncomment when HasDrive and GetDrive exist
        /*if(this->HasDrive())
        {
            m_strPath = this->GetDrive();*/
        if(false)
        {
#else
        if(m_strPath[0] == TILDE)
        {
            m_strPath = string_q(TILDE) + QPath::PATH_SEPARATOR;
#endif
            m_strPath.Append(absoluteURI.GetPath());
        }
        else
        {
            m_strPath = absoluteURI.GetPath();
        }
        
        QUri::Decode(m_strPath, m_strPath);

        if(!relativePath.m_strFilename.IsEmpty())
            m_strFilename = relativePath.m_strFilename;
    }
}

string_q QPath::GetAbsolutePath() const
{
    string_q strResult;

    if(this->IsAbsolute())
    {
        // [TODO] Thund: Replace with ToString
        strResult.Append(m_strHostname);
        strResult.Append(m_strPath);
        strResult.Append(m_strFilename);
    }
    else
    {
        QPath targetPath = QPath::_GetCurrentWorkingDirectory();
        targetPath.Resolve(*this);
        // [TODO] Thund: Uncomment when ToString exists
        //strResult = targetPath.ToString();
        strResult.Append(targetPath.m_strHostname);
        strResult.Append(targetPath.m_strPath);
        strResult.Append(targetPath.m_strFilename);
    }

    return strResult;
}

string_q QPath::GetRelativePath() const
{
    return this->GetRelativePathTo(QPath::_GetCurrentWorkingDirectory());
}

string_q QPath::GetRelativePathTo(const QPath &absolutePath) const
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

#if defined(QE_OS_WINDOWS)
    // On Windows, paths are not case sensitive
    static const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseInsensitive;
#else
    static const EQComparisonType COMPARISON_TYPE = EQComparisonType::E_BinaryCaseSensitive;
    static const char_q CHAR_TILDE('~');
#endif

    QE_ASSERT_WARNING(absolutePath.IsAbsolute(), "The input path must be absolute.");
    QE_ASSERT_WARNING(this->IsAbsolute(), "The resident path must be absolute.");
    QE_ASSERT_WARNING(absolutePath.m_strHostname.CompareTo(m_strHostname, COMPARISON_TYPE) == 0, "When paths have hostname, they must be equal.");

#if defined(QE_OS_WINDOWS)
    // [TODO] Thund: Uncomment this when HasDrive and GetDrive exist
    /*QE_ASSERT_WARNING((this->HasDrive() && absolutePath.HasDrive() && this->GetDrive() == absolutePath.GetDrive()) || (!this->HasDrive() && !absolutePath.HasDrive()), 
                        "When paths have drive, they must be equal.");*/
#else
    QE_ASSERT_WARNING((m_strPath[0] == CHAR_TILDE) == (absolutePath.m_strPath[0] == CHAR_TILDE), "When paths start with a tilde ('~'), both must start with it.");
#endif

    string_q strAbsolutePath;

    if(absolutePath.m_strHostname.CompareTo(m_strHostname, COMPARISON_TYPE) == 0 &&
       (absolutePath.IsAbsolute() && 
       this->IsAbsolute()
#if defined(QE_OS_WINDOWS)
       )
       // [TODO] Thund: Uncomment this when HasDrive and GetDrive exist
       //&& // If both have drives, they must be equal. Otherwise they must not have drives.
       //((this->HasDrive() && absolutePath.HasDrive() && this->GetDrive() == absolutePath.GetDrive()) || (!this->HasDrive() && !absolutePath.HasDrive())))
#else
       || // Both must start with tildes ("~") or none
       ((m_strPath[0] == CHAR_TILDE) == (absolutePath.m_strPath[0] == CHAR_TILDE)))
#endif
       )
    {
        static const string_q DOUBLE_DOT(string_q("..") + QPath::PATH_SEPARATOR);
        static const string_q SINGLE_DOT(string_q(".") + QPath::PATH_SEPARATOR);

        // Variables for resident path
        int nSlashPosition1 = 0;
        int nPreviousSlashPosition1 = 0;
        string_q strCurrentSegment1;

        // Variables for input path
        int nSlashPosition2 = 0;
        int nPreviousSlashPosition2 = 0;
        string_q strCurrentSegment2;

        int nFirstDifferentDirectory = string_q::PATTERN_NOT_FOUND;

        strAbsolutePath.Append(SINGLE_DOT);

#if defined(QE_OS_WINDOWS)
        // If resident path starts with a separator (without drive)
        if((m_strPath[0] == QPath::PATH_SEPARATOR[0]) == (absolutePath.m_strPath[0] == QPath::PATH_SEPARATOR[0]))
        {
            /* [TODO] Thund: Uncomment when HasDrive exists
            if(this->HasDrive())
            {
                // Skips the drive of the resident path
                nSlashPosition1 = m_strPath.IndexOf(QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive, nSlashPosition1) + 1;
            }
            else
            {
                // Skips the drive of the input path
                nSlashPosition2 = absolutePath.m_strPath.IndexOf(QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive, nSlashPosition1) + 1;
            }*/
        }
#endif

        // For every segment in the resident path
        while((nSlashPosition1 = m_strPath.IndexOf(QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive, nSlashPosition1)) != string_q::PATTERN_NOT_FOUND)
        {
            // If there were more segments in the input path
            if(nSlashPosition2 != string_q::PATTERN_NOT_FOUND)
            {
                nSlashPosition2 = absolutePath.m_strPath.IndexOf(QPath::PATH_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive, nSlashPosition2);

                // If there are more segments in the input path
                if(nSlashPosition2 != string_q::PATTERN_NOT_FOUND)
                {
                    // Gets the current segment from both paths
                    strCurrentSegment1 = m_strPath.Substring(nPreviousSlashPosition1, nSlashPosition1);
                    strCurrentSegment2 = absolutePath.m_strPath.Substring(nPreviousSlashPosition2, nSlashPosition2);

                    // If they are not equal
                    if(strCurrentSegment1.CompareTo(strCurrentSegment2, COMPARISON_TYPE) != 0)
                    {
                        // Puts a mark at the first different segment found
                        if(nFirstDifferentDirectory == string_q::PATTERN_NOT_FOUND)
                            nFirstDifferentDirectory = nPreviousSlashPosition2 + 1;

                        strAbsolutePath.Append(DOUBLE_DOT);
                    }

                    nPreviousSlashPosition2 = nSlashPosition2;
                    ++nSlashPosition2;
                }
                else
                {
                    // There one segment more in the resident path than in the input path
                    strAbsolutePath.Append(DOUBLE_DOT);
                }
            }
            else
            {
                strAbsolutePath.Append(DOUBLE_DOT);
            }

            nPreviousSlashPosition1 = nSlashPosition1;
            ++nSlashPosition1;
        }

        // Adds the rest of segments of the input path
        if(nFirstDifferentDirectory != string_q::PATTERN_NOT_FOUND && nFirstDifferentDirectory < scast_q(absolutePath.m_strPath.GetLength(), int))
        {
            // If there are differences between paths, it adds the segments that are different
            strAbsolutePath.Append(absolutePath.m_strPath.Substring(nFirstDifferentDirectory));
        }
        else if(absolutePath.m_strPath.GetLength() > m_strPath.GetLength())
        {
            // If there are more segments in the input path than in the resident path, adds the rest
            strAbsolutePath.Append(absolutePath.m_strPath.Substring(m_strPath.GetLength()));
        }
    }

    return strAbsolutePath;
}

int QPath::_GetLastIndexOfString(const char_q &pattern, const string_q &strSource, const int nFromIndex)
{
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;

    int nLastDotPosition = string_q::PATTERN_NOT_FOUND;
    int i = nFromIndex;

    while(i >= 0 && strSource[i] != pattern)
        --i;

    if(i >= 0)
        nLastDotPosition = i;

    return nLastDotPosition;
}


//##################=======================================================##################
//##################             ____________________________              ##################
//##################            |                            |             ##################
//##################            |         PROPERTIES         |             ##################
//##################           /|                            |\            ##################
//##################             \/\/\/\/\/\/\/\/\/\/\/\/\/\/              ##################
//##################                                                       ##################
//##################=======================================================##################

bool QPath::IsAbsolute() const
{
    using Kinesis::QuimeraEngine::Common::DataTypes::char_q;
    using Kinesis::QuimeraEngine::Common::DataTypes::EQComparisonType;

    static const string_q COLON_FOLLOWED_BY_SEPARATOR(string_q(":") + QPath::PATH_SEPARATOR);
    static const char_q CHAR_SEPARATOR(QPath::PATH_SEPARATOR[0]);
    
    return m_strPath[0] == CHAR_SEPARATOR || !m_strHostname.IsEmpty() // [TODO] Thund: Replace this with HasHostname when it exists
#if defined(QE_OS_WINDOWS)
           // Note: On Windows, the path "C:directory1" (without slash after the drive letter), for example, means a relative path in the current directory of the drive C
           || 
           m_strPath.Contains(COLON_FOLLOWED_BY_SEPARATOR, EQComparisonType::E_BinaryCaseSensitive)
#endif
           ;
}

string_q QPath::GetFilenameWithoutExtension() const
{
    string_q strFilename;

    if(!m_strFilename.IsEmpty())
    {
        // Searches for the last dot
        int nDotPosition = string_q::PATTERN_NOT_FOUND;
        nDotPosition = QPath::_GetLastIndexOfString(QPath::DOT, m_strFilename, m_strFilename.GetLength() - 1);

        if(nDotPosition != string_q::PATTERN_NOT_FOUND)
            strFilename = m_strFilename.Substring(0, nDotPosition - 1U);
        else
            strFilename = m_strFilename;
    }

    return strFilename;
}

string_q QPath::GetFilename() const
{
    return m_strFilename;
}

string_q QPath::GetFileExtension() const
{
    string_q strExtension;

    if(!m_strFilename.IsEmpty())
    {
        // Searches for the last dot
        int nDotPosition = string_q::PATTERN_NOT_FOUND;
        nDotPosition = QPath::_GetLastIndexOfString(QPath::DOT, m_strFilename, m_strFilename.GetLength() - 1);

        if(nDotPosition != string_q::PATTERN_NOT_FOUND && scast_q(nDotPosition + 1, unsigned int) < m_strFilename.GetLength())
            strExtension = m_strFilename.Substring(nDotPosition + 1);
    }

    return strExtension;
}


} //namespace FileSystem
} //namespace IO
} //namespace System
} //namespace QuimeraEngine
} //namespace Kinesis
