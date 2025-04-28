cmake_minimum_required(VERSION 4.0.1)
project(my_shell VERSION 1.0)

set(CMAKE_C_STANDARD 23)
set(C_STANDARD_REQUIRED true)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -g")

include_directories(include)

add_executable(
    ${PROJECT_NAME} 
    src/main.c # Lance le programes
    src/input.c # Lit les commandes 
    src/commandes.c # Excute les commandes 
    src/shell.c  # Boucle principale du shell
    src/utils.c # Gere les pipes et les redirections
)
