#!/bin/bash

image_micro_services='scrambler_service_img'
container_micro_services='micro_services'

clear_micro_services() {
    echo "Start removing micro_services"
    docker kill $container_micro_services &>/dev/null
    docker container rm -f $container_micro_services &>/dev/null
    echo "Finish of removing micro_services"
}

remove_micro_services() {
    echo "Start removing image micro_services"
    docker rmi $(docker images $image_micro_services -a -q) &>/dev/null
    echo "Finish of removing image micro_services"
}
