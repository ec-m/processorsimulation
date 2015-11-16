/*
 * This file is part of Processorsimulation.
 *
 * The Processorsimulation is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by the Free
 * Software Foundation, Version 3.
 *
 * The Processorsimulation is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "infoboxcontent.h"

// @author: Andreas Rist

infoBoxContent::infoBoxContent()
{
}

QString infoBoxContent::halfStepInfo(bool step, short oCode)
{
    if(step){
        switch (oCode) {
        case STO:return " ADDR=IR; ALU=ACCU; WRITE[RAM]";
        case LDA:return " ADDR=IR; ALU=RAM; SET[ACCU]";
        case BRZ:return " SET[PC]";
        case ADD:return " ADDR=IR; ALU=ACCU+RAM; SET[ACCU]";
        case SUB:return " ADDR=IR; ALU=ACCU-RAM; SET[ACCU]";
        case OR:return  " ADDR=IR; ALU=ACCU|RAM; SET[ACCU]";
        case AND:return " ADDR=IR; ALU=ACCU&RAM; SET[ACCU]";
        case XOR:return " ADDR=IR; ALU=ACCU^RAM; SET[ACCU]";
        case NOT:return " ALU=~ACCU; SET[ACCU]";
        case INC:return " ALU=ACCU+1; SET[ACCU";
        case DEC:return " ALU=ACCU-1; SET[ACCU]";
        case ZRO:return " ALU=0; SET[ACCU]";

        default:
            if(oCode>= NOP0 && oCode<= NOP3){
                return "ADDR=PC; SET[IR]; INC[PC]";
            }
            break;
        }
    }else{
        return "ADDR=PC; SET[IR]; INC[PC]";
    }
}

QString infoBoxContent::fullStepInfo(short oCode)
{
    switch (oCode) {
    case STO:return " ADDR=IR; ALU=ACCU; WRITE[RAM]<br> ADDR=PC; SET[IR]; INC[PC]";
    case LDA:return " ADDR=IR; ALU=RAM; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case BRZ:return " SET[PC]<br> ADDR=PC; SET[IR]; INC[PC]";
    case ADD:return " ADDR=IR; ALU=ACCU+RAM; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case SUB:return " ADDR=IR; ALU=ACCU-RAM; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case OR:return  " ADDR=IR; ALU=ACCU|RAM; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case AND:return " ADDR=IR; ALU=ACCU&RAM; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case XOR:return " ADDR=IR; ALU=ACCU^RAM; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case NOT:return " ALU=~ACCU; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case INC:return " ALU=ACCU+1; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case DEC:return " ALU=ACCU-1; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    case ZRO:return " ALU=0; SET[ACCU]<br> ADDR=PC; SET[IR]; INC[PC]";
    default:
        if(oCode>= NOP0 && oCode<= NOP3){
            return " ADDR=PC; SET[IR]; INC[PC]";
        }
        break;
    }
}

QString infoBoxContent::step1()
{
    return "ADDR=IR";
}

QString infoBoxContent::step2(short oCode)
{
    switch (oCode) {
    case STO: return "ALU=ACCU";
    case LDA: return "ALU=RAM";
    case ADD: return "ALU=ACCU+RAM";
    case SUB: return "ALU=ACCU-RAM";
    case OR: return "ALU=ACCU|RAM";
    case AND: return "ALU=ACCU&RAM";
    case XOR: return "ALU=ACCU^RAM";
    case NOT: return "ALU=!ACCU";
    case INC: return "ALU=ACCU+1";
    case DEC: return "ALU=ACCU-1";
    case ZRO: return "ALU=0";

    default:
        return "";
        break;
    }
}

QString infoBoxContent::step3(short oCode)
{
    if(oCode==BRZ){
        return "SET[PC]";
    }else if(oCode==STO)
        {
        return "WRITE[RAM]";
        }else if(oCode<=ZRO)
            {
                return "SET[ACCU]";
                }

    return"";
}


QString infoBoxContent::step4()
{
    return "ADDR=PC";
}

QString infoBoxContent::step5()
{
    return "SET[IR]";
}

QString infoBoxContent::step6()
{
    return "INC[PC]";
}

