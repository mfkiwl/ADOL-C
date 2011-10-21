
/*----------------------------------------------------------------------------
 ADOL-C -- Automatic Differentiation by Overloading in C++
 File:     uni5_for.c


 Revision: $Id$

 Contents: Contains the routines :
           zos_forward (zero-order-scalar forward mode):      define _ZOS_
           fos_forward (first-order-scalar forward mode):     define _FOS_
           hos_forward (higher-order-scalar forward mode):    define _HOS_
           fov_forward (first-order-vector forward mode):     define _FOV_
           hov_forward (higher-order-vector forward mode):    define _HOV_
           hov_wk_forward (higher-order-vector forward mode): define _HOV_WK_
	   int_forward_safe:                                  define _INT_FOR_ and _NTIGHT__

           Uses the preprocessor to compile the 7 different object files
           with/without "keep" parameter:                     define _KEEP_

 Copyright (c) Andrea Walther, Andreas Griewank, Andreas Kowarz,
               Hristo Mitev, Sebastian Schlenkrich, Jean Utke, Olaf Vogel,
               Benjamin Letschert

 This file is part of ADOL-C. This software is provided as open source.
 Any use, reproduction, or distribution of the software constitutes
 recipient's acceptance of the terms of the accompanying license file.

----------------------------------------------------------------------------*/

#include <adolc/interfaces.h>
#include <adolc/adalloc.h>
#include <adolc/taping.h>
#include "taping_p.h"
#include <adolc/oplate.h>
#include <adolc/externfcts.h>
#include "externfcts_p.h"

#include <math.h>

#if defined(ADOLC_DEBUG)
#include <string.h>
#endif /* ADOLC_DEBUG */

#if defined(_MPI_)
#include <adolc/adolc_mpi.h>
#endif

/****************************************************************************/
/*                                                                   MACROS */
#undef _ADOLC_VECTOR_
#undef _HIGHER_ORDER_



/*--------------------------------------------------------------------------*/
#if defined(_ZOS_)
#if defined(_MPI_)
#  define GENERATED_FILENAME "zos_forward_mpi"
#else
#  define GENERATED_FILENAME "zos_forward"
#endif
/*--------------------------------------------------------------------------*/
#else
#if defined(_FOS_)
#if defined(_MPI_)
#define GENERATED_FILENAME "fos_forward_mpi"
#else
#define GENERATED_FILENAME "fos_forward"
#endif

#define ARGUMENT(indexi,l,i) argument[indexi]
#define TAYLORS(indexd,l,i)   taylors[indexd]

/*--------------------------------------------------------------------------*/
#else
#if defined(_FOV_)
#if defined(_MPI_)
#define GENERATED_FILENAME "fov_forward_mpi"
#else
#define GENERATED_FILENAME "fov_forward"
#endif

#define _ADOLC_VECTOR_

#if defined(_CHUNKED_)
#define ARGUMENT(indexi,l,i) argument[indexi][l+offset]
#define TAYLORS(indexd,l,i)   taylors[indexd][l+offset]
#else
#define ARGUMENT(indexi,l,i) argument[indexi][l]
#define TAYLORS(indexd,l,i)   taylors[indexd][l]
#endif

/*--------------------------------------------------------------------------*/
#else
#if defined(_HOS_)
#if defined(_MPI_)
#define GENERATED_FILENAME "hos_forward_mpi"
#else
#define GENERATED_FILENAME "hos_forward"
#endif

#define _HIGHER_ORDER_

#define ARGUMENT(indexi,l,i) argument[indexi][i]
#define TAYLORS(indexd,l,i)   taylors[indexd][i]

/*--------------------------------------------------------------------------*/
#else
#if defined(_HOV_)
#if defined(_MPI_)
#define GENERATED_FILENAME "hov_forward_mpi"
#else
#define GENERATED_FILENAME "hov_forward"
#endif

#define _ADOLC_VECTOR_
#define _HIGHER_ORDER_

#define ARGUMENT(indexi,l,i) argument[indexi][l][i]
#define TAYLORS(indexd,l,i)   taylors[indexd][l][i]

/*--------------------------------------------------------------------------*/
#else
#if defined(_HOV_WK_)
#define GENERATED_FILENAME "hov_wk_forward"

#define _ADOLC_VECTOR_
#define _HIGHER_ORDER_

#define ARGUMENT(indexi,l,i) argument[indexi][l][i]
#define TAYLORS(indexd,l,i)   taylors[indexd][l][i]

/*--------------------------------------------------------------------------*/
#else
#if defined(_INT_FOR_)
#if defined(_TIGHT_)
#if defined(_MPI_)
#define GENERATED_FILENAME "int_forward_t_mpi"
#else
#define GENERATED_FILENAME "int_forward_t"
#endif
#endif

#if defined(_NTIGHT_)
#if defined(_MPI_)
#define GENERATED_FILENAME "int_forward_s_mpi"
#else
#define GENERATED_FILENAME "int_forward_s"
#endif
#endif
#define ARGUMENT(indexi,l,i) argument[indexi][l]
#define TAYLORS(indexd,l,i)   taylors[indexd][l]
/*--------------------------------------------------------------------------*/
#else
#if defined(_INDO_)
void copy_index_domain(int res, int arg, locint **ind_dom);
void merge_2_index_domains(int res, int arg, locint **ind_dom);
void combine_2_index_domains(int res, int arg1, int arg2, locint **ind_dom);
void merge_3_index_domains(int res, int arg1, int arg2, locint **ind_dom);
#if defined(_MPI_)
void combine_index_domain_received_data(int res, int count, locint **ind_dom, locint *trade);
#endif

#define NUMNNZ 20
#define FMIN_ADOLC(x,y)  ((y<x)?y:x)

#if defined(_INDOPRO_)
#if defined(_TIGHT_)
#if defined(_MPI_)
#define GENERATED_FILENAME "indopro_forward_t_mpi"
#else
#define GENERATED_FILENAME "indopro_forward_t"
#endif
#endif

#if defined(_NTIGHT_)
#if defined(_MPI_)
#define GENERATED_FILENAME "indopro_forward_s_mpi"
#else
#define GENERATED_FILENAME "indopro_forward_s"
#endif
#endif
#endif
#if defined(_NONLIND_)

/*
 * This is the type used for the list elements. The entry is either a counter
 * (first element of the NID list) or the index of an independent variable.
 */

void extend_nonlinearity_domain_binary_step
(int arg1, int arg2, locint **ind_dom, locint **nonl_dom);
void extend_nonlinearity_domain_unary
(int arg, locint **ind_dom, locint **nonl_dom);
void extend_nonlinearity_domain_binary
(int arg1, int arg2, locint **ind_dom, locint **nonl_dom);

#if defined(_MPI_)
void extend_nonlinearity_domain_combine_received_trade
(int arg1, int counts, locint **nonl_dom, locint *trade);
#endif


#if defined(_TIGHT_)
#if defined(_MPI_)
#define GENERATED_FILENAME "nonl_ind_forward_t_mpi"
#else
#define GENERATED_FILENAME "nonl_ind_forward_t"
#endif
#endif

#if defined(_NTIGHT_)
#if defined(_MPI_)
#define GENERATED_FILENAME "nonl_ind_forward_s_mpi"
#else
#define GENERATED_FILENAME "nonl_ind_forward_s"
#endif
#endif
#endif


/*--------------------------------------------------------------------------*/
#else
#error Error ! Define [_ZOS_ | _FOS_ |\
   _HOS_ | _FOV_ | _HOV_ | _HOV_WK_  | _INT_FOR_SAFE_ | _INT_FOR_TIGHT_ | _INDOPRO_ | _NONLIND_ ] [{_KEEP_}]
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------------------*/
/*                                                               KEEP stuff */
#if defined(_KEEP_)

#if defined(_HOV_WK_) /* keep in this vector mode */
#define IF_KEEP_TAYLOR_CLOSE \
if (keep){\
  fprintf(DIAG_OUT,"Succeeding reverse sweep will fail!\n");\
  taylor_close(0);\
}
#define IF_KEEP_WRITE_TAYLOR(res,keep,k,p) \
    { \
        UPDATE_TAYLORWRITTEN(keep * k * p) \
        if (keep) \
        { \
            ADOLC_WRITE_SCAYLOR(dp_T0[res]); \
            if (keep > 1) \
            write_taylors(res,(keep-1),k,p); \
        } \
    }
#else
#if defined(_ADOLC_VECTOR_) /* otherwise no keep */
#define IF_KEEP_TAYLOR_CLOSE
#define IF_KEEP_WRITE_TAYLOR(res,keep,k,p)
#else /* _ZOS_, _FOS_, _HOS_ */
#define IF_KEEP_TAYLOR_CLOSE \
if (keep){\
  fprintf(DIAG_OUT,"Otherwise succeeding reverse sweep will fail!\n");\
  taylor_close(0);\
}
#if defined(_ZOS_)
#define IF_KEEP_WRITE_TAYLOR(res,keep,k,p) \
    { \
        UPDATE_TAYLORWRITTEN(keep) \
        if (keep) \
            ADOLC_WRITE_SCAYLOR(dp_T0[res]); \
    }
#else
#if defined(_FOS_)
#define IF_KEEP_WRITE_TAYLOR(res,keep,k,p) \
    { \
        UPDATE_TAYLORWRITTEN(keep) \
        if (keep) \
        { \
            ADOLC_WRITE_SCAYLOR(dp_T0[res]); \
            if (keep > 1) \
                ADOLC_WRITE_SCAYLOR(dp_T[res]); \
        } \
    }
#else
#if defined(_HOS_)
#define IF_KEEP_WRITE_TAYLOR(res,keep,k,p) \
    { \
        UPDATE_TAYLORWRITTEN(keep) \
        if (keep) \
        { \
            ADOLC_WRITE_SCAYLOR(dp_T0[res]); \
            if (keep > 1) \
                write_taylor(res,keep-1); \
        } \
    }
#endif
#endif
#endif
#endif
#endif

#else  /* no _KEEP_ */
#define IF_KEEP_TAYLOR_CLOSE
#define IF_KEEP_WRITE_TAYLOR(res,keep,k,p)
#endif

/*--------------------------------------------------------------------------*/
/*                                                      access to variables */
#if !defined(_ZOS_)
#if defined(_FOS_)
#define TRES         *Tres
#define TARG         *Targ
#define TARG1        *Targ1
#define TARG2        *Targ2
#define TQO          *Tqo

#define TRES_INC     *Tres
#define TARG_INC     *Targ
#define TARG1_INC    *Targ1
#define TARG2_INC    *Targ2
#define TQO_INC      *Tqo

#define TRES_DEC     *Tres
#define TARG_DEC     *Targ
#define TARG1_DEC    *Targ1
#define TARG2_DEC    *Targ2
#define TQO_DEC      *Tqo

#define TRES_FOINC   *Tres
#define TARG_FOINC   *Targ
#define TARG1_FOINC  *Targ1
#define TARG2_FOINC  *Targ2
#define TQO_FOINC    *Tqo

#define TRES_FODEC   *Tres
#define DEC_TRES_FO
#define TARG_FODEC   *Targ
#define TARG1_FODEC  *Targ1
#define TARG2_FODEC  *Targ2
#define TQO_FODEC    *Tqo

#define ASSIGN_T(a,b)  a = &b;

#else
#if defined(_INT_FOR_)
#define TRES         *Tres
#define TARG         *Targ
#define TARG1        *Targ1
#define TARG2        *Targ2
#define TQO          *Tqo

#define TRES_INC     *Tres++
#define TARG_INC     *Targ++
#define TARG1_INC    *Targ1++
#define TARG2_INC    *Targ2++
#define TQO_INC      *Tqo++

#define TRES_DEC     *Tres--
#define TARG_DEC     *Targ--
#define TARG1_DEC    *Targ1--
#define TARG2_DEC    *Targ2--
#define TQO_DEC      *Tqo--

#define TRES_FOINC   *Tres++
#define TARG_FOINC   *Targ++
#define TARG1_FOINC  *Targ1++
#define TARG2_FOINC  *Targ2++
#define TQO_FOINC    *Tqo++

#define TRES_FODEC   *Tres--
#define TARG_FODEC   *Targ--
#define TARG1_FODEC  *Targ1--
#define TARG2_FODEC  *Targ2--
#define TQO_FODEC    *Tqo--


#define ASSIGN_T(a,b)  a = b;

#else  /* _HOS_, _FOV_, _HOV_, _HOV_WK */
#define TRES         *Tres
#define TARG         *Targ
#define TARG1        *Targ1
#define TARG2        *Targ2
#define TQO          *Tqo

#define TRES_INC     *Tres++
#define TARG_INC     *Targ++
#define TARG1_INC    *Targ1++
#define TARG2_INC    *Targ2++
#define TQO_INC      *Tqo++

#define TRES_DEC     *Tres--
#define TARG_DEC     *Targ--
#define TARG1_DEC    *Targ1--
#define TARG2_DEC    *Targ2--
#define TQO_DEC      *Tqo--

#if defined(_FOV_)
#define TRES_FOINC   *Tres++
#define TARG_FOINC   *Targ++
#define TARG1_FOINC  *Targ1++
#define TARG2_FOINC  *Targ2++
#define TQO_FOINC    *Tqo++

#define TRES_FODEC   *Tres
#define DEC_TRES_FO  Tres--;
#define TARG_FODEC   *Targ--
#define TARG1_FODEC  *Targ1--
#define TARG2_FODEC  *Targ2--
#define TQO_FODEC    *Tqo--
#else /* _HOS_, _HOV_, _HOV_WK */
#define TRES_FOINC   *Tres
#define TARG_FOINC   *Targ
#define TARG1_FOINC  *Targ1
#define TARG2_FOINC  *Targ2
#define TQO_FOINC    *Tqo

#define TRES_FODEC   *Tres
#define DEC_TRES_FO
#define TARG_FODEC   *Targ
#define TARG1_FODEC  *Targ1
#define TARG2_FODEC  *Targ2
#define TQO_FODEC    *Tqo
#endif
#endif

#define ASSIGN_T(a,b)  a = b;
#endif
#endif


/*--------------------------------------------------------------------------*/
/*                                                               loop stuff */
#if defined(_ADOLC_VECTOR_)
#define FOR_0_LE_l_LT_p for (l=0; l<p; l++)
#define FOR_p_GT_l_GE_0 for (l=p-1; l>=0; l--)
#else
#if defined(_INT_FOR_)
#define FOR_0_LE_l_LT_p for (l=0; l<p; l++)
#define FOR_p_GT_l_GE_0 for (l=p-1; l>=0; l--)
#else
#define FOR_0_LE_l_LT_p
#define FOR_p_GT_l_GE_0
#endif
#endif

#if defined(_HIGHER_ORDER_)
#define FOR_0_LE_i_LT_k for (i=0; i<k; i++)
#define FOR_k_GT_i_GE_0 for (i=k-1; i>=0; i--)
#else
#define FOR_0_LE_i_LT_k
#define FOR_k_GT_i_GE_0
#endif

#if defined(_HOV_)
#define FOR_0_LE_l_LT_pk for (l=0; l<pk; l++)
#define INC_pk_1(T)      T += pk-1;
#define VEC_INC(T,inc)   T += inc;
#define HOV_INC(T,inc)   T += inc;
#else
#if defined(_HOV_WK_)
#define FOR_0_LE_l_LT_pk for (l=0; l<pk; l++)
#define INC_pk_1(T)      T += pk-1;
#define VEC_INC(T,inc)   T += inc;
#define HOV_INC(T,inc)   T += inc;
#else
#if defined(_FOV_)
#define FOR_0_LE_l_LT_pk for (l=0; l<p; l++)
#define INC_pk_1(T)      T += p-1;
#define VEC_INC(T,inc)   T++;
#define HOV_INC(T,inc)
#else
#if defined(_HOS_)
#define FOR_0_LE_l_LT_pk for (l=0; l<k; l++)
#define INC_pk_1(T)      T += k-1;
#define VEC_INC(T,inc)
#define HOV_INC(T,inc)
#else
#if defined(_INT_FOR_)
#define FOR_0_LE_l_LT_pk for (l=0; l<p; l++)
#define INC_pk_1(T)      T += p-1;
#define VEC_INC(T,inc)   T++;
#else
#define FOR_0_LE_l_LT_pk
#define INC_pk_1(T)
#define VEC_INC(T,inc)
#define HOV_INC(T,inc)
#endif
#endif
#endif
#endif
#endif

/*--------------------------------------------------------------------------*/
/*                                                        higher order case */
#if defined(_HIGHER_ORDER_)
#define BREAK_FOR_I break;
#else
#define BREAK_FOR_I ;
#endif

/* END Macros */

BEGIN_C_DECLS

#if defined(_ZOS_)
/****************************************************************************/
/* Zero Order Scalar version of the forward mode.                           */
/****************************************************************************/
#if defined(_MPI_)
int zos_forward_mpi(
    int mpi_id, int mpi_size,
#else
#if defined(_KEEP_)
int  zos_forward(
#else
int  zos_forward_nk(
#endif
#endif
    short  tnum,              /* tape id */
    int    depcheck,          /* consistency chk on # of deps */
    int    indcheck,          /* consistency chk on # of indeps */
#if defined(_KEEP_)
    int    keep,              /* flag for reverse sweep */
#endif
    const double *basepoint,  /* independant variable values */
    double       *valuepoint) /* dependent variable values */

#else
#if defined(_FOS_)
/****************************************************************************/
/* First Order Scalar version of the forward mode.                          */
/****************************************************************************/
#if defined(_MPI_)
int  fos_forward_mpi(
    int mpi_id, int mpi_size,
#else
#if defined(_KEEP_)
int  fos_forward(
#else
int  fos_forward_nk(
#endif
#endif
    short  tnum,        /* tape id */
    int    depcheck,    /* consistency chk on # of deps */
    int    indcheck,    /* consistency chk on # of indeps */
#if defined(_KEEP_)
    int    keep,        /* flag for reverse sweep */
#endif
    const double *basepoint,  /* independent variable values */
    double *argument,   /* Taylor coefficients (input) */
    double *valuepoint, /* Taylor coefficients (output) */
    double *taylors)    /* matrix of coefficient vectors */
/* the order of the indices in argument and taylors is [var][taylor] */

#else
#if defined(_INT_FOR_)
#if defined(_TIGHT_)
/****************************************************************************/
/* First Order Vector version of the forward mode for bit patterns, tight   */
/****************************************************************************/
#if defined(_MPI_)
int int_forward_tight_mpi(
    int mpi_id, int mpi_size,
#else
int int_forward_tight(
#endif
    short               tnum,     /* tape id                              */
    int                 depcheck, /* consistency chk on # of dependents   */
    int                 indcheck, /* consistency chk on # of independents */
    int                 p,        /* # of taylor series, bit pattern      */
    const double       *basepoint,  /* independent variable values   (in)*/
    unsigned long int **argument,  /* Taylor coeff.                 (in)*/
    double             *valuepoint, /* dependent variable values    (out)*/
    unsigned long int **taylors)   /* matrix of coefficient vectors(out)*/

/* int_forward_tight( tag, m, n, p, x[n], X[n][p], y[m], Y[m][p]),

     nBV = number of Boolean Vectors to be packed
                      (see Chapter Dependence Analysis, ADOL-C Documentation)
     bits_per_long = 8*sizeof(unsigned long int)
     p = nBV / bits_per_long + ( (nBV % bits_per_long) != 0 )

     The order of the indices in argument and taylors is [var][taylor]

     For the full Jacobian matrix set
     p = indep / bits_per_long + ((indep % bits_per_long) != 0)
     and pass a bit pattern version of the identity matrix as an argument   */


#endif
#if defined (_NTIGHT_)
/****************************************************************************/
/* First Order Vector version of the forward mode, bit pattern, safe        */
/****************************************************************************/
#if defined(_MPI_)
int int_forward_safe_mpi(
    int mpi_id, int mpi_size,
#else
int int_forward_safe(
#endif
    short             tnum,     /* tape id                              */
    int               depcheck, /* consistency chk on # of dependents   */
    int               indcheck, /* consistency chk on # of independents */
    int               p,        /* # of taylor series, bit pattern      */
    unsigned long int **argument, /* Taylor coeff.                  (in)*/
    unsigned long int **taylors)  /* matrix of coefficient vectors (out)*/

/* int_forward_safe( tag, m, n, p, X[n][p], Y[m][p]),

nBV = number of Boolean Vectors to be packed
(see Chapter Dependence Analysis, ADOL-C Documentation)
bits_per_long = 8*sizeof(unsigned long int)
p = nBV / bits_per_long + ( (nBV % bits_per_long) != 0 )

The order of the indices in argument and taylors is [var][taylor]

For the full Jacobian matrix set
p = indep / bits_per_long + ((indep % bits_per_long) != 0)
and pass a bit pattern version of the identity matrix as an argument    */
#endif
#else
#if defined(_INDOPRO_)
#if defined(_TIGHT_)
/****************************************************************************/
/* First Order Vector version of the forward mode for bit patterns, tight   */
/****************************************************************************/
#if defined(_MPI_)
int indopro_forward_tight_mpi(
    int mpi_id, int mpi_size,
#else
int indopro_forward_tight(
#endif
    short             tnum,        /* tape id                              */
    int               depcheck,    /* consistency chk on # of dependents   */
    int               indcheck,    /* consistency chk on # of independents */
    const double     *basepoint,  /* independent variable values   (in)   */
    unsigned int    **crs)        /* returned row index storage (out)     */

/* indopro_forward_tight( tag, m, n, x[n], *crs[m]),

  */


#endif
#if defined (_NTIGHT_)
/****************************************************************************/
/* First Order Vector version of the forward mode, bit pattern, safe        */
/****************************************************************************/
#if defined(_MPI_)
int indopro_forward_safe_mpi(
    int mpi_id, int mpi_size,
#else
int indopro_forward_safe(
#endif
    short             tnum,        /* tape id                              */
    int               depcheck,    /* consistency chk on # of dependents   */
    int               indcheck,    /* consistency chk on # of independents */
    const double     *basepoint,   /* independent variable values   (in)   */
    unsigned int    **crs)         /* returned row index storage (out)     */

/* indopro_forward_safe( tag, m, n, x[n], *crs[m]),

  */
#endif
#else
#if defined(_NONLIND_)
#if defined(_TIGHT_)
/****************************************************************************/
/* First Order Vector version of the forward mode for bit patterns, tight   */
/****************************************************************************/
#if defined(_MPI_)
int nonl_ind_forward_tight_mpi(
    int mpi_id, int mpi_size,
#else
int nonl_ind_forward_tight(
#endif
    short             tnum,        /* tape id                              */
    int               depcheck,    /* consistency chk on # of dependents   */
    int               indcheck,    /* consistency chk on # of independents */
    const double     *basepoint,  /* independent variable values   (in)   */
    unsigned int     **crs)        /* returned row index storage (out)     */

/* indopro_forward_tight( tag, m, n, x[n], *crs[m]),

  */

#endif
#if defined (_NTIGHT_)
/****************************************************************************/
/* First Order Vector version of the forward mode, bit pattern, safe        */
/****************************************************************************/
#if defined(_MPI_)
int nonl_ind_forward_safe_mpi(
    int mpi_id, int mpi_size,
#else
int nonl_ind_forward_safe(
#endif
    short             tnum,        /* tape id                              */
    int               depcheck,    /* consistency chk on # of dependents   */
    int               indcheck,    /* consistency chk on # of independents */
    const double      *basepoint,  /* independent variable values   (in)   */
    unsigned int    **crs)        /* returned row index storage (out)     */

/* indopro_forward_safe( tag, m, n, x[n], *crs[m]),

  */
#endif
#else
#if defined(_FOV_)
#if defined(_CHUNKED_)
/****************************************************************************/
/* First Order Vector version of the forward mode with p-offset in          */
/* **argument and **taylors                                                 */
/****************************************************************************/
int  fov_offset_forward(
    short  tnum,        /* tape id */
    int    depcheck,    /* consistency chk on # of deps */
    int    indcheck,    /* consistency chk on # of indeps */
    int    p,           /* # of taylor series */
    int    offset,      /* offset for assignments */
    double *basepoint,  /* independent variable values */
    double **argument,  /* Taylor coefficients (input) */
    double *valuepoint, /* Taylor coefficients (output) */
    double **taylors)   /* matrix of coifficient vectors */
/* the order of the indices in argument and taylors is [var][taylor] */
#else
/****************************************************************************/
/* First Order Vector version of the forward mode.                          */
/****************************************************************************/
#if defined(_MPI_)
int  fov_forward_mpi(
    int mpi_id, int mpi_size,
#else
int  fov_forward(
#endif
    short         tnum,        /* tape id */
    int           depcheck,    /* consistency chk on # of deps */
    int           indcheck,    /* consistency chk on # of indeps */
    int           p,           /* # of taylor series */
    const double *basepoint,   /* independent variable values */
    double      **argument,    /* Taylor coefficients (input) */
    double       *valuepoint,  /* Taylor coefficients (output) */
    double      **taylors)     /* matrix of coifficient vectors */
/* the order of the indices in argument and taylors is [var][taylor] */
#endif

#else
#if defined(_HOS_)
/****************************************************************************/
/* Higher Order Scalar version of the forward mode.                         */
/****************************************************************************/
#if defined(_MPI_)
int  hos_forward_mpi(
    int mpi_id, int mpi_size,
#else
#if defined(_KEEP_)
int  hos_forward(
#else
int  hos_forward_nk(
#endif
#endif
    short  tnum,        /* tape id */
    int    depcheck,    /* consistency chk on # of dependents */
    int    indcheck,    /* consistency chk on # of independents */
    int    gdegree,     /* highest derivative degree */
#if defined(_KEEP_)
    int    keep,        /* flag for reverse sweep */
#endif
    double *basepoint,  /* independent variable values */
    double **argument,  /* independant variable values */
    double *valuepoint, /* Taylor coefficients (output) */
    double **taylors)   /* matrix of coifficient vectors */


#else
/****************************************************************************/
/* Higher Order Vector version of the forward mode.                         */
/****************************************************************************/
#if defined(_MPI_)
int hov_forward_mpi(int mpi_id, int mpi_size,
#else
#if defined(_KEEP_)
int  hov_wk_forward(
#else
int  hov_forward(
#endif
#endif
    short  tnum,        /* tape id */
    int    depcheck,    /* consistency chk on # of deps */
    int    indcheck,    /* consistency chk on # of indeps */
    int    gdegree,     /* highest derivative degree */
#if defined(_KEEP_)
    int    keep,        /* flag for reverse sweep */
#endif
    int    p,           /* # of taylor series */
    double *basepoint,  /* independent variable values */
    double ***argument, /* Taylor coefficients (input) */
    double *valuepoint, /* Taylor coefficients (output) */
    double ***taylors)  /* matrix of coifficient vectors */
/* the order of the indices in argument and taylors is [var][taylor][deriv] */

#endif
#endif
#endif
#endif
#endif
#endif
#endif
{
    /****************************************************************************/
    /*                                                            ALL VARIABLES */
    unsigned char operation;   /* operation code */
    int ret_c =3;              /* return value */

    locint size = 0;
    locint res  = 0;
    locint arg  = 0;
    locint arg1 = 0;
    locint arg2 = 0;

    double coval = 0, *d = 0;

    int indexi = 0,  indexd = 0;
#if defined(_MPI_)
    short this_tnum = mpi_size*tnum + mpi_id;
#endif

    /* loop indices */
#if !defined (_ZOS_)
#if !defined (_INT_FOR_)
    int i;
#if !defined (_INDO_)
    int ii;
#endif
#endif
#endif
#if defined (_HIGHER_ORDER_)
    int j, l=0;
#endif
    int ls;
#if defined(_ADOLC_VECTOR_)
#if !defined (_HIGHER_ORDER_)
    int l=0;
#endif
#endif
#if defined (_INT_FOR_)
    int l=0;
#endif
#if defined (_INDO_)
    int l=0;
    int max_ind_dom;
#if defined(_NONLIND_)
    /* nonlinear interaction domains */
    locint** nonl_dom;
    locint*  temp;
    locint*  temp1;
#endif
#endif

    /* other necessary variables */
#if !defined (_ZOS_)
#if !defined (_INDO_)
#if !defined (_INT_FOR_)
    double r0=0.0, x, y, divs;
    int even;
#endif
#endif
#endif

#if defined(_INT_FOR_)
#ifdef _TIGHT_
    double  *dp_T0;
    double y, divs;
#endif /* _TIGHT_ */

    /* Taylor stuff */
    unsigned long int  **up_T;

    unsigned long int         *Tres, *Targ, *Targ1, *Targ2;
#ifdef _TIGHT_
    unsigned long int         *Tqo;
    unsigned long int         *Targ1OP, *Targ2OP;
#endif

#define T0res  T0temp
#else
#if defined(_INDO_)
#ifdef _TIGHT_
    double  *dp_T0;
    double  T0temp;
    double divs;
#endif /* _TIGHT_ */
#define T0res  T0temp
#define T0arg  T0temp

    /* index domains */
    locint** ind_dom;

#else
    double *dp_T0;
#if !defined(_ZOS_)
#if  defined(_FOS_)
    double  *dp_T;
# define T_TEMP Ttemp;
# else
    double *dp_Ttemp, **dpp_T;
#endif
    double         *Tres, *Targ, *Targ1, *Targ2, *Tqo;

#if defined (_HIGHER_ORDER_)
    double         *TresOP, *TresOP2, *zOP;
    double *dp_z;
#endif
   double         *TargOP, *Targ1OP, *Targ2OP;
   double         T0temp;
#endif
#define T0res  T0temp
#define T0arg  T0temp
#endif
#endif

#if defined(_HIGHER_ORDER_)
    int k = gdegree;
#endif

#if defined(_KEEP_)
    int taylbuf=0;
#endif

#if defined(_HOV_)
    int pk = k*p;
#else
#if defined(_HOV_WK_)
    int pk = k*p;
#endif
#endif

    /* extern diff. function variables */
#if defined(_EXTERN_)
#  undef (_EXTERN_)
#endif
    /* ZOS_FORWARD */
#if defined(_ZOS_)
#   define _EXTERN_ 1
#   define ADOLC_EXT_FCT_POINTER zos_forward
#   define ADOLC_EXT_FCT_COMPLETE \
    zos_forward(n, edfct->dp_x, m, edfct->dp_y)
#   define ADOLC_EXT_LOOP
#   define ADOLC_EXT_SUBSCRIPT
#endif
    /* FOS_FORWARD */
#if defined(_FOS_)
#   define _EXTERN_ 1
#   define ADOLC_EXT_FCT_POINTER fos_forward
#   define ADOLC_EXT_FCT_COMPLETE \
    fos_forward(n, edfct->dp_x, edfct->dp_X, m, edfct->dp_y, edfct->dp_Y)
#   define ADOLC_EXT_POINTER_X edfct->dp_X
#   define ADOLC_EXT_POINTER_Y edfct->dp_Y
#   define ADOLC_EXT_LOOP
#   define ADOLC_EXT_SUBSCRIPT
#endif
    /* FOV_FORWARD */
#if defined(_FOV_)
#   define _EXTERN_ 1
#   define ADOLC_EXT_FCT_POINTER fov_forward
#   define ADOLC_EXT_FCT_COMPLETE \
    fov_forward(n, edfct->dp_x, edfct->dpp_X, m, edfct->dp_y, edfct->dpp_Y)
#   define ADOLC_EXT_POINTER_X edfct->dpp_X
#   define ADOLC_EXT_POINTER_Y edfct->dpp_Y
#   define ADOLC_EXT_LOOP for (loop2 = 0; loop2 < p; ++loop2)
#   define ADOLC_EXT_SUBSCRIPT [loop2]
#endif

#if defined(_EXTERN_)
    locint n, m;
    ext_diff_fct *edfct;
    int loop;
#   if defined(_FOV_)
        int loop2;
#   endif
    int ext_retc;
#endif

    ADOLC_OPENMP_THREAD_NUMBER;

#if defined(ADOLC_DEBUG)
    /****************************************************************************/
    /*                                                           DEBUG MESSAGES */
    fprintf(DIAG_OUT,"Call of %s(..) with tag: %d, n: %d, m %d,\n",
            GENERATED_FILENAME,
#if defined(_MPI_)
            this_tnum,
#else
            tnum,
#endif
            indcheck, depcheck);
#if defined(_KEEP_)
    fprintf(DIAG_OUT,"                    keep: %d\n", keep);
#endif
#if defined(_HIGHER_ORDER_)
    fprintf(DIAG_OUT,"                    degree: %d\n",gdegree);
#endif
#if defined(_ADOLC_VECTOR_)
    fprintf(DIAG_OUT,"                    p: %d\n\n",p);
#endif

#endif

    /****************************************************************************/
    /*                                                                    INITs */

   /* Set up stuff for the tape */
    ADOLC_OPENMP_GET_THREAD_NUMBER;

    /* Initialize the Forward Sweep */
#if defined(_MPI_)
    init_for_sweep(this_tnum);
#else
    init_for_sweep(tnum);
#endif
      if ( (depcheck != ADOLC_CURRENT_TAPE_INFOS.stats[NUM_DEPENDENTS]) ||
            (indcheck != ADOLC_CURRENT_TAPE_INFOS.stats[NUM_INDEPENDENTS]) ) {
        fprintf(DIAG_OUT,"ADOL-C error: forward sweep on tape %d  aborted!\n"
                "Number of dependent(%u) and/or independent(%u) variables passed"
                " to forward is\ninconsistent with number "
                "recorded on tape (%d, %d) \n",
# if defined(_MPI_)
this_tnum,
#else
tnum,
#endif
                depcheck, indcheck,
                ADOLC_CURRENT_TAPE_INFOS.stats[NUM_DEPENDENTS],
                ADOLC_CURRENT_TAPE_INFOS.stats[NUM_INDEPENDENTS]);
        exit (-1);
    }
#if defined(_MPI_)
     double *trade, *rec_buf, *mpi_tmp;
     MPI_Status status_MPI;
     int mpi_i,mpi_ii, s_r_c=1;
     locint *loc_send, *loc_recv;
     int myid,root, count, count2, target,tag;
#if defined(_NONLIND_)
     locint *tmp_element;
#endif
#if defined(_INDO_)
     int *trade_loc, *rec_buf_loc;
     int *counts, *tmp_counts;
     int anz;
#endif
#if  defined(_INT_FOR_)
     locint *trade_loc, *rec_buf_loc;
#endif
#endif


    /****************************************************************************/
    /*                                                        MEMORY ALLOCATION */
    /* olvo 980626 has to be revised for common blocks */

    /*--------------------------------------------------------------------------*/
#if !defined(_NTIGHT_)
    dp_T0 = myalloc1(ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES]);
    ADOLC_CURRENT_TAPE_INFOS.dp_T0 = dp_T0;
#endif /* !_NTIGHT_ */
#if defined(_ZOS_)                                                   /* ZOS */

#if defined(_KEEP_)
    if (keep>1) {
        fprintf(DIAG_OUT,"\n ADOL-C error: zero order scalar forward cannot save"
                " more\nthan zero order taylor coefficients!\n");
        exit (-1);
    }
#endif
#if defined(_KEEP_)
    if (keep) {
      taylbuf = ADOLC_CURRENT_TAPE_INFOS.stats[TAY_BUFFER_SIZE];

        taylor_begin(taylbuf,&dp_T0,keep-1);
    }
#endif

    /*--------------------------------------------------------------------------*/
#else                                                                /* FOS */
#if defined(_FOS_)
#if defined(_KEEP_)
    if (keep>2) {
        fprintf(DIAG_OUT,"\n ADOL-C error: first order scalar forward cannot save"
                " more  \nthan first order taylor coefficients!\n");
        exit (-1);
    }
#endif
    dp_T = myalloc1(ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES]);
# define TAYLOR_BUFFER dp_T
#if defined(_KEEP_)
    if (keep) {
        taylbuf = ADOLC_CURRENT_TAPE_INFOS.stats[TAY_BUFFER_SIZE];
        taylor_begin(taylbuf,&dp_T,keep-1);
    }
#endif

    /*--------------------------------------------------------------------------*/
#else                                                                /* INF_FOR */
#if defined(_INT_FOR_)
        up_T     = myalloc2_ulong(ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES],p);
#define TAYLOR_BUFFER up_T

    /*--------------------------------------------------------------------------*/
#else                                                                /* INDOPRO */
#if defined(_INDO_)
    ind_dom = (locint**)  malloc(sizeof(locint*) * ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES]);

    for(i=0;i<ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES];i++)
    {
        ind_dom[i] = (locint*)  malloc(sizeof(locint)*(NUMNNZ+2));
        ind_dom[i][0] = 0;
        ind_dom[i][1] = NUMNNZ;
    }

    max_ind_dom = ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES];
#if defined(_NONLIND_)
#if defined(_MPI_)
    int s_r_indep =indcheck;
    if (mpi_initialized) {
       MPI_Comm_rank(MPI_COMM_WORLD, &myid);
       MPI_Bcast(&s_r_indep,1,MPI_INT,0,MPI_COMM_WORLD);

       nonl_dom = (locint**) malloc(sizeof(locint*) * s_r_indep);
       for(i=0;i<s_r_indep;i++){
           nonl_dom[i] = (locint*) malloc(sizeof(locint)*(NUMNNZ+2));
           nonl_dom[i][0] = 0;
           nonl_dom[i][1] = NUMNNZ;
       }
    }
    else {
       nonl_dom = (locint**) malloc(sizeof(locint*) * s_r_indep);
       for(i=0;i<indcheck;i++){
          nonl_dom[i] = (locint*) malloc(sizeof(locint)*(NUMNNZ+2));
          nonl_dom[i][0]=0;
          nonl_dom[i][1]=NUMNNZ;
       }
    }
#else
    nonl_dom = (locint**) malloc(sizeof(locint*) * indcheck);
    for(i=0;i<indcheck;i++){
          nonl_dom[i] = (locint*) malloc(sizeof(locint)*(NUMNNZ+2));
          nonl_dom[i][0]=0;
          nonl_dom[i][1]=NUMNNZ;
       }
#endif
#endif

    /*--------------------------------------------------------------------------*/
#else                                                                /* FOV */
#if defined(_FOV_)
    dpp_T = myalloc2(ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES],p);
# define TAYLOR_BUFFER dpp_T
    dp_Ttemp = myalloc1(p);
# define T_TEMP dp_Ttemp;

    /*--------------------------------------------------------------------------*/
#else                                                                /* HOS */
#if defined(_HOS_)
    dpp_T = myalloc2(ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES],k);
# define TAYLOR_BUFFER dpp_T
    dp_z  = myalloc1(k);
    dp_Ttemp = myalloc1(k);
# define T_TEMP dp_Ttemp;
#if defined(_KEEP_)
    if (keep) {
        taylbuf = ADOLC_CURRENT_TAPE_INFOS.stats[TAY_BUFFER_SIZE];
        taylor_begin(taylbuf,dpp_T,keep-1);
    }
#endif

    /*--------------------------------------------------------------------------*/
#else                                                     /* HOV and HOV_WK */
    dpp_T = myalloc2(ADOLC_CURRENT_TAPE_INFOS.stats[NUM_MAX_LIVES],p*k);
# define TAYLOR_BUFFER dpp_T
    dp_z  = myalloc1(k);
    dp_Ttemp = myalloc1(p*k);
# define T_TEMP dp_Ttemp;
#if defined(_KEEP_)
    if (keep) {
        taylbuf = ADOLC_CURRENT_TAPE_INFOS.stats[TAY_BUFFER_SIZE];
        taylor_begin(taylbuf,dpp_T,keep-1);
    }
#endif
#endif
#endif
#endif
#endif
#endif
#endif
    /****************************************************************************/
    /*                                                            FORWARD SWEEP */

#if defined(ADOLC_DEBUG)
/* #include <string.h> */
    int v = 0;
    unsigned int countPerOperation[256], taylorPerOperation[256];
    memset(countPerOperation, 0, 1024);
    memset(taylorPerOperation, 0, 1024);
#   define UPDATE_TAYLORWRITTEN(X) taylorPerOperation[operation] += X;
#else
#   define UPDATE_TAYLORWRITTEN(X)
#endif /* ADOLC_DEBUG */

    operation=get_op_f();
#if defined(ADOLC_DEBUG)
    ++countPerOperation[operation];
#endif /* ADOLC_DEBUG */
    while (operation !=end_of_tape) {

      switch (operation) {


                /****************************************************************************/
                /*                                                                  MARKERS */

                /*--------------------------------------------------------------------------*/
            case end_of_op:                                          /* end_of_op */
                get_op_block_f();
                operation=get_op_f();
                /* Skip next operation, it's another end_of_op */
                break;

                /*--------------------------------------------------------------------------*/
            case end_of_int:                                        /* end_of_int */
                get_loc_block_f();
                break;

                /*--------------------------------------------------------------------------*/
            case end_of_val:                                        /* end_of_val */
               get_val_block_f();
                break;
                /*--------------------------------------------------------------------------*/
            case start_of_tape:                                  /* start_of_tape */
            case end_of_tape:                                      /* end_of_tape */
                break;


                /****************************************************************************/
                /*                                                               COMPARISON */

                /*--------------------------------------------------------------------------*/
            case eq_zero:                                              /* eq_zero */
                arg = get_locint_f();

#if !defined(_NTIGHT_)
                if (dp_T0[arg] != 0) {
                    if (ADOLC_GLOBAL_TAPE_VARS.branchSwitchWarning)
                        fprintf(DIAG_OUT,
                                "ADOL-C Warning: Branch switch detected in comparison "
                                "(operator eq_zero).\n"
                                "Forward sweep aborted! Retaping recommended!\n");
                    ret_c = -1;
                    operation = end_of_tape;
                    continue;
                }
                ret_c = 0;
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case neq_zero:                                            /* neq_zero */
                arg = get_locint_f();

#if !defined(_NTIGHT_)
                if (dp_T0[arg] == 0) {
                    if (ADOLC_GLOBAL_TAPE_VARS.branchSwitchWarning)
                        fprintf(DIAG_OUT,
                                "ADOL-C Warning: Branch switch detected in comparison "
                                "(operator neq_zero).\n"
                                "Forward sweep aborted! Retaping recommended!\n");
                    ret_c = -1;
                    operation = end_of_tape;
                    continue;
                }
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case le_zero:                                              /* le_zero */
                arg = get_locint_f();

#if !defined(_NTIGHT_)
                if (dp_T0[arg] > 0) {
                    if (ADOLC_GLOBAL_TAPE_VARS.branchSwitchWarning)
                        fprintf(DIAG_OUT,
                                "ADOL-C Warning: Branch switch detected in comparison "
                                "(operator le_zero).\n"
                                "Forward sweep aborted! Retaping recommended!\n");
                    ret_c = -1;
                    operation = end_of_tape;
                    continue;
                }
                if (dp_T0[arg] == 0)
                    ret_c = 0;
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case gt_zero:                                              /* gt_zero */
                arg = get_locint_f();

#if !defined(_NTIGHT_)
                if (dp_T0[arg] <= 0) {
                    if (ADOLC_GLOBAL_TAPE_VARS.branchSwitchWarning)
                        fprintf(DIAG_OUT,
                                "ADOL-C Warning: Branch switch detected in comparison "
                                "(operator gt_zero).\n"
                                "Forward sweep aborted! Retaping recommended!\n");
                    ret_c = -1;
                    operation = end_of_tape;
                    continue;
                }
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case ge_zero:                                              /* ge_zero */
                arg = get_locint_f();

#if !defined(_NTIGHT_)
                if (dp_T0[arg] < 0) {
                    if (ADOLC_GLOBAL_TAPE_VARS.branchSwitchWarning)
                        fprintf(DIAG_OUT,
                                "ADOL-C Warning: Branch switch detected in comparison "
                                "(operator ge_zero).\n"
                                "Forward sweep aborted! Retaping recommended!\n");
                    ret_c = -1;
                    operation = end_of_tape;
                    continue;
                }
                if (dp_T0[arg] == 0)
                    ret_c = 0;
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case lt_zero:                                              /* lt_zero */
                arg = get_locint_f();

#if !defined(_NTIGHT_)
                if (dp_T0[arg] >= 0) {
                    if (ADOLC_GLOBAL_TAPE_VARS.branchSwitchWarning)
                        fprintf(DIAG_OUT,
                                "ADOL-C Warning: Branch switch detected in comparison "
                                "(operator lt_zero).\n"
                                "Forward sweep aborted! Retaping recommended!\n");
                    ret_c = -1;
                    operation = end_of_tape;
                    continue;
                }
#endif /* !_NTIGHT_ */
                break;


                /****************************************************************************/
                /*                                                              ASSIGNMENTS */

                /*--------------------------------------------------------------------------*/
            case assign_a:           /* assign an adouble variable an    assign_a */
                /* adouble value. (=) */
                arg = get_locint_f();
                res = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)


#if !defined(_NTIGHT_)
                dp_T0[res] = dp_T0[arg];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Targ,TAYLOR_BUFFER[arg])
                ASSIGN_T(Tres,TAYLOR_BUFFER[res])

                FOR_0_LE_l_LT_pk
                TRES_INC = TARG_INC;
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case assign_d:            /* assign an adouble variable a    assign_d */
                /* double value. (=) */
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = coval;
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
		ind_dom[res][0]=0;
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

                FOR_0_LE_l_LT_pk
                TRES_INC = 0;
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case assign_d_zero:  /* assign an adouble variable a    assign_d_zero */
                /* double value. (0) (=) */
                res   = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = 0.0;
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
		ind_dom[res][0]=0;
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

                FOR_0_LE_l_LT_pk
                TRES_INC = 0;
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case assign_d_one:    /* assign an adouble variable a    assign_d_one */
                /* double value. (1) (=) */
                res   = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = 1.0;
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
		ind_dom[res][0]=0;
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

                FOR_0_LE_l_LT_pk
                TRES_INC = 0;

#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case assign_ind:       /* assign an adouble variable an    assign_ind */
                /* independent double value (<<=) */
                res = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = basepoint[indexi];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
		ind_dom[res][0] = 1;
		ind_dom[res][2] = indexi;
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_INC = ARGUMENT(indexi,l,i);
#else
                FOR_0_LE_l_LT_p
                FOR_0_LE_i_LT_k
                TRES_INC = ARGUMENT(indexi,l,i);
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                ++indexi;
                break;

                /*--------------------------------------------------------------------------*/
            case assign_dep:           /* assign a float variable a    assign_dep */
                /* dependent adouble value. (>>=) */
                res = get_locint_f();

#if !defined(_INDO_)
#if !defined(_NTIGHT_)
                if ( valuepoint != NULL )
		  valuepoint[indexd] = dp_T0[res];
#endif /* !_NTIGHT_ */
#endif

#if defined(_INDO_)
#if defined(_INDOPRO_)
		if (ind_dom[res][0] != 0) {
		  crs[indexd] = (unsigned int*) malloc(sizeof(unsigned int) * (ind_dom[res][0]+1));
		  crs[indexd][0] = ind_dom[res][0];
		  for(l=1;l<=crs[indexd][0];l++) {
		    crs[indexd][l] = ind_dom[res][l+1];
		  }
		}
		else {
		  crs[indexd] = (unsigned int*) malloc(sizeof(unsigned int));
		  crs[indexd][0] =0;
		}
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

#ifdef _INT_FOR_
                if (taylors != 0 )  /* ??? question: why here? */
                    FOR_0_LE_l_LT_p
                    TAYLORS(indexd,l,i) = TRES_INC;
#else
                if (taylors != 0 )  /* ??? question: why here? */
                    FOR_0_LE_l_LT_p
                    FOR_0_LE_i_LT_k
                    TAYLORS(indexd,l,i) = TRES_INC;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                indexd++;
                break;


                /****************************************************************************/
                /*                                                   OPERATION + ASSIGNMENT */

                /*--------------------------------------------------------------------------*/
            case eq_plus_d:            /* Add a floating point to an    eq_plus_d */
                /* adouble. (+=) */
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] += coval;
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case eq_plus_a:             /* Add an adouble to another    eq_plus_a */
                /* adouble. (+=) */
                arg = get_locint_f();
                res = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] += dp_T0[arg];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                merge_2_index_domains(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_pk
                TRES_INC |= TARG_INC;
#else
                FOR_0_LE_l_LT_pk
                TRES_INC += TARG_INC;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case eq_min_d:       /* Subtract a floating point from an    eq_min_d */
                /* adouble. (-=) */
                res = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] -= coval;
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case eq_min_a:        /* Subtract an adouble from another    eq_min_a */
                /* adouble. (-=) */
                arg = get_locint_f();
                res = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] -= dp_T0[arg];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                merge_2_index_domains(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_pk
                TRES_INC |= TARG_INC;
#else
                FOR_0_LE_l_LT_pk
                TRES_INC -= TARG_INC;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case eq_mult_d:              /* Multiply an adouble by a    eq_mult_d */
                /* flaoting point. (*=) */
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] *= coval;
#endif /* !_NTIGHT_ */

#if !defined(_INDO_)
#if !defined(_ZOS_) /* BREAK_ZOS */
#if !defined( _INT_FOR_)

                FOR_0_LE_l_LT_pk
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

                FOR_0_LE_l_LT_pk
                TRES_INC *= coval;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case eq_mult_a:       /* Multiply one adouble by another    eq_mult_a */
                /* (*=) */
                arg = get_locint_f();
                res = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if defined(_INDO_)
                merge_2_index_domains(res, arg, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_binary(res, arg, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

                INC_pk_1(Tres)
                INC_pk_1(Targ)

#ifdef _INT_FOR_
                FOR_p_GT_l_GE_0
                TRES_FODEC |= TARG_DEC;
#else
                FOR_p_GT_l_GE_0
                FOR_k_GT_i_GE_0
                { TRES_FODEC = dp_T0[res]*TARG_DEC +
                               TRES*dp_T0[arg];
                  DEC_TRES_FO
#ifdef _HIGHER_ORDER_
                  TresOP = Tres-i;
                  TargOP = Targ;

                  for (j=0;j<i;j++)
                  *Tres += (*TresOP++) * (*TargOP--);
                  Tres--;
#endif /* _HIGHER_ORDER_ */
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
#if !defined(_NTIGHT_)
               dp_T0[res] *= dp_T0[arg];
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case incr_a:                        /* Increment an adouble    incr_a */
                res   = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res]++;
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case decr_a:                        /* Increment an adouble    decr_a */
                res   = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res]--;
#endif /* !_NTIGHT_ */
                break;


                /****************************************************************************/
                /*                                                        BINARY OPERATIONS */

                /*--------------------------------------------------------------------------*/
            case plus_a_a:                 /* : Add two adoubles. (+)    plus a_a */
                arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = dp_T0[arg1] +
                                               dp_T0[arg2];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                combine_2_index_domains(res, arg1, arg2, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_pk
                TRES_INC = TARG1_INC | TARG2_INC;
#else
                FOR_0_LE_l_LT_pk
                TRES_INC = TARG1_INC + TARG2_INC;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case plus_d_a:             /* Add an adouble and a double    plus_d_a */
                /* (+) */
                arg   = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = dp_T0[arg] + coval;
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

                FOR_0_LE_l_LT_pk
                TRES_INC = TARG_INC;
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case min_a_a:              /* Subtraction of two adoubles     min_a_a */
                /* (-) */
                arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = dp_T0[arg1] -
                                               dp_T0[arg2];
#endif /* !_NTIGHT_ */


#if defined(_INDO_)
                combine_2_index_domains(res, arg1, arg2, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_pk
                TRES_INC = TARG1_INC | TARG2_INC;
#else
                 FOR_0_LE_l_LT_pk
                TRES_INC = TARG1_INC - TARG2_INC;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case min_d_a:                /* Subtract an adouble from a    min_d_a */
                /* double (-) */
                arg =get_locint_f();
                res = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = coval - dp_T0[arg];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_pk
                TRES_INC = TARG_INC;
#else
                FOR_0_LE_l_LT_pk
                TRES_INC = -TARG_INC;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case mult_a_a:               /* Multiply two adoubles (*)    mult_a_a */
                arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if defined(_INDO_)
                combine_2_index_domains(res, arg1, arg2, ind_dom);
#if defined(_NONLIND_)
		extend_nonlinearity_domain_binary(arg1, arg2, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG2_INC | TARG1_INC;
#else
                /* olvo 980915 now in reverse order to allow x = x*x etc. */
                INC_pk_1(Tres)
                INC_pk_1(Targ1)
                INC_pk_1(Targ2)

                FOR_p_GT_l_GE_0
                FOR_k_GT_i_GE_0
                { TRES_FODEC = dp_T0[arg1]*TARG2_DEC +
                               TARG1_DEC*dp_T0[arg2];
                  DEC_TRES_FO
#if defined(_HIGHER_ORDER_)
                  Targ1OP = Targ1-i+1;
                  Targ2OP = Targ2;

                  for (j=0;j<i;j++) {
                  *Tres += (*Targ1OP++) * (*Targ2OP--);
                  }
                  Tres--;
#endif /* _HIGHER_ORDER_ */
            }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
#if !defined(_NTIGHT_)
                dp_T0[res] = dp_T0[arg1] *
                                               dp_T0[arg2];
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
                /* olvo 991122: new op_code with recomputation */
            case eq_plus_prod:   /* increment a product of           eq_plus_prod */
                /* two adoubles (*) */
                arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

#if defined(_INDO_)
                merge_3_index_domains(res, arg1, arg2, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_binary(arg1, arg2, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC |= TARG2_INC | TARG1_INC;
#else
                /* olvo 980915 now in reverse order to allow x = x*x etc. */
                INC_pk_1(Tres)
                INC_pk_1(Targ1)
                INC_pk_1(Targ2)

                FOR_p_GT_l_GE_0
                FOR_k_GT_i_GE_0
                { TRES_FODEC += dp_T0[arg1]*TARG2_DEC +
                                TARG1_DEC*dp_T0[arg2];
                  DEC_TRES_FO
#if defined(_HIGHER_ORDER_)
                  Targ1OP = Targ1-i+1;
                  Targ2OP = Targ2;

                  for (j=0;j<i;j++)
                  *Tres += (*Targ1OP++) * (*Targ2OP--);
                  Tres--;
#endif /* _HIGHER_ORDER_ */
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
#if !defined(_NTIGHT_)
                dp_T0[res] += dp_T0[arg1] *
                                                    dp_T0[arg2];
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
                /* olvo 991122: new op_code with recomputation */
            case eq_min_prod:    /* decrement a product of            eq_min_prod */
                /* two adoubles (*) */
                arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

#if defined(_INDO_)
                merge_3_index_domains(res, arg1, arg2, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_binary(arg1, arg2, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC |= TARG2_INC | TARG1_INC;
#else
                /* olvo 980915 now in reverse order to allow x = x*x etc. */
                INC_pk_1(Tres)
                INC_pk_1(Targ1)
                INC_pk_1(Targ2)

                FOR_p_GT_l_GE_0
                FOR_k_GT_i_GE_0
                { TRES_FODEC -= dp_T0[arg1]*TARG2_DEC +
                                TARG1_DEC*dp_T0[arg2];
                  DEC_TRES_FO
#if defined(_HIGHER_ORDER_)
                  Targ1OP = Targ1-i+1;
                  Targ2OP = Targ2;

                  for (j=0;j<i;j++)
                  *Tres -= (*Targ1OP++) * (*Targ2OP--);
                  Tres--;
#endif /* _HIGHER_ORDER_ */
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */

#if !defined(_NTIGHT_)
                dp_T0[res] -= dp_T0[arg1] *
                                                    dp_T0[arg2];
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case mult_d_a:         /* Multiply an adouble by a double    mult_d_a */
                /* (*) */
                arg   = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = dp_T0[arg] * coval;
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_pk
                TRES_INC = TARG_INC;
#else
                FOR_0_LE_l_LT_pk
                TRES_INC = TARG_INC * coval;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case div_a_a:           /* Divide an adouble by an adouble    div_a_a */
                /* (/) */
                arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
#if !defined(_ZOS_) /* BREAK_ZOS */
                divs = 1.0 / dp_T0[arg2];
#endif /* ALL_TOGETHER_AGAIN */

                dp_T0[res] = dp_T0[arg1] /
                                               dp_T0[arg2];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                combine_2_index_domains(res, arg1, arg2, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_binary(arg1, arg2, ind_dom, nonl_dom);
                extend_nonlinearity_domain_unary(arg2, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_INC | TARG2_FOINC;
#else
                FOR_0_LE_l_LT_p
                FOR_0_LE_i_LT_k
                { /* olvo 980922 changed order to allow x = y/x */
#if defined(_HIGHER_ORDER_)
                    zOP      = dp_z+i;
                    (*zOP--) = -(*Targ2) * divs;
#endif /* _HIGHER_ORDER_ */

                    TRES_FOINC = TARG1_INC * divs + dp_T0[res] *
                                 (-TARG2_INC * divs);

#if defined(_HIGHER_ORDER_)
                    TresOP = Tres-i;

                    for (j=0;j<i;j++)
                    *Tres += (*TresOP++) * (*zOP--);
                    Tres++;
#endif /* _HIGHER_ORDER_ */
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

            /*--------------------------------------------------------------------------*/
        case div_d_a:             /* Division double - adouble (/)    div_d_a */
            arg   = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

                /* olvo 980922 necessary for reverse */
                if (arg == res) {
                    IF_KEEP_WRITE_TAYLOR(arg,keep,k,p)
                }

#if !defined(_NTIGHT_)
#if !defined(_ZOS_) /* BREAK_ZOS */
                divs = 1.0 / dp_T0[arg];
#endif /* ALL_TOGETHER_AGAIN */

                dp_T0[res] = coval / dp_T0[arg];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG_FOINC;
#else
                FOR_0_LE_l_LT_p
                FOR_0_LE_i_LT_k
                { /* olvo 980922 changed order to allow x = d/x */
#if defined(_HIGHER_ORDER_)
                    zOP      = dp_z+i;
                    (*zOP--) = -(*Targ) * divs;
#endif /* _HIGHER_ORDER_ */

                    TRES_FOINC = dp_T0[res] * (-TARG_INC * divs);

#if defined(_HIGHER_ORDER_)
                    TresOP = Tres-i;

                    for (j=0;j<i;j++)
                    *Tres += (*TresOP++) * (*zOP--);
                    Tres++;
#endif /* _HIGHER_ORDER_ */
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;


            /****************************************************************************/
            /*                                                         SIGN  OPERATIONS */

            /*--------------------------------------------------------------------------*/
        case pos_sign_a:                                        /* pos_sign_a */
            arg   = get_locint_f();
                res   = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = dp_T0[arg];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

                FOR_0_LE_l_LT_pk
                TRES_INC = TARG_INC;
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case neg_sign_a:                                        /* neg_sign_a */
                arg   = get_locint_f();
                res   = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = -dp_T0[arg];
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_pk
                TRES_INC = TARG_INC;
#else
                FOR_0_LE_l_LT_pk
                TRES_INC = -TARG_INC;
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;


                /****************************************************************************/
                /*                                                         UNARY OPERATIONS */

                /*--------------------------------------------------------------------------*/
            case exp_op:                          /* exponent operation    exp_op */
                arg = get_locint_f();
                res = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = exp(dp_T0[arg]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG_FOINC;
#else
                FOR_0_LE_l_LT_p
                FOR_0_LE_i_LT_k
                { /* olvo 980915 changed order to allow x = exp(x) */
#if defined(_HIGHER_ORDER_)
                    zOP      = dp_z+i;
                    (*zOP--) = (i+1) * (*Targ);
#endif /* _HIGHER_ORDER_ */

                    TRES_FOINC = dp_T0[res] * TARG_INC;

#if defined(_HIGHER_ORDER_)
                    TresOP = Tres-i;

                    *Tres *= (i+1);
                    for (j=0;j<i;j++)
                    *Tres += (*TresOP++) * (*zOP--);
                    *Tres++ /= (i+1); /* important only for i>0 */
#endif /* _HIGHER_ORDER_ */
                }

#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

            /*--------------------------------------------------------------------------*/
        case sin_op:                              /* sine operation    sin_op */
            arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(arg2,keep,k,p) /* olvo 980710 covalue */
                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                /* Note: always arg2 != arg1 */
                dp_T0[arg2] = cos(dp_T0[arg1]);
                dp_T0[res]  = sin(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg1, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                { /* olvo 980923 changed order to allow x = sin(x) */
                    TARG2_FOINC =  TARG1;
                    TRES_FOINC  =  TARG1_FOINC;
            }
#else
                FOR_0_LE_l_LT_p
                FOR_0_LE_i_LT_k
                { /* olvo 980921 changed order to allow x = sin(x) */
#if defined(_HIGHER_ORDER_)
                    zOP      = dp_z+i;
                    (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                    /* Note: always arg2 != arg1 */
                    TARG2_FOINC = -dp_T0[res]  * TARG1;
                    TRES_FOINC  =  dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                    TresOP  = Tres-i;
                    Targ2OP = Targ2-i;

                    *Tres  *= (i+1);
                    *Targ2 *= (i+1);
                    for (j=0;j<i;j++) {
                    *Tres  += (*Targ2OP++) * (*zOP);
                        *Targ2 -= (*TresOP++)  * (*zOP--);
                    }
                    *Targ2++ /= (i+1);
                    *Tres++  /= (i+1);
#endif /* _HIGHER_ORDER_ */
            }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case cos_op:                            /* cosine operation    cos_op */
                arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(arg2,keep,k,p) /* olvo 980710 covalue */
                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                /* Note: always arg2 != arg1 */
                dp_T0[arg2] = sin(dp_T0[arg1]);
                dp_T0[res]  = cos(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg1, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                { /* olvo 980923 changed order to allow x = cos(x) */
                    TARG2_FOINC = TARG1;
                    TRES_FOINC  = TARG1_FOINC;
            }
#else
                FOR_0_LE_l_LT_p
                FOR_0_LE_i_LT_k
                { /* olvo 980921 changed order to allow x = cos(x) */
#if defined(_HIGHER_ORDER_)
                    zOP      = dp_z+i;
                    (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                    /* Note: always arg2 != arg1 */
                    TARG2_FOINC =  dp_T0[res]  * TARG1;
                    TRES_FOINC  = -dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                    TresOP  = Tres-i;
                    Targ2OP = Targ2-i;

                    *Tres  *= (i+1);
                    *Targ2 *= (i+1);
                    for (j=0;j<i;j++) {
                    *Tres  -= (*Targ2OP++) * (*zOP);
                        *Targ2 += (*TresOP++)  * (*zOP--);
                    }
                    *Targ2++ /= (i+1);
                    *Tres++  /= (i+1);
#endif /* _HIGHER_ORDER_ */
            }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case atan_op:                                              /* atan_op */
                arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res]=atan(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg1, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_FOINC;
#else
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

                FOR_0_LE_l_LT_p
                { FOR_0_LE_i_LT_k
                  { /* olvo 980921 changed order to allow x = atan(x) */
#if defined(_HIGHER_ORDER_)
                      zOP      = dp_z+i;
                      (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                      TRES_FOINC = dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                      Targ2OP = Targ2;

                      *Tres *= (i+1);
                      for (j=0;j<i;j++)
                      *Tres  += (*Targ2OP++) * (*zOP--);
                      *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                  }
                  HOV_INC(Targ2, k)
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

            /*--------------------------------------------------------------------------*/
        case asin_op:                                              /* asin_op */
            arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = asin(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg1, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_FOINC;
#else
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

                if (dp_T0[arg1] == 1.0)
                    FOR_0_LE_l_LT_p
                    { FOR_0_LE_i_LT_k
                      if (TARG1 > 0.0) {
                      r0 = make_nan();
                          VEC_INC(Targ1, k-i)
                          BREAK_FOR_I
                      } else
                          if (TARG1 < 0.0) {
                          r0 = make_inf();
                              VEC_INC(Targ1, k-i)
                              BREAK_FOR_I
                          } else {
                              r0 = 0.0;
                              Targ1++;
                          }
                  TRES = r0;
                  VEC_INC(Tres, k)
            } else
                    if (dp_T0[arg1] == -1.0)
                        FOR_0_LE_l_LT_p
                        { FOR_0_LE_i_LT_k
                          if (TARG1 > 0.0) {
                          r0 = make_inf();
                              VEC_INC(Targ1, k-i)
                              BREAK_FOR_I
                          } else
                              if (TARG1 < 0.0) {
                              r0 = make_nan();
                                  VEC_INC(Targ1, k-i)
                                  BREAK_FOR_I
                              } else {
                                  r0 = 0.0;
                                  Targ1++;
                              }
                  TRES = r0;
                  VEC_INC(Tres, k)
                } else
                        FOR_0_LE_l_LT_p {
                            FOR_0_LE_i_LT_k
                            { /* olvo 980921 changed order to allow x = asin(x) */
#if defined(_HIGHER_ORDER_)
                                zOP      = dp_z+i;
                                (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                                TRES_FOINC = dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                                Targ2OP = Targ2;

                                *Tres *= (i+1);
                                for (j=0;j<i;j++)
                                *Tres += (*Targ2OP++) * (*zOP--);
                                *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                            }
                            HOV_INC(Targ2, k)
                        }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                        break;

            /*--------------------------------------------------------------------------*/
        case acos_op:                                              /* acos_op */
            arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = acos(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg1, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_FOINC;
#else
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

                if (dp_T0[arg1] == 1.0)
                    FOR_0_LE_l_LT_p
                    { FOR_0_LE_i_LT_k
                      if (TARG1 > 0.0) {
                      r0 = make_nan();
                          VEC_INC(Targ1, k-i)
                          BREAK_FOR_I
                      } else
                          if (TARG1 < 0.0) {
                          r0 = -make_inf();
                              VEC_INC(Targ1, k-i)
                              BREAK_FOR_I
                          } else {
                              r0 = 0.0;
                              Targ1++;
                          }
                  TRES = r0;
                  VEC_INC(Tres, k)
            } else
                    if (dp_T0[arg1] == -1.0)
                        FOR_0_LE_l_LT_p
                        { FOR_0_LE_i_LT_k
                          if (TARG1 > 0.0) {
                          r0 = -make_inf();
                              VEC_INC(Targ1, k-i)
                              BREAK_FOR_I
                          } else
                              if (TARG1 < 0.0) {
                              r0 = make_nan();
                                  VEC_INC(Targ1, k-i)
                                  BREAK_FOR_I
                              } else {
                                  r0 = 0.0;
                                  Targ1++;
                              }
                  TRES = r0;
                  VEC_INC(Tres, k)
                } else
                        FOR_0_LE_l_LT_p {
                            FOR_0_LE_i_LT_k
                            { /* olvo 980921 changed order to allow x = acos(x) */
#if defined(_HIGHER_ORDER_)
                                zOP      = dp_z+i;
                                (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                                TRES_FOINC = dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                                Targ2OP = Targ2;

                                *Tres *= (i+1);
                                for (j=0;j<i;j++)
                                *Tres += (*Targ2OP++) * (*zOP--);
                                *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                            }
                            HOV_INC(Targ2, k)
                        }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                        break;

#ifdef ATRIG_ERF

            /*--------------------------------------------------------------------------*/
        case asinh_op:                                            /* asinh_op */
            arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = asinh(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg1, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_FOINC;
#else
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

                FOR_0_LE_l_LT_p
                { FOR_0_LE_i_LT_k
                  { /* olvo 980921 changed order to allow x = asinh(x) */
#if defined(_HIGHER_ORDER_)
                      zOP      = dp_z+i;
                      (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                      TRES_FOINC = dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                      Targ2OP = Targ2;

                      *Tres *= (i+1);
                      for (j=0;j<i;j++)
                      *Tres += (*Targ2OP++) * (*zOP--);
                      *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                  }
                  HOV_INC(Targ2, k)
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

            /*--------------------------------------------------------------------------*/
        case acosh_op:                                           /* acosh_op */
            arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = acosh(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg1, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_FOINC;
#else
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

                if (dp_T0[arg1] == 1.0)
                    FOR_0_LE_l_LT_p
                    { FOR_0_LE_i_LT_k
                      if (TARG1 > 0.0) {
                      r0 = make_inf();
                          VEC_INC(Targ1, k-i)
                          BREAK_FOR_I
                      } else
                          if (TARG1 < 0.0) {
                          r0 = make_nan();
                              VEC_INC(Targ1, k-i)
                              BREAK_FOR_I
                          } else {
                              r0 = 0.0;
                              Targ1++;
                          }
                  TRES_INC = r0;
#if defined(_HIGHER_ORDER_)
                  for (i=1;i<k;i++)
                  *Tres++ = make_nan();
#endif /* _HIGHER_ORDER_ */
                } else
                    FOR_0_LE_l_LT_p {
                        FOR_0_LE_i_LT_k
                        { /* olvo 980921 changed order to allow x = acosh(x) */
#if defined(_HIGHER_ORDER_)
                            zOP      = dp_z+i;
                            (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                            TRES_FOINC = dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                            Targ2OP = Targ2;

                            *Tres *= (i+1);
                            for (j=0;j<i;j++)
                                *Tres += (*Targ2OP++) * (*zOP--);
                                *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                            }
                            HOV_INC(Targ2, k)
                        }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                        break;

            /*--------------------------------------------------------------------------*/
        case atanh_op:                                            /* atanh_op */
            arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = atanh(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg1, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_FOINC;
#else
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

                if (dp_T0[arg1] == 1.0)
                    FOR_0_LE_l_LT_p
                    { FOR_0_LE_i_LT_k
                      if (TARG1 > 0.0) {
                      r0 = make_nan();
                          VEC_INC(Targ1, k-i)
                          BREAK_FOR_I
                      } else
                          if (TARG1 < 0.0) {
                          r0 = make_inf();
                              VEC_INC(Targ1, k-i)
                              BREAK_FOR_I
                          } else {
                              r0 = 0.0;
                              Targ1++;
                          }
                  TRES_INC = r0;
#if defined(_HIGHER_ORDER_)
                  for (i=1;i<k;i++)
                  *Tres++ = make_nan();
#endif /* _HIGHER_ORDER_ */
                } else
                    if (dp_T0[arg1] == -1.0)
                            FOR_0_LE_l_LT_p
                            { FOR_0_LE_i_LT_k
                              if (TARG1 > 0.0) {
                              r0 = make_inf();
                                  VEC_INC(Targ1, k-i)
                                  BREAK_FOR_I
                              } else
                                  if (TARG1 < 0.0) {
                                  r0 = make_nan();
                                      VEC_INC(Targ1, k-i)
                                      BREAK_FOR_I
                                  } else {
                                      r0 = 0.0;
                                      Targ1++;
                                  }
                  TRES_INC = r0;
#if defined(_HIGHER_ORDER_)
                  for (i=1;i<k;i++)
                  *Tres++ = make_nan();
#endif /* _HIGHER_ORDER_ */
                        } else
                            FOR_0_LE_l_LT_p {
                                FOR_0_LE_i_LT_k
                                { /* olvo 980921 changed order to allow x = atanh(x) */
#if defined(_HIGHER_ORDER_)
                                    zOP      = dp_z+i;
                                    (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                                    TRES_FOINC = dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                                    Targ2OP = Targ2;

                                    *Tres *= (i+1);
                                    for (j=0;j<i;j++)
                                        *Tres += (*Targ2OP++) * (*zOP--);
                                        *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                                    }
                                    HOV_INC(Targ2, k)
                                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                                break;

            /*--------------------------------------------------------------------------*/
        case erf_op:                                                /* erf_op */
            arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = erf(dp_T0[arg1]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;
#if defined(_INDO_)
                copy_index_domain(res, arg1, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1,TAYLOR_BUFFER[arg1])
#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_FOINC;
#else
                ASSIGN_T(Targ2,TAYLOR_BUFFER[arg2])

                FOR_0_LE_l_LT_p
                { FOR_0_LE_i_LT_k
                  { /* olvo 980921 changed order to allow x = erf(x) */
#if defined(_HIGHER_ORDER_)
                      zOP      = dp_z+i;
                      (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                      TRES_FOINC = dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                      Targ2OP = Targ2;

                      *Tres *= (i+1);
                      for (j=0;j<i;j++)
                      *Tres += (*Targ2OP++) * (*zOP--);
                      *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                  }
                  HOV_INC(Targ2, k)
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

#endif

            /*--------------------------------------------------------------------------*/
        case log_op:                                                /* log_op */
            arg = get_locint_f();
                res = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG_INC;
#else
                divs = 1.0 / dp_T0[arg];
                FOR_0_LE_l_LT_p
                { if (dp_T0[arg] == 0.0) {
                  TargOP = Targ;
                  FOR_0_LE_i_LT_k
                  { if (*TargOP++ < 0.0) {
                        divs = make_nan();
                            BREAK_FOR_I
                        }
                      }
                  }

                  /* olvo 980921 changed order to allow x = log(x) */
                  FOR_0_LE_i_LT_k
                  { TRES_FOINC = TARG_INC * divs;
#if defined(_HIGHER_ORDER_)
                    TresOP = Tres - i;
                    zOP    = dp_z+i;

                    (*zOP--) = *Tres;
                    (*Tres) *= i+1;
                    for (j=0;j<i;j++)
                    (*Tres) -= (*zOP--) * (*TresOP++) * (j+1);
                    *Tres++ /= i+1;
#endif /* _HIGHER_ORDER_ */
                  }
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
#if !defined(_NTIGHT_)
                dp_T0[res] = log(dp_T0[arg]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;
                break;

                /*--------------------------------------------------------------------------*/
            case pow_op:                                                /* pow_op */
                arg   = get_locint_f();
                res   = get_locint_f();

                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

                /* olvo 980921 necessary for reverse */
                if (arg == res) {
                    IF_KEEP_WRITE_TAYLOR(arg,keep,k,p)
                }

#if !defined(_NTIGHT_)

#ifndef _ZOS_ /* BREAK_ZOS */
#if !defined(_INT_FOR_)
                T0arg   = dp_T0[arg];
#endif
#endif /* ALL_TOGETHER_AGAIN */

                dp_T0[res] =
                    pow(dp_T0[arg], coval);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;
#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg, ind_dom, nonl_dom);
#endif
#else
#ifndef _ZOS_ /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG_INC;
#else
                if (T0arg == 0.0) {
                    if (coval <= 0.0)
                        FOR_0_LE_l_LT_pk
                        TRES_INC = make_nan();
                    else {
                        /* coval not a whole number */
                        if (coval - floor(coval) != 0) {
                            FOR_0_LE_l_LT_p
                            {
                                i = 0;
                                FOR_0_LE_i_LT_k
                                {
                                    if (coval - i > 1)
                                    TRES_INC = 0;
                                    if ((coval - i < 1) && (coval - i > 0))
                                        TRES_INC = make_inf();
                                        if (coval - i < 0)
                                            TRES_INC = make_nan();
                                        }
                                    }
                                } else {
                        if (coval == 1) {
                                FOR_0_LE_l_LT_pk
                                TRES_INC = TARG_INC;
                            } else
                                /* coval is an int > 1 */
                                /* the following is not efficient but at least it works */
                                /* it reformulates x^n into x* ... *x n times */
                            {
                                INC_pk_1(Targ)
                                INC_pk_1(Tres)

                                FOR_p_GT_l_GE_0
                                {
                                    FOR_k_GT_i_GE_0
                                    {
                                        *Tres = 0;
                                        DEC_TRES_FO
#if defined(_HIGHER_ORDER_)
                                        if (i == k-1) {
                                        zOP = dp_z+k-1;
                                        for(j=k-1;j>=0;j--) {
                                                (*zOP--) = (*Targ--);
                                            }
                                        }
                                        for (j=0;j<i;j++) {
                                        *Tres += dp_z[j] *
                                                     dp_z[i-j-1];
                                        }
                                        Tres--;
#endif /* _HIGHER_ORDER_ */
                                    }
                                }
                                for(ii=3;ii<=coval;ii++) {
                                    ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                                    ASSIGN_T(Targ, TAYLOR_BUFFER[arg])
                                    INC_pk_1(Targ)
                                    INC_pk_1(Tres)

                                    FOR_p_GT_l_GE_0
                                    {
                                        FOR_k_GT_i_GE_0
                                        {
                                            *Tres = 0;
                                            DEC_TRES_FO
#if defined(_HIGHER_ORDER_)
                                            TresOP = Tres-i;
                                            for (j=0;j<i;j++)
                                            *Tres += TresOP[j] * dp_z[i-j-1];
                                            Tres--;
#endif /* _HIGHER_ORDER_ */
                                        }
                                    }
                                }
                        }
                    }
                }
            } else {
                r0 = 1.0 / T0arg;
                FOR_0_LE_l_LT_p
                FOR_0_LE_i_LT_k
                { /* olvo 980921 changed order to allow x = pow(x,n) */
#ifdef _HIGHER_ORDER_
                    zOP      = dp_z+i;
                    (*zOP--) = (*Targ) * r0;
#endif /* _HIGHER_ORDER_ */

                    TRES_FOINC = dp_T0[res] *
                                 TARG_INC * coval * r0;

#ifdef _HIGHER_ORDER_
                    TresOP = Tres-i;

                    (*Tres) *= i+1;
                    y = coval*i -1;
                    for (j=0;j<i;j++) {
                        *Tres += (*TresOP++) * (*zOP--) * y;
                            y -= coval + 1;
                        }
                        *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                    }
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case sqrt_op:                                              /* sqrt_op */
                arg = get_locint_f();
                res = get_locint_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = sqrt(dp_T0[arg]);
#endif /* !_NTIGHT_ */

                ADOLC_OPENMP_RESTORE_THREAD_NUMBER;

#if defined(_INDO_)
                copy_index_domain(res, arg, ind_dom);
#if defined(_NONLIND_)
                extend_nonlinearity_domain_unary(arg, ind_dom, nonl_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG_INC;
#else
                FOR_0_LE_l_LT_p
                { TargOP = Targ;
                  if (dp_T0[arg] == 0.0)
                  /* Note: <=> dp_T0[res] == 0.0 */
              { r0 = 0.0;
                  FOR_0_LE_i_LT_k
                  { if (TARG>0.0) {
                        r0 = make_inf();
                            VEC_INC(Targ, k-i)
                            BREAK_FOR_I
                        } else
                            if (TARG<0.0) {
                            r0 = make_nan();
                                VEC_INC(Targ, k-i)
                                BREAK_FOR_I
                            } else
                                Targ++;
                              }
                          }
                  else {
                      r0 = 0.5/dp_T0[res];
                  }
                  Targ = TargOP;

                  even = 1;
                  FOR_0_LE_i_LT_k
                  { TRES_FOINC = r0 * TARG_INC;
#if defined(_HIGHER_ORDER_)
                    TresOP  = Tres-i;
                    TresOP2 = Tres-1;

                    x = 0;
                    for (j=1;2*j-1<i;j++)
                    x += (*TresOP++) * (*TresOP2--);
                    x *= 2;
                    if (!even)
                        x += (*TresOP) * (*TresOP2); /* !!! */
                        even = !even;
                        *Tres++ -= r0*x;
#endif /* _HIGHER_ORDER_ */
                      }
                    }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                    break;

            /*--------------------------------------------------------------------------*/
        case gen_quad:                                            /* gen_quad */
            arg1 = get_locint_f();
                arg2 = get_locint_f();
                res  = get_locint_f();

#if !defined(_NTIGHT_)
                if (get_val_f()!=dp_T0[arg1]) {
                    fprintf(DIAG_OUT,
                            "ADOL-C Warning: forward sweep aborted; tape invalid!\n");
                    IF_KEEP_TAYLOR_CLOSE
                    end_sweep();
                    return -2;
                }
#endif /* !_NTIGHT_ */

                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = coval;
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
               fprintf(DIAG_OUT,
                    "ADOL-C Warning: forward sweep aborted; sparse mode not available for gen_quad!\n");
               end_sweep();
               return -2;
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
#ifdef _INT_FOR_
                FOR_0_LE_l_LT_p
                TRES_FOINC = TARG1_FOINC;
#else
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])

                FOR_0_LE_l_LT_p
                { FOR_0_LE_i_LT_k
                  { /* olvo 980922 changed order to allow x = gen_quad(x) */
#if defined(_HIGHER_ORDER_)
                      zOP      = dp_z+i;
                      (*zOP--) = (i+1) * (*Targ1);
#endif /* _HIGHER_ORDER_ */

                      TRES_FOINC = dp_T0[arg2] * TARG1_INC;

#if defined(_HIGHER_ORDER_)
                      Targ2OP = Targ2;

                      *Tres *= (i+1);
                      for (j=0;j<i;j++)
                      *Tres += (*Targ2OP++) * (*zOP--);
                      *Tres++ /= (i+1);
#endif /* _HIGHER_ORDER_ */
                  }
                  HOV_INC(Targ2, k)
                }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

            /*--------------------------------------------------------------------------*/
        case min_op:                                                /* min_op */
            arg1  = get_locint_f();
                arg2  = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                /* olvo 980923 changed order to allow x = min(x,y) etc. */

                /* olvo/mitev 980721 return value (taken from below) */
                if (dp_T0[arg1] > dp_T0[arg2]) {
                    if (coval)
                        MINDEC(ret_c,2);
                } else
                    if (dp_T0[arg1] < dp_T0[arg2]) {
                        if (!coval)
                            MINDEC(ret_c,2);
                    } else
                        if (arg1 != arg2)
                            MINDEC(ret_c,1);
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
#ifdef _TIGHT_
                    if (dp_T0[arg1] < dp_T0[arg2])
                        copy_index_domain(res, arg1, ind_dom);
                    else {
                        if (dp_T0[arg1] > dp_T0[arg2])
                            copy_index_domain(res, arg2, ind_dom);
                        else
                            combine_2_index_domains(res, arg1, arg2, ind_dom);
                    }
#else
                    combine_2_index_domains(res, arg1, arg2, ind_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])

#ifdef _INT_FOR_
#ifdef _TIGHT_
                Tqo = NULL;
                if (dp_T0[arg1] > dp_T0[arg2])
                    Tqo = Targ2;
                else
                    if (dp_T0[arg1] < dp_T0[arg2])
                        Tqo = Targ1;

                FOR_0_LE_l_LT_p
                { Targ = Tqo;
                  if (Targ == NULL) /* e.g. T0[arg1] == T0[arg2] */
              { Targ1OP = Targ1;
                  Targ2OP = Targ2;
                  if (TARG1 > TARG2)
                          Targ = Targ2OP;
                      else
                          if (TARG1 < TARG2)
                              Targ = Targ1OP;
                      Targ1++;
                      Targ2++;
                      if (Targ == NULL) /* e.g. both are equal */
                          Targ = Targ1OP;
                  }

                  TRES_INC = TARG_INC;

                  if (Tqo)
                  Tqo++;
                }

                dp_T0[res] = MIN_ADOLC(dp_T0[arg1], dp_T0[arg2]);
#endif /* _TIGHT_ */
#ifdef _NTIGHT_
                TRES_INC = TARG1_INC | TARG2_INC;
#endif /* _NTIGHT_ */
#else
                Tqo = NULL;
                if (dp_T0[arg1] > dp_T0[arg2])
                    Tqo = Targ2;
                else
                    if (dp_T0[arg1] < dp_T0[arg2])
                        Tqo = Targ1;

                FOR_0_LE_l_LT_p
                { Targ = Tqo;
                  if (Targ == NULL) /* e.g. dp_T0[arg1] ==
                                                                                 dp_T0[arg2] */
              { Targ1OP = Targ1;
                  Targ2OP = Targ2;
                  FOR_0_LE_i_LT_k
                  { if (TARG1 > TARG2) {
                        Targ = Targ2OP;
                        VEC_INC(Targ1, k-i)
                            VEC_INC(Targ2, k-i)
                            BREAK_FOR_I
                        } else
                            if (TARG1 < TARG2) {
                            Targ = Targ1OP;
                            VEC_INC(Targ1, k-i)
                                VEC_INC(Targ2, k-i)
                                BREAK_FOR_I
                            }
                        Targ1++;
                        Targ2++;
                      }
                      if (Targ == NULL) /* e.g. both are equal */
                          Targ = Targ1OP;
                  }

                  FOR_0_LE_i_LT_k
                  TRES_INC = TARG_INC;

                  if (Tqo) {
                  VEC_INC(Tqo, k)
                  }
            }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
#if !defined(_NTIGHT_)
                dp_T0[res] =
                    MIN_ADOLC( dp_T0[arg1],
                               dp_T0[arg2] );
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case abs_val:                                              /* abs_val */
                arg   = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                /* olvo 980923 changed order to allow x = min(x,y) etc. */

                /* olvo/mitev 980721 ec n3l (taken from below) */
                if (dp_T0[arg] < 0.0) {
                    if (coval)
                        MINDEC(ret_c,2);
                } else
                    if (dp_T0[arg] > 0.0) {
                        if (!coval)
                            MINDEC(ret_c,2);
                    }
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
		copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])
                ASSIGN_T(Targ, TAYLOR_BUFFER[arg])

#ifdef _INT_FOR_
#ifdef _TIGHT_
                y = 0.0;
                if (dp_T0[arg] != 0.0) {
                    if (dp_T0[arg] < 0.0)
                        y = -1.0;
                    else
                        y = 1.0;
                }
                FOR_0_LE_l_LT_p
                { if ((y == 0.0) && (TARG != 0.0))
                  MINDEC(ret_c,1);

                  TRES_INC = TARG_INC;
                }

                dp_T0[res] = fabs(dp_T0[arg]);
#endif /* _TIGHT_ */
#ifdef _NTIGHT_
                FOR_0_LE_l_LT_p
                TRES_INC = TARG_INC;
#endif /* _NTIGHT_ */
#else
                y = 0.0;
                if (dp_T0[arg] != 0.0) {
                    if (dp_T0[arg] < 0.0)
                        y = -1.0;
                    else
                        y = 1.0;
                }

                FOR_0_LE_l_LT_p
                { x = y;
                  FOR_0_LE_i_LT_k
                  { if ((x == 0.0) && (TARG != 0.0)) {
                    MINDEC(ret_c,1);
                        if (TARG < 0.0)
                            x = -1.0;
                        else
                            x = 1.0;
                    }
                    TRES_INC = x * TARG_INC;
              }
            }
#endif
#endif
#endif /* ALL_TOGETHER_AGAIN */
#if !defined(_NTIGHT_)
                dp_T0[res] = fabs(dp_T0[arg]);
#endif /* !_NTIGHT_ */
                break;

                /*--------------------------------------------------------------------------*/
            case ceil_op:                                              /* ceil_op */
                arg   = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res]=ceil(dp_T0[arg]);
                /* olvo/mitev 980721 ec n2l (taken from below) */
                if (coval != dp_T0[res])
                    MINDEC(ret_c,2);
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
		copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

                FOR_0_LE_l_LT_pk
                TRES_INC = 0.0;
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case floor_op:                 /* Compute ceil of adouble    floor_op */
                arg   = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

#if !defined(_NTIGHT_)
                dp_T0[res] = floor(dp_T0[arg]);
                /* olvo/mitev 980721 ec n2l (taken from below) */
                if (coval != dp_T0[res])
                    MINDEC(ret_c,2);
#endif /* !_NTIGHT_ */

#if defined(_INDO_)
		copy_index_domain(res, arg, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres, TAYLOR_BUFFER[res])

                FOR_0_LE_l_LT_pk
                TRES_INC = 0.0;
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;


                /****************************************************************************/
                /*                                                             CONDITIONALS */

                /*--------------------------------------------------------------------------*/
            case cond_assign:                                      /* cond_assign */
                arg   = get_locint_f();
                arg1  = get_locint_f();
                arg2  = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

                /* olvo 980924 changed order to allow reflexive ops */
#if defined(_INDO_)
#ifdef _TIGHT_
                if (dp_T0[arg] > 0) {
                    if (coval <= 0.0)
                        MINDEC(ret_c,2);
                    dp_T0[res] = dp_T0[arg1];

		    combine_2_index_domains(res, arg1, arg2, ind_dom);
#else
                        copy_index_domain(res, arg1, ind_dom);
#endif
#ifdef _TIGHT_
                } else {
                    if (coval > 0.0)
                        MINDEC(ret_c,2);
                    if (dp_T0[arg] == 0)
                        MINDEC(ret_c,0);
                    dp_T0[res] = dp_T0[arg2];

                        combine_2_index_domains(res, arg1, arg2, ind_dom);
                }
#else
                        copy_index_domain(res, arg2, ind_dom);
#endif
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
                ASSIGN_T(Targ2, TAYLOR_BUFFER[arg2])
#endif /* ALL_TOGETHER_AGAIN */

#ifdef _INT_FOR_
#ifdef _TIGHT_
                coval = get_val_f();

                if (dp_T0[arg] > 0)
                    FOR_0_LE_l_LT_pk
                    TRES_INC = TARG1_INC;
                else
                    FOR_0_LE_l_LT_pk
                    TRES_INC = TARG2_INC;

                if (dp_T0[arg] > 0) {
                    if (coval <= 0.0)
                        MINDEC(ret_c,2);
                    dp_T0[res] = dp_T0[arg1];
                } else {
                    if (coval > 0.0)
                        MINDEC(ret_c,2);
                    if (dp_T0[arg] == 0)
                        MINDEC(ret_c,0);
                    dp_T0[res] = dp_T0[arg2];
                }
#endif /* _TIGHT_ */
#ifdef _NTIGHT_
                FOR_0_LE_l_LT_pk
                TRES_INC = TARG1_INC | TARG2_INC;
#endif /* _NTIGHT_ */
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                if (dp_T0[arg] > 0)
                    FOR_0_LE_l_LT_pk
                    TRES_INC = TARG1_INC;
                else
                    FOR_0_LE_l_LT_pk
                    TRES_INC = TARG2_INC;
#endif

                if (dp_T0[arg] > 0) {
                    if (coval <= 0.0)
                        MINDEC(ret_c,2);
                    dp_T0[res] = dp_T0[arg1];
                } else {
                    if (coval > 0.0)
                        MINDEC(ret_c,2);
                    if (dp_T0[arg] == 0)
                        MINDEC(ret_c,0);
                    dp_T0[res] = dp_T0[arg2];
                }
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;

                /*--------------------------------------------------------------------------*/
            case cond_assign_s:                                  /* cond_assign_s */
                arg   = get_locint_f();
                arg1  = get_locint_f();
                res   = get_locint_f();
                coval = get_val_f();

                IF_KEEP_WRITE_TAYLOR(res,keep,k,p)

                /* olvo 980924 changed order to allow reflexive ops */
#if defined(_INDO_)
                    copy_index_domain(res, arg1, ind_dom);
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                ASSIGN_T(Tres,  TAYLOR_BUFFER[res])
                ASSIGN_T(Targ1, TAYLOR_BUFFER[arg1])
#endif /* ALL_TOGETHER_AGAIN */

#ifdef _INT_FOR_
#ifdef _TIGHT_
                coval = get_val_f();

                if (dp_T0[arg] > 0)
#endif /* _TIGHT_ */
                    FOR_0_LE_l_LT_pk
                    TRES_INC = TARG1_INC;

#ifdef _TIGHT_
                if (dp_T0[arg] > 0) {
                    if (coval <= 0.0)
                        MINDEC(ret_c,2);
                    dp_T0[res] = dp_T0[arg1];
                } else
                    if (dp_T0[arg] == 0)
                        MINDEC(ret_c,0);
#endif /* _TIGHT_ */
#else
#if !defined(_ZOS_) /* BREAK_ZOS */
                if (dp_T0[arg] > 0)
                    FOR_0_LE_l_LT_pk
                    TRES_INC = TARG1_INC;
#endif
                if (dp_T0[arg] > 0) {
                    if (coval <= 0.0)
                        MINDEC(ret_c,2);
                    dp_T0[res] = dp_T0[arg1];
                } else
                    if (dp_T0[arg] == 0)
                        MINDEC(ret_c,0);
#endif
#endif /* ALL_TOGETHER_AGAIN */
                break;


                /****************************************************************************/
                /*                                                          REMAINING STUFF */

                /*--------------------------------------------------------------------------*/
            case take_stock_op:                                  /* take_stock_op */
                size = get_locint_f();
                res  = get_locint_f();
                d    = get_val_v_f(size);

                for (ls=0;ls<size;ls++) {
#if !defined(_NTIGHT_)
                    dp_T0[res]=*d;
#endif /* !_NTIGHT_ */
#if !defined(_INDO_)
#if !defined(_ZOS_) /* BREAK_ZOS */
                    ASSIGN_T(Tres,TAYLOR_BUFFER[res])

                    FOR_0_LE_l_LT_pk
                    TRES_INC = 0;

#endif /* ALL_TOGETHER_AGAIN */
                    res++;
#if !defined(_NTIGHT_)
                    d++;
#endif /* !_NTIGHT_ */
#endif
                }
                break;

                /*--------------------------------------------------------------------------*/
            case death_not:                                          /* death_not */
                arg1=get_locint_f();
                arg2=get_locint_f();

#ifdef _KEEP_
                if (keep) {
                    do {
                        IF_KEEP_WRITE_TAYLOR(arg2,keep,k,p)
                    } while(arg1 < arg2-- );
                }
#endif
                break;

                /*--------------------------------------------------------------------------*/
#if defined(_EXTERN_) /* ZOS and FOS up to now */
            case ext_diff:                       /* extern differntiated function */
                ADOLC_CURRENT_TAPE_INFOS.ext_diff_fct_index=get_locint_f();
                n=get_locint_f();
                m=get_locint_f();
                ADOLC_CURRENT_TAPE_INFOS.lowestXLoc_for = get_locint_f();
                ADOLC_CURRENT_TAPE_INFOS.lowestYLoc_for = get_locint_f();
                ADOLC_CURRENT_TAPE_INFOS.cpIndex = get_locint_f();
                edfct=get_ext_diff_fct(ADOLC_CURRENT_TAPE_INFOS.ext_diff_fct_index);

                if (edfct->ADOLC_EXT_FCT_POINTER==NULL)
                    fail(ADOLC_EXT_DIFF_NULLPOINTER_DIFFFUNC);
                if (n>0) {
                    if (edfct->dp_x==NULL) fail(ADOLC_EXT_DIFF_NULLPOINTER_ARGUMENT);
#if !defined(_ZOS_)
                    if (ADOLC_EXT_POINTER_X==NULL) fail(ADOLC_EXT_DIFF_NULLPOINTER_ARGUMENT);
#endif
                }
                if (m>0) {
                    if (edfct->dp_y==NULL) fail(ADOLC_EXT_DIFF_NULLPOINTER_ARGUMENT);
#if !defined(_ZOS_)
                    if (ADOLC_EXT_POINTER_Y==NULL) fail(ADOLC_EXT_DIFF_NULLPOINTER_ARGUMENT);
#endif
                }

                arg = ADOLC_CURRENT_TAPE_INFOS.lowestXLoc_for;
                for (loop=0; loop<n; ++loop) {
                    edfct->dp_x[loop]=dp_T0[arg];
#if !defined(_ZOS_)
                    ADOLC_EXT_LOOP
                        ADOLC_EXT_POINTER_X[loop]ADOLC_EXT_SUBSCRIPT =
                        TAYLOR_BUFFER[arg]ADOLC_EXT_SUBSCRIPT;
#endif
                    ++arg;
                }
                arg = ADOLC_CURRENT_TAPE_INFOS.lowestYLoc_for;
                for (loop=0; loop<m; ++loop) {
                    edfct->dp_y[loop]=dp_T0[arg];
#if !defined(_ZOS_)
                    ADOLC_EXT_LOOP
                        ADOLC_EXT_POINTER_Y[loop]ADOLC_EXT_SUBSCRIPT =
                        TAYLOR_BUFFER[arg]ADOLC_EXT_SUBSCRIPT;
#endif
                    ++arg;
                }

                ext_retc = edfct->ADOLC_EXT_FCT_COMPLETE;
                MINDEC(ret_c, ext_retc);

                res = ADOLC_CURRENT_TAPE_INFOS.lowestXLoc_for;
                for (loop=0; loop<n; ++loop) {
                    IF_KEEP_WRITE_TAYLOR(res, keep, k, p);
                    dp_T0[res]=edfct->dp_x[loop];
#if !defined(_ZOS_)
                    ADOLC_EXT_LOOP
                        TAYLOR_BUFFER[res]ADOLC_EXT_SUBSCRIPT =
                        ADOLC_EXT_POINTER_X[loop]ADOLC_EXT_SUBSCRIPT;
#endif
                    ++res;
                }
                res = ADOLC_CURRENT_TAPE_INFOS.lowestYLoc_for;
                for (loop=0; loop<m; ++loop) {
                    IF_KEEP_WRITE_TAYLOR(res, keep, k, p);
                    dp_T0[res]=edfct->dp_y[loop];
#if !defined(_ZOS_)
                    ADOLC_EXT_LOOP
                        TAYLOR_BUFFER[res]ADOLC_EXT_SUBSCRIPT =
                        ADOLC_EXT_POINTER_Y[loop]ADOLC_EXT_SUBSCRIPT;
#endif
                    ++res;
                }

                break;
#endif
                /*--------------------------------------------------------------------------*/
#if defined(_MPI_)
      case send_data:	// MPI-Send-Befehl
	      count = get_locint_f(); // first Buffer
           loc_send = (locint*) malloc(count*sizeof(locint));
           for(mpi_i=0; mpi_i < count; mpi_i++)
               loc_send[mpi_i] = get_locint_f();
           res = get_locint_f();
	      target = get_locint_f(); // dest
	      tag = get_locint_f(); // tag

#if defined(_ZOS_)
          trade = myalloc1( count );
          for (mpi_i=0; mpi_i< count; mpi_i++)
                    trade[mpi_i] = dp_T0[ loc_send[mpi_i]];
          MPI_Send( trade , count, MPI_DOUBLE , target, tag , MPI_COMM_WORLD);
          free(trade);
#endif /* _ZOS_ */
#if defined(_FOS_)
           trade = myalloc1(count*2);
           for (mpi_i=0; mpi_i< count; mpi_i++) {
                trade[2*mpi_i ]= dp_T0[loc_send[mpi_i]];
                trade[2*mpi_i+1]= dp_T[loc_send[mpi_i]];
           }
           MPI_Send( trade , count*2, MPI_DOUBLE , target, tag , MPI_COMM_WORLD);
           free(trade);
#endif /* END FOS */
#if defined(_FOV_)
           trade = myalloc1((p+1)*count);
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
                trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                mpi_ii++;
                for(i=0;i<p;i++,mpi_ii++)
                     trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
           }
           MPI_Send( trade , count*(p+1), MPI_DOUBLE , target, tag , MPI_COMM_WORLD);
           free(trade);
#endif /* END FOV */
#if defined(_HOS_)
           trade = myalloc1(count*(k+1));
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++){
               trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
               mpi_ii++;
               for (i=0; i<k; i++,mpi_ii++)
                   trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
           }
           MPI_Send( trade , count*(k+1), MPI_DOUBLE , target, tag , MPI_COMM_WORLD);
           free(trade);
#endif /* END HOS */
#if defined(_HOV_)
           trade = myalloc1(count*(p*k+1));
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++){
               trade[mpi_ii] = dp_T0[loc_send[mpi_ii]];
               mpi_ii++;
               for (i=0; i<p*k; i++,mpi_ii)
                   trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
           }
           MPI_Send( trade , count*(p*k+1), MPI_DOUBLE , target, tag , MPI_COMM_WORLD);
           free(trade);
#endif /* END HOV */

#if defined(_TIGHT_) /* with dp_T0 */
#if defined(_INT_FOR_)
           trade = myalloc1(count*(p+1));
           mpi_ii=0;
           for(mpi_i=0; mpi_i< count; mpi_i++) {
              trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
              mpi_ii++;
              for(l=0;l<p;l++,mpi_ii++)
                 trade[mpi_ii]= (double) up_T[loc_send[mpi_i]][l];
           }
           MPI_Send( trade_loc , count*(p+1), MPI_DOUBLE , target, tag , MPI_COMM_WORLD);
           free(trade_loc);
#endif /* END INT_FOR */
#if defined(_INDO_)
           trade = myalloc1(count*2);
           anz=0;
           for (mpi_i=0; mpi_i< count; mpi_i++){
               trade[2*mpi_i ] = dp_T0[loc_send[mpi_i]];
               trade[2*mpi_i+1]= (double) ind_dom[loc_send[mpi_i]][0];
               anz += ind_dom[loc_send[mpi_i]][0];
           }
           MPI_Send( trade , count*2 , MPI_DOUBLE , target, tag , MPI_COMM_WORLD);

           // sending index domains
           if (anz > 0 ){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              l =0;
              for (mpi_i=0; mpi_i< count; mpi_i++){
                  for(i=2;i < ind_dom[loc_send[mpi_i]][0]+2 ;i++ ){
                       trade_loc[l] = (int) ind_dom[loc_send[mpi_i]][i];
                       l++;
                  }
              }
              MPI_Send( trade_loc , anz , MPI_INT , target, tag , MPI_COMM_WORLD);
              free(trade_loc);
           }
           free(trade);
#endif
#if defined(_NONLIND_)
           trade = myalloc1(s_r_indep*2);
           anz=0;
           for (mpi_i=0; mpi_i< s_r_indep; mpi_i++){
               trade[2*mpi_i ] = dp_T0[loc_send[mpi_i]];
               trade[2*mpi_i+1]= (double) nonl_dom[loc_send[mpi_i]][0];
               anz += nonl_dom[loc_send[mpi_i]][0];
           }
           MPI_Send( trade , s_r_indep*2 , MPI_DOUBLE , target, tag , MPI_COMM_WORLD);
           // sending index domains
           if (anz >0 ){
              trade_loc = (int*) malloc(anz*sizeof(int));
              l =0;
              for (mpi_i=0; mpi_i < s_r_indep ; mpi_i++ )
                  for (i=2; i < nonl_dom[mpi_i][0]+2 ; i++ ){
                      trade_loc[l] = nonl_dom[mpi_i][i];
                      l++;
                  }
              MPI_Send( trade_loc , anz , MPI_INT , target, tag , MPI_COMM_WORLD);
              free( trade_loc);
           }
           free( trade);
#endif    // end _NONLIND_
#endif /* END OF TIGHT */
#if defined(_NTIGHT_) /* without dp_T0 */
#if defined(_INT_FOR_)
           trade_loc = (locint*) malloc(count*p*sizeof(locint));
           mpi_ii=0;
           for(mpi_i=0; mpi_i< count; mpi_i++) {
              for(l=0;l<p;l++,mpi_ii++)
                 trade[mpi_ii]= up_T[loc_send[mpi_i]][l];
           }
           MPI_Send( trade_loc , count*p, MPI_UNSIGNED_LONG , target, tag , MPI_COMM_WORLD);
           free(trade_loc);
#endif /* END INT_FOR */
#if defined(_INDO_)
           counts = (int*) malloc(count*sizeof(int));
           anz=0;
           for (mpi_i=0; mpi_i< count; mpi_i++){
               trade[mpi_i]= ind_dom[loc_send[mpi_i]][0];
               anz += ind_dom[loc_send[mpi_i]][0];
           }
           MPI_Send( counts , count , MPI_INT , target, tag , MPI_COMM_WORLD);

           // sending index domains
           if (anz > 0 ){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              l =0;
              for (mpi_i=0; mpi_i< count; mpi_i++){
                  for(i=2;i < ind_dom[loc_send[mpi_i]][0]+2 ;i++ ){
                       trade_loc[l] = ind_dom[loc_send[mpi_i]][i];
                       l++;
                  }
              }
              MPI_Send( trade_loc , anz , MPI_INT , target, tag , MPI_COMM_WORLD);
              free(trade_loc);
           }
           free(trade);
#endif
#if defined(_NONLIND_)
           counts = (int*) malloc(s_r_indep*sizeof(int));
           anz=0;
           for (mpi_i=0; mpi_i< s_r_indep; mpi_i++){
               counts[mpi_i]= nonl_dom[loc_send[mpi_i]][0];
               anz += nonl_dom[loc_send[mpi_i]][0];
           }
           MPI_Send( counts , s_r_indep , MPI_INT , target, tag , MPI_COMM_WORLD);
           // sending index domains
           if (anz >0 ){
              trade_loc = (int*) malloc(anz*sizeof(int));
              l =0;
              for (mpi_i=0; mpi_i < s_r_indep ; mpi_i++ )
                  for (i=2; i < counts[mpi_i]+2 ; i++ ){
                      trade_loc[l] = nonl_dom[mpi_i][i];
                      l++;
                  }
              MPI_Send( trade_loc , anz , MPI_INT , target, tag , MPI_COMM_WORLD);
              free( trade_loc);
           }
           free(counts);
#endif    // end _NONLIND_
#endif /* END OF TIGHT */
           free(loc_send);
	      break;
                /*--------------------------------------------------------------------------*/
      case receive_data: // MPI-Receive
           count =get_locint_f(); // count
           loc_recv = (locint*) malloc(count*sizeof(locint));
           for(mpi_i=0; mpi_i<count;mpi_i++)
               loc_recv[mpi_i] = get_locint_f();
           res =get_locint_f(); // count
           target = get_locint_f(); // source
           tag = get_locint_f(); // tag
#if defined(_ZOS_)
           // receiving values for dp_T0
           trade = myalloc1( count );
           MPI_Recv( trade , count, MPI_DOUBLE , target, tag , MPI_COMM_WORLD, &status_MPI);
           for(mpi_i =0; mpi_i < count; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = trade[mpi_i];
           }
           free(trade);
#endif /* END _ZOS_ */
#if defined(_FOS_)
           trade = myalloc1(count*2);
           MPI_Recv( trade , count*2, MPI_DOUBLE , target, tag , MPI_COMM_WORLD, &status_MPI);
           /*  Receiving double Values by MPI and try to save Taylorbuffer before overwriting */
           for(mpi_i=0; mpi_i< count; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = trade[2*mpi_i];
              dp_T[loc_recv[mpi_i]] = trade[2*mpi_i]+1;
              }
           free(trade);
#endif
#if defined(_FOV_)
           trade = myalloc1(count*(p+1));
           MPI_Recv( trade , (p+1)*count, MPI_DOUBLE , target, tag , MPI_COMM_WORLD, &status_MPI);
           /*  Receiving double Values by MPI and try to save Taylorbuffer before overwriting */
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = trade[mpi_ii];
              mpi_ii++;
              for(i=0;i<p;i++,mpi_ii++)
                 dpp_T[loc_recv[mpi_i]][i] = trade[mpi_ii];
           }
           free(trade);
#endif
#if defined(_HOS_)
           trade =myalloc1(count*(k+1));
           MPI_Recv( trade , (k+1)*count, MPI_DOUBLE , target, tag , MPI_COMM_WORLD, &status_MPI);
           /*  Receiving double Values by MPI and try to save Taylorbuffer before overwriting */
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = trade[mpi_i];
               for(i=0; i < k ; i++ )
                dpp_T[loc_recv[mpi_i]][i] = trade[k*mpi_i+i];
           }
           myfree1(trade);
#endif
#if defined(_HOV_)
           trade =myalloc1(count*(p*k+1));
           MPI_Recv( trade , (p*k+1)*count, MPI_DOUBLE , target, tag , MPI_COMM_WORLD, &status_MPI);
           /*  Receiving double Values by MPI and try to save Taylorbuffer before overwriting */
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = trade[mpi_ii];
              mpi_ii++;
              for(i=0; i < p*k ; i++,mpi_ii++)
                 dpp_T[loc_recv[mpi_i]][i] = trade[mpi_ii];
           }
           free(trade);
#endif
#if defined(_TIGHT_)
#if defined(_INT_FOR_)
           trade = myalloc1(count*(p+1));
           MPI_Recv( trade , count*(p+1), MPI_DOUBLE , target, tag , MPI_COMM_WORLD, &status_MPI);
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = trade[mpi_ii];
              mpi_ii++;
              for(l=0; l < p;l++,mpi_ii++)
                up_T[loc_recv[mpi_i]][l]= (unsigned long int) trade[mpi_ii];
           }
           free(trade_loc);
#endif /* END INT_FOR */
#if defined(_INDO_)
           // getting information about count of entries
           counts = ( int*) malloc( count*sizeof(int) );
           trade = myalloc1(count*2);
           MPI_Recv( trade , count*2, MPI_DOUBLE , target, tag , MPI_COMM_WORLD, &status_MPI);

           anz =0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = trade[2*mpi_i];
              counts[mpi_i] = (int) trade[2*mpi_i+1];
              anz += counts[mpi_i];
           }
           free(trade);
           if ( anz > 0){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              MPI_Recv( trade_loc , anz , MPI_INT , target, tag , MPI_COMM_WORLD, &status_MPI);

              // combine each index domain ...
              l = 0;
              for(mpi_i=0; mpi_i < count; mpi_i++){
                   combine_index_domain_received_data(loc_recv[mpi_i], counts[mpi_i], ind_dom, &trade_loc[l] );
                   l += counts[mpi_i];
              }
              free(trade_loc);
           }
           free( counts);
#endif
#if defined(_NONLIND_)
           counts = ( int*) malloc( s_r_indep*sizeof(int) );
           trade = myalloc1(s_r_indep*2);
           MPI_Recv( trade , s_r_indep*2, MPI_DOUBLE , target, tag , MPI_COMM_WORLD, &status_MPI);

           anz =0;
           for (mpi_i=0; mpi_i< s_r_indep; mpi_i++) {
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = trade[2*mpi_i];
              counts[mpi_i] = (int) trade[2*mpi_i+1];
              anz += counts[mpi_i];
           }
           free(trade);
           if (anz > 0) {
              trade_loc = (int*) calloc( anz,sizeof(int) );
              MPI_Recv( trade_loc , anz , MPI_INT , target, tag , MPI_COMM_WORLD, &status_MPI);

              // combine each index domain ...
              l = 0;
              for (mpi_i=0; mpi_i < s_r_indep; mpi_i++){
                  // nonl_dom settings
                  extend_nonlinearity_domain_combine_received_trade(mpi_i, counts[mpi_i], nonl_dom, &trade_loc[l] );
                  l += counts[mpi_i];
              }

              free( trade_loc);
           }
           free( counts);
#endif    // end _NONLIND_
#endif /* END TIGHT */
#if defined(_NTIGHT_)
#if defined(_INT_FOR_)
           trade_loc = (locint*) malloc(count*p*sizeof(locint));
           MPI_Recv( trade_loc , count*p, MPI_INT , target, tag , MPI_COMM_WORLD, &status_MPI);
           for (mpi_i=0; mpi_i< count; mpi_i++) {
               FOR_0_LE_l_LT_pk
                up_T[loc_recv[mpi_i]][l]=trade_loc[mpi_i*p+l];
           }
           free(trade_loc);
#endif /* END INT_FOR */
#if defined(_INDO_)
           // getting information about count of entries
           counts = ( int*) malloc( count*sizeof(int) );
           MPI_Recv( counts , count, MPI_INT , target, tag , MPI_COMM_WORLD, &status_MPI);

           anz =0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
               anz += counts[mpi_i];
           }
           if ( anz > 0){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              MPI_Recv( trade_loc , anz , MPI_INT , target, tag , MPI_COMM_WORLD, &status_MPI);

              // combine each index domain ...
              l = 0;
              for(mpi_i=0; mpi_i < count; mpi_i++){
                   combine_index_domain_received_data(loc_recv[mpi_i], counts[mpi_i], ind_dom, &trade_loc[l] );
                   l += counts[mpi_i];
              }
              free(trade_loc);
           }
           free( counts);
#endif
#if defined(_NONLIND_)
           counts = ( int*) malloc( s_r_indep*sizeof(int) );
           MPI_Recv( counts , s_r_indep, MPI_INT , target, tag , MPI_COMM_WORLD, &status_MPI);
           anz =0;
           for (mpi_i=0; mpi_i< s_r_indep; mpi_i++){
               anz +=  (int) counts[mpi_i];
           }
           if (anz > 0) {
              trade_loc = (int*) calloc( anz,sizeof(int) );
              MPI_Recv( trade_loc , anz , MPI_INT , target, tag , MPI_COMM_WORLD, &status_MPI);

              // combine each index domain ...
              l = 0;
              for (mpi_i=0; mpi_i < s_r_indep; mpi_i++){
                  // nonl_dom settings
                  extend_nonlinearity_domain_combine_received_trade(mpi_i, counts[mpi_i], nonl_dom, &trade_loc[l] );
                  l += counts[mpi_i];
              }

              free( trade_loc);
           }
           free( counts);
#endif    // end _NONLIND_
#endif /* END OF NTIGHT */
           free(loc_recv);
	      break;
      case barrier_op:
	      MPI_Barrier(MPI_COMM_WORLD);
	      break;
      case broadcast:
           count = get_locint_f(); // count
           loc_send = (locint*) malloc(count*sizeof(locint));
           for(mpi_i=0;mpi_i<count;mpi_i++)
              loc_send[mpi_i] = get_locint_f(); // Send Location
           count2 = get_locint_f(); // count
           root = get_locint_f(); // root
           myid = get_locint_f(); // process id

#if defined(_ZOS_)
           // receiving values for dp_T0
           trade = myalloc1( count );
           if (myid == root){
              for(mpi_i =0; mpi_i < count ; mpi_i++)
                 trade[mpi_i] = dp_T0[loc_send[mpi_i]];
            }
           MPI_Bcast(trade,count, MPI_DOUBLE, root, MPI_COMM_WORLD);
           for( mpi_i =0; mpi_i < count; mpi_i++){
               IF_KEEP_WRITE_TAYLOR(loc_send[mpi_i],keep,k,p)
               dp_T0[loc_send[mpi_i]] = trade[mpi_i];
           }
           free(trade);
#endif /* END ZOS  */
#if defined(_FOS_)
           trade = myalloc1( count*2 );
           if (myid ==root){
               for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[2*mpi_i] = dp_T0[loc_send[mpi_i]];
                 trade[2*mpi_i+1] = dp_T[loc_send[mpi_i]];
              }
           }
           MPI_Bcast(trade,count*2, MPI_DOUBLE, root, MPI_COMM_WORLD);

           for( mpi_i =0; mpi_i < count; mpi_i++){
               IF_KEEP_WRITE_TAYLOR(loc_send[mpi_i],keep,k,p)
               dp_T0[loc_send[mpi_i]] = trade[2*mpi_i];
               dp_T[loc_send[mpi_i]] = trade[2*mpi_i+1];
           }
           free(trade);
#endif
#if defined(_FOV_)
           trade = myalloc1( count*(p+1));
           if (myid ==root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                 mpi_ii++;
                 for(i=0; i<p; i++,mpi_ii++)
                    trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
              }
           }
           MPI_Bcast(trade,count*(p+1), MPI_DOUBLE, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for(mpi_i =0; mpi_i < count; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_send[mpi_i],keep,k,p)
              dp_T0[loc_send[mpi_i]] = trade[ mpi_ii];
              mpi_ii++;
              for(i=0; i<p; i++,mpi_ii++)
                 dpp_T[loc_send[mpi_i]][i] = trade[mpi_ii];
           }
           free(trade);
#endif
#if defined(_HOS_)
           trade = myalloc1(count * (k+1));
           if (myid ==root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                 mpi_ii++;
                 for(i=0; i<k; i++,mpi_ii++)
                    trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
              }
           }
           MPI_Bcast(trade,count*(k+1), MPI_DOUBLE, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for(mpi_i =0; mpi_i < count; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_send[mpi_i],keep,k,p)
              dp_T0[loc_send[mpi_i]] = trade[ mpi_ii];
              mpi_ii++;
              for(i=0; i<k; i++,mpi_ii++)
                 dpp_T[loc_send[mpi_i]][i] = trade[mpi_ii];
           }
           free(trade);
#endif
#if defined(_HOV_)
           trade = myalloc1(count * (p*k+1));
           if (myid ==root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                 mpi_ii++;
                 for(i=0; i<p*k; i++,mpi_ii++)
                    trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
              }
           }
           MPI_Bcast(trade,count*(p*k+1), MPI_DOUBLE, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for(mpi_i =0; mpi_i < count; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_send[mpi_i],keep,k,p)
              dp_T0[loc_send[mpi_i]] = trade[ mpi_ii];
              mpi_ii++;
              for(i=0; i<p*k; i++,mpi_ii++)
                 dpp_T[loc_send[mpi_i]][i] = trade[mpi_ii];
           }
           free(trade);
#endif
#if defined(_TIGHT_)
#if defined(_INT_FOR_)
           trade = myalloc1(count*(p+1));
           if (myid == root){
              mpi_ii=0;
              for(mpi_i=0; mpi_i< count; mpi_i++) {
                 trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                 mpi_ii++;
                 for(l=0; l< p; l++,mpi_ii++)
                    trade[mpi_ii]= (double) up_T[loc_send[mpi_i]][l];
              }
           }
           MPI_Bcast(trade,count*(p+1), MPI_DOUBLE, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for( mpi_i =0; mpi_i < count; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_send[mpi_i],keep,k,p)
              dp_T0[loc_send[mpi_i]] = trade[mpi_ii];
              mpi_ii++;
              for(l=0; l<p; l++,mpi_ii++)
                 up_T[loc_send[mpi_i]][l] = (unsigned long int) trade[mpi_ii];
           }
           free(trade);
#endif /* END INT_FOR */
#if defined(_INDO_)
           trade = myalloc1( count*2);
           if (myid ==root){
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[2*mpi_i] = dp_T0[loc_send[mpi_i]];
                 trade[2*mpi_i+1] = (double) ind_dom[loc_send[mpi_i]][0];
              }
           }
           MPI_Bcast(trade,count*2, MPI_DOUBLE, root, MPI_COMM_WORLD);

           counts = (int*) malloc(count*sizeof(int));
           anz =0;
           for(mpi_i=0; mpi_i< count; mpi_i++) {
              IF_KEEP_WRITE_TAYLOR(loc_send[mpi_i],keep,k,p)
              dp_T0[loc_send[mpi_i]] = trade[2*mpi_i];
              counts[mpi_i] = (int) trade[2*mpi_i+1];
              anz += counts[mpi_i];
           }
           free(trade);
           if ( anz > 0){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              if (myid ==root ){
                 l=0;
                 for(mpi_i =0; mpi_i < anz; mpi_i++)
                    for(i=2; i < ind_dom[loc_send[mpi_i]][0]+2; i++){
                       trade_loc[l] = ind_dom[loc_send[mpi_i]][i];
                       l++;
                    }
              }
              MPI_Bcast(trade_loc,anz, MPI_INT, root, MPI_COMM_WORLD);
              if (myid != root){
                 l = 0;
                 for(mpi_i=0; mpi_i < count; mpi_i++){
                    combine_index_domain_received_data(loc_send[mpi_i], counts[mpi_i], ind_dom, &trade_loc[l] );
                    l += counts[mpi_i];
                 }
              }
              free(trade_loc);
           }
           free(counts);
#endif
#if defined(_NONLIND_)
           trade = myalloc1( s_r_indep*2);
           if (myid ==root){
              for(mpi_i =0; mpi_i < s_r_indep; mpi_i++){
                 trade[2*mpi_i] = dp_T0[loc_send[mpi_i]];
                 trade[2*mpi_i+1] = (double) nonl_dom[mpi_i][0];
              }
           }
           MPI_Bcast(trade,s_r_indep*2, MPI_DOUBLE, root, MPI_COMM_WORLD);

           counts = (int*) malloc(s_r_indep*sizeof(int));
           anz =0;
           for(mpi_i=0; mpi_i< s_r_indep; mpi_i++) {
              IF_KEEP_WRITE_TAYLOR(loc_send[mpi_i],keep,k,p)
              dp_T0[loc_send[mpi_i]] = trade[2*mpi_i];
              counts[mpi_i] = (int) trade[2*mpi_i+1];
              anz += counts[mpi_i];
           }
           free(trade);
           if (anz > 0) {
              trade_loc = (int*) calloc( anz,sizeof(int) );
              if (myid == root){
                 l=0;
                 for(mpi_i=0; mpi_i < s_r_indep ; mpi_i++)
                    for(i=2; i < nonl_dom[mpi_i][0]+2 ; i++){
                        trade_loc[l] = nonl_dom[mpi_i][i];
                        l++;
                    }
              }
              MPI_Bcast(trade_loc,anz, MPI_INT, root, MPI_COMM_WORLD);
              if( myid != root){
                 // combine each index domain ...
                 l = 0;
                 for (mpi_i=0; mpi_i < s_r_indep; mpi_i++){
                     // nonl_dom settings
                     extend_nonlinearity_domain_combine_received_trade(mpi_i, counts[mpi_i], nonl_dom, &trade_loc[l]);
                     l += counts[mpi_i];
                 }
              }
              free(trade_loc);
           }
           free(counts);
#endif    // end _NONLIND_
#endif /* TIGHT */
#if defined(_NTIGHT_)
#if defined(_INT_FOR_)
           trade_loc = (locint*) malloc(count*p*sizeof(locint));
           for (mpi_i=0; mpi_i< count; mpi_i++) {
               FOR_0_LE_l_LT_pk
                trade_loc[mpi_i*p+l]=up_T[loc_send[mpi_i]][l];
           }
           MPI_Bcast(trade_loc,count*p, MPI_INT, root, MPI_COMM_WORLD);
           for( mpi_i =0; mpi_i < count; mpi_i++){
              FOR_0_LE_l_LT_pk
               up_T[loc_send[mpi_i]][l] = trade_loc[mpi_i*p+l];
           }
           free(trade_loc);
#endif /* END INT_FOR */
#if defined(_INDO_)
           // getting information about count of entries
           counts = ( int*) malloc( count*sizeof(int) );
           if (myid ==root){
              for(mpi_i =0; mpi_i < count; mpi_i++)
                 counts[mpi_i] = ind_dom[loc_send[mpi_i]][0];
           }
           MPI_Bcast(counts,count, MPI_INT, root, MPI_COMM_WORLD);

           anz =0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
               anz += counts[mpi_i];
           }
           if ( anz > 0){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              if (myid ==root ){
                 l=0;
                 for(mpi_i =0; mpi_i < anz; mpi_i++)
                    for(i=2; i < ind_dom[loc_send[mpi_i]][0]+2; i++){
                       trade_loc[l] = ind_dom[loc_send[mpi_i]][i];
                       l++;
                    }
              }
              MPI_Bcast(trade_loc,anz, MPI_INT, root, MPI_COMM_WORLD);
              if(myid != root){
                 // combine each index domain ...
                 l = 0;
                 for(mpi_i=0; mpi_i < count; mpi_i++){
                    combine_index_domain_received_data(loc_send[mpi_i], counts[mpi_i], ind_dom, &trade_loc[l] );
                    l += counts[mpi_i];
                 }
              }
              free(trade_loc);
           }
           free(counts);
#endif
#if defined(_NONLIND_)
           counts = ( int*) malloc( s_r_indep*sizeof(int) );
           if (myid ==root){
              for(mpi_i =0; mpi_i < s_r_indep; mpi_i++)
                 counts[mpi_i] = nonl_dom[mpi_i][0];
           }
           MPI_Bcast(counts,s_r_indep, MPI_INT, root, MPI_COMM_WORLD);

           anz =0;
           for (mpi_i=0; mpi_i< s_r_indep; mpi_i++){
               anz +=  (int) counts[mpi_i];
           }
           if (anz > 0) {
              trade_loc = (int*) calloc( anz,sizeof(int) );
              if (myid == root){
                 l=0;
                 for(mpi_i=0; mpi_i < s_r_indep ; mpi_i++)
                    for(i=2; i < nonl_dom[mpi_i][0]+2 ; i++){
                        trade_loc[l] = nonl_dom[mpi_i][i];
                        l++;
                    }
              }
              MPI_Bcast(trade_loc,anz, MPI_INT, root, MPI_COMM_WORLD);
              if( myid != root){
                 // combine each index domain ...
                 l = 0;
                 for (mpi_i=0; mpi_i < s_r_indep; mpi_i++){
                     // nonl_dom settings
                     extend_nonlinearity_domain_combine_received_trade(mpi_i, counts[mpi_i], nonl_dom, &trade_loc[l]);
                     l += counts[mpi_i];
                 }
              }
              free(trade_loc);
           }
           free(counts);
#endif    // end _NONLIND_
#endif
           free(loc_send);
           break;
      case gather:
           count = get_locint_f(); // count
           loc_send = (locint*) malloc(count*sizeof(locint));
           for(mpi_i=0; mpi_i < count ; mpi_i++)
               loc_send[mpi_i] = get_locint_f(); // Send Location
           count = get_locint_f(); // count
           root = get_locint_f(); // root
           myid = get_locint_f(); // process id
           count2 = get_locint_f(); // count*process_count
           if(myid==root){
             loc_recv = (locint*) malloc(count2*sizeof(locint));
             for(mpi_i=0; mpi_i < count2 ; mpi_i++)
                loc_recv[mpi_i] = get_locint_f(); // Receive Location
           }
           arg = get_locint_f(); // count*process_count
           arg = get_locint_f(); // root
           arg = get_locint_f(); // myid
           mpi_op = get_locint_f();

#if defined(_ZOS_)
           // receiving values for dp_T0
           trade =  myalloc1( count );
           if (myid == root)
              rec_buf = myalloc1(count2);
           else
              rec_buf =NULL;
           for(mpi_i =0; mpi_i < count; mpi_i++)
              trade[mpi_i] = dp_T0[loc_send[mpi_i]];

           MPI_Gather(trade,count, MPI_DOUBLE,rec_buf, count,MPI_DOUBLE, root, MPI_COMM_WORLD);
           if (myid == root){
              for( mpi_i =0; mpi_i < count2; mpi_i++){
                 IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
                 dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_i];
              }
              free(rec_buf);
           }
           free(trade);
#endif /* END ZOS */
#if defined(_FOS_)
           trade = myalloc1( count*2 );
           if (myid ==root)
               rec_buf = myalloc1(count2*2);
           else
               rec_buf = NULL;
           for(mpi_i =0; mpi_i < count; mpi_i++) {
              trade[2*mpi_i] = dp_T0[loc_send[mpi_i]];
              trade[2*mpi_i+1] = dp_T[loc_send[mpi_i]];
           }
           MPI_Gather(trade,count*2, MPI_DOUBLE,rec_buf, count*2 ,MPI_DOUBLE, root, MPI_COMM_WORLD);
           if ( myid == root){
              for( mpi_i =0; mpi_i < count2; mpi_i++){
                 IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
                 dp_T0[loc_recv[mpi_i]] = rec_buf[2*mpi_i];
                 dp_T[loc_recv[mpi_i]] = rec_buf[2*mpi_i+1];
               }
               free(rec_buf);
           }
           free(trade);
#endif
#if defined(_FOV_)
           trade = myalloc1( count*(p+1));
           if (myid == root)
              rec_buf = myalloc1(count2*(p+1));
           else
              rec_buf=NULL;
           mpi_ii=0;
           for(mpi_i =0; mpi_i < count; mpi_i++){
              trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
              mpi_ii++;
              for(i=0; i<p; i++,mpi_ii++)
                 trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
           }
           MPI_Gather(trade,count*(p+1), MPI_DOUBLE,rec_buf, count*(p+1),MPI_DOUBLE, root, MPI_COMM_WORLD);
           if ( myid == root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count2; mpi_i++){
                 IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
                 dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_ii];
                 mpi_ii++;
                 for(i=0; i<p; i++,mpi_ii++)
                    dpp_T[loc_recv[mpi_i]][i] = rec_buf[mpi_ii];
              }
              free(rec_buf);
           }
           free(trade);
#endif
#if defined(_HOS_)
           trade = myalloc1( count*(k+1));
           if (myid == root)
              rec_buf = myalloc1(count2*(k+1));
           else
              rec_buf=NULL;
           mpi_ii=0;
           for(mpi_i =0; mpi_i < count; mpi_i++){
              trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
              mpi_ii++;
              for(i=0; i<k; i++,mpi_ii++)
                 trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
           }
           MPI_Gather(trade,count*(k+1), MPI_DOUBLE,rec_buf, count*(k+1),MPI_DOUBLE, root, MPI_COMM_WORLD);
           if ( myid == root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count2; mpi_i++){
                 IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
                 dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_ii];
                 mpi_ii++;
                 for(i=0; i<k; i++,mpi_ii++)
                    dpp_T[loc_recv[mpi_i]][i] = rec_buf[mpi_ii];
              }
              free(rec_buf);
           }
           free(trade);
#endif
#if defined(_HOV_)
           trade = myalloc1( count*(p*k+1));
           if (myid == root)
              rec_buf = myalloc1(count2*(p*k+1));
           else
              rec_buf=NULL;
           mpi_ii=0;
           for(mpi_i =0; mpi_i < count; mpi_i++){
              trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
              mpi_ii++;
              for(i=0; i<p*k; i++,mpi_ii++)
                 trade[mpi_ii] = dpp_T[loc_send[mpi_i]][i];
           }
           MPI_Gather(trade,count*(p*k+1), MPI_DOUBLE,rec_buf, count*(p*k+1),MPI_DOUBLE, root, MPI_COMM_WORLD);
           if ( myid == root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count2; mpi_i++){
                 IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
                 dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_ii];
                 mpi_ii++;
                 for(i=0; i<p*k; i++,mpi_ii++)
                    dpp_T[loc_recv[mpi_i]][i] = rec_buf[mpi_ii];
              }
              free(rec_buf);
           }
           free(trade);
#endif
#if defined(_TIGHT_)
#if defined(_INT_FOR_)
           trade = myalloc1(count*(p+1));
           if (myid == root)
             rec_buf = myalloc1(count2*(p+1));
           else
              rec_buf =NULL;
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
               trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
               mpi_ii++;
               for(l=0;l<p;l++,mpi_ii++)
                   trade[mpi_ii]= (double) up_T[loc_send[mpi_i]][l];
           }
           MPI_Gather(trade,count*(p+1), MPI_DOUBLE,rec_buf, count*(p+1),MPI_DOUBLE, root, MPI_COMM_WORLD);
           if (myid == root){
              mpi_ii=0;
              for( mpi_i =0; mpi_i < count; mpi_i++){
                 IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
                 dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_ii];
                 mpi_ii++;
                 for(l=0;l<p;l++,mpi_ii++)
                  up_T[loc_recv[mpi_i]][l] = (unsigned long int) rec_buf[mpi_ii];
              }
              free(rec_buf_loc);
           }
           free(trade_loc);
#endif /* END INT_FOR */
#if defined(_INDO_)
           counts = ( int*) malloc( count*sizeof(int) );
           trade = myalloc1(count*2);
           if( myid == root){
              tmp_counts = ( int*) malloc( count2*sizeof(int) );
              rec_buf = myalloc1(count2*2);
              }
           else {
              tmp_counts = NULL;
              rec_buf = NULL;
           }

           for(mpi_i =0; mpi_i < count; mpi_i++){
                trade[2*mpi_i] = dp_T0[loc_send[mpi_i]];
                counts[mpi_i] = ind_dom[loc_send[mpi_i]][0];
                trade[2*mpi_i+1] = (double) counts[mpi_i];
                }

           MPI_Gather(trade,count*2, MPI_DOUBLE, rec_buf, count*2, MPI_DOUBLE, root, MPI_COMM_WORLD);
           if (myid == root){
              for(mpi_i =0; mpi_i < count2; mpi_i++ ){
                 IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
                 dp_T0[loc_recv[mpi_i]] = rec_buf[2*mpi_i];
                 tmp_counts[mpi_i]  = (int) rec_buf[2*mpi_i+1];
              }
              for(mpi_i =0; mpi_i < count; mpi_i++ ){
                 for(i=1; i < process_count; i++ )
                   if( counts[mpi_i] < tmp_counts[count*i + mpi_i])
                         counts[mpi_i] = tmp_counts[count*i + mpi_i];
              }
              free(rec_buf);
           }
           free(trade);
           MPI_Bcast(counts,count,MPI_INT, root, MPI_COMM_WORLD);
           anz=0;
           for(mpi_i =0; mpi_i < count; mpi_i++ )
                anz += counts[mpi_i];

           // every process has same counts
           if ( anz > 0){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              l=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 for (i=2; i < ind_dom[loc_send[mpi_i]][0]+2; i++){
                    trade_loc[l] = ind_dom[loc_send[mpi_i]][i];
                    l++;
                 }
                 for(i=ind_dom[loc_send[mpi_i]][0]; i < counts[mpi_i] ; i++  ){
                    trade_loc[l] = -10;
                    l++;
                 }
              }
              if (myid == root)
                 rec_buf_loc = (int*) malloc(process_count * anz * sizeof(int) );
              else
                 rec_buf_loc = NULL ;

              MPI_Gather(trade_loc, anz, MPI_INT, rec_buf_loc, anz, MPI_INT, root, MPI_COMM_WORLD);
              free( trade_loc );

              if(myid == root){
                l = 0;
                for(i=0;i<process_count; i++) {
                   for(mpi_i=0; mpi_i < count; mpi_i++){
                      combine_index_domain_received_data(loc_recv[mpi_i], tmp_counts[i*count+mpi_i], ind_dom, &rec_buf_loc[l] );
                      l += counts[mpi_i];
                   }
                }
              free(rec_buf_loc);
              free(tmp_counts);
              }
           }
           free(counts);
#endif
#if defined(_NONLIND_)
           counts = ( int*) malloc( count*sizeof(int) );
           trade = myalloc1(count*2);
           if( myid == root){
              tmp_counts = ( int*) malloc( count2*sizeof(int) );
              rec_buf = myalloc1(count2*2);
              }
           else {
              tmp_counts = NULL;
              rec_buf = NULL;
           }

           for(mpi_i =0; mpi_i < count; mpi_i++){
                trade[2*mpi_i] = dp_T0[loc_send[mpi_i]];
                counts[mpi_i] = nonl_dom[mpi_i][0];
                trade[2*mpi_i+1] = (double) counts[mpi_i];
                }

           MPI_Gather(trade,count*2, MPI_DOUBLE, rec_buf, count*2, MPI_DOUBLE, root, MPI_COMM_WORLD);
           if (myid == root){
              for(mpi_i =0; mpi_i < count2; mpi_i++ ){
                 IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
                 dp_T0[loc_recv[mpi_i]] = trade[2*mpi_i];
                 tmp_counts[mpi_i]  = (int) trade[2*mpi_i+1];
              }
              for(mpi_i =0; mpi_i < count; mpi_i++ ){
                 for(i=1; i < process_count; i++ )
                   if( counts[mpi_i] < tmp_counts[count*i + mpi_i])
                         counts[mpi_i] = tmp_counts[count*i + mpi_i];
              }
              free(rec_buf);
           }
           free(trade);
           MPI_Bcast(counts,count,MPI_INT, root, MPI_COMM_WORLD);
           anz=0;
           for(mpi_i =0; mpi_i < count; mpi_i++ )
                anz += counts[mpi_i];

           // every process has same counts
           if ( anz > 0){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              if (myid == root){
                 rec_buf_loc = (int*) malloc(process_count * anz * sizeof(int));
              } else { rec_buf_loc =NULL; }

              l=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 for (i=2; i < nonl_dom[mpi_i][0]+2; i++){
                    trade_loc[l] = nonl_dom[mpi_i][i];
                    l++;
                 }
                 for(i=nonl_dom[mpi_i][0]; i < counts[0] ; i++  ){
                    trade_loc[l] = -10;
                    l++;
                 }
              }
              MPI_Gather(trade_loc,anz, MPI_INT, rec_buf_loc, anz, MPI_INT, root, MPI_COMM_WORLD);
              free( trade_loc );
              if(myid == root){
                 // rewrite each index domain  rec_buf_loc[pc*process_count*anz + count]
                 l = 0;
                 for(mpi_i=0; mpi_i < count2; mpi_i++){
                    i = 0;
                    free(nonl_dom[mpi_i]);
                    nonl_dom[mpi_i] = (locint*) calloc(2*tmp_counts[mpi_i]+2,sizeof(locint));
                    nonl_dom[mpi_i][1] = 2*tmp_counts[mpi_i];
                    while ((rec_buf_loc[l+i] > -1 ) && ( i < tmp_counts[mpi_i]) ) {
                       nonl_dom[mpi_i][i+2]= rec_buf_loc[l+i];
                       i++;
                    }
                    nonl_dom[mpi_i][0]= i;
                    l += counts[mpi_i];
                 }
              }
              free(rec_buf_loc);
           }
           if( myid == root) free(tmp_counts);
           free(counts);
#endif    // end _NONLIND_
#endif
#if defined(_NTIGHT_)
#if defined(_INT_FOR_)
           trade_loc = (locint*) malloc(count*p*sizeof(locint));
           if (myid == root)
             rec_buf_loc = (locint*) malloc(count2*p*sizeof(locint));
           else
              rec_buf =NULL;
           mpi_ii=0;
           for(mpi_i=0; mpi_i< count; mpi_i++) {
              for(l=0;l<p;l++,mpi_ii++)
                 trade[mpi_ii]=up_T[loc_send[mpi_i]][l];
           }
           MPI_Gather(trade,count*p, MPI_UNSIGNED_LONG,rec_buf, count*p,MPI_UNSIGNED_LONG, root, MPI_COMM_WORLD);
           if (myid == root){
              for( mpi_i =0; mpi_i < count; mpi_i++){
                 FOR_0_LE_l_LT_pk
                  up_T[loc_recv[mpi_i]][l] = rec_buf_loc[mpi_i*p+l];
              }
              free(rec_buf_loc);
           }
           free(trade_loc);
#endif /* END INT_FOR */
#if defined(_INDO_)
           // getting information about count of entries
           counts = ( int*) malloc( count*sizeof(int) );
           if( myid == root)
              tmp_counts = ( int*) malloc( count2*sizeof(int) );
           else
              tmp_counts = NULL;

           for(mpi_i =0; mpi_i < count; mpi_i++)
                counts[mpi_i] = ind_dom[loc_send[mpi_i]][0];

           MPI_Gather(counts,count, MPI_INT, tmp_counts, count, MPI_INT, root, MPI_COMM_WORLD);
           if (myid == root){
              for(mpi_i =0; mpi_i < count; mpi_i++ ){
                 for(i=1; i < process_count; i++ )
                   if( counts[mpi_i] < tmp_counts[count*i + mpi_i])
                         counts[mpi_i] = tmp_counts[count*i + mpi_i];
              }
           }
           MPI_Bcast(counts,count,MPI_INT, root, MPI_COMM_WORLD);
           anz=0;
           for(mpi_i =0; mpi_i < count; mpi_i++ )
                anz += counts[mpi_i];

           // every process has same counts
           if ( anz > 0){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              l=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 for (i=2; i < ind_dom[loc_send[mpi_i]][0]+2; i++){
                    trade_loc[l] = ind_dom[loc_send[mpi_i]][i];
                    l++;
                 }
                 for(i=ind_dom[loc_send[mpi_i]][0]; i < counts[mpi_i] ; i++  ){
                    trade_loc[l] = -10;
                    l++;
                 }
              }
              if (myid == root) rec_buf_loc = (int*) malloc(process_count * anz * sizeof(int) );
              else  rec_buf_loc = NULL ;

              MPI_Gather(trade_loc, anz, MPI_INT, rec_buf_loc, anz, MPI_INT, root, MPI_COMM_WORLD);
              free( trade_loc );

              if(myid == root){
                l = 0;
                for(i=0;i<process_count; i++) {
                   for(mpi_i=0; mpi_i < count; mpi_i++){
                      combine_index_domain_received_data(loc_recv[mpi_i], tmp_counts[i*count+mpi_i], ind_dom, &rec_buf_loc[l] );
                      l += counts[mpi_i];
                   }
                }
              free(rec_buf_loc);
              free(tmp_counts);
              }
           }
           free(counts);
#endif
#if defined(_NONLIND_)
           // getting information about count of entries
           counts = ( int*) malloc( count*sizeof(int) );
           if( myid == root)
              tmp_counts = ( int*) malloc( count2*sizeof(int) );
           else
              tmp_counts = NULL;

           for(mpi_i =0; mpi_i < count; mpi_i++)
                counts[mpi_i] = nonl_dom[mpi_i][0];

           MPI_Gather(counts,count, MPI_INT, tmp_counts, count, MPI_INT, root, MPI_COMM_WORLD);
           if (myid == root){
              for(mpi_i =0; mpi_i < count; mpi_i++ ){
                 for(i=1; i < process_count; i++ )
                   if( counts[mpi_i] < tmp_counts[count*i + mpi_i])
                         counts[mpi_i] = tmp_counts[count*i + mpi_i];
              }
           }
           MPI_Bcast(counts,count,MPI_INT, root, MPI_COMM_WORLD);
           anz=0;
           for(mpi_i =0; mpi_i < count; mpi_i++ )
                anz += counts[mpi_i];

           // every process has same counts
           if ( anz > 0){
              trade_loc = (int*) malloc( anz*sizeof(int) );
              if (myid == root){
                 rec_buf_loc = (int*) malloc(process_count * anz * sizeof(int));
              } else { rec_buf_loc =NULL; }

              l=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 for (i=2; i < nonl_dom[mpi_i][0]+2; i++){
                    trade_loc[l] = nonl_dom[mpi_i][i];
                    l++;
                 }
                 for(i=nonl_dom[mpi_i][0]; i < counts[0] ; i++  ){
                    trade_loc[l] = -10;
                    l++;
                 }
              }
              MPI_Gather(trade_loc,anz, MPI_INT, rec_buf_loc, anz, MPI_INT, root, MPI_COMM_WORLD);
              free( trade_loc );
              if(myid == root){
                 // rewrite each index domain  rec_buf_loc[pc*process_count*anz + count]
                 l = 0;
                 for(mpi_i=0; mpi_i < count2; mpi_i++){
                    i = 0;
                    free(nonl_dom[mpi_i]);
                    nonl_dom[mpi_i] = (locint*) calloc(2*tmp_counts[mpi_i]+2,sizeof(locint));
                    nonl_dom[mpi_i][1] = 2*tmp_counts[mpi_i];
                    while ((rec_buf_loc[l+i] > -1 ) && ( i < tmp_counts[mpi_i]) ) {
                       nonl_dom[mpi_i][i+2]= rec_buf_loc[l+i];
                       i++;
                    }
                    nonl_dom[mpi_i][0]= i;
                    l += counts[mpi_i];
                 }
                 free(rec_buf_loc);
              }
           }
           if( myid == root) free(tmp_counts);
           free(counts);
#endif    // end _NONLIND_
#endif /* END _NTIGHT_ */
           if ( myid == root)
              free(loc_recv);
           free(loc_send);
           break;
      case scatter:
           count = get_locint_f(); // count*procsize
           root = get_locint_f();
           myid = get_locint_f();
           if(myid == root){
             loc_send = (locint*) malloc(count*sizeof(locint));
             for(mpi_i=0; mpi_i < count ; mpi_i++)
               loc_send[mpi_i] = get_locint_f(); // Send Location
           }
           res = get_locint_f(); // count*procsize
           res = get_locint_f(); // root
           res = get_locint_f(); // process id
           count2 = get_locint_f(); // count or recv_count
           loc_recv = (locint*) malloc(count2*sizeof(locint));
           for(mpi_i=0;mpi_i< count2; mpi_i++)
             loc_recv[mpi_i] = get_locint_f(); // Receive Location
           arg = get_locint_f(); // count
#if defined(_ZOS_)
           // receiving values for dp_T0
           if (myid == root)
               trade = myalloc1( count );
           else
              trade = NULL;

           rec_buf = myalloc1(count2);

           if(myid == root)
             for(mpi_i =0; mpi_i < count; mpi_i++)
                trade[mpi_i] = dp_T0[loc_send[mpi_i]];

           MPI_Scatter(trade,count2, MPI_DOUBLE,rec_buf, count2 ,MPI_DOUBLE, root, MPI_COMM_WORLD);

           for( mpi_i =0; mpi_i < count2; mpi_i++){
               IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
               dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_i];
           }
           free(rec_buf);
           if (myid==root)
              free(trade);
#endif /* END _ZOS_ */
#if defined(_FOS_)
           rec_buf = myalloc1( count2*2 );
           if (myid ==root)
               trade = myalloc1(count*2);
           else
               trade = NULL;

           if ( myid == root){
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[2*mpi_i] = dp_T0[loc_send[mpi_i]];
                 trade[2*mpi_i+1] = dp_T[loc_send[mpi_i]];
              }
           }
           MPI_Scatter(trade,count2*2, MPI_DOUBLE,rec_buf, count2*2, MPI_DOUBLE, root, MPI_COMM_WORLD);

           for( mpi_i =0; mpi_i < count2; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = rec_buf[2*mpi_i];
              dp_T[loc_recv[mpi_i]] = rec_buf[2*mpi_i+1];
           }
           free(rec_buf);
           if (myid==root)
              free(trade);
#endif
#if defined(_FOV_)
           rec_buf = myalloc1( count2*(p+1));
           if (myid ==root)
               trade = myalloc1(count*(p+1));
           else
               trade = NULL;

           if ( myid == root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                 mpi_ii++;
                 for(l=0;l<p;l++,mpi_ii++)
                    trade[mpi_ii] = dpp_T[loc_send[mpi_i]][l];
              }
           }
           MPI_Scatter(trade,count2*(p+1), MPI_DOUBLE,rec_buf, count2*(p+1), MPI_DOUBLE, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for( mpi_i =0; mpi_i < count2; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_ii];
              mpi_ii++;
              for(l=0;l<p;l++,mpi_ii++)
                 dpp_T[loc_recv[mpi_i]][l] = rec_buf[mpi_ii];
           }
           free(rec_buf);
           if (myid==root)
              free(trade);
#endif
#if defined(_HOS_)
           rec_buf = myalloc1( count2*(k+1));
           if (myid ==root)
               trade = myalloc1(count*(k+1));
           else
               trade = NULL;

           if ( myid == root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                 mpi_ii++;
                 for(l=0;l<k;l++,mpi_ii++)
                    trade[mpi_ii] = dpp_T[loc_send[mpi_i]][l];
              }
           }
           MPI_Scatter(trade,count2*(k+1), MPI_DOUBLE,rec_buf, count2*(k+1), MPI_DOUBLE, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for( mpi_i =0; mpi_i < count2; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_ii];
              mpi_ii++;
              for(l=0;l<k;l++,mpi_ii++)
                 dpp_T[loc_recv[mpi_i]][l] = rec_buf[mpi_ii];
           }
           free(rec_buf);
           if (myid==root)
              free(trade);
#endif
#if defined(_HOV_)
           rec_buf = myalloc1( count2*(p*k+1));
           if (myid ==root)
               trade = myalloc1(count*(p*k+1));
           else
               trade = NULL;

           if ( myid == root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                 mpi_ii++;
                 for(l=0;l<p*k;l++,mpi_ii++)
                    trade[mpi_ii] = dpp_T[loc_send[mpi_i]][l];
              }
           }
           MPI_Scatter(trade,count2*(p*k+1), MPI_DOUBLE,rec_buf, count2*(p*k+1), MPI_DOUBLE, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for( mpi_i =0; mpi_i < count2; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_ii];
              mpi_ii++;
              for(l=0;l<p*k;l++,mpi_ii++)
                 dpp_T[loc_recv[mpi_i]][l] = rec_buf[mpi_ii];
           }
           free(rec_buf);
           if (myid==root)
              free(trade);
#endif
#if defined(_TIGHT_)
#if defined(_INT_FOR_)
           rec_buf = myalloc1( count2*(p+1));
           if (myid ==root)
               trade = myalloc1(count*(p+1));
           else
               trade = NULL;

           if ( myid == root){
              mpi_ii=0;
              for(mpi_i =0; mpi_i < count; mpi_i++){
                 trade[mpi_ii] = dp_T0[loc_send[mpi_i]];
                 mpi_ii++;
                 for(l=0;l<p;l++,mpi_ii++)
                    trade[mpi_ii] = (double) up_T[loc_send[mpi_i]][l];
              }
           }
           MPI_Scatter(trade,count2*(p+1), MPI_DOUBLE,rec_buf, count2*(p+1), MPI_DOUBLE, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for( mpi_i =0; mpi_i < count2; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_ii];
              mpi_ii++;
              for(l=0;l<p;l++,mpi_ii++)
                 up_T[loc_recv[mpi_i]][l] = (unsigned long int) rec_buf[mpi_ii];
           }
           free(rec_buf);
           if (myid==root)
              free(trade);
#endif /* END INT_FOR */
#if defined(_INDO_)
           rec_buf = myalloc1(count2+1);
           if (myid == root)
              trade = myalloc1(count+process_count);
           else
              trade = NULL;
           if(myid== root){
              anz = ind_dom[loc_send[0]][0];
              for(mpi_i =1; mpi_i < count; mpi_i++){
                 if(anz < ind_dom[loc_send[mpi_i]][0])
                     anz = ind_dom[loc_send[mpi_i]][0];
              }
              i=0;
              l=0;
              for(mpi_ii=0; mpi_ii<process_count; mpi_ii++){
                 for(mpi_i=0; mpi_i < count2; mpi_i++,l++,i++)
                    trade[l] = dp_T0[loc_send[i]];
                 trade[l] = (double) anz;
                 l++;
              }
           }
           MPI_Scatter(trade,count2+1, MPI_DOUBLE, rec_buf, count2 +1, MPI_DOUBLE, root, MPI_COMM_WORLD);
           if (myid == root)
              free(trade);
           for(mpi_i=0; mpi_i < count2; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_i];
           }
           anz = (int) rec_buf[count2];
           free(rec_buf);
           l=0;
           if(myid == root){
              trade_loc = (int*) calloc(count*anz,sizeof(int));
              for(mpi_i =0; mpi_i < count; mpi_i++ ){
                 for (i=2; i < ind_dom[loc_send[mpi_i]][0]+2; i++){
                    trade_loc[l] = ind_dom[loc_send[mpi_i]][i];
                    l++;
                    }
                 for(i=ind_dom[loc_send[mpi_i]][0]; i < anz ; i++  ){
                    trade_loc[l] = -10;
                    l++;
                 }
              }
           }
           rec_buf_loc = ( int*) malloc(anz*count2*sizeof(int) );
           MPI_Scatter(trade_loc,anz*count2, MPI_INT, rec_buf_loc, anz*count2, MPI_INT, root, MPI_COMM_WORLD);

           if(myid == root) free( trade_loc );
           l = 0;
           for(mpi_i=0; mpi_i < count2; mpi_i++){
               i = 0;
               free(ind_dom[loc_recv[mpi_i]]);
               ind_dom[loc_recv[mpi_i]] = (locint*) calloc(2*anz+2,sizeof(locint));
               ind_dom[loc_recv[mpi_i]][1] = 2*anz;

               while ((rec_buf_loc[l+i] > -1 ) && ( i < anz) ) {
                       ind_dom[loc_recv[mpi_i]][i+2]= rec_buf_loc[l+i];
                       i++;
               }
               ind_dom[loc_recv[mpi_i]][0]= i;
               l += anz;
           }

           free(rec_buf_loc);
#endif
#if defined(_NONLIND_)
           rec_buf = myalloc1(count2+1);
           if (myid == root)
              trade = myalloc1(count+process_count);
           else
              trade = NULL;
           if(myid== root){
              anz = nonl_dom[0][0];
              for(mpi_i =1; mpi_i < count; mpi_i++){
                 if(anz < nonl_dom[mpi_i][0])
                     anz = nonl_dom[mpi_i][0];
              }
              i=0;
              l=0;
              for(mpi_ii=0; mpi_ii<process_count; mpi_ii++){
                 for(mpi_i=0; mpi_i < count2; mpi_i++,l++,i++)
                    trade[l] = dp_T0[loc_send[i]];
                 trade[l] = (double) anz;
                 l++;
              }
           }
           MPI_Scatter(trade,count2+1, MPI_DOUBLE, rec_buf, count2 +1, MPI_DOUBLE, root, MPI_COMM_WORLD);
           if (myid == root)
              free(trade);
           for(mpi_i=0; mpi_i < count2; mpi_i++){
              IF_KEEP_WRITE_TAYLOR(loc_recv[mpi_i],keep,k,p)
              dp_T0[loc_recv[mpi_i]] = rec_buf[mpi_i];
           }
           anz = (int) rec_buf[count2];
           free(rec_buf);
           l = 0;
           for(mpi_i=0; mpi_i < count2; mpi_i++){
               i = 0;
               free(nonl_dom[mpi_i]);
               nonl_dom[mpi_i] = (locint*) calloc(2*anz+2,sizeof(locint));
               nonl_dom[mpi_i][1] = 2*anz;

               while ((rec_buf_loc[l+i] > -1 ) && ( i < anz) ) {
                       nonl_dom[mpi_i][i+2]= rec_buf_loc[l+i];
                       i++;
               }
               nonl_dom[mpi_i][0]= i;
               l += anz;
           }
           free(rec_buf_loc);
#endif    // end _NONLIND_
#endif
#if defined(_NTIGHT_)
#if defined(_INT_FOR_)
           if (myid == root)
             trade_loc = (locint*) malloc(count*p*sizeof(locint));
           else
             trade_loc =NULL;
           rec_buf_loc = (locint*) malloc(count2*p*sizeof(locint));
           mpi_ii=0;
           for (mpi_i=0; mpi_i< count; mpi_i++) {
               for(l=0;l<p;l++,mpi_ii++)
                  trade_loc[mpi_ii]=up_T[loc_send[mpi_i]][l];
           }
           MPI_Scatter(trade_loc,count2*p, MPI_INT,rec_buf_loc, count2*p ,MPI_INT, root, MPI_COMM_WORLD);
           mpi_ii=0;
           for( mpi_i =0; mpi_i < count; mpi_i++){
              for(l=0;l<p;l++,mpi_ii++)
                up_T[loc_recv[mpi_i]][l] = rec_buf_loc[mpi_ii];
           }
           free(rec_buf_loc);
           if(myid==root) free(trade_loc);
#endif /* END INT_FOR */
#if defined(_INDO_)
           // getting information about count of entries
           if(myid== root){
              anz = ind_dom[loc_send[0]][0];
              for(mpi_i =1; mpi_i < count; mpi_i++)
                 if(anz < ind_dom[loc_send[mpi_i]][0])
                     anz = ind_dom[loc_send[mpi_i]][0];
           }
           MPI_Bcast(&anz,1,MPI_INT, root, MPI_COMM_WORLD);
           l=0;
           if(myid == root){
              trade_loc = (int*) calloc(count*anz,sizeof(int));
              for(mpi_i =0; mpi_i < count; mpi_i++ )
                 for (i=2; i < ind_dom[loc_send[mpi_i]][0]+2; i++){
                    trade_loc[l] = ind_dom[loc_send[mpi_i]][i];
                    l++;
                    }
              for(i=ind_dom[loc_send[mpi_i]][0]; i < anz ; i++  ){
                    trade_loc[l] = -10;
                    l++;
                 }
           }
           rec_buf_loc = ( int*) malloc(anz*count2*sizeof(int) );
           MPI_Scatter(trade_loc,anz*count2, MPI_INT, rec_buf_loc, anz*count2, MPI_INT, root, MPI_COMM_WORLD);

           if(myid == root) free( trade_loc );
           l = 0;
           for(mpi_i=0; mpi_i < count2; mpi_i++){
               i = 0;
               free(ind_dom[loc_recv[mpi_i]]);
               ind_dom[loc_recv[mpi_i]] = (locint*) calloc(2*anz+2,sizeof(locint));
               ind_dom[loc_recv[mpi_i]][1] = 2*anz;

               while ((rec_buf_loc[l+i] > -1 ) && ( i < anz) ) {
                       ind_dom[loc_recv[mpi_i]][i+2]= rec_buf_loc[l+i];
                       i++;
               }
               ind_dom[loc_recv[mpi_i]][0]= i;
               l += anz;
           }

           free(rec_buf_loc);
           free(counts);
#endif
#if defined(_NONLIND_)
           // getting information about count of entries
           counts = ( int*) malloc( sizeof(int) );
           if(myid== root){
              counts[0] = nonl_dom[0][0];
              for(mpi_i =1; mpi_i < count; mpi_i++)
                 if(counts[0] < nonl_dom[mpi_i][0])
                     counts[0] = nonl_dom[mpi_i][0];
           }
           MPI_Bcast(counts,1,MPI_INT, root, MPI_COMM_WORLD);
           l=0;
           if(myid == root){
              trade_loc = (int*) calloc(count*counts[0],sizeof(int));
              for(mpi_i =0; mpi_i < count; mpi_i++ )
                 for (i=2; i < nonl_dom[mpi_i][0]+2; i++){
                    trade_loc[l] = nonl_dom[mpi_i][i];
                    l++;
                    }
              for(i=nonl_dom[mpi_i][0]; i < counts[0] ; i++  ){
                    trade_loc[l] = -10;
                    l++;
                 }
           }
           rec_buf_loc = ( int*) malloc(counts[0]*count2*sizeof(int) );
           MPI_Scatter(trade_loc,counts[0]*count2, MPI_INT, rec_buf_loc, counts[0]*count2, MPI_INT, root, MPI_COMM_WORLD);

           if(myid == root) free( trade_loc );
           l = 0;
           for(mpi_i=0; mpi_i < count2; mpi_i++){
               i = 0;
               free(nonl_dom[mpi_i]);
               nonl_dom[mpi_i] = (locint*) calloc(2*tmp_counts[0]+2,sizeof(locint));
               nonl_dom[mpi_i][1] = 2*counts[0];

               while ((rec_buf_loc[l+i] > -1 ) && ( i < counts[0]) ) {
                       nonl_dom[mpi_i][i+2]= rec_buf_loc[l+i];
                       i++;
               }
               nonl_dom[mpi_i][0]= i;
               l += counts[0];
           }

           free(rec_buf_loc);
           free(counts);
#endif    // end _NONLIND_
#endif
           if (myid == root)
              free(loc_send);
           free(loc_recv);
           break;
#endif
                /*--------------------------------------------------------------------------*/

            default:                                                   /* default */
                /* Die here, we screwed up */

                fprintf(DIAG_OUT,"ADOL-C fatal error in " GENERATED_FILENAME " ("
                        __FILE__
                        ") : no such operation %d\n", operation);
                exit(-1);
                break;

        } /* endswitch */

        /* Read the next operation */
        operation=get_op_f();
#if defined(ADOLC_DEBUG)
        ++countPerOperation[operation];
#endif /* ADOLC_DEBUG */
    }  /* endwhile */

#if defined(ADOLC_DEBUG)
    printf("\nTape contains:\n");
    for (v = 0; v < 256; ++v)
        if (countPerOperation[v] > 0)
            printf("operation %3d: %6d time(s) - %6d taylors written (%10.2f per operation)\n", v, countPerOperation[v], taylorPerOperation[v], (double)taylorPerOperation[v] / (double)countPerOperation[v]);
    printf("\n");
#endif /* ADOLC_DEBUG */

#if defined(_KEEP_)
    if (keep) taylor_close(taylbuf);
#endif

    /* clean up */
#if !defined (_NTIGHT_)
    free(dp_T0);
#endif /* !_NTIGHT_ */
#if !defined(_INDO_)
#if !defined(_ZOS_)
#   if defined(_FOS_)
    free(dp_T);
#   else
#if !defined (_INT_FOR_)
    myfree2(dpp_T);
    free(dp_Ttemp);
#endif /* !_NTIGHT_ */
#endif
#endif
#endif
#if defined(_HIGHER_ORDER_)
    free(dp_z);
#endif

    end_sweep();


#if defined(_INDO_)

    for(i=0;i<max_ind_dom;i++)
      {
	free(ind_dom[i]);
      }
    free(ind_dom);

#if defined(_NONLIND_)
#if defined(_MPI_)
    if (mpi_initialized){
       indcheck = s_r_indep;
       if (mpi_id == 0 ){
          for ( i=0;i<indcheck;i++) {
              crs[i] = (unsigned int*) malloc( sizeof(unsigned int)*(nonl_dom[i][0]+1));
              crs[i][0] = nonl_dom[i][0];
              for (l=1;l<=crs[i][0];l++) {
                  crs[i][l] = nonl_dom[i][l+1];
              }
              free( nonl_dom[i]);
          }
          free(nonl_dom);
       }
   } else {
       for ( i=0;i<indcheck;i++) {
             for ( i=0;i<indcheck;i++) {
                 crs[i] = (unsigned int*) malloc(sizeof(unsigned int) * (nonl_dom[i][0]+1));
                 crs[i][0] = nonl_dom[i][0];
                 for (l=1;l<=crs[i][0];l++)
                     crs[i][l] = nonl_dom[i][l+1];
             }
        }
     for ( i=0;i<indcheck;i++)
       free( nonl_dom[i]);
     free(nonl_dom);
    }
#else
    for( i=0; i < indcheck; i++) {
       crs[i] = (unsigned int*) malloc(sizeof(unsigned int) * (nonl_dom[i][0]+1));
       crs[i][0] = nonl_dom[i][0];
       for(l=1; l < crs[i][0]+1; l++)
          crs[i][l] = nonl_dom[i][l+1];
       free(nonl_dom[i]);
    }
    for ( i=0;i<indcheck;i++)
       free( nonl_dom[i]);
    free(nonl_dom);
#endif
#endif
#endif
    return ret_c;
}

/****************************************************************************/

#if defined(_INDOPRO_)

/****************************************************************************/
/* set operations for propagation of index domains                          */

/*--------------------------------------------------------------------------*/
/* operations on index domains                                              */

#if defined(_TIGHT_)
void copy_index_domain(int res, int arg, locint **ind_dom) {

   int i;

   if (ind_dom[arg][0] > ind_dom[res][1]-2)
     {
       free(ind_dom[res]);
       ind_dom[res] = (locint *)  malloc(sizeof(locint) * 2*(ind_dom[arg][0])+1);
       ind_dom[res][1] = 2*ind_dom[arg][0];
     }


    for(i=2;i<ind_dom[arg][0]+2;i++)
       ind_dom[res][i] = ind_dom[arg][i];
    ind_dom[res][0] = ind_dom[arg][0];
}


void merge_2_index_domains(int res, int arg, locint **ind_dom)
{

  int num,num1,num2, i,j,k,l;
  locint *temp_array, *arg_ind_dom, *res_ind_dom;

  if (ind_dom[res][0] == 0)
    copy_index_domain(res,arg,ind_dom);
  else
    {
      if (res != arg)
	{
	  arg_ind_dom = ind_dom[arg];
	  res_ind_dom = ind_dom[res];

	  num  = ind_dom[res][0];
	  num1 = arg_ind_dom[0];
	  num2 = ind_dom[res][1];

	  if (num2 < num1+num)
	    num2 = num1+num;

	  temp_array = (locint *)  malloc(sizeof(locint)* (num2+2));
	  temp_array[1] = num2;

	  i = 2;
	  j = 2;
	  k = 2;
	  num += 2;
	  num1 += 2;
	  while ((i< num) && (j < num1))
	    {
	      if (res_ind_dom[i] < arg_ind_dom[j])
		{
		  temp_array[k] = res_ind_dom[i];
		  i++; k++;
		}
	      else
		{
		  if (res_ind_dom[i] == arg_ind_dom[j])
		    {
		      temp_array[k] = arg_ind_dom[j];
		      i++;j++;k++;
		    }
		  else
		    {
		      temp_array[k] = arg_ind_dom[j];
		      j++;k++;
		    }
		}
	    }
	  for(l = i;l<num;l++)
	    {
	      temp_array[k] = res_ind_dom[l];
	      k++;
	    }
	  for(l = j;l<num1;l++)
	    {
	      temp_array[k] = arg_ind_dom[l];
	      k++;
	    }
	  temp_array[0] = k-2;
	  free(ind_dom[res]);
	  ind_dom[res]=temp_array;
	}
    }


}

void combine_2_index_domains(int res, int arg1, int arg2, locint **ind_dom) {

    if (res != arg1)
       copy_index_domain(res, arg1, ind_dom);

    merge_2_index_domains(res, arg2, ind_dom);
}

void merge_3_index_domains(int res, int arg1, int arg2, locint **ind_dom) {
    merge_2_index_domains(res, arg1, ind_dom);
    merge_2_index_domains(res, arg2, ind_dom);
}


#if defined(_MPI_)
void combine_index_domain_received_data(int res, int count, locint **ind_dom, locint *trade) {

    int num,num1,i,j,k,l;
    locint *temp_array;

    if (ind_dom[res][0] == 0){
          if (count > ind_dom[res][1] )
          {
               free(ind_dom[res]);
               ind_dom[res] = (locint *)  malloc(sizeof(locint) *2*(count+2) );
               ind_dom[res][1] = 2*count;
          }

          for(i=2, j=0;i < count+2;i++,j++)
               ind_dom[res][i] = trade[j];

          ind_dom[res][0] = count;
    }
    else
    {
     num = ind_dom[res][0];
     temp_array = (locint *)  malloc(sizeof(locint)* num);
     num1 = count;

     for(i=0;i<num;i++)
         temp_array[i] = ind_dom[res][i+2];

     if (num1+num > ind_dom[res][1] )
     {
       i = 2*(num1+num);
       free(ind_dom[res]);
       ind_dom[res] = (locint *)  malloc(sizeof(locint) *(i+2));
          ind_dom[res][1] = i;
     }
     i = 0;
     j = 0;
     k = 2;
     while ((i< num) && (j < num1))
         {
           if (temp_array[i] < trade[j])
          {
            ind_dom[res][k] = temp_array[i];
            i++; k++;
          }
           else
           {
            if (temp_array[i] == trade[j])
              {
                ind_dom[res][k] = trade[j];
                i++;j++;k++;
              }
            else
              {
                ind_dom[res][k] = trade[j];
                j++;k++;
              }
          }
         }
       for(l = i;l<num;l++)
       {
           ind_dom[res][k] = temp_array[l];
           k++;
       }
       for(l = j;l<num1;l++)
       {
           ind_dom[res][k] = trade[l];
           k++;
       }
       ind_dom[res][0] = k-2;
       free(temp_array);
    }

}
#endif
#endif
#endif


#if defined(_NONLIND_)
#if defined(_TIGHT_)

void extend_nonlinearity_domain_binary_step
(int arg1, int arg2, locint **ind_dom, locint **nonl_dom)
{
  int index,num,num1, num2, i,j,k,l,m;
  locint *temp_nonl, *index_nonl_dom, *arg1_ind_dom, *arg2_ind_dom;

  num = ind_dom[arg2][0];

  for(m=2;m<ind_dom[arg1][0]+2;m++)
    {
      index = ind_dom[arg1][m];
      index_nonl_dom = nonl_dom[index];

      if (index_nonl_dom[0] == 0)  /* empty list */
	{
	  if ( index_nonl_dom[1] < num)
	    {
	      free(index_nonl_dom);
	      index_nonl_dom = (locint*) malloc(sizeof(locint)*2*(num+1) );
	      index_nonl_dom[1] = 2*num;
	    }
	  for(i=2;i<num+2;i++)      /* append index domain list of "arg" */
	    index_nonl_dom[i] = ind_dom[arg2][i];
	  index_nonl_dom[0] = num;
	}
      else
	{ /* merge lists */
	  num1 = index_nonl_dom[0];
	  num2 = index_nonl_dom[1];

	  if (num1+num > num2)
	    num2 = num1+num;

	  temp_nonl = (locint*) malloc(sizeof(locint)*(num2+2));
	  temp_nonl[1] = num2;

	  i = 2;
	  k = 2;
	  j = 2;
	  num1 +=2;
	  num2 = num+2;
	  while ((i<num1) && (j < num2)){
	    if (ind_dom[arg2][j] < index_nonl_dom[i]) /* < */ {
	      temp_nonl[k] = ind_dom[arg2][j];
	      j++; k++;
	    } else {
	      if (ind_dom[arg2][j] == index_nonl_dom[i])  /* == */ {
		temp_nonl[k] = ind_dom[arg2][j];
		j++; k++; i++;
	      } else {
		temp_nonl[k] = index_nonl_dom[i];
		i++; k++;
	      }
	    }
	  }
	  for(l = j;l<num2;l++) {
	    temp_nonl[k] = ind_dom[arg2][l];
	    k++;
	  }
	  for(l = i;l<num1;l++) {
	    temp_nonl[k] = index_nonl_dom[l];
	    k++;
	  }
	  temp_nonl[0] = k-2;
	  free((char*) nonl_dom[index]);
	  nonl_dom[index] = temp_nonl;
	}
    }
}

void extend_nonlinearity_domain_unary
(int arg, locint **ind_dom, locint **nonl_dom) {
    extend_nonlinearity_domain_binary_step(arg, arg, ind_dom, nonl_dom);
}

void extend_nonlinearity_domain_binary
(int arg1, int arg2, locint **ind_dom, locint **nonl_dom) {
    extend_nonlinearity_domain_binary_step(arg1, arg2, ind_dom, nonl_dom);
    extend_nonlinearity_domain_binary_step(arg2, arg1, ind_dom, nonl_dom);
}


#if defined(_MPI_)
void extend_nonlinearity_domain_combine_received_trade(int index, int counts, locint **nonl_dom, locint *trade) {
    int num, i,j,k,l,m;
    locint* temp_nonl;
    num = nonl_dom[index][0];
    if ( num == 0) {
          if ( counts > nonl_dom[index][1]){
             free( nonl_dom[index]);
             nonl_dom[index] = (locint*) malloc(sizeof(locint)*(2*counts+2));
             nonl_dom[index][1] = 2*counts;
          }
          for( i=0; i<counts; i++ )
             nonl_dom[index][i+2] = trade[i];
          nonl_dom[index][0] = counts;
       } else { /* merge lists */
          temp_nonl = (locint*) malloc(sizeof(locint)*num);
          for(i=0; i<num; i++ )
             temp_nonl[i] = nonl_dom[index][i+2];
          if ( counts+num > nonl_dom[index][1]){
             free( nonl_dom[index]);
             nonl_dom[index] = (locint*) malloc(sizeof(locint)*2*(counts+num+1));
             nonl_dom[index][1] = 2*(counts+num);
          }
          i = 0; // counts in temp_nonl
          j = 0; // counts in trade
          k = 2; // actually adress in nonl_dom[arg1][...]
          while ((i<num) && (j < counts)) {
             if (trade[j] < temp_nonl[i]) /* < */  {
                nonl_dom[index][k] = trade[j];
                j++; k++;
             } else {
                if (trade[j] == temp_nonl[i])  /* == */ {
                nonl_dom[index][k] = trade[j];
                j++; k++; i++;
                } else /* > */ {
                   nonl_dom[index][k] = temp_nonl[i];
                   i++; k++;
                }
             }
          }
          for(l = j ; l<counts;l++) {
             nonl_dom[index][k] = trade[l];
             k++;
          }
          for (l = i ; l<num;l++) {
             nonl_dom[index][k] = temp_nonl[l];
             k++;
          }
         nonl_dom[index][0] = k-2;
         free((char*) temp_nonl);
       }
}
#endif
#endif
#endif
END_C_DECLS
