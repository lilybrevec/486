/*
 *    int.h  ( List 7-2 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    ���̃t�@�C���́w�͂��߂ēǂ�486�x�i�A�X�L�[�o�ŋǁj�Ɍf�ڂ���
 *    �v���O�����̈ꕔ�ł��B�v���O�������e�◘�p���@�ɂ��Ă͖{����
 *    �L�q���Q�Ƃ��Ă��������B
 */

/*
 *    List 7-2  �w�b�_�t�@�C��
 *              [int.h  1/1] (page 243)
 */

#define IDTNUM 256
#define FLAG_INT_ENABLE  0x200

typedef void    IntFunc(
  unsigned short di, unsigned short si, unsigned short bp,
  unsigned short sp, unsigned short bx, unsigned short dx,
  unsigned short cx, unsigned short ax, unsigned short es,
  unsigned short ds, unsigned short n, long eip,
  unsigned short cs, unsigned short f1, unsigned eflags
);
extern IntFunc     *IntHandler;
extern DescTblPtr  idtptr,ridtptr;
extern void        (*IntHook)(int n, unsigned short cs,
                                           unsigned short ip);

void SetIDTGateDesc(int i, unsigned short sel, void (*f)(),
                   unsigned short count, unsigned char type,
                                           unsigned char dpl);
void SetUpIDT(unsigned char dpl);
void    RealModeInt(
  unsigned short di, unsigned short si, unsigned short bp,
  unsigned short sp, unsigned short bx, unsigned short dx,
  unsigned short cx, unsigned short ax, unsigned short es,
  unsigned short ds, unsigned short n, long eip, 
  unsigned short cs, unsigned short f1, unsigned eflags
);
void RealToProto_I(int sw);
void ProtoToReal_I(void);

void lidt(DescTblPtr *idtptr);
void EnableInterrupt(void);
void DisableInterrupt(void);

#ifdef PC98
#define KEYINTVEC 9
#define TIMERVEC 0x0A
#else /* PC/AT */
#define KEYINTVEC 9
#define TIMERVEC 8
#endif
