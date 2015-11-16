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

#include "alu.h"
#include <QDebug>

// @author: Andreas Rist

ALU::ALU()
{
}

/**
 * @brief ALU::workAlu
 * @param opCode
 * @param akku
 * @param ramValue
 * @param aluMode false is arethmetik-mode and true is logic-mode
 * @param aluCIn false is alucin=0 true is alucin=1
 * @return
 */
short ALU::workAlu(unsigned short alu3210, short akku, short ramValue, bool aluMode, bool aluCIn)
{
    if(aluMode){
        return this->logical(alu3210,akku,ramValue);
    }else if(aluCIn){
        return this->alucin1(alu3210,akku,ramValue);

    }else
        return this->alucin0(alu3210,akku,ramValue);
}

/**
 * @brief ALU::alucin0
 * @param opCode The opcode 4 bit/shortvalue <=16
 * @param akku Value of akku
 * @param ramValue ramvalue 16 bits
 * @return solution of alu
 */
short ALU::alucin0(unsigned short alu3210, short akku, short ramValue)
{
    switch (alu3210) {
    case 0b0000:
        return alucin0b0000(akku,ramValue);
        break;
    case 0b0001:
        return alucin0b0001(akku,ramValue);
        break;
    case 0b0010:
        return alucin0b0010(akku,ramValue);
        break;
    case 0b0011:
        return alucin0b0011(akku,ramValue);
        break;
    case 0b0100:
        return alucin0b0100(akku,ramValue);
        break;
    case 0b0101:
        return alucin0b0101(akku,ramValue);
        break;
    case 0b0110:
        return alucin0b0110(akku,ramValue);
        break;
    case 0b0111:
        return alucin0b0111(akku,ramValue);
        break;
    case 0b1000:
        return alucin0b1000(akku,ramValue);
        break;
    case 0b1001:
        return alucin0b1001(akku,ramValue);
        break;
    case 0b1010:
        return alucin0b1010(akku,ramValue);
        break;
    case 0b1011:
        return alucin0b1011(akku,ramValue);
        break;
    case 0b1100:
        return alucin0b1100(akku,ramValue);
        break;
    case 0b1101:
        return alucin0b1101(akku,ramValue);
        break;
    case 0b1110:
        return alucin0b1110(akku,ramValue);
        break;
    case 0b1111:
        return alucin0b1111(akku,ramValue);
        break;
    default: qDebug()<<"wrong opcode in ALU";
        break;
    }
}

/**
 * @brief ALU::alucin1
 * @param opCode The opcode 4 bit/shortvalue <=16
 * @param akku Value of akku
 * @param ramValue ramvalue 16 bits
 * @return solution of alu
 */
short ALU::alucin1(unsigned short alu3210, short akku, short ramValue)
{
    switch (alu3210) {
    case 0b0000:
        return alucin1b0000(akku,ramValue);
        break;
    case 0b0001:
        return alucin1b0001(akku,ramValue);
        break;
    case 0b0010:
        return alucin1b0010(akku,ramValue);
        break;
    case 0b0011:
        return alucin1b0011(akku,ramValue);
        break;
    case 0b0100:
        return alucin1b0100(akku,ramValue);
        break;
    case 0b0101:
        return alucin1b0101(akku,ramValue);
        break;
    case 0b0110:
        return alucin1b0110(akku,ramValue);
        break;
    case 0b0111:
        return alucin1b0111(akku,ramValue);
        break;
    case 0b1000:
        return alucin1b1000(akku,ramValue);
        break;
    case 0b1001:
        return alucin1b1001(akku,ramValue);
        break;
    case 0b1010:
        return alucin1b1010(akku,ramValue);
        break;
    case 0b1011:
        return alucin1b1011(akku,ramValue);
        break;
    case 0b1100:
        return alucin1b1100(akku,ramValue);
        break;
    case 0b1101:
        return alucin1b1101(akku,ramValue);
        break;
    case 0b1110:
        return alucin1b1110(akku,ramValue);
        break;
    case 0b1111:
        return alucin1b1111(akku,ramValue);
        break;
    default: qDebug()<<"wrong opcode in ALU";
        break;
    }
}

/**
 * @brief ALU::logical logic funktion
 * @param opCode
 * @param akku
 * @param ramValue
 * @return gives the Solution of Alu back
 */
short ALU::logical(unsigned short alu3210, short akku, short ramValue)
{
    switch (alu3210) {
    case 0b0000:
        return logical0000(akku,ramValue);
        break;
    case 0b0001:
        return logical0001(akku,ramValue);
        break;
    case 0b0010:
        return logical0010(akku,ramValue);
        break;
    case 0b0011:
        return logical0011(akku,ramValue);
        break;
    case 0b0100:
        return logical0100(akku,ramValue);
        break;
    case 0b0101:
        return logical0101(akku,ramValue);
        break;
    case 0b0110:
        return logical0110(akku,ramValue);
        break;
    case 0b0111:
        return logical0111(akku,ramValue);
        break;
    case 0b1000:
        return logical1000(akku,ramValue);
        break;
    case 0b1001:
        return logical1001(akku,ramValue);
        break;
    case 0b1010:
        return logical1010(akku,ramValue);
        break;
    case 0b1011:
        return logical1011(akku,ramValue);
        break;
    case 0b1100:
        return logical1100(akku,ramValue);
        break;
    case 0b1101:
        return logical1101(akku,ramValue);
        break;
    case 0b1110:
        return logical1110(akku,ramValue);
        break;
    case 0b1111:
        return logical1111(akku,ramValue);
        break;
    default: qDebug()<<"wrong opcode in ALU in Logical";
        break;
    }
}
