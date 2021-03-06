//=======================================================================
// Copyright Baptiste Wicht 2013-2014.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#include <file.hpp>
#include <system.hpp>
#include <errors.hpp>
#include <print.hpp>
#include <directory_entry.hpp>

static constexpr const size_t BUFFER_SIZE = 4096;

int main(int argc, char* argv[]){
    //TODO Support ls with no-arg

    if(argc == 1){
        print_line("Usage: ls file_path");
        exit(1);
    }

    auto fd = open(argv[1]);

    if(fd.valid()){
        auto info = stat(*fd);

        if(info.valid()){
            if(!(info->flags & STAT_FLAG_DIRECTORY)){
                print_line("ls: error: Is not a directory");
            } else {
                auto buffer = new char[BUFFER_SIZE];

                auto entries_result = entries(*fd, buffer, BUFFER_SIZE);

                if(entries_result.valid()){
                    size_t position = 0;

                    while(true){
                        auto entry = reinterpret_cast<directory_entry*>(buffer + position);

                        print_line(&entry->name);

                        if(!entry->offset_next){
                            break;
                        }

                        position += entry->offset_next;
                    }
                } else {
                    printf("ls: error: %s\n", std::error_message(entries_result.error()));
                }

                delete[] buffer;
            }
        } else {
            printf("ls: error: %s\n", std::error_message(info.error()));
        }

        close(*fd);
    } else {
        printf("ls: error: %s\n", std::error_message(fd.error()));
    }

    exit(0);
}