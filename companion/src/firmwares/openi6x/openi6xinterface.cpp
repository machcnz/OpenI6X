/*
 * OpenI6X (FlySky i6X) firmware registration for Companion
 *
 * This keeps the FlySky target modular (like other vendor modules) and avoids
 * mixing it into the generic OpenTX registration unit.
 */

#include "openi6xinterface.h"

#include "firmwares/opentx/opentxinterface.h"
#include "firmwares/opentx/opentxeeprom.h"   // for GVARS_VARIANT

using namespace Board;

static void addOpenTxFlyskyOptions(OpenTxFirmware * firmware)
{
  // FlySky target forces LUA=NO and SDCARD=NO, so do not add lua/luac.

  // Common options
  firmware->addOption("ppmus", Firmware::tr("Channel values displayed in us"));
  firmware->addOption("nooverridech", Firmware::tr("No OverrideCH functions available"));

  // FAI options group (matches other OpenTX targets)
  static const Firmware::OptionsGroup fai_options = {
    Firmware::Option("faichoice", Firmware::tr("Possibility to enable FAI MODE (no telemetry) at field")),
    Firmware::Option("faimode",   Firmware::tr("FAI MODE (no telemetry) always enabled"))
  };
  firmware->addOptionsGroup(fai_options);

  // Feature set aligned with ARM-class radios (minus Lua)
  firmware->addOption("heli", Firmware::tr("Enable HELI menu and cyclic mix support"));
  firmware->addOption("gvars", Firmware::tr("Global variables"), GVARS_VARIANT);
  firmware->addOption("potscroll", Firmware::tr("Pots use in menus navigation"));
  firmware->addOption("autosource", Firmware::tr("In model setup menus automatically set source by moving the control"));
  firmware->addOption("autoswitch", Firmware::tr("In model setup menus automatically set switch by moving the control"));
  firmware->addOption("nographics", Firmware::tr("No graphical check boxes and sliders"));
  firmware->addOption("battgraph", Firmware::tr("Battery graph"));
  firmware->addOption("nobold", Firmware::tr("Don't use bold font for highlighting active items"));

  // RF options (EU + flex are harmless even if unused by the target)
  static const Firmware::Option opt_eu("eu", Firmware::tr("Removes D8 FrSky protocol support which is not legal for use in the EU on radios sold after Jan 1st, 2015"));
  static const Firmware::Option opt_fl("flexr9m", Firmware::tr("Enable non certified firmwares"));
  firmware->addOption("multimodule", Firmware::tr("Support for the DIY-Multiprotocol-TX-Module"));
  firmware->addOptionsGroup({opt_eu, opt_fl});

  // Font option
  firmware->addOption("sqt5font", Firmware::tr("Use alternative SQT5 font"));
}

void registerOpenI6xFirmwares()
{
  OpenTxFirmware * firmware = new OpenTxFirmware("opentx-i6x", Firmware::tr("FlySky i6X"), BOARD_I6X);
  addOpenTxFlyskyOptions(firmware);
  registerOpenTxFirmware(firmware);
}
