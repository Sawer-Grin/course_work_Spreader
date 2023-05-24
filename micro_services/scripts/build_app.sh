#!/bin/bash

build_micro_sevices() {
    echo "Start of buildding micro_services"
    directory="$PWD/micro_services/Dockerfile"
    result=$(docker build -t micro_services -f $directory .)
    echo "Finishing building of micro_services"
}
