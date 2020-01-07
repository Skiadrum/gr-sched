#!/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir="/home/robin/GNU/gr-sched/python"
export GR_CONF_CONTROLPORT_ON=False
export PATH="/home/robin/GNU/gr-sched/utils/python":$PATH
export LD_LIBRARY_PATH="":$LD_LIBRARY_PATH
export PYTHONPATH=/home/robin/GNU/gr-sched/utils/swig:$PYTHONPATH
/usr/bin/python3.6 /home/robin/GNU/gr-sched/python/qa_timestamp_out.py 
