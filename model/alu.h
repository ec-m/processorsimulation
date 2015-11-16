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

#ifndef ALU_H
#define ALU_H
#include <QDebug>

// @author: Andreas Rist

class ALU
{
public:

    ALU();

    /*
     * Makes the call depending on Flags alu3210, alucin and alumode
     * alu3210 is a number from combining the flags alu3, alu2, alu1, and alu0
     * more you can read in the Controllunit
     */
    short workAlu (unsigned short alu3210, short akku, short ramValue, bool aluMode, bool aluCIn);

    /*here is the solution saved of the Alu-Operation*/
    unsigned short aluResult;

private:

    /*
     * The functions alucin0,alucin1 and logical call the definitions at the bottom
     * Depending on the modes set From the flags aluMode and aluCin
     */
    short alucin0 (unsigned short alu3210,short akku, short ramValue);
    short alucin1 (unsigned short alu3210,short akku, short ramValue);
    short logical (unsigned short alu3210,short akku, short ramValue);

    /*
     *These definitions are used for the work of the Arithmetiklogikalunit
     * When the Alucin=false then these are selected
     */
    short alucin0b0000 (short a, short b){return a;}
    short alucin0b0001 (short a, short b){return a|b;}
    short alucin0b0010 (short a, short b){return a|~b;}
    short alucin0b0011 (short a, short b){return -1;}
    short alucin0b0100 (short a, short b){return a+(a&~b);}
    short alucin0b0101 (short a, short b){return (a|b)+(a&~b);}
    short alucin0b0110 (short a, short b){return a-b-1;}
    short alucin0b0111 (short a, short b){return (a&b)-1;}
    short alucin0b1000 (short a, short b){return a+(a&b);}
    short alucin0b1001 (short a, short b){return a+b;}
    short alucin0b1010 (short a, short b){return (a|~b)+(a&b);}
    short alucin0b1011 (short a, short b){return (a&b)-1;}
    short alucin0b1100 (short a, short b){return a+a;}
    short alucin0b1101 (short a, short b){return (a|b)+a;}
    short alucin0b1110 (short a, short b){return (a|~b)+a;}
    short alucin0b1111 (short a, short b){return a-1;}

    /*
     *these are used for alucin=true
     */
    short alucin1b0000 (short a, short b){return alucin0b0000(a,b)+1;}
    short alucin1b0001 (short a, short b){return alucin0b0001(a,b)+1;}
    short alucin1b0010 (short a, short b){return alucin0b0010(a,b)+1;}
    short alucin1b0011 (short a, short b){return alucin0b0011(a,b)+1;}
    short alucin1b0100 (short a, short b){return alucin0b0100(a,b)+1;}
    short alucin1b0101 (short a, short b){return alucin0b0101(a,b)+1;}
    short alucin1b0110 (short a, short b){return alucin0b0110(a,b)+1;}
    short alucin1b0111 (short a, short b){return alucin0b0111(a,b)+1;}
    short alucin1b1000 (short a, short b){return alucin0b1000(a,b)+1;}
    short alucin1b1001 (short a, short b){return alucin0b1001(a,b)+1;}
    short alucin1b1010 (short a, short b){return alucin0b1010(a,b)+1;}
    short alucin1b1011 (short a, short b){return alucin0b1011(a,b)+1;}
    short alucin1b1100 (short a, short b){return alucin0b1100(a,b)+1;}
    short alucin1b1101 (short a, short b){return alucin0b1101(a,b)+1;}
    short alucin1b1110 (short a, short b){return alucin0b1110(a,b)+1;}
    short alucin1b1111 (short a, short b){return alucin0b1111(a,b)+1;}

    /*
     * These are when the Alumode is Alumode is true
     * For more informations check the script from "Einführung in die technische Informatik
     * Register Transfer Ebene
     */
    short logical0000(short a, short b) {return ~a;}
    short logical0001(short a, short b) {return ~(a|b);}
    short logical0010(short a, short b) {return (~a)&b;}
    short logical0011(short a, short b) {return 0;}
    short logical0100(short a, short b) {return ~(a&b);}
    short logical0101(short a, short b) {return ~b;}
    short logical0110(short a, short b) {return a^b;}
    short logical0111(short a, short b) {return a&(~b);}
    short logical1000(short a, short b) {return (~a)|b;}
    short logical1001(short a, short b) {return ~(a^b);}
    short logical1010(short a, short b) {return b;}
    short logical1011(short a, short b) {return a&b;}
    short logical1100(short a, short b) {return 1;}
    short logical1101(short a, short b) {return a|(~b);}
    short logical1110(short a, short b) {return a|b;}
    short logical1111(short a, short b) {return a;}

};

#endif // ALU_H
