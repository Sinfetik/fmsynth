/* STMB.H -- Programming interface for FMSYNTH.DRV
 *           Copyright (c) 1993 by Jamie O'Connell
 *
 * Currently six functions are defined: GetTimbre, SetTimbre, GetParm, 
 * SetParm, GetPercMap, and SetPercMap.  With Version 2.0 of the driver
 * GetPercMap and SetPercMap are somewhat obsolete, but will still be
 * supported.  In addition, GetParm and SetParm operate on the Driver
 * System Parameters.     
 * 
 * Get Timbre retrieves the Timbre parameters from the specified location.
 * Timbres are Sent and Received in IBK format.
 *
 * SetTimbre will change the sound of an instrument in either working 
 * storage or the sound of an instrument stored within a RAM Timbre Bank.
 * 
 * GetParm retrieves the FM Synth system parameters
 * SetParm sets the System Parameters
 *     
 * *** OBSOLETE ***
 * GetPercMap and SetPercMap perform equivalent functions on the internal
 * percussion map: which note plays which percussion timbre at what pitch.
 *
 * NOTE - In version 1.x of the driver, only 47 percussion timbres were
 *        stored -- implementing the General MIDI percussion map.  For
 *        version 2.0, we store an entire 128 timbre bank for percussion.
 *        In addition, the Pitch parameter which used to be in the Percussion
 *        map is now stored directly in the Timbre, and the position within
 *        the bank defines the MIDI Key mapping. For instance, the Timbre
 *        stored in slot 35 of the percussion bank is the first GM Bass Drum.
 *
 *        Passing the obsolete TMB_BANK_PERCUSSION to GetTimbre will continue 
 *        to retrieve one of the 47 GM percussion timbres.  For example,
 *        requesting Timbre 0 will retrieve percussion Timbre 35.  To access
 *        the entire Percussion bank use the new TMB_PERCUSSION constant.     
 *     
 * **************************************************************************
 *
 * Working storage is the current version of a Timbre stored on a 
 * per-channel basis.  It is the version of the timbre which is used to
 * sound a voice for the channel when a note is to be played. The working 
 * storage is overwritten by Bank storage whenever a program change is 
 * received for the channel.
 *
 * The RAM Timbre bank is either the internal Timbre Bank, or one which 
 * has been loaded from a file.  In either case it is volatile storage
 * which is overwritten when the bank is reloaded.
 */

#ifndef  __STMB_H
#define  __STMB_H

#define TMB_WORKING_STORAGE      0
#define TMB_BANK_STORAGE         1
#define TMB_BANK_PERCUSSION      2 /* OBSOLETE */
#define TMB_PERCUSSION           3 /* Use this to retrieve percussion now */

#define FIRSTDRUMNOTE  35
#define LASTDRUMNOTE   81
#define NUMDRUMNOTES   (LASTDRUMNOTE - FIRSTDRUMNOTE + 1)

/* The timbre definition (IBK - SBI Format) */

typedef struct _tagTIMBRE {
        BYTE MSndChr;
        BYTE CSndChr;
        BYTE MKSLOut;
        BYTE CKSLOut;
        BYTE MAtkDcy;
        BYTE CAtkDcy;
        BYTE MSusRel;
        BYTE CSusRel;
        BYTE MWavSel;
        BYTE CWavSel;
        BYTE FDBkCon;
        BYTE PercVoc;   /* New for version 1.x -- Bass Drum=6, Snare=7 */
                        /* Tom-Tom=8,  Cymbal=9, HiHat=10 */
        CHAR Transpos;  /* New for version 1.x -- # of semitones offset */ 
        BYTE PrcPitch;  /* New for version 2.0 */
        BYTE Future[2];
        } TIMBRE;
        
typedef TIMBRE FAR * LPTIMBRE;

/* *** OBSOLETE ******************************************************* */

typedef struct _tagPERCMAP {
        BYTE patch;                 // the patch to use 
        BYTE note;                  // the note to play  
        } PERCMAP;

typedef PERCMAP FAR * LPPERCMAP;

/* The percussion map provides info for each pecussion MIDI key   
** To access (retrieve or send) the Percussion map you create an
** array of these things: PERCMAP percMap[NUMDRUMNOTES]; 
** and pass it to GetPercMap or SetPercMap.  The buffer must be at least
** sizeof(PERCMAP) * NUMDRUMNOTES = 94 bytes large.
*/

extern void FAR  PASCAL GetPercMap(LPPERCMAP lpPM);
extern void FAR  PASCAL SetPercMap(LPPERCMAP lpPM);

/* ********************************************************************* */


extern WORD FAR  PASCAL GetTimbre(WORD wLoc, LPTIMBRE lpTmb, WORD wSrc);
extern WORD FAR  PASCAL SetTimbre(WORD wLoc, LPTIMBRE lpTmb, WORD wDest);

/*   
 *  DESCRIPTION
 *
 *  wLoc - If the Destination (wDest) or Source (wSrc) is TMB_WORKING_STORAGE,
 *         then wLoc is the channel number (0 based) for storing the Timbre.  
 *         If the Destination is TMB_BANK_STORAGE, then the most
 *         significant byte of wLoc (HIBYTE(wLoc)) is the Bank number
 *         (valid values: 0 - 4), and the least significant byte is the
 *         timbre number (0-127).
 *         If the destination is TMB_PERC_BANK, the Bank number is ignored
 *         (there is only one percussion bank), and the LSB is the timbre
 *         number (0-46).      
 *
 *  lpTmb  A far pointer to a TIMBRE structure, defining the new timbre to
 *         store.  The structure should be the full 16 bytes in length.
 *                                                                    
 *  wSrc   This value determines how wLoc is interpreted when retrieving
 *         the timbre.  If wSrc is TMB_WORKING_STORAGE the timbre is retrieved
 *         from working storage (wLoc is a channel number). If wSrc is 
 *         TMB_BANK_STORAGE or TMB_PERCUSSION, the timbre is 
 *         retrieved from the specified bank and timbre slot (wLoc is the 
 *         combination of Bank & Timbre#).
 *
 *  wDest  This value determines how wLoc is interpreted and the final 
 *         destination for the timbre.  If wDest is TMB_WORKING_STORAGE the
 *         channel timbre info is updated, and future voices on channel will
 *         sound this timbre. If wDest is TMB_BANK_STORAGE ot TMB_PERCUSSION, 
 *         both the Bank Timbre, and any channels set to this Bank and Timbre 
 *         are updated. Any future notes playing this bank and timbre will 
 *         sound the timbre.
 *                                                             
 *  Return Value
 *         If all goes well, 0 is returned, otherwise a non-zero value is
 *         returned indicating, an incorrect or out-of-range parameter.  
 *         The values within the TIMBRE structure itself are not checked
 *         for validity, but stored as supplied.
 */

typedef struct _tagSYSPARM {
        BYTE    fStereo;      /* 1 = on, 0 = off */
        BYTE    fPercussion;  /* 1 = on, 0 = off */
        BYTE    PerChannel;   /* if Percussion mode = 1: channel = 0-15 */
                              /* (i.e. MIDI channel 10 is value 9)      */
        BYTE    DftBank;      /* 0-4 (Bank1 - Bank5) */
        BYTE    fVibDepth;    /* 0 = light, 1 = deep */
        BYTE    fTremDepth;   /* 0 = light, 1 = deep */
        BYTE    BendRange;     /* 0-12 semitones (1 octave) */
        BYTE    fSaveSettings;/* 1 = Save the settings in the INI file */
        BYTE    ChanMap[16];  /* 1 = on, 0 = off -- one byte per channel */
        char    PercBoost;     /* signed: -64 to +63 -- 0 is no boost */
        } SYSPARM, FAR *LPSYSPARM;
    
/* You can use sizeof(SYSPARM) as the StructLen parameter */
            
        
extern WORD FAR  PASCAL GetParm(LPSYSPARM lpSysParm, WORD StructLen);
extern WORD FAR  PASCAL SetParm(LPSYSPARM lpSysParm, WORD StructLen);

/*   
 *  DESCRIPTION
 *
 *  lpSysParm   - a FAR pointer to a SYSPARM struct as shown above.  All
 *                parameters are retrieved and set at once.  When setting
 *                parameters the driver is reinitialized so the driver
 *                is reset when the function returns.
 *
 *  StructLen     Is the size of SYSPARM.  Passing this value allows future
 *                additions and modifications to the structure.
 *
 *  Return Value
 *         If all goes well, 0 is returned, otherwise a non-zero value is
 *         returned indicating, an incorrect or out-of-range parameter.  
 *     
 */

#endif
