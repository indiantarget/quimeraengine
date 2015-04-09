//-------------------------------------------------------------------------------//
//                   TEST AUTOMATION TOOL : LICENSE                              //
//-------------------------------------------------------------------------------//
// This file is part of Test Automation Tool.                                    //
// Test Automation Tool is free software: you can redistribute it and/or modify  //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation, either version 3 of the License, or             //
// (at your option) any later version.                                           //
//                                                                               //
// Test Automation Tool is distributed in the hope that it will be useful,       //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License for more details.                                  //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with Test Automation Tool. If not, see <http://www.gnu.org/licenses/>.  //
//                                                                               //
// This license doesn't force you to put any kind of banner or logo telling      //
// that you are using Test Automation Tool in your project but we would          //
// appreciate if you do so or, at least, if you let us know about that.          //
//                                                                               //
// Enjoy!                                                                        //
//                                                                               //
// Kinesis Team                                                                  //
//-------------------------------------------------------------------------------//

#include "TestConfiguration/TATRuleNode.h"


namespace Kinesis
{
namespace TestAutomationTool
{
namespace Backend
{

//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |  ATTRIBUTES INITIALIZATION |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################



//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |       CONSTRUCTORS		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

TATRuleNode::TATRuleNode() : m_bCanBeEmpty(false),
                             m_bIsObligatory(false),
                             m_nMaxCount(false)
{
}

TATRuleNode::TATRuleNode(const wxString& strName, const int nMaxCount, const bool& bCanBeEmpty,
                         const bool& bIsObligatory, const ETATConfigNodeType& type) :
                            m_bCanBeEmpty(bCanBeEmpty),
                            m_bIsObligatory(bIsObligatory),
                            m_nMaxCount(nMaxCount)
{
    m_strName = strName;
    m_type = type;
}


//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |		    METHODS			 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################



//##################=======================================================##################
//##################			 ____________________________			   ##################
//##################			|							 |			   ##################
//##################		    |         PROPERTIES		 |			   ##################
//##################		   /|							 |\			   ##################
//##################			 \/\/\/\/\/\/\/\/\/\/\/\/\/\/			   ##################
//##################													   ##################
//##################=======================================================##################

int TATRuleNode::GetMaxCount() const
{
    return m_nMaxCount;
}

void TATRuleNode::SetMaxCount(const int& nMaxCount)
{
    m_nMaxCount = nMaxCount;
}

bool TATRuleNode::GetIsObligatory() const
{
    return m_bIsObligatory;
}

void TATRuleNode::SetIsObligatory(const bool& bIsObligatory)
{
    m_bIsObligatory = bIsObligatory;
}

bool TATRuleNode::GetCanBeEmpty() const
{
    return m_bCanBeEmpty;
}

void TATRuleNode::SetCanBeEmpty(const bool& bCanBeEmpty)
{
    m_bCanBeEmpty = bCanBeEmpty;
}


} //namespace Backend
} //namespace TestAutomationTool
} //namespace Kinesis