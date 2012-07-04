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


#ifndef INC_WEBFLAGS
#define INC_WEBFLAGS

/*********************************************************************************************

>	class WebCorrectFlags: public CCObject

	Author:		Graham_Walmsley (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/6/97
	Purpose:	A set of flags that define how a URL should be corrected.

				For example, should "www.xara.com" be corrected to 
				"http://www.xara.com/"? Should "d:\dir1\file.htm"
				be corrected to "file://d|/dir1/file.htm"? And so on...
	
*********************************************************************************************/

class WebCorrectFlags : public CCObject
{
	CC_DECLARE_DYNAMIC(WebCorrectFlags);

	//Member variables
protected:
	BOOL m_fBackslashes;	//TRUE if we should correct all backslashes to forward slashes

	BOOL m_fLocalFilenames;	//TRUE if we should correct local filenames to URLs
							//e.g. d:\dir1\file.htm to file://d|/dir1/file.htm
							//and \\netloc\dir1\file.htm to file:////netloc/dir1/file.htm

	BOOL m_fNetscapeFilenames;
							//TRUE if we should correct Netscape's local filename URLs
							//to IE3's local filename urls
							//i.e. file:///d|/dir1/filename.h to
							// file://d|/dir1/filename.h
							//(Note the different number of slashes after the "file:"


	BOOL m_fFTP;			//TRUE if we should correct ftp.xxxx.xxxx to
							//ftp://ftp.xxxx.xxxx

	BOOL m_fHTTP;			//TRUE if we should correct xxx.xxx.xxx to
							//http://xxx.xxx.xxx

	BOOL m_fMailto;			//TRUE if we should correct xxxxx@xxxxxxxxxxx
							//to mailto:xxxxx@xxxxxxxxxxx

	BOOL m_fNoSlash;		//TRUE if we should correct http://xxx.xxx.xxx
							//to http://xxx.xxx.xxx/
							//and http://xxx.xxx.xxx/xxx 
							//to http://xxx.xxx.xxx/xxx/

	BOOL m_fNoNetLoc;		//TRUE if we should correct http:xxxxxxxx
							//and http:/xxxxxxxxxx to 
							//http://xxxxxxxxxx


	//Access functions
public:
	BOOL CorrectBackslashes()
	{
		return m_fBackslashes;
	}

	BOOL CorrectLocalFilenames()
	{
		return m_fLocalFilenames;
	}

	BOOL CorrectNetscapeFilenames()
	{
		return m_fNetscapeFilenames;
	}
						  
	BOOL CorrectFTP()
	{
		return m_fFTP;
	}

	BOOL CorrectHTTP()
	{
		return m_fHTTP;
	}

	BOOL CorrectMailto()
	{
		return m_fMailto;
	}

	BOOL CorrectNoSlash()
	{
		return m_fNoSlash;
	}

	BOOL CorrectNoNetLoc()
	{
		return m_fNoNetLoc;
	}


	void SetCorrectBackslashes(BOOL fNewValue)
	{
		m_fBackslashes=fNewValue;
	}

	void SetCorrectLocalFilemames(BOOL fNewValue)
	{
		m_fLocalFilenames=fNewValue;
	}

	void SetCorrectNetscapeFilemames(BOOL fNewValue)
	{
		m_fNetscapeFilenames=fNewValue;
	}

	void SetCorrectFTP(BOOL fNewValue)
	{
		m_fFTP=fNewValue;
	}

	void SetCorrectHTTP(BOOL fNewValue)
	{
		m_fHTTP=fNewValue;
	}

	void SetCorrectMailto(BOOL fNewValue)
	{
		m_fMailto=fNewValue;
	}

	void SetCorrectNoSlash(BOOL fNewValue)
	{
		m_fNoSlash=fNewValue;
	}

	void SetCorrectNoNetLoc(BOOL fNewValue)
	{
		m_fNoNetLoc=fNewValue;
	}


	//Copy constructor, destructor and assignment operator
public:
	WebCorrectFlags& operator=(const WebCorrectFlags&);	
	WebCorrectFlags(const WebCorrectFlags& InFlags);	
	~WebCorrectFlags();	

	//Constructors
public:
	WebCorrectFlags()
	{
		m_fBackslashes=FALSE;
		m_fLocalFilenames=FALSE;
		m_fNetscapeFilenames=FALSE;
		m_fFTP=FALSE;
		m_fHTTP=FALSE;
		m_fMailto=FALSE;
		m_fNoSlash=FALSE;
		m_fNoNetLoc=FALSE;
	}

	WebCorrectFlags(BOOL fBackslashes, BOOL fLocalFilenames, BOOL fNetscapeFilenames, BOOL fFTP, BOOL fHTTP,	BOOL fMailto, BOOL fNoSlash, BOOL fNoNetLoc)
	{
		m_fBackslashes=fBackslashes;
		m_fLocalFilenames=fLocalFilenames;
		m_fNetscapeFilenames=fNetscapeFilenames;
		m_fFTP=fFTP;
		m_fHTTP=fHTTP;
		m_fMailto=fMailto;
		m_fNoSlash=fNoSlash;
		m_fNoNetLoc=fNoNetLoc;
	};

	//Functions to set the flags to appropriate presets
public:
	void SetForURLImport()
	{
		m_fBackslashes=TRUE;
		m_fLocalFilenames=TRUE;
		m_fNetscapeFilenames=TRUE;
		m_fFTP=FALSE;
		m_fHTTP=TRUE;
		m_fMailto=FALSE;
		m_fNoSlash=TRUE;
		m_fNoNetLoc=TRUE;
	}

	void SetForWebAddressDialog()
	{
		m_fBackslashes=TRUE;
		m_fLocalFilenames=TRUE;
		m_fNetscapeFilenames=TRUE;
		m_fFTP=TRUE;
		m_fHTTP=TRUE;
		m_fMailto=TRUE;
		m_fNoSlash=TRUE;
		m_fNoNetLoc=TRUE;
	}


	
			
};

#endif

