/**
 * @file sch_assertion.h
 * @author Mike Strangewood (michael.a.strangewood@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2025-12-23
 *  
 */

#ifndef SCH_ASSERTION_H
#define SCH_ASSERTION_H

#ifdef __cplusplus
extern "C" {
#endif

/*--Weak macro definition----------------------------------------------------*/

/**
 * @brief 
 * 
 */
#if defined(__GNUC__)
  #define __WEAK __attribute__((weak))
#elif defined(__ICCARM__)
  #define __WEAK __weak
#elif defined(__ARMCC_VERSION)
  #define __WEAK __weak
#else
  #define __WEAK
#endif

/*--Checking compilation conditions------------------------------------------*/

/**
 * @brief Check macro definitions
 * 
 * @details Checking the definition of a macro, 
 * with the value of which the functions of the 
 * "function module" sch_assertion will later 
 * be called
 * 
 */
#ifdef SCH_ASSERTION_NORETURN
    #define SCH_NORETURN_FUNC_ATTRIBUTE __attribute__((noreturn))
#else
    #define SCH_NORETURN_FUNC_ATTRIBUTE
#endif

/**
 * @brief Check macro definitions
 * 
 * @details Checking the definition of the macro 
 * responsible for calling the sch_fault_handler 
 * error handler
 * 
 * @note The configuration of the sch_fault_handler 
 * function is determined, among other things, by 
 * the SCH_ASSERTION_NORETURN macro
 * 
 */
#ifdef SCH_ASSERTION
    #define SCH_ASSERT(expr) ((expr) ? ((void)0) : sch_fault_handler())
#else
    #define SCH_ASSERT(expr) ((expr) ? ((void)0) : sch_fault_handler())
#endif

/*--Definition of functions--------------------------------------------------*/

/**
 * @brief Error handling function
 * 
 * @note The function has an additional attribute 
 * for returning to the context from which the 
 * function was called. The value of this attribute 
 * depends on the definition (or non-definition) of 
 * the SCH_ASSERTION_NORETURN macro
 * 
 * @return void 
 */
__WEAK SCH_NORETURN_FUNC_ATTRIBUTE void sch_fault_handler(void);

/*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif