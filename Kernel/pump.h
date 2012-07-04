/*
 * xara-cairo, a vector drawing program
 *
 * Based on Xara XL, Copyright (C) 1993-2006 Xara Group Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 2 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

/*
 *  */ 

#ifndef INC_PUMP
#define INC_PUMP       

#include "ccobject.h"
#include "listitem.h"
#include "list.h"
#include "msg.h"
#include "selmsg.h"
//#include "colmsg.h"
#include "docvmsg.h"
#include "barmsg.h"
#include "docmsgs.h"
//#include "optsmsgs.h"

class BarMsg;
class ColourChangingMsg;
class OptionsChangingMsg;

// MsgResult is returned by the MessageHandler's Message function 

enum MsgResult
{ 
	FAIL = 0,	// Something terrible happened whilst processing the message
	 			// eg. we run out of memory 
	OK, 		// Message handled ok
	EAT_MSG   	// The Message was handled ok but don't send it to any
	 			// more MessageHandlers. 
};



/********************************************************************************************

>	class MessageHandler: public ListItem

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/03/93

	Purpose: 	If a system object must respond to system messages then its class should be
				derived from the abstract MessageHandler class. When a MessageHandler is 
				constructed it gets added to a list of MessageHandlers which are all targets
				of system messages. To send a message to all or just a subset of 
				MessageHandlers, you should use the static Broadcast method. The virtual 
				'Message' function is called whenever the MessageHandler is sent a message.   

	SeeAlso:	

********************************************************************************************/
class MessageHandler: public ListItem	 
{
	CC_DECLARE_DYNCREATE( MessageHandler )
public: 
	// If you wish to create a class which does not get sent system messages then set the 
	// SendMessages flag to FALSE. 
  	MessageHandler(CCRuntimeClass* Class = CC_RUNTIME_CLASS(MessageHandler), BOOL SendMessages = TRUE); 

	// Destructor
	virtual ~MessageHandler(); 

	// Broadcast is used to send a message to all MessageHandlers which are derived from the 
	// given runtime class. 
	static MsgResult Broadcast(Msg* Message,
						 CCRuntimeClass* Class = NULL  // NULL = Send message to all
						 							   // MessageHandlers. 
								 );

	static BOOL RegisterClassGroup(CCRuntimeClass* Class); 

	// GetClassList can be used to get a pointer to the list of MessageHandlers in the same 
	// class group.  
	static List* GetClassList(CCRuntimeClass* Class); 

	static void	Destroy(); // This function must be called to delete the MessageHandler lists
						   // at system termination time. 

	// Used to determine if there is a live MessageHandler with class Class  
	static BOOL MessageHandlerExists(CCRuntimeClass* Class); 
	
	// The default constructor has to be provided for DYNCREATE to work. It should 
	// never get called. 

	// This silly variable is required by the BROADCAST macros 
	static Msg* pTmpMsg; 


	
protected:
	// The virtual Message function. This base class function decodes the message and calls 
	// the appropriate On message fn. (See below).    
	virtual MsgResult Message(Msg* Msg);

	// -------------------------------------------------------------------------------------
	// Add On message handlers here for all messages which are likely to be of interest to
	// all MessageHandler objects. The name format should be On<MessageName>
	// These will be the messages broadcast using BROADCAST_TO_ALL

	// Called by the Message fn when a death message is received
	virtual BOOL OnDeathMsg(void) {return TRUE;}; 
	// Called when a SelChangingMessage is received
	virtual BOOL OnSelChangingMsg(SelChangingMsg::SelectionState State) {return TRUE;}; 
	// Called when a ColourChangingMsg is received
	virtual BOOL OnColourChangingMsg(ColourChangingMsg* Msg) { return TRUE; };
	// Called when a DocViewMsg is received
	virtual BOOL OnDocViewMsg(DocView* pDocView, DocViewMsg::DocViewState State) {return TRUE;};
	// Called whenever a BarMsg is received
	virtual BOOL OnBarMsg(BarMsg* Msg) {return TRUE;};
	// Called whenever a DocChangingMsg is received
	virtual BOOL OnDocChangingMsg(Document* pChangingDoc, DocChangingMsg::DocState State) {return TRUE;};
	// Called whenever an OptionsChangingMsg is received
	virtual BOOL OnOptionsChangingMsg(OptionsChangingMsg* Msg) {return TRUE;};
	// Called whenever a CommonAttrsChangedMsg is received
	virtual BOOL OnCommonAttrsChangedMsg(void) {return TRUE;};
			
	// --------------------------------------------------------------------------------------

	// The SendNoMoreMessages method removes a MessageHandler from the MessageHandler list.
	// UndoableOperations need to call this function whenever they get added to the 
	// OperationHistory. 
	static void SendNoMoreMessages(MessageHandler* MessageHandlerToRemove); 

	// The MessageHandlerClassList is a list of lists of MessageHandlers. The MessageHandlers
	// are grouped according to the class specified in the MessageHandler's constructor.  
	static List MessageHandlerClassList; // A list of MessageHandlerClassItems 

	// The PostDeath flag indicates that the DeathMsg has been sent and that therfore
	// no more messages will be allowed to be sent from this point on!
	static BOOL PostDeath;
};		

/********************************************************************************************

>	class MessageHandlerList: public Listitem					  

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	18/3/94
	Inputs:		-
	Outputs:	-
	Returns:	-
	Purpose:	A MessageHandlerList contains a List of MessageHandler objects derived 
				from the same runtime class 
	Errors:		-
	SeeAlso:	-

********************************************************************************************/

class MessageHandlerList: public ListItem					  
{
	CC_DECLARE_MEMDUMP(MessageHandlerList);

public:
	MessageHandlerList(CCRuntimeClass* Class); 
	CCRuntimeClass*  MessageHandlerClass; 
	List 				m_List;	// A list of all MessageHandler objects derived from 
								// MessageHandlerClass. 
}; 
#endif 
