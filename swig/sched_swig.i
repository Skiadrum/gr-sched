/* -*- c++ -*- */

#define SCHED_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "sched_swig_doc.i"

%{
#include "sched/ncopy.h"
#include "sched/msg_forward.h"
#include "sched/timestamp_in.h"
#include "sched/timestamp_out.h"
%}

%include "sched/ncopy.h"
GR_SWIG_BLOCK_MAGIC2(sched, ncopy);
%include "sched/msg_forward.h"
GR_SWIG_BLOCK_MAGIC2(sched, msg_forward);

%include "sched/timestamp_in.h"
GR_SWIG_BLOCK_MAGIC2(sched, timestamp_in);
%include "sched/timestamp_out.h"
GR_SWIG_BLOCK_MAGIC2(sched, timestamp_out);
