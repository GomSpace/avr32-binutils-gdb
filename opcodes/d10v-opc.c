/* d10v-opc.c -- D10V opcode list
   Copyright 1996 Free Software Foundation, Inc.
   Written by Martin Hunt, Cygnus Support

This file is part of GDB, GAS, and the GNU binutils.

GDB, GAS, and the GNU binutils are free software; you can redistribute
them and/or modify them under the terms of the GNU General Public
License as published by the Free Software Foundation; either version
2, or (at your option) any later version.

GDB, GAS, and the GNU binutils are distributed in the hope that they
will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this file; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  */

#include <stdio.h>
#include "ansidecl.h"
#include "opcode/d10v.h"

const struct d10v_operand d10v_operands[] =
{
#define UNUSED	(0)
  { 0, 0, 0 },
#define RSRC	(UNUSED + 1)
  { 4, 1, OPERAND_REG },
#define RDST	(RSRC + 1)
  { 4, 5, OPERAND_DEST|OPERAND_REG },
#define ASRC	(RDST + 1)
  { 1, 4, OPERAND_ACC|OPERAND_REG },
#define ADST	(ASRC + 1)
  { 1, 8, OPERAND_DEST|OPERAND_ACC|OPERAND_REG },
#define RSRCE	(ADST + 1)
  { 4, 1, OPERAND_EVEN|OPERAND_REG },
#define RDSTE	(RSRCE + 1)
  { 4, 5, OPERAND_EVEN|OPERAND_DEST|OPERAND_REG },
#define NUM16	(RDSTE + 1)
  { 16, 0, OPERAND_NUM },
#define NUM3	(NUM16 + 1)
  { 3, 1, OPERAND_NUM },
#define NUM4	(NUM3 + 1)
  { 4, 1, OPERAND_NUM },
#define NUM8	(NUM4 + 1)	/* only used in REPI */
  { 8, 16, OPERAND_NUM },
#define ANUM16	(NUM8 + 1)
  { 16, 0, OPERAND_ADDR },
#define ANUM8	(ANUM16 + 1)
  { 8, 0, OPERAND_ADDR },
#define ASRC2	(ANUM8 + 1)
  { 1, 8, OPERAND_ACC|OPERAND_REG },
#define RSRC2	(ASRC2 + 1)
  { 4, 5, OPERAND_REG },
#define RSRC2E	(RSRC2 + 1)
  { 4, 5, OPERAND_REG|OPERAND_EVEN },
#define ASRC0	(RSRC2E + 1)
  { 1, 0, OPERAND_ACC|OPERAND_REG },
#define ADST0	(ASRC0 + 1)
  { 1, 0, OPERAND_ACC|OPERAND_REG|OPERAND_DEST },
#define FSRC	(ADST0 + 1)
  { 2, 1, OPERAND_REG | OPERAND_FLAG },
#define FDST	(FSRC + 1)
  { 1, 5, OPERAND_REG | OPERAND_FLAG | OPERAND_DEST},
#define ATSIGN	(FDST + 1)
  { 0, 0, OPERAND_ATSIGN},
#define ATPAR	(ATSIGN + 1)	/* "@(" */
  { 0, 0, OPERAND_ATPAR},
#define PLUS	(ATPAR + 1)	/* postincrement */
  { 0, 0, OPERAND_PLUS},
#define MINUS	(PLUS + 1)	/* postdecrement */
  { 0, 0, OPERAND_MINUS},
#define ATMINUS	(MINUS + 1)	/* predecrement */
  { 0, 0, OPERAND_ATMINUS},
#define CSRC	(ATMINUS + 1)	/* control register */
  { 4, 1, OPERAND_REG|OPERAND_CONTROL},
#define CDST	(CSRC + 1)	/* control register */
  { 4, 5, OPERAND_REG|OPERAND_CONTROL|OPERAND_DEST},
};

const struct d10v_opcode d10v_opcodes[] = {
  { "abs", SHORT_2, 1, EITHER, PAR, 0x4607, 0x7e1f, { RDST } },
  { "abs", SHORT_2, 1, IU, PAR, 0x5607, 0x7eff, { ADST } },
  { "add", SHORT_2, 1, EITHER, PAR, 0x0200, 0x7e01, { RDST, RSRC } },
  { "add", SHORT_2, 1, IU, PAR, 0x1201, 0x7ee3, { ADST, RSRCE } },
  { "add", SHORT_2, 1, IU, PAR, 0x1203, 0x7eef, { ADST, ASRC } },
  { "add2w", SHORT_2, 2, IU, PAR, 0x1200, 0x7e23, { RDSTE, RSRCE } },
  { "add3", LONG_L, 1, MU, SEQ, 0x1000000, 0x3f000000, { RDST, RSRC, NUM16 } },
  { "addac3", LONG_R, 1, IU, SEQ, 0x17000200, 0x3ffffe22, { RDSTE, RSRCE, ASRC0 } },
  { "addac3", LONG_R, 1, IU, SEQ, 0x17000202, 0x3ffffe2e, { RDSTE, ASRC, ASRC0 } },
  { "addac3s", LONG_R, 1, IU, SEQ, 0x17001200, 0x3ffffe22, { RDSTE, RSRCE, ASRC0 } },
  { "addac3s", LONG_R, 1, IU, SEQ, 0x17001202, 0x3ffffe2e, { RDSTE, ASRC, ASRC0 } },
  { "addi", SHORT_2, 1, EITHER, PAR,  0x201, 0x7e01, { RDST, NUM4 } },
  { "and", SHORT_2, 1, EITHER, PAR, 0xc00, 0x7e01, { RDST, RSRC } },
  { "and3", LONG_L, 1, MU, SEQ, 0x6000000, 0x3f000000, { RDST, RSRC, NUM16 } },
  { "bclri", SHORT_2, 1, IU, PAR, 0xc01, 0x7e01, { RDST, NUM4 } },
  { "bl", LONG_B, 3, MU, BRANCH_LINK, 0x24800000, 0x3fff8000, { ANUM16 } },
  { "bl.s", SHORT_B, 3, MU, BRANCH_LINK, 0x4900, 0x7f00, { ANUM8 } },
  { "bnoti", SHORT_2, 1, IU, PAR, 0xa01, 0x7e01, { RDST, NUM4 } },
  { "bra", LONG_B, 3, MU, SEQ, 0x24000000, 0x3fff0000, { ANUM16 } },
  { "bra.s", SHORT_B, 3, MU, PAR, 0x4800, 0x7f00, { ANUM8 } },
  { "brf0f", LONG_B, 3, MU, SEQ, 0x25000000, 0x3fff0000, { ANUM16 } },
  { "brf0f.s", SHORT_B, 3, MU, PAR, 0x4a00, 0x7f00, { ANUM8 } },
  { "brf0t", LONG_B, 3, MU, SEQ, 0x25800000, 0x3fff0000, { ANUM16 } },
  { "brf0t.s", SHORT_B, 3, MU, PAR, 0x4b00, 0x7f00, { ANUM8 } },
  { "bseti", SHORT_2, 1, IU, PAR, 0x801, 0x7e01, { RDST, NUM4 } },
  { "btsti", SHORT_2, 1, IU, PAR, 0xe01, 0x7e01, { RDST, NUM4 } },
  { "clrac", SHORT_2, 1, IU, PAR, 0x5601, 0x7eff, { ADST } },
  { "cmp", SHORT_2, 1, EITHER, PAR, 0x600, 0x7e01, { RSRC2, RSRC } },
  { "cmp", SHORT_2, 1, IU, PAR, 0x1603, 0x7eef, { ASRC2, ASRC } },
  { "cmpeq", SHORT_2, 1, EITHER, PAR, 0x400, 0x7e01, { RSRC2, RSRC } },
  { "cmpeq", SHORT_2, 1, IU, PAR, 0x1403, 0x7eef, { ASRC2, ASRC } },
  { "cmpeqi", SHORT_2, 1, EITHER, PAR, 0x401, 0x7e01, { RSRC2, NUM4 } },
  { "cmpeqi", LONG_L, 1, MU, SEQ, 0x2000000, 0x3f0f0000, { RSRC2, NUM16 } },
  { "cmpi", SHORT_2, 1, EITHER, PAR, 0x601, 0x7e01, { RSRC2, NUM4 } },
  { "cmpi", LONG_L, 1, MU, SEQ, 0x3000000, 0x3f0f0000, { RSRC2, NUM16 } },
  { "cmpu", SHORT_2, 1, EITHER, PAR, 0x4600, 0x7e01, { RSRC2, RSRC } },
  { "cmpui", LONG_L, 1, MU, SEQ, 0x23000000, 0x3f0f0000, { RSRC2, NUM16 } },
  { "cpfg", SHORT_2, 1, MU, PAR, 0x4e09, 0x7fd9, { FDST, FSRC } },
  { "dbt", SHORT_2, 5, MU, PAR, 0x5f20, 0x7fff, { 0 } },
  { "exef0f", SHORT_2, 1, EITHER, PAR, 0x4e04, 0x7fff, { 0 } },
  { "exef0t", SHORT_2, 1, EITHER, PAR, 0x4e24, 0x7fff, { 0 } },
  { "exef1f", SHORT_2, 1, EITHER, PAR, 0x4e40, 0x7fff, { 0 } },
  { "exef1t", SHORT_2, 1, EITHER, PAR, 0x4e42, 0x7fff, { 0 } },
  { "exefaf", SHORT_2, 1, EITHER, PAR, 0x4e00, 0x7fff, { 0 } },
  { "exefat", SHORT_2, 1, EITHER, PAR, 0x4e02, 0x7fff, { 0 } },
  { "exetaf", SHORT_2, 1, EITHER, PAR, 0x4e20, 0x7fff, { 0 } },
  { "exetat", SHORT_2, 1, EITHER, PAR, 0x4e22, 0x7fff, { 0 } },
  { "exp", LONG_R, 1, IU, SEQ, 0x15002a00, 0x3ffffe03, { RDST, RSRCE } },
  { "exp", LONG_R, 1, IU, SEQ, 0x15002a02, 0x3ffffe0f, { RDST, ASRC } },
  { "jl", SHORT_2, 3, MU, BRANCH_LINK, 0x4d00, 0x7fe1, { RSRC } },
  { "jmp", SHORT_2, 3, MU, PAR, 0x4c00, 0x7fe1, { RSRC } },
  { "ld", LONG_L, 1, MU, SEQ, 0x30000000, 0x3f000000, { RDST, ATPAR, NUM16, RSRC } },
  { "ld", SHORT_2, 1, MU, PAR, 0x6401, 0x7e01, { RDST, ATSIGN, RSRC, MINUS } },
  { "ld", SHORT_2, 1, MU, PAR, 0x6001, 0x7e01, { RDST, ATSIGN, RSRC, PLUS } },
  { "ld", SHORT_2, 1, MU, PAR, 0x6000, 0x7e01, { RDST, ATSIGN, RSRC } },
  { "ld2w", LONG_L, 1, MU, SEQ, 0x31000000, 0x3f100000, { RDSTE, ATPAR, NUM16, RSRC } },
  { "ld2w", SHORT_2, 1, MU, PAR, 0x6601, 0x7e21, { RDSTE, ATSIGN, RSRC, MINUS } },
  { "ld2w", SHORT_2, 1, MU, PAR, 0x6201, 0x7e21, { RDSTE, ATSIGN, RSRC, PLUS } },
  { "ld2w", SHORT_2, 1, MU, PAR, 0x6200, 0x7e21, { RDSTE, ATSIGN, RSRC } },
  { "ldb", LONG_L, 1, MU, SEQ, 0x38000000, 0x3f000000, { RDST, ATPAR, NUM16, RSRC } },
  { "ldb", SHORT_2, 1, MU, PAR, 0x7000, 0x7e01, { RDST, ATSIGN, RSRC } },
  { "ldi", LONG_L, 1, MU, SEQ, 0x20000000, 0x3f0f0000, { RDST, NUM16 } },
  { "ldi", SHORT_2, 1, EITHER, PAR,0x4001, 0x7e01 , { RDST, NUM4 } },
  { "ldub", LONG_L, 1, MU, SEQ, 0x39000000, 0x3f000000, { RDST, ATPAR, NUM16, RSRC } },
  { "ldub", SHORT_2, 1, MU, PAR, 0x7200, 0x7e01, { RDST, ATSIGN, RSRC } },
  { "mac", SHORT_2, 1, IU, PAR, 0x2a00, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "macsu", SHORT_2, 1, IU, PAR, 0x1a00, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "macu", SHORT_2, 1, IU, PAR, 0x3a00, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "max", SHORT_2, 1, IU, PAR, 0x2600, 0x7e01, { RDST, RSRC } },
  { "max", SHORT_2, 1, IU, PAR, 0x3600, 0x7ee3, { ADST, RSRCE } },
  { "max", SHORT_2, 1, IU, PAR, 0x3602, 0x7eef, { ADST, ASRC } },
  { "min", SHORT_2, 1, IU, PAR, 0x2601, 0x7e01 , { RDST, RSRC } },
  { "min", SHORT_2, 1, IU, PAR, 0x3601, 0x7ee3 , { ADST, RSRCE } },
  { "min", SHORT_2, 1, IU, PAR, 0x3603, 0x7eef, { ADST, ASRC } },
  { "msb", SHORT_2, 1, IU, PAR, 0x2800, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "msbsu", SHORT_2, 1, IU, PAR, 0x1800, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "msbu", SHORT_2, 1, IU, PAR, 0x3800, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "mul", SHORT_2, 1, IU, PAR, 0x2e00, 0x7e01 , { RDST, RSRC } },
  { "mulx", SHORT_2, 1, IU, PAR, 0x2c00, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "mulxsu", SHORT_2, 1, IU, PAR, 0x1c00, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "mulxu", SHORT_2, 1, IU, PAR, 0x3c00, 0x7e00, { ADST0, RSRC2, RSRC } },
  { "mv", SHORT_2, 1, IU, PAR, 0x4000, 0x7e01, { RDST, RSRC } },
  { "mv2w", SHORT_2, 1, IU, PAR, 0x5000, 0x7e23, { RDSTE, RSRCE } },
  { "mv2wfac", SHORT_2, 1, IU, PAR, 0x3e00, 0x7e2f, { RDSTE, ASRC } },
  { "mv2wtac", SHORT_2, 1, IU, PAR, 0x3e01, 0x7ee3, { RSRCE, ADST } },
  { "mvac", SHORT_2, 1, IU, PAR, 0x3e03, 0x7eef, { ADST, ASRC } },
  { "mvb", SHORT_2, 1, IU, PAR, 0x5400, 0x7e01, { RDST, RSRC } },
  { "mvf0f", SHORT_2, 1, EITHER, PAR, 0x4400, 0x7e01, { RDST, RSRC } },
  { "mvf0t", SHORT_2, 1, EITHER, PAR, 0x4401, 0x7e01, { RDST, RSRC } },
  { "mvfacg", SHORT_2, 1, IU, PAR, 0x1e04, 0x7e0f, { RDST, ASRC } },
  { "mvfachi", SHORT_2, 1, IU, PAR, 0x1e00, 0x7e0f, { RDST, ASRC } },
  { "mvfaclo", SHORT_2, 1, IU, PAR, 0x1e02, 0x7e0f, { RDST, ASRC } },
  { "mvfc", SHORT_2, 1, MU, PAR, 0x5200, 0x7e01, { RDST, CSRC } },
  { "mvtacg", SHORT_2, 1, IU, PAR, 0x1e41, 0x7ee1, { RSRC, ADST } },
  { "mvtachi", SHORT_2, 1, IU, PAR, 0x1e01, 0x7ee1, { RSRC, ADST } },
  { "mvtaclo", SHORT_2, 1, IU, PAR, 0x1e21, 0x7ee1, { RSRC, ADST } },
  { "mvtc", SHORT_2, 1, MU, PAR, 0x5600, 0x7e01, { RSRC, CDST } },
  { "mvub", SHORT_2, 1, IU, PAR, 0x5401, 0x7e01, { RDST, RSRC } },
  { "neg", SHORT_2, 1, EITHER, PAR, 0x4605, 0x7e1f, { RDST } },
  { "neg", SHORT_2, 1, IU, PAR, 0x5605, 0x7eff, { ADST } },
  { "nop", SHORT_2, 1, EITHER, PAR, 0x5e00, 0x7fff, { 0 } },
  { "not", SHORT_2, 1, EITHER, PAR, 0x4603, 0x7e1f, { RDST } },
  { "or", SHORT_2, 1, EITHER, PAR, 0x800, 0x7e01, { RDST, RSRC } },
  { "or3", LONG_L, 1, MU, SEQ, 0x4000000, 0x3f000000, { RDST, RSRC, NUM16 } },
  { "rac", SHORT_2, 1, IU, PAR, 0x5201, 0x7e21, { RDSTE, ASRC, NUM3 } },
  { "rachi", SHORT_2, 1, IU, PAR, 0x4201, 0x7e01, { RDST, ASRC, NUM3 } },
  { "rep", LONG_L, 2, MU, SEQ, 0x27000000, 0x3ff00000, { RSRC, ANUM16 } },
  { "repi", LONG_L, 2, MU, SEQ, 0x2f000000, 0x3f000000, { NUM8, ANUM16 } },
  { "rtd", SHORT_2, 3, MU, PAR, 0x5f60, 0x7fff, { 0 } },
  { "rte", SHORT_2, 3, MU, PAR, 0x5f40, 0x7ff, { 0 } },
  { "sadd", SHORT_2, 1, IU, PAR, 0x1223, 0x7eef, { ADST, ASRC } },
  { "setf0f", SHORT_2, 1, MU, PAR, 0x4611, 0x7e1f, { RDST } },
  { "setf0t", SHORT_2, 1, MU, PAR, 0x4613, 0x7e1f, { RDST } },
  { "sleep", SHORT_2, 1, MU, PAR, 0x5fc0, 0x7fff, { 0 } },
  { "sll", SHORT_2, 1, IU, PAR, 0x2200, 0x7e01, { RDST, RSRC } },
  { "sll", SHORT_2, 1, IU, PAR, 0x3200, 0x7ee1, { ADST, RSRC } },
  { "slli", SHORT_2, 1, IU, PAR, 0x2201, 0x7e01, { RDST, NUM4 } },
  { "slli", SHORT_2, 1, IU, PAR, 0x3201, 0x7ee1, { ADST, NUM4 } },
  { "slx", SHORT_2, 1, IU, PAR, 0x460b, 0x7e1f, { RDST } },
  { "sra", SHORT_2, 1, IU, PAR, 0x2400, 0x7e01, { RDST, RSRC } },
  { "sra", SHORT_2, 1, IU, PAR, 0x3400, 0x7ee1, { ADST, RSRC } },
  { "srai", SHORT_2, 1, IU, PAR, 0x2401, 0x7e01, { RDST, NUM4 } },
  { "srai", SHORT_2, 1, IU, PAR, 0x3401, 0x7ee1, { ADST, NUM4 } },
  { "srl", SHORT_2, 1, IU, PAR, 0x2000, 0x7e01, { RDST, RSRC } },
  { "srl", SHORT_2, 1, IU, PAR, 0x3000, 0x7ee1, { ADST, RSRC } },
  { "srli", SHORT_2, 1, IU, PAR, 0x2001, 0x7e01, { RDST, NUM4 } },
  { "srli", SHORT_2, 1, IU, PAR, 0x3001, 0x7ee1, { ADST, NUM4 } },
  { "srx", SHORT_2, 1, IU, PAR, 0x4609, 0x7e1f, { RDST } },
  { "st", LONG_L, 1, MU, SEQ, 0x34000000, 0x3f000000, { RSRC2, ATPAR, NUM16, RSRC } },
  { "st", SHORT_2, 1, MU, PAR, 0x6800, 0x7e01, { RSRC2, ATSIGN, RSRC } },
  { "st", SHORT_2, 1, MU, PAR, 0x6c1f, 0x7e1f, { RSRC2, ATMINUS, RSRC } },
  { "st", SHORT_2, 1, MU, PAR, 0x6801, 0x7e01, { RSRC2, ATSIGN, RSRC, PLUS } },
  { "st", SHORT_2, 1, MU, PAR, 0x6c01, 0x7e01, { RSRC2, ATSIGN, RSRC, MINUS } },
  { "st2w", LONG_L, 1, MU, SEQ, 0x35000000, 0x3f100000, { RSRC2E, ATPAR, NUM16, RSRC } },
  { "st2w", SHORT_2, 1, MU, PAR, 0x6a00, 0x7e21, { RSRC2E, ATSIGN, RSRC } },
  { "st2w", SHORT_2, 1, MU, PAR, 0x6e1f, 0x7e3f, { RSRC2E, ATMINUS, RSRC } },
  { "st2w", SHORT_2, 1, MU, PAR, 0x6a01, 0x7e21, { RSRC2E, ATSIGN, RSRC, PLUS } },
  { "st2w", SHORT_2, 1, MU, PAR, 0x6e01, 0x7e21, { RSRC2E, ATSIGN, RSRC, MINUS } },
  { "stb", LONG_L, 1, MU, SEQ, 0x3c000000, 0x3f000000, { RSRC2, ATPAR, NUM16, RSRC } },
  { "stb", SHORT_2, 1, MU, PAR, 0x7800, 0x7e01, { RSRC2, ATSIGN, RSRC } },
  /*  { "stop", SHORT_2, 1, MU, PAR, 0x5fe0, 0x7fff, { 0 } }, */
  { "sub", SHORT_2, 1, EITHER, PAR, 0x0, 0x7e01, { RDST, RSRC } },
  { "sub2w", SHORT_2, 1, IU, PAR, 0x1000, 0x7e23, { RDSTE, RSRCE } },
  { "subac3", LONG_R, 1, IU, SEQ, 0x17000000, 0x3ffffe22, { RDSTE, RSRCE, ASRC0 } },
  { "subac3", LONG_R, 1, IU, SEQ, 0x17000002, 0x3ffffe2e, { RDSTE, ASRC, ASRC0 } },
  { "subac3s", LONG_R, 1, IU, SEQ, 0x17001000, 0x3ffffe22, { RDSTE, RSRCE, ASRC0 } },
  { "subac3s", LONG_R, 1, IU, SEQ, 0x17001002, 0x3ffffe2e, { RDSTE, ASRC, ASRC0 } },
  { "subi", SHORT_2, 1, EITHER, PAR, 0x1, 0x7e01, { RDST, NUM4 } },
  { "trap", SHORT_2, 5, MU, PAR, 0x5f00, 0x7fe1, { NUM4 } },
  { "tst0i", LONG_L, 1, MU, SEQ, 0x7000000, 0x3f0f0000, { RSRC2, NUM16 } },
  { "tst1i", LONG_L, 1, MU, SEQ, 0xf000000, 0x3f0f0000, { RSRC2, NUM16 } },
  { "wait", SHORT_2, 1, MU, PAR, 0x5f80, 0x7fff, { 0 } },
  { "xor", SHORT_2, 1, EITHER, PAR, 0xa00, 0x7e01, { RDST, RSRC } },
  { "xor3", LONG_L, 1, MU, SEQ, 0x5000000, 0x3f000000, { RDST, RSRC, NUM16 } },
  { 0, 0, 0, 0, 0, 0, 0, { 0 } },
};


