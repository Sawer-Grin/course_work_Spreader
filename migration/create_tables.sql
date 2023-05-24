create type status_files as enum (
    'Uploaded', 'Compressing', 'Saved', 'Unclenched', 
    'ReadyToSend', 'Deleted'
);

create table file_storage
(
    size         bigint                                             not null,
    sender       varchar(40)                                                ,
    receiver     varchar(40)                                                ,
    uuid         uuid                     default gen_random_uuid() not null
        constraint file_storage_pk
            primary key,
    time_created timestamp with time zone default now()             not null,
    last_moment  timestamp with time zone                           not null,
    status       status_files                                       not null
);

alter table file_storage
    owner to file_system;