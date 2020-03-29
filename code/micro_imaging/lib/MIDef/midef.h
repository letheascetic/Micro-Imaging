#ifndef MIDEF_H
#define MIDEF_H

/******************************************
 *             Definitions
 ******************************************/
#define API_RETURN_CODE_STARTS 0x200 /* Starting return code */

/* API Return Code Values */
typedef enum _MI_RESULTS
{
    API_SUCCESS = API_RETURN_CODE_STARTS,    // 512
    APC_FAILED                               // 513
} MI_RESULTS;


#endif // MIDEF_H
