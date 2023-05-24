#!/bin/bash

build_service() {
    echo "Start of building view_app container"
    path_to_container="$PWD/eShare/Dockerfile"
    result=$(docker build -t view_app -f $path_to_container .)
    echo "Finish of building view_app container"
}

rebuild_front_end() {
    directory="$PWD/eShare/"
    rm -f -d -r $directory/build
    npm run build --prefix $directory/js
    mv -f $directory/js/build $directory/build
}
