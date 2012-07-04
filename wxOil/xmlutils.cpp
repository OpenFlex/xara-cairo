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


// The module that controls the OIL side of import/export filters.


#include "camtypes.h"

#include "xmlutils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <libxml/tree.h>
#include <libxml/parser.h>
//#include <libxml/xpath.h>

/************************************************************************************
> 	BOOL CXMLUtils::Initialise()

    Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
    Created:	08/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if succeeded
    Purpose:	Set up application wide XML support

************************************************************************************/
BOOL CXMLUtils::Initialise()
{
	xmlInitParser();
    LIBXML_TEST_VERSION

	return TRUE;
}




/************************************************************************************
> 	BOOL CXMLUtils::DeInitialise()

    Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
    Created:	08/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	TRUE if succeeded
    Purpose:	Set up application wide XML support

************************************************************************************/
BOOL CXMLUtils::DeInitialise()
{
	xmlCleanupParser();

#if _DEBUG
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
#endif

	return TRUE;
}




/************************************************************************************
>	static wxString CXMLUtils::ConvertToWXString(xmlChar* xmlString)

    Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
    Created:	08/May/2006
	Inputs:		-
	Outputs:	-
	Returns:	Pointer to newly allocated StringBase object (caller takes ownership)
    Purpose:	Set up application wide XML support

************************************************************************************/
wxString CXMLUtils::ConvertToWXString(const xmlChar* xmlString)
{
	// Use wx to convert from UTF8 to native
	wxString strTemp((const char*)xmlString, wxConvUTF8);

	return strTemp;
}




/************************************************************************************
>	static void CXMLUtils::ConvertToXMLString(wxString str)

    Author: 	Phil_Martin (Xara Group Ltd) <camelotdev@xara.com>
    Created:	09/May/2006
	Inputs:		str - wxString input
	Outputs:	pxmlstr - xmlChar* output
	Returns:	Pointer to newly allocated StringBase object (caller takes ownership)
    Purpose:	Set up application wide XML support

************************************************************************************/
void CXMLUtils::ConvertToXMLString(wxString str, xmlChar** pxmlstr)
{
//	wxCharBuffer buf = str.mb_str(wxConvUTF8);
//	wxStrdup from buf to pxmlstr?
}




#if _DEBUG
#if defined(LIBXML_XPATH_ENABLED) && \
	defined(LIBXML_SAX1_ENABLED) && \
    defined(LIBXML_OUTPUT_ENABLED)

/*
 * section: 	XPath
 * synopsis: 	Load a document, locate subelements with XPath, modify
 *              said elements and save the resulting document.
 * purpose: 	Shows how to make a full round-trip from a load/edit/save
 * usage:	xpath2 <xml-file> <xpath-expr> <new-value>
 * test:	xpath2 test3.xml '//discarded' discarded > xpath2.tmp ; diff xpath2.tmp xpath2.res ; rm xpath2.tmp
 * author: 	Aleksey Sanin and Daniel Veillard
 * copy: 	see Copyright for the status of this software.
 */
void CXMLUtils::Test()
{
    /* Init libxml */
    xmlInitParser();
    LIBXML_TEST_VERSION

    /* Do the main job */
    example4("/tmp/testin.xml", (xmlChar*)"//fred", (xmlChar*)"jim");

    /* Shutdown libxml */
    xmlCleanupParser();
    
    /*
     * this is to debug memory for regression tests
     */
    xmlMemoryDump();
}

/**
 * example4:
 * @filename:		the input XML filename.
 * @xpathExpr:		the xpath expression for evaluation.
 * @value:		the new node content.
 *
 * Parses input XML file, evaluates XPath expression and update the nodes
 * then print the result.
 *
 * Returns 0 on success and a negative value otherwise.
 */
INT32 CXMLUtils::example4(const char* filename, const xmlChar* xpathExpr, const xmlChar* value)
{
    xmlDocPtr doc;
    xmlXPathContextPtr xpathCtx; 
    xmlXPathObjectPtr xpathObj; 
    
    assert(filename);
    assert(xpathExpr);
    assert(value);

    /* Load XML document */
    doc = xmlParseFile(filename);
    if (doc == NULL) {
	fprintf(stderr, "Error: unable to parse file \"%s\"\n", filename);
	return(-1);
    }

    /* Create xpath evaluation context */
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL) {
        fprintf(stderr,"Error: unable to create new XPath context\n");
        xmlFreeDoc(doc); 
        return(-1);
    }
    
    /* Evaluate xpath expression */
    xpathObj = xmlXPathEvalExpression(xpathExpr, xpathCtx);
    if(xpathObj == NULL) {
        fprintf(stderr,"Error: unable to evaluate xpath expression \"%s\"\n", xpathExpr);
        xmlXPathFreeContext(xpathCtx); 
        xmlFreeDoc(doc); 
        return(-1);
    }

    /* update selected nodes */
    update_xpath_nodes(xpathObj->nodesetval, value);

    
    /* Cleanup of XPath data */
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtx); 

    /* dump the resulting document */
    xmlDocDump(stdout, doc);

	/* save the doc out to a temp file */
	xmlSaveFileEnc("/tmp/testout.xml", doc, "UTF-8");

    /* free the document */
    xmlFreeDoc(doc); 
    
    return(0);
}

/**
 * update_xpath_nodes:
 * @nodes:		the nodes set.
 * @value:		the new value for the node(s)
 *
 * Prints the @nodes content to @output.
 */
void CXMLUtils::update_xpath_nodes(xmlNodeSetPtr nodes, const xmlChar* value)
{
    INT32 size;
    INT32 i;
    
    assert(value);
    size = (nodes) ? nodes->nodeNr : 0;
    
    /*
     * NOTE: the nodes are processed in reverse order, i.e. reverse document
     *       order because xmlNodeSetContent can actually free up descendant
     *       of the node and such nodes may have been selected too ! Handling
     *       in reverse order ensure that descendant are accessed first, before
     *       they get removed. Mixing XPath and modifications on a tree must be
     *       done carefully !
     */
    for(i = size - 1; i >= 0; i--) {
	assert(nodes->nodeTab[i]);
	
	xmlNodeSetContent(nodes->nodeTab[i], value);
	/*
	 * All the elements returned by an XPath query are pointers to
	 * elements from the tree *except* namespace nodes where the XPath
	 * semantic is different from the implementation in libxml2 tree.
	 * As a result when a returned node set is freed when
	 * xmlXPathFreeObject() is called, that routine must check the
	 * element type. But node from the returned set may have been removed
	 * by xmlNodeSetContent() resulting in access to freed data.
	 * This can be exercised by running
	 *       valgrind xpath2 test3.xml '//discarded' discarded
	 * There is 2 ways around it:
	 *   - make a copy of the pointers to the nodes from the result set 
	 *     then call xmlXPathFreeObject() and then modify the nodes
	 * or
	 *   - remove the reference to the modified nodes from the node set
	 *     as they are processed, if they are not namespace nodes.
	 */
	if (nodes->nodeTab[i]->type != XML_NAMESPACE_DECL)
	    nodes->nodeTab[i] = NULL;
    }
}

#else
	#pragma error "XPath support not compiled in"
#endif

#endif

