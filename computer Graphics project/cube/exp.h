
#define NUM_PARTICLES    100000                      // Number of particles
#define NUM_triparts       1000                         // Number of triparts





	struct particleData
	{
	  float   position[3];                           // structure required for particle type.
	  float   speed[3];
	  float   color[3];
	};
	typedef struct particleData    particleData;


                                                        // structure for traingle creation.

	struct tripartsData
	{
	  float   position[3];
	  float   speed[3];
	  float   orientation[3];                         // Rotation angles around x,y,z.
	  float   orientationSpeed[3];
	  float   color[3];
	  float   scale[3];
	};
	typedef struct tripartsData    tripartsData;

	particleData     particles[NUM_PARTICLES];
	tripartsData       triparts[NUM_triparts];
	int   timeout = 0;                                                  // timeout for the explosion
	float   angle = 0.0;


		int      wantNormalize = 0;                                           // flag for speed vector
		int      wantPause = 0;                                               // flag to pause

void newSpeed (float dest[3])
{
		  float    x;
		  float    y;
		  float    z;
		  float    len;

		  x = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
		  y = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;               // randomize speed of the particles.
		  z = (2.0 * ((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;


		  if (wantNormalize)
			{
			  len = sqrt (x * x + y * y + z * z);

			  if (len)
			{
			  x = x / len;
			  y = y / len;
			  z = z / len;                                  // code to give fireball effect.
			}
			}

		  dest[0] = x;
		  dest[1] = y;
		  dest[2] = z;
}

void newExplosion (void)
{
		  int    i;

		/*  for (i = 0; i < NUM_PARTICLES/6; i++)
			{
			  particles[i].position[0] = 0.0;
			  particles[i].position[1] = 0.0;
			  particles[i].position[2] = 0.0;

			  particles[i].color[0] = 1.0;
			  particles[i].color[1] = 0.0;
			  particles[i].color[2] = 0.0;                      // create a new explosion

			  newSpeed (particles[i].speed);
			}
			  for (i = NUM_PARTICLES/6; i < 2*NUM_PARTICLES/6; i++)
			{
			  particles[i].position[0] = 0.0;
			  particles[i].position[1] = 0.0;
			  particles[i].position[2] = 0.0;

			  particles[i].color[0] = 0.0;
			  particles[i].color[1] = 1.0;
			  particles[i].color[2] = 0.0;                      // create a new explosion

			  newSpeed (particles[i].speed);
			}
			for (i = 2*NUM_PARTICLES/6; i < 3*NUM_PARTICLES/6; i++)
			{
			  particles[i].position[0] = 0.0;
			  particles[i].position[1] = 0.0;
			  particles[i].position[2] = 0.0;

			  particles[i].color[0] = 0.0;
			  particles[i].color[1] = 0.0;
			  particles[i].color[2] = 1.0;                      // create a new explosion

			  newSpeed (particles[i].speed);
			}
			for (i = 3*NUM_PARTICLES/6; i < 4*NUM_PARTICLES/6; i++)
			{
			  particles[i].position[0] = 0.0;
			  particles[i].position[1] = 0.0;
			  particles[i].position[2] = 0.0;

			  particles[i].color[0] = 1.0;
			  particles[i].color[1] = 1.0;
			  particles[i].color[2] = 0.0;                      // create a new explosion

			  newSpeed (particles[i].speed);
			}
			for (i = 4*NUM_PARTICLES/6; i < 5*NUM_PARTICLES/6; i++)
			{
			  particles[i].position[0] = 0.0;
			  particles[i].position[1] = 0.0;
			  particles[i].position[2] = 0.0;

			  particles[i].color[0] = 1.0;
			  particles[i].color[1] = 1.0;
			  particles[i].color[2] = 1.0;                      // create a new explosion

			  newSpeed (particles[i].speed);
			}*/
        for(int i = 0;i< NUM_triparts/6;i++)
        {
              triparts[i].color[0] = 1;
			  triparts[i].color[1] = 0;
			  triparts[i].color[2] = 0;
        }
        for(int i = NUM_triparts/6;i< 2*NUM_triparts/6;i++)
        {
              triparts[i].color[0] = 0;
			  triparts[i].color[1] = 1;
			  triparts[i].color[2] = 0;
        }
        for(int i =2*NUM_triparts/6;i< 3*NUM_triparts;i++)
        {
              triparts[i].color[0] = 0;
			  triparts[i].color[1] = 0;
			  triparts[i].color[2] = 1;
        }
        for(int i =3*NUM_triparts/6;i< 4*NUM_triparts;i++)
        {
              triparts[i].color[0] = 1;
			  triparts[i].color[1] = 1;
			  triparts[i].color[2] = 0;
        }
        for(int i =4*NUM_triparts/6;i< 5*NUM_triparts;i++)
        {
              triparts[i].color[0] = 1;
			  triparts[i].color[1] = 1;
			  triparts[i].color[2] = 1;
        }
		  for (i = 0; i < NUM_triparts; i++)
			{
			  triparts[i].position[0] = 0.0;
			  triparts[i].position[1] = 0.0;
			  triparts[i].position[2] = 0.0;

			  triparts[i].orientation[0] = 0.0;
			  triparts[i].orientation[1] = 0.0;
			  triparts[i].orientation[2] = 0.0;



			  triparts[i].scale[0] = (2.0 *
						((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
			  triparts[i].scale[1] = (2.0 *
						((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;
			  triparts[i].scale[2] = (2.0 *
						((GLfloat) rand ()) / ((GLfloat) RAND_MAX)) - 1.0;

			  newSpeed (triparts[i].speed);
			  newSpeed (triparts[i].orientationSpeed);
			}

		  timeout = 1100;
}


void display2 (void)                                                            // display the scene
{
		  int    i;

		  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		  glLoadIdentity ();

		                                                                           // Place the camera
		  glTranslated (0, 0, -1);

		  glRotatef (angle, 0.0, 1.0, 0.0);



		  if (timeout > 0)
			{
			  /*glPushMatrix ();

		//	 glDisable (GL_LIGHTING);
		//	 glDisable (GL_DEPTH_TEST);

			  glBegin (GL_POINTS);

			  for (i = 0; i < NUM_PARTICLES; i++)
			{                                                              //update particle colour and position
			  glColor3fv (particles[i].color);
			  glVertex3fv (particles[i].position);
			}

			  glEnd ();

			  glPopMatrix ();*/
//
		//	 glEnable (GL_LIGHTING);
		//	 glEnable (GL_LIGHT0);
			// glEnable (GL_DEPTH_TEST);

			 // glNormal3f (0.0, 0.0, 1.0);

			  for (i = 0; i < NUM_triparts; i++)
			{
			  glColor3fv (triparts[i].color);                             // update triangle-positions and colour

			  glPushMatrix ();

			  glTranslatef (triparts[i].position[0],
					triparts[i].position[1],
					triparts[i].position[2]);

			  glRotatef (triparts[i].orientation[0], 1.0, 0.0, 0.0);
			  glRotatef (triparts[i].orientation[1], 0.0, 1.0, 0.0);
			  glRotatef (triparts[i].orientation[2], 0.0, 0.0, 1.0);

			  glScalef (triparts[i].scale[0],
					triparts[i].scale[1],
					triparts[i].scale[2]);

			  glBegin (GL_TRIANGLES);
			  glVertex3f (0.0, 0.5, 0.0);
			  glVertex3f (-0.25, 0.0, 0.0);
			  glVertex3f (0.25, 0.0, 0.0);
			  glEnd ();

			  glPopMatrix ();
			}
			}

		  glutSwapBuffers ();
}






void idle (void)
{
		  int    i;
			 printAt(100,0,"THANKYOU!");

		  if (!wantPause)
			{
			  if (timeout > 0)
			{

			/*  for (i = 0; i < NUM_PARTICLES; i++)
				{
				  particles[i].position[0] += particles[i].speed[0] * 0.1;
				  particles[i].position[1] += particles[i].speed[1] * 0.1;
				  particles[i].position[2] += particles[i].speed[2] * 0.1;

				  particles[i].color[0] -= 1.0 / 500.0;
				  if (particles[i].color[0] < 0.0)
				{
				  particles[i].color[0] = 0.0;                                          // function to define state of particles in static motion
				}

				  particles[i].color[1] -= 1.0 / 100.0;
				  if (particles[i].color[1] < 0.0)
				{
				  particles[i].color[1] = 0.0;
				}

				  particles[i].color[2] -= 1.0 / 50.0;
				  if (particles[i].color[2] < 0.0)
				{
				  particles[i].color[2] = 0.0;
				}
				}*/

			  for (i = 0; i < NUM_triparts; i++)
				{
				  triparts[i].position[0] += triparts[i].speed[0] * 0.1;
				  triparts[i].position[1] += triparts[i].speed[1] * 0.1;
				  triparts[i].position[2] += triparts[i].speed[2] * 0.1;

				  triparts[i].orientation[0] += triparts[i].orientationSpeed[0] * 10;
				  triparts[i].orientation[1] += triparts[i].orientationSpeed[1] * 10;
				  triparts[i].orientation[2] += triparts[i].orientationSpeed[2] * 10;
				}

			  --timeout;
			}

			  angle += 0.3;                                                        // Always continue to rotate the camera
			}

		  glutPostRedisplay ();
}

