#!/bin/bash

source $PWD/scripts/clear_all_staff.sh

rebuild_view_app_front_end() {
    source $PWD/eShare/scripts/build_app.sh
    rebuild_front_end
}

build_view_app_padding() {
    source $PWD/eShare/scripts/build_app.sh
    build_service
}

build_micro_services_padding() {
    source $PWD/micro_services/scripts/build_app.sh
    build_micro_sevices
}

injection_into_micro_service_container() {
    docker exec -it micro_services /bin/bash
}

build_all_containers() {
    build_micro_services_padding
    build_view_app_padding
}

create_empty_directory() {
    mkdir $PWD/../../temp
    mkdir $PWD/../../uploads
}

run_all_serves_in_background() {
    docker compose up -d
}

run_app() {
    docker compose up
}

run() {
    case "$1" in 
        --force-rebuild | -f)
            echo "Force way for running app..."
            clear_all_containers
            remove_all_images
            remove_dir_temp_and_uploads
            create_empty_directory
            build_all_containers
            run_app
        ;;
        --overload-all | -o)
            echo "Running app with overloading..."
            clear_all_containers
            build_all_containers
            run_app
        ;;
        --overload-micro-services | -o-micro)
            echo "Running app with overloading... micro_services"
            clear_all_containers
            build_micro_services_padding
            run_app
        ;;
        --overload-view-app | -o-view)
            echo "Running app with overloading... view_app"
            clear_all_containers
            build_view_app_padding
            run_app
        ;;
        --rebuld-front | -front)
            echo "Force way for running app... with rebuilding front end part"
            rebuild_view_app_front_end
            clear_all_containers
            remove_image_main_services
            build_all_containers
            run_app
        ;;
        --inject-micro-services | -inject)
            injection_into_micro_service_container
        ;;
        *)
            echo "Mistake. Choose a option"
        ;;
    esac
}

run "$@"
