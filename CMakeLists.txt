cmake_minimum_required(VERSION 3.0.0)
project(Algorithm VERSION 0.1.0)

aux_source_directory(. MAIN)

aux_source_directory(./include/information INCLUDE_INFORMATION)
aux_source_directory(./include/tools INCLUDE_TOOLS)
aux_source_directory(./include/login INCLUDE_LOGIN)
aux_source_directory(./include/system INCLUDE_SYSTEM)
aux_source_directory(./include/student INCLUDE_STUDENT)


aux_source_directory(./information INFORMATION)
aux_source_directory(./tools TOOLS)
aux_source_directory(./login LOGIN)
aux_source_directory(./system SYSTEM)
aux_source_directory(./student STUDENT)


add_executable(
    Stu_Info_Manager
    ${MAIN} 

    ${INCLUDE_INFORMATION} 
    ${INCLUDE_TOOLS}
    ${INCLUDE_LOGIN} 
    ${INCLUDE_SYSTEM} 
    ${INCLUDE_STUDENT} 

    ${INFORMATION} 
    ${TOOLS}
    ${LOGIN} 
    ${SYSTEM} 
    ${STUDENT} 
    )
