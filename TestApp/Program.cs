using System;
//using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using NvInterop;

namespace TestApp
{
  
  public struct Test_Struct
  {
    public Int32 version;
  }

  class Program
  {
    const UInt32 PREFERRED_PSTATE_ID = 0x1057EB71;

    static void Main( string[] args )
    {
      NvAPI_Interop nvapi = new NvAPI_Interop();
      string ErrMsg = "";
      uint stage = 0;
      bool init = false;
      
      const uint MAX_STAGE = 5;

      while ( stage < 5 )
      {
        switch ( stage )
        {
          case 0:
            if ( !nvapi.Init() ) {
              ErrMsg = "Failed to initialize the NVAPI.";
              stage = MAX_STAGE;
            }
            else {
              init = true;
              stage++;
            }
            break;
          case 1:
            if ( !nvapi.CreateSession() ) {
              ErrMsg = "Failed to create the session.";
              stage = MAX_STAGE;
            }
            else {
              stage++;
            }
            break;
          case 2:
            if ( !nvapi.LoadSettings() ) {
              ErrMsg = "Failed to load the settings.";
              stage = MAX_STAGE;
            }
            else {
              stage++;
            }
            break;
          case 3:
            if ( !nvapi.GetGlobalProfile() ) {
              ErrMsg = "Failed to get the global profile.";
              stage = MAX_STAGE;
            }
            else {
              stage++;
            }
            break;
          case 4:
            NvDRS_Setting drsSetting = new NvDRS_Setting();
            if ( !nvapi.GetSetting( PREFERRED_PSTATE_ID, drsSetting ) ) {
              ErrMsg = "Failed to get the global profile.";
              stage = MAX_STAGE;
            }
            else {
              Console.WriteLine( String.Format( "Version: {0} (0x{1:X8})",
                drsSetting.version,
                drsSetting.version ) );
              Console.WriteLine( "Setting Name: " + drsSetting.settingName );
              Console.WriteLine( String.Format( "Setting Id: {0} (0x{1:X8})",
                drsSetting.settingId,
                drsSetting.settingId ) );
              Console.Write("Setting Type: ");
              switch ( drsSetting.settingType ) {
                case NvdrsSettingType.NVDRS_BINARY_TYPE:
                  Console.Write( "Binary" );
                  break;
                case NvdrsSettingType.NVDRS_DWORD_TYPE:
                  Console.Write( "Dword" );
                  break;
                case NvdrsSettingType.NVDRS_STRING_TYPE:
                  Console.Write( "String" );
                  break;
                case NvdrsSettingType.NVDRS_WSTRING_TYPE:
                  Console.Write( "Unicode" );
                  break;
              }
              Console.WriteLine();
              Console.Write( "Setting Location: " );
              switch ( drsSetting.settingLocation ) {
                case NvdrsSettingLocation.NVDRS_BASE_PROFILE_LOCATION:
                  Console.Write( "Base" );
                  break;
                case NvdrsSettingLocation.NVDRS_CURRENT_PROFILE_LOCATION:
                  Console.Write( "Current" );
                  break;
                case NvdrsSettingLocation.NVDRS_DEFAULT_PROFILE_LOCATION:
                  Console.Write( "Default" );
                  break;
                case NvdrsSettingLocation.NVDRS_GLOBAL_PROFILE_LOCATION:
                  Console.Write( "Global" );
                  break;
              }
              Console.WriteLine();
              Console.WriteLine( "Current Value is: " +
                ( drsSetting.isCurrentPredefined != 0 ? "predefined" : "from user" ) );
              Console.WriteLine( "isPredefinedValid: " +
                ( drsSetting.isPredefinedValid != 0 ? "true" : "false" ) );
              Console.WriteLine( String.Format( "Predefined Value: {0} (0x{1:X8})",
                drsSetting.u32PredefinedValue,
                drsSetting.u32PredefinedValue ) );
              stage++;
            }
            break;
          default:
            stage = MAX_STAGE;
            break;
        }
      }
      
      if ( init && ErrMsg.Length != 0 ) {
        Console.WriteLine( ErrMsg );
        Console.WriteLine( nvapi.GetErrMsg() );
      }

      Console.WriteLine( "Press any key to continue" );
      Console.ReadKey();
    }
  }
}
