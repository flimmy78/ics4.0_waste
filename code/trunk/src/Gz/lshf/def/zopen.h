#ifndef __zopen__H
#define __zopen__H

#ifdef __cplusplus
extern "C"
{
#endif

#include <sys/types.h>
#include <sys/stat.h>

#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

#ifdef _WIN32
	#include <io.h>
	#include <windows.h>
	typedef unsigned char u_char;
	typedef unsigned short u_short;
	typedef unsigned int u_int;
#else
#include <unistd.h>
#include <sys/param.h>
#endif

#define	BITS		16		/* Default bits. */
#define	HSIZE		69001		/* 95% occupancy */
#define	ZBUFSIZ		8192		/* I/O buffer size */

#define LZW_MAGIC "\037\235"

/* A code_int must be able to hold 2**BITS values of type int, and also -1. */
typedef long code_int;
typedef long count_int;

#define	BIT_MASK	0x1f		/* Defines for third byte of header. */
#define	BLOCK_MASK	0x80

/*
 * Masks 0x40 and 0x20 are free.  I think 0x20 should mean that there is
 * a fourth header byte (for expansion).
 */
#define	INIT_BITS 9			/* Initial number of bits/code. */

#define	MAXCODE(n_bits)	((1 << (n_bits)) - 1)



#define	CHECK_GAP 10000		/* Ratio check interval. */

/*
 * the next two codes should not be changed lightly, as they must not
 * lie within the contiguous general code space.
 */
#define	FIRST	257		/* First free entry. */
#define	CLEAR	256		/* Table clear output code. */

#ifdef _KRC_
struct ZHead
{
	u_char* zs_pIn;	/* source data */
	u_char* zs_pOut;	/* object data */
	int len_in; 
	int len_out;
	int len_hasRead; 
	int len_hasWritten;
	int zs_remain;
	char zs_mode;			/* r or w */
	enum {
		S_START, S_MIDDLE, S_EOF
	} zs_state;				/* State of computation */
	int zs_n_bits;			/* Number of bits/code. */
	int zs_maxbits;			/* User settable max # bits/code. */
	code_int zs_maxcode;		/* Maximum code, given n_bits. */
	code_int zs_maxmaxcode;		/* Should NEVER generate this code. */
	count_int zs_htab [HSIZE];
	u_short zs_codetab [HSIZE];
	code_int zs_hsize;		/* For dynamic table sizing. */
	code_int zs_free_ent;	/* First unused entry. */
	/*
	 * Block compression parameters -- after all codes are used up,
	 * and compression rate changes, start over.
	 */
	int zs_block_compress;
	int zs_clear_flg;
	long zs_ratio;
	count_int zs_checkpoint;
	long zs_in_count;		/* Length of input. */
	long zs_bytes_out;		/* Length of compressed output. */
	long zs_out_count;		/* # of codes output (for debugging).*/
	u_char zs_buf[ZBUFSIZ];	/* I/O buffer */
	u_char *zs_bp;			/* Current I/O window in the zs_buf */
	int zs_offset;			/* Number of bits in the zs_buf */
	union {
		struct {
			long zs_fcode2;
			code_int zs_ent2;
			code_int zs_hsize_reg2;
			int zs_hshift2;
		} w;			/* Write paramenters */
		struct {
			u_char *zs_stackp2, *zs_ebp2;
			int zs_finchar2;
			code_int zs_code2, zs_oldcode2, zs_incode2;
			int zs_size2;
		} r;			/* Read parameters */
	} u;
};

#define zs_fcode	u.w.zs_fcode2
#define zs_ent		u.w.zs_ent2
#define zs_hsize_reg	u.w.zs_hsize_reg2
#define zs_hshift	u.w.zs_hshift2

#define zs_stackp	u.r.zs_stackp2
#define zs_finchar	u.r.zs_finchar2
#define zs_code		u.r.zs_code2
#define zs_oldcode	u.r.zs_oldcode2
#define zs_incode	u.r.zs_incode2
#define zs_size		u.r.zs_size2
#define zs_ebp		u.r.zs_ebp2

#else
struct ZHead
{
	u_char* zs_pIn;	/* source data */
	u_char* zs_pOut;	/* object data */
	int len_in; 
	int len_out;
	int len_hasRead; 
	int len_hasWritten;
	int zs_remain;
	char zs_mode;			/* r or w */
	enum {
		S_START, S_MIDDLE, S_EOF
	} zs_state;				/* State of computation */
	int zs_n_bits;			/* Number of bits/code. */
	int zs_maxbits;			/* User settable max # bits/code. */
	code_int zs_maxcode;		/* Maximum code, given n_bits. */
	code_int zs_maxmaxcode;		/* Should NEVER generate this code. */
	count_int zs_htab [HSIZE];
	u_short zs_codetab [HSIZE];
	code_int zs_hsize;		/* For dynamic table sizing. */
	code_int zs_free_ent;	/* First unused entry. */
	/*
	 * Block compression parameters -- after all codes are used up,
	 * and compression rate changes, start over.
	 */
	int zs_block_compress;
	int zs_clear_flg;
	long zs_ratio;
	count_int zs_checkpoint;
	long zs_in_count;		/* Length of input. */
	long zs_bytes_out;		/* Length of compressed output. */
	long zs_out_count;		/* # of codes output (for debugging).*/
	u_char zs_buf[ZBUFSIZ];	/* I/O buffer */
	u_char *zs_bp;			/* Current I/O window in the zs_buf */
	int zs_offset;			/* Number of bits in the zs_buf */
	union {
		struct {
			long zs_fcode;
			code_int zs_ent;
			code_int zs_hsize_reg;
			int zs_hshift;
		} w;			/* Write paramenters */
		struct {
			u_char *zs_stackp, *zs_ebp;
			int zs_finchar;
			code_int zs_code, zs_oldcode, zs_incode;
			int zs_size;
		} r;			/* Read parameters */
	} u;
};

#define zs_fcode	u.w.zs_fcode
#define zs_ent		u.w.zs_ent
#define zs_hsize_reg	u.w.zs_hsize_reg
#define zs_hshift	u.w.zs_hshift
#define zs_stackp	u.r.zs_stackp
#define zs_finchar	u.r.zs_finchar
#define zs_code		u.r.zs_code
#define zs_oldcode	u.r.zs_oldcode
#define zs_incode	u.r.zs_incode
#define zs_size		u.r.zs_size
#define zs_ebp		u.r.zs_ebp

#endif

#define Z_BUFSIZE 16384

#ifdef __cplusplus
}
#endif

#endif
