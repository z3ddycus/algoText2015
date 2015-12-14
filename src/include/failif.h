/*
 * Imported Code from Christophe Hancart.
 */
#ifndef FAILIF_H
#define FAILIF_H

#ifdef XFAIL_IF

#define STR(expr) #expr
#define FAIL_IF(expr, cause)                                      \
  fail_if(__FILE__, __LINE__, __func__, expr, STR(expr), cause)

#else

#define FAIL_IF(expr, cause)                                  \
  fail_if(__FILE__, __LINE__, __func__, expr, #expr, cause)

#endif // XFAIL_IF

extern void fail_if(
  const char *file, int line, const char *func,
  int expr, const char *code, const char *cause);

#endif // FAILIF_H
