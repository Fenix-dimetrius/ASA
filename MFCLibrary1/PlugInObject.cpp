// This is the PLUGINOBJECT source file that implements the virtual
// methods (functions) of the Plug-in-object class.

#include "StdAfx.h"
#include "PlugInObject.h"
#include <mmreg.h>



// Standard constructor
CPlugInObject::CPlugInObject(void)
{
}

// Standard destructor 
CPlugInObject::~CPlugInObject()
{
	// Clean up buffers and other directX stuff here
	ExitPlugIn();
}


// This function initializes the PLUGIN and LOADS the settings
// from the object settings file. (each plugin object instance has one)
BOOL CPlugInObject::InitPlugIn( HWND hWnd )
{

	// Check window handle
    if ( hWnd == NULL )
	{
		AfxMessageBox( "Error: Window handle invalid!");
		//MessageBox(NULL, " Error: Window handle invalid!", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return( FALSE );
	}
	

	return( TRUE );

}

// Cleaning up when the plugin DLL is unloaded
BOOL CPlugInObject::ExitPlugIn(void)
{


	return( TRUE );

}

