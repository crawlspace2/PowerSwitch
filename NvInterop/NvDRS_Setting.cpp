#include <Windows.h>
#include "NvDRS_Setting.h"

using namespace NvInterop;

NvDRS_Setting::NvDRS_Setting() : m_pSetting( new NVDRS_SETTING )
{
  InitializeComponent();
  //
  //TODO: Add the constructor code here
  //
}

NvDRS_Setting::NvDRS_Setting( System::ComponentModel::IContainer^ container )
{
  /// <summary>
  /// Required for Windows.Forms Class Composition Designer support
  /// </summary>

  container->Add( this );
  InitializeComponent();
}

/// <summary>
/// Clean up any resources being used.
/// </summary>
NvDRS_Setting::~NvDRS_Setting()
{
  if ( 0 != m_pSetting )
  {
    delete m_pSetting;
  }

  if ( components )
  {
    delete components;
  }
}

/// <summary>
/// Get native pointer to member structure.
/// </summary>
NVDRS_SETTING* NvDRS_Setting::GetNativePtr()
{
  return m_pSetting;
}

System::UInt32 NvDRS_Setting::version::get()
{
  return static_cast<System::UInt32>( m_pSetting->version );
}

System::String^ NvDRS_Setting::settingName::get()
{
  return gcnew System::String( (wchar_t*)m_pSetting->settingName );
}

System::UInt32 NvDRS_Setting::settingId::get()
{
  return static_cast<System::UInt32>( m_pSetting->settingId );
}

NvdrsSettingType NvDRS_Setting::settingType::get()
{
  return static_cast<NvdrsSettingType>(m_pSetting->settingType);
}

NvdrsSettingLocation NvDRS_Setting::settingLocation::get()
{
  return static_cast<NvdrsSettingLocation>( m_pSetting->settingLocation );
}

System::UInt32 NvDRS_Setting::isCurrentPredefined::get()
{
  return static_cast<System::UInt32>( m_pSetting->isCurrentPredefined );
}

System::UInt32 NvDRS_Setting::isPredefinedValid::get()
{
  return static_cast<System::UInt32>( m_pSetting->isPredefinedValid );
}

System::UInt32 NvDRS_Setting::u32PredefinedValue::get()
{
  return static_cast<System::UInt32>( m_pSetting->u32PredefinedValue );
}

NvdrsBinarySetting NvDRS_Setting::binaryDefaultValue::get()
{
  //return static_cast<NvdrsBinarySetting>( m_pSetting->binaryPredefinedValue );
  NvdrsBinarySetting setting;
  return setting;
}