/** @file pack_address.h
 *  @brief contains packing and masking macros
 *
 *  @author Heather Arthur (harthur)
 */

#ifndef __PACK_ADDRESS_H
#define __PACK_ADDRESS_H

/* masking macros */
#define LOWER8(p)       ((p) & 0xFF)
#define UPPER8(p)       (((p) & 0xFF00) >> 8)
#define LOWER16(p)      ((p) & 0xFFFF)
#define UPPER16(p)      (((p) & 0xFFFF0000) >> 16)


/* pack the upper offset for the trap gate */
#define OFF_PACK(off)  ((UPPER16(off)) << 16)
/* pack the segment selector for the trap gate */
#define SS_PACK(ss)    ((ss) << 16)
/* pack the dpl for the trap gate */
#define DPL_PACK(dpl)  ((dpl) << 13)
/* pack the gate size for the trap gate */
#define D_PACK(d)      (((d) << 11) | (0x7 << 8))
/* pack the present for the trap gate */
#define P_PACK(p)      ((p) << 15)
/* pack least significant bits of trap gate */
#define LSB_PACK(off, ss)   ((SS_PACK(ss)) | (LOWER16(off)))
/* pack most significant bits of trap gate */
#define MSB_PACK(off, dpl,d ,p) ((OFF_PACK(off)) | (DPL_PACK(dpl)) | (D_PACK(d)) | (P_PACK(p)))
/* pack the trap gate */
#define TRAP_PACK(off,ss,dpl,d,p) ((LSB_PACK(off,ss)) | (((long long)MSB_PACK(off,dpl,d,p)) << 32))   

#endif 
