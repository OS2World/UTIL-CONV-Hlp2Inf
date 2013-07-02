#include <io.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

   // Function Prototypes

extern int main ( int argc, char *argv[] ) ;


   // Main Program

extern int main ( int argc, char *argv[] ) {

   char Buffer [0x1000] ;
   int BytesRead ;
   int Error ;
   FILE *File1, *File2 ;
   char Filename [_MAX_PATH] = { 0 } ;
   char Drive[_MAX_DRIVE], Dir[_MAX_DIR], Fname[_MAX_FNAME], Ext[_MAX_EXT];
   char Filename2 [_MAX_PATH] ;

   while ( --argc ) {
      argv ++ ;
      strupr ( *argv ) ;

      if ( *argv[0] == '?' ) {
	 printf ( "HLP2INF: Create OS/2 INF file from OS/2 HLP file.\n"
            "\n"
            "Parameters:\n"
	    "  Filename       Name of file to convert.\n"
         ) ;
         return ( 0 ) ;
      } /* endif */

      if ( Filename[0] == 0 ) {
         strcpy ( Filename, *argv ) ;
         if ( access ( Filename, 0 ) ) {
            fprintf ( stderr, "ERROR: File '%s' doesn't exist.", Filename ) ;
            return ( 1 ) ;
         } /* endif */
         continue ;
      } /* endif */

      fprintf ( stderr, "ERROR: Unrecognized option '%s'.", *argv ) ;
      return ( 1 ) ;

   } /* endwhile */

   _splitpath ( Filename, Drive, Dir, Fname, Ext ) ;
   strcpy ( Filename2, Drive ) ;
   strcat ( Filename2, Dir ) ;
   strcat ( Filename2, Fname ) ;
   strcat ( Filename2, ".INF" ) ;
   if ( access ( Filename2, 0 ) == 0 ) {
      fprintf ( stderr, "ERROR: File '%s' already exists.", Filename2 ) ;
      return ( 1 ) ;
   } /* endif */

   Error = 0 ;
   File1 = fopen ( Filename, "rb" ) ;
   if ( File1 ) {
      BytesRead = fread ( Buffer, 1, sizeof(Buffer), File1 ) ;
      if ( memcmp ( Buffer, "HSP\x10", 4 ) ) {
	 fprintf ( stderr, "ERROR: File header invalid for HLP." ) ;
	 Error = 1 ;
      } else {
	 File2 = fopen ( Filename2, "wb" ) ;
	 if ( File2 ) {
	    Buffer[3] = 1 ;
	    while ( BytesRead ) {
	       fwrite ( Buffer, 1, BytesRead, File2 ) ;
	       BytesRead = fread ( Buffer, 1, sizeof(Buffer), File1 ) ;
	    } /* endwhile */
	    fclose ( File2 ) ;
	 } else {
	    fprintf ( stderr, "ERROR: Unable to create '%s'.", Filename2 ) ;
	    Error = 1 ;
	 } /* endif */
      } /* endif */
      fclose ( File1 ) ;
   } else {
      fprintf ( stderr, "ERROR: Unable to open '%s'.", Filename ) ;
      Error = 1 ;
   } /* endif */

   return ( Error ) ;
}
