#ifndef MESSAGE_H
#define MESSAGE_H

/*
 * Message objects get send between
 * GUI, Controller, Model and Parser.
 * The void pointer as an attribute
 * contains all the information that
 * need to be passed on in between the
 * different components. The different
 * messages can be distinguished with
 * their enumeration type.
 * @author: Eva Charlotte Mayer
 */


class Message
{
public:

    enum TYPE {

        /* Steuerungsphasen */
        AddrIsIR,
        AlluIsAccu,
        WriteRAM,
        AddrIsPC,
        SetIR,
        IncPC,
        AluIsRAM,
        SetAccu,
        SetPC,
        AluWork,
        ClockCircle,
        CUisIR,
        SetPcWithout,
        Phase1withRam,
        Phase1withAccu,
        Phase1withoutAdresse,
        Phase2,

        /* FullStepMessages */
        FullstepNormal,
        FullstepBRZ,
        FullstepBRZJump,
        FullstepSingle,

        /* Communication between Model and GUI */
        FileOpen, //From GUI to Model: msg.content is set to path from file that user opens
        RAMwasSet, //Model sends whole RAM to GUI
        GetActiveRamRow, //sends current RAM cell to be highlighted
        infoText, //to update infoBox
        Speed,// send ms of Automaticmode

        /* Bausteine updaten */
        IRvalues, //Model sends OpCode and Address to GUI
        PCupdate, //PC value is send to GUI by Model
        ACCUupdate, //Accu value is send to GUI by Model
        SendSingleRAMCell, //if Model updates just one cell of the RAM
        RefreshCuFlags, //if Model updates cu flags

        /* Einstellungen, welcher Modus gerade im GUI ausgewählt wurde */
        SingleStep, //no content - simply calls method "step"
        HalfCycle, //when user chooses half-cycle mode
        Stop, //when user wants to stop automatic mode
        Cycle, //when user chooses full-cycle-mode
        Automatic, //when user chooses automatic mode
        Reset, //when user wants to reset
        StopAuto,

        /* User input from GUI to Model --> gets checked by Controller! */
        UserInputPC,
        UserInputOpCode,
        UserInputAddress,
        UserInputAccu,
        UserInputRAM,

        /* If user input was not correct --> from Controller to GUI */
        WrongInputPC,
        WrongInputOpCode,
        WrongInputAddress,
        WrongInputAccu,
        WrongInputRAM,

        /* Communication from Parser to GUI */
        ParserError, //if toyexception is thrown
        GetOpCodeRows //to know until what cell opcodes need to be translated into mnemonic
    };


    /* Attributes */
    const TYPE type;
    const void* content;
    Message(const TYPE &t);

};

#endif // MESSAGE_H
