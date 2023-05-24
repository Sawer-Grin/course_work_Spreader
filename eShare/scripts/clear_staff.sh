#!/bin/bash

service_view_app='view_app'

clear_view_app() {
    echo "Start remove view_app container"
    docker container kill $service_view_app &>/dev/null
    docker container rm -f $service_view_app &>/dev/null
    echo "Finish removing view_app container"
}

remove_view_app() {
    echo "Start removing image of view_app container"
    docker rmi $(docker images $service_view_app -a -q) &>/dev/null
    echo "Finish process of removing view_app container"
}
