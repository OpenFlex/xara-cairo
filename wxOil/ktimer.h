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


#ifndef INC_KTIMER
#define	INC_KTIMER

class KernelTimer;

/********************************************************************************************

>	class TimerMsg: public Msg

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2006
	Purpose:	This message is sent whenever something happens with a timer
	SeeAlso:	-

********************************************************************************************/

class TimerMsg: public Msg
{
	CC_DECLARE_DYNAMIC(TimerMsg);
public:

	enum TimerMsgType
	{
		NOTIFY			// A timer event has occurred 
	};

	TimerMsgType m_MsgType;
	KernelTimer* m_pTimer; // A pointer to the timer concerned

	TimerMsg(TimerMsgType MsgType=TimerMsg::NOTIFY, KernelTimer * pTimer = NULL)
	  : m_MsgType(MsgType), m_pTimer(pTimer)
		{ /* empty */ }
};


/*******************************************************************************************

>	class KernelTimer : public CCObject

	Author:		Alex_Bligh <alex@alex.org.uk>
	Created:	25/04/2005
	Purpose:	A class exposing a timer to the kernel
	Notes:		In the OIL
	See Also:	

This class provides a kernel timer object, with an OIL-layer independent interface layer.
Currently it uses wxTimer, though any timer interface could be used.

There are two main ways of using this class:
1. As is, in which case it will broadcast timer events
2. By deriving a class from it, and overriding Notify()

If you know exactly where the notifcation should go, then in your class definition
do something like the following, which will avoid any broadcasts.

	class MyClass : public CCObject
	{
		MyClass() : m_Timer(this);
		void OnTimer();

	private:
		class MyTimer : public KernelTimer
		{
		public:
			MyTimer(MyClass * pOwner) : m_pOwner(pOwner) {}
			virtual void Notify() {m_pOwner->OnTimer();}
			MyClass * m_pOwner;
		};
		MyTimer m_Timer;
	};

********************************************************************************************/

class KernelTimer : public CCObject
{
	CC_DECLARE_DYNAMIC(KernelTimer);

private:
	CCRuntimeClass* m_BroadcastClass;

public:
	KernelTimer(CCRuntimeClass * BroadcastClass = NULL) : m_BroadcastClass (BroadcastClass), m_Timer(this) {}
	~KernelTimer() {}

	void SetBroadcastClass (CCRuntimeClass * BroadcastClass) {m_BroadcastClass = BroadcastClass;}
	CCRuntimeClass * GetBroadcastClass () const {return m_BroadcastClass;}

protected:
	virtual void Notify()
	{
		Msg * pMsg = new TimerMsg(TimerMsg::NOTIFY, this);
		if (pMsg)
			MessageHandler::Broadcast(pMsg, m_BroadcastClass);
	}

private:

	class CamTimer : public wxTimer
	{
	public:
		CamTimer(KernelTimer * pKTimer = NULL) : m_pKTimer(pKTimer) {};
		~CamTimer() {};
		KernelTimer * m_pKTimer;
		virtual void Notify() {if (m_pKTimer) { m_pKTimer->Notify();}}
	};

	CamTimer m_Timer;

public:
	INT32 GetInterval() const { return m_Timer.GetInterval(); }
	BOOL IsOneShost() const { return m_Timer.IsOneShot(); }
	BOOL IsRunning() const { return m_Timer.IsRunning(); }
	BOOL Start(INT32 milliseconds = -1, BOOL OneShot = FALSE) { return m_Timer.Start(milliseconds, OneShot); }
	void Stop() { m_Timer.Stop(); }
};

#endif

