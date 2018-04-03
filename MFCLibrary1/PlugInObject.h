#pragma once


class CPlugInObject
{
public:
	CPlugInObject();
	virtual ~CPlugInObject();
	virtual BOOL InitPlugIn( HWND hWindowHandle );
	virtual BOOL ExitPlugIn(void);
};

