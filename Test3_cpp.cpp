#include "Test3_cpp.h"

namespace DemoTest
{

	void VerifyDomainUserUtil::VerifyDomainUser()
	{
		int iRet = 0;
		bool bBreakLoop = false;
		std::wstring temp = L"";
		std::wstring strmsg = L"";

		try
		{
			while (bBreakLoop == false)
			{
				iRet = GetCredentials();

				if (iRet == 0)
				{
					if (VerifyDomainUserCredentials())
					{
						bBreakLoop = true;
						bVerificationResult = true;
					}
				}
			}
		}
		catch (const std::runtime_error &ex)
		{
			std::wcout << L"exception: " << ex.what() << std::endl;
		}
	}

	int VerifyDomainUserUtil::GetCredentials()
	{
		int iRet = 0;
		CREDUI_INFO credui = CREDUI_INFO();

		Window *window = Window::GetWindow(this->Owner);
		auto wih = new WindowInteropHelper(window);
		std::any hWnd = wih->Handle;
		credui.hwndParent = hWnd;

		std::wstring temp = L"";
		credui.pszCaptionText = L"Demo";
		credui.pszMessageText = L"Demo Message";

		credui.cbSize = Marshal::SizeOf(credui);
		unsigned int authPackage = 0;
		std::any outCredBuffer = std::any();
		unsigned int outCredSize = 0;
		bool save = false;
		int result = ERROR_CANCELLED;
		int flags = CREDUIWIN_GENERIC;

		std::wstring username = strInputADCredUsername;
		std::wstring password = strInputADCredPassword;
		int inCredSize = 0;
		std::any inCredBuffer = std::any::Zero;
		bool bCredPack = false;

		if (!username.empty())
		{
			bCredPack = CredPackAuthenticationBuffer(CRED_PACK_PROTECTED_CREDENTIALS, username, password, inCredBuffer, inCredSize);
			if (!bCredPack)
			{
				inCredBuffer = Marshal::AllocCoTaskMem(inCredSize);
				bCredPack = CredPackAuthenticationBuffer(0, username, password, inCredBuffer, inCredSize);
				if (!bCredPack)
				{
					std::wcout << L"Pack authentication buffer failed" << std::endl;
				}
			}
		}

		try
		{
			if (bCredPack)
			{
				result = CredUIPromptForWindowsCredentials(credui, 0, authPackage, inCredBuffer, static_cast<unsigned int>(inCredSize), outCredBuffer, outCredSize, save, flags);

				if (inCredBuffer != std::any::Zero)
				{
					Marshal::FreeCoTaskMem(inCredBuffer);
				}
			}

		}
		catch (const std::runtime_error &ex)
		{
			std::wcout << L"Get credentials input failed" << std::endl;
		}

		if (result == 0)
		{
			auto usernameBuf = new StringBuilder(0x100);
			auto passwordBuf = new StringBuilder(0x100);
			auto domainBuf = new StringBuilder(0x100);

			int maxUserName = 0x100;
			int maxDomain = 0x100;
			int maxPassword = 0x100;

			if (CredUnPackAuthenticationBuffer(CRED_PACK_PROTECTED_CREDENTIALS, outCredBuffer, outCredSize, usernameBuf, maxUserName, domainBuf, maxDomain, passwordBuf, maxPassword))
			{
				CoTaskMemFree(outCredBuffer);
				bSaveCredentials = save;
				strDomainUserName = usernameBuf->toString();
				strDomainUserPWD = passwordBuf->toString();
				strDomainName = domainBuf->toString();

				// If appending string "test" into password in credential dialog,
				// then here I will get "SAVED_PASSWORDtest" string
				strInputADCredUsername = strDomainUserName;
				strInputADCredPassword = strDomainUserPWD;
			}

//C# TO C++ CONVERTER TODO TASK: A 'delete domainBuf' statement was not added since domainBuf was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete passwordBuf' statement was not added since passwordBuf was passed to a method or constructor. Handle memory management manually.
//C# TO C++ CONVERTER TODO TASK: A 'delete usernameBuf' statement was not added since usernameBuf was passed to a method or constructor. Handle memory management manually.
		}

		delete wih;
	}

	bool VerifyDomainUserUtil::VerifyDomainUserCredentials()
	{
		bool bVerifyDomainUser = false;

		try
		{
			PrincipalContext *pc = new PrincipalContext(ContextType::Domain, strDomainName, strDomainUserName, strDomainUserPWD);
			bVerifyDomainUser = pc->ValidateCredentials(strDomainUserName, strDomainUserPWD, ContextOptions->Negotiate);

			delete pc;
		}
		catch (const std::runtime_error &ex)
		{
			std::wcout << L"exception: " << ex.what() << std::endl;
		}

		return bVerifyDomainUser;
	}
}