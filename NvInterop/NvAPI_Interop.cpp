#include <Windows.h>
#include "NvAPI_Interop.h"
#include "NvApiDriverSettings.h"

#include <vector>

#define METHOD __FUNCTION__

using namespace NvInterop;

NvAPI_Interop::NvAPI_Interop() :
  m_Init(false),
  m_hSession(0),
  m_hProfile(0)
{
  InitializeComponent();
}

/// <summary>
/// Required for Windows.Forms Class Composition Designer support
/// </summary>
NvAPI_Interop::NvAPI_Interop( System::ComponentModel::IContainer^ container ) :
  m_Init(false),
  m_hSession(0),
  m_hProfile(0)
{
  container->Add( this );
  InitializeComponent();
}

/// <summary>
/// Clean up any managed resources being used.
/// </summary>
NvAPI_Interop::~NvAPI_Interop()
{
  if ( components )
  {
    delete components;
  }
  // Clean up unmanaged resources
  this->!NvAPI_Interop();
}

/// <summary>
/// Clean up any unmanaged resources being used.
/// </summary>
NvAPI_Interop::!NvAPI_Interop()
{
  // Destroy the NVAPI session (if applicable)
  DestroySession();
}

/// <summary>
/// Initialize the NVAPI
/// </summary>
System::Boolean NvAPI_Interop::Init()
{ 
  NvAPI_Status ret = NVAPI_ERROR;
  if ( !m_Init )
  {
    ret = NvAPI_Initialize();
  }
  else
  {
    // NVAPI already initialized
  }
  if ( NVAPI_OK != ret ) {
    m_lastErrInfo.status = ret;
    m_lastErrInfo.method = gcnew System::String( METHOD );
  }
  return ( NVAPI_OK == ret );
}

/// <summary>
/// Create the Session
/// </summary>
System::Boolean NvAPI_Interop::CreateSession()
{
  NvAPI_Status ret = NVAPI_ERROR;
  if ( m_hSession == 0 )
  {
    pin_ptr<NvDRSSessionHandle> hSession = &m_hSession;
    ret = NvAPI_DRS_CreateSession( hSession );
  }
  else
  {
    // Session already created
  }
  if ( NVAPI_OK != ret ) {
    m_lastErrInfo.status = ret;
    m_lastErrInfo.method = gcnew System::String( METHOD );
  }
  return ( NVAPI_OK == ret );
}

/// <summary>
/// Destroy the Session
/// </summary>
System::Boolean NvAPI_Interop::DestroySession()
{
  NvAPI_Status ret = NVAPI_ERROR;
  if ( m_hSession != 0 )
  {
    ret = NvAPI_DRS_DestroySession( m_hSession );
    m_hSession = 0;
  }
  if ( NVAPI_OK != ret )  {
    m_lastErrInfo.status = ret;
    m_lastErrInfo.method = gcnew System::String( METHOD );
  }
  return ( NVAPI_OK == ret );
}

/// <summary>
/// Load the settings data
/// </summary>
System::Boolean NvAPI_Interop::LoadSettings()
{
  NvAPI_Status ret = NvAPI_DRS_LoadSettings( m_hSession );
  if ( NVAPI_OK != ret )  {
    m_lastErrInfo.status = ret;
    m_lastErrInfo.method = gcnew System::String( METHOD );
  }
  return ( NVAPI_OK == ret );
}

/// <summary>
/// Get the current Global Profile
/// </summary>
System::Boolean NvAPI_Interop::GetGlobalProfile()
{
  NvAPI_Status ret = NVAPI_ERROR;
  pin_ptr<NvDRSProfileHandle> hProfile = &m_hProfile;
  ret = NvAPI_DRS_GetCurrentGlobalProfile( m_hSession, hProfile );
  if ( NVAPI_OK != ret )  {
    m_lastErrInfo.status = ret;
    m_lastErrInfo.method = gcnew System::String( METHOD );
  }
  return ( NVAPI_OK == ret );
}

/// <summary>
/// Enumerate the Settings
/// </summary>
System::Boolean NvAPI_Interop::EnumSettings( array<NvDRS_Setting^>^ drsSettings )
{
  NvAPI_Status ret = NVAPI_ERROR;

  // get profile info
  NVDRS_PROFILE profileInfo;
  profileInfo.version = NVDRS_PROFILE_VER;
  ret = NvAPI_DRS_GetProfileInfo( m_hSession, m_hProfile, &profileInfo );

  if ( NVAPI_OK == ret )
  {
    // enumerate the settings
    NvU32 numOfSettings = profileInfo.numOfSettings;
    // allocate dynamic-sized array to hold settings
    //std::vector<NVDRS_SETTING> drsSettingArray( static_cast<std::size_t>(numOfSettings) );
    NVDRS_SETTING* drsSettingArray = new NVDRS_SETTING[static_cast<std::size_t>(numOfSettings)];
    drsSettingArray[0].version = NVDRS_SETTING_VER;
    //ret = NvAPI_DRS_EnumSettings( m_hSession, m_hProfile, 0, &numOfSettings, drsSettingArray.data() );
    ret = NvAPI_DRS_EnumSettings( m_hSession, m_hProfile, 0, &numOfSettings, drsSettingArray );

    drsSettings = gcnew array<NvDRS_Setting^>( static_cast<std::size_t>(numOfSettings) );
    for ( std::size_t idx = 0; idx < static_cast<std::size_t>(numOfSettings); ++idx )
    {
      drsSettings[idx] = gcnew NvDRS_Setting(drsSettingArray[idx]); //copy
    }
  }

  if ( NVAPI_OK != ret )  {
    m_lastErrInfo.status = ret;
    m_lastErrInfo.method = gcnew System::String( METHOD );
  }
  return ( NVAPI_OK == ret );
}

/// <summary>
/// Get the Setting Info
/// </summary>
System::Boolean NvAPI_Interop::GetSetting( System::UInt32 settingId, NvDRS_Setting^ drsSetting )
{
  NVDRS_SETTING* pSetting = drsSetting->GetNativePtr();
  pSetting->version = NVDRS_SETTING_VER;
  NvU32 id = static_cast<NvU32>( settingId );
  NvAPI_Status ret = NvAPI_DRS_GetSetting( m_hSession, m_hProfile, id, pSetting );
  if ( NVAPI_OK != ret )  {
    m_lastErrInfo.status = ret;
    m_lastErrInfo.method = gcnew System::String( METHOD );
  }
  return ( NVAPI_OK == ret );
}

/// <summary>
/// Get the current Global Profile.
/// Note: Fails if the NVAPI has not been initialized
/// </summary>
System::String^ NvAPI_Interop::GetErrMsg()
{
  NvAPI_ShortString szDesc = {0};
  NvAPI_Status ret = NvAPI_GetErrorMessage( m_lastErrInfo.status, szDesc );
  if ( NVAPI_OK != ret ) {
    return System::String::Format( "{0}: Could not decode error message (0x{1:X8}).",
      m_lastErrInfo.method,
      static_cast<System::UInt32>( m_lastErrInfo.status ) );
  }
  return System::String::Format( "{0}(): {1}",
    m_lastErrInfo.method,
    gcnew System::String(szDesc) );
}
