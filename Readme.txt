FM Midi Synth driver Version 2.14
Copyright (c) 1993-1995 by Jamie O'Connell
 
The FM MIDI Synth driver is a replacement driver for sound cards
that implement FM synthesis.  It features an extensive MIDI 
implementation as well as support for loadable instrument banks
and a Control Panel applet for run-time configuration of driver 
parameters.  It is designed to work with as many different sound 
cards from various manufacturers as possible. 

Version 2.12 New Things: 
   New voice allocation         - A new algorithm has been implemented,
                                  that chooses the oldest "off" voice
                                  when picking the next free voice to use.

Version 2.10 New Things: 
   Multiple Driver Openings     - Several programs can now share FM Synth
   Support for Channel and Key Aftertouch
   More efficient MIDI handling - The driver's response has been improved
                                  while the run-time size has been reduced.
   New Percussion Algorithm     - Better sounding percussion
   Some Patches Revised         - Certain Instruments have been improved.
   New Help File                - The FM Synth help file has been expanded
                                  and enhanced, thanks to Jerry Jorgenrud
                                  CIS [75060,1040].
   Optional MIDI Mapper Setup   - The driver installation offers to 
                                  automatically add a new MIDI Mapper setup, 
                                  while preserving any existing Mapper setup.

The following files should be include in this ZIP file:

 FMSYNTH.DRV	 The driver.
 FMCFG.DLL      Driver configuration library
 FMTASK.EXE     FM Synth run-time task.
 FMSYNTH.HLP	 The Windows help file.
 ADDMAPFM.EXE   Installation Program to append MIDI Mapper Setup
 ADDMAPFM.EXE   Recorder Macro.
 OEMSETUP.INF   Windows Driver installation information file.
 FMSYNTH.WRI    A Windows Write file with installation
                instructions.

 FMSYN.CAL      Cakewalk Pro CAL routine
 FMSYNTH.DRM    Cakewalk Pro Dump request Macros
 WJFM.INI       WinJammer and WinJammer Pro SysEX request macros
 STMB.H         C header file detailing FM Synth API
 STMB.PAS       Pascal file   detailing FM Synth API
 SYSEX.TXT      Text file describing System Exclusive messages
 README.TXT	    This file.
 VENDOR.TXT	    Vendor Information.

Other Information

FMSYN.CAL, is a CAL program that will launch the FM Synth applet 
from within Cakewalk.  It requires Cakewalk for Windows version
2.0 (or above), and can be easily bound to a key sequence for quick 
launching.

FMSYN.DRM, is a set of DRMs (Dump Request Macros) for getting System 
Exclusive information from the driver.  In order to use it, just 
insert the file into your WINCAKE.INI file.  Ensure that you have the 
"FM Synth (jwo) SysEx Input" driver selected as one of the MIDI Input 
drivers.  The Macros work with all versions of Cakewalk Professional for
Windows.

WJFM.INI, details request macros for getting SysEx dump information using
WinJammer and WinJammer Pro sequencers.

STMB.H and STMB.PAS, are C and Pascal header files.  They detail the
FM Synth API for getting and setting driver information.

SYSEX.TXT, details the System Exclusive implementation for the FM Synth
driver.

Jamie O'Connell - CIS [72662,1433]

DISCLAIMER

This program is provided without any warranty, expressed or implied,
including but not limited to fitness for a particular purpose.

