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

#include "controllunit.h"
#include <QDebug>

// @author: Andreas Rist

void ControllUnit::refresh(short IntFlagList)
{
    short shift=0b000000000001;
    for (int i = FLAG_LENGTH-1 ; i >=0; --i) {
        flag[i]=IntFlagList&shift;
        shift= shift<<1;
    }
}

ControllUnit::ControllUnit()
{
}

void ControllUnit::setOpCode(unsigned short opCode)
{
    this->opCode=opCode;
}

void ControllUnit::refreshFlags(short phase)
{
    this->defaultFalgs();
    if(phase == 0){
        switch (opCode) {
        case STO:refresh(FLAGS_STO_0);break;
        case LDA:refresh(FLAGS_LDA_0);break;
        case BRZ:refresh(FLAGS_BRZ_0);break;
        case ADD:refresh(FLAGS_ADD_0);break;
        case SUB:refresh(FLAGS_SUB_0);break;
        case OR:refresh(FLAGS_OR_0);break;
        case AND:refresh(FLAGS_AND_0);break;
        case XOR:refresh(FLAGS_XOR_0);break;
        case NOT:refresh(FLAGS_NOT_0);break;
        case INC:refresh(FLAGS_INC_0);break;
        case DEC:refresh(FLAGS_DEC_0);break;
        case ZRO:refresh(FLAGS_ZRO_0);break;
        case NOP0:refresh(FLAGS_NOP_0);break;
        case NOP1:refresh(FLAGS_NOP_0);break;
        case NOP2:refresh(FLAGS_NOP_0);break;
        case NOP3:refresh(FLAGS_NOP_0);break;
        default:
            qCritical() << "Not allowed OpCode";
            qCritical() << "Something went Wrong Phase 0";
            break;
        }
    }else if(phase==1){

        switch (opCode) {
        case STO:refresh(FLAGS_STO_1);break;
        case LDA:refresh(FLAGS_LDA_1);break;
        case BRZ:refresh(FLAGS_BRZ_1);break;
        case ADD:refresh(FLAGS_ADD_1);break;
        case SUB:refresh(FLAGS_SUB_1);break;
        case OR:refresh(FLAGS_OR_1);break;
        case AND:refresh(FLAGS_AND_1);break;
        case XOR:refresh(FLAGS_XOR_1);break;
        case NOT:refresh(FLAGS_NOT_1);break;
        case INC:refresh(FLAGS_INC_1);break;
        case DEC:refresh(FLAGS_DEC_1);break;
        case ZRO:refresh(FLAGS_ZRO_1);break;
        case NOP0:refresh(FLAGS_NOP_1);break;
        case NOP1:refresh(FLAGS_NOP_1);break;
        case NOP2:refresh(FLAGS_NOP_1);break;
        case NOP3:refresh(FLAGS_NOP_1);break;
        default:
            qCritical() << "Not allowed OpCode";
            qCritical() << "Something went Wrong Phase 1";
            break;
        }
    }
}

void ControllUnit::defaultFalgs()
{
    for (int i= 0; i < 12; ++i) {
        flag[i]=false;
    }
}

unsigned short ControllUnit::getALU3210()
{
    short alu3210=0;
    alu3210 +=flag[alu3]*8;
    alu3210 +=flag[alu2]*4;
    alu3210 +=flag[alu1]*2;
    alu3210 +=flag[alu0];
    return alu3210;
}

bool ControllUnit::getFlag(short Flag)
{
    return this->flag[Flag];
}

