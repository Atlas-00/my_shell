cmake_minimum_required(VERSION 3.20)
project(my_shell VERSION 2.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME}
    src/main.c      # Lance le programme
    src/input.c     # Lit les commandes
    src/commandes.c # Exécute les commandes
    src/shell.c     # Boucle principale du shell
    src/utils.c     # Gère les pipes et les redirections
)

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g)

# macOS : readline GNU installé par Homebrew (keg-only)
if(APPLE)
    execute_process(
        COMMAND brew --prefix readline
        OUTPUT_VARIABLE READLINE_PREFIX
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    target_include_directories(${PROJECT_NAME} PRIVATE ${READLINE_PREFIX}/include)
    target_link_directories(${PROJECT_NAME} PRIVATE ${READLINE_PREFIX}/lib)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE readline history)