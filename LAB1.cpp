//
//
//run command g++ LAB1.cpp -lglut -lGL -lGLEW -g

#include "initShaders.h"
#include "vec.h"
#include <cstdlib>
#include <ctime>

using namespace std;
int counter=0;
const int numpoints=4000;

//vertexIDs
GLuint vaoID, vboID;// the buffers that are going to be linked too

//vertices
GLfloat vertexarray[]={0.5f,-0.5f,0.0f,0.0f,0.5f,0.0f,-0.5f,-0.5f,0.0f};// vertices that are drawn x,y,z ...
//indices of triangle
GLubyte indices[3]={0,1,2};

void init(){
	
	vec2 points[numpoints];
	float k;
	float j;
	srand(time(0));
	
	for(int i=0;i<numpoints;i++){
		switch(i%4){
			case 0:
			j=((float) rand()/RAND_MAX);
			k=((float) rand()/RAND_MAX-1);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 1:
			j=((float) rand()/RAND_MAX-1);
			k=((float) rand()/RAND_MAX-1);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 2:
			j=((float) rand()/RAND_MAX);
			k=((float) rand()/RAND_MAX);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			case 3:
			j=((float) rand()/RAND_MAX-1);
			k=((float) rand()/RAND_MAX);
			//cout << " j: "<< j << " k: " << k << endl;
			points[i]=vec2(j,k);
			break;
			}
	}
	
	glGenVertexArrays(1,&vaoID);
	glBindVertexArray(vaoID);
	
	glGenBuffers(1,&vboID);
	glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,sizeof(points),points,GL_STATIC_DRAW);
	
	
	ShaderInfo shaders[]={
  { GL_VERTEX_SHADER , "vertexshader.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader.glsl"},
  { GL_NONE , NULL} 
  };
  
	initShaders(shaders);
	
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,0,(void*)0);
	
}

//opengl 4
void triangle1(){
  glClear(GL_COLOR_BUFFER_BIT);//clears the screen
  
  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);//allocates the memory of the vertices

 ShaderInfo shaders[]={//create the shader specified by my initshaders 
  { GL_VERTEX_SHADER , "vertexshader1.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader1.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw

  glDrawArrays(GL_TRIANGLES, 0, 3);//draws array
  glFlush();//makes sure the prcesses finish
}

void triangle2(){
  glClear(GL_COLOR_BUFFER_BIT);//clear screen

  glGenVertexArrays(1, &vaoID);//generates object name for Vertex Array Objects
  glBindVertexArray(vaoID);//bind the object to the array

  glGenBuffers(1, &vboID);//generates object name for the Vertex Buffer Object
  glBindBuffer(GL_ARRAY_BUFFER, vboID);//bind the object to the array
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertexarray), vertexarray, GL_STATIC_DRAW);//allocates the memory of the vertices

 ShaderInfo shaders[]={//create the shader specified by my initshaders input
  { GL_VERTEX_SHADER , "vertexshader2.glsl"} ,
  { GL_FRAGMENT_SHADER , "fragmentshader2.glsl"},
  { GL_NONE , NULL} 
  };

  initShaders(shaders);//creates shaders
  	  	
  glEnableVertexAttribArray(0);//enables the vertex attribute index 
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);//specified the start the vertice array used to the draw
  
  glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, indices);//draws object based on indices of the polygon
  glDisableVertexAttribArray(0);
  glFlush();//make sure the processes finish
}

void drawscene(){
  switch(counter%3){//easy way to switch throw functions
    case 0:
      glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_POINTS,0,numpoints);
	glFlush();
      break;
    case 1:
      glutDisplayFunc(triangle1);
      glutPostRedisplay();//sets flags for opengl to redraw the display
      break;
    case 2:
      glutDisplayFunc(triangle2);
      glutPostRedisplay();
      break;
  }
}
//this function create the interaction with the mouse
void mousepress(int button, int state, int x, int y){
  if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)//right click closes the screen
    exit(0);
  else if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){//left click changes the shape color
    counter++;
    drawscene();
  }
}

void idle(void){
  glutPostRedisplay();
}

int main(int argc, char **argv){

	//Freeglut window and context management	
  glutInit(&argc, argv);
  glutCreateWindow("Lab01 Shapes");//creates the window with the specified name
  
  //initializes glew
  glewExperimental=GL_TRUE;
  if(glewInit()){
    fprintf(stderr, "Unable to initalize GLEW");
    exit(EXIT_FAILURE);
  }
  
  glutInitContextVersion(4, 3);//specifies the version of opengl
  glutInitContextProfile(GLUT_CORE_PROFILE|GLUT_COMPATIBILITY_PROFILE);//specifies what profile your using


  //retruns what version of opengl and glsl your computer can use
  const GLubyte* version=glGetString(GL_SHADING_LANGUAGE_VERSION);
  fprintf(stderr,"Opengl glsl version %s\n", version);

  version=glGetString(GL_VERSION);
  fprintf(stderr,"Opengl version %s\n", version);

  glutDisplayFunc(drawscene);//displays callback draws the shapes
  glutMouseFunc(mousepress);//control callback specifies the mouse controls
  glutMainLoop();//sets opengl state in a neverending loop
  return 0;
}

