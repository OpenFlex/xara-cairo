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




#ifndef INC_CCASYNCHFILE
#define INC_CCASYNCHFILE


class LoadContext;



/********************************************************************************************
>	class asynchstreambuf : public streambuf

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	5/8/96
	Purpose:	an asynch version of streambuf 
				It is assumed that two versions of the file will be open i.e. read and write.
				The read and write will run in seperate threads. Any access to the file that 
				might fail due to lack of data will cause the read thread to sleep until more 
				data is available.
				It is assumed that the write thread will never seek - this would corrupt the 
				BytesAvailable count.
				
	SeeAlso:	streambuf; ios; costream
********************************************************************************************/

class asynchstreambuf : public filebuf
{
private:
	
		
	// determine whether a read or seek can succed
	BOOL DataAvailable(INT32 Length);

	LoadContext * pLoadContext;

	wxCondition			*WakeEvents[2];

	// allow xsgetn to return less bytes than required without failing
	// this is used for LoadInitialSegment
	BOOL DontFail;

public:
	asynchstreambuf();
	~asynchstreambuf();

	void DownloadHasEnded(HRESULT Status);
    void SetDontFail(BOOL state){ DontFail = state;};
	
	virtual streampos seekoff(streamoff sOff ,ios::seekdir eDir,INT32 mode =ios::in|ios::out);
    virtual streampos seekpos(streampos,INT32 mode =ios::in|ios::out);	

    virtual INT32 xsputn(const char *,INT32);
    virtual INT32 xsgetn(char *,INT32);
	void SetLoadContext(LoadContext *pLContext);
	LoadContext *GetLoadContext() const {return pLoadContext;}

	// the total set of virtual functions in streambuf 
	/*
	// Creation & destruction.
	asynchstreambuf(IStream* pIStream = 0);
	virtual INT32 sync();
	virtual streambuf* setbuf(char *, INT32);
    virtual INT32 overflow(INT32 i =EOF) ; // pure virtual function
    virtual INT32 underflow() ;        // pure virtual function
  	virtual INT32 pbackfail(INT32);
	*/

	
};




/********************************************************************************************

>	class CCAsynchDiskFile : public CCDiskFile

	Author:		Chris_Parks (Xara Group Ltd) <camelotdev@xara.com>
	Created:	31/8/1993          
	Purpose:	a file class that can be used for asynchronous loading. It contains an
				asynchstreambuf (see above)
				
********************************************************************************************/

class CCAPI CCAsynchDiskFile : public CCDiskFile
{                             
CC_DECLARE_DYNAMIC(CCAsynchDiskFile);
    
public:

	CCAsynchDiskFile(UINT32 bufferSize = CCFILE_DEFAULTSIZE,
     		   BOOL ErrorReporting = TRUE,
     		   BOOL ExceptionThrowing = FALSE);
     
		                                      
	CCAsynchDiskFile(PathName fPath, INT32 fileMode, 
			   INT32 fileAccess  = 0,
			   UINT32 bufferSize = CCFILE_DEFAULTSIZE,
			   BOOL ErrorReporting = TRUE,
			   BOOL ExceptionThrowing = FALSE);

	
	~CCAsynchDiskFile();



	// Uses the above flags to determine whether to report errors and/or throw exceptions
	virtual void GotError( UINT32 errorID, const TCHAR* errorString);	
	virtual void GotError( UINT32 errorID);
	
	virtual size_t   Size();
	virtual BOOL     eof() const;

	void SetDownloadContext(LoadContext * pLContext)
		{ ((asynchstreambuf*)(IOFile->rdbuf()))->SetLoadContext(pLContext);};

	void DownloadHasEnded(HRESULT Status);
	void SetDontFail(BOOL state){ ((asynchstreambuf*)(IOFile->rdbuf()))->SetDontFail(state);
									DontFail=state;};


};



/********************************************************************************************
>	class async_fstream : public fstream

	Author:		Justin_Flude (Xara Group Ltd) <camelotdev@xara.com>
	Created:	9/9/96
	Purpose:		Converts fstream to use an async_filebuf.
********************************************************************************************/

class async_fstream : public fstream
{
public:
	async_fstream();
	async_fstream(const char * name, INT32 mode, INT32 prot);
	async_fstream(filedesc fd);
	async_fstream(filedesc fd, char* sbuf, INT32 len);

protected:
	streambuf * set_streambuf(streambuf* pbuf);
};



#endif


