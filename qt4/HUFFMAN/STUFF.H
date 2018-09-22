typedef	unsigned char		byte;
typedef	unsigned short		word;
typedef	unsigned long		dword;
typedef	unsigned			bit;

#define	TRUE		1
#define 	FALSE	0
#define	SUCCESS	0
#define   FAILURE	1
#define	ERROR	2

#if defined( BETATEST ) && defined( VERSIONE ) && ( VERSIONE == 0 )
#   define  BETATEST
#endif

#if defined( MAIN )
# define  GLOBAL
#else
#   define GLOBAL extern
#endif