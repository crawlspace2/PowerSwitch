#include <Windows.h>
#include "NvDRS_Setting.h"

using namespace NvInterop;

/// <summary>
/// Default constructor.
/// </summary>
NvDRS_Setting::NvDRS_Setting() : m_pSetting( new NVDRS_SETTING )
{
  InitializeComponent();
}

/// <summary>
/// Construct from pointer.
/// Note that class instance takes ownership of pointed-to data.
/// </summary>
NvDRS_Setting::NvDRS_Setting( NVDRS_SETTING* pSetting ) : m_pSetting( pSetting )
{
  InitializeComponent();
}

/// <summary>
/// Construct by copying argument into member data.
/// </summary>
NvDRS_Setting::NvDRS_Setting( const NVDRS_SETTING& pSetting ) : m_pSetting( new NVDRS_SETTING )
{
  memcpy_s( m_pSetting, sizeof(m_pSetting), &pSetting, sizeof(pSetting) );  
  InitializeComponent();
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
/// Clean up any managed resources being used.
/// </summary>
NvDRS_Setting::~NvDRS_Setting()
{
  if ( components )
  {
    delete components;
  }
  // Clean up unmanaged resourced
  this->!NvDRS_Setting();
}

/// <summary>
/// Clean up any unmanaged resources being used.
/// </summary>
NvDRS_Setting::!NvDRS_Setting()
{
  if ( 0 != m_pSetting )
  {
    delete m_pSetting;
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

/// <summary>
/// Helper to copy native structured data to managed
/// </summary>
NvdrsBinarySetting^ CopyBinarySetting( const NVDRS_SETTING_TYPE& settingType, const NVDRS_BINARY_SETTING& nativeSetting )
{
  NvdrsBinarySetting^ pManagedSetting = gcnew NvdrsBinarySetting();
  if ( settingType == NVDRS_BINARY_TYPE )
  {
    pManagedSetting->valueLength = static_cast<System::UInt32>( nativeSetting.valueLength );
    // pre-allocate the array before copying
    pManagedSetting->valueData = gcnew array<System::Byte>( pManagedSetting->valueLength );
    for ( std::size_t idx = 0; idx < pManagedSetting->valueLength; ++idx )
    {
      pManagedSetting->valueData[idx] = static_cast<System::Byte>( nativeSetting.valueData[idx] );
    }
  }
  else
  {
    pManagedSetting->valueData = gcnew array<System::Byte>(0);
  }
  return pManagedSetting;
}

/// <summary>
/// Helper to copy native string data
/// </summary>
System::String^ CopyString( const NVDRS_SETTING_TYPE& settingType, const NvAPI_UnicodeString& nativeString )
{
  if ( settingType == NVDRS_STRING_TYPE ||
    settingType == NVDRS_WSTRING_TYPE )
  {
    return gcnew System::String( (wchar_t*)nativeString );
  }
  return "";
}

/// <summary>
/// Returns a managed copy/equivalent of the native structure
/// </summary>
NvdrsBinarySetting^ NvDRS_Setting::binaryPredefinedValue::get()
{
  return CopyBinarySetting( m_pSetting->settingType, m_pSetting->binaryPredefinedValue );
}

System::String^ NvDRS_Setting::wszPredefinedValue::get()
{
  return CopyString( m_pSetting->settingType, m_pSetting->wszPredefinedValue );
}

System::UInt32 NvDRS_Setting::u32CurrentValue::get()
{
  return static_cast<System::UInt32>( m_pSetting->u32CurrentValue );
}

/// <summary>
/// Returns a managed copy/equivalent of the native structure
/// </summary>
NvdrsBinarySetting^ NvDRS_Setting::binaryCurrentValue::get()
{
  return CopyBinarySetting( m_pSetting->settingType, m_pSetting->binaryCurrentValue );
}

System::String^ NvDRS_Setting::wszCurrentValue::get()
{
  return CopyString( m_pSetting->settingType, m_pSetting->wszCurrentValue );
}