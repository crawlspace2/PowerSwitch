#pragma once

#include "nvapi.h"
#include <memory>

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;

namespace NvInterop {

  public enum class NvdrsSettingType
  {
    NVDRS_DWORD_TYPE,
    NVDRS_BINARY_TYPE,
    NVDRS_STRING_TYPE,
    NVDRS_WSTRING_TYPE
  };

  public enum class NvdrsSettingLocation
  {
    NVDRS_CURRENT_PROFILE_LOCATION,
    NVDRS_GLOBAL_PROFILE_LOCATION,
    NVDRS_BASE_PROFILE_LOCATION,
    NVDRS_DEFAULT_PROFILE_LOCATION
  };

  public struct NvdrsBinarySetting
  {
    //System::UInt32 valueLength;
    //System::Byte   valueData[NVAPI_BINARY_DATA_MAX];
    NvU32 valueLength;
    NvU8  valueData[NVAPI_BINARY_DATA_MAX];
  };

	/// <summary>
	/// Summary for NvAPISetting
	/// </summary>
	public ref class NvDRS_Setting :  public System::ComponentModel::Component
	{
	public:
    NvDRS_Setting( void );
    NvDRS_Setting( System::ComponentModel::IContainer^ container );
    NVDRS_SETTING* GetNativePtr();

    property System::UInt32 version { System::UInt32 get(); };
    property System::String^ settingName { System::String^ get(); };
    property System::UInt32 settingId { System::UInt32 get(); };
    property NvdrsSettingType settingType { NvdrsSettingType get(); };
    property NvdrsSettingLocation settingLocation { NvdrsSettingLocation get(); };
    property System::UInt32 isCurrentPredefined { System::UInt32 get(); };
    property System::UInt32 isPredefinedValid { System::UInt32 get(); };
    property System::UInt32 u32PredefinedValue { System::UInt32 get(); };
    property NvdrsBinarySetting binaryDefaultValue { NvdrsBinarySetting get(); };

	protected:
    ~NvDRS_Setting();

	private:
    NVDRS_SETTING* m_pSetting;

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
