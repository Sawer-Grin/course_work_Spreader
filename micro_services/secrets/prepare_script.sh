#!/bin/bash

python3 create_password.py
set -a
source .temp_env
set +a
rm -f .temp_env
# tail -f &>/dev/null 
./micro_service
