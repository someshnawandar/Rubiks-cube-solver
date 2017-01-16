#define LEN 8192
void glWindowPos4f(float x,float y,float z,float w)
{
   //  Integer versions of x and y
   int ix = (int)x;
   int iy = (int)y;
   //  Save transform attributes (Matrix Mode and Viewport)
   glPushAttrib(GL_TRANSFORM_BIT|GL_VIEWPORT_BIT);
   //  Save projection matrix and set identity
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   //  Save model view matrix and set to indentity
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   //  Set viewport to 2x2 pixels around (x,y)
   glViewport(ix-1,iy-1,2,2);
   //  Finally set the raster position
   glRasterPos4f(x-ix,y-iy,z,w);
   //  Reset model view matrix
   glPopMatrix();
   //  Reset projection matrix
   glMatrixMode(GL_PROJECTION);
   glPopMatrix();
   //  Pop transform attributes (Matrix Mode and Viewport)
   glPopAttrib();
}
void glWindowPos2i(int    x,int    y)                   {glWindowPos4f(x,y,0,1);}

void printv(va_list args, const char* format)
{
  char buf[LEN];
  char* ch=buf;
  vsnprintf(buf,LEN,format,args);
  while (*ch)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

void print(const char* format, ...)
{
  va_list args;
  va_start(args,format);
  printv(args,format);
  va_end(args);
}

void printAt(int x, int y, const char* format, ...)
{
  va_list args;
    glWindowPos2i(x,y) ;
 va_start(args,format);
  printv(args,format);
  va_end(args);
}

/*
 *  Convenience method to print out OpenGL errors to stderr
 */
void errCheck(char* where)
{
   int err = glGetError();
   if (err) fprintf(stderr,"ERROR: %s [%s]\n",gluErrorString(err),where);
}
