/*
 * File: LMS_simu_generate.h
 *
 * Code generated for Simulink model 'LMS_simu_generate'.
 *
 * Model version                  : 1.117
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Wed Mar 16 13:26:07 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->STM32 32-bit Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef RTW_HEADER_LMS_simu_generate_h_
#define RTW_HEADER_LMS_simu_generate_h_
#include "rtwtypes.h"
#include <math.h>
#include <string.h>
#ifndef LMS_simu_generate_COMMON_INCLUDES_
# define LMS_simu_generate_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* LMS_simu_generate_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

#ifndef typedef_dsp_private_SlidingWindowAverag
#define typedef_dsp_private_SlidingWindowAverag

typedef struct {
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real32_T pCumSum;
  real32_T pCumSumRev[3];
  real32_T pCumRevIndex;
} dsp_private_SlidingWindowAverag;

#endif                                 /*typedef_dsp_private_SlidingWindowAverag*/

#ifndef typedef_cell_wrap
#define typedef_cell_wrap

typedef struct {
  uint32_T f1[8];
} cell_wrap;

#endif                                 /*typedef_cell_wrap*/

#ifndef typedef_dsp_simulink_MovingAverage
#define typedef_dsp_simulink_MovingAverage

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap inputVarSize;
  dsp_private_SlidingWindowAverag *pStatistic;
  int32_T NumChannels;
} dsp_simulink_MovingAverage;

#endif                                 /*typedef_dsp_simulink_MovingAverage*/

#ifndef typedef_dsp_private_MedianFilterCG
#define typedef_dsp_private_MedianFilterCG

typedef struct {
  int32_T isInitialized;
  boolean_T isSetupComplete;
  real32_T pWinLen;
  real32_T pBuf[40];
  real32_T pHeap[40];
  real32_T pMidHeap;
  real32_T pIdx;
  real32_T pPos[40];
  real32_T pMinHeapLength;
  real32_T pMaxHeapLength;
} dsp_private_MedianFilterCG;

#endif                                 /*typedef_dsp_private_MedianFilterCG*/

#ifndef typedef_dsp_MedianFilter
#define typedef_dsp_MedianFilter

typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int32_T isInitialized;
  boolean_T isSetupComplete;
  cell_wrap inputVarSize;
  int32_T NumChannels;
  dsp_private_MedianFilterCG pMID;
} dsp_MedianFilter;

#endif                                 /*typedef_dsp_MedianFilter*/

/* Block signals and states (default storage) for system '<Root>/Moving Average1' */
typedef struct {
  dsp_simulink_MovingAverage obj;      /* '<Root>/Moving Average1' */
  dsp_private_SlidingWindowAverag gobj_0;/* '<Root>/Moving Average1' */
  dsp_private_SlidingWindowAverag gobj_1;/* '<Root>/Moving Average1' */
  real32_T MovingAverage1_n;           /* '<Root>/Moving Average1' */
  boolean_T objisempty;                /* '<Root>/Moving Average1' */
} DW_MovingAverage1;

/* Block signals and states (default storage) for system '<Root>/Median Filter1' */
typedef struct {
  dsp_MedianFilter obj;                /* '<Root>/Median Filter1' */
  real32_T MedianFilter1_i;            /* '<Root>/Median Filter1' */
  boolean_T objisempty;                /* '<Root>/Median Filter1' */
} DW_MedianFilter1;

/* Block signals and states (default storage) for system '<Root>/MATLAB Function1' */
typedef struct {
  real_T t;                            /* '<Root>/MATLAB Function1' */
  real_T pre;                          /* '<Root>/MATLAB Function1' */
} DW_MATLABFunction1;

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  DW_MATLABFunction1 sf_MATLABFunction2;/* '<Root>/MATLAB Function2' */
  DW_MATLABFunction1 sf_MATLABFunction1;/* '<Root>/MATLAB Function1' */
  DW_MedianFilter1 MedianFilter;       /* '<Root>/Median Filter1' */
  DW_MovingAverage1 MovingAverage;     /* '<Root>/Moving Average1' */
  DW_MedianFilter1 MedianFilter1_p;    /* '<Root>/Median Filter1' */
  DW_MovingAverage1 MovingAverage1_p;  /* '<Root>/Moving Average1' */
  real_T i;                            /* '<Root>/MATLAB Function4' */
  real_T t;                            /* '<Root>/MATLAB Function3' */
  real_T pre;                          /* '<Root>/MATLAB Function3' */
  real_T i_j;                          /* '<Root>/MATLAB Function' */
  real32_T Delay1_DSTATE;              /* '<Root>/Delay1' */
  real32_T Delay_DSTATE;               /* '<Root>/Delay' */
  real32_T Delay3_DSTATE;              /* '<Root>/Delay3' */
  real32_T Delay2_DSTATE;              /* '<Root>/Delay2' */
  real32_T T;                          /* '<Root>/MATLAB Function4' */
  real32_T S;                          /* '<Root>/MATLAB Function4' */
  real32_T N;                          /* '<Root>/MATLAB Function4' */
  real32_T T_n;                        /* '<Root>/MATLAB Function' */
  real32_T S_m;                        /* '<Root>/MATLAB Function' */
  real32_T N_e;                        /* '<Root>/MATLAB Function' */
  uint32_T pre_f;                      /* '<Root>/MATLAB Function4' */
  uint32_T cur;                        /* '<Root>/MATLAB Function4' */
  uint32_T pre_k;                      /* '<Root>/MATLAB Function' */
  uint32_T cur_l;                      /* '<Root>/MATLAB Function' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  uint32_T In1;                        /* '<Root>/In1' */
  uint32_T In2;                        /* '<Root>/In2' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  uint8_T Out1;                        /* '<Root>/Out1' */
  uint8_T Out2;                        /* '<Root>/Out2' */
  uint8_T Out3;                        /* '<Root>/Out3' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void LMS_simu_generate_initialize(void);
extern void LMS_simu_generate_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<Root>/Gain' : Eliminated nontunable gain of 1
 * Block '<Root>/Gain1' : Eliminated nontunable gain of 1
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'LMS_simu_generate'
 * '<S1>'   : 'LMS_simu_generate/MATLAB Function'
 * '<S2>'   : 'LMS_simu_generate/MATLAB Function1'
 * '<S3>'   : 'LMS_simu_generate/MATLAB Function2'
 * '<S4>'   : 'LMS_simu_generate/MATLAB Function3'
 * '<S5>'   : 'LMS_simu_generate/MATLAB Function4'
 */
#endif                                 /* RTW_HEADER_LMS_simu_generate_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
