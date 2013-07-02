         Convert OS/2 HLP files to OS/2 INF files
        ==========================================

  This program creates an OS/2 INF file from an OS/2 HLP file.
It simply copies the HLP file to a new file with the INF extension,
changing the four-byte header from "HSP\x10" to "HSP\x01".  There
may be more differences between HLP and INF files, but I haven't
seem them yet.  Don't ask me why IBM chose to distinguish between
the two file types, if this is their only difference . . .

  The command-line syntax is as follows:

        HLP2INF filename

  The source code and make file (MSC 6.00a) are included.  The information
required to make this program was obtained by simply comparing HLP and INF
files generated from the same IPF script.

  Questions, suggestions, criticisms to:

        Rick Papo
        Internet: rpapo@msen.com
        CompuServe: 72607,3111

