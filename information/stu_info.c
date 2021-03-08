#include "../include/information/stu_info_basic.h"

int get_college(char *college, Col_Type ctype)
{
    switch (ctype)
    {
    case COMMUNICATION:
        strcat(college, "communication");
        break;
    case COMPUTER:
        strcat(college, "computer");
        break;
    case AUTOMATION:
        strcat(college, "automation");
        break;
    case MANUFACTURE:
        strcat(college, "manufacture");
        break;
    case PHOTOELECTRICITY:
        strcat(college, "photoelectricity");
        break;
    case SOFTWARE:
        strcat(college, "software");
        break;
    case SCIENCE:
        strcat(college, "science");
        break;
    case MANAGEMENT:
        strcat(college, "management");
        break;
    case MEDIA:
        strcat(college, "media");
        break;
    case FOREIGH:
        strcat(college, "forigh");
        break;
    case INTERNATIONAL:
        strcat(college, "internationmal");
        break;
    case LAW:
        strcat(college, "law");
        break;
    default:
        return 0;
    }
    return 1;
}

int get_stype(char *student, Stu_Type stype)
{
    switch (stype)
    {
    case BACHELOR:
        strcat(student, "bachelor");
        break;
    case MASTER:
        strcat(student, "master");
        break;
    case DOCTOR:
        strcat(student, "doctor");
        break;
    default:
        return 0;
    }
    return 1;
}