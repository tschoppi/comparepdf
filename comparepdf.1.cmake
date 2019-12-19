.TH COMPAREPDF 1 "@COMPAREPDF_DATE@" "comparepdf v@COMPAREPDF_VERSION@"
.SH NAME
comparepdf \- compare two PDF files textually or visually
.SH SYNOPSIS
.B diffpdf
.RI [ file1 ]
.RI [ file2 ]
.SH SYNOPSIS
.B comparepdf
.RI [OPTIONS]
.RI file1.pdf
.RI file2.pdf
.SH DESCRIPTION
\fBcomparepdf\fP is a command line application used to compare two PDF
files.
.br
The default comparison mode is text mode where the text of each
corresponding pair of pages is compared. As soon as a difference is
detected the program terminates with a message (unless -v0 is set) and
an indicative return code.
.br
The OPTIONS are -ct or --compare=text (the default) for text mode
comparisons or -ca or --compare=appearance for visual comparisons
(useful if diagrams or other images have changed), and -v=1 or
--verbose=1 for reporting differences (and saying nothing for matching
files): use -v=0 for no reporting or -v=2 for reporting both different
and matching files.
.SH "SEE ALSO"
For a GUI tool for showing the detailed differences between PDF files see
http://www.qtrac.eu/diffpdf.html.
.SH AUTHOR
comparepdf was written by Mark Summerfield <mark@qtrac.eu>.
