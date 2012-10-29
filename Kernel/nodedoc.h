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


// header for NodeDocument

#ifndef INC_NODEDOC
#define	INC_NODEDOC


class BaseDocument;

/***********************************************************************************************

>	class NodeDocument : public NodeRenderablePaper

	Author:		Simon_Maneggio (Xara Group Ltd) <camelotdev@xara.com>
	Created:	25/4/93
	Purpose:	This class represents the root of a document tree. It contains the extents
				of the entire document as two DocCoords (LowExtent, HighExtent). LowExtent
				is the Coordinate position of the low corner of its first chapter whilst  
				High Extent is the coordinate position of the high corner of its final chapter. 

	SeeAlso:	NodeRenderablePaper   

***********************************************************************************************/
            
class NodeDocument: public NodeRenderablePaper
{   
	CC_DECLARE_DYNAMIC( NodeDocument ) 
public:            

	NodeDocument();   
	
	NodeDocument(Node* ContextNode,  
					AttachNodeDirection Direction,
					BOOL Locked=FALSE, 
					BOOL Mangled=FALSE,  
					BOOL Marked=FALSE, 
					BOOL Selected=FALSE 
		   		   );  

	~NodeDocument();
	 
	void SetParentDoc(BaseDocument *pNewDoc);
	BaseDocument *GetParentDoc() { return pParentDoc; };
	virtual BOOL IsNodeDocument() const;

    DocCoord LoExtent() const; 
    DocCoord HiExtent() const;    
    void DescribeExtents(DocCoord* LoExtent, DocCoord* HiExtent) const;   
    void SetExtents();   
    
    #ifdef _DEBUG
    void ShowDebugTreeDetails() const;
    #endif      
    virtual UINT32 GetNodeSize() const; 			// Returns size of node in bytes

    virtual void GetDebugDetails(StringBase* Str);   // This is used by the Debug Tree dialog
													 // It will probably be deleted when we ship !. 
	                        
	virtual void PolyCopyNodeContents(NodeRenderable* pNodeCopy);

protected:              
	virtual Node* SimpleCopy();  
	void CopyNodeContents(NodeDocument* NodeCopy); 
	        
	// The low corner of the first chapters pasteboard.  
	DocCoord LowExtent;  
	// The high corner of the final chapters pasteboard.                                          
	DocCoord HighExtent; 

	BaseDocument *pParentDoc;
};   


#endif
