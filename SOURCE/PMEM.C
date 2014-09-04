/*
 *    pmem.c  ( List 5-22 )
 *    Copyright (C) Teruhisa Kamachi and ASCII Corp. 1994
 *    All rights reserved.
 *
 *    ���̃t�@�C���́w�͂��߂ēǂ�486�x�i�A�X�L�[�o�ŋǁj�Ɍf�ڂ���
 *    �v���O�����̈ꕔ�ł��B�v���O�������e�◘�p���@�ɂ��Ă͖{����
 *    �L�q���Q�Ƃ��Ă��������B
 */

/*
 *    List 5-22  1M�o�C�g�𒴂���A�h���X�ɏ������݂�ǂݏo�����s�����߂̊֐��Q
 *               [pmem.c  1/1] (page 169)
 */

#include <dos.h>
#include "proto.h"
#include "pmem.h"
#define min(a,b) (a)<(b)?(a):(b)

void MemTransfer(unsigned long,unsigned long,unsigned long);
unsigned long GetPmemBufSize(void);

void InitPmemBuf(void)
{
    RealToProto();
    SetPmemBufSize(0L);
    ProtoToReal();
}

void SetPmemBufSize(unsigned long m)
{
    MemTransfer(0x100000L,
        SegToLinier(seg.ds, (unsigned short)&m),
        (unsigned long) sizeof(m));
}

unsigned long GetPmemBufSize()
{
    unsigned long m;

    MemTransfer(SegToLinier(seg.ds, (unsigned short)&m),
        0x100000L, (unsigned long) sizeof(m));
    return m;
}

void PutPmemBuf(char *buf, unsigned long m)
{
    unsigned long s;

    s = GetPmemBufSize();
    MemTransfer(0x100000L+sizeof(s)+s,
        SegToLinier(seg.ds, (unsigned short)buf), m);
    SetPmemBufSize(s+m);
}

unsigned long GetPmemBuf(char *buf, unsigned long s, unsigned long m)
{
    unsigned long mm;

    mm = min(GetPmemBufSize()-s, m);
    if (mm>0)
        MemTransfer( SegToLinier(seg.ds, (unsigned short)buf),
            0x100000L+sizeof(s)+s, mm);
    return mm;
}
