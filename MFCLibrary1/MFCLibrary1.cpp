// MFCLibrary1.cpp: определяет процедуры инициализации для DLL.
//
//#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include "MFCLibrary1.h"
#include "ASADlg.h"
#include "PlugInSettingDlg.h"
#include "ASATest.h"
//#include "PlugInObject.cpp"
#include <fstream>
ASATest TestBody2;


#pragma warning(disable : 4996)
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: если эта библиотека DLL динамически связана с библиотеками DLL MFC,
//		все функции, экспортированные из данной DLL-библиотеки, которые выполняют вызовы к
//		MFC, должны содержать макрос AFX_MANAGE_STATE в
//		самое начало функции.
//
//		Например:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// тело нормальной функции
//		}
//
//		Важно, чтобы данный макрос был представлен в каждой
//		функции до вызова MFC.  Это означает, что
//		он должен быть первым оператором 
//		функции и предшествовать даже любым объявлениям переменных объекта,
//		поскольку их конструкторы могут выполнять вызовы к MFC
//		DLL.
//
//		В Технических указаниях MFC 33 и 58 содержатся более
//		подробные сведения.
//


// CMFCLibrary1App

PlugInSettingDlg m_SettingDlg;

CImage imgPlugIn;
MyStruct UpdInfoVal;
BEGIN_MESSAGE_MAP(CMFCLibrary1App, CWinApp)
END_MESSAGE_MAP()

//#define m_AuxPlugInNum (6)
typedef NameInstrument(*importFunction)();
//importFunction func2dll, func3dll;
importFunction * func2dllArr = new importFunction[m_AuxPlugInNum];
//HMODULE hinstLib, hinstLib2;
HMODULE *hinstLibArr = new HMODULE[m_AuxPlugInNum];

NameInstrument NameChannelSecDll;
//NameInstrument NameChannelThrDll;
//importFunction func2dllArr[m_AuxPlugInNum];
//HMODULE hinstLibArr[m_AuxPlugInNum];


struct UpdateInfo
{
	DWORD		dwMSTime;		// Current session time in milliseconds. Starts at 0
	double		dDataVal;		// The current (single) data value
	double*		pdDataArray;	// A pointer to the array of new data values
	DWORD		dwNewSamples;	// The amount of new samples present in the array
	DWORD		dwChanIndex;	// The index of the channel to update (0,1,2 or 3)
	DWORD		dwLinkState;	// The threshold state of the linked instrument (bits 0,1,2,3)
	DWORD		dwInhibitFlag;	// Is this instrument inhibited? (no feedback or movement)
	double		dRangeStart;	// Range START of linked instrument (use this to normalize)
	double		dRangeEnd;		// Range END of linked instrument (use this to normalize)
	DWORD		dwReserved1;	// Reserved for future use
	DWORD		dwReserved2;
};
// создание CMFCLibrary1App


// Global WINDOW handles:
HWND	g_hWnd;

CMFCLibrary1App::CMFCLibrary1App()
{
	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance
	
}


// Единственный объект CMFCLibrary1App

CMFCLibrary1App theApp;


// инициализация CMFCLibrary1App

BOOL CMFCLibrary1App::InitInstance()
{
	CWinApp::InitInstance();

	// Время показа
	m_ShowTime = 1000;
	// Задержка до показа
	m_BeforeShow = 1000;
	//  Задержка после показа
	m_AfterShow = 1000;

	//  Задержка после показа
	m_DelaySpeedMouse = 500;

	// завершить показ по клику
	m_EndShowByClick = false;
	imgPlugIn.Load(_T("PlugIns/TestASA/fonASA.jpg"));

	UpdInfoVal.ChouseCard = " ";
	UpdInfoVal.TimeInterval = " ";
	UpdInfoVal.NumActualCard = " ";
	UpdInfoVal.TruOrFalseCard = " ";

	return TRUE;
}


// THE plugin object class

//CPlugInObject	*g_cpPlugInClass;

//************************************************************************************
// During DLL LOAD this initializes all and checks if the 
// right ACTIVATION KEYCODE has been entered for this plugin
// Called once only when the application is initializing
// It returns the DWORD TYPE of this plugin
// (called by BioTrace)
//************************************************************************************

extern "C" __declspec(dllexport) DWORD InitPlugInDLL(HINSTANCE hDLL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//AsaDlgClass.Create(IDD_ASA); // создаем окно настроек
	//m_SettingDlg.Create(IDD_SETTINGS); // создаем окно настроек
	//g_cpPlugInClass = NULL;
	/*ASADlg AsaTestDlg;

	AsaTestDlg.SetTimersInterval();*/



	return(1);	// Return number of instances supported (default=1, 0 in case of error)
}

//************************************************************************************
// Get NAME (description) of plugin and the name of the preview thumbnail JPG
// (called by BioTrace)
//************************************************************************************
// The UNIQUE TYPE identifier of this plugin DLL
#define UNIQUE_PLUGIN_ID	201

extern "C" __declspec(dllexport) DWORD GetPlugInInfo(char *pszTextDescription, char *pszThumbNailJpg)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (pszTextDescription != NULL)
	{
		sprintf(pszTextDescription, "ASA");
		
	}

	if (pszThumbNailJpg != NULL)
	{
		sprintf(pszThumbNailJpg, "ASA.jpg");
	}

	CString * str = new CString[m_AuxPlugInNum];
	
	for (int i = 0; i < m_AuxPlugInNum; i++)
	{
		//Buf.Format("%i", i);
		str[i].Format("PlugIns/TestASA/Aux4Ch%i%s", i+2, ".dll");
		hinstLibArr[i] = LoadLibrary(str[i]);
	}

	//str[1].Format("PlugIns/TestASA/Aux4Ch%i%s", 3, ".dll");
	//hinstLibArr[1] = LoadLibrary(str[1]);

	


	//hinstLib = LoadLibrary("PlugIns/TestASA/Aux4Ch2.dll");
	//if (hinstLib == NULL) {
	//	//cout << "ERROR: unable to load DLL\n";
	//	//return 1;
	//	//MessageBox
	//	//TextOut(hDC, 20, 100, "Error find func", strlen("Error find func"));
	//	MessageBoxA(NULL, "Error", "Error Load Aux4Ch2 Dll", IDOK);
	//	//cin >> n1;
	//}

	//hinstLib2 = LoadLibrary("PlugIns/TestASA/Aux4Ch3.dll");
	//if (hinstLib == NULL) {
	//	//cout << "ERROR: unable to load DLL\n";
	//	//return 1;
	//	//MessageBox
	//	MessageBoxA(NULL, "Error", "Error Load Aux4Ch3 Dll", IDOK);
	//	//cin >> n1;
	//}


	return(UNIQUE_PLUGIN_ID);	// return the unique TYPE identification of this plugin
}

//************************************************************************************
// Create a NEW plug-in object class 
// (called by BioTrace)
//************************************************************************************


extern "C" __declspec(dllexport) BOOL CreatePlugInObject(DWORD dwObjectIndex, char * szScreenFilePath, HWND hWindowHandle)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Copy WINDOW HANDLE 
	g_hWnd = hWindowHandle;
	return(TRUE);
}


//************************************************************************************
// Clean up (destroy) the plug in class after use. 
// (called by BioTrace)
//************************************************************************************

extern "C" __declspec(dllexport) BOOL DestroyPlugInObject(DWORD dwObjectIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// выгружаем вспомогательные библиотеки

	for (int i = 0; i < m_AuxPlugInNum; i++)
	{
		FreeLibrary(hinstLibArr[i]);
		//FreeLibrary(hinstLib);
		//FreeLibrary(hinstLib2);
	}
	
//	TestBody2.~ASATest();
//	UpdInfoVal.TextInfChan.clear();
	//UpdInfoVal.TextInfChan.shrink_to_fit();

	/*if (!UpdInfoVal.updInfChan.empty())
	{
		UpdInfoVal.updInfChan.clear();
		UpdInfoVal.updInfChan.shrink_to_fit();
	}
	if (!UpdInfoVal.TextInfChan.empty())
	{
		UpdInfoVal.TextInfChan.clear();
		UpdInfoVal.TextInfChan.shrink_to_fit();
	}
	

	
	if (!NameChannelSecDll.TextInfCh.empty())
	{
		NameChannelSecDll.TextInfCh.clear();
		NameChannelSecDll.TextInfCh.shrink_to_fit();
	}

	if (!NameChannelSecDll.valChannel.empty())
	{
		NameChannelSecDll.valChannel.clear();		
		NameChannelSecDll.valChannel.shrink_to_fit();
	}*/

	//delete[] NameChannelSecDll;
	return(TRUE);
}


//************************************************************************************
// More cleaning up.......this is where you release buffers/memory allocations
// (called by BioTrace)
//************************************************************************************

extern "C" __declspec(dllexport) BOOL ExitPlugInDLL(HINSTANCE hDLL)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//AsaDlgClass.DestroyWindow();
	
	// Expand this to all instances that were created...!
	DestroyPlugInObject(0);

	return(TRUE);	// All OK
}

//************************************************************************************
// if there is any limitation in data channels your plugin can handle (simulatenously)
// this is where you return the number
// (called by BioTrace)
//************************************************************************************

extern "C" __declspec(dllexport) DWORD GetMaxChannels(DWORD dwObjectIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	return(6);	// Default max 1 data channel
}


//************************************************************************************
// Sometimes a plug-in is LINKED to another instrument (NOT to a data channel directly)
// in that case the data is provided from the other (linked) instruments data channel
// (called by BioTrace)
//************************************************************************************


extern "C" __declspec(dllexport) BOOL SetNoOfInstrumentLinks(DWORD dwObjectIndex, DWORD NumOfInstruments)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//g_nLinkedInstruments = (int)NumOfInstruments;

	/*if (g_nLinkedInstruments > MAX_LINKEDINSTRUMENTS)
	{
		g_nLinkedInstruments = MAX_LINKEDINSTRUMENTS;
	}*/
	//testOut(dwObjectIndex, NumOfInstruments);
	return(TRUE);
}



//************************************************************************************
// Set the text description of the linked instrument.
// (called by BioTrace)
//************************************************************************************
// Maximum number of instruments (threshold and/or data channels) that this instruments supports
#define MAX_LINKEDINSTRUMENTS	4
char  g_szTextArray[MAX_LINKEDINSTRUMENTS][64];

extern "C" __declspec(dllexport) BOOL SetLinkText(DWORD dwObjectIndex, DWORD dwLink, char *szLinkText)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Valid LINK index?
	if (dwLink >= 0 && dwLink < MAX_LINKEDINSTRUMENTS)
	{
		// Copy the text description for this LINK:
		// (Add check if there is sufficient space , re: the 64 byte size)
		sprintf(g_szTextArray[dwLink], "%s", szLinkText);
	}
	testOut(dwObjectIndex, dwLink);
	// наименование подключенных каналов

	// сбрасываем вектор, т.к. SetLinkText может вызываться не единожды
	UpdInfoVal.TextInfChan.clear();
	UpdInfoVal.TextInfChan.shrink_to_fit();
	for (int i1 = 0; i1 <= dwLink; i1++)
	{
		UpdInfoVal.TextInfChan.push_back(g_szTextArray[i1]);
		UpdInfoVal.TextInfChan[i1].Delete(0, (UpdInfoVal.TextInfChan[i1 ].Find('.') + 1));// удаляем название инструмента, оставляя только название канала

	}

	// вызываем функции из вспомогательных dll для получения размера векторов


	for (int i = 0;i < m_AuxPlugInNum; i++)
	{
		func2dllArr[i] = (importFunction)GetProcAddress(hinstLibArr[i], "ExportData");
		
		
		if (func2dllArr[i] != NULL)
		{
			NameChannelSecDll = func2dllArr[i]();//.. 

			for (int i1 = 0; i1 < NameChannelSecDll.TextInfCh.size();i1++)
			{
				UpdInfoVal.TextInfChan.push_back(NameChannelSecDll.TextInfCh[i1]);
			}
		}
		

	}

	UpdInfoVal.updInfChan.resize(UpdInfoVal.TextInfChan.size());
	/*UpdInfoVal.TextInfChan[0] = g_szTextArray[0];
	UpdInfoVal.TextInfChan[1] = g_szTextArray[1];
	UpdInfoVal.TextInfChan[2] = g_szTextArray[2];
	UpdInfoVal.TextInfChan[3] = g_szTextArray[3];*/
	
	/*for (int i0 = 0; i0 < MAX_LINKEDINSTRUMENTS; i0++)
	{

	}*/

	//UpdInfoVal.TextInfChan0.Delete(0, (UpdInfoVal.TextInfChan0.Find('.') + 1)); // удаляем название инструмента, оставляя только название канала
	//UpdInfoVal.TextInfChan1.Delete(0, (UpdInfoVal.TextInfChan1.Find('.') + 1)); // + 1 т.к. нужно удалить вместе со знаком '.'
	//UpdInfoVal.TextInfChan2.Delete(0, (UpdInfoVal.TextInfChan2.Find('.') + 1));
	//UpdInfoVal.TextInfChan3.Delete(0, (UpdInfoVal.TextInfChan3.Find('.') + 1));
	//UpdInfoVal.TextInfChan4.Delete(0, (UpdInfoVal.TextInfChan4.Find('.') + 1));
	//strlen(g_szTextArray[0]);

	return(0);
}



//************************************************************************************
// This is the PAINT function that clears/refreshed the background of the plugin
// (called by BioTrace during PAINT of the main screen)
//************************************************************************************

extern CString SelCard;
CString lastNum;

extern "C" __declspec(dllexport) BOOL PaintPlugIn(DWORD dwObjectIndex)
{
	RECT rc;
	//HGDIOBJ hStockObject, hOldObject;

	// Get a valid device context (DC)
	HDC hDC = GetDC(g_hWnd);

	// Get the SIZE of the window we are using for this plug in
	GetClientRect(g_hWnd, &rc);
	imgPlugIn.AlphaBlend(hDC, 0, 0, rc.right, rc.bottom, 0, 0, imgPlugIn.GetWidth(), imgPlugIn.GetHeight()); // выводим изображение фона на окно
	
	// вывод текста
	//CRect rect;
	

	

	//
	//rect.left = 20;
	//rect.top = 90;
	//rect.right = 200;
	//rect.bottom = 115;


	//DrawText(hDC, _T("Pictures: " + lastNum), 13, &rect, DT_CENTER | DT_NOPREFIX | DT_VCENTER);//| DT_WORDBREAK

	//rect.left = 20;
	//rect.top = 120;
	//rect.right = 200;
	//rect.bottom = 145;
	//DrawText(hDC, _T(SelCard), SelCard.GetLength(), &rect, DT_CENTER  | DT_NOPREFIX | DT_VCENTER);//| DT_WORDBREAK
	
	//CString csStr;
	
	
	
	SetBkMode(hDC,TRANSPARENT); // убираем фон в тексте

	SetTextColor(hDC, RGB(250, 20, 0)); // изменяем цвет текста
	
	TextOut(hDC, 20, 40, TestBody2.GetActualNumPic(), TestBody2.GetActualNumPic().GetLength());
	
	lastNum.Format("Pictures: \%i", TestBody2.GetSizeVec());//"The number of remaining pictures: " +
	TextOut(hDC, 20, 60, lastNum, lastNum.GetLength());

	//csStr = "Pictures: " + lastNum;
	TextOut(hDC, 20, 90, SelCard, SelCard.GetLength());


	
	//
	//// Get a drak gray for a standard background
	//hStockObject = GetStockObject(DKGRAY_BRUSH);		// WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH, DKGRAY_BRUSH, BLACK_BRUSH
	//hOldObject = SelectObject(hDC, hStockObject);

	//// Draw a rectangle the size of the entire window
	//Rectangle(hDC, rc.left, rc.top, rc.right, rc.bottom);

	//// Restore object
	//SelectObject(hDC, hOldObject);

	// Release the device context
	ReleaseDC(g_hWnd, hDC);

	// Return
	return(TRUE);
}

void redrawPlugIn(CString url)
{
	imgPlugIn.Destroy();
	imgPlugIn.Load(_T(url));
	//ReleaseDC(g_hWnd, hDC);
	PaintPlugIn(0);
}

//************************************************************************************
// This is the MAIN update function that is DOING the data display and processing
// You minimally need to put some code in here, in order to do anything.
// (called by BioTrace about 15-20 times per second)
//************************************************************************************

// расчет количества символов в числе
int numOfDigits(int number)
{
	int result = 0;

	while (number != 0)
	{
		number /= 10;
		result++;
	}

	return result;
}



float val1 = 0;
extern "C" __declspec(dllexport) BOOL  UpdatePlugIn(DWORD dwObjectIndex, struct UpdateInfo *psUInfo)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Valid data structure?
	if (psUInfo == NULL)
	{
		MessageBeep(0);
		return(FALSE);
	}


	//std::ofstream out1("PlugIns/TestASA/TestOutUpd.csv", std::ios::app);
	//out1 << "\n" << psUInfo->dRangeStart << " psUInfo->dRange: " << psUInfo->dRangeEnd << "\n";
	//out1 << "\n" << "psUInfo->dwNewSamples: " << psUInfo->dwNewSamples << "\n"
	//	<< "psUInfo->dDataVal: " << psUInfo->dDataVal << "\n";

	//	/*<< "psUInfo->pdDataArray1: " << psUInfo->pdDataArray[1] << "\n"
	//	<< "psUInfo->pdDataArray2: " << psUInfo->pdDataArray[2] << "\n"
	//	<< "psUInfo->pdDataArray3: " << psUInfo->pdDataArray[3] << "\n";*/
	//for (int i1 = 0; i1 < 10; i1++)
	//{
	//	out1 << psUInfo->pdDataArray[i1] << ";";// "\n";
	//}
	//out1.close();



	HDC hDC = GetDC(g_hWnd);
	
	//GetClientRect(g_hWnd, &rect);
	//imgPlugIn.AlphaBlend(hDC, 0, 0, rect.right, rect.bottom, 0, 0, imgPlugIn.GetWidth(), imgPlugIn.GetHeight()); // выводим изображение фона на окно
	CString csStr;
	char* valLen;
	// this prints the supplied data channel value.
	// To normalize, take the ratio of the data channel value and the (psUInfo->dRangeEnd-psUInfo->dRangeStart)
	// you yourself are responsible for testing the supplied psUInfo->dDataVal for exceeding limits
	// of the supplied range
	//csStr.Format("Sample DATA = %5.3f (g_hWnd = %d)", psUInfo->dDataVal, g_hWnd);
	
	//csStr.Format("Sample DATA = %5.3f", psUInfo->dDataVal);
	
	//SetBkMode(hDC, TRANSPARENT); // убираем фон в тексте
	//SetBkMode(hDC, TRANSPARENT); // убираем фон в тексте

	//SetTextColor(hDC, RGB(250, 20, 0)); // изменяем цвет текста
	//SetTextColor(hDC, RGB(250, 20, 0)); // изменяем цвет текста
	val1 = psUInfo->dDataVal;
	//csStr.Format("Sample DATA = %5.3f", val1);
	switch (psUInfo->dwChanIndex)
	{
	case 0:
	{
		if (!UpdInfoVal.updInfChan.empty())
		{


			UpdInfoVal.updInfChan[0] = val1;
		

			csStr.Format("%s" "%s" "%5.3f", UpdInfoVal.TextInfChan[0], " = ", val1);
			//csStr.Format("Sample DATA = %5.3f", val1);

			TextOut(hDC, 20, 120, csStr, strlen(UpdInfoVal.TextInfChan[0]) + numOfDigits(val1) + 6); // выводим текст в заданные координаты с длиной выводимой области равной длине строки массива
		}																		// +6 это 3 числа после запятой и 3 знака в " = "
	}
	break;
	case 1:
	{
		//csStr.Format("Sample DATA = %5.3f", val1);
		if (!UpdInfoVal.updInfChan.empty())
		{
			UpdInfoVal.updInfChan[1] = val1;
			csStr.Format("%s" "%s" "%5.3f", UpdInfoVal.TextInfChan[1], " = ", UpdInfoVal.updInfChan[1]);
			TextOut(hDC, 20, 140, csStr, strlen(UpdInfoVal.TextInfChan[1]) + numOfDigits(UpdInfoVal.updInfChan[1]) + 6);
		}
	}
	break;
	case 2:
	{
		if (!UpdInfoVal.updInfChan.empty())
		{
			UpdInfoVal.updInfChan[2] = val1;
			csStr.Format("%s" "%s" "%5.3f", UpdInfoVal.TextInfChan[2], " = ", val1);
			TextOut(hDC, 20, 160, csStr, strlen(UpdInfoVal.TextInfChan[2]) + numOfDigits(val1) + 6);
		}
	}
	break;
	case 3:
	{
		//csStr.Format("Sample DATA = %5.3f", val1);
		if (!UpdInfoVal.updInfChan.empty())
		{
			UpdInfoVal.updInfChan[3] = val1;
			csStr.Format("%s" "%s" "%5.3f", UpdInfoVal.TextInfChan[3], " = ", val1);
			TextOut(hDC, 20, 180, csStr, strlen(UpdInfoVal.TextInfChan[3]) + numOfDigits(val1) + 6);
		}
	}
	break;
	
	default:
		break;
	}
	



	// выводим показания со вспомогательных плагинов


	for (int i = 0;i < m_AuxPlugInNum; i++)//
	{
		func2dllArr[i] = (importFunction)GetProcAddress(hinstLibArr[i], "ExportData");


		if (func2dllArr[i] != NULL)
		{
			NameChannelSecDll = func2dllArr[i]();//.. 

			csStr.Format("Aux %i %s", i+2, "dll:");
			TextOut(hDC, 20, 220 + 100 * i, csStr, csStr.GetLength());
				if (NameChannelSecDll.isInclude)
				{

					for (int i1 = 0; i1 < NameChannelSecDll.TextInfCh.size();i1++)
					{
						UpdInfoVal.updInfChan[4 + 4*i + i1] = NameChannelSecDll.valChannel[i1]; // добавляем значения из вспомогательной dll в основной вектор с данными
						csStr.Format("%s" "%s" "%5.3f", NameChannelSecDll.TextInfCh[i1], " = ", NameChannelSecDll.valChannel[i1]);
						TextOut(hDC, 20, 240 + i1 * 20 + 100*i, csStr, strlen(NameChannelSecDll.TextInfCh[i1]) + numOfDigits(NameChannelSecDll.valChannel[i1]) + 6);

					}
				}
		}
		else
		{
			TextOut(hDC, 20, 200, "Error find ExportData func", strlen("Error find ExportData func"));
		}



	}

	ReleaseDC(g_hWnd, hDC);
	
	return(0);
}

//************************************************************************************
// This is the function that is called by BioTrace when the user wants to EDIT
// the properties of the plug-in. It will bring up your own dialogbox code that you
// code in "PlugInDialogBox.cpp"
//
// (called by BioTrace when user clicks on EDIT menu)
//************************************************************************************

extern "C" __declspec(dllexport) BOOL  EditPlugInSettings(DWORD dwObjectIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//SettingDlg.ShowSettings();
	//delete m_SettingDlg;
	m_SettingDlg.DoModal();
	
		
	
	


	//m_SettingDlg.ShowWindow(SW_SHOW); // показываем окно настроек
	//AsaDlgClass.ShowASA();
	//AsaDlgClass.DoModal();
	//ShowASA();
	//ShowSettings();
	// Show the dialog box handling all plugin specific settings
	// The code for this can be found in PlugInDialogBox.cpp
	//ShowPlugInDialogBox();

	return(0);
}

//***********************************************************************
// The multimedia plugin functions for starting/stopping media display
// in case your plug-in should use the RECORD/REPLAY/PAUSE buttons
//***********************************************************************

bool StartRecorPlay = false;// проверка на запуск записи
// Start to "PLAY" your content/media
extern "C" __declspec(dllexport) BOOL  Play(DWORD dwObjectIndex, char *szSessionDirectory)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	StartRecorPlay = true;
	return(0);
}

// Stop PLAYING/RECORDING your content/media
extern "C" __declspec(dllexport) BOOL  Stop(DWORD dwObjectIndex)
{
	StartRecorPlay = false;
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return(0);
}

// Pause PLAYING/RECORDING your content/media
extern "C" __declspec(dllexport) BOOL  Pause(DWORD dwObjectIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return(0);
}

// Resume PLAYING/RECORDING your content/media
extern "C" __declspec(dllexport) BOOL  Resume(DWORD dwObjectIndex)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return(0);
}

// Start RECORDING your content/media
extern "C" __declspec(dllexport) BOOL  Record(DWORD dwObjectIndex, char *szSessionDirectory)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	StartRecorPlay = true;
	return(0);
}