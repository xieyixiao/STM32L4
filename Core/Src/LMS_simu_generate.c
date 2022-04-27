/*
 * File: LMS_simu_generate.c
 *
 * Code generated for Simulink model 'LMS_simu_generate'.
 *
 * Model version                  : 1.131
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Mon Apr 25 15:26:19 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: STMicroelectronics->STM32 32-bit Cortex-M
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "LMS_simu_generate.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
static void MovingAverage1_Init(DW_MovingAverage1 *localDW);
static void MovingAverage1_Start(DW_MovingAverage1 *localDW);
static void MovingAverage1(real32_T rtu_0, DW_MovingAverage1 *localDW);
static void MedianFilter1_Init(DW_MedianFilter1 *localDW);
static void MedianFilter1_Start(DW_MedianFilter1 *localDW);
static void MedianFilter1(real32_T rtu_0, DW_MedianFilter1 *localDW);

/* Forward declaration for local functions */
static void SystemCore_release(dsp_simulink_MovingAverage *obj);
static void SystemCore_delete(dsp_simulink_MovingAverage *obj);
static void matlabCodegenHandle_matlabCodeg(dsp_simulink_MovingAverage *obj);

/* Forward declaration for local functions */
static void MedianFilterCG_resetImpl(dsp_private_MedianFilterCG *obj);
static void MedianFilterCG_trickleDownMax(dsp_private_MedianFilterCG *obj,
  real32_T i);
static void MedianFilterCG_trickleDownMin(dsp_private_MedianFilterCG *obj,
  real32_T i);
static void SystemCore_release_m(dsp_MedianFilter *obj);
static void SystemCore_delete_a(dsp_MedianFilter *obj);
static void matlabCodegenHandle_matlabCod_g(dsp_MedianFilter *obj);
static void SystemCore_release(dsp_simulink_MovingAverage *obj)
{
  dsp_private_SlidingWindowAverag *obj_0;
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    obj_0 = obj->pStatistic;
    if (obj_0->isInitialized == 1) {
      obj_0->isInitialized = 2;
    }

    obj->NumChannels = -1;
  }
}

static void SystemCore_delete(dsp_simulink_MovingAverage *obj)
{
  SystemCore_release(obj);
}

static void matlabCodegenHandle_matlabCodeg(dsp_simulink_MovingAverage *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete(obj);
  }
}

/*
 * System initialize for atomic system:
 *    synthesized block
 *    synthesized block
 */
static void MovingAverage1_Init(DW_MovingAverage1 *localDW)
{
  /* InitializeConditions for MATLABSystem: '<Root>/Moving Average1' */
  if (localDW->obj.pStatistic->isInitialized == 1) {
    localDW->obj.pStatistic->pCumSum = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[0] = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[1] = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[2] = 0.0F;
    localDW->obj.pStatistic->pCumRevIndex = 1.0F;
  }

  /* End of InitializeConditions for MATLABSystem: '<Root>/Moving Average1' */
}

/*
 * Start for atomic system:
 *    synthesized block
 *    synthesized block
 */
static void MovingAverage1_Start(DW_MovingAverage1 *localDW)
{
  /* Start for MATLABSystem: '<Root>/Moving Average1' */
  localDW->obj.matlabCodegenIsDeleted = true;
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  localDW->obj.isSetupComplete = false;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  localDW->gobj_0.isInitialized = 0;
  localDW->obj.pStatistic = &localDW->gobj_0;
  localDW->obj.isSetupComplete = true;
  localDW->obj.TunablePropsChanged = false;
}

/*
 * Output and update for atomic system:
 *    synthesized block
 *    synthesized block
 */
static void MovingAverage1(real32_T rtu_0, DW_MovingAverage1 *localDW)
{
  real32_T cumRevIndex;
  real32_T csum;
  real32_T csumrev[3];
  real32_T z;
  int32_T z_tmp;

  /* MATLABSystem: '<Root>/Moving Average1' */
  if (localDW->obj.TunablePropsChanged) {
    localDW->obj.TunablePropsChanged = false;
  }

  if (localDW->obj.pStatistic->isInitialized != 1) {
    localDW->obj.pStatistic->isSetupComplete = false;
    localDW->obj.pStatistic->isInitialized = 1;
    localDW->obj.pStatistic->pCumSum = 0.0F;
    localDW->obj.pStatistic->pCumRevIndex = 1.0F;
    localDW->obj.pStatistic->isSetupComplete = true;
    localDW->obj.pStatistic->pCumSum = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[0] = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[0] = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[1] = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[1] = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[2] = 0.0F;
    localDW->obj.pStatistic->pCumSumRev[2] = 0.0F;
    localDW->obj.pStatistic->pCumRevIndex = 1.0F;
  }

  cumRevIndex = localDW->obj.pStatistic->pCumRevIndex;
  csum = localDW->obj.pStatistic->pCumSum;
  csumrev[0] = localDW->obj.pStatistic->pCumSumRev[0];
  csumrev[1] = localDW->obj.pStatistic->pCumSumRev[1];
  csumrev[2] = localDW->obj.pStatistic->pCumSumRev[2];
  csum += rtu_0;
  z_tmp = (int32_T)cumRevIndex - 1;
  z = csumrev[z_tmp] + csum;
  csumrev[z_tmp] = rtu_0;
  if (cumRevIndex != 3.0F) {
    cumRevIndex++;
  } else {
    cumRevIndex = 1.0F;
    csum = 0.0F;
    csumrev[1] += csumrev[2];
    csumrev[0] += csumrev[1];
  }

  localDW->obj.pStatistic->pCumSum = csum;
  localDW->obj.pStatistic->pCumSumRev[0] = csumrev[0];
  localDW->obj.pStatistic->pCumSumRev[1] = csumrev[1];
  localDW->obj.pStatistic->pCumSumRev[2] = csumrev[2];
  localDW->obj.pStatistic->pCumRevIndex = cumRevIndex;
  localDW->MovingAverage1_n = z / 4.0F;

  /* End of MATLABSystem: '<Root>/Moving Average1' */
}

static void MedianFilterCG_resetImpl(dsp_private_MedianFilterCG *obj)
{
  real32_T cnt1;
  real32_T cnt2;
  int32_T c_index;
  memset(&obj->pBuf[0], 0, 40U * sizeof(real32_T));
  memset(&obj->pPos[0], 0, 40U * sizeof(real32_T));
  memset(&obj->pHeap[0], 0, 40U * sizeof(real32_T));
  obj->pWinLen = 40.0F;
  obj->pIdx = obj->pWinLen;
  obj->pMidHeap = (real32_T)ceil((obj->pWinLen + 1.0F) / 2.0F);
  cnt1 = (obj->pWinLen - 1.0F) / 2.0F;
  if (cnt1 < 0.0F) {
    obj->pMinHeapLength = (real32_T)ceil(cnt1);
  } else {
    obj->pMinHeapLength = (real32_T)floor(cnt1);
  }

  cnt1 = obj->pWinLen / 2.0F;
  if (cnt1 < 0.0F) {
    obj->pMaxHeapLength = (real32_T)ceil(cnt1);
  } else {
    obj->pMaxHeapLength = (real32_T)floor(cnt1);
  }

  cnt1 = 1.0F;
  cnt2 = obj->pWinLen;
  for (c_index = 0; c_index < 40; c_index++) {
    if ((int32_T)(real32_T)fmod(40.0F + -(real32_T)c_index, 2.0) == 0) {
      obj->pPos[(40 - c_index) - 1] = cnt1;
      cnt1++;
    } else {
      obj->pPos[(40 - c_index) - 1] = cnt2;
      cnt2--;
    }

    obj->pHeap[(int32_T)obj->pPos[(40 - c_index) - 1] - 1] = 40.0F + -(real32_T)
      c_index;
  }
}

static void MedianFilterCG_trickleDownMax(dsp_private_MedianFilterCG *obj,
  real32_T i)
{
  real32_T temp;
  real32_T u;
  real32_T ind2;
  int32_T temp_tmp;
  boolean_T exitg1;
  exitg1 = false;
  while ((!exitg1) && (i >= -obj->pMaxHeapLength)) {
    if ((i < -1.0F) && (i > -obj->pMaxHeapLength) && (obj->pBuf[(int32_T)
         obj->pHeap[(int32_T)(i + obj->pMidHeap) - 1] - 1] < obj->pBuf[(int32_T)
         obj->pHeap[(int32_T)((i - 1.0F) + obj->pMidHeap) - 1] - 1])) {
      i--;
    }

    u = i / 2.0F;
    if (u < 0.0F) {
      u = (real32_T)ceil(u);
    } else {
      u = (real32_T)floor(u);
    }

    ind2 = i + obj->pMidHeap;
    if (!(obj->pBuf[(int32_T)obj->pHeap[(int32_T)(u + obj->pMidHeap) - 1] - 1] <
          obj->pBuf[(int32_T)obj->pHeap[(int32_T)ind2 - 1] - 1])) {
      exitg1 = true;
    } else {
      u = i / 2.0F;
      if (u < 0.0F) {
        u = (real32_T)ceil(u);
      } else {
        u = (real32_T)floor(u);
      }

      u += obj->pMidHeap;
      temp_tmp = (int32_T)u - 1;
      temp = obj->pHeap[temp_tmp];
      obj->pHeap[temp_tmp] = obj->pHeap[(int32_T)ind2 - 1];
      obj->pHeap[(int32_T)ind2 - 1] = temp;
      obj->pPos[(int32_T)obj->pHeap[(int32_T)u - 1] - 1] = u;
      obj->pPos[(int32_T)obj->pHeap[(int32_T)ind2 - 1] - 1] = ind2;
      i *= 2.0F;
    }
  }
}

static void MedianFilterCG_trickleDownMin(dsp_private_MedianFilterCG *obj,
  real32_T i)
{
  real32_T temp;
  real32_T u;
  real32_T ind1;
  int32_T tmp;
  boolean_T exitg1;
  exitg1 = false;
  while ((!exitg1) && (i <= obj->pMinHeapLength)) {
    if ((i > 1.0F) && (i < obj->pMinHeapLength) && (obj->pBuf[(int32_T)
         obj->pHeap[(int32_T)((i + 1.0F) + obj->pMidHeap) - 1] - 1] < obj->pBuf
         [(int32_T)obj->pHeap[(int32_T)(i + obj->pMidHeap) - 1] - 1])) {
      i++;
    }

    u = i / 2.0F;
    if (u < 0.0F) {
      u = (real32_T)ceil(u);
    } else {
      u = (real32_T)floor(u);
    }

    ind1 = i + obj->pMidHeap;
    if (!(obj->pBuf[(int32_T)obj->pHeap[(int32_T)ind1 - 1] - 1] < obj->pBuf
          [(int32_T)obj->pHeap[(int32_T)(u + obj->pMidHeap) - 1] - 1])) {
      exitg1 = true;
    } else {
      u = i / 2.0F;
      if (u < 0.0F) {
        u = (real32_T)ceil(u);
      } else {
        u = (real32_T)floor(u);
      }

      u += obj->pMidHeap;
      temp = obj->pHeap[(int32_T)ind1 - 1];
      tmp = (int32_T)u - 1;
      obj->pHeap[(int32_T)ind1 - 1] = obj->pHeap[tmp];
      obj->pHeap[tmp] = temp;
      obj->pPos[(int32_T)obj->pHeap[(int32_T)ind1 - 1] - 1] = ind1;
      obj->pPos[(int32_T)obj->pHeap[(int32_T)u - 1] - 1] = u;
      i *= 2.0F;
    }
  }
}

static void SystemCore_release_m(dsp_MedianFilter *obj)
{
  if ((obj->isInitialized == 1) && obj->isSetupComplete) {
    obj->NumChannels = -1;
    if (obj->pMID.isInitialized == 1) {
      obj->pMID.isInitialized = 2;
    }
  }
}

static void SystemCore_delete_a(dsp_MedianFilter *obj)
{
  SystemCore_release_m(obj);
}

static void matlabCodegenHandle_matlabCod_g(dsp_MedianFilter *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    SystemCore_delete_a(obj);
  }
}

/*
 * System initialize for atomic system:
 *    synthesized block
 *    synthesized block
 */
static void MedianFilter1_Init(DW_MedianFilter1 *localDW)
{
  /* InitializeConditions for MATLABSystem: '<Root>/Median Filter1' */
  if (localDW->obj.pMID.isInitialized == 1) {
    MedianFilterCG_resetImpl(&localDW->obj.pMID);
  }

  /* End of InitializeConditions for MATLABSystem: '<Root>/Median Filter1' */
}

/*
 * Start for atomic system:
 *    synthesized block
 *    synthesized block
 */
static void MedianFilter1_Start(DW_MedianFilter1 *localDW)
{
  dsp_MedianFilter *obj;

  /* Start for MATLABSystem: '<Root>/Median Filter1' */
  localDW->obj.matlabCodegenIsDeleted = true;
  localDW->obj.isInitialized = 0;
  localDW->obj.NumChannels = -1;
  localDW->obj.matlabCodegenIsDeleted = false;
  localDW->objisempty = true;
  obj = &localDW->obj;
  localDW->obj.isSetupComplete = false;
  localDW->obj.isInitialized = 1;
  localDW->obj.NumChannels = 1;
  obj->pMID.isInitialized = 0;
  localDW->obj.isSetupComplete = true;
}

/*
 * Output and update for atomic system:
 *    synthesized block
 *    synthesized block
 */
static void MedianFilter1(real32_T rtu_0, DW_MedianFilter1 *localDW)
{
  dsp_MedianFilter *obj;
  dsp_private_MedianFilterCG *obj_0;
  real32_T vprev;
  real32_T p;
  boolean_T flag;
  real32_T ind2;
  real32_T temp;
  int32_T temp_tmp;
  real32_T flag_tmp_tmp;
  boolean_T exitg1;

  /* MATLABSystem: '<Root>/Median Filter1' */
  obj = &localDW->obj;
  obj_0 = &localDW->obj.pMID;
  if (obj->pMID.isInitialized != 1) {
    obj->pMID.isSetupComplete = false;
    obj->pMID.isInitialized = 1;
    obj->pMID.isSetupComplete = true;
    MedianFilterCG_resetImpl(&obj->pMID);
  }

  vprev = obj->pMID.pBuf[(int32_T)obj->pMID.pIdx - 1];
  obj->pMID.pBuf[(int32_T)obj->pMID.pIdx - 1] = rtu_0;
  p = obj->pMID.pPos[(int32_T)obj->pMID.pIdx - 1];
  obj->pMID.pIdx++;
  if (obj->pMID.pWinLen + 1.0F == obj->pMID.pIdx) {
    obj->pMID.pIdx = 1.0F;
  }

  if (p > obj->pMID.pMidHeap) {
    if (vprev < rtu_0) {
      vprev = p - obj->pMID.pMidHeap;
      MedianFilterCG_trickleDownMin(&obj->pMID, vprev * 2.0F);
    } else {
      vprev = p - obj->pMID.pMidHeap;
      exitg1 = false;
      while ((!exitg1) && (vprev > 0.0F)) {
        flag_tmp_tmp = (real32_T)floor(vprev / 2.0F);
        flag = (obj_0->pBuf[(int32_T)obj_0->pHeap[(int32_T)(vprev +
                 obj_0->pMidHeap) - 1] - 1] < obj_0->pBuf[(int32_T)obj_0->pHeap
                [(int32_T)(flag_tmp_tmp + obj_0->pMidHeap) - 1] - 1]);
        if (!flag) {
          exitg1 = true;
        } else {
          p = vprev + obj_0->pMidHeap;
          ind2 = (real32_T)floor(vprev / 2.0F) + obj_0->pMidHeap;
          temp = obj_0->pHeap[(int32_T)p - 1];
          obj_0->pHeap[(int32_T)p - 1] = obj_0->pHeap[(int32_T)ind2 - 1];
          obj_0->pHeap[(int32_T)ind2 - 1] = temp;
          obj_0->pPos[(int32_T)obj_0->pHeap[(int32_T)p - 1] - 1] = p;
          obj_0->pPos[(int32_T)obj_0->pHeap[(int32_T)ind2 - 1] - 1] = ind2;
          vprev = flag_tmp_tmp;
        }
      }

      if (vprev == 0.0F) {
        MedianFilterCG_trickleDownMax(&obj->pMID, -1.0F);
      }
    }
  } else if (p < obj->pMID.pMidHeap) {
    if (rtu_0 < vprev) {
      vprev = p - obj->pMID.pMidHeap;
      MedianFilterCG_trickleDownMax(&obj->pMID, vprev * 2.0F);
    } else {
      vprev = p - obj->pMID.pMidHeap;
      exitg1 = false;
      while ((!exitg1) && (vprev < 0.0F)) {
        p = vprev / 2.0F;
        if (p < 0.0F) {
          p = (real32_T)ceil(p);
        } else {
          p = -0.0F;
        }

        flag = (obj_0->pBuf[(int32_T)obj_0->pHeap[(int32_T)(p + obj_0->pMidHeap)
                - 1] - 1] < obj_0->pBuf[(int32_T)obj_0->pHeap[(int32_T)(vprev +
                 obj_0->pMidHeap) - 1] - 1]);
        if (!flag) {
          exitg1 = true;
        } else {
          p = vprev / 2.0F;
          if (p < 0.0F) {
            p = (real32_T)ceil(p);
          } else {
            p = -0.0F;
          }

          p += obj_0->pMidHeap;
          ind2 = vprev + obj_0->pMidHeap;
          temp_tmp = (int32_T)p - 1;
          temp = obj_0->pHeap[temp_tmp];
          obj_0->pHeap[temp_tmp] = obj_0->pHeap[(int32_T)ind2 - 1];
          obj_0->pHeap[(int32_T)ind2 - 1] = temp;
          obj_0->pPos[(int32_T)obj_0->pHeap[(int32_T)p - 1] - 1] = p;
          obj_0->pPos[(int32_T)obj_0->pHeap[(int32_T)ind2 - 1] - 1] = ind2;
          p = vprev / 2.0F;
          if (p < 0.0F) {
            vprev = (real32_T)ceil(p);
          } else {
            vprev = -0.0F;
          }
        }
      }

      if (vprev == 0.0F) {
        MedianFilterCG_trickleDownMin(&obj->pMID, 1.0F);
      }
    }
  } else {
    if (obj->pMID.pMaxHeapLength != 0.0F) {
      MedianFilterCG_trickleDownMax(&obj->pMID, -1.0F);
    }

    if (obj->pMID.pMinHeapLength > 0.0F) {
      MedianFilterCG_trickleDownMin(&obj->pMID, 1.0F);
    }
  }

  vprev = obj->pMID.pBuf[(int32_T)obj->pMID.pHeap[(int32_T)obj->pMID.pMidHeap -
    1] - 1];
  vprev += obj->pMID.pBuf[(int32_T)obj->pMID.pHeap[(int32_T)(obj->pMID.pMidHeap
    - 1.0F) - 1] - 1];
  localDW->MedianFilter1_i = vprev / 2.0F;

  /* End of MATLABSystem: '<Root>/Median Filter1' */
}

/* Model step function */
void LMS_simu_generate_step(void)
{
  /* local block i/o variables */
  real32_T rtb_DataTypeConversion;
  real32_T rtb_Sum;
  real32_T rtb_DataTypeConversion1;
  real32_T rtb_Sum1;
  real_T rtb_y_h;
  real32_T rtb_Delay1;
  real32_T rtb_Delay;
  real32_T rtb_Delay2;
  real32_T rtb_y_d;
  real32_T rtb_y_j;
  uint32_T qY;

  /* Delay: '<Root>/Delay1' */
  rtb_Delay1 = rtDW.Delay1_DSTATE;

  /* Delay: '<Root>/Delay' */
  rtb_Delay = rtDW.Delay_DSTATE;

  /* DataTypeConversion: '<Root>/Data Type Conversion' incorporates:
   *  Inport: '<Root>/In1'
   */
  rtb_DataTypeConversion = (real32_T)rtU.In1;
  MedianFilter1(rtb_DataTypeConversion, &rtDW.MedianFilter);

  /* Sum: '<Root>/Sum' */
  rtb_Sum = rtb_DataTypeConversion - rtDW.MedianFilter.MedianFilter1_i;
  MovingAverage1(rtb_Sum, &rtDW.MovingAverage);

  /* MATLAB Function: '<Root>/MATLAB Function' */
  rtb_y_d = 0.0F;
  if ((rtDW.i_j < 30.0) && (rtb_Delay > rtb_Delay1) && (rtb_Delay >
       rtDW.MovingAverage.MovingAverage1_n)) {
    if (!(rtDW.T_n > rtb_Delay)) {
      rtDW.T_n = rtb_Delay;
    }

    if (!(rtDW.N_e < rtb_Delay)) {
      rtDW.N_e = rtb_Delay;
    }

    rtDW.i_j++;
  }

  if (rtDW.i_j == 30.0) {
    rtDW.T_n *= 0.333333343F;
    rtDW.S_m = rtDW.T_n;
    rtDW.N_e *= 0.333333343F;
    rtDW.i_j++;
  }

  if ((rtDW.i_j > 30.0) && (rtb_Delay >= rtb_Delay1) && (rtb_Delay >=
       rtDW.MovingAverage.MovingAverage1_n)) {
    qY = rtDW.cur_l - /*MW:OvSatOk*/ rtDW.pre_k;
    if (qY > rtDW.cur_l) {
      qY = 0U;
    }

    if ((rtb_Delay > rtDW.T_n) && (qY >= 37U)) {
      rtDW.S_m = 0.125F * rtb_Delay + 0.875F * rtDW.S_m;
      rtb_y_d = rtb_Delay;
      rtDW.pre_k = rtDW.cur_l;
    } else {
      rtDW.N_e = 0.125F * rtb_Delay + 0.875F * rtDW.N_e;
    }

    rtDW.T_n = (rtDW.S_m - rtDW.N_e) * 0.25F + rtDW.N_e;
  }

  qY = rtDW.cur_l + /*MW:OvSatOk*/ 1U;
  if (qY < rtDW.cur_l) {
    qY = MAX_uint32_T;
  }

  rtDW.cur_l = qY;

  /* End of MATLAB Function: '<Root>/MATLAB Function' */

  /* MATLAB Function: '<Root>/MATLAB Function1' */
  if (rtb_y_d == 0.0F) {
    rtDW.t_n++;
    rtb_y_h = rtDW.pre_h;
  } else {
    rtb_y_h = 6000.0 / rtDW.t_n;
    rtDW.pre_h = rtb_y_h;
    rtDW.t_n = 0.0;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function1' */

  /* Outport: '<Root>/Out1' incorporates:
   *  DataTypeConversion: '<Root>/Data Type Conversion2'
   */
  rtY.Out1 = (uint16_T)rtb_y_h;

  /* Delay: '<Root>/Delay3' */
  rtb_Delay1 = rtDW.Delay3_DSTATE;

  /* Delay: '<Root>/Delay2' */
  rtb_Delay2 = rtDW.Delay2_DSTATE;

  /* DataTypeConversion: '<Root>/Data Type Conversion1' incorporates:
   *  Inport: '<Root>/In2'
   */
  rtb_DataTypeConversion1 = (real32_T)rtU.In2;

  /* MATLABSystem: '<Root>/Median Filter1' */
  MedianFilter1(rtb_DataTypeConversion1, &rtDW.MedianFilter1_p);

  /* Sum: '<Root>/Sum1' */
  rtb_Sum1 = rtb_DataTypeConversion1 - rtDW.MedianFilter1_p.MedianFilter1_i;

  /* MATLABSystem: '<Root>/Moving Average1' */
  MovingAverage1(rtb_Sum1, &rtDW.MovingAverage1_p);

  /* MATLAB Function: '<Root>/MATLAB Function4' */
  rtb_y_j = 0.0F;
  if ((rtDW.i < 30.0) && (rtb_Delay2 > rtb_Delay1) && (rtb_Delay2 >
       rtDW.MovingAverage1_p.MovingAverage1_n)) {
    if (rtDW.i < 5.0) {
      rtDW.i++;
    } else {
      if (!(rtDW.T > rtb_Delay2)) {
        rtDW.T = rtb_Delay2;
      }

      if (!(rtDW.N < rtb_Delay2)) {
        rtDW.N = rtb_Delay2;
      }

      rtDW.i++;
    }
  }

  if (rtDW.i == 30.0) {
    rtDW.T *= 0.333333343F;
    rtDW.S = rtDW.T;
    rtDW.N *= 0.5F;
    rtDW.i++;
  }

  if ((rtDW.i > 30.0) && (rtb_Delay2 >= rtb_Delay1) && (rtb_Delay2 >=
       rtDW.MovingAverage1_p.MovingAverage1_n)) {
    qY = rtDW.cur - /*MW:OvSatOk*/ rtDW.pre_f;
    if (qY > rtDW.cur) {
      qY = 0U;
    }

    if ((rtb_Delay2 > rtDW.T) && (qY >= 36U)) {
      rtDW.S = 0.125F * rtb_Delay2 + 0.875F * rtDW.S;
      rtb_y_j = rtb_Delay2;
      rtDW.pre_f = rtDW.cur;
    } else {
      rtDW.N = 0.125F * rtb_Delay2 + 0.875F * rtDW.N;
    }

    rtDW.T = (rtDW.S - rtDW.N) * 0.25F + rtDW.N;
  }

  qY = rtDW.cur + /*MW:OvSatOk*/ 1U;
  if (qY < rtDW.cur) {
    qY = MAX_uint32_T;
  }

  rtDW.cur = qY;

  /* End of MATLAB Function: '<Root>/MATLAB Function4' */

  /* MATLAB Function: '<Root>/MATLAB Function3' */
  if (rtb_y_d == 0.0F) {
    rtDW.t++;
    rtb_y_h = rtDW.pre;
  } else {
    rtDW.t = 0.0;
    rtb_y_h = rtDW.pre;
  }

  if (rtb_y_j > 0.0F) {
    rtb_y_h = rtDW.t;
    rtDW.pre = rtDW.t;
    rtDW.t = 0.0;
  }

  /* End of MATLAB Function: '<Root>/MATLAB Function3' */

  /* Outport: '<Root>/Out2' incorporates:
   *  Bias: '<Root>/Bias'
   *  DataTypeConversion: '<Root>/Data Type Conversion3'
   *  Gain: '<Root>/Gain2'
   */
  rtY.Out2 = (uint16_T)(-1.875 * rtb_y_h + 177.5);

  /* Outport: '<Root>/Out3' incorporates:
   *  Bias: '<Root>/Bias1'
   *  DataTypeConversion: '<Root>/Data Type Conversion5'
   *  Gain: '<Root>/Gain3'
   */
  rtY.Out3 = (uint16_T)(-0.8571 * rtb_y_h + 108.3);

  /* Update for Delay: '<Root>/Delay1' */
  rtDW.Delay1_DSTATE = rtb_Delay;

  /* Update for Delay: '<Root>/Delay' */
  rtDW.Delay_DSTATE = rtDW.MovingAverage.MovingAverage1_n;

  /* Update for Delay: '<Root>/Delay3' */
  rtDW.Delay3_DSTATE = rtb_Delay2;

  /* Update for Delay: '<Root>/Delay2' */
  rtDW.Delay2_DSTATE = rtDW.MovingAverage1_p.MovingAverage1_n;
}

/* Model initialize function */
void LMS_simu_generate_initialize(void)
{
  MedianFilter1_Start(&rtDW.MedianFilter);
  MovingAverage1_Start(&rtDW.MovingAverage);

  /* Start for MATLABSystem: '<Root>/Median Filter1' */
  MedianFilter1_Start(&rtDW.MedianFilter1_p);

  /* Start for MATLABSystem: '<Root>/Moving Average1' */
  MovingAverage1_Start(&rtDW.MovingAverage1_p);
  MedianFilter1_Init(&rtDW.MedianFilter);
  MovingAverage1_Init(&rtDW.MovingAverage);
  MedianFilter1_Init(&rtDW.MedianFilter1_p);
  MovingAverage1_Init(&rtDW.MovingAverage1_p);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
