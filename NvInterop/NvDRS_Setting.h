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

  public enum class NvdrsSettingId : System::UInt32
  {
    OGL_AA_LINE_GAMMA_ID = 0x2089BF6C,
    OGL_DEEP_COLOR_SCANOUT_ID = 0x2097C2F6,
    OGL_DEFAULT_SWAP_INTERVAL_ID = 0x206A6582,
    OGL_DEFAULT_SWAP_INTERVAL_FRACTIONAL_ID = 0x206C4581,
    OGL_DEFAULT_SWAP_INTERVAL_SIGN_ID = 0x20655CFA,
    OGL_EVENT_LOG_SEVERITY_THRESHOLD_ID = 0x209DF23E,
    OGL_EXTENSION_STRING_VERSION_ID = 0x20FF7493,
    OGL_FORCE_BLIT_ID = 0x201F619F,
    OGL_FORCE_STEREO_ID = 0x204D9A0C,
    OGL_IMPLICIT_GPU_AFFINITY_ID = 0x20D0F3E6,
    OGL_MAX_FRAMES_ALLOWED_ID = 0x208E55E3,
    OGL_MULTIMON_ID = 0x200AEBFC,
    OGL_OVERLAY_PIXEL_TYPE_ID = 0x209AE66F,
    OGL_OVERLAY_SUPPORT_ID = 0x206C28C4,
    OGL_QUALITY_ENHANCEMENTS_ID = 0x20797D6C,
    OGL_SINGLE_BACKDEPTH_BUFFER_ID = 0x20A29055,
    OGL_SLI_MULTICAST_ID = 0x2092D3BE,
    OGL_THREAD_CONTROL_ID = 0x20C1221E,
    OGL_TMON_LEVEL_ID = 0x202888C1,
    OGL_TRIPLE_BUFFER_ID = 0x20FDD1F9,
    AA_BEHAVIOR_FLAGS_ID = 0x10ECDB82,
    AA_MODE_ALPHATOCOVERAGE_ID = 0x10FC2D9C,
    AA_MODE_GAMMACORRECTION_ID = 0x107D639D,
    AA_MODE_METHOD_ID = 0x10D773D2,
    AA_MODE_REPLAY_ID = 0x10D48A85,
    AA_MODE_SELECTOR_ID = 0x107EFC5B,
    AA_MODE_SELECTOR_SLIAA_ID = 0x107AFC5B,
    ANISO_MODE_LEVEL_ID = 0x101E61A9,
    ANISO_MODE_SELECTOR_ID = 0x10D2BB16,
    ANSEL_ALLOW_ID = 0x1035DB89,
    ANSEL_ENABLE_ID = 0x1075D972,
    ANSEL_WHITELISTED_ID = 0x1085DA8A,
    APPLICATION_PROFILE_NOTIFICATION_TIMEOUT_ID = 0x104554B6,
    APPLICATION_STEAM_ID_ID = 0x107CDDBC,
    BATTERY_BOOST_ID = 0x10115C89,
    CPL_HIDDEN_PROFILE_ID = 0x106D5CFF,
    CUDA_EXCLUDED_GPUS_ID = 0x10354FF8,
    D3DOGL_GPU_MAX_POWER_ID = 0x10D1EF29,
    EXPORT_PERF_COUNTERS_ID = 0x108F0841,
    FXAA_ALLOW_ID = 0x1034CB89,
    FXAA_ENABLE_ID = 0x1074C972,
    FXAA_INDICATOR_ENABLE_ID = 0x1068FB9C,
    MCSFRSHOWSPLIT_ID = 0x10287051,
    NV_QUALITY_UPSCALING_ID = 0x10444444,
    OPTIMUS_MAXAA_ID = 0x10F9DC83,
    PHYSXINDICATOR_ID = 0x1094F16F,
    PREFERRED_PSTATE_ID = 0x1057EB71,
    PREVENT_UI_AF_OVERRIDE_ID = 0x103BCCB5,
    PS_FRAMERATE_LIMITER_ID = 0x10834FEE,
    PS_FRAMERATE_LIMITER_2_CONTROL_ID = 0x10834FFF,
    PS_FRAMERATE_LIMITER_GPS_CTRL_ID = 0x10834F01,
    PS_FRAMERATE_MONITOR_CTRL_ID = 0x10834F05,
    SHIM_MAXRES_ID = 0x10F9DC82,
    SHIM_MCCOMPAT_ID = 0x10F9DC80,
    SHIM_RENDERING_MODE_ID = 0x10F9DC81,
    SHIM_RENDERING_OPTIONS_ID = 0x10F9DC84,
    SLI_GPU_COUNT_ID = 0x1033DCD1,
    SLI_PREDEFINED_GPU_COUNT_ID = 0x1033DCD2,
    SLI_PREDEFINED_GPU_COUNT_DX10_ID = 0x1033DCD3,
    SLI_PREDEFINED_MODE_ID = 0x1033CEC1,
    SLI_PREDEFINED_MODE_DX10_ID = 0x1033CEC2,
    SLI_RENDERING_MODE_ID = 0x1033CED1,
    VRPRERENDERLIMIT_ID = 0x10111133,
    VRRFEATUREINDICATOR_ID = 0x1094F157,
    VRROVERLAYINDICATOR_ID = 0x1095F16F,
    VRRREQUESTSTATE_ID = 0x1094F1F7,
    VRR_APP_OVERRIDE_ID = 0x10A879CF,
    VRR_APP_OVERRIDE_REQUEST_STATE_ID = 0x10A879AC,
    VRR_MODE_ID = 0x1194F158,
    VSYNCSMOOTHAFR_ID = 0x101AE763,
    VSYNCVRRCONTROL_ID = 0x10A879CE,
    VSYNC_BEHAVIOR_FLAGS_ID = 0x10FDEC23,
    WKS_API_STEREO_EYES_EXCHANGE_ID = 0x11AE435C,
    WKS_API_STEREO_MODE_ID = 0x11E91A61,
    WKS_MEMORY_ALLOCATION_POLICY_ID = 0x11112233,
    WKS_STEREO_DONGLE_SUPPORT_ID = 0x112493BD,
    WKS_STEREO_SUPPORT_ID = 0x11AA9E99,
    WKS_STEREO_SWAP_MODE_ID = 0x11333333,
    AO_MODE_ID = 0x00667329,
    AO_MODE_ACTIVE_ID = 0x00664339,
    AUTO_LODBIASADJUST_ID = 0x00638E8F,
    EXPORT_PERF_COUNTERS_DX9_ONLY_ID = 0x00B65E72,
    ICAFE_LOGO_CONFIG_ID = 0x00DB1337,
    LODBIASADJUST_ID = 0x00738E8F,
    MAXWELL_B_SAMPLE_INTERLEAVE_ID = 0x0098C1AC,
    NLS_ALLOW_ID = 0x00041806,
    NLS_ENABLE_ID = 0x00120618,
    PRERENDERLIMIT_ID = 0x007BA09E,
    PS_SHADERDISKCACHE_ID = 0x00198FFF,
    PS_TEXFILTER_ANISO_OPTS2_ID = 0x00E73211,
    PS_TEXFILTER_BILINEAR_IN_ANISO_ID = 0x0084CD70,
    PS_TEXFILTER_DISABLE_TRILIN_SLOPE_ID = 0x002ECAF2,
    PS_TEXFILTER_NO_NEG_LODBIAS_ID = 0x0019BB68,
    QUALITY_ENHANCEMENTS_ID = 0x00CE2691,
    REFRESH_RATE_OVERRIDE_ID = 0x0064B541,
    SET_POWER_THROTTLE_FOR_PCIe_COMPLIANCE_ID = 0x00AE785C,
    SET_VAB_DATA_ID = 0x00AB8687,
    VSYNCMODE_ID = 0x00A879CF,
    VSYNCTEARCONTROL_ID = 0x005A375C,
  };

  public ref struct NvdrsBinarySetting sealed
  {
    System::UInt32       valueLength;
    array<System::Byte>^ valueData;
  };
    
	/// <summary>
	/// Summary for NvAPISetting
	/// </summary>
	public ref class NvDRS_Setting :  public System::ComponentModel::Component
	{
	public:
    NvDRS_Setting();
    NvDRS_Setting( NVDRS_SETTING* setting );
    NvDRS_Setting( const NVDRS_SETTING& setting );
    NvDRS_Setting( System::ComponentModel::IContainer^ container );
    NVDRS_SETTING* GetNativePtr();

    property System::UInt32       version { System::UInt32 get(); };
    property System::String^      settingName { System::String^ get(); };
    property System::UInt32       settingId { System::UInt32 get(); };
    property NvdrsSettingType     settingType { NvdrsSettingType get(); };
    property NvdrsSettingLocation settingLocation { NvdrsSettingLocation get(); };
    property System::UInt32       isCurrentPredefined { System::UInt32 get(); };
    property System::UInt32       isPredefinedValid { System::UInt32 get(); };
    property System::UInt32       u32PredefinedValue { System::UInt32 get(); };
    property NvdrsBinarySetting^  binaryPredefinedValue { NvdrsBinarySetting^ get(); };
    property System::String^      wszPredefinedValue { System::String^ get(); };
    property System::UInt32       u32CurrentValue { System::UInt32 get(); };
    property NvdrsBinarySetting^  binaryCurrentValue { NvdrsBinarySetting^ get(); };
    property System::String^      wszCurrentValue { System::String^ get(); };

	protected:
    ~NvDRS_Setting();
    !NvDRS_Setting();

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
