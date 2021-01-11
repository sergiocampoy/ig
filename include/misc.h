#ifndef _MENU_H
#define _MENU_H

// selección de objeto
#define OBJ_ALL 0b111111111111

#define OBJ_CUB 0b1
#define OBJ_TET 0b10
#define OBJ_CON 0b100
#define OBJ_ESF 0b1000
#define OBJ_FLE 0b10000
#define OBJ_HAB 0b100000
#define OBJ_MES 0b1000000
#define OBJ_MON 0b10000000
#define OBJ_LAT 0b100000000
#define OBJ_PE1 0b1000000000
#define OBJ_PE2 0b10000000000
#define OBJ_TAP 0b100000000000
/*
#define OBJ_ALL 0b11111

#define OBJ_CUB 0b1
#define OBJ_TET 0b10
#define OBJ_PLY 0b100
#define OBJ_REV 0b1000
#define OBJ_TAP 0b10000
*/


// selección de modo de visualización
#define VIS_ALL 0b11111

#define VIS_PUN 0b1
#define VIS_LIN 0b10
#define VIS_SOL 0b100
#define VIS_AJE 0b1000
#define VIS_TEX 0b10000


// colores terminal

#define RST   "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define FRED(x) KRED x RST
#define FGRN(x) KGRN x RST
#define FYEL(x) KYEL x RST
#define FBLU(x) KBLU x RST
#define FMAG(x) KMAG x RST
#define FCYN(x) KCYN x RST
#define FWHT(x) KWHT x RST

#define BOLD(x) "\x1B[1m" x RST
#define UNDL(x) "\x1B[4m" x RST

#endif