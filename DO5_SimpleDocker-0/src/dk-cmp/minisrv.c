#include <stdio.h>
#include <stdlib.h>
#include "fcgiapp.h"

int main() {
  FCGX_Init();
  FCGX_Request req;
  FCGX_InitRequest(&req, 0, 0);

  while (FCGX_Accept_r(&req) >= 0) {
    FCGX_FPrintF(req.out, "Content-Type: text/html\n\n");
    FCGX_FPrintF(req.out, "\n"); 
    FCGX_FPrintF(req.out, "\r<head>\n");  
    FCGX_FPrintF(req.out, "\r<title> Hello locie! </title>\n");
    FCGX_FPrintF(req.out, "\r<head>\n");
    FCGX_FPrintF(req.out, "<html>\n");
    FCGX_FPrintF(req.out, "\r<body>\n");
    FCGX_FPrintF(req.out, "\r<h1> Hello World! </h1>\n");
    FCGX_FPrintF(req.out, "\r</body>\n");
    FCGX_FPrintF(req.out, "</html>\n");
    FCGX_Finish_r(&req);
  }
}
