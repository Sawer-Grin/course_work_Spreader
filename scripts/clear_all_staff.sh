#!/bin/bash

db_container_name='files'

clear_directories() {
    rm -f -r -d $PWD/temp/* &>/dev/null
    rm -f -r -d $PWD/uploads/* &>/dev/null
}

clear_container_with_db() {
    echo "Start removing container files"
    docker container kill $db_container_name &>/dev/null
    docker container rm -f $db_container_name &>/dev/null
    echo "Finish of removing container files"
}

clear_container_micro_services() {
    source $PWD/micro_services/scripts/clear_staff.sh
    clear_micro_services
}

remove_image_micro_services() {
    source $PWD/micro_services/scripts/clear_staff.sh
    remove_micro_services
}

clear_container_main_service() {
    source $PWD/eShare/scripts/clear_staff.sh
    clear_view_app
}

remove_image_main_services() {
    source $PWD/eShare/scripts/clear_staff.sh
    remove_view_app
}

remove_dir_temp_and_uploads() {
    rm -f -r -d $PWD/../../temp
    rm -f -r -d $PWD/../../uploads
}

clear_all_containers() {
    clear_container_micro_services
    clear_container_main_service
    clear_container_with_db
}

remove_all_images() {
    remove_image_micro_services
    remove_image_main_services
}

run() {
    case "$1" in 
        --all | -a)
            echo "Clear all (containers, images)"
            clear_all_containers
            remove_all_images
            clear_directories
        ;;
        --containers | -c)
            echo "Clear just containers..."
            clear_all_containers
        ;;
        --image | -i)
            echo "Clear just images..."
            remove_all_images
        ;;
        *)
            echo "Empty call for clear_all_staff"
        ;;  
    esac
}

run "$@"