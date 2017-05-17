#pragma once

#include "nvapi.h"
#include "NvDRS_Setting.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;

namespace NvInterop {

  public value struct ErrorInfo {
  public:
    NvAPI_Status    status;
    System::String^ method;
  };

	/// <summary>
	/// Summary for NvAPI_Interop
	/// </summary>
	public ref class NvAPI_Interop : public System::ComponentModel::Component
	{
	public:
    NvAPI_Interop();
		NvAPI_Interop( System::ComponentModel::IContainer^ container );

    System::Boolean Init();
    System::Boolean CreateSession();
    System::Boolean DestroySession();
    System::Boolean LoadSettings();
    System::Boolean GetGlobalProfile();
    System::Boolean EnumSettings( array<NvDRS_Setting^>^ drsSettings );
    System::Boolean GetSetting( System::UInt32 settingId, NvDRS_Setting^ drsSetting );
    System::String^ GetErrMsg();
    
	protected:
    ~NvAPI_Interop();
    !NvAPI_Interop();

	private:
    bool               m_Init;
    NvDRSSessionHandle m_hSession;
    NvDRSProfileHandle m_hProfile;
    ErrorInfo          m_lastErrInfo;


		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent()
		{
			components = gcnew System::ComponentModel::Container();
		}
#pragma endregion
	};
}
